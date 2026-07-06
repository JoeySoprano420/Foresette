# 🧩 **1. The exact C++ project directory layout**

```
foresette/
│
├── CMakeLists.txt
├── README.md
│
├── src/
│   ├── lexer/
│   │   ├── Token.hpp
│   │   ├── Token.cpp
│   │   ├── Lexer.hpp
│   │   └── Lexer.cpp
│   │
│   ├── parser/
│   │   ├── Parser.hpp
│   │   └── Parser.cpp
│   │
│   ├── ast/
│   │   ├── AST.hpp
│   │   ├── Nodes.hpp
│   │   └── ASTPrinter.cpp
│   │
│   ├── sem/
│   │   ├── SemanticGraph.hpp
│   │   ├── SemanticGraph.cpp
│   │   ├── Tables.hpp
│   │   ├── Tables.cpp
│   │   ├── Verifier.hpp
│   │   └── Verifier.cpp
│   │
│   ├── llvm/
│   │   ├── Lowering.hpp
│   │   ├── Lowering.cpp
│   │   ├── Metadata.hpp
│   │   └── Metadata.cpp
│   │
│   ├── runtime/
│   │   ├── Threads.hpp
│   │   ├── Threads.cpp
│   │   ├── Sync.hpp
│   │   └── Sync.cpp
│   │
│   ├── diag/
│   │   ├── Diagnostics.hpp
│   │   └── Diagnostics.cpp
│   │
│   ├── driver/
│   │   ├── ForesetteDriver.hpp
│   │   ├── ForesetteDriver.cpp
│   │   └── main.cpp
│
├── include/
│   └── foresette/ (public headers)
│
├── tests/
│   ├── lexer/
│   ├── parser/
│   ├── sem/
│   ├── llvm/
│   └── driver/
│
└── examples/
    ├── hello.4se
    ├── memory.4se
    ├── parallel.4se
    └── engine.4se
```

This is the **canonical layout** for a modern native compiler.

---

# 🧩 **2. The first 10 source files to write**

These are the *exact* first 10 files that get the compiler off the ground.

### **1. Token.hpp**
Defines:
- token kinds  
- literals  
- operators  
- punctuation  
- keyword enum  

### **2. Token.cpp**
Implements:
- keyword lookup  
- token → string conversion  
- debugging helpers  

### **3. Lexer.hpp**
Defines:
- lexer class  
- streaming interface  
- peek/advance  
- error hooks  

### **4. Lexer.cpp**
Implements:
- identifier scanning  
- number scanning  
- string scanning  
- operator scanning  
- newline handling  
- keyword recognition  

### **5. AST.hpp**
Defines:
- base `Node` class  
- visitor interface  
- node categories  

### **6. Nodes.hpp**
Defines:
- `ProgramNode`  
- `EntryNode`  
- `SlotDeclNode`  
- `MemoryDeclNode`  
- `PermissionNode`  
- `DelegationNode`  
- `ErrorDeclNode`  
- `ParallelNode`  
- `ConcurrentNode`  
- `PathNode`  
- `IfNode`, `MatchNode`, `RepeatNode`, `WhileNode`, `ForNode`, `EachNode`  
- `ReturnNode`, `StopNode`, `BypassNode`, `BreakNode`, `ContinueNode`  
- `BinaryExprNode`, `UnaryExprNode`, `LiteralNode`, `IdentifierNode`, `CallNode`, `ListNode`

### **7. Parser.hpp**
Defines:
- parser class  
- entry points (`parseProgram()`)  
- error interface  

### **8. Parser.cpp**
Implements:
- grammar rules  
- AST construction  
- precedence parsing  
- error recovery  

### **9. SemanticGraph.hpp**
Defines:
- symbol table  
- memory table  
- permission table  
- delegation table  
- execution table  
- semantic graph nodes  

### **10. SemanticGraph.cpp**
Implements:
- table construction  
- slot/memory mapping  
- permission graph building  
- delegation graph building  
- execution topology building  

Once these 10 files exist, you can **parse full Foresette programs** and build the **Strategic Semantic Graph**.

---

# 🧩 **3. Compiler bootstrap plan (the real one)**

### **Phase 1 — Front-end (Week 1–2)**
- Implement lexer  
- Implement parser  
- Implement AST  
- Add AST printer  
- Add basic diagnostics  

**Milestone:** Parse `.4se` files into AST.

---

### **Phase 2 — Semantic engine (Week 3–4)**
- Build symbol/memory/permission/delegation/execution tables  
- Build semantic graph  
- Implement semantic checks  

**Milestone:** Reject invalid programs with meaningful diagnostics.

---

### **Phase 3 — Verifier (Week 5–6)**
Implement all verification rules:

- permission  
- delegation  
- memory  
- parallel  
- concurrent  
- error/handler  

**Milestone:** Semantic graph is fully validated.

---

### **Phase 4 — LLVM lowering (Week 7–10)**
- Integrate LLVM  
- Lower entries → functions  
- Lower slots → SSA or alloca  
- Lower assignments → load/add/store  
- Lower dedicated memory → metadata  
- Lower delegation → call metadata  
- Lower errors → branches  
- Lower parallel/concurrent → outlined functions  
- Emit object files  

**Milestone:** `.4se` → native executable.

---

### **Phase 5 — Driver & runtime (Week 11–12)**
- Implement `4sec` CLI  
- Implement thread pool  
- Implement sync/wait/signal/lock/unlock runtime  
- Add emit modes (llvm, asm, obj)  

**Milestone:** Full compiler usable by developers.

---

### **Phase 6 — Tests & stabilization (Week 13–16)**
- Unit tests  
- Integration tests  
- Stress tests  
- Parallel/concurrent tests  
- Memory/permission/delegation tests  

**Milestone:** Industrial stability.

---

# 🧩 **4. Official C++ coding style guide for the Foresette compiler**

### **Core principles**
- **Zero-overhead abstractions**  
- **No exceptions** (use `Expected<T>` or error structs)  
- **No RTTI**  
- **No dynamic polymorphism unless necessary**  
- **Prefer value types**  
- **Prefer `std::vector` over raw arrays**  
- **Prefer `std::unique_ptr` over raw pointers**  
- **Use `enum class` for token kinds, node kinds, permission kinds**  
- **Use `final` for AST node classes**  
- **Use `const` aggressively**  
- **Use `inline` for small helpers**  
- **Use `[[nodiscard]]` for functions returning error-sensitive values**  

### **Naming**
- Types: `PascalCase`  
- Functions: `camelCase`  
- Members: `camelCase`  
- Constants: `SCREAMING_SNAKE_CASE`  
- Namespaces: `foresette::lexer`, `foresette::parser`, etc.

### **Memory**
- No raw `new` or `delete`.  
- Use `std::unique_ptr` for AST nodes.  
- Use `std::vector` for lists.  
- Use `std::string_view` for token text.

### **Error handling**
- No exceptions.  
- Use:

```cpp
struct Error {
    ErrorCode code;
    std::string message;
    SourceLocation loc;
};
```

### **Inline ASM**
Allowed only in:
- runtime sync primitives  
- thread pool fast paths  
- metadata emission  
- target-specific lowering  

---

# 🧩 Final synthesis  
You now have:

- **The exact C++ directory tree**  
- **The first 10 files to write**  
- **The full compiler bootstrap plan**  
- **The official C++ coding style guide**  

This is the **real beginning** of the Foresette compiler — the industrial version, not the toy version.

