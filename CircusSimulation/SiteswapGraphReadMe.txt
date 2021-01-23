SiteswapGraph is built for parameter t, the maximum throw height allowed

The maximum throw height does not have to be included in a pattern -
it just places a limit on how many patterns are covered by the SiteswapGraph.

It also implicitly places a limit on how many balls are included -
e.g. patterns with maximum throw height of 5 cannot cater for 6 balls, 7 balls, etc.

The pattern states themselves are not stored internally, however their properties are stored
in arrays where the array index unique defines the pattern state.

In bitwise notation these indices denote future "beats" in the pattern by ascending bits.

e.g. t = 5, 3 ball patterns

state XXX-- = 11100 = 1 + 2 + 4		= 7
state X-X-X = 10101 = 1 + 4 + 16	= 21
state XX-X- = 11010 = 1 + 2 + 8		= 11

On construction, a lot of internal data is computed and stored to maximise efficiency, this is...

a) the maximum state, ComputeMaxState()

This is the largest unsigned int representing a state
Given inputs b and t, this is fairly easy to compute.

e.g. b = 3, t = 5

max state = --XXX = 4 + 8 + 16 = 28

b) the individual states, ComputeStates()

There are Choose(t, b) states to compute.
Currently unsure of what order these come out in.
I think it would be better to rework this now.

YEP MAKE THIS A TODO.

c) the connections, ComputeConnections()

There are Choose(t, b) separate forward_list<> structures that correspond to each of the states.
Each forward list contains a dataset describing the connection between one state and another.

The function GetPatterns() returns the siteswap patterns in the order given by comparisons
between patterns A and B as follows -

1) If A contains fewer balls than B, A comes first.
2) If A contains fewer throws in its sequence than B, A comes first.

For current purposes however, all patterns in a set will be equal for 1) and 2).

3) Starting from the 1st position, compare the throw value of A to B.
   If A < B, A comes first.

However what I'm unsure of is, given a pattern 531, 315, 153,
in what order does the algorithm present things?

So now you need to add in an unordered_map mapping integers (num balls) to states,
std::queue





