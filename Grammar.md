Foresette ".4se" Grammar, AST, and LLVM Lowering Map

1. Token Classes

TOKEN_PROGRAM       program
TOKEN_ENTRY         entry
TOKEN_END           end
TOKEN_SLOT          slot
TOKEN_MEMORY        memory
TOKEN_DEDICATED     dedicated
TOKEN_ASSIGN        assign
TOKEN_PERMIT        permit
TOKEN_DENY          deny
TOKEN_READ          read
TOKEN_CHANGE        change
TOKEN_MOVE          move
TOKEN_SHARE         share
TOKEN_EXPOSE        expose
TOKEN_ENTER         enter
TOKEN_LEAVE         leave
TOKEN_DELEGATE      delegate
TOKEN_FROM          from
TOKEN_TO            to
TOKEN_WITH          with
TOKEN_RETURN        return
TOKEN_STOP          stop
TOKEN_BYPASS        bypass
TOKEN_ERROR         error
TOKEN_HANDLE        handle
TOKEN_ATTEMPT       attempt
TOKEN_ROUTE         route
TOKEN_PATH          path
TOKEN_PARALLEL      parallel
TOKEN_CONCURRENT    concurrent
TOKEN_SYNC          sync
TOKEN_WAIT          wait
TOKEN_SIGNAL        signal
TOKEN_LOCK          lock
TOKEN_UNLOCK        unlock
TOKEN_IF            if
TOKEN_ELSE          else
TOKEN_WHEN          when
TOKEN_CASE          case
TOKEN_MATCH         match
TOKEN_REPEAT        repeat
TOKEN_WHILE         while
TOKEN_FOR           for
TOKEN_EACH          each
TOKEN_BREAK         break
TOKEN_CONTINUE      continue
TOKEN_IMPORT        import
TOKEN_EXPORT        export
TOKEN_EXTERNAL      external
TOKEN_NATIVE        native

2. Literal Tokens

IDENTIFIER          [A-Za-z_][A-Za-z0-9_]*
INTEGER             [0-9]+
FLOAT               [0-9]+ "." [0-9]+
STRING              "..."
BOOLEAN             true | false
NULL                null

3. Operator Tokens

PLUS                +
MINUS               -
STAR                *
SLASH               /
PERCENT             %

EQUAL_EQUAL         ==
NOT_EQUAL           !=
LESS                <
LESS_EQUAL          <=
GREATER             >
GREATER_EQUAL       >=

AND                 &&
OR                  ||
NOT                 !

ARROW_LEFT          <-
ARROW_RIGHT         ->
SHARE_LINK          <>
EXCLUSIVE_LINK      <<
INPUT_LINK          <=

LPAREN              (
RPAREN              )
LBRACKET            [
RBRACKET            ]
COMMA               ,
DOT                 .
COLON               :
NEWLINE
EOF

---

4. AST Node Types

ProgramNode
ImportNode
ExportNode
ExternalNode
NativeNode

EntryNode
BlockNode

SlotDeclNode
MemoryDeclNode
AssignmentNode

PermissionNode
DelegationNode

ErrorDeclNode
AttemptNode
HandleNode

RouteNode
PathNode
ParallelNode
ConcurrentNode

SyncNode
WaitNode
SignalNode
LockNode
UnlockNode

IfNode
WhenNode
MatchNode
CaseNode

RepeatNode
WhileNode
ForNode
EachNode

ReturnNode
StopNode
BypassNode
BreakNode
ContinueNode

BinaryExprNode
UnaryExprNode
LiteralNode
IdentifierNode
CallNode
AccessNode
ListNode

---

5. Core Grammar

program_file
    ::= import_decl*
        external_decl*
        native_decl*
        program_decl
        top_level_decl*
        EOF
    ;

program_decl
    ::= "program" IDENTIFIER NEWLINE
    ;

top_level_decl
    ::= entry_decl
     |  error_decl
     |  export_decl
    ;

entry_decl
    ::= "entry" IDENTIFIER NEWLINE block "end" NEWLINE?
    ;

block
    ::= statement*
    ;

statement
    ::= slot_decl
     |  memory_decl
     |  assignment
     |  permission_stmt
     |  delegation_stmt
     |  attempt_stmt
     |  handle_stmt
     |  route_stmt
     |  parallel_stmt
     |  concurrent_stmt
     |  sync_stmt
     |  wait_stmt
     |  signal_stmt
     |  lock_stmt
     |  unlock_stmt
     |  if_stmt
     |  when_stmt
     |  match_stmt
     |  repeat_stmt
     |  while_stmt
     |  for_stmt
     |  each_stmt
     |  return_stmt
     |  stop_stmt
     |  bypass_stmt
     |  break_stmt
     |  continue_stmt
    ;

---

6. Slots and Assignment Grammar

slot_decl
    ::= "slot" IDENTIFIER slot_memory? slot_assign? NEWLINE
    ;

slot_memory
    ::= "from" IDENTIFIER
    ;

slot_assign
    ::= "assign" expression
    ;

assignment
    ::= IDENTIFIER "assign" expression NEWLINE
    ;

memory_decl
    ::= "memory" IDENTIFIER "dedicated" NEWLINE
    ;

Examples:

slot score assign 90
slot pixels from frame assign width * height
score assign score + 10
memory frame dedicated

---

7. Permissions Grammar

permission_stmt
    ::= permission_mode permission_kind IDENTIFIER NEWLINE
    ;

permission_mode
    ::= "permit"
     |  "deny"
    ;

permission_kind
    ::= "read"
     |  "change"
     |  "move"
     |  "share"
     |  "expose"
     |  "enter"
     |  "leave"
    ;

Examples:

permit read pixels
permit change result
deny expose private_key

---

8. Delegation Grammar

delegation_stmt
    ::= "delegate" IDENTIFIER delegation_permission? "to" IDENTIFIER NEWLINE
    ;

delegation_permission
    ::= "with" permission_kind
    ;

Examples:

delegate frame to render
delegate image with read to inspect
delegate buffer with change to normalize
delegate packet with move to consume
delegate data with share to broadcast

---

9. Error Grammar

error_decl
    ::= "error" IDENTIFIER NEWLINE error_field* "end" NEWLINE?
    ;

error_field
    ::= "slot" IDENTIFIER NEWLINE
    ;

attempt_stmt
    ::= "attempt" IDENTIFIER NEWLINE
    ;

handle_stmt
    ::= "handle" IDENTIFIER NEWLINE block "end" NEWLINE?
    ;

Examples:

error InvalidFrame
    slot reason
end

attempt load_texture

handle InvalidFrame
    stop
end

---

10. Route and Path Grammar

route_stmt
    ::= "route" IDENTIFIER "to" IDENTIFIER NEWLINE
    ;

parallel_stmt
    ::= "parallel" NEWLINE block "end" NEWLINE?
    ;

concurrent_stmt
    ::= "concurrent" NEWLINE path_decl+ "end" NEWLINE?
    ;

path_decl
    ::= "path" IDENTIFIER NEWLINE block "end" NEWLINE?
    ;

Examples:

route startup to main_loop

parallel
    delegate left to render_left
    delegate right to render_right
end

concurrent
    path network
        wait packet_ready
    end
end

---

11. Synchronization Grammar

sync_stmt
    ::= "sync" IDENTIFIER NEWLINE
    ;

wait_stmt
    ::= "wait" IDENTIFIER NEWLINE
    ;

signal_stmt
    ::= "signal" IDENTIFIER NEWLINE
    ;

lock_stmt
    ::= "lock" IDENTIFIER NEWLINE
    ;

unlock_stmt
    ::= "unlock" IDENTIFIER NEWLINE
    ;

---

12. Control Flow Grammar

if_stmt
    ::= "if" expression NEWLINE block else_clause? "end" NEWLINE?
    ;

else_clause
    ::= "else" NEWLINE block
    ;

when_stmt
    ::= "when" expression NEWLINE block "end" NEWLINE?
    ;

match_stmt
    ::= "match" expression NEWLINE case_clause+ else_clause? "end" NEWLINE?
    ;

case_clause
    ::= "case" expression NEWLINE block
    ;

---

13. Loop Grammar

repeat_stmt
    ::= "repeat" expression NEWLINE block "end" NEWLINE?
    ;

while_stmt
    ::= "while" expression NEWLINE block "end" NEWLINE?
    ;

for_stmt
    ::= "for" IDENTIFIER "from" expression "to" expression NEWLINE block "end" NEWLINE?
    ;

each_stmt
    ::= "each" IDENTIFIER "from" IDENTIFIER NEWLINE block "end" NEWLINE?
    ;

---

14. Return and Exit Grammar

return_stmt
    ::= "return" expression? NEWLINE
    ;

stop_stmt
    ::= "stop" NEWLINE
    ;

bypass_stmt
    ::= "bypass" NEWLINE
    ;

break_stmt
    ::= "break" NEWLINE
    ;

continue_stmt
    ::= "continue" NEWLINE
    ;

---

15. Imports, Exports, External, Native

import_decl
    ::= "import" qualified_name NEWLINE
    ;

export_decl
    ::= "export" IDENTIFIER NEWLINE
    ;

external_decl
    ::= "external" IDENTIFIER NEWLINE
    ;

native_decl
    ::= "native" IDENTIFIER NEWLINE
    ;

qualified_name
    ::= IDENTIFIER ("." IDENTIFIER)*
    ;

---

16. Expression Grammar

expression
    ::= logical_or
    ;

logical_or
    ::= logical_and ("||" logical_and)*
    ;

logical_and
    ::= equality ("&&" equality)*
    ;

equality
    ::= comparison (("==" | "!=") comparison)*
    ;

comparison
    ::= term (("<" | "<=" | ">" | ">=") term)*
    ;

term
    ::= factor (("+" | "-") factor)*
    ;

factor
    ::= unary (("*" | "/" | "%") unary)*
    ;

unary
    ::= ("!" | "-") unary
     |  primary
    ;

primary
    ::= INTEGER
     |  FLOAT
     |  STRING
     |  BOOLEAN
     |  NULL
     |  IDENTIFIER
     |  call_expr
     |  list_expr
     |  "(" expression ")"
    ;

call_expr
    ::= IDENTIFIER "(" argument_list? ")"
    ;

argument_list
    ::= expression ("," expression)*
    ;

list_expr
    ::= "[" argument_list? "]"
    ;

---

17. AST Shape Example

Source:

program Demo

entry main
    memory frame dedicated
    slot width from frame assign 1920
    slot height from frame assign 1080
    slot pixels from frame assign width * height
    permit read pixels
    return pixels
end

AST:

ProgramNode
    name: Demo

    EntryNode
        name: main

        BlockNode
            MemoryDeclNode
                name: frame
                mode: dedicated

            SlotDeclNode
                name: width
                memory: frame
                value:
                    LiteralNode integer 1920

            SlotDeclNode
                name: height
                memory: frame
                value:
                    LiteralNode integer 1080

            SlotDeclNode
                name: pixels
                memory: frame
                value:
                    BinaryExprNode *
                        left: IdentifierNode width
                        right: IdentifierNode height

            PermissionNode
                mode: permit
                kind: read
                target: pixels

            ReturnNode
                value:
                    IdentifierNode pixels

---

18. Semantic Tables

The compiler maintains five major tables.

Symbol Table
    names
    slots
    entries
    errors
    externals

Memory Table
    dedicated memory regions
    slot-to-memory relationship
    lifetime region
    escape status

Permission Table
    target
    permission kind
    granted or denied
    scope

Delegation Table
    caller
    callee
    value
    permission mode
    transfer behavior

Execution Table
    routes
    paths
    parallel regions
    concurrent regions
    synchronization points

---

19. Permission Verification

Before LLVM lowering, Foresette verifies:

read requires permit read
mutation requires permit change
transfer requires permit move
sharing requires permit share
external exposure requires permit expose
memory entrance requires permit enter
memory exit requires permit leave

Invalid example:

slot score assign 90
permit read score
score assign score + 10

Compiler diagnostic:

4SE-PERM-014

change denied for slot `score`

granted:
    read

required:
    change

---

20. LLVM Lowering Map

Program

ProgramNode
    → LLVM Module

Entry

EntryNode
    → LLVM Function

Example:

entry main

lowers to:

define i32 @main() {
}

---

21. Slot Lowering

slot x assign 10

If local and non-escaping:

%x = add i32 0, 10

If address is required:

%x.addr = alloca i32
store i32 10, ptr %x.addr

If optimized away:

no physical storage emitted

Slot rule:

A slot is a semantic position first.
Storage is emitted only when required.

---

22. Assignment Lowering

x assign x + 1

Lowering:

%old = load i32, ptr %x.addr
%new = add i32 %old, 1
store i32 %new, ptr %x.addr

If register-promoted:

%x.next = add i32 %x, 1

---

23. Dedicated Memory Lowering

memory frame dedicated
slot pixels from frame assign width * height

Semantic lowering:

create LLVM lifetime region metadata
attach noalias / alias.scope metadata where valid
attach lifetime.start / lifetime.end when storage exists

Possible LLVM form:

%frame.pixels = alloca i32
call void @llvm.lifetime.start.p0(i64 4, ptr %frame.pixels)

If frame does not escape, stack allocation is preferred.

If frame escapes, heap or caller-selected external storage is used.

---

24. Permission Lowering

Permissions mostly lower into compile-time verification and LLVM metadata.

permit read pixels
permit change pixels

Compiler effect:

allow loads
allow stores
attach access metadata
strengthen alias and mutation model

Denied permission:

deny expose private_key

Compiler effect:

reject external delegation or export of private_key

Permissions do not create runtime overhead unless runtime checking is explicitly requested.

---

25. Delegation Lowering

delegate image with read to inspect

Lowering:

call @inspect(image)

With metadata:

call void @inspect(ptr readonly %image)

Delegation modes:

with read
    → readonly parameter

with change
    → mutable pointer / reference

with move
    → ownership transfer; caller invalidated after call

with share
    → shared access; synchronization required if mutable

---

26. Error Lowering

error InvalidFrame
    slot reason
end

Lowers to one of:

tagged error code
small struct
direct control branch

Preferred optimized form:

br i1 %invalid, label %error.InvalidFrame, label %ok

Foresette errors are control-flow-visible.

No mandatory exception runtime is emitted.

---

27. Handle Lowering

handle InvalidFrame
    stop
end

Lowers to:

error.InvalidFrame:
    ret i32 1

or:

call void @abort()
unreachable

depending on "stop" policy.

---

28. Bypass Lowering

bypass

Lowers to:

br label %continue

If no work is required:

emits nothing

---

29. If Lowering

if pixels <= 0
    stop
else
    return pixels
end

LLVM shape:

%cond = icmp sle i32 %pixels, 0
br i1 %cond, label %if.then, label %if.else

if.then:
    ret i32 1

if.else:
    ret i32 %pixels

---

30. Match Lowering

match command
    case 1
        return 10
    case 2
        return 20
    else
        return 0
end

Lowers to:

switch i32 %command, label %match.else [
    i32 1, label %case.1
    i32 2, label %case.2
]

---

31. Loop Lowering

Repeat

repeat 10
    ...
end

Lowers to counted loop.

While

while active
    ...
end

Lowers to conditional branch loop.

For

for i from 0 to 10
    ...
end

Lowers to induction-variable loop.

Each

each entity from entities
    ...
end

Lowers to indexed loop or iterator lowering depending on collection representation.

---

32. Parallel Lowering

parallel
    delegate left to render_left
    delegate right to render_right
end

Lowers to one of:

LLVM task runtime call
OpenMP-style outlined functions
platform thread pool
target-specific parallel lowering

But only after verification proves:

no illegal shared mutation
all shared values have permit share
all mutable shared values are synchronized

---

33. Concurrent Lowering

concurrent
    path network
        ...
    end

    path audio
        ...
    end
end

Each path lowers to:

outlined LLVM function
state machine
coroutine-compatible function
native thread/task target

Concurrency is never implicit.

Every path originates from a source-level "path".

---

34. Sync / Wait / Signal Lowering

sync buffer

Lowers to:

memory fence
mutex boundary
atomic coordination
barrier

depending on the declared synchronization object.

wait packet_ready
signal packet_ready

Lower to condition variable, event flag, semaphore, or target runtime primitive.

---

35. Lock / Unlock Lowering

lock buffer
unlock buffer

LLVM lowering uses:

runtime lock primitive
atomic spinlock
platform mutex
target synchronization intrinsic

The chosen implementation depends on the target profile.

The semantic meaning is fixed.

---

36. External and Native Lowering

external puts
native c

Lowering:

declare i32 @puts(ptr)

Delegation:

delegate message to puts

LLVM call:

call i32 @puts(ptr %message)

---

37. Return Lowering

return value

Lowers to:

ret <type> %value

return

Lowers to:

ret void

---

38. Stop Lowering

stop

Lowers to routine termination.

Inside "main":

ret i32 1

Inside non-main:

ret error_code

or:

unreachable

depending on declared routine contract.

---

39. Optimization Metadata

Foresette gives LLVM unusually strong metadata:

slot identity
memory dedication
permission authority
delegation mode
path independence
parallel independence
error route visibility
lifetime termination
non-exposure guarantees

This enables:

mem2reg
SROA
GVN
DCE
LICM
loop unrolling
vectorization
function inlining
alias reduction
branch pruning
escape reduction
LTO
PGO

---

40. Final Compiler Contract

Foresette compilation follows this contract:

Lex source into explicit tokens.

Parse tokens into structural AST.

Build semantic graph.

Verify assignments.

Verify slots.

Verify dedicated memory.

Verify permissions.

Verify delegation.

Verify errors and handlers.

Verify parallel independence.

Verify concurrent path safety.

Lower verified graph to LLVM.

Attach Foresette intent as LLVM metadata.

Run LLVM optimization.

Emit target-native machine code.

The compiler does not guess.

The compiler does not invent missing logic.

The compiler does not infer hidden rules.

The programmer states the strategy.

The AST preserves it.

The semantic graph verifies it.

LLVM lowers it.

The machine runs it.
