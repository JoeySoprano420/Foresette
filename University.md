Foresette Academy

Taught by Clarissa Taylor

Assistant Instructor: Sherita Pleasant

---

Opening Scene

The classroom lights dim.

On the screen appears:

FORESETTE .4se
Nothing is guessed that can be stated.

Clarissa Taylor steps to the front of the room.

She is calm, sharp, and encouraging — the kind of teacher who makes complicated things feel possible.

Sherita Pleasant stands beside the desk with a laptop open, already smiling like she knows somebody is about to say, “Wait… programming can be this direct?”

Clarissa says:

“Today, you are not learning a toy language. You are learning how to speak directly to a machine with clarity. Foresette is about telling the computer exactly what you mean.”

Sherita adds:

“And not making the compiler dig through a swamp with a flashlight.”

The class laughs.

Clarissa points to the screen.

“Good. Let’s begin.”

---

Lesson 1 — What Foresette Is

Foresette is a performance-oriented programming language.

Its files end in:

.4se

It is:

AOT-compiled
LLVM-based
native-speed
explicit
deterministic
permission-based
manual-error-handled
slot-based
memory-aware
parallel/concurrent by declaration

Clarissa writes:

The programmer states the strategy.
The compiler verifies it.
LLVM optimizes it.
The machine runs it.

Sherita says:

“In other words, Foresette does not want mystery. It wants receipts.”

---

Lesson 2 — The First Program

Clarissa types:

program Hello

external puts
native c

entry main
    slot message assign "Hello, Foresette."
    delegate message to puts
    return 0
end

She explains:

program Hello

names the program.

external puts
native c

means we are using a C-style native function named "puts".

entry main

is where the program starts.

slot message assign "Hello, Foresette."

creates a value position called "message".

delegate message to puts

sends the message to the print function.

return 0

ends successfully.

Sherita says:

“This is Hello World, but wearing steel-toe boots.”

---

Lesson 3 — The 50 Keywords

Clarissa hands out the official keyword sheet:

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

Clarissa says:

“These are the bricks. Everything else is how we build.”

---

Lesson 4 — Slots

A slot is a named value position.

slot age assign 16
slot name assign "Maya"
slot active assign true
slot score assign 98

Sherita explains:

“A slot is not automatically a box in memory. It is a place in the program’s logic. The compiler later decides if it becomes a register, stack spot, memory space, or disappears during optimization.”

Clarissa writes:

slot total assign 10 + 20
return total

The class sees:

total = 30

Clarissa says:

“In Foresette, slots make value flow visible.”

---

Lesson 5 — Assignment

Assignment is the value contract.

slot score assign 90

This tells the compiler:

score behaves like a number

Another example:

slot name assign "Clarissa"

This tells the compiler:

name behaves like text

Foresette does not start with type ceremony.

It starts with assignment truth.

Sherita says:

“Basically, the value introduces itself.”

---

Lesson 6 — Changing Values

To change a value, you must have permission.

Wrong:

entry main
    slot score assign 80
    permit read score

    score assign score + 10

    return score
end

Clarissa says:

“This fails.”

Why?

Because the program only said:

permit read score

But this line changes score:

score assign score + 10

Correct:

entry main
    slot score assign 80

    permit read score
    permit change score

    score assign score + 10

    return score
end

Sherita says:

“You cannot redecorate the room just because you were allowed to look inside.”

---

Lesson 7 — Permissions

Permissions define authority.

permit read data
permit change data
permit move packet
permit share buffer
permit expose result
permit enter zone
permit leave zone

You can also deny:

deny expose private_key

Clarissa says:

“Safety in Foresette is not vibes. It is authority.”

If code has permission, it may act.

If code does not have permission, compilation fails.

---

Lesson 8 — Dedicated Memory

Dedicated memory tells the compiler where values belong.

memory frame dedicated

slot width from frame assign 1920
slot height from frame assign 1080
slot pixels from frame assign width * height

Clarissa explains:

frame

is a dedicated memory region.

These slots belong to it:

width
height
pixels

Sherita says:

“This is like saying, ‘These supplies belong to this table.’ Nobody has to guess where they came from.”

---

Lesson 9 — Delegation

Delegation sends a value to another routine.

delegate image to render

With permission:

delegate image with read to inspect
delegate image with change to sharpen
delegate packet with move to consume
delegate buffer with share to broadcast

Clarissa says:

“Delegation is clearer than a vague function call. It tells the compiler what relationship the receiver has with the value.”

Example:

entry main
    slot frame assign 1

    permit read frame

    delegate frame with read to render

    return 0
end

Sherita says:

“Not just ‘here, take this.’ More like, ‘here, you may read this, and only read it.’”

---

Lesson 10 — Functions / Entries

Foresette uses "entry".

entry add
    slot a assign 10
    slot b assign 20
    slot sum assign a + b
    return sum
end

Main program:

program MathDemo

entry main
    slot result assign add()
    return result
end

entry add
    slot a assign 10
    slot b assign 20
    slot sum assign a + b
    return sum
end

Clarissa says:

“An entry is a named executable routine.”

---

Lesson 11 — Conditions

if score >= 90
    return "excellent"
else
    return "keep training"
end

Full example:

program GradeDemo

entry main
    slot score assign 95

    permit read score

    if score >= 90
        return "A"
    else
        return "Not A"
    end
end

Sherita says:

“Foresette conditions are straight arrows. If this, do that. Otherwise, do this.”

---

Lesson 12 — When

"when" responds to a condition or state.

when ready
    delegate frame to render
end

Example:

entry main
    slot ready assign true
    slot frame assign 1

    permit read ready
    permit read frame

    when ready
        delegate frame with read to render
    end

    return 0
end

Clarissa says:

“Use "if" for branching. Use "when" when something becoming true triggers action.”

---

Lesson 13 — Match and Case

match command
    case "start"
        return 1

    case "stop"
        return 0

    else
        return -1
end

Sherita says:

“This is like a menu. The program checks which option was chosen.”

---

Lesson 14 — Loops

Repeat

repeat 5
    delegate message to puts
end

While

while active
    delegate frame to render
end

For

for i from 0 to 10
    slot total assign total + i
end

Each

each enemy from enemies
    delegate enemy to update
end

Clarissa says:

“Loops repeat action. Foresette makes the kind of repeat visible.”

---

Lesson 15 — Break and Continue

while active
    if danger
        break
    else
        continue
    end
end

"break" exits the loop.

"continue" skips to the next loop cycle.

Sherita says:

“Break leaves the dance floor. Continue stays dancing but skips that move.”

---

Lesson 16 — Errors

Foresette errors are user-defined.

error InvalidScore
    slot value
    slot reason
end

Clarissa says:

“The language does not tell your program what failure means. You define failure.”

Examples:

error MissingFile
    slot path
end

error NetworkDown
    slot reason
end

error InvalidFrame
    slot reason
end

---

Lesson 17 — Manual Error Handling

attempt load_texture

handle MissingFile
    bypass
end

handle NetworkDown
    stop
end

"bypass" means do nothing and continue safely.

"stop" means terminate the route.

Clarissa says:

“Foresette has no invisible exception ghost flying through the program. If failure exists, you put it on the map.”

Sherita whispers:

“No ghost exceptions. We love peace.”

---

Lesson 18 — Routes

Routes define execution direction.

route startup to load_assets
route load_assets to main_loop
route main_loop to shutdown

Clarissa says:

“Routes are strategic control lines. They help the program’s major movement stay visible.”

---

Lesson 19 — Parallelism

Parallelism means doing independent work at the same time.

parallel
    delegate left_half to render_left
    delegate right_half to render_right
end

Clarissa asks:

“Can these two tasks safely happen together?”

The class answers:

“Yes, if they do not illegally share or change the same data.”

Sherita says:

“Parallelism is not ‘everybody run around screaming.’ It is organized teamwork.”

---

Lesson 20 — Concurrency

Concurrency means multiple paths progress independently.

concurrent
    path network
        wait packet_ready
        delegate packet to process_packet
    end

    path audio
        delegate sound to mix_audio
    end

    path input
        delegate controller to read_input
    end
end

Clarissa explains:

“Parallelism is simultaneous work. Concurrency is independent progress.”

Sherita adds:

“Parallel is three students solving problems at once. Concurrent is three clubs running different activities during the same school day.”

---

Lesson 21 — Sync, Wait, Signal

signal packet_ready
wait packet_ready
sync buffer

"signal" announces.

"wait" pauses until something is ready.

"sync" coordinates shared access.

Example:

concurrent
    path network
        signal packet_ready
    end

    path game
        wait packet_ready
        sync packets
        delegate packets with change to process
    end
end

Clarissa says:

“No hidden race conditions. If paths share, they must coordinate.”

---

Lesson 22 — Lock and Unlock

lock buffer
buffer assign buffer + 1
unlock buffer

Locks protect shared mutation.

Correct pattern:

permit share buffer
permit change buffer

lock buffer
buffer assign buffer + 1
unlock buffer

Sherita says:

“Lock the locker before ten people try to grab the same notebook.”

---

Lesson 23 — Imports and Exports

import math
import engine.render

export main
export render_frame

"import" brings in known modules.

"export" exposes routines.

Clarissa says:

“Imports and exports make large programs organized.”

---

Lesson 24 — External and Native

Foresette can talk to native code.

external puts
native c

Example:

program NativePrint

external puts
native c

entry main
    slot message assign "Native call from Foresette."
    delegate message to puts
    return 0
end

Sherita says:

“This is how Foresette shakes hands with C.”

---

Lesson 25 — Full Beginner Program

program StudentScore

external puts
native c

error InvalidScore
    slot reason
end

entry main
    slot score assign 95
    slot message assign "Score accepted."

    permit read score
    permit read message

    if score > 100
        handle InvalidScore
            slot reason assign "Score is too high."
            delegate reason to puts
            stop
        end
    else
        delegate message to puts
        return score
    end
end

Clarissa says:

“This program uses slots, assignments, permissions, errors, handling, delegation, external native interop, and return.”

Sherita says:

“Look at y’all. Writing native-strategy code like tiny engine goblins.”

---

Lesson 26 — Full Memory Program

program FrameMath

entry main
    memory frame dedicated

    slot width from frame assign 1920
    slot height from frame assign 1080
    slot pixels from frame assign width * height

    permit read width
    permit read height
    permit read pixels

    return pixels
end

Clarissa asks:

“What does the compiler know?”

The class answers:

width belongs to frame
height belongs to frame
pixels belongs to frame
pixels depends on width and height
pixels may be read

Clarissa smiles.

“Exactly.”

---

Lesson 27 — Full Parallel Program

program ParallelDemo

entry main
    memory frame dedicated

    slot left from frame assign 1
    slot right from frame assign 2

    permit read left
    permit read right

    parallel
        delegate left with read to render_left
        delegate right with read to render_right
    end

    return 0
end

Clarissa says:

“This is safe because left and right are separate readable values.”

Sherita adds:

“If both tried to change the same slot without sync, the compiler would throw the red flag.”

---

Lesson 28 — Full Concurrent Program

program EnginePaths

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

Clarissa says:

“Each path is visible. Nothing secretly runs in the background.”

---

Lesson 29 — How Foresette Compiles

Clarissa draws the pipeline:

.4se source
    ↓
tokens
    ↓
AST
    ↓
semantic graph
    ↓
permission verification
    ↓
memory verification
    ↓
delegation verification
    ↓
LLVM IR
    ↓
LLVM optimization
    ↓
native machine code

Sherita says:

“The compiler is not doing detective work. It is doing construction work.”

Clarissa nods.

“Exactly.”

---

Lesson 30 — Tokens

A token is a meaningful piece of code.

This line:

slot score assign 90

becomes:

TOKEN_SLOT
IDENTIFIER(score)
TOKEN_ASSIGN
INTEGER(90)

Clarissa says:

“The lexer turns text into recognizable pieces.”

---

Lesson 31 — AST

The parser turns tokens into a tree.

Source:

slot pixels from frame assign width * height

AST:

SlotDeclNode
    name: pixels
    memory: frame
    value:
        BinaryExprNode *
            left: IdentifierNode width
            right: IdentifierNode height

Sherita says:

“The AST is the code’s skeleton.”

---

Lesson 32 — LLVM Lowering

Clarissa writes:

slot x assign 10

Possible LLVM-style idea:

x = 10

If it needs memory:

allocate x
store 10 into x

If it does not need memory:

keep x in register

If it is constant and obvious:

replace x with 10

Clarissa says:

“Foresette gives LLVM clean information. LLVM makes it fast.”

---

Lesson 33 — Optimization

Foresette helps optimization because it is explicit.

The compiler can remove:

dead slots
unused paths
impossible errors
unneeded storage
duplicate calculations
unnecessary branches

It can improve:

register use
inlining
loop unrolling
vectorization
parallel scheduling
memory layout

Sherita says:

“Clean code gives the optimizer a runway. Messy code gives it a swamp.”

---

Lesson 34 — Final Class Project

Clarissa says:

“Now we build a small image pipeline.”

The final program:

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

Clarissa asks:

“What did we use?”

The class answers:

program
external
native
error
entry
memory
dedicated
slot
from
assign
permit
read
change
share
if
handle
delegate
to
stop
else
parallel
concurrent
path
signal
wait
return
end

Sherita says:

“That’s not just a program. That’s a full execution strategy.”

---

Lesson 35 — Best Foresette Habits

Clarissa writes the final rules on the board:

Use slots for meaningful values.
Use dedicated memory when values belong together.
Grant the smallest permission needed.
Never share mutable data casually.
Delegate with clear intent.
Define errors manually.
Handle errors visibly.
Use parallel only for independent work.
Use concurrent paths only when architecture requires them.
Synchronize shared paths.
Keep native boundaries explicit.
Let LLVM optimize clean structure.

Sherita adds:

“And do not make the compiler guess. The compiler is not your group project partner who has to read your mind.”

---

Final Exam Review

What is Foresette?

A deterministic native programming language.

What is a slot?

A named computational position.

What is assignment?

The value contract.

What is dedicated memory?

A declared memory relationship.

What are permissions?

Authority to read, change, move, share, expose, enter, or leave.

What is delegation?

Explicitly sending a value to a routine with a known relationship.

What are user-defined errors?

Failures created by the programmer.

What is manual error handling?

The programmer defines what happens when failure occurs.

What is parallelism?

Declared simultaneous independent work.

What is concurrency?

Declared independent execution paths.

What is zero-guess compilation?

The programmer states the strategy so the compiler does not invent intent.

---

Closing Scene

The bell is almost about to ring.

Clarissa looks around the room.

“At the beginning, Foresette probably looked strict. But now you should see what it really is. It is not strict because it wants to slow you down. It is strict because it wants your program to be clear enough to become fast.”

Sherita closes the laptop.

“Basically, Foresette says: say what you mean, mean what you say, and let the machine eat.”

The students laugh.

Clarissa smiles.

“Exactly. Class dismissed.”

On the screen, the final line remains:

The strategy is explicit.
The path is clear.
The execution is native.



## --- ##



Foresette Academy — Class Two

Execution Thinking, Permission Tracing, and Building a Realtime Engine

Instructor: Clarissa Taylor
Assistant Instructor: Sherita Pleasant

---

8:57 A.M. — Before Class

Three students are already arguing.

“I still think "permit change" is annoying.”

“No, you forgot it four times.”

“That's why it's annoying.”

Sherita Pleasant is sitting on the edge of Clarissa's desk, slowly eating a breakfast bar.

She looks toward the students.

“So your complaint is that the compiler caught the exact mistake you kept making?”

The student freezes.

Sherita nods.

“Mmm-hmm.”

Clarissa Taylor walks into the classroom carrying a laptop and a thin stack of papers.

“Good morning.”

“Morning, Ms. Taylor.”

Clarissa sets the laptop down.

“Yesterday, you learned Foresette syntax.”

She turns toward the board.

“Today, we're going to learn something harder.”

She writes:

THINK LIKE EXECUTION

The room becomes quieter.

Clarissa turns around.

“A programmer reads code.”

She taps the board.

“A Foresette programmer sees the machine moving.”

Sherita raises her breakfast bar.

“That's today's whole sermon.”

---

Lesson 1 — Stop Reading Code Like English

Clarissa places a program on the screen.

program Counter

entry main
    slot score assign 10

    permit read score
    permit change score

    score assign score + 5

    return score
end

“What happens?”

A student answers.

“Score becomes fifteen.”

Clarissa shakes her head.

“Too fast.”

The student looks confused.

“But it does.”

“It does. But I asked what happens.”

Clarissa points to the first line.

slot score assign 10

“A computational position named "score" is established.”

She moves downward.

permit read score

“Read authority is established.”

permit change score

“Mutation authority is established.”

score assign score + 5

“The current value is read. Five is added. A new assignment is established.”

return score

“The current assigned value leaves the entry.”

Clarissa faces the class.

“Now tell me what happens.”

The student tries again.

“A slot is established with ten. The program gains read and change authority. The slot is read, five is added, fifteen becomes the new assignment, and fifteen returns.”

Clarissa smiles.

“Now you're reading Foresette.”

Sherita points at him.

“Congratulations. You have temporarily become a compiler.”

---

Lesson 2 — The Five Questions

Clarissa writes five questions.

1. What exists?
2. Where does it belong?
3. Who may touch it?
4. Where does it go?
5. What can stop it?

“These five questions will let you understand almost any Foresette program.”

She displays:

memory engine dedicated

slot frame from engine assign 0

permit read frame
permit change frame

delegate frame with change to render

Clarissa asks:

“What exists?”

“Frame.”

“Where does it belong?”

“Engine.”

“Who may touch it?”

“It can be read and changed.”

“Where does it go?”

“Render.”

“What can stop it?”

A student pauses.

“No error is defined.”

Clarissa nods.

“Excellent.”

Sherita squints at the screen.

“So right now, "render" better behave itself.”

---

Lesson 3 — Permission Tracing

Clarissa draws this:

frame
  |
  +-- read
  |
  +-- change
  |
  X-- expose

“This is a permission graph.”

Source:

slot frame assign 1

permit read frame
permit change frame
deny expose frame

Clarissa continues:

“Now watch.”

delegate frame with read to inspect

“Legal?”

“Yes.”

delegate frame with change to sharpen

“Legal?”

“Yes.”

delegate frame with expose to external_device

“Legal?”

“No.”

“Why?”

“Expose is denied.”

Clarissa nods.

“The compiler does not debate this.”

She writes:

DENIED > REQUESTED

“The source already answered the question.”

---

Lesson 4 — Permission Failure Lab

Clarissa hands out the first exercise.

program Broken

entry main
    slot energy assign 100

    permit read energy

    energy assign energy - 10

    return energy
end

“Find the problem.”

Almost every hand rises.

Sherita looks impressed.

“Oh, now everybody sees it.”

A student answers.

“"energy" is changed, but it only has read permission.”

“Correct.”

Fix:

program Fixed

entry main
    slot energy assign 100

    permit read energy
    permit change energy

    energy assign energy - 10

    return energy
end

Clarissa says:

“This is not a runtime crash.”

She taps the screen.

“This program never becomes a binary until the authority problem is fixed.”

---

Lesson 5 — Assignment Is Not a Box

Clarissa writes:

slot speed assign 10

“What is "speed"?”

“A variable?”

Clarissa tilts her head.

Sherita immediately says:

“Dangerous answer.”

The class laughs.

Clarissa says:

“"speed" is a slot.”

She writes:

slot speed assign 10

Then:

speed assign speed + 5

Then:

return speed

“The slot describes a computational position.”

She draws:

speed₀ = 10
speed₁ = speed₀ + 5
return speed₁

Clarissa explains:

“LLVM may convert your assignments into Static Single Assignment form.”

She writes:

%speed.0 = 10
%speed.1 = add %speed.0, 5

“The physical machine does not necessarily maintain a little box named "speed".”

Sherita says:

“Sometimes the box was imaginary the entire time.”

A student says:

“That's creepy.”

“Welcome to compiler engineering,” Sherita replies.

---

Lesson 6 — When Slots Disappear

Clarissa displays:

entry main
    slot a assign 10
    slot b assign 20
    slot result assign a + b

    return result
end

“What might LLVM produce?”

A student guesses.

“Add ten and twenty?”

“Maybe.”

Clarissa changes the screen.

return 30

Several students blink.

Sherita grins.

“Your beautiful little slots got vaporized.”

Clarissa explains:

“The compiler can prove the result.”

10 + 20 = 30

Therefore:

a
b
result

may never physically exist.

This is constant folding.

Clarissa writes:

SEMANTIC EXISTENCE
≠
PHYSICAL STORAGE

“Slots exist in the program's meaning.”

“They only receive physical storage when necessary.”

---

Lesson 7 — Dedicated Memory Is a Relationship

Clarissa displays:

memory player dedicated

slot health from player assign 100
slot stamina from player assign 100
slot speed from player assign 12

“Does this mean Foresette immediately calls "malloc"?”

“No.”

“Correct.”

Dedicated memory means:

health belongs to player
stamina belongs to player
speed belongs to player

The compiler now understands their memory relationship.

Clarissa continues.

“If "player" never escapes "main", the compiler may use stack storage.”

“If values remain temporary, they may stay in registers.”

“If the entire structure can be dissolved, it may disappear.”

Sherita says:

“Dedicated memory tells the compiler the family tree. It does not order furniture from IKEA.”

---

Lesson 8 — Building a Player

Clarissa types:

program PlayerDemo

entry main
    memory player dedicated

    slot health from player assign 100
    slot stamina from player assign 100
    slot speed from player assign 12

    permit read health
    permit change health

    permit read stamina
    permit change stamina

    permit read speed

    return health
end

“Now we have a player state.”

A student asks:

“Where are classes?”

Clarissa smiles.

“We don't need one yet.”

“Objects?”

“Don't need one yet.”

“Inheritance?”

“Still don't need it.”

Sherita leans toward the student.

“She's gonna make you earn every abstraction.”

Clarissa says:

“Foresette starts with the actual computational relationship.”

player memory
    health
    stamina
    speed

“If a higher structure becomes useful, the language architecture builds from explicit relationships.”

---

Lesson 9 — Damage

Clarissa adds:

entry damage
    slot amount assign 20
    return amount
end

Then:

entry main
    memory player dedicated

    slot health from player assign 100

    permit read health
    permit change health

    slot damage_value assign damage()

    health assign health - damage_value

    return health
end

“What returns?”

“Eighty.”

Clarissa nods.

“Trace it.”

The class responds:

health = 100
damage_value = 20
health = 100 - 20
health = 80
return 80

Sherita says:

“You're getting suspiciously competent.”

---

Lesson 10 — Delegation Versus Calling

Clarissa writes:

damage()

Then:

delegate player with change to apply_damage

“These communicate different things.”

A call says:

execute this routine

Delegation says:

this value crosses this boundary
with this authority
for this operation

Clarissa circles:

with change

“The compiler knows "apply_damage" receives mutation authority.”

Example:

delegate health with change to apply_damage

Now the semantic graph contains:

main
  |
  +-- health
        |
        +-- change authority
        |
        +--> apply_damage

Sherita says:

“Delegation leaves footprints.”

---

Lesson 11 — Move Permission

Clarissa types:

slot packet assign network_packet

permit move packet

delegate packet with move to consume

“What does "move" mean?”

A student answers.

“Consume gets it.”

“And the caller?”

“Shouldn't use it anymore.”

“Correct.”

After:

delegate packet with move to consume

this is invalid:

delegate packet with read to inspect

Clarissa explains:

“The packet's authority was transferred.”

Sherita says:

“You gave away the pizza. Stop trying to eat the pizza.”

---

Lesson 12 — Sharing Is Serious

Clarissa writes:

slot buffer assign data

permit share buffer

“Sharing means multiple execution paths may access the relationship.”

Then:

concurrent
    path one
        delegate buffer with share to worker_one
    end

    path two
        delegate buffer with share to worker_two
    end
end

Clarissa asks:

“What if both workers change "buffer"?”

“Race condition.”

“Exactly.”

So Foresette requires explicit coordination.

sync buffer

or:

lock buffer
buffer assign buffer + 1
unlock buffer

Clarissa writes:

SHARED + MUTABLE = COORDINATE

Sherita says:

“Put that on a T-shirt.”

---

Lesson 13 — Race Condition Demonstration

Broken:

program Race

entry main
    slot counter assign 0

    permit share counter
    permit change counter

    concurrent
        path one
            counter assign counter + 1
        end

        path two
            counter assign counter + 1
        end
    end

    return counter
end

Clarissa says:

“This is rejected.”

Why?

Two paths mutate shared state without synchronization.

Fixed:

program SafeCounter

entry main
    slot counter assign 0

    permit share counter
    permit change counter

    concurrent
        path one
            lock counter
            counter assign counter + 1
            unlock counter
        end

        path two
            lock counter
            counter assign counter + 1
            unlock counter
        end
    end

    return counter
end

Sherita says:

“The compiler saw the fight before it happened.”

---

Lesson 14 — Parallel or Concurrent?

Clarissa draws two diagrams.

PARALLEL

TASK A ────────►
TASK B ────────►
TASK C ────────►

Then:

CONCURRENT

NETWORK ─────────────►
AUDIO   ───────────────────►
INPUT   ───────►

“Parallelism asks whether work can happen simultaneously.”

“Concurrency describes independently progressing paths.”

Example parallel work:

parallel
    delegate left with read to scan_left
    delegate right with read to scan_right
end

Example concurrency:

concurrent
    path network
        ...
    end

    path audio
        ...
    end
end

Sherita says:

“Parallel is splitting homework between three people.”

“Concurrency is doing homework while your laundry runs and your food cooks.”

A student says:

“That sounds dangerous.”

Sherita nods.

“Depends on your cooking.”

---

Lesson 15 — Errors Are Part of Architecture

Clarissa writes:

error PlayerDead
    slot health
end

Then:

if health <= 0
    handle PlayerDead
        stop
    end
end

She turns around.

“What's wrong with thinking of errors as accidents?”

A student says:

“Some failures are expected.”

“Exactly.”

A file can be missing.

A network can disconnect.

A player can reach zero health.

A device can stop responding.

Clarissa writes:

EXPECTED FAILURE
IS PROGRAM STRUCTURE

“Foresette makes failure visible.”

---

Lesson 16 — Bypass

Clarissa displays:

handle MissingTexture
    bypass
end

“What happens?”

“The program continues.”

“Yes.”

Maybe the engine uses a fallback.

Maybe the texture is optional.

Maybe the missing resource does not matter.

Clarissa says:

“"bypass" is not accidental ignorance.”

“It is explicit non-action.”

Sherita says:

“Foresette lets you say, ‘Yep, saw it. Moving on.’”

---

Lesson 17 — Route Thinking

Clarissa places this on screen:

route startup to load
route load to game
route game to shutdown

She draws:

STARTUP
   |
   v
 LOAD
   |
   v
 GAME
   |
   v
SHUTDOWN

“A route expresses major execution direction.”

Now:

error LoadFailure

Clarissa adds:

LOAD
 | \
 |  \
 v   v
GAME ERROR

“Your program is a graph.”

Sherita says:

“Code is less scary when you stop imagining a giant wall of text.”

---

Lesson 18 — Building the Realtime Engine

Clarissa turns off the classroom lights.

The projector displays:

CLASS PROJECT
FORESETTE MINI ENGINE

Several students sit forward.

Sherita smiles.

“Here we go.”

Clarissa begins.

program MiniEngine

external puts
native c

error EngineFailure
    slot reason
end

entry main
    memory engine dedicated
    memory player dedicated
    memory frame dedicated

    slot running from engine assign true
    slot frame_count from engine assign 0

    slot health from player assign 100
    slot stamina from player assign 100

    slot width from frame assign 1280
    slot height from frame assign 720
    slot pixels from frame assign width * height

    permit read running
    permit change running

    permit read frame_count
    permit change frame_count

    permit read health
    permit change health

    permit read stamina
    permit change stamina

    permit read pixels
    permit share pixels

    route startup to engine_loop

    while running
        parallel
            delegate pixels with read to render_frame
            delegate health with read to update_hud
            delegate stamina with read to update_stamina
        end

        concurrent
            path input
                wait input_ready
                delegate running with change to process_input
            end

            path audio
                wait frame_ready
                signal audio_ready
            end
        end

        frame_count assign frame_count + 1

        if health <= 0
            handle EngineFailure
                slot reason assign "Player health exhausted."
                delegate reason to puts
                stop
            end
        end
    end

    route engine_loop to shutdown

    return 0
end

The room is silent.

Clarissa says:

“Don't panic.”

Sherita says:

“Some of you definitely panicked.”

A few students laugh.

Clarissa points to the top.

“We use the five questions.”

---

Lesson 19 — Trace the Engine

What exists?

running
frame_count
health
stamina
width
height
pixels

Where does it belong?

engine
    running
    frame_count

player
    health
    stamina

frame
    width
    height
    pixels

Who may touch it?

running
    read
    change

frame_count
    read
    change

health
    read
    change

stamina
    read
    change

pixels
    read
    share

Where does it go?

pixels -> render_frame
health -> update_hud
stamina -> update_stamina
running -> process_input

What can stop it?

EngineFailure

Clarissa turns toward the class.

“Now is the program scary?”

“No.”

Sherita points at them.

“Yesterday y'all were scared of "permit change".”

---

Lesson 20 — Find the Engine Bug

Clarissa says:

“There is a problem.”

The class scans the program.

Thirty seconds.

A hand rises.

“"health" is read inside the loop, but okay, it has read permission.”

Another student squints.

“Pixels are shared.”

“Yes.”

Another student says:

“"running" is changed inside the input path.”

Clarissa nods.

“And?”

“It isn't shared.”

Clarissa smiles.

“There it is.”

The concurrent input path receives:

running with change

But "running" crosses into a concurrent path.

The program needs:

permit share running

and appropriate synchronization.

Corrected:

permit read running
permit change running
permit share running

Input path:

path input
    wait input_ready

    lock running
    delegate running with change to process_input
    unlock running
end

Sherita looks around.

“You found a concurrency bug in a realtime engine.”

She nods slowly.

“Okay. That's actually pretty cool.”

---

Lesson 21 — Compiler View

Clarissa shows the compiler pipeline.

MiniEngine.4se
       |
       v
LEXER
       |
       v
TOKENS
       |
       v
PARSER
       |
       v
AST
       |
       v
SEMANTIC GRAPH
       |
       +--> SLOT TABLE
       |
       +--> MEMORY TABLE
       |
       +--> PERMISSION TABLE
       |
       +--> DELEGATION TABLE
       |
       +--> EXECUTION TABLE
       |
       v
VERIFICATION
       |
       v
LLVM IR
       |
       v
OPTIMIZATION
       |
       v
NATIVE CODE

“The Foresette compiler sees far more than words.”

It sees:

running:
    memory = engine
    readable = yes
    mutable = yes
    shared = yes

pixels:
    memory = frame
    readable = yes
    mutable = no
    shared = yes

Sherita says:

“The compiler has a spreadsheet on everybody.”

---

Lesson 22 — What LLVM Does

Clarissa writes:

slot width assign 1280
slot height assign 720
slot pixels assign width * height

LLVM may determine:

1280 * 720 = 921600

The generated program may simply contain:

921600

No multiplication at runtime.

No width slot.

No height slot.

Possibly no pixels slot.

Clarissa says:

“Foresette gives LLVM facts.”

“LLVM removes unnecessary work.”

Sherita says:

“The fastest instruction is the one you never execute.”

Clarissa pauses.

“Exactly.”

Sherita looks surprised.

“Wait, I sounded official.”

---

Lesson 23 — Class Challenge

Clarissa writes:

program Drone

entry main
    memory drone dedicated

    slot altitude from drone assign 100
    slot power from drone assign 80

    permit read altitude
    permit read power

    altitude assign altitude + 10

    parallel
        delegate altitude with read to navigation
        delegate power with change to battery
    end

    return altitude
end

“Find every problem.”

The class studies it.

Problem one:

altitude assign altitude + 10

requires:

permit change altitude

Problem two:

delegate power with change to battery

requires:

permit change power

Correct:

program Drone

entry main
    memory drone dedicated

    slot altitude from drone assign 100
    slot power from drone assign 80

    permit read altitude
    permit change altitude

    permit read power
    permit change power

    altitude assign altitude + 10

    parallel
        delegate altitude with read to navigation
        delegate power with change to battery
    end

    return altitude
end

Clarissa nods.

“Good.”

---

Homework — Build a Smart Locker

Clarissa puts the assignment on screen.

SMART LOCKER

Requirements:

memory locker dedicated

slot locked
slot code
slot attempts

permissions for:
    read
    change

error:
    InvalidCode

three attempts maximum

when correct:
    unlock locker

when incorrect:
    increase attempts

after three failures:
    stop

Sherita says:

“And before somebody asks — no, "unlock locker" does not mean Foresette is magically controlling your school locker.”

A student raises his hand.

“I was actually going to ask that.”

“I know,” Sherita says.

---

End of Class

The bell rings.

Nobody immediately stands.

Clarissa closes the compiler window.

“Yesterday, you learned the language.”

She looks around the room.

“Today, you learned to trace authority, memory, and execution.”

She points to the five questions still written on the board.

What exists?

Where does it belong?

Who may touch it?

Where does it go?

What can stop it?

“If you can answer those questions, you can understand a Foresette program.”

Sherita grabs her laptop.

“And if you can't answer them…”

She pauses.

“Do not add twelve concurrent paths and hope for spiritual guidance.”

The class erupts laughing.

Clarissa tries not to smile.

“Class dismissed.”

As the students leave, the projector still shows:

FORESETTE

Clear intent.
Verified authority.
Visible execution.
Native speed.



## --- ##



Foresette Academy — Class Three

Collections, Layout, and the First Game Loop

Instructor: Clarissa Taylor
Assistant Instructor: Sherita Pleasant

---

8:58 A.M. — The Homework Stack

Sherita Pleasant walks in carrying a folder labeled:

SMART LOCKER HOMEWORK

She places it on Clarissa Taylor’s desk.

Clarissa looks at the folder.

“Any disasters?”

Sherita opens it.

“One student gave the locker "permit expose code".”

The entire class gasps.

Clarissa slowly turns toward them.

“Who exposed the locker code?”

A student sinks into his chair.

Sherita points gently.

“We’re not mad. We are deeply concerned.”

Clarissa writes on the board:

deny expose code

She turns around.

“Today’s first lesson just wrote itself.”

---

Lesson 1 — Smart Locker Review

Clarissa projects a strong version of the homework.

program SmartLocker

external puts
native c

error InvalidCode
    slot reason
end

entry main
    memory locker dedicated

    slot locked from locker assign true
    slot code from locker assign 2468
    slot entered from locker assign 2468
    slot attempts from locker assign 0

    permit read locked
    permit change locked

    permit read code
    deny expose code

    permit read entered
    permit change entered

    permit read attempts
    permit change attempts

    if entered == code
        locked assign false
        return 0
    else
        attempts assign attempts + 1

        if attempts >= 3
            handle InvalidCode
                slot reason assign "Too many failed attempts."
                delegate reason to puts
                stop
            end
        else
            bypass
        end
    end
end

Clarissa says:

“This is good Foresette.”

Sherita nods.

“It protects the secret code, tracks attempts, and does not randomly trust the universe.”

---

Lesson 2 — Why "deny expose code" Matters

Clarissa writes:

permit read code
deny expose code

She explains:

“Reading a value inside the program is different from exposing it outside the program.”

This is allowed:

if entered == code
    locked assign false
end

This is rejected:

delegate code to puts

Why?

Because:

deny expose code

Sherita says:

“You may check the password. You may not shout the password into the hallway.”

---

Lesson 3 — Collections Begin

Clarissa changes the projector.

COLLECTIONS

She says:

“Today we add groups of values.”

Foresette supports collection assignments through list expressions.

slot scores assign [90, 85, 100]
slot names assign ["Maya", "Luis", "Tasha"]
slot flags assign [true, false, true]

Sherita says:

“A collection is just the language saying, ‘These values travel together.’”

Clarissa adds:

“But Foresette still wants clarity.”

---

Lesson 4 — Lists Are Assigned Contracts

slot scores assign [90, 85, 100]

This tells the compiler:

scores is a collection of numeric values

The assignment establishes the contract.

Clarissa writes:

slot mixed assign [90, "hello", true]

She pauses.

“This is rejected in normal Foresette collection mode.”

A student asks:

“Why?”

Clarissa answers:

“Because a zero-guess compiler does not want to wonder what kind of collection this is.”

Sherita says:

“If your list has a number, a sandwich, and a ghost in it, the compiler files a complaint.”

---

Lesson 5 — Reading From a Collection

Clarissa writes:

slot scores assign [90, 85, 100]

permit read scores

slot first assign scores[0]
slot second assign scores[1]
slot third assign scores[2]

Indexes begin at zero.

scores[0] = 90
scores[1] = 85
scores[2] = 100

Sherita says:

“Computers count from zero because apparently one was too emotionally available.”

---

Lesson 6 — Changing a Collection Element

Wrong:

slot scores assign [90, 85, 100]

permit read scores

scores[1] assign 95

Clarissa asks:

“What’s missing?”

The class answers:

permit change scores

Correct:

slot scores assign [90, 85, 100]

permit read scores
permit change scores

scores[1] assign 95

Clarissa says:

“The collection is still protected by authority.”

---

Lesson 7 — Each Loops

each score from scores
    delegate score with read to print_score
end

Clarissa explains:

“"each" walks through a collection.”

Full example:

program ScoreList

entry main
    slot scores assign [90, 85, 100]

    permit read scores

    each score from scores
        delegate score with read to inspect_score
    end

    return 0
end

Sherita says:

“This is the polite loop. It says: one at a time, please.”

---

Lesson 8 — For Loops With Indexes

for i from 0 to 3
    slot score assign scores[i]
end

Clarissa says:

“Use "for" when the index matters.”

Example:

entry main
    slot scores assign [90, 85, 100]
    slot total assign 0

    permit read scores
    permit read total
    permit change total

    for i from 0 to 3
        total assign total + scores[i]
    end

    return total
end

The result:

275

Sherita says:

“That is not a grade average. That is three grades standing on each other’s shoulders.”

---

Lesson 9 — Average Score

Clarissa extends it.

program AverageScore

entry main
    slot scores assign [90, 85, 100]
    slot total assign 0
    slot count assign 3

    permit read scores
    permit read total
    permit change total
    permit read count

    for i from 0 to count
        total assign total + scores[i]
    end

    slot average assign total / count

    return average
end

Clarissa says:

“Notice: "average" does not need change permission because we assign it once and return it.”

Sherita adds:

“But if you modify it later, the permission goblin returns.”

---

Lesson 10 — Collection Layout

Clarissa draws:

scores
 ├─ [0] 90
 ├─ [1] 85
 └─ [2] 100

Then:

memory class_data dedicated

slot scores from class_data assign [90, 85, 100]

Now the compiler knows:

scores belongs to class_data
scores contains three numeric values
scores may be laid out contiguously
scores can be indexed
scores has known length

Clarissa says:

“When Foresette knows collection shape, LLVM has optimization opportunities.”

Such as:

bounds verification
vectorization
loop unrolling
constant folding
dead value removal

Sherita says:

“Give the compiler a neat shelf, and it stops dropping cans on its foot.”

---

Lesson 11 — Bounds Safety

Clarissa writes:

slot scores assign [90, 85, 100]
slot bad assign scores[5]

The class groans.

Clarissa nods.

“Rejected.”

The compiler knows:

valid indexes: 0, 1, 2
invalid index: 5

Foresette rejects obvious out-of-bounds access.

If index is runtime-calculated, Foresette requires a visible guard.

if i < 3
    slot value assign scores[i]
else
    bypass
end

Sherita says:

“The compiler is not letting you dive into the empty end of the pool.”

---

Lesson 12 — Player Inventory

Clarissa says:

“Let’s make a small game-style inventory.”

program InventoryDemo

entry main
    memory player dedicated

    slot inventory from player assign ["key", "coin", "map"]

    permit read inventory
    permit change inventory

    inventory[1] assign "gem"

    return 0
end

Before:

["key", "coin", "map"]

After:

["key", "gem", "map"]

Sherita says:

“Congratulations, the coin evolved.”

---

Lesson 13 — Game State Memory

Clarissa writes:

memory game dedicated
memory player dedicated
memory enemy dedicated

Then:

slot running from game assign true
slot frame from game assign 0

slot player_health from player assign 100
slot player_x from player assign 10
slot player_y from player assign 5

slot enemy_health from enemy assign 50
slot enemy_x from enemy assign 20
slot enemy_y from enemy assign 5

Clarissa says:

“Now our game has structure without needing objects yet.”

Sherita says:

“It’s not anti-object. It’s pre-object. Like soup before noodles.”

---

Lesson 14 — Permissions for Game State

permit read running
permit change running

permit read frame
permit change frame

permit read player_health
permit change player_health

permit read player_x
permit change player_x

permit read enemy_health
permit change enemy_health

permit read enemy_x
permit change enemy_x

Clarissa says:

“Yes, this looks careful.”

Sherita says:

“Careful is cheaper than debugging at 2 A.M.”

---

Lesson 15 — Collision Check

Clarissa writes:

if player_x == enemy_x
    player_health assign player_health - 10
end

A student asks:

“What about y?”

Clarissa smiles.

“Good catch.”

Correct:

if player_x == enemy_x
    if player_y == enemy_y
        player_health assign player_health - 10
    end
end

Sherita says:

“If you only check X, then everyone on the same street gets punched.”

---

Lesson 16 — Cleaner Collision With Match-Like Thinking

Clarissa says:

“We can also define a collision flag.”

slot collided assign false

permit read collided
permit change collided

if player_x == enemy_x
    if player_y == enemy_y
        collided assign true
    end
end

when collided
    player_health assign player_health - 10
end

Clarissa says:

“This separates detection from response.”

Sherita says:

“First: did they bump? Second: okay, now drama.”

---

Lesson 17 — First Game Loop

Clarissa turns the projector dark.

Then types:

program TinyGame

external puts
native c

error PlayerDefeated
    slot reason
end

entry main
    memory game dedicated
    memory player dedicated
    memory enemy dedicated

    slot running from game assign true
    slot frame from game assign 0

    slot player_health from player assign 100
    slot player_x from player assign 10
    slot player_y from player assign 5

    slot enemy_health from enemy assign 50
    slot enemy_x from enemy assign 20
    slot enemy_y from enemy assign 5

    permit read running
    permit change running

    permit read frame
    permit change frame

    permit read player_health
    permit change player_health

    permit read player_x
    permit change player_x

    permit read player_y
    permit change player_y

    permit read enemy_health
    permit change enemy_health

    permit read enemy_x
    permit change enemy_x

    permit read enemy_y
    permit change enemy_y

    while running
        frame assign frame + 1

        player_x assign player_x + 1

        if player_x == enemy_x
            if player_y == enemy_y
                player_health assign player_health - 10
            end
        end

        if player_health <= 0
            handle PlayerDefeated
                slot reason assign "Player defeated."
                delegate reason to puts
                stop
            end
        end

        if frame >= 60
            running assign false
        end
    end

    return 0
end

The students stare.

Clarissa says:

“This is a game loop.”

Sherita nods.

“Tiny, but alive.”

---

Lesson 18 — Trace the Game

Initial values:

frame = 0
player_health = 100
player_x = 10
player_y = 5
enemy_x = 20
enemy_y = 5

Each loop:

frame increases
player_x increases
collision is checked
health may decrease
defeat may stop program
frame 60 ends loop

Clarissa asks:

“When does collision happen?”

The class calculates.

Player starts at:

10

Enemy is at:

20

Player moves by:

+1 per frame

Collision X happens after 10 moves.

Y is already equal:

5 == 5

So health drops at that moment.

Sherita says:

“Math just punched the player.”

---

Lesson 19 — Add Parallel Rendering

Clarissa adds:

parallel
    delegate player_health with read to draw_hud
    delegate player_x with read to draw_player
    delegate enemy_x with read to draw_enemy
end

Inside the loop:

while running
    frame assign frame + 1

    parallel
        delegate player_health with read to draw_hud
        delegate player_x with read to draw_player
        delegate enemy_x with read to draw_enemy
    end

    player_x assign player_x + 1

    ...
end

Clarissa says:

“This is safe because rendering reads values.”

Sherita says:

“Read-only parallel work is the chillest kind.”

---

Lesson 20 — Add Concurrent Input

concurrent
    path input
        wait input_ready

        lock running
        delegate running with change to process_input
        unlock running
    end
end

Required permissions:

permit share running
permit change running

Clarissa says:

“Because "running" crosses into a concurrent path, it must be shareable.”

Sherita says:

“Concurrency means your variables need passports.”

---

Lesson 21 — Final Class Three Game

program TinyGameFinal

external puts
native c

error PlayerDefeated
    slot reason
end

entry main
    memory game dedicated
    memory player dedicated
    memory enemy dedicated

    slot running from game assign true
    slot frame from game assign 0

    slot player_health from player assign 100
    slot player_x from player assign 10
    slot player_y from player assign 5

    slot enemy_health from enemy assign 50
    slot enemy_x from enemy assign 20
    slot enemy_y from enemy assign 5

    permit read running
    permit change running
    permit share running

    permit read frame
    permit change frame

    permit read player_health
    permit change player_health

    permit read player_x
    permit change player_x

    permit read player_y
    permit change player_y

    permit read enemy_health
    permit change enemy_health

    permit read enemy_x
    permit change enemy_x

    permit read enemy_y
    permit change enemy_y

    while running
        frame assign frame + 1

        parallel
            delegate player_health with read to draw_hud
            delegate player_x with read to draw_player
            delegate enemy_x with read to draw_enemy
        end

        concurrent
            path input
                wait input_ready

                lock running
                delegate running with change to process_input
                unlock running
            end
        end

        player_x assign player_x + 1

        if player_x == enemy_x
            if player_y == enemy_y
                player_health assign player_health - 10
            end
        end

        if player_health <= 0
            handle PlayerDefeated
                slot reason assign "Player defeated."
                delegate reason to puts
                stop
            end
        end

        if frame >= 60
            running assign false
        end
    end

    return 0
end

Clarissa says:

“This program now has collections knowledge, memory structure, permissions, a game loop, collision, parallel rendering, concurrent input, and manual error handling.”

Sherita says:

“And nobody had to summon an invisible runtime demon.”

---

Lesson 22 — What the Compiler Sees

Clarissa displays:

game:
    running
    frame

player:
    player_health
    player_x
    player_y

enemy:
    enemy_health
    enemy_x
    enemy_y

Permission graph:

running:
    read
    change
    share

player_health:
    read
    change

player_x:
    read
    change

enemy_x:
    read
    change

Execution graph:

main
 └─ while running
     ├─ parallel render work
     ├─ concurrent input path
     ├─ movement update
     ├─ collision check
     ├─ defeat check
     └─ frame limit check

Clarissa says:

“This is why Foresette is fast. The compiler sees the strategy plainly.”

---

Lesson 23 — Optimization Discussion

Sherita asks:

“So what can LLVM optimize?”

The class answers:

constant values
simple arithmetic
dead paths
read-only parallel work
slot storage
loop conditions
unnecessary memory

Clarissa adds:

“Also likely register promotion, branch simplification, inlining, and loop optimization.”

Sherita grins.

“They’re learning the fancy words. Dangerous.”

---

Lesson 24 — Class Three Rules

Clarissa writes:

Collections must have clear element behavior.

Index access must be valid or guarded.

Changing a collection requires change permission.

Shared mutation requires coordination.

Game state should be separated by memory relationship.

Detection and response can be separate.

Read-only parallel work is easiest to verify.

Concurrent paths require share permission.

Sherita adds underneath:

Do not expose the locker code.

The class laughs.

---

Homework — Build a Battle Simulator

Requirements:

program BattleSim

memory player dedicated
memory enemy dedicated
memory battle dedicated

player:
    health
    attack
    defense

enemy:
    health
    attack
    defense

battle:
    round
    running

Use:
    slots
    assignments
    permissions
    while loop
    if checks
    error PlayerDefeated
    error EnemyDefeated
    manual handling
    at least one collection
    at least one each loop

Bonus:

parallel
    calculate player damage
    calculate enemy damage
end

Sherita says:

“And if your player and enemy both change the same battle slot at the same time without sync, I will personally draw a race condition monster on your paper.”

---

Closing Scene

The bell rings.

Clarissa closes the projector.

“Today you built structure.”

She points to the board.

collections
memory layout
game loop
collision
parallel rendering
concurrent input

“These are not beginner-only concepts. These are real software ideas.”

Sherita picks up the homework folder.

“And tomorrow, we make the battle simulator hurt feelings.”

Clarissa gives her a look.

Sherita shrugs.

“Academically.”

The class laughs as they leave.

On the screen, the final message remains:

Foresette:
State clearly.
Move carefully.
Run natively.



## --- ##



Foresette Academy — Class Four

Battle Simulation, Procedures, Damage Logic, and Clean Execution Graphs

Instructor: Clarissa Taylor
Assistant Instructor: Sherita Pleasant

---

8:56 A.M. — The Drawing on the Board

The students walk in and stop.

On the board is a cartoon monster with six arms, three keyboards, and smoke coming out of its ears.

Under it:

RACE CONDITION MONSTER

Sherita Pleasant stands beside it holding a purple marker.

Clarissa Taylor enters, sees the drawing, pauses, then says:

“Sherita.”

Sherita smiles.

“You said visual learning was valid.”

Clarissa looks at the monster again.

“It is horrifying.”

“Thank you.”

The class sits down laughing.

Clarissa opens her laptop.

“Today we review your Battle Simulator homework. Then we improve it into professional Foresette.”

---

Lesson 1 — Battle Simulator Requirements Review

Clarissa writes:

BattleSim must include:

player memory
enemy memory
battle memory

health
attack
defense
round
running

while loop
if checks
PlayerDefeated error
EnemyDefeated error
manual handling
one collection
one each loop

Sherita adds:

Bonus:
parallel damage calculation

Clarissa says:

“Most of you built something that works.”

Sherita says:

“Some of you built something that attacks physics.”

---

Lesson 2 — A Basic BattleSim

Clarissa displays a clean beginner version:

program BattleSim

external puts
native c

error PlayerDefeated
    slot reason
end

error EnemyDefeated
    slot reason
end

entry main
    memory player dedicated
    memory enemy dedicated
    memory battle dedicated

    slot player_health from player assign 100
    slot player_attack from player assign 18
    slot player_defense from player assign 5

    slot enemy_health from enemy assign 80
    slot enemy_attack from enemy assign 14
    slot enemy_defense from enemy assign 3

    slot round from battle assign 1
    slot running from battle assign true

    slot battle_log from battle assign ["start", "clash", "finish"]

    permit read player_health
    permit change player_health

    permit read player_attack
    permit read player_defense

    permit read enemy_health
    permit change enemy_health

    permit read enemy_attack
    permit read enemy_defense

    permit read round
    permit change round

    permit read running
    permit change running

    permit read battle_log

    each event from battle_log
        delegate event with read to puts
    end

    while running
        slot player_damage assign player_attack - enemy_defense
        slot enemy_damage assign enemy_attack - player_defense

        enemy_health assign enemy_health - player_damage
        player_health assign player_health - enemy_damage

        if enemy_health <= 0
            handle EnemyDefeated
                slot reason assign "Enemy defeated."
                delegate reason to puts
                running assign false
            end
        end

        if player_health <= 0
            handle PlayerDefeated
                slot reason assign "Player defeated."
                delegate reason to puts
                running assign false
            end
        end

        round assign round + 1

        if round > 10
            running assign false
        end
    end

    return 0
end

Clarissa says:

“This is solid. It is readable, explicit, and deterministic.”

Sherita points.

“And nobody exposed the secret attack stat to the hallway. Growth.”

---

Lesson 3 — Trace the Battle

Clarissa writes:

player_damage = player_attack - enemy_defense
enemy_damage = enemy_attack - player_defense

Given:

player_attack = 18
enemy_defense = 3

enemy_attack = 14
player_defense = 5

Then:

player_damage = 15
enemy_damage = 9

Every round:

enemy_health loses 15
player_health loses 9
round increases by 1

Sherita says:

“This is turn-based pain with math receipts.”

---

Lesson 4 — The First Bug: Negative Damage

Clarissa changes the stats.

slot player_attack assign 4
slot enemy_defense assign 10

Now:

player_damage = 4 - 10
player_damage = -6

A student raises their hand.

“That would heal the enemy.”

Clarissa nods.

“Exactly.”

This is a logic bug.

Foresette will not guess that negative damage should become zero.

The programmer must state it.

Correct:

slot player_damage assign player_attack - enemy_defense

if player_damage < 0
    player_damage assign 0
end

But now what permission is needed?

The class answers:

permit change player_damage

Clarissa smiles.

“Good.”

Sherita says:

“You cannot fix damage without permission to fix damage. The compiler is petty in a healthy way.”

---

Lesson 5 — Cleaner Damage Clamp

Clarissa writes:

slot player_damage assign player_attack - enemy_defense
permit read player_damage
permit change player_damage

if player_damage < 0
    player_damage assign 0
end

Then:

slot enemy_damage assign enemy_attack - player_defense
permit read enemy_damage
permit change enemy_damage

if enemy_damage < 0
    enemy_damage assign 0
end

Clarissa says:

“This is called clamping.”

Sherita says:

“Clamp means: no, number, you’re not allowed to go there.”

---

Lesson 6 — Procedures for Damage

Clarissa says:

“Our main entry is getting crowded.”

She writes:

entry calculate_player_damage
    slot attack assign 18
    slot defense assign 3

    slot damage assign attack - defense

    permit read damage
    permit change damage

    if damage < 0
        damage assign 0
    end

    return damage
end

A student asks:

“But those numbers are fixed.”

Clarissa nods.

“Yes. This version teaches structure. Later, delegation sends real values.”

Sherita says:

“Training wheels. Stylish training wheels, but still.”

---

Lesson 7 — Delegated Damage Procedure

Clarissa introduces a cleaner pattern:

entry calculate_damage
    slot attack assign received_attack
    slot defense assign received_defense

    slot damage assign attack - defense

    permit read damage
    permit change damage

    if damage < 0
        damage assign 0
    end

    return damage
end

Then she explains:

“In finalized Foresette, routine input is delegation-aware. The compiler tracks what values crossed the boundary and under what authority.”

Conceptual call:

delegate player_attack with read to calculate_damage
delegate enemy_defense with read to calculate_damage

Sherita says:

“Attack and defense walk into the routine with name tags.”

---

Lesson 8 — Why Main Should Stay Clean

Clarissa compares two programs.

Messy main:

while running
    calculate everything here
    fix damage here
    check defeat here
    print here
    update round here
end

Clean main:

while running
    calculate damage
    apply damage
    check defeat
    update round
end

Clarissa says:

“Professional code separates responsibilities.”

Sherita says:

“If your main routine looks like a junk drawer, the bug is hiding under the batteries.”

---

Lesson 9 — Battle State Layout

Clarissa draws:

battle
 ├─ round
 ├─ running
 └─ battle_log

player
 ├─ health
 ├─ attack
 └─ defense

enemy
 ├─ health
 ├─ attack
 └─ defense

“This layout is clear.”

The compiler sees:

player values belong to player
enemy values belong to enemy
battle values belong to battle

Sherita says:

“Separate closets. Less chaos.”

---

Lesson 10 — Each Loop With Battle Log

Clarissa revisits:

slot battle_log assign ["start", "clash", "finish"]

each event from battle_log
    delegate event with read to puts
end

She asks:

“What does "each" do?”

The class answers:

“It walks through every item.”

Clarissa asks:

“What permission is required?”

permit read battle_log

Sherita says:

“The list is not being changed, just read. So no "change" needed.”

---

Lesson 11 — Changing a Collection

Clarissa writes:

battle_log[1] assign "critical clash"

“What permission is required?”

permit change battle_log

Correct:

permit read battle_log
permit change battle_log

battle_log[1] assign "critical clash"

Sherita says:

“Editing the battle log requires editor privileges. We are civilized.”

---

Lesson 12 — Manual Victory Handling

Clarissa improves the victory logic.

if enemy_health <= 0
    handle EnemyDefeated
        slot reason assign "Enemy defeated."
        delegate reason to puts
        running assign false
    end
end

She asks:

“What happens if both player and enemy reach zero in the same round?”

The class pauses.

Sherita slowly turns.

“Ohhh. Double knockout.”

Clarissa nods.

“Foresette will not decide that for you.”

You must define the rule.

Example:

if enemy_health <= 0
    if player_health <= 0
        slot result assign "Draw."
        delegate result to puts
        running assign false
    else
        handle EnemyDefeated
            slot reason assign "Enemy defeated."
            delegate reason to puts
            running assign false
        end
    end
end

Clarissa says:

“Rules do not exist unless you write them.”

---

Lesson 13 — Explicit Draw Error

Clarissa adds:

error DrawBattle
    slot reason
end

Then:

if enemy_health <= 0
    if player_health <= 0
        handle DrawBattle
            slot reason assign "Both fighters fell."
            delegate reason to puts
            running assign false
        end
    end
end

Sherita says:

“Now the draw is not a weird accident. It has a name.”

---

Lesson 14 — Parallel Damage Calculation

Clarissa writes:

parallel
    slot player_damage assign player_attack - enemy_defense
    slot enemy_damage assign enemy_attack - player_defense
end

Then pauses.

“Is this always safe?”

A student says:

“Yes, because they calculate different slots.”

Clarissa nods.

“Correct, if the inputs are read-only and outputs are separate.”

Needed permissions:

permit read player_attack
permit read enemy_defense
permit read enemy_attack
permit read player_defense

And if damage slots are later changed for clamping:

permit change player_damage
permit change enemy_damage

Sherita says:

“Parallel math is easy when nobody is grabbing the same steering wheel.”

---

Lesson 15 — Parallel Clamp

Clarissa shows:

parallel
    if player_damage < 0
        player_damage assign 0
    end

    if enemy_damage < 0
        enemy_damage assign 0
    end
end

This is safe because:

player_damage and enemy_damage are separate slots

Unsafe would be:

parallel
    total_damage assign total_damage + player_damage
    total_damage assign total_damage + enemy_damage
end

unless synchronized.

Sherita points at the monster on the board.

“That’s how you summon him.”

---

Lesson 16 — Race Condition Monster Example

Broken:

slot total_damage assign 0

permit read total_damage
permit change total_damage
permit share total_damage

parallel
    total_damage assign total_damage + player_damage
    total_damage assign total_damage + enemy_damage
end

Clarissa says:

“Two branches mutate one shared slot.”

Fix:

slot player_total assign player_damage
slot enemy_total assign enemy_damage
slot total_damage assign player_total + enemy_total

Sherita says:

“Don’t fight over one bucket. Use two buckets, then pour them together.”

---

Lesson 17 — Final BattleSim Professional Version

Clarissa displays the upgraded class version.

program BattleSimPro

external puts
native c

error PlayerDefeated
    slot reason
end

error EnemyDefeated
    slot reason
end

error DrawBattle
    slot reason
end

entry main
    memory player dedicated
    memory enemy dedicated
    memory battle dedicated

    slot player_health from player assign 100
    slot player_attack from player assign 18
    slot player_defense from player assign 5

    slot enemy_health from enemy assign 80
    slot enemy_attack from enemy assign 14
    slot enemy_defense from enemy assign 3

    slot round from battle assign 1
    slot running from battle assign true
    slot battle_log from battle assign ["battle start", "battle running", "battle end"]

    permit read player_health
    permit change player_health

    permit read player_attack
    permit read player_defense

    permit read enemy_health
    permit change enemy_health

    permit read enemy_attack
    permit read enemy_defense

    permit read round
    permit change round

    permit read running
    permit change running

    permit read battle_log

    each event from battle_log
        delegate event with read to puts
    end

    while running
        slot player_damage assign 0
        slot enemy_damage assign 0

        permit read player_damage
        permit change player_damage

        permit read enemy_damage
        permit change enemy_damage

        parallel
            player_damage assign player_attack - enemy_defense
            enemy_damage assign enemy_attack - player_defense
        end

        parallel
            if player_damage < 0
                player_damage assign 0
            end

            if enemy_damage < 0
                enemy_damage assign 0
            end
        end

        enemy_health assign enemy_health - player_damage
        player_health assign player_health - enemy_damage

        if enemy_health <= 0
            if player_health <= 0
                handle DrawBattle
                    slot reason assign "Both fighters fell."
                    delegate reason to puts
                    running assign false
                end
            else
                handle EnemyDefeated
                    slot reason assign "Enemy defeated."
                    delegate reason to puts
                    running assign false
                end
            end
        else
            if player_health <= 0
                handle PlayerDefeated
                    slot reason assign "Player defeated."
                    delegate reason to puts
                    running assign false
                end
            end
        end

        round assign round + 1

        if round > 10
            running assign false
        end
    end

    return 0
end

Clarissa says:

“This version defines battle state, damage, victory, defeat, draw, rounds, logging, parallel calculation, and manual control.”

Sherita says:

“It has drama, but organized drama.”

---

Lesson 18 — Compiler View of BattleSimPro

Clarissa writes:

Memory Table

player:
    player_health
    player_attack
    player_defense

enemy:
    enemy_health
    enemy_attack
    enemy_defense

battle:
    round
    running
    battle_log

Permission Table:

player_health:
    read
    change

player_attack:
    read

enemy_health:
    read
    change

running:
    read
    change

Execution Table:

main
 ├─ each battle_log
 └─ while running
     ├─ parallel damage calculation
     ├─ parallel damage clamp
     ├─ apply damage
     ├─ defeat/draw checks
     ├─ round increment
     └─ round limit

Clarissa says:

“This is a clean execution graph.”

Sherita adds:

“And the compiler did not need a detective hat.”

---

Lesson 19 — What LLVM Can Optimize

Clarissa asks:

“What can LLVM improve?”

The class answers:

constant stats
damage calculations
dead branches
loop structure
slot storage
parallel independence
inlining
branch simplification

Clarissa says:

“Correct.”

Because:

player_attack
enemy_defense
enemy_attack
player_defense

are known constants in this example, LLVM can simplify the damage math.

Sherita says:

“The optimizer sees the numbers and starts cleaning like somebody’s auntie is coming over.”

---

Lesson 20 — Professional Habit: Separate Facts From Events

Clarissa writes:

Facts:
    health
    attack
    defense
    round

Events:
    damage
    defeat
    draw
    round advance

“Good Foresette separates stable state from events.”

Bad:

everything in one slot

Good:

player_health
player_attack
player_defense
enemy_health
enemy_attack
enemy_defense

Sherita says:

“If one slot is doing twelve jobs, it needs therapy.”

---

Lesson 21 — Professional Habit: Name Failure

Clarissa says:

“Never hide meaningful failure.”

Instead of:

stop

Prefer:

handle PlayerDefeated
    stop
end

Because now the reason is visible.

Errors should describe domain meaning:

PlayerDefeated
EnemyDefeated
DrawBattle
InvalidCode
MissingTexture
ConnectionLost
FrameInvalid

Sherita says:

“Named failure is less scary. Still rude, but less scary.”

---

Lesson 22 — Homework

Clarissa opens the next assignment.

ARENA SIMULATOR

Requirements:

program ArenaSim

memory player dedicated
memory enemy dedicated
memory arena dedicated

player:
    health
    attack
    defense
    position

enemy:
    health
    attack
    defense
    position

arena:
    round
    running
    hazards

Must include:

collection hazards
each loop over hazards
damage calculation
position check
manual errors:
    PlayerDefeated
    EnemyDefeated
    HazardTriggered
parallel section
while loop
permissions
dedicated memory

Bonus:

concurrent
    path crowd
    path announcer
end

Sherita says:

“Somebody better make the hazard a banana peel.”

Clarissa gives her a look.

Sherita shrugs.

“Classic arena design.”

---

Final Scene

The bell rings.

Clarissa erases everything except:

State.
Authority.
Movement.
Failure.
Execution.

She turns to the class.

“That is Foresette.”

Sherita adds:

“And don’t summon the monster.”

One student points to the board.

“Can I take a picture of it?”

Sherita beams.

“Absolutely.”

Clarissa sighs, but she is smiling.

The projector fades to:

Foresette Academy

A clear program is a fast program.
A visible failure is a controllable failure.
A synchronized path is a peaceful path.



## --- ##



Foresette Academy — Class Five

Arena Simulation, Hazards, Events, and Concurrent Atmosphere

Instructor: Clarissa Taylor
Assistant Instructor: Sherita Pleasant

---

8:55 A.M. — The Banana Peel Problem

The students walk in to find one phrase written on the board:

HAZARD TRIGGERED

Under it, Sherita Pleasant has drawn a banana peel wearing sunglasses.

Clarissa Taylor stands beside the board with her arms folded.

Sherita says, “It’s educational.”

Clarissa looks at the drawing.

“It has sunglasses.”

“Safety goggles,” Sherita says.

The class laughs.

Clarissa opens her laptop.

“Today we review the Arena Simulator. You are going to learn how environment events work in Foresette.”

Sherita points at the banana peel.

“And how one peel can ruin a whole combat system.”

---

Lesson 1 — ArenaSim Requirements Review

Clarissa writes:

program ArenaSim

memory player dedicated
memory enemy dedicated
memory arena dedicated

player:
    health
    attack
    defense
    position

enemy:
    health
    attack
    defense
    position

arena:
    round
    running
    hazards

Required features:

collection hazards
each loop over hazards
damage calculation
position check
manual errors:
    PlayerDefeated
    EnemyDefeated
    HazardTriggered
parallel section
while loop
permissions
dedicated memory

Bonus:

concurrent
    path crowd
    path announcer
end

Clarissa says:

“Today’s focus is event clarity. In Foresette, things do not ‘just happen.’ Events are stated.”

Sherita nods.

“Even the banana peel needs paperwork.”

---

Lesson 2 — Basic Arena Layout

Clarissa displays:

program ArenaSim

external puts
native c

error PlayerDefeated
    slot reason
end

error EnemyDefeated
    slot reason
end

error HazardTriggered
    slot reason
end

entry main
    memory player dedicated
    memory enemy dedicated
    memory arena dedicated

    slot player_health from player assign 100
    slot player_attack from player assign 18
    slot player_defense from player assign 5
    slot player_position from player assign 2

    slot enemy_health from enemy assign 80
    slot enemy_attack from enemy assign 14
    slot enemy_defense from enemy assign 3
    slot enemy_position from enemy assign 5

    slot round from arena assign 1
    slot running from arena assign true
    slot hazards from arena assign [2, 4, 6]

    return 0
end

Clarissa says:

“This gives us three memory regions.”

player
enemy
arena

Sherita adds:

“Separate closets again. We are not stuffing the enemy inside the player drawer.”

---

Lesson 3 — Position Logic

Clarissa writes:

slot player_position assign 2
slot enemy_position assign 5

Position is a simple number representing arena location.

Distance:

slot distance assign enemy_position - player_position

If:

distance <= 1

then the fighters are close enough to attack.

Example:

if distance <= 1
    enemy_health assign enemy_health - player_damage
end

Sherita says:

“So if you are across the arena, no anime sword slash unless you programmed one.”

---

Lesson 4 — The Absolute Distance Problem

Clarissa changes the values:

player_position = 8
enemy_position = 3

Then:

distance = enemy_position - player_position
distance = -5

Clarissa asks:

“Is negative distance useful here?”

The class says:

“No.”

Clarissa nods.

“So we define absolute distance manually.”

slot distance assign enemy_position - player_position

permit read distance
permit change distance

if distance < 0
    distance assign distance * -1
end

Sherita says:

“The compiler does not assume you wanted absolute value. It waits for you to say it.”

---

Lesson 5 — Hazard Collection

The arena has hazards:

slot hazards from arena assign [2, 4, 6]

These are dangerous positions.

Clarissa asks:

“What does the compiler know?”

The class answers:

hazards belongs to arena
hazards is a numeric collection
hazards has three elements

Clarissa smiles.

“Good.”

---

Lesson 6 — Each Hazard Check

each hazard from hazards
    if player_position == hazard
        handle HazardTriggered
            slot reason assign "Player stepped on hazard."
            delegate reason to puts
            player_health assign player_health - 10
        end
    end
end

Clarissa says:

“This checks every hazard.”

Sherita points at the banana peel drawing.

“Position 2. That’s the peel. Player walked right into it. Tragic.”

---

Lesson 7 — Permissions Needed

Clarissa asks:

“What permissions do we need?”

The class builds the list:

permit read player_position

permit read hazards

permit read player_health
permit change player_health

For printing:

permit read reason

Clarissa corrects gently:

“"reason" is local inside the handler. It is assigned and delegated. Depending on the compiler’s strict profile, delegation to external output may require exposure authority.”

So professional form:

permit expose reason

Sherita says:

“If you send it outside the program, that’s exposure. Even if it’s just yelling at "puts".”

---

Lesson 8 — HazardTriggered Is Not Defeat

Clarissa writes:

HazardTriggered

Then:

PlayerDefeated

“These are different events.”

Hazard:

player takes damage
game continues

Defeat:

player health reaches zero
game stops

Sherita says:

“A banana peel is not automatically death. Unless it’s a very committed banana peel.”

---

Lesson 9 — Applying Battle Damage

Clarissa adds:

slot player_damage assign player_attack - enemy_defense
slot enemy_damage assign enemy_attack - player_defense

Clamp both:

if player_damage < 0
    player_damage assign 0
end

if enemy_damage < 0
    enemy_damage assign 0
end

Then:

if distance <= 1
    enemy_health assign enemy_health - player_damage
    player_health assign player_health - enemy_damage
end

Clarissa says:

“The position check controls whether damage applies.”

Sherita says:

“No proximity, no bonk.”

---

Lesson 10 — Movement

Clarissa writes:

if player_position < enemy_position
    player_position assign player_position + 1
else
    player_position assign player_position - 1
end

This moves the player toward the enemy.

She adds:

if enemy_position < player_position
    enemy_position assign enemy_position + 1
else
    enemy_position assign enemy_position - 1
end

Sherita squints.

“So they both walk toward each other?”

Clarissa nods.

“Exactly.”

Sherita says:

“Very dramatic. Like two tiny math gladiators.”

---

Lesson 11 — Parallel Movement

Clarissa says:

“Player and enemy positions are separate slots, so movement can be parallel if they read stable positions first.”

Safe pattern:

slot player_target assign enemy_position
slot enemy_target assign player_position

parallel
    if player_position < player_target
        player_position assign player_position + 1
    else
        player_position assign player_position - 1
    end

    if enemy_position < enemy_target
        enemy_position assign enemy_position + 1
    else
        enemy_position assign enemy_position - 1
    end
end

Clarissa explains:

“We snapshot target positions first.”

Sherita says:

“Otherwise they both move while staring at each other’s moving feet. Chaos ballet.”

---

Lesson 12 — Full ArenaSim Core

Clarissa displays the class version.

program ArenaSimCore

external puts
native c

error PlayerDefeated
    slot reason
end

error EnemyDefeated
    slot reason
end

error HazardTriggered
    slot reason
end

entry main
    memory player dedicated
    memory enemy dedicated
    memory arena dedicated

    slot player_health from player assign 100
    slot player_attack from player assign 18
    slot player_defense from player assign 5
    slot player_position from player assign 2

    slot enemy_health from enemy assign 80
    slot enemy_attack from enemy assign 14
    slot enemy_defense from enemy assign 3
    slot enemy_position from enemy assign 5

    slot round from arena assign 1
    slot running from arena assign true
    slot hazards from arena assign [2, 4, 6]

    permit read player_health
    permit change player_health

    permit read player_attack
    permit read player_defense

    permit read player_position
    permit change player_position

    permit read enemy_health
    permit change enemy_health

    permit read enemy_attack
    permit read enemy_defense

    permit read enemy_position
    permit change enemy_position

    permit read round
    permit change round

    permit read running
    permit change running

    permit read hazards

    while running
        slot player_target assign enemy_position
        slot enemy_target assign player_position

        parallel
            if player_position < player_target
                player_position assign player_position + 1
            else
                player_position assign player_position - 1
            end

            if enemy_position < enemy_target
                enemy_position assign enemy_position + 1
            else
                enemy_position assign enemy_position - 1
            end
        end

        each hazard from hazards
            if player_position == hazard
                handle HazardTriggered
                    slot reason assign "Player stepped on hazard."
                    delegate reason to puts
                    player_health assign player_health - 10
                end
            end

            if enemy_position == hazard
                handle HazardTriggered
                    slot reason assign "Enemy stepped on hazard."
                    delegate reason to puts
                    enemy_health assign enemy_health - 10
                end
            end
        end

        slot distance assign enemy_position - player_position

        permit read distance
        permit change distance

        if distance < 0
            distance assign distance * -1
        end

        slot player_damage assign player_attack - enemy_defense
        slot enemy_damage assign enemy_attack - player_defense

        permit read player_damage
        permit change player_damage

        permit read enemy_damage
        permit change enemy_damage

        parallel
            if player_damage < 0
                player_damage assign 0
            end

            if enemy_damage < 0
                enemy_damage assign 0
            end
        end

        if distance <= 1
            enemy_health assign enemy_health - player_damage
            player_health assign player_health - enemy_damage
        end

        if enemy_health <= 0
            handle EnemyDefeated
                slot reason assign "Enemy defeated."
                delegate reason to puts
                running assign false
            end
        end

        if player_health <= 0
            handle PlayerDefeated
                slot reason assign "Player defeated."
                delegate reason to puts
                running assign false
            end
        end

        round assign round + 1

        if round > 10
            running assign false
        end
    end

    return 0
end

Sherita says:

“That’s officially a little arena simulator.”

Clarissa nods.

“It has state, movement, hazards, combat, errors, loops, and parallel sections.”

---

Lesson 13 — Find the Hidden Issue

Clarissa asks:

“What issue exists in this program?”

The class studies.

A student says:

“If both enemy and player die in the same round, it handles both separately.”

Clarissa nods.

“Good. We need draw handling again.”

Add:

error DrawBattle
    slot reason
end

Then:

if enemy_health <= 0
    if player_health <= 0
        handle DrawBattle
            slot reason assign "Both fighters fell in the arena."
            delegate reason to puts
            running assign false
        end
    else
        handle EnemyDefeated
            slot reason assign "Enemy defeated."
            delegate reason to puts
            running assign false
        end
    end
else
    if player_health <= 0
        handle PlayerDefeated
            slot reason assign "Player defeated."
            delegate reason to puts
            running assign false
        end
    end
end

Sherita says:

“Double knockout gets its own paperwork too.”

---

Lesson 14 — Concurrent Atmosphere

Clarissa says:

“Now we add atmosphere. Crowd and announcer do not control combat. They run beside it.”

concurrent
    path crowd
        wait round_started
        signal crowd_reacts
    end

    path announcer
        wait crowd_reacts
        delegate round with read to announce_round
    end
end

Sherita says:

“The crowd path is basically: ‘OHHHH!’”

Clarissa says:

“Academic interpretation: yes.”

---

Lesson 15 — Concurrency Permissions

Because "round" enters the announcer path:

delegate round with read to announce_round

and this occurs in concurrent execution, professional Foresette requires:

permit share round

Since it is only read:

permit read round
permit share round

If the announcer changed "round", it would also require:

permit change round
lock round
unlock round

Sherita says:

“The announcer may describe the round. The announcer may not rewrite reality.”

---

Lesson 16 — Full ArenaSim Professional Version

Clarissa shows the upgraded version.

program ArenaSimPro

external puts
native c

error PlayerDefeated
    slot reason
end

error EnemyDefeated
    slot reason
end

error DrawBattle
    slot reason
end

error HazardTriggered
    slot reason
end

entry main
    memory player dedicated
    memory enemy dedicated
    memory arena dedicated

    slot player_health from player assign 100
    slot player_attack from player assign 18
    slot player_defense from player assign 5
    slot player_position from player assign 2

    slot enemy_health from enemy assign 80
    slot enemy_attack from enemy assign 14
    slot enemy_defense from enemy assign 3
    slot enemy_position from enemy assign 5

    slot round from arena assign 1
    slot running from arena assign true
    slot hazards from arena assign [2, 4, 6]

    permit read player_health
    permit change player_health

    permit read player_attack
    permit read player_defense

    permit read player_position
    permit change player_position

    permit read enemy_health
    permit change enemy_health

    permit read enemy_attack
    permit read enemy_defense

    permit read enemy_position
    permit change enemy_position

    permit read round
    permit change round
    permit share round

    permit read running
    permit change running

    permit read hazards

    while running
        signal round_started

        concurrent
            path crowd
                wait round_started
                signal crowd_reacts
            end

            path announcer
                wait crowd_reacts
                delegate round with read to announce_round
            end
        end

        slot player_target assign enemy_position
        slot enemy_target assign player_position

        parallel
            if player_position < player_target
                player_position assign player_position + 1
            else
                player_position assign player_position - 1
            end

            if enemy_position < enemy_target
                enemy_position assign enemy_position + 1
            else
                enemy_position assign enemy_position - 1
            end
        end

        each hazard from hazards
            if player_position == hazard
                handle HazardTriggered
                    slot reason assign "Player stepped on hazard."
                    delegate reason to puts
                    player_health assign player_health - 10
                end
            end

            if enemy_position == hazard
                handle HazardTriggered
                    slot reason assign "Enemy stepped on hazard."
                    delegate reason to puts
                    enemy_health assign enemy_health - 10
                end
            end
        end

        slot distance assign enemy_position - player_position

        permit read distance
        permit change distance

        if distance < 0
            distance assign distance * -1
        end

        slot player_damage assign player_attack - enemy_defense
        slot enemy_damage assign enemy_attack - player_defense

        permit read player_damage
        permit change player_damage

        permit read enemy_damage
        permit change enemy_damage

        parallel
            if player_damage < 0
                player_damage assign 0
            end

            if enemy_damage < 0
                enemy_damage assign 0
            end
        end

        if distance <= 1
            enemy_health assign enemy_health - player_damage
            player_health assign player_health - enemy_damage
        end

        if enemy_health <= 0
            if player_health <= 0
                handle DrawBattle
                    slot reason assign "Both fighters fell in the arena."
                    delegate reason to puts
                    running assign false
                end
            else
                handle EnemyDefeated
                    slot reason assign "Enemy defeated."
                    delegate reason to puts
                    running assign false
                end
            end
        else
            if player_health <= 0
                handle PlayerDefeated
                    slot reason assign "Player defeated."
                    delegate reason to puts
                    running assign false
                end
            end
        end

        round assign round + 1

        if round > 10
            running assign false
        end
    end

    return 0
end

Clarissa says:

“This is now a small deterministic arena simulation.”

Sherita says:

“It has combat, movement, hazards, crowd noise, announcer drama, and no secret compiler mind-reading.”

---

Lesson 17 — Compiler Tables

Clarissa projects:

Memory Table

player:
    player_health
    player_attack
    player_defense
    player_position

enemy:
    enemy_health
    enemy_attack
    enemy_defense
    enemy_position

arena:
    round
    running
    hazards

Permission Table:

round:
    read
    change
    share

running:
    read
    change

hazards:
    read

player_health:
    read
    change

enemy_health:
    read
    change

Execution Table:

while running
 ├─ signal round_started
 ├─ concurrent atmosphere paths
 ├─ parallel movement
 ├─ each hazard check
 ├─ distance calculation
 ├─ parallel damage clamp
 ├─ combat damage
 ├─ defeat/draw handling
 ├─ round increment
 └─ round limit

Clarissa says:

“The compiler can see the architecture.”

Sherita adds:

“And if the architecture is messy, the compiler will not politely pretend it is fine.”

---

Lesson 18 — Optimization Opportunities

Clarissa asks:

“What can be optimized?”

The class answers:

constant hazard list
known attack/defense math
distance calculation
parallel movement independence
damage clamp branches
round limit
dead error paths
slot storage

Clarissa adds:

“Also loop simplification, register promotion, branch folding, inlining, and possibly vectorized hazard checks if the collection grows.”

Sherita says:

“Translation: clean explicit code gives LLVM more places to flex.”

---

Lesson 19 — Design Lesson: Events Need Names

Clarissa writes:

HazardTriggered
PlayerDefeated
EnemyDefeated
DrawBattle

“These names matter.”

Bad:

if something bad
    stop
end

Good:

handle HazardTriggered
    ...
end

Sherita says:

“If something matters to the story of your program, name it.”

Clarissa nods.

“Exactly. Named events are easier to test, trace, optimize, and debug.”

---

Lesson 20 — Homework: Arena Replay System

Clarissa writes the next assignment.

ARENA REPLAY SYSTEM

Requirements:

memory replay dedicated

slots:
    replay_frames
    current_frame
    recording
    playback

Use:
    collection of frame positions
    each loop
    for loop
    permissions
    manual error:
        ReplayCorrupt
        ReplayEnded

Add:
    route record to playback
    route playback to shutdown

Bonus:

parallel
    validate player positions
    validate enemy positions
end

Super bonus:

concurrent
    path recorder
    path viewer
end

Sherita says:

“And no, your replay system cannot ‘just remember everything spiritually.’ Use slots.”

---

Closing Scene

The bell rings.

Clarissa turns off the projector.

“Today you learned that environments are programs too.”

She points to the board:

position
hazard
event
movement
atmosphere
replay

“An arena is not just a background. It is state, rules, and events.”

Sherita looks at the banana peel drawing.

“And sometimes sunglasses.”

Clarissa sighs.

The class laughs.

As they leave, the final slide remains:

Foresette Academy

If it affects execution, state it.
If it changes state, permit it.
If it crosses paths, share it.
If it can fail, name it.



## --- ##



Foresette Academy — Class Six

Replay Systems, Recorded State, Validation, and Deterministic Playback

Instructor: Clarissa Taylor
Assistant Instructor: Sherita Pleasant

---

8:54 A.M. — The Replay Disaster

The students enter.

On the board, Sherita has written:

REPLAY SYSTEM RULE #1:
THE PAST NEEDS STRUCTURE

Under it she has drawn a tiny arena fighter rewinding into a banana peel.

Clarissa Taylor looks at it.

“Is that the same banana peel from yesterday?”

Sherita nods.

“It has continuity.”

Clarissa pauses.

“I respect the commitment.”

The class laughs.

Clarissa opens the lesson.

“Today we are learning replay systems. A replay system is not magic. It records important state, validates it, and plays it back in order.”

Sherita adds:

“If your replay system says, ‘Trust me, bro,’ it is already corrupt.”

---

Lesson 1 — Replay Homework Requirements

Clarissa writes:

memory replay dedicated

slots:
    replay_frames
    current_frame
    recording
    playback

Required:

collection of frame positions
each loop
for loop
permissions
manual errors:
    ReplayCorrupt
    ReplayEnded

routes:
    record to playback
    playback to shutdown

Bonus:

parallel
    validate player positions
    validate enemy positions
end

Super bonus:

concurrent
    path recorder
    path viewer
end

Clarissa says:

“Today’s central idea is recorded truth.”

---

Lesson 2 — Basic Replay Memory

program ArenaReplay

external puts
native c

error ReplayCorrupt
    slot reason
end

error ReplayEnded
    slot reason
end

entry main
    memory replay dedicated

    slot replay_frames from replay assign [2, 3, 4, 5, 6]
    slot current_frame from replay assign 0
    slot recording from replay assign true
    slot playback from replay assign false

    return 0
end

Clarissa explains:

replay_frames

stores positions across time.

current_frame

tracks where playback is.

recording

means we are saving data.

playback

means we are replaying data.

Sherita says:

“Basically: what happened, where we are, are we recording, are we watching.”

---

Lesson 3 — Permissions for Replay

Clarissa asks:

“What permissions do we need?”

The class builds:

permit read replay_frames
permit change replay_frames

permit read current_frame
permit change current_frame

permit read recording
permit change recording

permit read playback
permit change playback

Clarissa nods.

“If we only read the replay frames during playback, we need read. If we append or modify frames during recording, we need change.”

Sherita says:

“If you write to the past, the compiler wants to see your badge.”

---

Lesson 4 — Routes

Clarissa writes:

route record to playback
route playback to shutdown

She explains:

“Routes describe major movement through the program.”

record
   ↓
playback
   ↓
shutdown

Foresette does not infer this.

You state it.

Sherita says:

“Routes are like hallway signs. No wandering into the cafeteria during shutdown.”

---

Lesson 5 — Recording State

Clarissa writes a simplified recording loop.

while recording
    replay_frames[current_frame] assign player_position
    current_frame assign current_frame + 1

    if current_frame >= 5
        recording assign false
        playback assign true
    end
end

“What permissions are used?”

The class answers:

change replay_frames
read current_frame
change current_frame
read recording
change recording
change playback

Clarissa smiles.

“Good.”

Sherita says:

“Y’all are getting permission reflexes. Beautifully suspicious.”

---

Lesson 6 — Playback State

Playback reads recorded frames.

while playback
    slot position assign replay_frames[current_frame]
    delegate position with read to draw_replay

    current_frame assign current_frame + 1

    if current_frame >= 5
        handle ReplayEnded
            slot reason assign "Replay finished."
            delegate reason to puts
            playback assign false
        end
    end
end

Clarissa says:

“Playback does not invent positions. It reads recorded positions in sequence.”

Sherita adds:

“The replay is not improvising jazz.”

---

Lesson 7 — Bounds Safety

Clarissa shows a dangerous version:

slot position assign replay_frames[current_frame]

She asks:

“What if "current_frame" is 9?”

The class says:

“Out of bounds.”

Correct guard:

if current_frame < 5
    slot position assign replay_frames[current_frame]
else
    handle ReplayEnded
        slot reason assign "Replay finished."
        delegate reason to puts
        playback assign false
    end
end

Clarissa says:

“Foresette wants visible safety.”

Sherita says:

“No jumping past the end of the memory diving board.”

---

Lesson 8 — Replay Corruption

Clarissa writes:

slot replay_frames assign [2, 3, -99, 5, 6]

“What is wrong?”

A student says:

“Position cannot be negative.”

Clarissa nods.

“So we define corruption.”

if position < 0
    handle ReplayCorrupt
        slot reason assign "Replay position is invalid."
        delegate reason to puts
        stop
    end
end

Sherita says:

“Negative position means someone threw the arena into the basement.”

---

Lesson 9 — Each Loop Validation

Clarissa writes:

each position from replay_frames
    if position < 0
        handle ReplayCorrupt
            slot reason assign "Replay contains invalid position."
            delegate reason to puts
            stop
        end
    end
end

Clarissa says:

“This validates every frame.”

Sherita adds:

“Before playback, inspect the receipts.”

---

Lesson 10 — For Loop Playback

Clarissa writes:

for i from 0 to 5
    slot position assign replay_frames[i]
    delegate position with read to draw_replay
end

Use "for" when index matters.

Use "each" when every item is simply visited.

each position from replay_frames
    validate position
end

for i from 0 to 5
    play frame i
end

Sherita says:

“Each is a walk. For is a numbered march.”

---

Lesson 11 — Full Replay Core

Clarissa displays:

program ArenaReplayCore

external puts
native c

error ReplayCorrupt
    slot reason
end

error ReplayEnded
    slot reason
end

entry main
    memory replay dedicated
    memory player dedicated

    slot player_position from player assign 2

    slot replay_frames from replay assign [2, 3, 4, 5, 6]
    slot current_frame from replay assign 0
    slot recording from replay assign true
    slot playback from replay assign false

    permit read player_position
    permit change player_position

    permit read replay_frames
    permit change replay_frames

    permit read current_frame
    permit change current_frame

    permit read recording
    permit change recording

    permit read playback
    permit change playback

    route record to playback
    route playback to shutdown

    each position from replay_frames
        if position < 0
            handle ReplayCorrupt
                slot reason assign "Replay contains invalid position."
                delegate reason to puts
                stop
            end
        end
    end

    while recording
        replay_frames[current_frame] assign player_position

        player_position assign player_position + 1
        current_frame assign current_frame + 1

        if current_frame >= 5
            recording assign false
            playback assign true
            current_frame assign 0
        end
    end

    while playback
        if current_frame < 5
            slot position assign replay_frames[current_frame]
            delegate position with read to draw_replay
            current_frame assign current_frame + 1
        else
            handle ReplayEnded
                slot reason assign "Replay finished."
                delegate reason to puts
                playback assign false
            end
        end
    end

    return 0
end

Clarissa says:

“This program records positions, validates them, resets to frame zero, and plays them back.”

Sherita says:

“It remembers the past without lying. Rare.”

---

Lesson 12 — Hidden Issue: Validation Before Recording

Clarissa asks:

“What issue exists?”

The class looks carefully.

A student says:

“It validates replay frames before recording changes them.”

Clarissa points.

“Excellent.”

If recording writes new values, validation should happen after recording and before playback.

Better order:

record
validate
playback
shutdown

Routes:

route record to validate
route validate to playback
route playback to shutdown

Sherita says:

“Do not inspect the cake batter before baking and declare the cake safe.”

---

Lesson 13 — Better Route Structure

route record to validate
route validate to playback
route playback to shutdown

Clarissa draws:

RECORD
  ↓
VALIDATE
  ↓
PLAYBACK
  ↓
SHUTDOWN

She says:

“Now the replay system has a clean lifecycle.”

Sherita nods.

“Past gets recorded, checked, then shown. Very adult.”

---

Lesson 14 — Parallel Validation

Bonus requirement:

parallel
    validate player positions
    validate enemy positions
end

Clarissa creates two collections:

slot player_frames from replay assign [2, 3, 4, 5, 6]
slot enemy_frames from replay assign [5, 4, 3, 2, 1]

Parallel validation:

parallel
    each position from player_frames
        if position < 0
            handle ReplayCorrupt
                slot reason assign "Player replay corrupt."
                delegate reason to puts
                stop
            end
        end
    end

    each position from enemy_frames
        if position < 0
            handle ReplayCorrupt
                slot reason assign "Enemy replay corrupt."
                delegate reason to puts
                stop
            end
        end
    end
end

Clarissa says:

“This is safe because the two collections are separate and read-only during validation.”

Sherita says:

“Two inspectors. Two clipboards. No fighting.”

---

Lesson 15 — Concurrent Recorder and Viewer

Super bonus:

concurrent
    path recorder
    path viewer
end

Clarissa warns:

“This is more dangerous. Recording and viewing can touch the same replay data.”

Unsafe:

concurrent
    path recorder
        replay_frames[current_frame] assign player_position
    end

    path viewer
        slot position assign replay_frames[current_frame]
    end
end

Problem:

same collection
same frame index
one writes
one reads
no sync

Sherita points dramatically at the board.

“Race condition monster is stretching.”

---

Lesson 16 — Safe Concurrent Replay

Clarissa writes:

permit share replay_frames
permit share current_frame

Then:

concurrent
    path recorder
        lock replay_frames
        replay_frames[current_frame] assign player_position
        signal frame_recorded
        unlock replay_frames
    end

    path viewer
        wait frame_recorded
        lock replay_frames
        slot position assign replay_frames[current_frame]
        delegate position with read to draw_replay
        unlock replay_frames
    end
end

Clarissa says:

“If paths share mutable replay data, they coordinate.”

Sherita says:

“No sync, no peace.”

---

Lesson 17 — Professional ReplaySim

Clarissa displays the upgraded version.

program ArenaReplayPro

external puts
native c

error ReplayCorrupt
    slot reason
end

error ReplayEnded
    slot reason
end

entry main
    memory replay dedicated
    memory player dedicated
    memory enemy dedicated

    slot player_position from player assign 2
    slot enemy_position from enemy assign 5

    slot player_frames from replay assign [0, 0, 0, 0, 0]
    slot enemy_frames from replay assign [0, 0, 0, 0, 0]

    slot current_frame from replay assign 0
    slot recording from replay assign true
    slot playback from replay assign false

    permit read player_position
    permit change player_position

    permit read enemy_position
    permit change enemy_position

    permit read player_frames
    permit change player_frames
    permit share player_frames

    permit read enemy_frames
    permit change enemy_frames
    permit share enemy_frames

    permit read current_frame
    permit change current_frame
    permit share current_frame

    permit read recording
    permit change recording

    permit read playback
    permit change playback

    route record to validate
    route validate to playback
    route playback to shutdown

    while recording
        player_frames[current_frame] assign player_position
        enemy_frames[current_frame] assign enemy_position

        player_position assign player_position + 1
        enemy_position assign enemy_position - 1

        current_frame assign current_frame + 1

        if current_frame >= 5
            recording assign false
            playback assign true
            current_frame assign 0
        end
    end

    parallel
        each position from player_frames
            if position < 0
                handle ReplayCorrupt
                    slot reason assign "Player replay corrupt."
                    delegate reason to puts
                    stop
                end
            end
        end

        each position from enemy_frames
            if position < 0
                handle ReplayCorrupt
                    slot reason assign "Enemy replay corrupt."
                    delegate reason to puts
                    stop
                end
            end
        end
    end

    while playback
        if current_frame < 5
            slot player_view assign player_frames[current_frame]
            slot enemy_view assign enemy_frames[current_frame]

            parallel
                delegate player_view with read to draw_player_replay
                delegate enemy_view with read to draw_enemy_replay
            end

            current_frame assign current_frame + 1
        else
            handle ReplayEnded
                slot reason assign "Replay finished."
                delegate reason to puts
                playback assign false
            end
        end
    end

    return 0
end

Clarissa says:

“This is a professional replay skeleton.”

Sherita says:

“It records, validates, plays back, and does not hallucinate the past.”

---

Lesson 18 — Compiler View

Clarissa projects:

Memory Table

replay:
    player_frames
    enemy_frames
    current_frame
    recording
    playback

player:
    player_position

enemy:
    enemy_position

Execution Table:

record loop
    write player/enemy frames
    update positions
    advance current frame

validate route
    parallel validate player frames
    parallel validate enemy frames

playback loop
    guarded frame access
    parallel draw replay views
    advance current frame

shutdown
    return

Permission Table:

player_frames:
    read
    change
    share

enemy_frames:
    read
    change
    share

current_frame:
    read
    change
    share

Clarissa says:

“The compiler can reason about replay state because the program states the lifecycle.”

---

Lesson 19 — Deterministic Replay

Clarissa writes:

DETERMINISTIC REPLAY

She explains:

“A deterministic replay gives the same playback every time.”

To achieve that:

record the necessary state
preserve frame order
validate before playback
avoid unsynchronized mutation
guard bounds
name corruption
end playback explicitly

Sherita says:

“If the replay changes every time, that is not a replay. That is a rumor.”

---

Lesson 20 — Homework: Save File System

Clarissa writes:

SAVE FILE SYSTEM

Requirements:

program SaveSystem

memory save dedicated
memory player dedicated

slots:
    save_slots
    selected_slot
    player_health
    player_position
    saved_health
    saved_position
    saving
    loading

Must include:

collection save_slots
for loop
each loop
manual errors:
    SaveCorrupt
    SaveMissing
    SaveComplete
    LoadComplete

routes:
    save to validate
    validate to load
    load to shutdown

permissions
dedicated memory
at least one parallel validation

Bonus:

concurrent
    path autosave
    path gameplay
end

Sherita says:

“And if your autosave changes player data while gameplay changes player data with no lock…”

She points to the race condition monster.

The class groans.

Sherita smiles.

“He waits.”

---

Closing Scene

The bell rings.

Clarissa closes her laptop.

“Replay systems teach one of the most important programming lessons.”

She writes:

State over time must be explicit.

Sherita adds underneath:

The past needs structure.

Clarissa looks at it and nods.

“That one can stay.”

The projector fades to:

Foresette Academy

Record clearly.
Validate honestly.
Replay deterministically.



## --- ##



Foresette Academy — Class Seven

Save Systems, Persistent State, Validation, and Autosave Safety

Instructor: Clarissa Taylor
Assistant Instructor: Sherita Pleasant

---

8:53 A.M. — The Save File Graveyard

The students walk in.

On the board, Sherita has drawn a tiny cemetery.

Each tombstone says:

save1
save2
final_FINAL
real_final
dont_delete

Clarissa Taylor stares at the board.

“Is this supposed to be a lesson?”

Sherita nods solemnly.

“This is what happens when save files have no structure.”

The class laughs.

Clarissa opens her laptop.

“Today we are learning save systems. A save system captures important program state, validates it, restores it, and handles failure explicitly.”

Sherita points at the board.

“And hopefully avoids the haunted folder of doom.”

---

Lesson 1 — Save System Requirements

Clarissa writes:

program SaveSystem

memory save dedicated
memory player dedicated

Required slots:

save_slots
selected_slot
player_health
player_position
saved_health
saved_position
saving
loading

Required features:

collection save_slots
for loop
each loop
manual errors:
    SaveCorrupt
    SaveMissing
    SaveComplete
    LoadComplete

routes:
    save to validate
    validate to load
    load to shutdown

permissions
dedicated memory
parallel validation

Bonus:

concurrent
    path autosave
    path gameplay
end

Clarissa says:

“Today’s idea is persistence. A program does not only run. Sometimes it must remember.”

---

Lesson 2 — Basic Save Memory

program SaveSystem

external puts
native c

error SaveCorrupt
    slot reason
end

error SaveMissing
    slot reason
end

error SaveComplete
    slot reason
end

error LoadComplete
    slot reason
end

entry main
    memory save dedicated
    memory player dedicated

    slot save_slots from save assign [0, 1, 2]
    slot selected_slot from save assign 0

    slot player_health from player assign 100
    slot player_position from player assign 5

    slot saved_health from save assign 0
    slot saved_position from save assign 0

    slot saving from save assign true
    slot loading from save assign false

    return 0
end

Clarissa explains:

save_slots

represents available save positions.

selected_slot

chooses which save position to use.

player_health
player_position

are live game state.

saved_health
saved_position

are stored state.

Sherita says:

“Live player is today. Saved player is yesterday in a jar.”

Clarissa pauses.

“That is strange, but accurate.”

---

Lesson 3 — Save Permissions

Clarissa asks:

“What permissions are needed?”

The class builds:

permit read save_slots

permit read selected_slot
permit change selected_slot

permit read player_health
permit change player_health

permit read player_position
permit change player_position

permit read saved_health
permit change saved_health

permit read saved_position
permit change saved_position

permit read saving
permit change saving

permit read loading
permit change loading

Sherita adds:

“If autosave and gameplay both touch these later, we need share too.”

Clarissa nods.

“Correct. Concurrency changes the authority story.”

---

Lesson 4 — Routes

Clarissa writes:

route save to validate
route validate to load
route load to shutdown

She draws:

SAVE
  ↓
VALIDATE
  ↓
LOAD
  ↓
SHUTDOWN

“This is the save lifecycle.”

Sherita says:

“Save first. Check it. Then load it. Do not load mysterious swamp data.”

---

Lesson 5 — Saving State

Basic save:

while saving
    saved_health assign player_health
    saved_position assign player_position

    handle SaveComplete
        slot reason assign "Save complete."
        delegate reason to puts
        saving assign false
        loading assign true
    end
end

Clarissa says:

“This copies live state into saved state.”

Sherita says:

“The player got photocopied. Respectfully.”

---

Lesson 6 — Loading State

while loading
    player_health assign saved_health
    player_position assign saved_position

    handle LoadComplete
        slot reason assign "Load complete."
        delegate reason to puts
        loading assign false
    end
end

Clarissa says:

“Loading restores saved state into live state.”

Sherita adds:

“Yesterday-in-a-jar becomes today again.”

Clarissa quietly says:

“We are not keeping that phrase.”

The class votes to keep it.

---

Lesson 7 — SaveMissing

Clarissa changes:

slot selected_slot assign 5
slot save_slots assign [0, 1, 2]

Selected slot 5 does not exist.

We check:

slot found assign false

permit read found
permit change found

each slot_id from save_slots
    if selected_slot == slot_id
        found assign true
    end
end

if found == false
    handle SaveMissing
        slot reason assign "Selected save slot does not exist."
        delegate reason to puts
        stop
    end
end

Sherita says:

“You cannot load from slot five when the building only has floors zero, one, and two.”

---

Lesson 8 — For Loop Slot Validation

Clarissa writes:

for i from 0 to 3
    slot slot_id assign save_slots[i]

    if slot_id < 0
        handle SaveCorrupt
            slot reason assign "Save slot index corrupt."
            delegate reason to puts
            stop
        end
    end
end

Clarissa says:

“Use "for" when the index matters.”

Sherita says:

“Numbered march again. Clipboards out.”

---

Lesson 9 — SaveCorrupt

Saved values can be invalid.

if saved_health < 0
    handle SaveCorrupt
        slot reason assign "Saved health is corrupt."
        delegate reason to puts
        stop
    end
end

Position can also be invalid:

if saved_position < 0
    handle SaveCorrupt
        slot reason assign "Saved position is corrupt."
        delegate reason to puts
        stop
    end
end

Clarissa says:

“The program defines what corruption means.”

Sherita says:

“If your saved player has negative health and lives under the floor, something happened.”

---

Lesson 10 — Parallel Validation

Clarissa introduces the required parallel validation.

parallel
    if saved_health < 0
        handle SaveCorrupt
            slot reason assign "Saved health is corrupt."
            delegate reason to puts
            stop
        end
    end

    if saved_position < 0
        handle SaveCorrupt
            slot reason assign "Saved position is corrupt."
            delegate reason to puts
            stop
        end
    end
end

Clarissa says:

“This is safe because health and position are separate read checks.”

Sherita says:

“Two guards checking two doors.”

---

Lesson 11 — Full SaveSystem Core

Clarissa displays:

program SaveSystemCore

external puts
native c

error SaveCorrupt
    slot reason
end

error SaveMissing
    slot reason
end

error SaveComplete
    slot reason
end

error LoadComplete
    slot reason
end

entry main
    memory save dedicated
    memory player dedicated

    slot save_slots from save assign [0, 1, 2]
    slot selected_slot from save assign 0

    slot player_health from player assign 100
    slot player_position from player assign 5

    slot saved_health from save assign 0
    slot saved_position from save assign 0

    slot saving from save assign true
    slot loading from save assign false

    permit read save_slots

    permit read selected_slot
    permit change selected_slot

    permit read player_health
    permit change player_health

    permit read player_position
    permit change player_position

    permit read saved_health
    permit change saved_health

    permit read saved_position
    permit change saved_position

    permit read saving
    permit change saving

    permit read loading
    permit change loading

    route save to validate
    route validate to load
    route load to shutdown

    slot found assign false
    permit read found
    permit change found

    each slot_id from save_slots
        if selected_slot == slot_id
            found assign true
        end
    end

    if found == false
        handle SaveMissing
            slot reason assign "Selected save slot does not exist."
            delegate reason to puts
            stop
        end
    end

    while saving
        saved_health assign player_health
        saved_position assign player_position

        handle SaveComplete
            slot reason assign "Save complete."
            delegate reason to puts
            saving assign false
            loading assign true
        end
    end

    parallel
        if saved_health < 0
            handle SaveCorrupt
                slot reason assign "Saved health is corrupt."
                delegate reason to puts
                stop
            end
        end

        if saved_position < 0
            handle SaveCorrupt
                slot reason assign "Saved position is corrupt."
                delegate reason to puts
                stop
            end
        end
    end

    while loading
        player_health assign saved_health
        player_position assign saved_position

        handle LoadComplete
            slot reason assign "Load complete."
            delegate reason to puts
            loading assign false
        end
    end

    return 0
end

Clarissa says:

“This is a complete save-load cycle.”

Sherita says:

“It checks the slot, saves the player, validates the save, loads the player, and exits without summoning folder ghosts.”

---

Lesson 12 — Hidden Issue: Infinite While Loops

Clarissa asks:

“What prevents the "while saving" loop from repeating forever?”

A student says:

“"saving assign false" inside the handler.”

Clarissa nods.

“And what about "while loading"?”

Another student says:

“"loading assign false".”

“Correct.”

Sherita says:

“If a loop has no exit, it becomes a treadmill with legal paperwork.”

---

Lesson 13 — Save Complete as Event

Clarissa says:

“This part matters.”

handle SaveComplete
    slot reason assign "Save complete."
    delegate reason to puts
    saving assign false
    loading assign true
end

Why use an event?

Because completion is meaningful.

It changes program route:

saving false
loading true

Sherita says:

“Completion is not nothing. It flips the story.”

---

Lesson 14 — Autosave Concurrency

Clarissa writes:

concurrent
    path autosave
    path gameplay
end

Then she warns:

“Autosave and gameplay may touch the same player state.”

Unsafe:

concurrent
    path autosave
        saved_health assign player_health
    end

    path gameplay
        player_health assign player_health - 10
    end
end

Problem:

autosave reads player_health
gameplay changes player_health
no synchronization

Sherita points to the race condition monster drawing she has taped to the wall.

“He heard that.”

---

Lesson 15 — Safe Autosave

Needed permissions:

permit share player_health
permit share player_position

permit share saved_health
permit share saved_position

Safe pattern:

concurrent
    path autosave
        lock player_health
        lock player_position

        saved_health assign player_health
        saved_position assign player_position

        unlock player_position
        unlock player_health

        signal save_done
    end

    path gameplay
        lock player_health
        player_health assign player_health - 10
        unlock player_health

        wait save_done
    end
end

Clarissa says:

“This coordinates shared state.”

Sherita says:

“Autosave takes the picture. Gameplay waits before throwing a chair.”

---

Lesson 16 — Lock Ordering

Clarissa writes:

lock player_health
lock player_position

Then:

unlock player_position
unlock player_health

“This is deliberate.”

If one path locks health then position, every path should lock in the same order.

Bad:

path one:
    lock player_health
    lock player_position

path two:
    lock player_position
    lock player_health

This can deadlock.

Sherita draws two stick figures holding each other’s backpacks.

“Neither can leave.”

Clarissa says:

“That is deadlock.”

Sherita adds:

“Backpack doom.”

---

Lesson 17 — Full SaveSystem Pro With Autosave

program SaveSystemPro

external puts
native c

error SaveCorrupt
    slot reason
end

error SaveMissing
    slot reason
end

error SaveComplete
    slot reason
end

error LoadComplete
    slot reason
end

entry main
    memory save dedicated
    memory player dedicated

    slot save_slots from save assign [0, 1, 2]
    slot selected_slot from save assign 0

    slot player_health from player assign 100
    slot player_position from player assign 5

    slot saved_health from save assign 0
    slot saved_position from save assign 0

    slot saving from save assign true
    slot loading from save assign false

    permit read save_slots

    permit read selected_slot
    permit change selected_slot

    permit read player_health
    permit change player_health
    permit share player_health

    permit read player_position
    permit change player_position
    permit share player_position

    permit read saved_health
    permit change saved_health
    permit share saved_health

    permit read saved_position
    permit change saved_position
    permit share saved_position

    permit read saving
    permit change saving

    permit read loading
    permit change loading

    route save to validate
    route validate to load
    route load to shutdown

    slot found assign false
    permit read found
    permit change found

    each slot_id from save_slots
        if selected_slot == slot_id
            found assign true
        end
    end

    if found == false
        handle SaveMissing
            slot reason assign "Selected save slot does not exist."
            delegate reason to puts
            stop
        end
    end

    concurrent
        path autosave
            lock player_health
            lock player_position

            saved_health assign player_health
            saved_position assign player_position

            unlock player_position
            unlock player_health

            signal save_done
        end

        path gameplay
            lock player_health
            player_health assign player_health - 10
            unlock player_health

            wait save_done
        end
    end

    parallel
        if saved_health < 0
            handle SaveCorrupt
                slot reason assign "Saved health is corrupt."
                delegate reason to puts
                stop
            end
        end

        if saved_position < 0
            handle SaveCorrupt
                slot reason assign "Saved position is corrupt."
                delegate reason to puts
                stop
            end
        end
    end

    while loading
        player_health assign saved_health
        player_position assign saved_position

        handle LoadComplete
            slot reason assign "Load complete."
            delegate reason to puts
            loading assign false
        end
    end

    return 0
end

Clarissa says:

“This is a safe autosave skeleton.”

Sherita says:

“It saves while gameplay happens, but nobody snatches the same variable without knocking.”

---

Lesson 18 — Compiler View

Clarissa projects:

Memory Table

save:
    save_slots
    selected_slot
    saved_health
    saved_position
    saving
    loading

player:
    player_health
    player_position

Permission Table:

player_health:
    read
    change
    share

player_position:
    read
    change
    share

saved_health:
    read
    change
    share

saved_position:
    read
    change
    share

Execution Table:

main
 ├─ validate selected slot
 ├─ concurrent autosave/gameplay
 │   ├─ autosave locks player state
 │   └─ gameplay locks player health
 ├─ parallel save validation
 ├─ load saved state
 └─ return

Clarissa says:

“The compiler sees which state is shared, when it is locked, and where it moves.”

---

Lesson 19 — Professional Save Habits

Clarissa writes:

Validate the selected slot.
Validate saved values before loading.
Name save failures.
Name completion events.
Use routes for lifecycle.
Use locks for autosave/gameplay overlap.
Use consistent lock order.
Never expose private save data casually.
Keep live state and saved state separate.

Sherita adds:

Do not name files final_FINAL_REAL_2.

The class laughs.

---

Lesson 20 — Homework: Settings System

Clarissa writes the next assignment:

SETTINGS SYSTEM

Requirements:

program SettingsSystem

memory settings dedicated

slots:
    volume
    brightness
    difficulty
    valid_difficulties
    selected_difficulty
    applying

Must include:

collection valid_difficulties
each loop
for loop
manual errors:
    InvalidSetting
    ApplyComplete

permissions
dedicated memory

route edit to validate
route validate to apply
route apply to shutdown

Bonus:

parallel
    validate volume
    validate brightness
    validate difficulty
end

Super bonus:

concurrent
    path ui
    path apply_worker
end

Sherita says:

“And if your brightness is 5000, your monitor becomes a small sun.”

Clarissa says:

“Not technically.”

Sherita whispers:

“Emotionally.”

---

Closing Scene

The bell rings.

Clarissa looks over the class.

“Today you learned that save systems are not just storage. They are trust.”

She writes:

A save file must be:
    selected
    written
    validated
    loaded
    completed

Sherita adds:

and not haunted

Clarissa lets it stay.

The projector fades to:

Foresette Academy

Persistent state must be explicit.
Shared saves must be synchronized.
Corruption must be named.



## --- ##



Foresette Academy — Class Eight

Settings, Constraints, Validation Paths, and Controlled Application

Instructor: Clarissa Taylor
Assistant Instructor: Sherita Pleasant

---

8:52 A.M. — Brightness 5000

The students enter the classroom.

The projector is completely white.

Not a normal white.

A violent, glowing rectangle of pure brightness.

Several students squint.

One immediately shields his eyes with a notebook.

Clarissa Taylor walks into the room.

She stops.

“Sherita.”

Sherita Pleasant is standing beside the projector controls.

“Yes?”

“What is the brightness set to?”

Sherita checks.

“Five thousand.”

Clarissa stares at her.

“The projector does not go to five thousand.”

Sherita nods.

“Exactly. Today's lesson.”

Clarissa slowly reaches over and turns the projector down.

The class laughs.

Clarissa places her laptop on the desk.

“Today, we are learning constraints.”

Sherita says:

“Because apparently the universe needs boundaries.”

Clarissa writes:

VALIDATE BEFORE APPLY

“Settings look simple. They are not.”

---

Lesson 1 — Settings System Requirements

Clarissa displays the homework requirements.

program SettingsSystem

memory settings dedicated

slots:
    volume
    brightness
    difficulty
    valid_difficulties
    selected_difficulty
    applying

Required:

collection valid_difficulties
each loop
for loop

manual errors:
    InvalidSetting
    ApplyComplete

permissions
dedicated memory

route edit to validate
route validate to apply
route apply to shutdown

Bonus:

parallel
    validate volume
    validate brightness
    validate difficulty
end

Super bonus:

concurrent
    path ui
    path apply_worker
end

Clarissa says:

“The main rule is simple.”

She points to the board.

EDIT
  ↓
VALIDATE
  ↓
APPLY

Sherita adds:

“Not edit, panic, apply, apologize.”

---

Lesson 2 — Basic Settings Memory

Clarissa types:

program SettingsSystem

external puts
native c

error InvalidSetting
    slot reason
end

error ApplyComplete
    slot reason
end

entry main
    memory settings dedicated

    slot volume from settings assign 70
    slot brightness from settings assign 50
    slot difficulty from settings assign "normal"

    slot valid_difficulties from settings assign [
        "easy",
        "normal",
        "hard"
    ]

    slot selected_difficulty from settings assign "normal"
    slot applying from settings assign false

    return 0
end

Clarissa says:

“This is our settings state.”

Sherita walks toward the board.

settings
 ├─ volume
 ├─ brightness
 ├─ difficulty
 ├─ valid_difficulties
 ├─ selected_difficulty
 └─ applying

“Everybody lives in the settings neighborhood.”

---

Lesson 3 — What Is a Constraint?

Clarissa writes:

volume >= 0
volume <= 100

“That is a constraint.”

Then:

brightness >= 0
brightness <= 100

Another constraint.

Then:

difficulty must exist in valid_difficulties

Another constraint.

Clarissa says:

“A constraint defines acceptable state.”

Sherita says:

“It tells your number where the fence is.”

---

Lesson 4 — Foresette Does Not Invent Constraints

Clarissa writes:

slot volume assign 900

She asks:

“Is nine hundred a valid volume?”

The class says:

“No.”

“Does the compiler automatically know that?”

The class pauses.

“No.”

Clarissa nods.

“Correct.”

Foresette knows:

volume = 900

It does not know:

your application considers 900 invalid

You define that logic.

if volume < 0
    handle InvalidSetting
        ...
    end
end

if volume > 100
    handle InvalidSetting
        ...
    end
end

Sherita says:

“The compiler knows math. It does not know your volume knob.”

---

Lesson 5 — Volume Validation

Clarissa writes:

if volume < 0
    handle InvalidSetting
        slot reason assign "Volume is below zero."
        delegate reason to puts
        stop
    end
end

if volume > 100
    handle InvalidSetting
        slot reason assign "Volume exceeds maximum."
        delegate reason to puts
        stop
    end
end

She asks:

“What permission does validation require?”

A student answers:

permit read volume

“Correct.”

Sherita says:

“We're inspecting. Not touching.”

---

Lesson 6 — Brightness Validation

if brightness < 0
    handle InvalidSetting
        slot reason assign "Brightness is below zero."
        delegate reason to puts
        stop
    end
end

if brightness > 100
    handle InvalidSetting
        slot reason assign "Brightness exceeds maximum."
        delegate reason to puts
        stop
    end
end

Sherita raises her hand.

“What about five thousand?”

Clarissa replies:

“Invalid.”

Sherita nods.

“Research complete.”

---

Lesson 7 — Difficulty Validation

Clarissa writes:

slot valid_difficulties assign [
    "easy",
    "normal",
    "hard"
]

Selected:

slot selected_difficulty assign "hard"

We need to check whether the selected difficulty exists.

slot difficulty_found assign false

permit read difficulty_found
permit change difficulty_found

each option from valid_difficulties
    if selected_difficulty == option
        difficulty_found assign true
    end
end

Then:

if difficulty_found == false
    handle InvalidSetting
        slot reason assign "Difficulty is invalid."
        delegate reason to puts
        stop
    end
end

Sherita says:

“If you choose "ultra-mega-nightmare-banana", the list says no.”

A student asks:

“Can we add that difficulty?”

Clarissa says:

“If you explicitly define it.”

Sherita points.

“That's Foresette.”

---

Lesson 8 — The Collection Is the Authority

Clarissa circles:

valid_difficulties

“The valid options are data.”

["easy", "normal", "hard"]

This means the program does not need:

if easy
if normal
if hard

The collection defines acceptable options.

Sherita says:

“The list is the guest list.”

Clarissa nods.

“That is actually a good analogy.”

Sherita quietly celebrates.

---

Lesson 9 — Each Versus For Again

Clarissa writes:

each option from valid_difficulties

Use "each" when:

visit every value
index does not matter

Then:

for i from 0 to 3

Use "for" when:

index matters
position matters
number of iterations matters

Example:

for i from 0 to 3
    slot option assign valid_difficulties[i]
    delegate option with read to display_option
end

Sherita says:

“Each says, ‘show me everybody.’ For says, ‘seat numbers, please.’”

---

Lesson 10 — Permissions

Clarissa builds the permission table.

permit read volume
permit change volume

permit read brightness
permit change brightness

permit read difficulty
permit change difficulty

permit read valid_difficulties

permit read selected_difficulty
permit change selected_difficulty

permit read applying
permit change applying

Clarissa asks:

“Why does "valid_difficulties" not need change permission?”

A student answers:

“Because we do not change it.”

“Exactly.”

Sherita says:

“Do not hand out keys nobody needs.”

---

Lesson 11 — Least Permission

Clarissa writes:

LEAST PERMISSION

She explains:

“If a slot only needs to be read, grant read.”

permit read valid_difficulties

Do not automatically write:

permit change valid_difficulties
permit share valid_difficulties
permit expose valid_difficulties
permit move valid_difficulties

Sherita says:

“That is like giving the pizza delivery person your house key, car key, and birth certificate.”

The class laughs.

Clarissa says:

“Excessive, but correct.”

---

Lesson 12 — Editing Versus Applied State

Clarissa says:

“Now we improve the system.”

She creates two sets of values.

slot volume from settings assign 70
slot brightness from settings assign 50
slot difficulty from settings assign "normal"

These are applied settings.

Then:

slot selected_volume from settings assign 85
slot selected_brightness from settings assign 65
slot selected_difficulty from settings assign "hard"

These are edited settings.

Clarissa draws:

SELECTED STATE
      ↓
  VALIDATION
      ↓
APPLIED STATE

Sherita says:

“Shopping cart versus checkout.”

Clarissa points at her.

“Exactly.”

---

Lesson 13 — Why Staged State Matters

Bad design:

volume assign user_input

The invalid value immediately becomes live.

Better:

selected_volume assign user_input

Validate:

if selected_volume >= 0
    if selected_volume <= 100
        volume assign selected_volume
    end
end

Clarissa says:

“Staged state protects live state.”

Sherita says:

“Do not install the weird setting before checking whether it is weird.”

---

Lesson 14 — Route Lifecycle

Clarissa writes:

route edit to validate
route validate to apply
route apply to shutdown

Then:

EDIT
  |
  v
selected_volume = 85
selected_brightness = 65
selected_difficulty = "hard"
  |
  v
VALIDATE
  |
  v
APPLY
  |
  v
volume = 85
brightness = 65
difficulty = "hard"

Clarissa says:

“The route describes state transition.”

Sherita says:

“The settings have a travel itinerary.”

---

Lesson 15 — Parallel Validation

Clarissa displays:

parallel
    if selected_volume < 0
        handle InvalidSetting
            slot reason assign "Volume below zero."
            delegate reason to puts
            stop
        end
    end

    if selected_volume > 100
        handle InvalidSetting
            slot reason assign "Volume above maximum."
            delegate reason to puts
            stop
        end
    end

    if selected_brightness < 0
        handle InvalidSetting
            slot reason assign "Brightness below zero."
            delegate reason to puts
            stop
        end
    end

    if selected_brightness > 100
        handle InvalidSetting
            slot reason assign "Brightness above maximum."
            delegate reason to puts
            stop
        end
    end
end

Clarissa says:

“These validations are independent reads.”

Sherita says:

“Four inspectors. Nobody touches anything.”

---

Lesson 16 — Parallel Difficulty Validation Problem

A student writes:

parallel
    each option from valid_difficulties
        if selected_difficulty == option
            difficulty_found assign true
        end
    end
end

Clarissa pauses.

“What problem might exist?”

A student answers:

“Multiple parallel iterations could change "difficulty_found".”

“Correct.”

Shared mutation.

Sherita slowly points toward the wall.

The race condition monster drawing is still taped there.

“He remains employed.”

---

Lesson 17 — Avoid Shared Mutation

Clarissa says:

“The cleanest solution is often not a lock.”

She writes:

slot easy_match assign selected_difficulty == "easy"
slot normal_match assign selected_difficulty == "normal"
slot hard_match assign selected_difficulty == "hard"

Then:

slot difficulty_found assign easy_match or normal_match or hard_match

Sherita says:

“Three answers. Merge them.”

Clarissa nods.

“Separate work, then combine.”

This is a common performance pattern:

split
compute
merge

---

Lesson 18 — The Split-Compute-Merge Pattern

Clarissa writes:

SPLIT
  ↓
COMPUTE
  ↓
MERGE

Example:

parallel
    slot volume_valid assign selected_volume >= 0
    slot brightness_valid assign selected_brightness >= 0
    slot difficulty_valid assign difficulty_found
end

Then:

slot settings_valid assign
    volume_valid
    and brightness_valid
    and difficulty_valid

Sherita says:

“Everybody does their homework separately. Then we compare answers.”

Clarissa says:

“Without copying.”

Sherita says:

“Right. Academic merge.”

---

Lesson 19 — Applying Settings

Once validation succeeds:

applying assign true

Then:

when applying
    volume assign selected_volume
    brightness assign selected_brightness
    difficulty assign selected_difficulty

    handle ApplyComplete
        slot reason assign "Settings applied."
        delegate reason to puts
        applying assign false
    end
end

Clarissa says:

“The live settings change only after validation.”

Sherita says:

“Checkout complete.”

---

Lesson 20 — Full SettingsSystem Core

Clarissa projects:

program SettingsSystemCore

external puts
native c

error InvalidSetting
    slot reason
end

error ApplyComplete
    slot reason
end

entry main
    memory settings dedicated

    slot volume from settings assign 70
    slot brightness from settings assign 50
    slot difficulty from settings assign "normal"

    slot selected_volume from settings assign 85
    slot selected_brightness from settings assign 65
    slot selected_difficulty from settings assign "hard"

    slot valid_difficulties from settings assign [
        "easy",
        "normal",
        "hard"
    ]

    slot applying from settings assign false

    permit read volume
    permit change volume

    permit read brightness
    permit change brightness

    permit read difficulty
    permit change difficulty

    permit read selected_volume
    permit change selected_volume

    permit read selected_brightness
    permit change selected_brightness

    permit read selected_difficulty
    permit change selected_difficulty

    permit read valid_difficulties

    permit read applying
    permit change applying

    route edit to validate
    route validate to apply
    route apply to shutdown

    slot difficulty_found assign false

    permit read difficulty_found
    permit change difficulty_found

    each option from valid_difficulties
        if selected_difficulty == option
            difficulty_found assign true
        end
    end

    parallel
        if selected_volume < 0
            handle InvalidSetting
                slot reason assign "Volume below zero."
                delegate reason to puts
                stop
            end
        end

        if selected_volume > 100
            handle InvalidSetting
                slot reason assign "Volume above maximum."
                delegate reason to puts
                stop
            end
        end

        if selected_brightness < 0
            handle InvalidSetting
                slot reason assign "Brightness below zero."
                delegate reason to puts
                stop
            end
        end

        if selected_brightness > 100
            handle InvalidSetting
                slot reason assign "Brightness above maximum."
                delegate reason to puts
                stop
            end
        end
    end

    if difficulty_found == false
        handle InvalidSetting
            slot reason assign "Difficulty is invalid."
            delegate reason to puts
            stop
        end
    end

    applying assign true

    when applying
        volume assign selected_volume
        brightness assign selected_brightness
        difficulty assign selected_difficulty

        handle ApplyComplete
            slot reason assign "Settings applied."
            delegate reason to puts
            applying assign false
        end
    end

    return 0
end

Clarissa says:

“This is a clean staged settings system.”

Sherita says:

“Edit. Inspect. Approve. Apply. No tiny sun.”

---

Lesson 21 — Concurrent UI and Apply Worker

Clarissa introduces the super bonus.

concurrent
    path ui
    path apply_worker
end

The UI edits selected state.

The worker applies validated state.

Unsafe:

concurrent
    path ui
        selected_volume assign 90
    end

    path apply_worker
        volume assign selected_volume
    end
end

Clarissa asks:

“What is wrong?”

The class answers:

“The worker may read while UI changes the value.”

“Correct.”

Sherita says:

“The worker might apply eighty-five, ninety, or a value caught halfway through the drama.”

---

Lesson 22 — Snapshot Before Apply

Clarissa shows the professional pattern.

slot apply_volume assign selected_volume
slot apply_brightness assign selected_brightness
slot apply_difficulty assign selected_difficulty

These are snapshots.

Then:

signal settings_snapshot_ready

Worker:

wait settings_snapshot_ready

volume assign apply_volume
brightness assign apply_brightness
difficulty assign apply_difficulty

Clarissa says:

“Snapshot state creates a stable application boundary.”

Sherita says:

“Take the picture. Then use the picture.”

---

Lesson 23 — Full Concurrent Pattern

permit share selected_volume
permit share selected_brightness
permit share selected_difficulty

concurrent
    path ui
        lock selected_volume
        lock selected_brightness
        lock selected_difficulty

        selected_volume assign 85
        selected_brightness assign 65
        selected_difficulty assign "hard"

        slot apply_volume assign selected_volume
        slot apply_brightness assign selected_brightness
        slot apply_difficulty assign selected_difficulty

        unlock selected_difficulty
        unlock selected_brightness
        unlock selected_volume

        signal settings_snapshot_ready
    end

    path apply_worker
        wait settings_snapshot_ready

        volume assign apply_volume
        brightness assign apply_brightness
        difficulty assign apply_difficulty

        signal settings_applied
    end
end

Clarissa says:

“This creates a stable handoff.”

Sherita says:

“UI packs the lunch. Worker takes the lunch. Nobody edits the sandwich mid-bite.”

---

Lesson 24 — Compiler View

Clarissa projects:

Memory Table

settings:
    volume
    brightness
    difficulty

    selected_volume
    selected_brightness
    selected_difficulty

    valid_difficulties
    applying

State categories:

APPLIED
    volume
    brightness
    difficulty

STAGED
    selected_volume
    selected_brightness
    selected_difficulty

CONSTRAINT
    valid_difficulties

CONTROL
    applying

Execution graph:

edit
  ↓
difficulty collection validation
  ↓
parallel numeric validation
  ↓
apply enabled
  ↓
copy staged state to applied state
  ↓
ApplyComplete
  ↓
shutdown

Clarissa says:

“Clear categories make compiler reasoning and human reasoning easier.”

---

Lesson 25 — What LLVM Can See

Clarissa writes:

selected_volume = 85

Validation:

selected_volume < 0
selected_volume > 100

Because 85 is known at compile time in this example, LLVM can prove:

85 < 0 = false
85 > 100 = false

Those branches may disappear.

Sherita says:

“The compiler checked the homework before runtime.”

Clarissa nods.

“If the value is compile-time known.”

She adds:

“Runtime user input still requires runtime validation.”

---

Lesson 26 — Zero-Guess Does Not Mean Zero Optimization

Clarissa writes:

ZERO-GUESS
≠
ZERO-OPTIMIZATION

She explains:

“Foresette avoids guessing programmer intent.”

LLVM can still prove mathematical and control-flow facts.

Foresette says:

Here is the meaning.
Here is the authority.
Here is the path.

LLVM says:

Given those facts,
this work is unnecessary.

Sherita says:

“Foresette gives LLVM a clean room. LLVM starts moving furniture.”

---

Lesson 27 — Class Challenge

Clarissa displays:

slot selected_volume assign 150
slot selected_brightness assign 40
slot selected_difficulty assign "legend"

Valid difficulties:

["easy", "normal", "hard"]

“What fails?”

The class answers:

selected_volume > 100

selected_difficulty not in valid_difficulties

“What passes?”

selected_brightness = 40

Clarissa asks:

“Should any setting apply?”

The class says:

“No.”

“Correct.”

Sherita says:

“One bad suitcase stops the whole luggage cart.”

---

Lesson 28 — Atomic Application Thinking

Clarissa writes:

ALL VALID
    ↓
APPLY ALL

Not:

volume valid
apply volume

brightness invalid
stop

difficulty never checked

That creates partially applied settings.

Professional approach:

validate volume
validate brightness
validate difficulty

if all valid
    apply everything
end

Sherita says:

“Do not change half the settings and then faint.”

---

Lesson 29 — Professional Settings Habits

Clarissa writes:

Separate staged state from applied state.

Validate before applying.

Use collections for allowed options.

Grant least permission.

Do not mutate live settings during validation.

Snapshot concurrent edits.

Apply settings atomically.

Name invalid state.

Name successful completion.

Use routes for lifecycle.

Sherita adds:

Brightness 5000 is forbidden.

Clarissa says:

“That is application-specific.”

Sherita underlines it anyway.

---

Lesson 30 — Homework: Resource Loader

Clarissa changes the projector.

RESOURCE LOADER

The room gets quieter.

“This is your first step toward engine infrastructure.”

Requirements:

program ResourceLoader

memory resources dedicated
memory loader dedicated

slots:
    resource_names
    resource_states
    current_resource
    loading
    loaded_count

Resource states:

"waiting"
"loading"
"loaded"
"failed"

Must include:

collection resource_names
collection resource_states

each loop
for loop

manual errors:
    ResourceMissing
    ResourceFailed
    LoadComplete

routes:
    discover to validate
    validate to load
    load to finalize
    finalize to shutdown

permissions
dedicated memory

parallel:
    validate independent resources

Bonus:

concurrent
    path disk_loader
    path texture_loader
    path audio_loader
end

Super bonus:

signals:
    texture_ready
    audio_ready
    all_resources_ready

Clarissa says:

“You are going to build a loader that knows what exists, what is waiting, what is loading, what succeeded, and what failed.”

Sherita grins.

“And if you write "slot resources assign everything"…”

She shakes her head.

“I will find you.”

---

Closing Scene

The bell rings.

Nobody moves immediately.

Clarissa points to the board.

EDIT
VALIDATE
APPLY

“Those three words exist far beyond settings systems.”

She adds:

REQUEST
VERIFY
COMMIT

“Databases use similar thinking.”

INPUT
CHECK
EXECUTE

“Security systems use similar thinking.”

BUILD
VALIDATE
DEPLOY

“Software pipelines use similar thinking.”

Sherita looks around the classroom.

“Basically, check your stuff before you release it into society.”

Clarissa smiles.

“Yes.”

The students begin packing their laptops.

The projector fades.

FORESETTE ACADEMY

State the constraint.
Validate the candidate.
Apply the truth.

Sherita reaches for the projector remote.

Clarissa immediately says:

“No.”

Sherita slowly puts it back.

The class erupts laughing.



## --- ##



Foresette Academy — Class Nine

Resource Loading, State Tables, Parallel Validation, and Concurrent Asset Pipelines

Instructor: Clarissa Taylor
Assistant Instructor: Sherita Pleasant

---

8:51 A.M. — The Missing Texture Incident

The classroom projector shows a giant gray square.

Under it:

missing_texture.png

Sherita Pleasant stands beside the screen, looking dramatic.

Clarissa Taylor enters.

“Why is there a gray square on my board?”

Sherita says:

“It’s not a square. It’s emotional damage from a failed resource loader.”

The class laughs.

Clarissa sets down her laptop.

“Today, we learn how a program finds, validates, loads, and finalizes resources.”

Sherita points at the gray square.

“So nobody has to stare at this poor rectangle of disappointment.”

---

Lesson 1 — Resource Loader Requirements

Clarissa writes:

program ResourceLoader

memory resources dedicated
memory loader dedicated

Required slots:

resource_names
resource_states
current_resource
loading
loaded_count

Resource states:

"waiting"
"loading"
"loaded"
"failed"

Required features:

collection resource_names
collection resource_states

each loop
for loop

manual errors:
    ResourceMissing
    ResourceFailed
    LoadComplete

routes:
    discover to validate
    validate to load
    load to finalize
    finalize to shutdown

permissions
dedicated memory

parallel:
    validate independent resources

Bonus:

concurrent
    path disk_loader
    path texture_loader
    path audio_loader
end

Super bonus:

signals:
    texture_ready
    audio_ready
    all_resources_ready

Clarissa says:

“A loader is a truth machine.”

Sherita adds:

“It asks: what do we need, does it exist, did it load, and are we done panicking?”

---

Lesson 2 — Basic Resource Memory

program ResourceLoader

external puts
native c

error ResourceMissing
    slot reason
end

error ResourceFailed
    slot reason
end

error LoadComplete
    slot reason
end

entry main
    memory resources dedicated
    memory loader dedicated

    slot resource_names from resources assign [
        "player.png",
        "enemy.png",
        "theme.wav"
    ]

    slot resource_states from resources assign [
        "waiting",
        "waiting",
        "waiting"
    ]

    slot current_resource from loader assign 0
    slot loading from loader assign true
    slot loaded_count from loader assign 0

    return 0
end

Clarissa explains:

resource_names

lists what must be loaded.

resource_states

tracks each resource’s status.

current_resource

tracks the loader’s position.

loading

controls the process.

loaded_count

tracks success.

Sherita says:

“Names are the grocery list. States are whether the groceries made it home.”

---

Lesson 3 — Resource States

Clarissa writes:

"waiting"
"loading"
"loaded"
"failed"

She explains:

waiting

means not started.

loading

means currently being processed.

loaded

means success.

failed

means explicit failure.

Sherita says:

“Every resource needs a mood.”

Clarissa pauses.

“Status.”

Sherita nods.

“Professional mood.”

---

Lesson 4 — Permissions

Clarissa asks:

“What permissions do we need?”

The class builds:

permit read resource_names

permit read resource_states
permit change resource_states

permit read current_resource
permit change current_resource

permit read loading
permit change loading

permit read loaded_count
permit change loaded_count

Clarissa nods.

“And if multiple loader paths touch these?”

The class answers:

permit share resource_states
permit share loaded_count

Sherita says:

“Concurrency means the clipboard becomes communal.”

---

Lesson 5 — Route Lifecycle

Clarissa writes:

route discover to validate
route validate to load
route load to finalize
route finalize to shutdown

She draws:

DISCOVER
   ↓
VALIDATE
   ↓
LOAD
   ↓
FINALIZE
   ↓
SHUTDOWN

Clarissa says:

“Resource loading is a lifecycle.”

Sherita says:

“Not a chaotic folder rummage.”

---

Lesson 6 — Discover Phase

The discover phase defines what resources exist in the plan.

slot resource_names from resources assign [
    "player.png",
    "enemy.png",
    "theme.wav"
]

Clarissa says:

“In this simplified version, discovery is manual.”

In a real loader, discovery could come from:

manifest file
asset folder
build system
package index
engine scene file

Sherita says:

“But Foresette still wants the result stated clearly.”

---

Lesson 7 — Validate Resource Names

Clarissa writes:

each name from resource_names
    if name == ""
        handle ResourceMissing
            slot reason assign "Resource name is empty."
            delegate reason to puts
            stop
        end
    end
end

She says:

“This checks that every resource has a name.”

Sherita says:

“Blank filename is not mysterious. It’s missing.”

---

Lesson 8 — For Loop State Alignment

Clarissa writes:

for i from 0 to 3
    slot name assign resource_names[i]
    slot state assign resource_states[i]
end

She explains:

“The index connects the resource name to its state.”

resource_names[0]  = "player.png"
resource_states[0] = "waiting"

resource_names[1]  = "enemy.png"
resource_states[1] = "waiting"

resource_names[2]  = "theme.wav"
resource_states[2] = "waiting"

Sherita says:

“Same seat number, different clipboard column.”

---

Lesson 9 — Loading One Resource

Clarissa writes:

resource_states[current_resource] assign "loading"

Then:

resource_states[current_resource] assign "loaded"
loaded_count assign loaded_count + 1

Basic pattern:

while loading
    resource_states[current_resource] assign "loading"

    resource_states[current_resource] assign "loaded"
    loaded_count assign loaded_count + 1

    current_resource assign current_resource + 1

    if current_resource >= 3
        loading assign false
    end
end

Sherita says:

“This loader is optimistic. It assumes everything loads. Cute, but naïve.”

---

Lesson 10 — Handling Failure

Clarissa adds failure logic.

if resource_names[current_resource] == "missing.png"
    resource_states[current_resource] assign "failed"

    handle ResourceFailed
        slot reason assign "Resource failed to load."
        delegate reason to puts
        stop
    end
else
    resource_states[current_resource] assign "loaded"
    loaded_count assign loaded_count + 1
end

Clarissa says:

“The failure is named and handled.”

Sherita says:

“The gray square has been legally identified.”

---

Lesson 11 — LoadComplete

When all resources are loaded:

if loaded_count == 3
    handle LoadComplete
        slot reason assign "All resources loaded."
        delegate reason to puts
        loading assign false
    end
end

Clarissa says:

“Completion is an event.”

Sherita says:

“Finished is not just silence. Finished is a state.”

---

Lesson 12 — Basic ResourceLoaderCore

program ResourceLoaderCore

external puts
native c

error ResourceMissing
    slot reason
end

error ResourceFailed
    slot reason
end

error LoadComplete
    slot reason
end

entry main
    memory resources dedicated
    memory loader dedicated

    slot resource_names from resources assign [
        "player.png",
        "enemy.png",
        "theme.wav"
    ]

    slot resource_states from resources assign [
        "waiting",
        "waiting",
        "waiting"
    ]

    slot current_resource from loader assign 0
    slot loading from loader assign true
    slot loaded_count from loader assign 0

    permit read resource_names

    permit read resource_states
    permit change resource_states

    permit read current_resource
    permit change current_resource

    permit read loading
    permit change loading

    permit read loaded_count
    permit change loaded_count

    route discover to validate
    route validate to load
    route load to finalize
    route finalize to shutdown

    each name from resource_names
        if name == ""
            handle ResourceMissing
                slot reason assign "Resource name is empty."
                delegate reason to puts
                stop
            end
        end
    end

    while loading
        resource_states[current_resource] assign "loading"

        if resource_names[current_resource] == "missing.png"
            resource_states[current_resource] assign "failed"

            handle ResourceFailed
                slot reason assign "Resource failed to load."
                delegate reason to puts
                stop
            end
        else
            resource_states[current_resource] assign "loaded"
            loaded_count assign loaded_count + 1
        end

        current_resource assign current_resource + 1

        if loaded_count == 3
            handle LoadComplete
                slot reason assign "All resources loaded."
                delegate reason to puts
                loading assign false
            end
        end
    end

    return 0
end

Clarissa says:

“This is the core loader.”

Sherita says:

“It is small, direct, and finally not emotionally dependent on gray squares.”

---

Lesson 13 — Hidden Issue: Current Resource Bounds

Clarissa asks:

“What if loaded_count never reaches 3?”

The class goes quiet.

A student says:

“"current_resource" could keep increasing.”

Clarissa nods.

“Correct.”

Add a guard:

if current_resource >= 3
    loading assign false
end

Better:

if current_resource >= 3
    if loaded_count == 3
        handle LoadComplete
            slot reason assign "All resources loaded."
            delegate reason to puts
            loading assign false
        end
    else
        handle ResourceFailed
            slot reason assign "Not all resources loaded."
            delegate reason to puts
            stop
        end
    end
end

Sherita says:

“Never let an index wander off into the cornfield.”

---

Lesson 14 — Parallel Validation

Clarissa writes:

parallel
    if resource_names[0] == ""
        handle ResourceMissing
            slot reason assign "Resource 0 missing."
            delegate reason to puts
            stop
        end
    end

    if resource_names[1] == ""
        handle ResourceMissing
            slot reason assign "Resource 1 missing."
            delegate reason to puts
            stop
        end
    end

    if resource_names[2] == ""
        handle ResourceMissing
            slot reason assign "Resource 2 missing."
            delegate reason to puts
            stop
        end
    end
end

Clarissa says:

“This is safe because each validation only reads independent names.”

Sherita says:

“Three inspectors, no shared pencil.”

---

Lesson 15 — Concurrent Loader Paths

Bonus version:

concurrent
    path disk_loader
    path texture_loader
    path audio_loader
end

Clarissa explains:

disk_loader

loads general files.

texture_loader

loads image assets.

audio_loader

loads sound assets.

Sherita says:

“Different workers. Different carts.”

---

Lesson 16 — Shared State Problem

Unsafe:

concurrent
    path texture_loader
        resource_states[0] assign "loaded"
        loaded_count assign loaded_count + 1
    end

    path audio_loader
        resource_states[2] assign "loaded"
        loaded_count assign loaded_count + 1
    end
end

Problem:

loaded_count

is changed by multiple paths.

Clarissa says:

“That requires synchronization.”

Correct:

permit share loaded_count

lock loaded_count
loaded_count assign loaded_count + 1
unlock loaded_count

Sherita points to the wall.

“Race condition monster sees counters.”

---

Lesson 17 — Signals

Super bonus signals:

signal texture_ready
signal audio_ready
signal all_resources_ready

Example:

path texture_loader
    resource_states[0] assign "loaded"
    signal texture_ready
end

path audio_loader
    resource_states[2] assign "loaded"
    signal audio_ready
end

path finalize
    wait texture_ready
    wait audio_ready
    signal all_resources_ready
end

Clarissa says:

“Signals create visible coordination.”

Sherita says:

“No secret vibes. Actual signal.”

---

Lesson 18 — ResourceLoaderPro

program ResourceLoaderPro

external puts
native c

error ResourceMissing
    slot reason
end

error ResourceFailed
    slot reason
end

error LoadComplete
    slot reason
end

entry main
    memory resources dedicated
    memory loader dedicated

    slot resource_names from resources assign [
        "player.png",
        "enemy.png",
        "theme.wav"
    ]

    slot resource_states from resources assign [
        "waiting",
        "waiting",
        "waiting"
    ]

    slot current_resource from loader assign 0
    slot loading from loader assign true
    slot loaded_count from loader assign 0

    permit read resource_names

    permit read resource_states
    permit change resource_states
    permit share resource_states

    permit read current_resource
    permit change current_resource

    permit read loading
    permit change loading

    permit read loaded_count
    permit change loaded_count
    permit share loaded_count

    route discover to validate
    route validate to load
    route load to finalize
    route finalize to shutdown

    parallel
        if resource_names[0] == ""
            handle ResourceMissing
                slot reason assign "Resource 0 missing."
                delegate reason to puts
                stop
            end
        end

        if resource_names[1] == ""
            handle ResourceMissing
                slot reason assign "Resource 1 missing."
                delegate reason to puts
                stop
            end
        end

        if resource_names[2] == ""
            handle ResourceMissing
                slot reason assign "Resource 2 missing."
                delegate reason to puts
                stop
            end
        end
    end

    concurrent
        path texture_loader
            resource_states[0] assign "loading"
            resource_states[0] assign "loaded"

            lock loaded_count
            loaded_count assign loaded_count + 1
            unlock loaded_count

            signal texture_ready
        end

        path enemy_texture_loader
            resource_states[1] assign "loading"
            resource_states[1] assign "loaded"

            lock loaded_count
            loaded_count assign loaded_count + 1
            unlock loaded_count

            signal enemy_texture_ready
        end

        path audio_loader
            resource_states[2] assign "loading"
            resource_states[2] assign "loaded"

            lock loaded_count
            loaded_count assign loaded_count + 1
            unlock loaded_count

            signal audio_ready
        end

        path finalize
            wait texture_ready
            wait enemy_texture_ready
            wait audio_ready

            if loaded_count == 3
                handle LoadComplete
                    slot reason assign "All resources loaded."
                    delegate reason to puts
                    loading assign false
                    signal all_resources_ready
                end
            else
                handle ResourceFailed
                    slot reason assign "Resource count mismatch."
                    delegate reason to puts
                    stop
                end
            end
        end
    end

    return 0
end

Clarissa says:

“This version loads multiple resources concurrently, coordinates completion with signals, and protects the shared counter.”

Sherita says:

“This is officially engine-flavored.”

---

Lesson 19 — Compiler View

Clarissa projects:

Memory Table

resources:
    resource_names
    resource_states

loader:
    current_resource
    loading
    loaded_count

Permission Table:

resource_states:
    read
    change
    share

loaded_count:
    read
    change
    share

Execution Table:

discover
  ↓
parallel validation
  ↓
concurrent loading
    ├─ texture_loader
    ├─ enemy_texture_loader
    ├─ audio_loader
    └─ finalize waits for signals
  ↓
LoadComplete
  ↓
shutdown

Clarissa says:

“The compiler sees which paths load which resources and where synchronization happens.”

---

Lesson 20 — Professional Loader Habits

Clarissa writes:

Keep resource names and states aligned.

Validate resources before loading.

Guard indexes.

Name missing resources.

Name failed resources.

Use states instead of mystery booleans.

Protect shared counters.

Signal readiness explicitly.

Finalize only after all required resources are ready.

Keep loader memory separate from resource memory.

Sherita adds:

Do not trust the gray square.

Clarissa lets it stay.

---

Lesson 21 — Homework: Scene Manager

Clarissa writes:

SCENE MANAGER

Requirements:

program SceneManager

memory scene dedicated
memory resources dedicated

slots:
    current_scene
    next_scene
    scene_names
    scene_loaded
    transition_active

Must include:

collection scene_names
collection scene_loaded

manual errors:
    SceneMissing
    SceneLoadFailed
    SceneTransitionComplete

routes:
    current to unload
    unload to load
    load to transition
    transition to active

permissions
dedicated memory
each loop
for loop
parallel validation

Bonus:

concurrent
    path unload_old_scene
    path load_new_scene
end

Super bonus:

signals:
    old_scene_unloaded
    new_scene_loaded
    transition_ready

Sherita says:

“And if your scene transition loads the new scene before the old one stops touching shared resources…”

She points at the race condition monster.

“He has moved into the building.”

---

Closing Scene

The bell rings.

Clarissa turns off the projector.

“Today you built the beginning of an engine pipeline.”

She writes:

discover
validate
load
finalize
signal readiness

Sherita looks at the gray square still on the screen.

“And we gave missing_texture.png closure.”

Clarissa smiles.

The final slide fades in:

Foresette Academy

A resource is not ready because you hope it is.
It is ready because the loader proved it.



## --- ##



Foresette Academy — Class Ten

Scene Management, Transitions, Unloading, Loading, and Active State Control

Instructor: Clarissa Taylor
Assistant Instructor: Sherita Pleasant

---

8:50 A.M. — The Cursed Scene Transition

The projector shows:

CURRENT SCENE: Forest
NEXT SCENE: Castle
STATUS: Somehow both are active

Sherita Pleasant stands beside it with a pointer.

“This,” she says, “is how game engines start crying.”

Clarissa Taylor walks in, reads the screen, and exhales.

“Sherita.”

Sherita points to the text.

“It’s accurate.”

Clarissa turns to the class.

“Today we learn scene management.”

Sherita adds:

“Also known as: please do not let the forest and castle fight for the same memory.”

---

Lesson 1 — Scene Manager Requirements

Clarissa writes:

program SceneManager

memory scene dedicated
memory resources dedicated

Required slots:

current_scene
next_scene
scene_names
scene_loaded
transition_active

Required features:

collection scene_names
collection scene_loaded

manual errors:
    SceneMissing
    SceneLoadFailed
    SceneTransitionComplete

routes:
    current to unload
    unload to load
    load to transition
    transition to active

permissions
dedicated memory
each loop
for loop
parallel validation

Bonus:

concurrent
    path unload_old_scene
    path load_new_scene
end

Super bonus:

signals:
    old_scene_unloaded
    new_scene_loaded
    transition_ready

Clarissa says:

“A scene manager controls world identity.”

Sherita says:

“It answers: where are we, where are we going, what is loaded, and are we allowed to switch?”

---

Lesson 2 — Basic Scene Memory

program SceneManager

external puts
native c

error SceneMissing
    slot reason
end

error SceneLoadFailed
    slot reason
end

error SceneTransitionComplete
    slot reason
end

entry main
    memory scene dedicated
    memory resources dedicated

    slot current_scene from scene assign "forest"
    slot next_scene from scene assign "castle"

    slot scene_names from resources assign [
        "forest",
        "castle",
        "arena"
    ]

    slot scene_loaded from resources assign [
        true,
        false,
        false
    ]

    slot transition_active from scene assign false

    return 0
end

Clarissa explains:

current_scene

is what is active now.

next_scene

is where we want to go.

scene_names

is the known scene list.

scene_loaded

tracks load status by index.

transition_active

says whether a transition is happening.

Sherita says:

“Scene names are the map. Scene loaded is the checklist. Transition active is the caution tape.”

---

Lesson 3 — Scene Name and Loaded State Alignment

Clarissa writes:

scene_names[0]  = "forest"
scene_loaded[0] = true

scene_names[1]  = "castle"
scene_loaded[1] = false

scene_names[2]  = "arena"
scene_loaded[2] = false

She says:

“The index connects the scene to its loaded state.”

Sherita says:

“Same chair, different clipboard.”

Clarissa nods.

“If the arrays become misaligned, the manager lies.”

---

Lesson 4 — Permissions

Clarissa asks:

“What permissions do we need?”

The class builds:

permit read current_scene
permit change current_scene

permit read next_scene
permit change next_scene

permit read scene_names

permit read scene_loaded
permit change scene_loaded

permit read transition_active
permit change transition_active

Clarissa adds:

“If concurrent paths touch these, we also need share permissions.”

permit share current_scene
permit share next_scene
permit share scene_loaded
permit share transition_active

Sherita says:

“Concurrency turns private notebooks into group projects. Add rules.”

---

Lesson 5 — Route Lifecycle

Clarissa writes:

route current to unload
route unload to load
route load to transition
route transition to active

Then draws:

CURRENT
   ↓
UNLOAD OLD
   ↓
LOAD NEW
   ↓
TRANSITION
   ↓
ACTIVE

Clarissa says:

“This is scene transition structure.”

Sherita adds:

“Not teleporting through chaos. Actual steps.”

---

Lesson 6 — Finding the Next Scene

Clarissa writes:

slot found assign false
slot next_index assign 0

Permissions:

permit read found
permit change found

permit read next_index
permit change next_index

Search:

for i from 0 to 3
    if scene_names[i] == next_scene
        found assign true
        next_index assign i
    end
end

Then:

if found == false
    handle SceneMissing
        slot reason assign "Next scene does not exist."
        delegate reason to puts
        stop
    end
end

Clarissa says:

“The program explicitly proves the scene exists before loading it.”

Sherita says:

“No loading imaginary castle.”

---

Lesson 7 — Validating Scene Names

Clarissa writes:

each name from scene_names
    if name == ""
        handle SceneMissing
            slot reason assign "Scene name is empty."
            delegate reason to puts
            stop
        end
    end
end

This catches blank scene entries.

Sherita says:

“An empty scene name is not mysterious. It’s a hole wearing a hat.”

Clarissa pauses.

“Fine. That one was good.”

---

Lesson 8 — Parallel Validation

Clarissa shows:

parallel
    if scene_names[0] == ""
        handle SceneMissing
            slot reason assign "Scene 0 missing."
            delegate reason to puts
            stop
        end
    end

    if scene_names[1] == ""
        handle SceneMissing
            slot reason assign "Scene 1 missing."
            delegate reason to puts
            stop
        end
    end

    if scene_names[2] == ""
        handle SceneMissing
            slot reason assign "Scene 2 missing."
            delegate reason to puts
            stop
        end
    end
end

Clarissa says:

“These checks are independent reads.”

Sherita says:

“Three inspectors, three doors, zero wrestling.”

---

Lesson 9 — Loading the New Scene

Clarissa writes:

if scene_loaded[next_index] == false
    scene_loaded[next_index] assign true
end

She explains:

“If the next scene is not loaded, we load it.”

If loading fails:

handle SceneLoadFailed
    slot reason assign "Scene failed to load."
    delegate reason to puts
    stop
end

Sherita says:

“Again: failed scene loading gets a name, not a shrug.”

---

Lesson 10 — Unloading the Current Scene

Clarissa writes:

slot current_index assign 0
slot current_found assign false

Search current scene:

for i from 0 to 3
    if scene_names[i] == current_scene
        current_found assign true
        current_index assign i
    end
end

Then unload:

if current_found
    scene_loaded[current_index] assign false
end

Sherita says:

“You turn off the old room before moving into the new one.”

---

Lesson 11 — Basic SceneManagerCore

program SceneManagerCore

external puts
native c

error SceneMissing
    slot reason
end

error SceneLoadFailed
    slot reason
end

error SceneTransitionComplete
    slot reason
end

entry main
    memory scene dedicated
    memory resources dedicated

    slot current_scene from scene assign "forest"
    slot next_scene from scene assign "castle"

    slot scene_names from resources assign [
        "forest",
        "castle",
        "arena"
    ]

    slot scene_loaded from resources assign [
        true,
        false,
        false
    ]

    slot transition_active from scene assign false

    permit read current_scene
    permit change current_scene

    permit read next_scene
    permit change next_scene

    permit read scene_names

    permit read scene_loaded
    permit change scene_loaded

    permit read transition_active
    permit change transition_active

    route current to unload
    route unload to load
    route load to transition
    route transition to active

    parallel
        if scene_names[0] == ""
            handle SceneMissing
                slot reason assign "Scene 0 missing."
                delegate reason to puts
                stop
            end
        end

        if scene_names[1] == ""
            handle SceneMissing
                slot reason assign "Scene 1 missing."
                delegate reason to puts
                stop
            end
        end

        if scene_names[2] == ""
            handle SceneMissing
                slot reason assign "Scene 2 missing."
                delegate reason to puts
                stop
            end
        end
    end

    slot current_index assign 0
    slot current_found assign false

    permit read current_index
    permit change current_index

    permit read current_found
    permit change current_found

    for i from 0 to 3
        if scene_names[i] == current_scene
            current_found assign true
            current_index assign i
        end
    end

    if current_found == false
        handle SceneMissing
            slot reason assign "Current scene does not exist."
            delegate reason to puts
            stop
        end
    end

    slot next_index assign 0
    slot next_found assign false

    permit read next_index
    permit change next_index

    permit read next_found
    permit change next_found

    for i from 0 to 3
        if scene_names[i] == next_scene
            next_found assign true
            next_index assign i
        end
    end

    if next_found == false
        handle SceneMissing
            slot reason assign "Next scene does not exist."
            delegate reason to puts
            stop
        end
    end

    transition_active assign true

    scene_loaded[current_index] assign false

    if scene_loaded[next_index] == false
        scene_loaded[next_index] assign true
    end

    current_scene assign next_scene

    handle SceneTransitionComplete
        slot reason assign "Scene transition complete."
        delegate reason to puts
        transition_active assign false
    end

    return 0
end

Clarissa says:

“This program validates scenes, finds indexes, unloads the current scene, loads the next scene, updates current state, and completes the transition.”

Sherita says:

“The forest moved out. The castle moved in. No roommate drama.”

---

Lesson 12 — Hidden Issue: Current Equals Next

Clarissa asks:

“What if current_scene and next_scene are the same?”

The class pauses.

One student says:

“You don’t need a transition.”

Clarissa nods.

“Correct.”

Add:

if current_scene == next_scene
    handle SceneTransitionComplete
        slot reason assign "Scene already active."
        delegate reason to puts
        transition_active assign false
    end
end

Sherita says:

“If you’re already in the castle, don’t pack your bags to go to the castle.”

---

Lesson 13 — Concurrent Unload and Load

Clarissa introduces the bonus.

concurrent
    path unload_old_scene
    path load_new_scene
end

Potential problem:

Both paths touch:

scene_loaded

So we need:

permit share scene_loaded

and coordinated writes.

lock scene_loaded
scene_loaded[current_index] assign false
unlock scene_loaded

lock scene_loaded
scene_loaded[next_index] assign true
unlock scene_loaded

Sherita says:

“Same checklist, two workers. Lock the clipboard.”

---

Lesson 14 — Signals

Super bonus:

signal old_scene_unloaded
signal new_scene_loaded
signal transition_ready

Example:

path unload_old_scene
    lock scene_loaded
    scene_loaded[current_index] assign false
    unlock scene_loaded

    signal old_scene_unloaded
end

path load_new_scene
    lock scene_loaded
    scene_loaded[next_index] assign true
    unlock scene_loaded

    signal new_scene_loaded
end

path transition
    wait old_scene_unloaded
    wait new_scene_loaded
    signal transition_ready
end

Clarissa says:

“Signals make readiness visible.”

Sherita says:

“No vibes-based transitions.”

---

Lesson 15 — SceneManagerPro

program SceneManagerPro

external puts
native c

error SceneMissing
    slot reason
end

error SceneLoadFailed
    slot reason
end

error SceneTransitionComplete
    slot reason
end

entry main
    memory scene dedicated
    memory resources dedicated

    slot current_scene from scene assign "forest"
    slot next_scene from scene assign "castle"

    slot scene_names from resources assign [
        "forest",
        "castle",
        "arena"
    ]

    slot scene_loaded from resources assign [
        true,
        false,
        false
    ]

    slot transition_active from scene assign false

    permit read current_scene
    permit change current_scene
    permit share current_scene

    permit read next_scene
    permit change next_scene
    permit share next_scene

    permit read scene_names

    permit read scene_loaded
    permit change scene_loaded
    permit share scene_loaded

    permit read transition_active
    permit change transition_active
    permit share transition_active

    route current to unload
    route unload to load
    route load to transition
    route transition to active

    if current_scene == next_scene
        handle SceneTransitionComplete
            slot reason assign "Scene already active."
            delegate reason to puts
            transition_active assign false
        end
    end

    parallel
        if scene_names[0] == ""
            handle SceneMissing
                slot reason assign "Scene 0 missing."
                delegate reason to puts
                stop
            end
        end

        if scene_names[1] == ""
            handle SceneMissing
                slot reason assign "Scene 1 missing."
                delegate reason to puts
                stop
            end
        end

        if scene_names[2] == ""
            handle SceneMissing
                slot reason assign "Scene 2 missing."
                delegate reason to puts
                stop
            end
        end
    end

    slot current_index assign 0
    slot current_found assign false

    permit read current_index
    permit change current_index

    permit read current_found
    permit change current_found

    for i from 0 to 3
        if scene_names[i] == current_scene
            current_found assign true
            current_index assign i
        end
    end

    if current_found == false
        handle SceneMissing
            slot reason assign "Current scene does not exist."
            delegate reason to puts
            stop
        end
    end

    slot next_index assign 0
    slot next_found assign false

    permit read next_index
    permit change next_index

    permit read next_found
    permit change next_found

    for i from 0 to 3
        if scene_names[i] == next_scene
            next_found assign true
            next_index assign i
        end
    end

    if next_found == false
        handle SceneMissing
            slot reason assign "Next scene does not exist."
            delegate reason to puts
            stop
        end
    end

    transition_active assign true

    concurrent
        path unload_old_scene
            lock scene_loaded
            scene_loaded[current_index] assign false
            unlock scene_loaded

            signal old_scene_unloaded
        end

        path load_new_scene
            lock scene_loaded
            scene_loaded[next_index] assign true
            unlock scene_loaded

            signal new_scene_loaded
        end

        path transition
            wait old_scene_unloaded
            wait new_scene_loaded

            lock current_scene
            current_scene assign next_scene
            unlock current_scene

            signal transition_ready
        end
    end

    wait transition_ready

    handle SceneTransitionComplete
        slot reason assign "Scene transition complete."
        delegate reason to puts
        transition_active assign false
    end

    return 0
end

Clarissa says:

“This version validates scenes, finds indexes, unloads and loads concurrently, waits for readiness, then commits the active scene.”

Sherita says:

“Now the forest leaves through the front door and the castle enters after knocking.”

---

Lesson 16 — Compiler View

Clarissa projects:

Memory Table

scene:
    current_scene
    next_scene
    transition_active

resources:
    scene_names
    scene_loaded

Permission Table:

current_scene:
    read
    change
    share

next_scene:
    read
    change
    share

scene_loaded:
    read
    change
    share

transition_active:
    read
    change
    share

Execution Table:

current
  ↓
parallel scene validation
  ↓
find current index
  ↓
find next index
  ↓
concurrent unload/load/transition
      ├─ unload_old_scene
      ├─ load_new_scene
      └─ transition waits for both
  ↓
SceneTransitionComplete
  ↓
active

Clarissa says:

“The compiler sees both the resource state and the transition path.”

---

Lesson 17 — Professional Scene Habits

Clarissa writes:

Never activate a missing scene.

Never load a scene without validation.

Never unload and load shared scene state without synchronization.

Keep current and next scene separate.

Use indexes to align scene names and loaded states.

Name scene failures.

Signal scene readiness.

Commit the active scene only after transition readiness.

Avoid transitioning to the already-active scene.

Sherita adds:

Do not let the forest and castle overlap emotionally.

Clarissa stares.

Sherita says:

“Fine. Technically.”

---

Lesson 18 — Homework: Input System

Clarissa writes:

INPUT SYSTEM

Requirements:

program InputSystem

memory input dedicated
memory player dedicated

slots:
    keys
    key_states
    current_key
    input_active
    player_position

Key states:

"up"
"down"
"pressed"
"released"

Must include:

collection keys
collection key_states

manual errors:
    InputMissing
    InputInvalid
    InputApplied

routes:
    poll to validate
    validate to apply
    apply to shutdown

permissions
dedicated memory
each loop
for loop
parallel validation

Bonus:

concurrent
    path keyboard
    path controller
end

Super bonus:

signals:
    keyboard_ready
    controller_ready
    input_ready

Sherita says:

“And if your keyboard and controller both move the player at the exact same time without sync…”

The class points at the wall.

“Race condition monster.”

Sherita wipes a fake tear.

“They grow up so fast.”

---

Closing Scene

The bell rings.

Clarissa closes the laptop.

“Scene management is controlled identity.”

She writes:

current
next
validate
unload
load
transition
active

Sherita adds:

no cursed zipper

Clarissa does not erase it.

The final slide fades in:

Foresette Academy

A scene becomes active only when the transition proves it is ready.



## --- ##



