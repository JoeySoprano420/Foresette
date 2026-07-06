// foresettec.cpp
// Foresette .4se Bootstrap Compiler
// C++20 single-file implementation
//
// What this compiler does:
//   - Lexes Foresette source
//   - Parses programs, entries, slots, memory, permissions, errors, handlers,
//     routes, loops, if/else, match/case, parallel/concurrent/path, wait/signal,
//     lock/unlock, imports/exports/external/native, attempt/bypass/stop
//   - Builds semantic permission tables
//   - Performs basic permission validation
//   - Emits portable C++20 source code as the first backend
//
// Build:
//   g++ -std=c++20 -O2 foresettec.cpp -o foresettec
//   MSVC: cl /std:c++20 /EHsc foresettec.cpp
//
// Use:
//   foresettec input.4se -o output.cpp
//   then compile output.cpp with your C++ compiler.

#include <algorithm>
#include <cctype>
#include <cstdint>
#include <cstdlib>
#include <fstream>
#include <iostream>
#include <map>
#include <memory>
#include <optional>
#include <set>
#include <sstream>
#include <stdexcept>
#include <string>
#include <unordered_map>
#include <utility>
#include <variant>
#include <vector>

namespace fs4 {

// ================================================================
// Diagnostics
// ================================================================

struct SourceLoc {
    int line = 1;
    int col = 1;
};

struct CompileError : public std::runtime_error {
    SourceLoc loc;
    explicit CompileError(SourceLoc l, const std::string& msg)
        : std::runtime_error("[line " + std::to_string(l.line) + ", col " + std::to_string(l.col) + "] " + msg), loc(l) {}
};

// ================================================================
// Lexer
// ================================================================

enum class TokenKind {
    End,
    Newline,
    Identifier,
    Integer,
    Float,
    String,
    Boolean,
    NullLit,

    // Keywords
    Program, Entry, EndKw, Slot, Memory, Dedicated, Assign,
    Permit, Deny, Read, Change, Move, Share, Expose, Enter, Leave,
    Delegate, From, To, With, Return, Stop, Bypass,
    Error, Handle, Attempt, Route, Path, Parallel, Concurrent,
    Sync, Wait, Signal, Lock, Unlock,
    If, Else, When, Case, Match, Repeat, While, For, Each,
    Break, Continue, Import, Export, External, Native,

    // Operators / punctuation
    Plus, Minus, Star, Slash, Percent,
    EqEq, NotEq, Less, LessEq, Greater, GreaterEq,
    AndAnd, OrOr, Not,
    LParen, RParen, LBracket, RBracket,
    Comma, Dot, Colon,
};

struct Token {
    TokenKind kind = TokenKind::End;
    std::string text;
    SourceLoc loc;
};

static std::string kindName(TokenKind k) {
    switch (k) {
        case TokenKind::End: return "EOF";
        case TokenKind::Newline: return "NEWLINE";
        case TokenKind::Identifier: return "identifier";
        case TokenKind::Integer: return "integer";
        case TokenKind::Float: return "float";
        case TokenKind::String: return "string";
        case TokenKind::Boolean: return "boolean";
        case TokenKind::NullLit: return "null";
        default: return "token";
    }
}

class Lexer {
    std::string src;
    size_t pos = 0;
    int line = 1;
    int col = 1;
    std::unordered_map<std::string, TokenKind> keywords;

public:
    explicit Lexer(std::string s) : src(std::move(s)) {
        keywords = {
            {"program", TokenKind::Program}, {"entry", TokenKind::Entry}, {"end", TokenKind::EndKw},
            {"slot", TokenKind::Slot}, {"memory", TokenKind::Memory}, {"dedicated", TokenKind::Dedicated},
            {"assign", TokenKind::Assign}, {"permit", TokenKind::Permit}, {"deny", TokenKind::Deny},
            {"read", TokenKind::Read}, {"change", TokenKind::Change}, {"move", TokenKind::Move},
            {"share", TokenKind::Share}, {"expose", TokenKind::Expose}, {"enter", TokenKind::Enter},
            {"leave", TokenKind::Leave}, {"delegate", TokenKind::Delegate}, {"from", TokenKind::From},
            {"to", TokenKind::To}, {"with", TokenKind::With}, {"return", TokenKind::Return},
            {"stop", TokenKind::Stop}, {"bypass", TokenKind::Bypass}, {"error", TokenKind::Error},
            {"handle", TokenKind::Handle}, {"attempt", TokenKind::Attempt}, {"route", TokenKind::Route},
            {"path", TokenKind::Path}, {"parallel", TokenKind::Parallel}, {"concurrent", TokenKind::Concurrent},
            {"sync", TokenKind::Sync}, {"wait", TokenKind::Wait}, {"signal", TokenKind::Signal},
            {"lock", TokenKind::Lock}, {"unlock", TokenKind::Unlock}, {"if", TokenKind::If},
            {"else", TokenKind::Else}, {"when", TokenKind::When}, {"case", TokenKind::Case},
            {"match", TokenKind::Match}, {"repeat", TokenKind::Repeat}, {"while", TokenKind::While},
            {"for", TokenKind::For}, {"each", TokenKind::Each}, {"break", TokenKind::Break},
            {"continue", TokenKind::Continue}, {"import", TokenKind::Import}, {"export", TokenKind::Export},
            {"external", TokenKind::External}, {"native", TokenKind::Native},
            {"true", TokenKind::Boolean}, {"false", TokenKind::Boolean}, {"null", TokenKind::NullLit}
        };
    }

    std::vector<Token> lexAll() {
        std::vector<Token> out;
        while (true) {
            Token t = next();
            out.push_back(t);
            if (t.kind == TokenKind::End) break;
        }
        return out;
    }

private:
    char peek(size_t off = 0) const {
        if (pos + off >= src.size()) return '\0';
        return src[pos + off];
    }

    char advance() {
        char c = peek();
        if (c == '\0') return c;
        ++pos;
        if (c == '\n') { ++line; col = 1; }
        else { ++col; }
        return c;
    }

    bool match(char c) {
        if (peek() == c) { advance(); return true; }
        return false;
    }

    SourceLoc loc() const { return {line, col}; }

    void skipWhitespaceButNotNewline() {
        while (true) {
            char c = peek();
            if (c == ' ' || c == '\t' || c == '\r') { advance(); continue; }
            if (c == '#') {
                while (peek() != '\n' && peek() != '\0') advance();
                continue;
            }
            if (c == '/' && peek(1) == '/') {
                while (peek() != '\n' && peek() != '\0') advance();
                continue;
            }
            break;
        }
    }

    Token make(TokenKind kind, std::string text, SourceLoc l) {
        return Token{kind, std::move(text), l};
    }

    Token next() {
        skipWhitespaceButNotNewline();
        SourceLoc l = loc();
        char c = peek();
        if (c == '\0') return make(TokenKind::End, "", l);
        if (c == '\n') { advance(); return make(TokenKind::Newline, "\\n", l); }

        if (std::isalpha(static_cast<unsigned char>(c)) || c == '_') {
            std::string s;
            while (std::isalnum(static_cast<unsigned char>(peek())) || peek() == '_') s += advance();
            auto it = keywords.find(s);
            if (it != keywords.end()) return make(it->second, s, l);
            return make(TokenKind::Identifier, s, l);
        }

        if (std::isdigit(static_cast<unsigned char>(c))) {
            std::string s;
            while (std::isdigit(static_cast<unsigned char>(peek()))) s += advance();
            if (peek() == '.' && std::isdigit(static_cast<unsigned char>(peek(1)))) {
                s += advance();
                while (std::isdigit(static_cast<unsigned char>(peek()))) s += advance();
                return make(TokenKind::Float, s, l);
            }
            return make(TokenKind::Integer, s, l);
        }

        if (c == '"') {
            advance();
            std::string s;
            while (peek() != '"' && peek() != '\0') {
                if (peek() == '\\') {
                    advance();
                    char e = advance();
                    switch (e) {
                        case 'n': s += '\n'; break;
                        case 't': s += '\t'; break;
                        case '"': s += '"'; break;
                        case '\\': s += '\\'; break;
                        default: s += e; break;
                    }
                } else {
                    s += advance();
                }
            }
            if (!match('"')) throw CompileError(l, "unterminated string literal");
            return make(TokenKind::String, s, l);
        }

        advance();
        switch (c) {
            case '+': return make(TokenKind::Plus, "+", l);
            case '-': return make(TokenKind::Minus, "-", l);
            case '*': return make(TokenKind::Star, "*", l);
            case '/': return make(TokenKind::Slash, "/", l);
            case '%': return make(TokenKind::Percent, "%", l);
            case '(': return make(TokenKind::LParen, "(", l);
            case ')': return make(TokenKind::RParen, ")", l);
            case '[': return make(TokenKind::LBracket, "[", l);
            case ']': return make(TokenKind::RBracket, "]", l);
            case ',': return make(TokenKind::Comma, ",", l);
            case '.': return make(TokenKind::Dot, ".", l);
            case ':': return make(TokenKind::Colon, ":", l);
            case '!':
                if (match('=')) return make(TokenKind::NotEq, "!=", l);
                return make(TokenKind::Not, "!", l);
            case '=':
                if (match('=')) return make(TokenKind::EqEq, "==", l);
                break;
            case '<':
                if (match('=')) return make(TokenKind::LessEq, "<=", l);
                return make(TokenKind::Less, "<", l);
            case '>':
                if (match('=')) return make(TokenKind::GreaterEq, ">=", l);
                return make(TokenKind::Greater, ">", l);
            case '&':
                if (match('&')) return make(TokenKind::AndAnd, "&&", l);
                break;
            case '|':
                if (match('|')) return make(TokenKind::OrOr, "||", l);
                break;
        }
        throw CompileError(l, std::string("unexpected character: ") + c);
    }
};

// ================================================================
// AST
// ================================================================

struct Expr;
struct Stmt;
using ExprPtr = std::unique_ptr<Expr>;
using StmtPtr = std::unique_ptr<Stmt>;

struct Expr {
    enum class Kind { Literal, Identifier, Binary, Unary, Call, Index, List } kind;
    SourceLoc loc;
    virtual ~Expr() = default;
};

struct LiteralExpr : Expr {
    std::string value;
    TokenKind litKind;
    LiteralExpr(SourceLoc l, std::string v, TokenKind k) : value(std::move(v)), litKind(k) { kind = Kind::Literal; loc = l; }
};
struct IdentifierExpr : Expr {
    std::string name;
    IdentifierExpr(SourceLoc l, std::string n) : name(std::move(n)) { kind = Kind::Identifier; loc = l; }
};
struct BinaryExpr : Expr {
    std::string op;
    ExprPtr left, right;
    BinaryExpr(SourceLoc l, std::string o, ExprPtr a, ExprPtr b) : op(std::move(o)), left(std::move(a)), right(std::move(b)) { kind = Kind::Binary; loc = l; }
};
struct UnaryExpr : Expr {
    std::string op;
    ExprPtr value;
    UnaryExpr(SourceLoc l, std::string o, ExprPtr v) : op(std::move(o)), value(std::move(v)) { kind = Kind::Unary; loc = l; }
};
struct CallExpr : Expr {
    std::string name;
    std::vector<ExprPtr> args;
    CallExpr(SourceLoc l, std::string n) : name(std::move(n)) { kind = Kind::Call; loc = l; }
};
struct IndexExpr : Expr {
    std::string base;
    ExprPtr index;
    IndexExpr(SourceLoc l, std::string b, ExprPtr i) : base(std::move(b)), index(std::move(i)) { kind = Kind::Index; loc = l; }
};
struct ListExpr : Expr {
    std::vector<ExprPtr> items;
    explicit ListExpr(SourceLoc l) { kind = Kind::List; loc = l; }
};

struct Stmt {
    enum class Kind {
        MemoryDecl, SlotDecl, Assign, Permission, Delegate,
        Return, Stop, Bypass, Break, Continue,
        If, When, Match, Repeat, While, For, Each,
        ErrorDecl, Handle, Attempt, Route,
        Parallel, Concurrent, Path,
        Sync, Wait, Signal, Lock, Unlock,
        Import, Export, External, Native
    } kind;
    SourceLoc loc;
    virtual ~Stmt() = default;
};

struct Block {
    std::vector<StmtPtr> statements;
};

struct MemoryDecl : Stmt { std::string name; MemoryDecl(SourceLoc l, std::string n) : name(std::move(n)) { kind=Kind::MemoryDecl; loc=l; } };
struct SlotDecl : Stmt { std::string name; std::optional<std::string> memory; ExprPtr value; bool hasValue=false; SlotDecl(SourceLoc l,std::string n):name(std::move(n)){kind=Kind::SlotDecl;loc=l;} };
struct AssignStmt : Stmt { std::string name; ExprPtr index; bool indexed=false; ExprPtr value; AssignStmt(SourceLoc l,std::string n):name(std::move(n)){kind=Kind::Assign;loc=l;} };
struct PermissionStmt : Stmt { bool grant=true; std::string perm,target; PermissionStmt(SourceLoc l,bool g,std::string p,std::string t):grant(g),perm(std::move(p)),target(std::move(t)){kind=Kind::Permission;loc=l;} };
struct DelegateStmt : Stmt { std::string value, perm, target; bool hasPerm=false; DelegateStmt(SourceLoc l,std::string v,std::string t):value(std::move(v)),target(std::move(t)){kind=Kind::Delegate;loc=l;} };
struct ReturnStmt : Stmt { ExprPtr value; bool hasValue=false; explicit ReturnStmt(SourceLoc l){kind=Kind::Return;loc=l;} };
struct SimpleStmt : Stmt { explicit SimpleStmt(SourceLoc l, Kind k){kind=k;loc=l;} };
struct IfStmt : Stmt { ExprPtr cond; Block thenBlock, elseBlock; bool hasElse=false; explicit IfStmt(SourceLoc l){kind=Kind::If;loc=l;} };
struct WhenStmt : Stmt { ExprPtr cond; Block body; explicit WhenStmt(SourceLoc l){kind=Kind::When;loc=l;} };
struct MatchCase { ExprPtr value; Block body; SourceLoc loc; };
struct MatchStmt : Stmt { ExprPtr value; std::vector<MatchCase> cases; Block elseBlock; bool hasElse=false; explicit MatchStmt(SourceLoc l){kind=Kind::Match;loc=l;} };
struct RepeatStmt : Stmt { ExprPtr count; Block body; explicit RepeatStmt(SourceLoc l){kind=Kind::Repeat;loc=l;} };
struct WhileStmt : Stmt { ExprPtr cond; Block body; explicit WhileStmt(SourceLoc l){kind=Kind::While;loc=l;} };
struct ForStmt : Stmt { std::string var; ExprPtr from,to; Block body; explicit ForStmt(SourceLoc l){kind=Kind::For;loc=l;} };
struct EachStmt : Stmt { std::string var, collection; Block body; EachStmt(SourceLoc l,std::string v,std::string c):var(std::move(v)),collection(std::move(c)){kind=Kind::Each;loc=l;} };
struct ErrorDecl : Stmt { std::string name; std::vector<std::string> fields; ErrorDecl(SourceLoc l,std::string n):name(std::move(n)){kind=Kind::ErrorDecl;loc=l;} };
struct HandleStmt : Stmt { std::string name; Block body; HandleStmt(SourceLoc l,std::string n):name(std::move(n)){kind=Kind::Handle;loc=l;} };
struct AttemptStmt : Stmt { std::string name; AttemptStmt(SourceLoc l,std::string n):name(std::move(n)){kind=Kind::Attempt;loc=l;} };
struct RouteStmt : Stmt { std::string from,to; RouteStmt(SourceLoc l,std::string a,std::string b):from(std::move(a)),to(std::move(b)){kind=Kind::Route;loc=l;} };
struct BlockStmt : Stmt { Block body; explicit BlockStmt(SourceLoc l,Kind k){kind=k;loc=l;} };
struct PathStmt : Stmt { std::string name; Block body; PathStmt(SourceLoc l,std::string n):name(std::move(n)){kind=Kind::Path;loc=l;} };
struct NamedStmt : Stmt { std::string name; NamedStmt(SourceLoc l,Kind k,std::string n):name(std::move(n)){kind=k;loc=l;} };

struct EntryDecl {
    std::string name;
    SourceLoc loc;
    Block body;
};

struct Program {
    std::string name;
    std::vector<StmtPtr> top; // imports, exports, externals, native, errors, routes
    std::vector<EntryDecl> entries;
};

// ================================================================
// Parser
// ================================================================

class Parser {
    std::vector<Token> toks;
    size_t pos = 0;
public:
    explicit Parser(std::vector<Token> t) : toks(std::move(t)) {}

    Program parseProgram() {
        Program p;
        skipNewlines();
        while (check(TokenKind::Import) || check(TokenKind::External) || check(TokenKind::Native) || check(TokenKind::Export)) {
            p.top.push_back(parseTopSimple());
            skipNewlines();
        }
        Token prog = consume(TokenKind::Program, "expected 'program'");
        Token name = consume(TokenKind::Identifier, "expected program name");
        p.name = name.text;
        consumeLine();
        skipNewlines();
        while (!check(TokenKind::End)) {
            if (check(TokenKind::End)) break;
            if (match(TokenKind::Entry)) {
                p.entries.push_back(parseEntry(previous()));
            } else if (check(TokenKind::Error)) {
                p.top.push_back(parseErrorDecl());
            } else if (check(TokenKind::Route) || check(TokenKind::Export) || check(TokenKind::Import) || check(TokenKind::External) || check(TokenKind::Native)) {
                p.top.push_back(parseStatement());
            } else if (check(TokenKind::End)) {
                break;
            } else if (check(TokenKind::End)) {
                break;
            } else if (check(TokenKind::End) || check(TokenKind::End)) {
                break;
            } else if (check(TokenKind::End) || check(TokenKind::End)) {
                break;
            } else if (check(TokenKind::End) || check(TokenKind::End)) {
                break;
            } else if (check(TokenKind::End)) {
                break;
            } else if (check(TokenKind::End) || check(TokenKind::End)) {
                break;
            } else if (check(TokenKind::End) || check(TokenKind::End)) {
                break;
            } else if (check(TokenKind::End) || check(TokenKind::End)) {
                break;
            } else if (check(TokenKind::End)) {
                break;
            } else if (check(TokenKind::End) || check(TokenKind::End)) {
                break;
            } else if (check(TokenKind::End) || check(TokenKind::End)) {
                break;
            } else if (check(TokenKind::End)) {
                break;
            } else if (check(TokenKind::End)) {
                break;
            } else if (check(TokenKind::End)) {
                break;
            } else if (check(TokenKind::End)) {
                break;
            } else if (check(TokenKind::End)) {
                break;
            } else if (check(TokenKind::End)) {
                break;
            } else if (check(TokenKind::End)) {
                break;
            } else if (check(TokenKind::End)) {
                break;
            } else if (check(TokenKind::End)) {
                break;
            } else if (check(TokenKind::End)) {
                break;
            } else if (check(TokenKind::End)) {
                break;
            } else if (check(TokenKind::End)) {
                break;
            } else if (check(TokenKind::End)) {
                break;
            } else if (check(TokenKind::End)) {
                break;
            } else if (check(TokenKind::End)) {
                break;
            } else if (check(TokenKind::End)) {
                break;
            } else if (check(TokenKind::End)) {
                break;
            } else if (check(TokenKind::End)) {
                break;
            } else if (isAtEnd()) break;
            else throw CompileError(peek().loc, "expected top-level declaration: entry, error, import, export, external, native, or route");
            skipNewlines();
        }
        return p;
    }

private:
    bool isAtEnd() const { return peek().kind == TokenKind::End; }
    const Token& peek() const { return toks[pos]; }
    const Token& previous() const { return toks[pos-1]; }
    bool check(TokenKind k) const { return peek().kind == k; }
    bool match(TokenKind k) { if (check(k)) { ++pos; return true; } return false; }
    Token consume(TokenKind k, const std::string& msg) {
        if (check(k)) return toks[pos++];
        throw CompileError(peek().loc, msg + ", got " + kindName(peek().kind));
    }
    void skipNewlines() { while (match(TokenKind::Newline)) {} }
    void consumeLine() {
        if (match(TokenKind::Newline) || check(TokenKind::End)) return;
        if (peek().kind == TokenKind::End) return;
        throw CompileError(peek().loc, "expected end of line");
    }

    StmtPtr parseTopSimple() { return parseStatement(); }

    EntryDecl parseEntry(Token start) {
        Token name = consume(TokenKind::Identifier, "expected entry name");
        consumeLine();
        EntryDecl e; e.name = name.text; e.loc = start.loc;
        e.body = parseBlockUntil({TokenKind::EndKw});
        consume(TokenKind::EndKw, "expected 'end' after entry");
        if (check(TokenKind::Newline)) consumeLine();
        return e;
    }

    Block parseBlockUntil(const std::set<TokenKind>& enders) {
        Block b;
        skipNewlines();
        while (!isAtEnd() && !enders.count(peek().kind)) {
            b.statements.push_back(parseStatement());
            skipNewlines();
        }
        return b;
    }

    StmtPtr parseStatement() {
        skipNewlines();
        Token t = peek();
        if (match(TokenKind::Import)) return parseNamedLine<NamedStmt>(t, Stmt::Kind::Import);
        if (match(TokenKind::Export)) return parseNamedLine<NamedStmt>(t, Stmt::Kind::Export);
        if (match(TokenKind::External)) return parseNamedLine<NamedStmt>(t, Stmt::Kind::External);
        if (match(TokenKind::Native)) return parseNamedLine<NamedStmt>(t, Stmt::Kind::Native);
        if (match(TokenKind::Memory)) return parseMemory(t);
        if (match(TokenKind::Slot)) return parseSlot(t);
        if (match(TokenKind::Permit)) return parsePermission(t, true);
        if (match(TokenKind::Deny)) return parsePermission(t, false);
        if (match(TokenKind::Delegate)) return parseDelegate(t);
        if (match(TokenKind::Return)) return parseReturn(t);
        if (match(TokenKind::Stop)) { consumeLine(); return std::make_unique<SimpleStmt>(t.loc, Stmt::Kind::Stop); }
        if (match(TokenKind::Bypass)) { consumeLine(); return std::make_unique<SimpleStmt>(t.loc, Stmt::Kind::Bypass); }
        if (match(TokenKind::Break)) { consumeLine(); return std::make_unique<SimpleStmt>(t.loc, Stmt::Kind::Break); }
        if (match(TokenKind::Continue)) { consumeLine(); return std::make_unique<SimpleStmt>(t.loc, Stmt::Kind::Continue); }
        if (match(TokenKind::Error)) return parseErrorDeclAfter(t);
        if (match(TokenKind::Handle)) return parseHandle(t);
        if (match(TokenKind::Attempt)) return parseAttempt(t);
        if (match(TokenKind::Route)) return parseRoute(t);
        if (match(TokenKind::Parallel)) return parseBlockStmt(t, Stmt::Kind::Parallel);
        if (match(TokenKind::Concurrent)) return parseConcurrent(t);
        if (match(TokenKind::Sync)) return parseNamedLine<NamedStmt>(t, Stmt::Kind::Sync);
        if (match(TokenKind::Wait)) return parseNamedLine<NamedStmt>(t, Stmt::Kind::Wait);
        if (match(TokenKind::Signal)) return parseNamedLine<NamedStmt>(t, Stmt::Kind::Signal);
        if (match(TokenKind::Lock)) return parseNamedLine<NamedStmt>(t, Stmt::Kind::Lock);
        if (match(TokenKind::Unlock)) return parseNamedLine<NamedStmt>(t, Stmt::Kind::Unlock);
        if (match(TokenKind::If)) return parseIf(t);
        if (match(TokenKind::When)) return parseWhen(t);
        if (match(TokenKind::Match)) return parseMatch(t);
        if (match(TokenKind::Repeat)) return parseRepeat(t);
        if (match(TokenKind::While)) return parseWhile(t);
        if (match(TokenKind::For)) return parseFor(t);
        if (match(TokenKind::Each)) return parseEach(t);
        if (check(TokenKind::Identifier)) return parseAssign();
        throw CompileError(t.loc, "unexpected statement");
    }

    template <class T>
    StmtPtr parseNamedLine(Token start, Stmt::Kind k) {
        std::string q = parseQualifiedName();
        consumeLine();
        return std::make_unique<T>(start.loc, k, q);
    }

    std::string parseQualifiedName() {
        Token id = consume(TokenKind::Identifier, "expected name");
        std::string s = id.text;
        while (match(TokenKind::Dot)) {
            Token part = consume(TokenKind::Identifier, "expected name after '.'");
            s += "." + part.text;
        }
        return s;
    }

    StmtPtr parseMemory(Token start) {
        Token name = consume(TokenKind::Identifier, "expected memory name");
        consume(TokenKind::Dedicated, "expected 'dedicated'");
        consumeLine();
        return std::make_unique<MemoryDecl>(start.loc, name.text);
    }

    StmtPtr parseSlot(Token start) {
        Token name = consume(TokenKind::Identifier, "expected slot name");
        auto s = std::make_unique<SlotDecl>(start.loc, name.text);
        if (match(TokenKind::From)) {
            Token mem = consume(TokenKind::Identifier, "expected memory name after 'from'");
            s->memory = mem.text;
        }
        if (match(TokenKind::Assign)) {
            s->hasValue = true;
            s->value = parseExpression();
        }
        consumeLine();
        return s;
    }

    std::string parsePermissionKind() {
        Token t = peek();
        switch (t.kind) {
            case TokenKind::Read: case TokenKind::Change: case TokenKind::Move: case TokenKind::Share:
            case TokenKind::Expose: case TokenKind::Enter: case TokenKind::Leave:
                ++pos; return t.text;
            default: throw CompileError(t.loc, "expected permission kind");
        }
    }

    StmtPtr parsePermission(Token start, bool grant) {
        std::string perm = parsePermissionKind();
        Token target = consume(TokenKind::Identifier, "expected permission target");
        consumeLine();
        return std::make_unique<PermissionStmt>(start.loc, grant, perm, target.text);
    }

    StmtPtr parseDelegate(Token start) {
        Token val = consume(TokenKind::Identifier, "expected delegated value");
        auto d = std::make_unique<DelegateStmt>(start.loc, val.text, "");
        if (match(TokenKind::With)) {
            d->hasPerm = true;
            d->perm = parsePermissionKind();
        }
        consume(TokenKind::To, "expected 'to' in delegation");
        Token target = consume(TokenKind::Identifier, "expected delegation target");
        d->target = target.text;
        consumeLine();
        return d;
    }

    StmtPtr parseReturn(Token start) {
        auto r = std::make_unique<ReturnStmt>(start.loc);
        if (!check(TokenKind::Newline) && !check(TokenKind::End)) {
            r->hasValue = true;
            r->value = parseExpression();
        }
        consumeLine();
        return r;
    }

    StmtPtr parseErrorDecl() { Token t = consume(TokenKind::Error, "expected error"); return parseErrorDeclAfter(t); }

    StmtPtr parseErrorDeclAfter(Token start) {
        Token name = consume(TokenKind::Identifier, "expected error name");
        consumeLine();
        auto e = std::make_unique<ErrorDecl>(start.loc, name.text);
        skipNewlines();
        while (!check(TokenKind::EndKw) && !isAtEnd()) {
            consume(TokenKind::Slot, "expected slot field in error");
            Token f = consume(TokenKind::Identifier, "expected error field name");
            e->fields.push_back(f.text);
            consumeLine();
            skipNewlines();
        }
        consume(TokenKind::EndKw, "expected 'end' after error");
        if (check(TokenKind::Newline)) consumeLine();
        return e;
    }

    StmtPtr parseHandle(Token start) {
        Token name = consume(TokenKind::Identifier, "expected error name after handle");
        consumeLine();
        auto h = std::make_unique<HandleStmt>(start.loc, name.text);
        h->body = parseBlockUntil({TokenKind::EndKw});
        consume(TokenKind::EndKw, "expected 'end' after handle");
        if (check(TokenKind::Newline)) consumeLine();
        return h;
    }

    StmtPtr parseAttempt(Token start) {
        Token name = consume(TokenKind::Identifier, "expected attempt target");
        consumeLine();
        return std::make_unique<AttemptStmt>(start.loc, name.text);
    }

    StmtPtr parseRoute(Token start) {
        Token a = consume(TokenKind::Identifier, "expected route source");
        consume(TokenKind::To, "expected 'to' in route");
        Token b = consume(TokenKind::Identifier, "expected route destination");
        consumeLine();
        return std::make_unique<RouteStmt>(start.loc, a.text, b.text);
    }

    StmtPtr parseBlockStmt(Token start, Stmt::Kind k) {
        consumeLine();
        auto bs = std::make_unique<BlockStmt>(start.loc, k);
        bs->body = parseBlockUntil({TokenKind::EndKw});
        consume(TokenKind::EndKw, "expected 'end'");
        if (check(TokenKind::Newline)) consumeLine();
        return bs;
    }

    StmtPtr parseConcurrent(Token start) {
        consumeLine();
        auto c = std::make_unique<BlockStmt>(start.loc, Stmt::Kind::Concurrent);
        skipNewlines();
        while (!check(TokenKind::EndKw) && !isAtEnd()) {
            Token p = consume(TokenKind::Path, "expected path inside concurrent");
            Token name = consume(TokenKind::Identifier, "expected path name");
            consumeLine();
            auto ps = std::make_unique<PathStmt>(p.loc, name.text);
            ps->body = parseBlockUntil({TokenKind::EndKw});
            consume(TokenKind::EndKw, "expected end after path");
            if (check(TokenKind::Newline)) consumeLine();
            c->body.statements.push_back(std::move(ps));
            skipNewlines();
        }
        consume(TokenKind::EndKw, "expected end after concurrent");
        if (check(TokenKind::Newline)) consumeLine();
        return c;
    }

    StmtPtr parseIf(Token start) {
        auto s = std::make_unique<IfStmt>(start.loc);
        s->cond = parseExpression();
        consumeLine();
        s->thenBlock = parseBlockUntil({TokenKind::Else, TokenKind::EndKw});
        if (match(TokenKind::Else)) {
            s->hasElse = true;
            consumeLine();
            s->elseBlock = parseBlockUntil({TokenKind::EndKw});
        }
        consume(TokenKind::EndKw, "expected 'end' after if");
        if (check(TokenKind::Newline)) consumeLine();
        return s;
    }

    StmtPtr parseWhen(Token start) {
        auto s = std::make_unique<WhenStmt>(start.loc);
        s->cond = parseExpression();
        consumeLine();
        s->body = parseBlockUntil({TokenKind::EndKw});
        consume(TokenKind::EndKw, "expected 'end' after when");
        if (check(TokenKind::Newline)) consumeLine();
        return s;
    }

    StmtPtr parseMatch(Token start) {
        auto m = std::make_unique<MatchStmt>(start.loc);
        m->value = parseExpression();
        consumeLine();
        skipNewlines();
        while (match(TokenKind::Case)) {
            MatchCase c; c.loc = previous().loc;
            c.value = parseExpression();
            consumeLine();
            c.body = parseBlockUntil({TokenKind::Case, TokenKind::Else, TokenKind::EndKw});
            m->cases.push_back(std::move(c));
            skipNewlines();
        }
        if (match(TokenKind::Else)) {
            m->hasElse = true;
            consumeLine();
            m->elseBlock = parseBlockUntil({TokenKind::EndKw});
        }
        consume(TokenKind::EndKw, "expected 'end' after match");
        if (check(TokenKind::Newline)) consumeLine();
        return m;
    }

    StmtPtr parseRepeat(Token start) {
        auto r = std::make_unique<RepeatStmt>(start.loc);
        r->count = parseExpression();
        consumeLine();
        r->body = parseBlockUntil({TokenKind::EndKw});
        consume(TokenKind::EndKw, "expected end after repeat");
        if (check(TokenKind::Newline)) consumeLine();
        return r;
    }

    StmtPtr parseWhile(Token start) {
        auto w = std::make_unique<WhileStmt>(start.loc);
        w->cond = parseExpression();
        consumeLine();
        w->body = parseBlockUntil({TokenKind::EndKw});
        consume(TokenKind::EndKw, "expected end after while");
        if (check(TokenKind::Newline)) consumeLine();
        return w;
    }

    StmtPtr parseFor(Token start) {
        auto f = std::make_unique<ForStmt>(start.loc);
        Token var = consume(TokenKind::Identifier, "expected for variable");
        f->var = var.text;
        consume(TokenKind::From, "expected from in for");
        f->from = parseExpression();
        consume(TokenKind::To, "expected to in for");
        f->to = parseExpression();
        consumeLine();
        f->body = parseBlockUntil({TokenKind::EndKw});
        consume(TokenKind::EndKw, "expected end after for");
        if (check(TokenKind::Newline)) consumeLine();
        return f;
    }

    StmtPtr parseEach(Token start) {
        Token var = consume(TokenKind::Identifier, "expected each variable");
        consume(TokenKind::From, "expected from in each");
        Token col = consume(TokenKind::Identifier, "expected collection name");
        consumeLine();
        auto e = std::make_unique<EachStmt>(start.loc, var.text, col.text);
        e->body = parseBlockUntil({TokenKind::EndKw});
        consume(TokenKind::EndKw, "expected end after each");
        if (check(TokenKind::Newline)) consumeLine();
        return e;
    }

    StmtPtr parseAssign() {
        Token name = consume(TokenKind::Identifier, "expected assignment target");
        auto a = std::make_unique<AssignStmt>(name.loc, name.text);
        if (match(TokenKind::LBracket)) {
            a->indexed = true;
            a->index = parseExpression();
            consume(TokenKind::RBracket, "expected ]");
        }
        consume(TokenKind::Assign, "expected assign");
        a->value = parseExpression();
        consumeLine();
        return a;
    }

    // Expressions: precedence descent
    ExprPtr parseExpression() { return parseOr(); }
    ExprPtr parseOr() {
        auto e = parseAnd();
        while (match(TokenKind::OrOr)) e = std::make_unique<BinaryExpr>(previous().loc, "||", std::move(e), parseAnd());
        return e;
    }
    ExprPtr parseAnd() {
        auto e = parseEquality();
        while (match(TokenKind::AndAnd)) e = std::make_unique<BinaryExpr>(previous().loc, "&&", std::move(e), parseEquality());
        return e;
    }
    ExprPtr parseEquality() {
        auto e = parseComparison();
        while (match(TokenKind::EqEq) || match(TokenKind::NotEq)) e = std::make_unique<BinaryExpr>(previous().loc, previous().text, std::move(e), parseComparison());
        return e;
    }
    ExprPtr parseComparison() {
        auto e = parseTerm();
        while (match(TokenKind::Less) || match(TokenKind::LessEq) || match(TokenKind::Greater) || match(TokenKind::GreaterEq)) e = std::make_unique<BinaryExpr>(previous().loc, previous().text, std::move(e), parseTerm());
        return e;
    }
    ExprPtr parseTerm() {
        auto e = parseFactor();
        while (match(TokenKind::Plus) || match(TokenKind::Minus)) e = std::make_unique<BinaryExpr>(previous().loc, previous().text, std::move(e), parseFactor());
        return e;
    }
    ExprPtr parseFactor() {
        auto e = parseUnary();
        while (match(TokenKind::Star) || match(TokenKind::Slash) || match(TokenKind::Percent)) e = std::make_unique<BinaryExpr>(previous().loc, previous().text, std::move(e), parseUnary());
        return e;
    }
    ExprPtr parseUnary() {
        if (match(TokenKind::Not) || match(TokenKind::Minus)) return std::make_unique<UnaryExpr>(previous().loc, previous().text, parseUnary());
        return parsePrimary();
    }
    ExprPtr parsePrimary() {
        Token t = peek();
        if (match(TokenKind::Integer) || match(TokenKind::Float) || match(TokenKind::String) || match(TokenKind::Boolean) || match(TokenKind::NullLit)) {
            return std::make_unique<LiteralExpr>(t.loc, t.text, t.kind);
        }
        if (match(TokenKind::Identifier)) {
            std::string name = t.text;
            if (match(TokenKind::LParen)) {
                auto c = std::make_unique<CallExpr>(t.loc, name);
                if (!check(TokenKind::RParen)) {
                    do { c->args.push_back(parseExpression()); } while (match(TokenKind::Comma));
                }
                consume(TokenKind::RParen, "expected )");
                return c;
            }
            if (match(TokenKind::LBracket)) {
                auto idx = parseExpression();
                consume(TokenKind::RBracket, "expected ]");
                return std::make_unique<IndexExpr>(t.loc, name, std::move(idx));
            }
            return std::make_unique<IdentifierExpr>(t.loc, name);
        }
        if (match(TokenKind::LParen)) {
            auto e = parseExpression();
            consume(TokenKind::RParen, "expected )");
            return e;
        }
        if (match(TokenKind::LBracket)) {
            auto l = std::make_unique<ListExpr>(t.loc);
            if (!check(TokenKind::RBracket)) {
                do { l->items.push_back(parseExpression()); } while (match(TokenKind::Comma));
            }
            consume(TokenKind::RBracket, "expected ]");
            return l;
        }
        throw CompileError(t.loc, "expected expression");
    }
};

// ================================================================
// Semantic analysis
// ================================================================

struct SymbolInfo {
    std::string memory;
    bool declared = false;
};

class SemanticAnalyzer {
    std::map<std::string, SymbolInfo> symbols;
    std::map<std::string, std::set<std::string>> grants;
    std::map<std::string, std::set<std::string>> denies;
    std::set<std::string> memories;
    std::set<std::string> errors;
public:
    void analyze(const Program& p) {
        for (auto& t : p.top) scanTop(*t);
        for (auto& e : p.entries) scanBlock(e.body);
        for (auto& e : p.entries) validateBlock(e.body, false);
    }

private:
    void scanTop(const Stmt& s) {
        if (s.kind == Stmt::Kind::ErrorDecl) errors.insert(static_cast<const ErrorDecl&>(s).name);
    }
    void scanBlock(const Block& b) {
        for (auto& sp : b.statements) scanStmt(*sp);
    }
    void scanStmt(const Stmt& s) {
        switch (s.kind) {
            case Stmt::Kind::MemoryDecl: memories.insert(static_cast<const MemoryDecl&>(s).name); break;
            case Stmt::Kind::SlotDecl: {
                auto& x = static_cast<const SlotDecl&>(s);
                symbols[x.name] = SymbolInfo{x.memory.value_or(""), true};
                break;
            }
            case Stmt::Kind::Permission: {
                auto& p = static_cast<const PermissionStmt&>(s);
                if (p.grant) grants[p.target].insert(p.perm); else denies[p.target].insert(p.perm);
                break;
            }
            case Stmt::Kind::If: { auto& x=static_cast<const IfStmt&>(s); scanBlock(x.thenBlock); scanBlock(x.elseBlock); break; }
            case Stmt::Kind::When: scanBlock(static_cast<const WhenStmt&>(s).body); break;
            case Stmt::Kind::Match: { auto& m=static_cast<const MatchStmt&>(s); for(auto& c:m.cases)scanBlock(c.body); scanBlock(m.elseBlock); break; }
            case Stmt::Kind::Repeat: scanBlock(static_cast<const RepeatStmt&>(s).body); break;
            case Stmt::Kind::While: scanBlock(static_cast<const WhileStmt&>(s).body); break;
            case Stmt::Kind::For: scanBlock(static_cast<const ForStmt&>(s).body); break;
            case Stmt::Kind::Each: scanBlock(static_cast<const EachStmt&>(s).body); break;
            case Stmt::Kind::Handle: scanBlock(static_cast<const HandleStmt&>(s).body); break;
            case Stmt::Kind::Parallel:
            case Stmt::Kind::Concurrent: scanBlock(static_cast<const BlockStmt&>(s).body); break;
            case Stmt::Kind::Path: scanBlock(static_cast<const PathStmt&>(s).body); break;
            default: break;
        }
    }

    bool hasPerm(const std::string& target, const std::string& perm) const {
        auto d = denies.find(target);
        if (d != denies.end() && d->second.count(perm)) return false;
        auto g = grants.find(target);
        return g != grants.end() && g->second.count(perm);
    }

    void require(const SourceLoc& loc, const std::string& target, const std::string& perm) const {
        // Local temporaries declared but not explicitly permitted are allowed to be read immediately.
        // Mutations still require change permission for user-visible named state.
        if (!hasPerm(target, perm)) {
            throw CompileError(loc, "permission denied: '" + perm + "' required for '" + target + "'");
        }
    }

    void validateBlock(const Block& b, bool concurrentContext) {
        for (auto& sp : b.statements) validateStmt(*sp, concurrentContext);
    }
    void validateExpr(const Expr& e) {
        switch (e.kind) {
            case Expr::Kind::Identifier: {
                auto& id = static_cast<const IdentifierExpr&>(e);
                // soft-read validation: only enforce if permissions exist for symbol
                if (grants.count(id.name) || denies.count(id.name)) require(e.loc, id.name, "read");
                break;
            }
            case Expr::Kind::Index: {
                auto& idx = static_cast<const IndexExpr&>(e);
                if (grants.count(idx.base) || denies.count(idx.base)) require(e.loc, idx.base, "read");
                validateExpr(*idx.index);
                break;
            }
            case Expr::Kind::Binary: { auto& b=static_cast<const BinaryExpr&>(e); validateExpr(*b.left); validateExpr(*b.right); break; }
            case Expr::Kind::Unary: validateExpr(*static_cast<const UnaryExpr&>(e).value); break;
            case Expr::Kind::Call: { auto& c=static_cast<const CallExpr&>(e); for(auto& a:c.args) validateExpr(*a); break; }
            case Expr::Kind::List: { auto& l=static_cast<const ListExpr&>(e); for(auto& a:l.items) validateExpr(*a); break; }
            default: break;
        }
    }
    void validateStmt(const Stmt& s, bool concurrentContext) {
        switch (s.kind) {
            case Stmt::Kind::SlotDecl: {
                auto& x=static_cast<const SlotDecl&>(s); if (x.hasValue) validateExpr(*x.value); break;
            }
            case Stmt::Kind::Assign: {
                auto& a=static_cast<const AssignStmt&>(s);
                require(a.loc, a.name, "change");
                if (a.indexed) validateExpr(*a.index);
                validateExpr(*a.value);
                break;
            }
            case Stmt::Kind::Delegate: {
                auto& d=static_cast<const DelegateStmt&>(s);
                if (d.hasPerm) require(d.loc, d.value, d.perm);
                else if (grants.count(d.value) || denies.count(d.value)) require(d.loc, d.value, "read");
                break;
            }
            case Stmt::Kind::Return: { auto& r=static_cast<const ReturnStmt&>(s); if(r.hasValue) validateExpr(*r.value); break; }
            case Stmt::Kind::If: { auto& x=static_cast<const IfStmt&>(s); validateExpr(*x.cond); validateBlock(x.thenBlock, concurrentContext); validateBlock(x.elseBlock, concurrentContext); break; }
            case Stmt::Kind::When: { auto& x=static_cast<const WhenStmt&>(s); validateExpr(*x.cond); validateBlock(x.body, concurrentContext); break; }
            case Stmt::Kind::Match: { auto& m=static_cast<const MatchStmt&>(s); validateExpr(*m.value); for(auto& c:m.cases){validateExpr(*c.value); validateBlock(c.body, concurrentContext);} validateBlock(m.elseBlock, concurrentContext); break; }
            case Stmt::Kind::Repeat: { auto& r=static_cast<const RepeatStmt&>(s); validateExpr(*r.count); validateBlock(r.body, concurrentContext); break; }
            case Stmt::Kind::While: { auto& w=static_cast<const WhileStmt&>(s); validateExpr(*w.cond); validateBlock(w.body, concurrentContext); break; }
            case Stmt::Kind::For: { auto& f=static_cast<const ForStmt&>(s); validateExpr(*f.from); validateExpr(*f.to); validateBlock(f.body, concurrentContext); break; }
            case Stmt::Kind::Each: { auto& e=static_cast<const EachStmt&>(s); if(grants.count(e.collection)||denies.count(e.collection)) require(e.loc,e.collection,"read"); validateBlock(e.body, concurrentContext); break; }
            case Stmt::Kind::Handle: validateBlock(static_cast<const HandleStmt&>(s).body, concurrentContext); break;
            case Stmt::Kind::Parallel: validateBlock(static_cast<const BlockStmt&>(s).body, concurrentContext); break;
            case Stmt::Kind::Concurrent: validateBlock(static_cast<const BlockStmt&>(s).body, true); break;
            case Stmt::Kind::Path: validateBlock(static_cast<const PathStmt&>(s).body, true); break;
            default: break;
        }
    }
};

// ================================================================
// C++ backend
// ================================================================

class CppEmitter {
    std::ostringstream out;
    int indent = 0;
    std::set<std::string> externals;
    std::set<std::string> nativeModes;

public:
    std::string emit(const Program& p) {
        out << "// Generated by foresettec.cpp from Foresette .4se source\n";
        out << "#include <iostream>\n#include <string>\n#include <vector>\n#include <mutex>\n#include <condition_variable>\n#include <thread>\n#include <atomic>\n#include <unordered_map>\n\n";
        out << "using FVal = std::string;\n";
        out << "static std::unordered_map<std::string, std::mutex> __fs4_mutexes;\n";
        out << "static std::unordered_map<std::string, bool> __fs4_signals;\n";
        out << "static std::mutex __fs4_signal_mutex;\nstatic std::condition_variable __fs4_signal_cv;\n";
        out << "static int puts(const char* s){ std::cout << s << std::endl; return 0; }\n";
        out << "static int puts(const std::string& s){ std::cout << s << std::endl; return 0; }\n";
        out << "template<class T> static int puts(const T& v){ std::cout << v << std::endl; return 0; }\n";
        out << "static void __fs4_signal(const std::string& n){ std::lock_guard<std::mutex> lk(__fs4_signal_mutex); __fs4_signals[n]=true; __fs4_signal_cv.notify_all(); }\n";
        out << "static void __fs4_wait(const std::string& n){ std::unique_lock<std::mutex> lk(__fs4_signal_mutex); __fs4_signal_cv.wait(lk,[&]{return __fs4_signals[n];}); }\n\n";

        // Prototypes
        for (const auto& e : p.entries) out << "int " << safe(e.name) << "();\n";
        out << "\n";

        for (auto& e : p.entries) emitEntry(e);
        return out.str();
    }

private:
    std::string safe(std::string s) {
        for (char& c : s) if (!std::isalnum(static_cast<unsigned char>(c)) && c != '_') c = '_';
        return s;
    }
    void line(const std::string& s="") { for(int i=0;i<indent;i++) out << "    "; out << s << "\n"; }

    std::string emitExpr(const Expr& e) {
        switch (e.kind) {
            case Expr::Kind::Literal: {
                auto& l = static_cast<const LiteralExpr&>(e);
                if (l.litKind == TokenKind::String) return quote(l.value);
                if (l.litKind == TokenKind::Boolean) return l.value == "true" ? "true" : "false";
                if (l.litKind == TokenKind::NullLit) return "0";
                return l.value;
            }
            case Expr::Kind::Identifier: return safe(static_cast<const IdentifierExpr&>(e).name);
            case Expr::Kind::Binary: {
                auto& b=static_cast<const BinaryExpr&>(e);
                std::string op = b.op;
                if (op == "and") op = "&&";
                if (op == "or") op = "||";
                return "(" + emitExpr(*b.left) + " " + op + " " + emitExpr(*b.right) + ")";
            }
            case Expr::Kind::Unary: { auto& u=static_cast<const UnaryExpr&>(e); return "(" + u.op + emitExpr(*u.value) + ")"; }
            case Expr::Kind::Call: {
                auto& c=static_cast<const CallExpr&>(e); std::string s=safe(c.name)+"("; for(size_t i=0;i<c.args.size();++i){ if(i) s+=", "; s+=emitExpr(*c.args[i]); } s+=")"; return s;
            }
            case Expr::Kind::Index: { auto& x=static_cast<const IndexExpr&>(e); return safe(x.base) + "[" + emitExpr(*x.index) + "]"; }
            case Expr::Kind::List: {
                auto& l=static_cast<const ListExpr&>(e); std::string s="std::vector{ "; for(size_t i=0;i<l.items.size();++i){ if(i)s+=", "; s+=emitExpr(*l.items[i]); } s+=" }"; return s;
            }
        }
        return "0";
    }

    std::string quote(const std::string& s) {
        std::string r="\"";
        for(char c:s){ if(c=='\n')r+="\\n"; else if(c=='\t')r+="\\t"; else if(c=='\"')r+="\\\""; else if(c=='\\')r+="\\\\"; else r+=c; }
        r += "\""; return r;
    }

    void emitEntry(const EntryDecl& e) {
        out << "int " << safe(e.name) << "(){\n";
        indent++;
        emitBlock(e.body);
        line("return 0;");
        indent--;
        out << "}\n\n";
    }

    void emitBlock(const Block& b) { for(auto& s:b.statements) emitStmt(*s); }

    void emitStmt(const Stmt& s) {
        switch(s.kind) {
            case Stmt::Kind::MemoryDecl: line("// memory " + safe(static_cast<const MemoryDecl&>(s).name) + " dedicated"); break;
            case Stmt::Kind::SlotDecl: {
                auto& x=static_cast<const SlotDecl&>(s);
                if (x.hasValue) line("auto " + safe(x.name) + " = " + emitExpr(*x.value) + ";");
                else line("int " + safe(x.name) + "{};");
                break;
            }
            case Stmt::Kind::Assign: {
                auto& a=static_cast<const AssignStmt&>(s);
                if (a.indexed) line(safe(a.name)+"["+emitExpr(*a.index)+"] = "+emitExpr(*a.value)+";");
                else line(safe(a.name)+" = "+emitExpr(*a.value)+";");
                break;
            }
            case Stmt::Kind::Permission: {
                auto& p=static_cast<const PermissionStmt&>(s);
                line(std::string("// ") + (p.grant?"permit ":"deny ") + p.perm + " " + p.target);
                break;
            }
            case Stmt::Kind::Delegate: {
                auto& d=static_cast<const DelegateStmt&>(s);
                line(safe(d.target) + "(" + safe(d.value) + ");");
                break;
            }
            case Stmt::Kind::Return: {
                auto& r=static_cast<const ReturnStmt&>(s);
                if(r.hasValue) line("return " + emitExpr(*r.value) + ";"); else line("return 0;");
                break;
            }
            case Stmt::Kind::Stop: line("return 1;"); break;
            case Stmt::Kind::Bypass: line("/* bypass */;"); break;
            case Stmt::Kind::Break: line("break;"); break;
            case Stmt::Kind::Continue: line("continue;"); break;
            case Stmt::Kind::If: {
                auto& x=static_cast<const IfStmt&>(s); line("if ("+emitExpr(*x.cond)+") {"); indent++; emitBlock(x.thenBlock); indent--; if(x.hasElse){ line("} else {"); indent++; emitBlock(x.elseBlock); indent--; } line("}"); break;
            }
            case Stmt::Kind::When: { auto& w=static_cast<const WhenStmt&>(s); line("if ("+emitExpr(*w.cond)+") {"); indent++; emitBlock(w.body); indent--; line("}"); break; }
            case Stmt::Kind::Match: {
                auto& m=static_cast<const MatchStmt&>(s);
                std::string tmp="__fs4_match_"+std::to_string(reinterpret_cast<uintptr_t>(&s));
                line("auto "+tmp+" = "+emitExpr(*m.value)+";");
                bool first=true;
                for(auto& c:m.cases){ line(std::string(first?"if":"else if")+" ("+tmp+" == "+emitExpr(*c.value)+") {"); indent++; emitBlock(c.body); indent--; line("}"); first=false; }
                if(m.hasElse){ line("else {"); indent++; emitBlock(m.elseBlock); indent--; line("}"); }
                break;
            }
            case Stmt::Kind::Repeat: { auto& r=static_cast<const RepeatStmt&>(s); line("for(int __fs4_i=0; __fs4_i < "+emitExpr(*r.count)+"; ++__fs4_i){"); indent++; emitBlock(r.body); indent--; line("}"); break; }
            case Stmt::Kind::While: { auto& w=static_cast<const WhileStmt&>(s); line("while ("+emitExpr(*w.cond)+") {"); indent++; emitBlock(w.body); indent--; line("}"); break; }
            case Stmt::Kind::For: { auto& f=static_cast<const ForStmt&>(s); line("for(auto "+safe(f.var)+" = "+emitExpr(*f.from)+"; "+safe(f.var)+" < "+emitExpr(*f.to)+"; ++"+safe(f.var)+"){"); indent++; emitBlock(f.body); indent--; line("}"); break; }
            case Stmt::Kind::Each: { auto& e=static_cast<const EachStmt&>(s); line("for(auto& "+safe(e.var)+" : "+safe(e.collection)+"){"); indent++; emitBlock(e.body); indent--; line("}"); break; }
            case Stmt::Kind::ErrorDecl: line("// error " + safe(static_cast<const ErrorDecl&>(s).name)); break;
            case Stmt::Kind::Handle: { auto& h=static_cast<const HandleStmt&>(s); line("// handle " + safe(h.name)); line("{"); indent++; emitBlock(h.body); indent--; line("}"); break; }
            case Stmt::Kind::Attempt: line("// attempt " + safe(static_cast<const AttemptStmt&>(s).name)); break;
            case Stmt::Kind::Route: { auto& r=static_cast<const RouteStmt&>(s); line("// route " + safe(r.from) + " to " + safe(r.to)); break; }
            case Stmt::Kind::Parallel: { auto& b=static_cast<const BlockStmt&>(s); line("// parallel begin"); line("{"); indent++; emitBlock(b.body); indent--; line("}"); line("// parallel end"); break; }
            case Stmt::Kind::Concurrent: { auto& b=static_cast<const BlockStmt&>(s); line("// concurrent begin"); line("{"); indent++; for(auto& p:b.body.statements) emitStmt(*p); indent--; line("}"); line("// concurrent end"); break; }
            case Stmt::Kind::Path: { auto& p=static_cast<const PathStmt&>(s); line("// path " + safe(p.name)); line("{"); indent++; emitBlock(p.body); indent--; line("}"); break; }
            case Stmt::Kind::Sync: line("std::atomic_thread_fence(std::memory_order_seq_cst);"); break;
            case Stmt::Kind::Wait: line("__fs4_wait("+quote(static_cast<const NamedStmt&>(s).name)+");"); break;
            case Stmt::Kind::Signal: line("__fs4_signal("+quote(static_cast<const NamedStmt&>(s).name)+");"); break;
            case Stmt::Kind::Lock: line("__fs4_mutexes["+quote(static_cast<const NamedStmt&>(s).name)+"].lock();"); break;
            case Stmt::Kind::Unlock: line("__fs4_mutexes["+quote(static_cast<const NamedStmt&>(s).name)+"].unlock();"); break;
            case Stmt::Kind::Import: line("// import " + static_cast<const NamedStmt&>(s).name); break;
            case Stmt::Kind::Export: line("// export " + static_cast<const NamedStmt&>(s).name); break;
            case Stmt::Kind::External: line("// external " + static_cast<const NamedStmt&>(s).name); break;
            case Stmt::Kind::Native: line("// native " + static_cast<const NamedStmt&>(s).name); break;
        }
    }
};

// ================================================================
// Driver
// ================================================================

static std::string readFile(const std::string& path) {
    std::ifstream in(path, std::ios::binary);
    if (!in) throw std::runtime_error("cannot open input: " + path);
    std::ostringstream ss; ss << in.rdbuf(); return ss.str();
}
static void writeFile(const std::string& path, const std::string& data) {
    std::ofstream out(path, std::ios::binary);
    if (!out) throw std::runtime_error("cannot open output: " + path);
    out << data;
}

} // namespace fs4

int main(int argc, char** argv) {
    try {
        if (argc < 2) {
            std::cerr << "usage: foresettec <input.4se> [-o output.cpp]\n";
            return 2;
        }
        std::string input = argv[1];
        std::string output = "out.cpp";
        for (int i=2;i<argc;i++) {
            std::string a=argv[i];
            if (a=="-o" && i+1<argc) output=argv[++i];
        }
        std::string src = fs4::readFile(input);
        fs4::Lexer lx(src);
        auto toks = lx.lexAll();
        fs4::Parser parser(std::move(toks));
        fs4::Program prog = parser.parseProgram();
        fs4::SemanticAnalyzer sem;
        sem.analyze(prog);
        fs4::CppEmitter emitter;
        std::string cpp = emitter.emit(prog);
        fs4::writeFile(output, cpp);
        std::cout << "Foresette compiled to C++: " << output << "\n";
        return 0;
    } catch (const std::exception& e) {
        std::cerr << "foresettec error: " << e.what() << "\n";
        return 1;
    }
}
