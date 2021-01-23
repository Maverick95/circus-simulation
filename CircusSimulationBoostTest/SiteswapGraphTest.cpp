#define BOOST_TEST_MODULE CircusSimulationBoostTest
#include <boost/test/included/unit_test.hpp>

#include <vector>

#include "SiteswapGraph.h"

/*
	* Test cases - 8 bits
	*
	* XXX-----		to		X-XX----		7		to		13		= 2
	* X-XXX--X		to		-X-XX-XX		157		to		218		= 6
	* X------X		to		--X---X-		129		to		68		= 1
	* -X-XX-X-		to		XXXX----		90		to		15		= 3
*/
BOOST_AUTO_TEST_CASE(DeriveShortestPath_8bit)
{
	struct DeriveShortestPathTest
	{
		unsigned int state_begin, state_end, path_length;
	};

	std::vector<DeriveShortestPathTest> tests;
	tests.push_back({ 7U, 13U, 2U });
	tests.push_back({ 157U, 218U, 6U });
	tests.push_back({ 129U, 68U, 1U });
	tests.push_back({ 90U, 15U, 3U });

	for (auto i = tests.begin(); i != tests.end(); i++)
	{
		BOOST_TEST(SiteswapGraph::DeriveShortestPath(i->state_begin, i->state_end) == i->path_length);
	}
}

BOOST_AUTO_TEST_CASE(GetPatterns_Balls3_Height5_Throws2)
{
	SiteswapGraph sg(5U);
	auto* paths = sg.GetPatterns(3U, 2U);

	BOOST_TEST(paths->size() == 2U);

	unsigned int index = 0U;
	unsigned int results[2U][2U] = { {4U, 2U}, {5U, 1U} };

	for (auto i = paths->begin(); i != paths->end(); i++)
	{
		BOOST_TEST(i->num_balls == 3U);

		for (unsigned int j = 0U; j < 2U; j++)
		{
			BOOST_TEST(i->throws[j].state_transfer_throw == results[index][j]);
		}
		index++;
	}

	delete paths;
}

/*
Further tests involve understanding how the patterns are returned,
e.g. for 3 balls, 531, 315, 153, which one comes back?
*/
