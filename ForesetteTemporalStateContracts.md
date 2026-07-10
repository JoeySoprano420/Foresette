Foresette Temporal State Contracts

Official Language Feature

Feature Name

Temporal State Contracts

Short Name

State Contracts

Purpose

Temporal State Contracts allow a Foresette program to declare what values, conditions, and relationships must remain true during a particular lifetime, phase, interval, or active state.

They describe not merely what a program should do, but what states the program is legally allowed to occupy over time.

A Temporal State Contract answers questions such as:

- What must remain true during this operation?
- Which values are legal before a transition?
- Which values become illegal after a transition?
- What conditions must hold while a resource is active?
- When may a state begin?
- When must a state end?
- Which combinations of values are forbidden?

The feature combines declarative state rules with imperative state transitions.

---

Core Example

slot X assign 7
slot count assign 0

during sort lifetime

    require X == 7 while count < 10

    when count reaches 10
        X assign 8
    end

    require X != 7 while count >= 10

end

This means:

While sort is active:

    count < 10
        X must equal 7

    count reaches 10
        X becomes 8

    count >= 10
        X must not equal 7

The compiler treats these rules as enforceable program semantics.

They are not comments.

They are not optional assertions.

They are part of the program’s state model.

---

Canonical Compact Form

The preferred compact form is:

during sort lifetime
    require X == 7 while count < 10
    require X != 7 while count >= 10
end

This form defines two legal state regions:

count < 10   → X == 7
count >= 10  → X != 7

The transition occurs at exactly "10".

---

Canonical Transition Form

When a specific value must be assigned at the transition boundary:

during sort lifetime

    require X == 7 while count < 10

    when count reaches 10
        X assign 8
    end

    require X != 7 while count >= 10

end

The "when" block performs an action.

The "require" statements define legal state.

---

Language Classification

Temporal State Contracts are primarily declarative.

They declare:

what must be true
when it must be true
how long it must remain true

For example:

require X == 7 while count < 10

does not instruct the computer to repeatedly assign "7".

It declares that every observable program state satisfying:

count < 10

must also satisfy:

X == 7

The following statement is imperative:

when count reaches 10
    X assign 8
end

It commands the program to perform a mutation when an event occurs.

Therefore, Foresette Temporal State Contracts form a:

«Declarative state-contract system with imperative transitions.»

They also relate to:

- temporal logic,
- design by contract,
- typestate,
- reactive programming,
- state machines,
- lifetime analysis,
- static verification,
- invariant checking.

However, the complete feature is distinct because it combines all of these ideas directly with Foresette’s assignment and state model.

---

Core Keywords

Temporal State Contracts introduce or formalize the following keywords:

during
lifetime
require
while
only while
when
reaches
release
end

---

"during"

The "during" keyword opens a temporal contract scope.

during sort lifetime
    ...
end

It means:

«The enclosed rules apply while the named lifetime is active.»

Examples:

during request lifetime
    require connection != null
end

during render lifetime
    require frame.status != complete while workers.active > 0
end

during payment lifetime
    require authorization == approved while funds.captured
end

---

"lifetime"

A lifetime is a compiler-recognized interval with a beginning and an end.

A lifetime may belong to:

- a routine,
- a task,
- a resource,
- a state,
- a transaction,
- a loop,
- an object-like item,
- a process,
- a lane,
- a request,
- a user-defined operation.

Example:

sort begin
    ...
sort end

The compiler may infer the active interval of "sort".

A contract may then refer to it:

during sort lifetime
    require count <= max_count
end

A lifetime may also be declared explicitly:

lifetime sort begin

    ...

end sort

---

"require"

The "require" keyword declares a condition that must remain true whenever its temporal qualification is active.

require X == 7 while count < 10

This does not necessarily perform an assignment.

It establishes an invariant.

The compiler must ensure that no legal execution path violates it.

Other examples:

require connection != null

require buffer.size <= buffer.capacity

require pressure == equal while door == open

require authenticated while admin

require workers.active == 0 while frame.complete

---

"while"

Within a Temporal State Contract, "while" defines the condition under which a requirement remains active.

require X == 7 while count < 10

The contract applies at every observable state in which:

count < 10

remains true.

This is stronger than a standard "if".

An "if" statement checks a condition at one execution point.

A temporal "while" requirement governs an entire state interval.

---

"only while"

The "only while" form declares that a value or condition is legal exclusively while another condition is true.

require door == open only while pressure == equal

This means:

door == open → pressure == equal

It does not necessarily mean that the door must open whenever the pressure is equal.

It means the door may not legally be open under any other condition.

Examples:

require admin == true only while authenticated

require memory.writable only while initialization.active

require reward.available only while battle.complete

require engine.running only while fuel_pressure >= minimum

require frame.readable only while kernel.complete

---

"when"

The "when" keyword introduces an event-triggered imperative transition.

when count reaches 10
    X assign 8
end

Unlike "require", "when" performs or initiates an action.

It may assign values, call routines, emit signals, release resources, or begin another state.

Example:

when payment reaches approved
    funds capture
end

when workers.active reaches 0
    frame.status assign complete
end

when temperature reaches maximum
    reactor shutdown
end

---

"reaches"

The "reaches" keyword describes a transition event.

when count reaches 10

It triggers when the observed value changes from a state that does not satisfy the target into a state that does.

For a numeric target:

when count reaches 10

the event occurs when "count" becomes "10".

It does not continually trigger while "count" remains "10".

This distinguishes it from:

while count == 10

which describes a persistent condition.

---

Persistent State Versus Transition Event

These statements are not interchangeable:

when count reaches 10

require X != 7 while count >= 10

The first describes a single transition event.

The second describes a continuing legal-state rule.

A complete transition therefore commonly uses both:

when count reaches 10
    X assign 8
end

require X != 7 while count >= 10

The event changes the state.

The requirement governs the state afterward.

---

"release"

The "release" keyword explicitly ends a requirement before the surrounding lifetime ends.

during sort lifetime

    require X == 7 while count < 10

    when count reaches 10
        release X == 7
        X assign 8
    end

    require X != 7 while count >= 10

end

In many cases, the compiler can infer that the first requirement is inactive once:

count >= 10

becomes true.

Therefore, "release" is optional when the active intervals are already mutually exclusive.

The explicit form is useful when:

- the contract is manually terminated,
- the condition is complex,
- a resource must be released,
- the programmer wants the transition to be highly visible,
- the compiler cannot infer the end safely.

---

State Contract Semantics

Consider:

during sort lifetime
    require X == 7 while count < 10
    require X != 7 while count >= 10
end

The compiler models this as:

sort_active AND count < 10
    implies X == 7

sort_active AND count >= 10
    implies X != 7

Formally:

∀t within lifetime(sort):

    count(t) < 10
        ⇒ X(t) = 7

    count(t) >= 10
        ⇒ X(t) ≠ 7

The contract applies throughout the entire active lifetime.

---

Assignment Interaction

Foresette already treats assignment as a value contract.

slot X assign 7

Temporal State Contracts extend that idea across time.

An ordinary assignment establishes a value:

X assign 7

A temporal requirement establishes when that value must remain legal:

require X == 7 while count < 10

If a program attempts:

X assign 4

while the compiler knows:

count < 10

and the sort lifetime is active, the assignment is invalid.

Example diagnostic:

Temporal State Contract Violation

Assignment:
    X assign 4

Active lifetime:
    sort

Active requirement:
    X == 7 while count < 10

Known state:
    count = 6

The assignment would create an illegal state.

---

Interaction With "permit change"

Changing an existing Foresette slot still requires permission when normal mutation rules apply.

slot X assign 7
permit change X

A permission allows mutation.

It does not allow a contract violation.

Example:

slot X assign 7
permit change X

during sort lifetime
    require X == 7 while count < 10

    X assign 4
end

This remains invalid.

"permit change X" means:

«"X" is allowed to change when all active contracts permit it.»

It does not mean:

«"X" may ignore temporal requirements.»

---

Contract Priority

Temporal State Contracts restrict legal assignment.

Their authority is evaluated in this order:

1. Is the slot declared?
2. Is mutation permitted?
3. Is the assignment type-valid?
4. Does the assignment satisfy all active state contracts?
5. Does the resulting state satisfy lifetime rules?
6. May the new state be applied?

An assignment must pass every level.

---

Contradictory Contracts

The compiler rejects contracts that require mutually impossible states during the same interval.

Invalid:

during sort lifetime
    require X == 7 while count < 10
    require X != 7 while count < 10
end

Diagnostic:

Contradictory Temporal State Contracts

Both requirements are active while:
    count < 10

Requirement A:
    X == 7

Requirement B:
    X != 7

No legal value of X can satisfy both requirements.

The compiler should attempt to detect contradictions statically.

When the overlap depends on runtime values, Foresette may generate a guarded contract check.

---

Complete Coverage

The compiler may warn when a temporal value has undefined legal behavior over part of a lifetime.

Example:

during sort lifetime
    require X == 7 while count < 10
    require X != 7 while count > 10
end

This leaves:

count == 10

uncovered.

Suggested diagnostic:

Temporal Boundary Gap

No contract defines the legal state of X when:
    count == 10

Did you mean:
    require X != 7 while count >= 10

This is why Version A uses:

count < 10
count >= 10

The two intervals meet exactly at the boundary.

---

Boundary Rules

Foresette Temporal State Contracts use ordinary comparison semantics:

count < 10
count <= 10
count == 10
count >= 10
count > 10

The programmer must decide whether the boundary value belongs to the earlier or later state.

Version A:

count < 10   → X == 7
count >= 10  → X != 7

Version B:

count <= 10  → X == 7
count > 10   → X != 7

The official sorting example uses Version A.

---

Static Verification

The compiler first attempts to prove each contract at compile time.

Example:

slot X assign 7

during sort lifetime
    require X == 7 while count < 10
end

If no path can change "X", the compiler proves the requirement.

No runtime check is necessary.

Compiler result:

Temporal contract proven.
Runtime guard omitted.

---

Runtime Enforcement

If a contract cannot be fully proven statically, the compiler may emit a runtime guard.

Conceptually:

if sort.active and count < 10:
    verify X == 7

The exact generated machine code is implementation-defined.

A failed runtime guard produces a structured contract failure rather than silent invalid state.

---

Zero-Cost Contract Elimination

When the compiler proves a contract, all related guards may be removed.

This means the source may remain highly defensive while the executable remains lean.

Example:

during request lifetime
    require connection != null
end

If Foresette proves that the connection is established before the request begins and cannot be cleared during the request, repeated null checks may be eliminated inside that lifetime.

The contract becomes optimization knowledge.

---

Optimization Benefits

Temporal State Contracts may enable:

- constant propagation,
- constant folding,
- branch elimination,
- redundant check removal,
- dead path deletion,
- range analysis,
- alias restriction,
- null-check elimination,
- state specialization,
- loop simplification,
- safer inlining,
- guarded devirtualization,
- more precise concurrency analysis.

Example:

during sort lifetime
    require X == 7 while count < 10

    if X == 7
        process
    end
end

Inside a compiler-proven region where:

count < 10

the test:

if X == 7

is always true.

The compiler may reduce:

if X == 7
    process
end

to:

process

---

Range Knowledge

A temporal requirement may establish numeric ranges.

during buffer lifetime
    require position >= 0
    require position < capacity
end

The compiler may use this knowledge to prove array access safety:

value assign buffer[position]

If the active contracts guarantee that "position" is always within range, the compiler may remove redundant bounds checks.

---

Null-State Safety

Example:

during request lifetime
    require connection != null
end

Within the request lifetime:

connection send response

is valid without repeated local null checks when the contract has been proven.

Any path that could clear the connection during the request is rejected or guarded.

---

Resource Safety

during file lifetime
    require file.open
    require file.handle != null
end

This ensures that operations within the lifetime cannot observe a closed or invalid file unless the lifetime ends or the requirement is explicitly released.

Example:

during file lifetime

    require file.open

    read file

    when file reaches complete
        release file.open
        close file
    end

end

---

Concurrency Safety

Temporal State Contracts are especially useful when several lanes, tasks, or workers may modify shared state.

during render lifetime

    require frame.status == building while workers.active > 0

    require frame.status == complete only while workers.active == 0

end

An invalid worker action:

frame.status assign complete

while:

workers.active assign 3

violates the contract.

The compiler may reject the mutation statically or generate synchronized validation.

---

Lock-State Contracts

during critical lifetime
    require lock.owned
    require shared_data.mutable only while lock.owned
end

This declares that shared mutable state may be changed only while the active operation owns the required lock.

Example violation:

lock release
shared_data assign replacement

The compiler can identify that the second operation occurs outside the permitted state.

---

Transaction Safety

during payment lifetime

    require funds.captured == false while authorization != approved

    require funds.captured == true only while authorization == approved

end

This prevents the system from entering the state:

funds captured
authorization not approved

Even though each individual value may be valid on its own, their combination is illegal.

This is one of the principal purposes of Temporal State Contracts:

«Preventing legal values from forming illegal combinations.»

---

Game-State Example

during boss_battle lifetime

    require arena.locked while boss.health > 0

    require reward.available == false while boss.health > 0

    require reward.available only while boss.health <= 0

    when boss.health reaches 0
        arena.locked assign false
        reward.available assign true
    end

end

This prevents:

- rewards appearing before the boss is defeated,
- the arena unlocking too early,
- victory state activating while the boss remains alive.

---

Airlock Example

during airlock lifetime

    require inner_door == closed while outer_door == open

    require outer_door == closed while inner_door == open

    require inner_door == open only while pressure == interior_equal

    require outer_door == open only while pressure == exterior_equal

end

This defines legal combinations of door and pressure states.

The language can reject any operation that creates an unsafe combination.

---

Authentication Example

during session lifetime

    require admin == true only while authentication.valid

    require private_data.visible only while authentication.valid

    when authentication reaches invalid
        admin assign false
        private_data.visible assign false
    end

end

The contract prevents privileged state from persisting after authentication becomes invalid.

---

Compiler Example

during parse lifetime

    require token.position >= 0

    require token.position <= source.length

    require current_node != sealed while building

    require current_node == sealed only while finalized

end

The parser cannot legally:

- move beyond the source,
- modify a sealed node,
- mark an incomplete node as finalized.

---

GPU Example

during dispatch lifetime

    require buffer.writable while kernel.pending

    require buffer.readable only while kernel.complete

    require result.available only while kernel.complete

    when kernel reaches complete
        buffer.writable assign false
        buffer.readable assign true
        result.available assign true
    end

end

This gives the compiler a precise model of GPU resource state.

---

Database Example

during transaction lifetime

    require transaction.open

    require record.mutable only while transaction.open

    require commit.allowed only while validation.passed

    require rollback.allowed while transaction.open

end

---

Network Request Example

during request lifetime

    require connection != null

    require response.sent == false while response.building

    require response.sent only while response.complete

    when response reaches complete
        send response
    end

end

---

Hardware-Control Example

during reactor lifetime

    require cooling.active while temperature >= warning

    require reactor.running only while pressure <= safe_maximum

    when temperature reaches maximum
        reactor.running assign false
        emergency_cooling activate
    end

end

This style is useful because the safety rule is expressed directly rather than being scattered across many independent control branches.

---

Relationship to Active State

Foresette distinguishes current program truth as active state.

Example:

slot current_scene assign "forest"

A Temporal State Contract governs what active state is permitted during a lifetime.

during exploration lifetime
    require current_scene != "battle" while enemies == 0
end

The contract does not merely observe active state.

It restricts it.

---

Relationship to Staged State

A staged value may be proposed before becoming active.

slot volume assign 70
slot selected_volume assign 85

A temporal contract may reject a staged state before application.

during quiet_mode lifetime
    require selected_volume <= 40
end

If:

selected_volume assign 85

is staged during quiet mode, the compiler or runtime validator may refuse to apply it.

---

Relationship to Applied State

A staged value becomes applied only after all active contracts are satisfied.

Conceptually:

staged value
    ↓
type validation
    ↓
permission validation
    ↓
temporal contract validation
    ↓
relationship validation
    ↓
applied state

This allows Foresette to prevent invalid state before it becomes live.

---

Recommended Grammar

A simplified grammar form:

temporal_contract
    ::= "during" identifier "lifetime"
        temporal_statement*
        "end"

temporal_statement
    ::= requirement
     | transition
     | release_statement
     | ordinary_statement

requirement
    ::= "require" expression
        temporal_qualifier?

temporal_qualifier
    ::= "while" expression
     | "only while" expression

transition
    ::= "when" expression "reaches" expression
        statement*
        "end"

release_statement
    ::= "release" expression

---

Alternative "during" Forms

A lifetime may include a direct condition:

during count < 10
    require X == 7
end

However, the named-lifetime form is preferred for larger programs:

during sort lifetime
    require X == 7 while count < 10
end

The named form provides:

- clearer diagnostics,
- stronger lifetime analysis,
- easier optimization,
- better documentation,
- cleaner nesting.

---

Nested Contracts

Temporal State Contracts may be nested.

during application lifetime

    require runtime.active

    during request lifetime
        require connection != null

        during transaction lifetime
            require transaction.open
        end
    end

end

Inner contracts inherit all active outer requirements.

A state must satisfy every active contract.

---

Contract Shadowing

A nested contract may not silently contradict an outer contract.

Invalid:

during application lifetime
    require mode == safe

    during diagnostic lifetime
        require mode != safe
    end
end

The programmer must explicitly release or transition the outer requirement when such behavior is intended.

Example:

during application lifetime

    require mode == safe

    when diagnostic begins
        release mode == safe
        mode assign diagnostic
    end

end

---

Contract Completion

When the named lifetime ends, its requirements are automatically released unless they belong to an enclosing lifetime.

during sort lifetime
    require X == 7 while count < 10
end

After "sort" ends, this contract no longer governs "X".

A separate contract may govern "X" afterward.

---

Lifetime Entry Validation

The program must satisfy unconditional requirements when entering a lifetime.

during request lifetime
    require connection != null
end

If the request lifetime begins while:

connection == null

the lifetime cannot legally activate.

Possible diagnostic:

Lifetime Entry Contract Failure

Lifetime:
    request

Required on entry:
    connection != null

Observed:
    connection == null

---

Lifetime Exit Validation

A contract may specify a required exit state.

Recommended syntax:

during transaction lifetime

    require transaction.open

    on exit require transaction.open == false

end

This ensures that the transaction is closed before the lifetime completes.

Another example:

during file lifetime
    require file.open
    on exit require file.closed
end

The "on exit" extension may be included as part of the broader Temporal State Contract system.

---

Lifetime Entry Actions

Recommended syntax:

during sort lifetime

    on enter
        count assign 0
        X assign 7
    end

    require X == 7 while count < 10

end

This separates initialization actions from continuing requirements.

---

Full Structured Form

during sort lifetime

    on enter
        count assign 0
        X assign 7
    end

    require X == 7 while count < 10

    when count reaches 10
        X assign 8
    end

    require X != 7 while count >= 10

    on exit
        release X != 7
    end

end

---

Error Handling

A failed temporal contract may be handled through Foresette’s error system.

Example:

error SortStateViolation
    value
    expected
    count
    lifetime
end

A contract may name its failure:

during sort lifetime

    require X == 7 while count < 10
        else SortStateViolation

end

Conceptually:

If the contract fails:
    produce SortStateViolation

The exact relationship between Temporal State Contracts and Foresette’s error-flow system should preserve Foresette’s existing error philosophy.

---

Strict Contract Mode

A compiler mode may require that every Temporal State Contract be statically proven.

Example:

strict contracts

Under strict contract mode:

- unproven contracts are compile-time errors,
- runtime guards are not automatically inserted,
- ambiguous lifetime boundaries are rejected,
- uncovered state intervals produce errors,
- contradictory contracts halt compilation.

This mode is appropriate for:

- operating systems,
- embedded control,
- financial infrastructure,
- deterministic simulation,
- safety-critical software,
- cryptographic systems.

---

Guarded Contract Mode

The default or general-purpose mode may permit runtime guards for contracts the compiler cannot fully prove.

guarded contracts

Under guarded mode:

- proven rules produce no runtime cost,
- partially proven rules receive minimal checks,
- failed checks produce structured contract errors,
- optimization removes unnecessary guards.

---

Advisory Contract Mode

An optional development mode may treat selected rules as warnings.

advise require frame.rate >= 30

This is not recommended for correctness-critical contracts.

It may be useful for:

- performance targets,
- quality thresholds,
- development diagnostics,
- nonessential policies.

Core "require" statements remain enforceable.

---

Compiler Responsibilities

The Foresette compiler should:

1. Parse lifetime scopes.
2. Identify contract activation intervals.
3. Build state predicates.
4. Detect contradictory requirements.
5. Detect uncovered boundaries when relevant.
6. Analyze all assignments that may affect contracted state.
7. Verify legal state combinations.
8. prove contracts statically where possible.
9. Insert runtime guards where permitted and necessary.
10. Remove redundant checks.
11. use proven contracts for optimization.
12. Report violations with lifetime and state context.
13. prevent staged values from becoming invalid applied state.
14. verify nested contract compatibility.
15. enforce entry and exit requirements.

---

Recommended Diagnostics

Illegal Assignment

Temporal State Contract Violation

X cannot become 4 during sort lifetime.

Active requirement:
    X == 7 while count < 10

Known state:
    count = 6

Boundary Gap

Temporal Boundary Gap

The legal state of X is undefined when:
    count == 10

Previous interval:
    count < 10

Next interval:
    count > 10

Contradiction

Temporal Contract Contradiction

Requirement A:
    door == open

Requirement B:
    door == closed

Both are active while:
    pressure == equal

Invalid Lifetime Entry

Lifetime Entry Failure

Cannot begin request lifetime.

Required:
    connection != null

Observed:
    connection == null

Invalid Lifetime Exit

Lifetime Exit Failure

Cannot end transaction lifetime.

Required on exit:
    transaction.open == false

Observed:
    transaction.open == true

---

Why This Feature Is Useful

Temporal State Contracts solve a common programming problem:

«Programs often enter states that are technically representable but logically illegal.»

A normal type system may allow:

door = open
pressure = unsafe

because both values are individually valid.

A Temporal State Contract can declare that the combination itself is illegal.

require door == open only while pressure == equal

This allows Foresette to reason about relationships between values over time.

The feature is useful because it:

- prevents illegal state combinations,
- centralizes important program rules,
- reduces scattered defensive checks,
- improves compiler analysis,
- strengthens concurrency safety,
- clarifies lifecycle behavior,
- documents the program in executable form,
- catches errors before state becomes active,
- enables zero-cost safety when contracts are proven,
- gives optimization passes more reliable information.

---

Programming Philosophy

Ordinary imperative programming says:

Do this.
Then do that.
Check this.
Change that.

Functional programming emphasizes:

Compute this value from those values.

Object-oriented programming emphasizes:

Ask this object to perform this behavior.

Temporal State Contract programming says:

This is the state the program is legally allowed to occupy during this time.

This becomes a natural extension of Foresette’s state-centered philosophy.

Foresette does not merely track values.

It tracks:

- active state,
- staged state,
- applied state,
- assignment permission,
- lifetime legality,
- transition boundaries,
- temporal invariants.

---

Official Paradigm Description

With this feature, Foresette may be described as:

«A state-contract-oriented, declarative-imperative, ahead-of-time compiled systems language.»

Its Temporal State Contract system provides:

«Declarative lifetime-bound invariants with imperative transition control.»

---

Official Canonical Example

slot X assign 7
permit change X

slot count assign 0
permit change count

during sort lifetime

    require X == 7 while count < 10

    when count reaches 10
        X assign 8
    end

    require X != 7 while count >= 10

end

Official meaning:

For the active lifetime of sort:

    Before count reaches 10:
        X must remain exactly 7.

    At the moment count reaches 10:
        X becomes 8.

    From count 10 onward:
        X may not become 7.

When sort ends:
    These temporal restrictions are released.

---

Final Definition

Temporal State Contract

A Temporal State Contract is a compiler-enforced declaration that defines which values, conditions, relationships, and transitions are legal during a named program lifetime or state interval.

It may be statically proven, dynamically guarded, optimized away, or rejected when contradictory.

It transforms lifetime from a question of:

«How long does this value exist?»

into the broader question:

«What must remain true while this program state exists?»

That makes Temporal State Contracts a foundational Foresette feature rather than syntax sugar.

They allow the programmer to define not only program behavior, but the legal shape of program reality.
