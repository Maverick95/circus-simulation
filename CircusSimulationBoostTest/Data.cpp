#include <algorithm>
#include <vector>

#include "Data.h"



std::vector<unsigned int*> GenerateDataStore(unsigned int** data, const unsigned int& count)
{
	std::vector<unsigned int*> result;
	std::for_each(data, data + count, [&result](unsigned int* d) { result.push_back(d); });
	return result;
}



/*
### DATA ###
*/



/*
### DisplayPatternTest
### DisplayPattern_Constructor_Success
*/

/*

[0] = balls
[1] = actions
[2]	= throws

[3] - [3 + (actions - 1)] = state_begin of first throw
[3 + actions] - [3 + (2 * actions) - 1] = state_end of first throw
[3 + (2 * actions)] = number of state_transfer elements (num_state_transfer)
[3 + (2 * actions) + 1]	- [3 + (2 * actions) + (3 * num_state_transfer)] = state_transfer details

and then next throw

*/

// 3 balls, 1 actions, 3 throws, [5][3][1]
static unsigned int
data_1_1[] =	{	3,	1,	3,	7,	19,	1,	0,	0,	5,	19,	13,	1,	0,	0,	3,	13,	7,	1,	0,	0,	1	};

// 3 balls, 2 actions, 2 throws, [4 2][2x 4x]
static unsigned int
data_1_2[] =	{	3,	2,	2,	3,	1,	3,	1,	2,	0,	0,	2,	1,	1,	1,	3,	1,	3,	1,	2,	0,	1,	1,	1,	0,	2	};

// 3 balls, 2 actions, 3 throws, [2x 4][4 4][0 4x]
static unsigned int
data_1_3[] =	{	3,	2,	3,	3,	1,	1,	3,	2,	0,	1,	1,	1,	1,	2,	1,	3,	2,	3,	2,	0,	0,	2,	1,	1,	2,	2,	3,	3,	1,	1,	1,	0,	2	};


static const unsigned int count_1 = 3;

static unsigned int* data_1_[] =
{
	data_1_1,
	data_1_2,
	data_1_3
};

static auto data_1 = GenerateDataStore(data_1_, count_1);



/*
### METHODS ###
*/



std::vector<unsigned int*>& Data::Data_DisplayPatternTest_DisplayPattern_Constructor_Success()
{
	return data_1;
}



