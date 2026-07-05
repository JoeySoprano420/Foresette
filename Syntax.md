Foresette ".4se" Syntax Specification

Finalized 50-Keyword Vocabulary

Foresette is built around explicit assignment, slots, permissions, delegation, paths, dedicated memory, manual errors, and zero-guess compilation.

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

1. File Extension

Foresette source files use:

.4se

Example:

main.4se
engine.4se
memory.4se

---

2. Program Structure

A Foresette program begins with "program" and contains one or more procedures.

program HelloWorld

entry main
    slot message assign "Hello, Foresette."
    return message
end

"program" names the compilation unit.

"entry" defines an executable entry routine.

"end" closes the current structure.

---

3. Assignment

Assignment is the value contract.

slot count assign 40
slot name assign "Foresette"
slot active assign true
slot ratio assign 0.75

Foresette does not force ceremonial static/dynamic type syntax.

The assignment establishes the value’s usable behavior.

---

4. Slots

A slot is an explicit computational position.

slot total assign 0
slot score assign 95
slot result assign total + score

Slots are not automatically heap objects.

A slot may lower to:

register
stack
dedicated memory
vector lane
constant
nothing after optimization

The compiler chooses the cheapest valid physical form.

---

5. Dedicated Memory

Dedicated memory creates an explicit storage relationship.

memory frame dedicated

slot pixels from frame assign camera_buffer
slot width from frame assign 1920
slot height from frame assign 1080

This tells the compiler:

pixels belongs to frame
width belongs to frame
height belongs to frame

The compiler does not guess memory association.

The source declares it.

---

6. Permissions

Permissions define authority.

permit read pixels
permit change pixels
deny expose pixels

Common permission patterns:

permit read data
permit change data
permit move packet
permit share buffer
permit enter memory_zone
deny expose private_key

If code lacks permission, compilation fails.

---

7. Delegation

Delegation defines parameter movement.

delegate frame to render
delegate packet to network
delegate image with read to filter
delegate buffer with change to normalize

Delegation is not a vague function call.

It states the relationship.

delegate value to routine

means:

this value is intentionally delivered to this routine

With permission:

delegate image with read to inspect
delegate image with change to sharpen
delegate image with move to consume
delegate image with share to broadcast

The compiler knows exactly what the callee may do.

---

8. Procedures

A routine is declared with "entry".

entry add
    slot a assign 10
    slot b assign 20
    slot sum assign a + b
    return sum
end

A routine may receive delegated values.

entry render
    slot frame assign received
    return frame
end

In mature Foresette, call boundaries are always delegation-aware.

---

9. Errors

Errors are user-defined.

error InvalidFrame
    slot reason assign "Frame is invalid."
end

Errors may carry explicit slots.

error InvalidScore
    slot value
    slot reason
end

The language supplies error structure.

The user supplies failure meaning.

---

10. Manual Error Handling

Failure handling is explicit.

attempt load_texture

handle CorruptTexture
    bypass
end

handle DeviceUnavailable
    stop
end

There is no hidden exception runtime.

There is no automatic unwinding.

There is no silent propagation.

Error flow is normal control flow.

---

11. Routes

Routes define explicit execution direction.

route startup to load_assets
route load_assets to main_loop
route main_loop to shutdown

Routes make control movement visible.

The compiler does not infer the program’s strategic path from scattered calls.

---

12. Paths

Paths define independent execution progression.

concurrent
    path network
    path audio
    path input
end

Each "path" is a named lane of progress.

Paths must use explicit sharing and synchronization.

permit share packets
sync packets

---

13. Parallelism

Parallel work is declared manually.

parallel
    delegate left_half to render_left
    delegate right_half to render_right
end

The programmer identifies independent work.

The compiler verifies it.

LLVM lowers it.

The machine executes it.

---

14. Concurrency

Concurrent systems are built explicitly.

concurrent
    path network
        wait signal packet_ready
        delegate packet to process_packet
    end

    path audio
        delegate sound_mix to output_audio
    end
end

No hidden tasks.

No surprise scheduler.

No invisible async behavior.

The concurrent topology is source-visible.

---

15. Synchronization

Synchronization is explicit.

lock buffer
change buffer
unlock buffer

Signals are explicit.

signal packet_ready
wait packet_ready

Shared values require permission.

permit share buffer
sync buffer

---

16. Conditions

Conditional execution is deterministic.

if score > 90
    return "excellent"
else
    return "normal"
end

"when" is used for direct state response.

when packet_ready
    delegate packet to process
end

"case" and "match" handle structured selection.

match command
    case "start"
        route current to startup
    case "stop"
        route current to shutdown
    else
        bypass
end

---

17. Loops

Foresette loops are direct and explicit.

repeat 10
    slot count assign count + 1
end

while active
    delegate frame to render
end

for i from 0 to 10
    slot total assign total + i
end

each entity from entities
    delegate entity to update
end

Loop control:

break
continue

---

18. Imports and Exports

Imports bring in declared interfaces.

import math
import engine.memory

Exports expose symbols.

export main
export render

External bindings are explicit.

external printf
native c

---

19. Native Interop

Native interop is declared directly.

external puts
native c

Example:

program NativeHello

external puts
native c

entry main
    slot message assign "Hello from Foresette."
    delegate message to puts
    return 0
end

Interop is never magical.

The external boundary is visible.

---

20. Canonical Hello World

program Hello

external puts
native c

entry main
    slot message assign "Hello, Foresette."
    delegate message to puts
    return 0
end

---

21. Canonical Memory Example

program FrameMemory

entry main
    memory frame dedicated

    slot width from frame assign 1920
    slot height from frame assign 1080
    slot pixels from frame assign width * height

    permit read pixels
    permit change pixels

    return pixels
end

---

22. Canonical Permission Example

program PermissionDemo

entry main
    slot score assign 90

    permit read score
    permit change score

    slot improved assign score + 10

    return improved
end

Invalid example:

program BadPermission

entry main
    slot score assign 90

    permit read score

    score assign score + 10

    return score
end

This fails because "change" permission was not granted.

---

23. Canonical Error Example

program ErrorDemo

error InvalidScore
    slot value
    slot reason
end

entry check_score
    slot score assign 120

    if score > 100
        handle InvalidScore
            stop
        end
    else
        return score
    end
end

---

24. Canonical Parallel Example

program ParallelRender

entry main
    memory frame dedicated

    slot left from frame assign 0
    slot right from frame assign 1

    permit read left
    permit read right

    parallel
        delegate left to render_left
        delegate right to render_right
    end

    return 0
end

---

25. Canonical Concurrent Example

program EngineLoop

entry main
    memory engine dedicated

    slot packets from engine assign 0
    slot audio from engine assign 0
    slot input from engine assign 0

    permit share packets
    permit share audio
    permit share input

    concurrent
        path network
            wait packet_ready
            delegate packets with change to process_network
        end

        path sound
            delegate audio with change to mix_audio
        end

        path controls
            delegate input with change to read_input
        end
    end

    return 0
end

---

26. Zero-Guess Compilation Rules

Foresette is governed by one compiler law:

Nothing is guessed that can be stated.

Therefore:

assignment defines value behavior
slot defines computational position
memory defines storage relationship
permission defines authority
delegation defines parameter relationship
error defines failure
handle defines response
parallel defines simultaneous work
concurrent defines independent progression
path defines execution lane
sync defines coordination
route defines control direction

The compiler does not invent intent.

The compiler verifies stated intent.

LLVM optimizes the verified strategy.

---

27. Fully Mature Foresette Example

program ImagePipeline

external puts
native c

error InvalidFrame
    slot reason
end

entry main
    memory frame dedicated
    memory output dedicated

    slot width from frame assign 1920
    slot height from frame assign 1080
    slot pixels from frame assign width * height

    slot result from output assign 0

    permit read width
    permit read height
    permit read pixels
    permit change result
    permit share pixels

    if pixels <= 0
        handle InvalidFrame
            slot reason assign "Frame has no pixels."
            delegate reason to puts
            stop
        end
    else
        parallel
            delegate pixels with read to scan_edges
            delegate pixels with read to scan_color
            delegate pixels with read to scan_motion
        end

        concurrent
            path render
                delegate pixels with read to draw_frame
            end

            path audio
                signal frame_ready
                wait audio_ready
            end
        end

        result assign pixels
        return result
    end
end

This example demonstrates the entire Foresette philosophy:

explicit memory
explicit slots
explicit assignment
explicit permission
explicit errors
explicit handling
explicit parallelism
explicit concurrency
explicit delegation
explicit native execution

---

Final Definition

Foresette ".4se" is a deterministic native language where the programmer writes the strategy plainly enough that the compiler does not have to guess.

Its syntax is built from 50 core keywords.

Its execution model is centered on assignment, slots, dedicated memory, permissions, delegation, routes, paths, explicit errors, manual handling, parallel regions, and concurrent topology.

Its compiler performs minimal semantic discovery because the source provides maximum strategic clarity.

Foresette is concise without being vague.

It is explicit without being bloated.

It is safe without being managed.

It is native without being reckless.

It is expressive without hiding execution.

The programmer states the plan.

The compiler verifies the plan.

LLVM clears the road.

The machine runs.
