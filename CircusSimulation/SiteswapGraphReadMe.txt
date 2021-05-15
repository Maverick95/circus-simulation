SiteswapGraph is built for parameter t, the maximum throw height allowed

The maximum throw height does not have to be included in a pattern -
it just places a limit on how many patterns are covered by the SiteswapGraph.

It also implicitly places a limit on how many balls are included -
e.g. patterns with maximum throw height of 5 cannot cater for 6 balls, 7 balls, etc.

The pattern states themselves are not stored internally, however their properties are stored
in arrays where the array index unique defines the pattern state.

In bitwise notation these indices denote future "beats" in the pattern by ascending bits.

e.g. t = 5, 3 ball patterns

state XXX-- = 11100 = 1 + 2 + 4		= 7		<-- standard state
state X-X-X = 10101 = 1 + 4 + 16	= 21
state XX-X- = 11010 = 1 + 2 + 8		= 11

On construction, internal data is computed and stored to maximise efficiency -

a) balls_states, a map of integers to a collection of states
Stores the states for a varying number of balls 0 to t.

b) connections, an array of collections of state transitions
Stores the possible moves in each state,
as a dataset describing the connection between one state and another.



The function GetPatterns(b = num_balls, t = num_throws) returns a collection
of valid patterns (if any), these are patterns containing b balls that begin
at a state and loop back to the same state after t throws.

Each pattern will contain no cycles w.r.t. states - the states at the beginning
of each throw will be unique.

These patterns are returned in the order given by comparisons
between patterns A and B as follows -

1) If A contains fewer balls than B, A comes first.
2) If A contains fewer throws in its sequence than B, A comes first.

For current purposes however, all patterns in a set will be equal for 1) and 2).

3) Starting from the 1st position, compare the throw value of A to B.
If A < B, A comes first.

For a valid siteswap pattern, the permutation is whichever begins at the state
with the lowest state index (remember from above, all states are unique)
e.g. for the pattern b = 3, t = 5, options 531, 315, 153
These are all permutations of the same pattern.

531		begins at state		XXX--	= 7		<-- lowest state
315		begins at state		XX--X	= 19
153		begins at state		X-XX-	= 13

Therefore 531 is the permutation returned.


Update 09/05/2021

Multi-action functionality is now available for both functions GetPatterns() and GetRandomPattern()

Arguments are -

numberBalls - number of balls used
numberActions - number of actions used
numberThrows - length of the pattern
maxThrow - maximum number of steps ahead allowed

A few key points need clarifying here

a) Valid states to begin from,
b) Valid states to include in a pattern,
c) Order of patterns returned.

a) Valid states to begin from,

This is the result of function SiteswapGraphMultiAction::StoreValidBeginStates

This is quite complex, so hopefully I can explain this in an easy way.

A state is a valid beginning state if two conditions are satisfied -

1.
for all 0 <= i < j < numberActions,
number of balls in action[i] >= number of balls in action[j]

2.
if number of balls in action[i] == number of balls in action[j],
then state[i] >= state[j], where the state is the integer representation

Example

numberBalls = 2, numberActions = 2, numberThrows = 2, maxThrow = 3

There are 15 total states to consider

X X -	2 balls		state 3		2 > 0		INCLUDED
- - -	0 balls		state 0

X - X	2 balls		state 5		2 > 0		INCLUDED
- - -	0 balls		state 0	

X - -	1 ball		state 1		1 == 1		INCLUDED
X - -	1 ball		state 1		1 == 1

X - -	1 ball		state 1		1 == 1		EXCLUDED	---
- X -	1 ball		state 2		1 < 2

X - -	1 ball		state 1		1 == 1		EXCLUDED	---
- - X	1 ball		state 4		1 < 4

- X X	2 balls		state 6		2 > 0		INCLUDED
- - -	0 balls		state 0

- X -	1 ball		state 2		1 == 1		INCLUDED
X - -	1 ball		state 1		2 > 1

- X -	1 ball		state 2		1 == 1		INCLUDED
- X -	1 ball		state 2		2 == 2

- X -	1 ball		state 2		1 == 1		EXCLUDED	---
- - X	1 ball		state 4		2 < 4

- - X	1 ball		state 4		1 == 1		INCLUDED
X - -	1 ball		state 1		4 > 1

- - X	1 ball		state 4		1 == 1		INCLUDED
- X -	1 ball		state 2		4 > 2

- - X	1 ball		state 4		1 == 1		INCLUDED
- - X	1 ball		state 4		4 == 4

- - -	0 balls		state 0		0 < 2		EXCLUDED	---
X X -	2 balls		state 3

- - -	0 balls		state 0		0 < 2		EXCLUDED	---
X - X	2 balls		state 5

- - -	0 balls		state 0		0 < 2		EXCLUDED	---
- X X	2 balls		state 6


There are 9 states here that are considered starting states.

b) Valid states to include in a pattern,

Every state is considered a valid state to include, WITH THE EXCEPTION of
any state that has already been considered as a starting state.

This is to avoid unnecessary repetition while ensuring all unique patterns
are discovered.

c) Order of patterns returned.

Patterns are stored as std::set<SiteswapPattern>, which means the order is based on
the < operator.

Compare numberBalls
Compare numberActions
Compare numberThrows
For each throw in order, compare the start state and the end state




