1. Full Foresette compiler architecture

Think of the compiler as five stacked layers:

1. Front-end — text → tokens → AST  
2. Semantic engine — AST → strategic semantic graph  
3. Verifier — permissions, memory, delegation, paths  
4. Lowering — semantic graph → LLVM IR (+ metadata)  
5. Driver & tooling — 4sec CLI, diagnostics, emit modes

1.1 Front-end

Components:

- Lexer:  
  - Recognizes 50 keywords (program, entry, slot, memory, parallel, concurrent, etc.).   
  - Identifiers, integers, floats, strings, booleans, operators, punctuation.

- Parser:  
  - Implements the grammar: programfile, entrydecl, slotdecl, memorydecl, permissionstmt, delegationstmt, parallelstmt, concurrentstmt, etc.   
  - Produces AST nodes: ProgramNode, EntryNode, SlotDeclNode, MemoryDeclNode, PermissionNode, DelegationNode, ParallelNode, ConcurrentNode, PathNode, ErrorDeclNode, IfNode, RepeatNode, WhileNode, ForNode, EachNode, etc.

1.2 Semantic engine

Core job: turn AST into a Strategic Semantic Graph:

- Symbol table: programs, entries, slots, errors, externals, exports.   
- Memory table: dedicated regions, slot→memory mapping, lifetime, escape status.
- Permission table: permit/deny for read, change, move, share, expose, enter, leave.   
- Delegation table: caller, callee, value, delegation mode (with read, with change, with move, with share).   
- Execution table: routes, paths, parallel regions, concurrent regions, sync/wait/signal/lock/unlock points.

Assignments define value behavior; slots define computational position; memory defines storage relationship.   

1.3 Verifier

This is where Foresette is unusually simple:

- Permission verification:  
  - read requires permit read.  
  - mutation requires permit change.  
  - transfer requires permit move.  
  - sharing requires permit share.  
  - exposure requires permit expose.   

- Delegation verification:  
  - Check that delegation mode matches permissions (with read → readonly, with change → mutable, with move → ownership transfer, with share → shared with sync).   

- Memory & slot verification:  
  - Every slot has a defined memory context (or none).  
  - Lifetime and escape rules are explicit.

- Parallel/concurrent verification:  
  - Parallel regions: no illegal shared mutation; all shared values have permit share; synchronized if mutable.   
  - Concurrent paths: explicit path blocks, explicit sync/wait/signal/lock/unlock.

- Error & handler verification:  
  - Errors are declared (error InvalidFrame), handlers are explicit (handle InvalidFrame).   

1.4 LLVM lowering

Each semantic construct has a direct lowering rule:

- Program / entry:  
  - ProgramNode → LLVM module.  
  - EntryNode → LLVM function (e.g., define i32 @main()).

- Slots:  
  - Local, non-escaping → SSA value.  
  - Needs address → alloca + store.  
  - Dead → no storage emitted.   

- Assignments:  
  - x assign x + 1 → load, add, store (or SSA add).

- Dedicated memory:  
  - memory frame dedicated → lifetime metadata, noalias/alias.scope, llvm.lifetime.start/end.   

- Permissions:  
  - Lower mostly to metadata: readonly, noalias, non-exposure guarantees.

- Delegation:  
  - delegate image with read to inspect → call @inspect(image) with readonly metadata.   

- Errors & handlers:  
  - Errors → branches / tagged codes.  
  - handle blocks → labeled basic blocks.

- Control flow:  
  - if, match, repeat, while, for, each → canonical LLVM branching and loops.   

- Parallel / concurrent:  
  - Parallel → outlined functions + runtime hooks / threads / tasks.  
  - Concurrent paths → outlined functions / coroutines / state machines.

1.5 Driver & tooling (4sec)

- Commands: 4sec build, 4sec run, 4sec check, 4sec emit llvm, 4sec emit asm, 4sec emit obj, 4sec optimize.   
- Diagnostics: permission errors, delegation errors, memory violations, path conflicts, etc., with codes like 4SE-PERM-014.   

---

2. Subsystem-by-subsystem LOC plan

Here’s a realistic LOC budget if you implement in a systems language (C, C++, Rust, Zig):

| Subsystem | LOC (min) | LOC (max) | Notes |
|----------|-----------|-----------|-------|
| Lexer | 1,000 | 2,000 | 50 keywords, simple tokens |
| Parser | 4,000 | 7,000 | Recursive descent or Pratt |
| AST definitions | 2,000 | 4,000 | Node structs/enums |
| Symbol table | 1,000 | 2,000 | Names, entries, errors, externals |
| Memory table | 800 | 1,500 | Dedicated regions, lifetimes |
| Permission table | 800 | 1,500 | permit/deny graph |
| Delegation table | 800 | 1,500 | Caller/callee/value/mode |
| Execution table | 1,500 | 3,000 | routes, paths, parallel, concurrent |
| Semantic verifier | 4,000 | 8,000 | permissions, delegation, memory, errors, paths |
| LLVM lowering core | 8,000 | 20,000 | IR builder, mapping rules |
| Optimization metadata | 1,000 | 3,000 | slot/memory/permission metadata |
| Runtime (threads, sync) | 2,000 | 5,000 | locks, signals, thread pool |
| Diagnostics & error reporting | 3,000 | 8,000 | codes, messages, context |
| Driver (4sec) | 3,000 | 8,000 | CLI, options, pipelines |
| Tests & examples | 10,000 | 30,000 | unit + integration tests |

Total mature compiler: ~55,000–140,000 LOC  
Minimal but complete: ~20,000–40,000 LOC

---

3. Minimal compiler in 30 steps

This is your “buildable” roadmap—no fluff, just steps.

Phase 1 — Skeleton (1–6)

1. Choose implementation language (C, C++, Rust, Zig).  
2. Set up project structure: lexer/, parser/, ast/, sem/, llvm/, driver/.  
3. Implement token enum + keyword table (50 keywords).   
4. Write a streaming lexer (identifiers, literals, operators, punctuation, NEWLINE).  
5. Implement basic error reporting infrastructure (file, line, column, code, message).  
6. Add a tiny main that lexes a file and prints tokens.

Phase 2 — Parsing & AST (7–13)

7. Implement parser for programfile and programdecl.   
8. Add entry_decl and block parsing.  
9. Implement slotdecl, memorydecl, assignment.  
10. Implement permissionstmt and delegationstmt.  
11. Implement errordecl, attemptstmt, handle_stmt.  
12. Implement parallelstmt, concurrentstmt, path_decl.  
13. Implement control flow (if, match, loops) and return/stop/bypass.

At this point: you can parse full Foresette programs into AST.

Phase 3 — Semantic graph (14–20)

14. Build symbol table from AST (programs, entries, slots, errors, externals).   
15. Build memory table (dedicated regions, slot→memory mapping, lifetimes).  
16. Build permission table from permit/deny statements.  
17. Build delegation table from delegate statements.  
18. Build execution table (routes, paths, parallel, concurrent, sync/wait/signal/lock/unlock).  
19. Implement assignment semantics (value behavior from assign).   
20. Add basic semantic checks (undefined slots, duplicate entries, missing errors).

Now you have a Strategic Semantic Graph.

Phase 4 — Verification (21–24)

21. Implement permission verification rules (read/change/move/share/expose/enter/leave).   
22. Implement delegation verification (mode vs permissions, ownership transfer).  
23. Implement parallel/concurrent verification (shared mutation, sync requirements).  
24. Implement error/handler verification (declared errors, reachable handlers).

At this point: you reject invalid programs with precise diagnostics.

Phase 5 — LLVM lowering (25–29)

25. Integrate LLVM and create module/function builders.  
26. Lower entries to LLVM functions.  
27. Lower slots, assignments, control flow, loops.   
28. Lower dedicated memory, permissions, delegation, errors, parallel, concurrent.  
29. Emit object files, executables, and emit llvm/asm/obj modes.

Phase 6 — Driver & self-check (30)

30. Implement 4sec driver with subcommands: build, run, check, emit llvm, emit asm, emit obj, optimize.   

At this point: you have a minimal but real Foresette compiler.

---

4. Self-hosting roadmap

Self-hosting is where this language really wants to go.

Stage 1 — Stable native compiler

- Compiler implemented in a host language (e.g., Rust or C++).  
- Can compile .4se to native binaries.  
- Has stable semantics and lowering.

Stage 2 — Foresette standard library

- Implement core library in Foresette:  
  - math, memory helpers, containers, concurrency helpers, IO wrappers.  
- Use Foresette’s own features: slots, dedicated memory, permissions, delegation, parallel, concurrent.

Stage 3 — Foresette-written tools

- Write small tools in Foresette:  
  - formatters, linters, test runners, build scripts.  
- Compile them with the host-language compiler.

Stage 4 — Foresette front-end in Foresette

- Reimplement lexer, parser, AST builder, semantic graph builder, verifier in Foresette itself.  
- Compile this Foresette front-end with the original compiler.  
- Link against the existing LLVM backend (still in host language) via native interop (external, native).   

Stage 5 — Foresette backend in Foresette

- Gradually port lowering logic to Foresette:  
  - IR builder wrappers  
  - metadata construction  
  - optimization configuration  

Stage 6 — Full self-host

- Build the compiler using its own binary.  
- Verify that compiling the compiler with itself is stable (same output or acceptable differences).  
- Freeze a “bootstrap” version for future builds.

---

