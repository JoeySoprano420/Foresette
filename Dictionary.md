Foresette ".4se" Complete Language Dictionary

AOT

Ahead-of-Time compilation.

Foresette compiles source code into native machine code before the program runs.

.4se source → LLVM → native executable

Foresette does not depend on an interpreter or mandatory virtual machine.

---

Active State

The current live state of a program.

Example:

slot current_scene assign "forest"

"current_scene" is active state because it represents what is true now.

---

Applied State

A finalized state after validation.

Example:

slot volume assign 70
slot selected_volume assign 85

"selected_volume" is staged.
"volume" is applied.

---

assign

Assigns a value to a slot.

slot score assign 90
score assign score + 10

Assignment is Foresette’s value contract.

---

Assignment

The act of establishing or replacing a value.

slot health assign 100
health assign health - 10

A new assignment changes the current value of a slot.

Changing an existing slot requires:

permit change health

---

Assignment Contract

The rule that a value’s behavior is established by what is assigned.

slot name assign "Clarissa"
slot score assign 95
slot active assign true

The compiler understands behavior from the assigned value.

---

AST

Abstract Syntax Tree.

The parser turns source code into a tree.

Example source:

slot pixels from frame assign width * height

AST idea:

SlotDeclNode
    name: pixels
    memory: frame
    value:
        BinaryExprNode *
            width
            height

---

attempt

Begins an operation that may fail.

attempt load_texture

Usually paired with "handle".

---

Bypass

An explicit “do nothing and continue” response.

handle MissingTexture
    bypass
end

This is not accidental ignoring. It is intentional non-action.

---

bypass

Keyword for intentional non-action.

bypass

Used when failure or a branch should safely continue.

---

break

Exits a loop.

while running
    if done
        break
    end
end

---

case

Used inside "match".

match command
    case "start"
        return 1
    case "stop"
        return 0
end

---

change

Permission allowing mutation.

permit change health
health assign health - 10

Without "change", modifying "health" fails compilation.

---

Collection

A group of values assigned together.

slot scores assign [90, 85, 100]

Collections should have clear element behavior.

---

Concurrent

Independent execution paths progressing at the same time.

concurrent
    path input
        wait input_ready
    end

    path audio
        signal audio_ready
    end
end

Concurrency is explicit in Foresette.

---

concurrent

Starts a concurrent block.

concurrent
    path network
        ...
    end
end

---

Compiler Contract

Foresette’s compiler contract:

Lex source.
Parse tokens.
Build AST.
Build semantic graph.
Verify permissions.
Verify memory.
Verify delegation.
Lower to LLVM.
Optimize.
Emit native code.

The compiler does not invent missing intent.

---

Constraint

A rule that defines valid state.

Example:

if volume > 100
    handle InvalidSetting
        stop
    end
end

Foresette does not invent application constraints. The programmer defines them.

---

continue

Skips to the next loop cycle.

while running
    if skip_frame
        continue
    end
end

---

Dead Path

A branch or execution path that can never run.

Example:

slot x assign 10

if x > 100
    stop
end

LLVM may remove the impossible branch.

---

dedicated

Marks memory as deliberately associated with a region.

memory player dedicated

---

Dedicated Memory

Explicit memory relationship.

memory player dedicated

slot health from player assign 100
slot stamina from player assign 80

The compiler sees that "health" and "stamina" belong to "player".

---

Delegation

Explicitly sending a value to a routine with authority.

delegate image with read to inspect
delegate buffer with change to normalize

Delegation defines parameter relationship.

---

delegate

Keyword for sending a value to a target routine.

delegate message to puts

With permission:

delegate frame with read to render

---

deny

Explicitly denies permission.

deny expose private_key

A denied operation is rejected even if attempted later.

---

Deterministic Execution

Execution where behavior is clearly defined.

Foresette favors:

explicit assignment
explicit memory
explicit permission
explicit delegation
explicit paths
explicit errors

---

Dictionary Rule

In Foresette, every important action answers:

What exists?
Where does it belong?
Who may touch it?
Where does it go?
What can stop it?

---

each

Loops over every item in a collection.

each score from scores
    delegate score with read to inspect
end

Use "each" when the index does not matter.

---

else

Fallback branch for "if" or "match".

if score >= 90
    return "A"
else
    return "Not A"
end

---

end

Closes a block.

entry main
    return 0
end

Used with:

entry
error
if
while
for
each
parallel
concurrent
path
handle
match
when

---

enter

Permission for entering a protected memory or execution context.

permit enter secure_zone

---

entry

Defines an executable routine.

entry main
    return 0
end

"main" is the usual program start.

---

Error

A user-defined failure.

error PlayerDefeated
    slot reason
end

Foresette does not impose a universal exception hierarchy.

---

error

Keyword for declaring a user-defined failure.

error InvalidScore
    slot value
    slot reason
end

---

Error Flow

The visible path of failure through the program.

handle SaveCorrupt
    stop
end

Error flow is control flow.

---

Execution Graph

The compiler’s view of program movement.

Example:

main
 ├─ validate
 ├─ load
 ├─ finalize
 └─ shutdown

Routes, paths, loops, and handlers all contribute to the execution graph.

---

Execution Table

Compiler table tracking routes, paths, parallel blocks, concurrent blocks, signals, waits, and synchronization.

---

expose

Permission for sending a value outside its boundary.

permit expose reason
deny expose private_key

Printing, exporting, or external calls may require exposure authority.

---

External

A native symbol outside Foresette.

external puts
native c

---

external

Declares an outside function or symbol.

external puts

---

Failed Resource

A resource that was attempted but did not load.

resource_states[i] assign "failed"

Usually paired with:

handle ResourceFailed

---

for

Indexed loop.

for i from 0 to 3
    slot value assign scores[i]
end

Use "for" when the index matters.

---

from

Connects a slot to memory or loop value source.

Memory use:

slot health from player assign 100

Loop use:

each item from inventory

For-loop use:

for i from 0 to 10

---

Grammar

The formal structure of valid Foresette code.

Example:

slot_decl ::= "slot" IDENTIFIER "assign" expression

Grammar decides what source code is valid.

---

handle

Defines what happens when an error occurs.

handle InvalidSetting
    slot reason assign "Bad setting."
    delegate reason to puts
    stop
end

---

Handler

A block that responds to an error.

handle PlayerDefeated
    stop
end

Handlers are explicit.

---

if

Conditional branch.

if health <= 0
    stop
end

With "else":

if score >= 90
    return "excellent"
else
    return "normal"
end

---

import

Brings in another module.

import math
import engine.render

---

Index

A numeric position inside a collection.

scores[0]
scores[1]
scores[2]

Foresette uses zero-based indexing.

---

Input Link

Delegation-style relationship for input.

Conceptual operator:

routine <= value

The official readable form is:

delegate value with read to routine

---

LLVM

The compiler infrastructure Foresette lowers into.

Pipeline:

Foresette AST → semantic graph → LLVM IR → optimized native code

LLVM handles optimization and machine-code generation.

---

LLVM Lowering

The process of converting Foresette semantics into LLVM IR.

Example:

slot x assign 10

can lower to:

%x = add i32 0, 10

or disappear if optimized.

---

lock

Protects shared mutable state.

lock counter
counter assign counter + 1
unlock counter

Used in concurrent or parallel shared mutation.

---

Lock Order

The consistent order of acquiring locks.

Good:

lock health
lock position

unlock position
unlock health

All paths should use the same order to avoid deadlock.

---

Manual Error Handling

The programmer defines failure behavior.

handle ReplayCorrupt
    stop
end

No invisible exception system decides what happens.

---

match

Structured selection.

match command
    case "start"
        return 1
    case "stop"
        return 0
    else
        return -1
end

---

Memory

A named storage relationship.

memory frame dedicated

---

memory

Declares a memory region.

memory engine dedicated

---

Memory Table

Compiler table tracking memory regions and which slots belong to them.

Example:

player:
    health
    stamina
    position

---

move

Permission for transfer.

permit move packet
delegate packet with move to consume

After move, the caller should not use the moved value.

---

Native

Targeting platform-native execution.

Foresette compiles to native binaries.

---

native

Declares the native interface style.

external puts
native c

---

No Guess Rule

Foresette’s central law:

Nothing is guessed that can be stated.

Programmer states intent. Compiler verifies and lowers it.

---

Parallel

Simultaneous independent work.

parallel
    delegate left with read to render_left
    delegate right with read to render_right
end

Parallel work must be safe.

---

parallel

Starts a parallel block.

parallel
    ...
end

---

Parameter Delegation

The Foresette alternative to vague function argument passing.

delegate image with read to inspect
delegate image with change to edit
delegate packet with move to consume

The relationship is visible.

---

path

Defines a concurrent execution lane.

concurrent
    path network
        wait packet_ready
    end
end

---

Path

A named independent execution progression.

Example:

path audio
path input
path network

---

Permission

Authority to act on a slot or memory context.

Kinds:

read
change
move
share
expose
enter
leave

---

Permission Table

Compiler table tracking granted and denied authority.

Example:

health:
    read
    change

---

Permission-Based Safety

Foresette’s safety model.

Code can only do what it has permission to do.

permit read score
deny expose password

---

permit

Grants permission.

permit read score
permit change score

---

Program

A Foresette source unit.

program Hello

---

program

Declares the program name.

program GameDemo

---

read

Permission for inspecting a value.

permit read health

Reading does not imply changing.

---

Replay

Recorded state over time.

Example:

slot replay_frames assign [2, 3, 4, 5, 6]

Replay systems validate before playback.

---

Resource State

A string or value describing a resource’s status.

Typical states:

"waiting"
"loading"
"loaded"
"failed"

---

return

Exits a routine and optionally sends back a value.

return 0
return health
return

---

route

Defines major execution direction.

route save to validate
route validate to load
route load to shutdown

---

Routine

An executable section declared with "entry".

entry update
    return 0
end

---

Safety

Foresette safety is based on explicit authority, visible memory, named errors, and synchronized sharing.

---

Scene

A game or program world-state.

Example:

slot current_scene assign "forest"
slot next_scene assign "castle"

---

Semantic Graph

The compiler’s meaning-level representation of the program.

It tracks:

slots
assignments
memory
permissions
delegation
errors
routes
paths
parallelism
concurrency

---

share

Permission allowing a value to cross shared execution contexts.

permit share buffer

Shared mutable state usually requires locking or synchronization.

---

Shared Mutation

When multiple paths can change the same value.

Requires:

permit share value
permit change value
lock value
unlock value

---

signal

Announces that an event is ready.

signal texture_ready

Used with "wait".

---

Slot

A named computational position.

slot score assign 90

A slot is not automatically physical memory. It may become a register, stack value, dedicated memory, or disappear during optimization.

---

slot

Declares a slot.

slot health assign 100

With memory:

slot health from player assign 100

---

Split-Compute-Merge

A safe performance pattern.

parallel
    slot left_result assign left + 1
    slot right_result assign right + 1
end

slot total assign left_result + right_result

Avoids shared mutation.

---

Staged State

Temporary candidate state waiting for validation.

Example:

slot selected_volume assign 85
slot volume assign 70

"selected_volume" is staged.
"volume" is applied.

---

stop

Terminates the current route or routine.

handle FatalError
    stop
end

---

sync

Coordinates shared state.

sync buffer

May lower to a fence, barrier, mutex, or target synchronization primitive.

---

Synchronization

Coordination that makes shared execution safe.

Tools:

sync
wait
signal
lock
unlock

---

Token

A meaningful source-code piece.

Example:

slot score assign 90

Tokens:

TOKEN_SLOT
IDENTIFIER(score)
TOKEN_ASSIGN
INTEGER(90)

---

to

Used in routes and delegation.

route load to finalize
delegate message to puts

---

unlock

Releases a lock.

unlock buffer

---

Validation

Checking candidate state before accepting it.

Example:

if selected_volume > 100
    handle InvalidSetting
        stop
    end
end

---

wait

Pauses until a signal/event is ready.

wait texture_ready

---

when

Runs a block when a condition is true.

when applying
    volume assign selected_volume
end

---

while

Loop that continues while a condition is true.

while running
    frame assign frame + 1
end

---

with

Used to attach permission to delegation.

delegate frame with read to render
delegate buffer with change to normalize

---

The 50 Core Keywords

program
entry
end
slot
memory
dedicated
assign
permit
deny
read
change
move
share
expose
enter
leave
delegate
from
to
with
return
stop
bypass
error
handle
attempt
route
path
parallel
concurrent
sync
wait
signal
lock
unlock
if
else
when
case
match
repeat
while
for
each
break
continue
import
export
external
native

---

Keyword Dictionary

program

Starts a program.

program Hello

---

entry

Defines a routine.

entry main
    return 0
end

---

end

Closes a block.

if ready
    return 1
end

---

slot

Creates a computational position.

slot score assign 90

---

memory

Declares a memory region.

memory player dedicated

---

dedicated

Marks memory as explicitly associated.

memory frame dedicated

---

assign

Assigns a value.

score assign score + 10

---

permit

Grants authority.

permit read score

---

deny

Forbids authority.

deny expose password

---

read

Allows inspection.

permit read health

---

change

Allows mutation.

permit change health

---

move

Allows transfer.

permit move packet

---

share

Allows shared access.

permit share buffer

---

expose

Allows external exposure.

permit expose message

---

enter

Allows entering a protected context.

permit enter zone

---

leave

Allows leaving a protected context.

permit leave zone

---

delegate

Sends a value to a target.

delegate frame with read to render

---

from

Specifies source or memory relationship.

slot health from player assign 100

---

to

Specifies destination.

delegate message to puts

---

with

Specifies delegation authority.

delegate data with read to inspect

---

return

Returns from a routine.

return 0

---

stop

Stops execution path.

stop

---

bypass

Does nothing intentionally.

bypass

---

error

Declares a user-defined error.

error InvalidInput
    slot reason
end

---

handle

Handles an error.

handle InvalidInput
    stop
end

---

attempt

Marks an attempted operation.

attempt load_file

---

route

Declares major control flow direction.

route validate to apply

---

path

Declares concurrent lane.

path audio
    ...
end

---

parallel

Runs independent work together.

parallel
    ...
end

---

concurrent

Runs independent paths.

concurrent
    path input
        ...
    end
end

---

sync

Coordinates shared state.

sync buffer

---

wait

Waits for a signal.

wait audio_ready

---

signal

Sends a readiness signal.

signal audio_ready

---

lock

Locks shared mutable state.

lock counter

---

unlock

Unlocks shared mutable state.

unlock counter

---

if

Conditional branch.

if health <= 0
    stop
end

---

else

Fallback branch.

else
    bypass

---

when

Condition-triggered action.

when ready
    delegate frame to render
end

---

case

Branch inside match.

case "start"
    return 1

---

match

Multi-case selection.

match command
    case "start"
        return 1
end

---

repeat

Repeats a block a fixed number of times.

repeat 5
    delegate message to puts
end

---

while

Repeats while condition is true.

while running
    ...
end

---

for

Indexed loop.

for i from 0 to 10
    ...
end

---

each

Collection loop.

each item from inventory
    ...
end

---

break

Exits a loop.

break

---

continue

Skips to next loop cycle.

continue

---

import

Imports module.

import engine.render

---

export

Exposes symbol.

export main

---

external

Declares outside symbol.

external puts

---

native

Declares native ABI/interface.

native c

---

Operator Dictionary

+

Addition.

slot total assign a + b

---

-

Subtraction or negative value.

slot damage assign attack - defense
slot inverse assign -value

---

*

Multiplication.

slot pixels assign width * height

---

/

Division.

slot average assign total / count

---

%

Remainder/modulo.

slot remainder assign value % 2

---

==

Equality comparison.

if selected == option

---

!=

Not equal.

if state != "loaded"

---

<

Less than.

if health < 0

---

<=

Less than or equal.

if health <= 0

---

>

Greater than.

if volume > 100

---

>=

Greater than or equal.

if score >= 90

---

&&

Logical AND.

if ready && active

---

||

Logical OR.

if failed || missing

---

!

Logical NOT.

if !ready

---

[]

Collection indexing.

scores[0]

---

()

Grouping or call syntax.

slot result assign add()
slot value assign (a + b) * c

---

.

Qualified name separator.

import engine.render

---

,

List separator.

[1, 2, 3]

---

Literal Dictionary

Integer

Whole number.

slot count assign 10

---

Float

Decimal number.

slot ratio assign 0.75

---

String

Text.

slot name assign "Foresette"

---

Boolean

Logical true or false.

slot running assign true
slot loaded assign false

---

Null

Empty value.

slot optional assign null

---

List

Collection literal.

slot names assign ["forest", "castle", "arena"]

---

Common Patterns

Hello World

program Hello

external puts
native c

entry main
    slot message assign "Hello, Foresette."
    delegate message to puts
    return 0
end

---

Safe Mutation

slot health assign 100

permit read health
permit change health

health assign health - 10

---

Dedicated Memory

memory player dedicated

slot health from player assign 100
slot stamina from player assign 80

---

Manual Error

error InvalidScore
    slot reason
end

handle InvalidScore
    slot reason assign "Score invalid."
    stop
end

---

Parallel Read Work

parallel
    delegate left with read to process_left
    delegate right with read to process_right
end

---

Safe Shared Counter

permit read counter
permit change counter
permit share counter

lock counter
counter assign counter + 1
unlock counter

---

Signal and Wait

path loader
    signal texture_ready
end

path renderer
    wait texture_ready
end

---

Validate Before Apply

if selected_volume > 100
    handle InvalidSetting
        stop
    end
end

volume assign selected_volume

---

Split-Compute-Merge

parallel
    slot a_result assign a + 1
    slot b_result assign b + 1
end

slot total assign a_result + b_result

---

Final Foresette Definition

Foresette is a deterministic, AOT-compiled, LLVM-based native language built around explicit strategy.

Its core ideas are:

assignment defines value behavior
slot defines computational position
memory defines storage relationship
permission defines authority
delegation defines parameter movement
error defines failure
handle defines response
route defines major direction
parallel defines simultaneous independent work
concurrent defines independent execution paths
sync/lock/wait/signal define coordination

Its philosophy is:

Nothing is guessed that can be stated.
Nothing is hidden that affects execution.
Nothing is carried at runtime that can disappear at compile time.

The programmer states the plan.

The compiler verifies the plan.

LLVM clears the path.

The machine runs.
