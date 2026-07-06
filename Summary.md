### Foresette compiler — unified blueprint

| Layer | Role | Core artifacts |
|-------|------|----------------|
| **Front-end** | Text → tokens → AST | Lexer, Parser, AST nodes |
| **Semantic engine** | AST → Strategic Semantic Graph | Symbol/Memory/Permission/Delegation/Execution tables |
| **Verifier** | Enforce rules | Permissions, memory, delegation, parallel/concurrent, errors |
| **Lowering** | Strategy → LLVM IR | IR builder, metadata, runtime hooks |
| **Driver & tooling** | Use, inspect, ship | `4sec` CLI, diagnostics, emit modes, tests |

---

### 1. Front-end

**Lexer**

- **Keywords (50):** `program`, `entry`, `slot`, `memory`, `dedicated`, `assign`, `permit`, `deny`, `delegate`, `parallel`, `concurrent`, `error`, `handle`, `route`, `path`, `sync`, `wait`, `signal`, `lock`, `unlock`, `if`, `else`, `when`, `case`, `match`, `repeat`, `while`, `for`, `each`, `break`, `continue`, `import`, `export`, `external`, `native`, etc.   
- **Literals:** identifiers, integers, floats, strings, booleans, `null`, lists.   
- **Operators:** arithmetic, comparison, logical, delegation arrows, punctuation.   

**Parser**

- Implements the full grammar: `program_file`, `entry_decl`, `slot_decl`, `memory_decl`, `permission_stmt`, `delegation_stmt`, `error_decl`, `attempt_stmt`, `handle_stmt`, `route_stmt`, `parallel_stmt`, `concurrent_stmt`, `path_decl`, control flow (`if`, `when`, `match`, loops), exits (`return`, `stop`, `bypass`, `break`, `continue`), imports/exports/external/native.   
- Produces AST nodes like `ProgramNode`, `EntryNode`, `SlotDeclNode`, `MemoryDeclNode`, `PermissionNode`, `DelegationNode`, `ErrorDeclNode`, `ParallelNode`, `ConcurrentNode`, `PathNode`, `IfNode`, `MatchNode`, `RepeatNode`, `WhileNode`, `ForNode`, `EachNode`, `ReturnNode`, etc.   

---

### 2. Semantic engine

Builds the **Strategic Semantic Graph**:

- **Symbol table:** programs, entries, slots, errors, externals, exports.   
- **Memory table:** dedicated regions (`memory frame dedicated`), slot→memory mapping, lifetimes, escape status.   
- **Permission table:** `permit`/`deny` for `read`, `change`, `move`, `share`, `expose`, `enter`, `leave`.   
- **Delegation table:** caller, callee, value, mode (`with read`, `with change`, `with move`, `with share`).   
- **Execution table:** routes, paths, parallel regions, concurrent regions, sync/wait/signal/lock/unlock points.   

Core philosophy:

- **Assignment defines value behavior.**  
- **Slot defines computational position.**  
- **Memory defines storage relationship.**   

---

### 3. Verifier

Enforces Foresette’s “nothing guessed” law:

**Permission verification**

- `read` requires `permit read`.  
- Mutation requires `permit change`.  
- Transfer requires `permit move`.  
- Sharing requires `permit share`.  
- Exposure requires `permit expose`.  
- Enter/leave require `permit enter` / `permit leave`.   

**Delegation verification**

- `with read` → readonly parameter.  
- `with change` → mutable.  
- `with move` → ownership transfer; caller invalidated.  
- `with share` → shared; sync required if mutable.   

**Memory & slot verification**

- Every slot has a clear memory context (or none).  
- Lifetimes and escapes are explicit via dedicated memory and routes/paths.   

**Parallel / concurrent verification**

- **Parallel:** no illegal shared mutation; all shared values have `permit share`; mutable shared values must be synchronized.   
- **Concurrent:** each `path` is explicit; sync/wait/signal/lock/unlock must make shared mutation safe.   

**Errors & handlers**

- Errors are declared (`error InvalidFrame`); handlers are explicit (`handle InvalidFrame`).  
- Error flow is normal control flow, not hidden exceptions.   

---

### 4. LLVM lowering

Every semantic construct has a direct lowering rule:

**Program / entry**

- `ProgramNode` → LLVM module.  
- `EntryNode` → LLVM function (e.g., `define i32 @main()` for `entry main`).   

**Slots & assignments**

- Local, non-escaping slots → SSA values.  
- Address-needed slots → `alloca` + `store`.  
- Dead slots → no storage emitted.   

**Dedicated memory**

- `memory frame dedicated` → lifetime metadata, `noalias` / `alias.scope`, `llvm.lifetime.start/end`.   

**Permissions**

- Lowered mostly to metadata: `readonly`, `noalias`, non-exposure guarantees; compile-time checks prevent illegal operations.   

**Delegation**

- `delegate image with read to inspect` → `call @inspect(image)` with `readonly` metadata.  
- `with change` → mutable pointer/reference.  
- `with move` → ownership transfer semantics.   

**Errors & handlers**

- Errors become branches / tagged codes; handlers become labeled blocks.   

**Control flow**

- `if`, `match`, `repeat`, `while`, `for`, `each` → canonical LLVM branching and loops (`br`, `switch`, induction variables).   

**Parallel / concurrent**

- **Parallel:** outlined functions + runtime hooks / threads / tasks, only after verification of independence.   
- **Concurrent:** each `path` lowers to an outlined function / coroutine / state machine; concurrency is never implicit.   

---

### 5. Driver & tooling (4sec)

**Commands**

- `4sec build app.4se`  
- `4sec run app.4se`  
- `4sec check app.4se`  
- `4sec emit llvm app.4se`  
- `4sec emit asm app.4se`  
- `4sec emit obj app.4se`  
- `4sec optimize app.4se`   

**Diagnostics**

- Rich, relationship-based messages, e.g.:

> `4SE-PERM-014`  
> change denied for slot `frame`  
> granted: read  
> required: change  
> path: render → filter → sharpen  
> resolution: permit change frame or delegate a change-enabled slot   

---

### LOC tiers (everything in one view)

**Mature industrial compiler (the full architecture)**

- Lexer, parser, AST, all tables, verifier, LLVM lowering, optimization metadata, runtime (threads/sync), diagnostics, driver, tests.  
- **≈ 55,000–140,000 LOC** in a systems language (C/C++/Rust/Zig).

**Minimal but complete compiler**

- Lexer, parser, AST, semantic graph, verifier, LLVM lowering, basic driver.  
- **≈ 20,000–40,000 LOC**.

**Self-hosting ecosystem**

- Mature compiler + standard library + Foresette-written tools + front-end/backend in Foresette + bootstrap stabilization.  
- **≈ 70,000–120,000 LOC** total.

---

