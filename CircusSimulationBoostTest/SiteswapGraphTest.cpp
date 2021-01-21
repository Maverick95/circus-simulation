#define BOOST_TEST_MODULE CircusSimulationBoostTest
#include <boost/test/included/unit_test.hpp>

#include "SiteswapGraph.h"

BOOST_AUTO_TEST_CASE(CheckMaxState)
{
	SiteswapGraph
		sg1(2U, 4U),
		sg2(3U, 5U),
		sg3(4U, 7U),
		sg4(5U, 9U),
		sg5(2U, 9U);

	BOOST_TEST(sg1.MaxState() == 12U);
	BOOST_TEST(sg2.MaxState() == 28U);
	BOOST_TEST(sg3.MaxState() == 120U);
	BOOST_TEST(sg4.MaxState() == 496U);
	BOOST_TEST(sg5.MaxState() == 384U);

}

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

  BOOST_TEST(SiteswapGraph::DeriveShortestPath(7U, 13U) == 2U);
  BOOST_TEST(SiteswapGraph::DeriveShortestPath(157U, 218U) == 6U);
  BOOST_TEST(SiteswapGraph::DeriveShortestPath(129U, 68U) == 1U);
  BOOST_TEST(SiteswapGraph::DeriveShortestPath(90U, 15U) == 3U);

}

BOOST_AUTO_TEST_CASE(GetPatterns_Balls3_Height5_Throws2)
{
	SiteswapGraph sg(3U, 5U);
	auto* paths = sg.GetPatterns(2U);

	//BOOST_TEST(paths != NULL);
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
