#define BOOST_TEST_MODULE CircusSimulationBoostTest
#include <boost/test/included/unit_test.hpp>

#include <vector>

#include "Struct.h"
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



BOOST_AUTO_TEST_CASE(GetPatterns_Balls3_Throws3_Max6)
{
	auto * patterns = SiteswapGraph(6).GetPatterns(3, 3);
	BOOST_CHECK(patterns != NULL);
	BOOST_TEST(patterns->size() == 7U);

	std::vector<SiteswapGraphConnection> results;

	results.push_back({ 7U, 11U, 4U });		// 4 4 1
	results.push_back({ 11U, 13U, 4U });
	results.push_back({ 13U, 7U, 1U });

	results.push_back({ 11U, 13U, 4U });	// 4 5 0
	results.push_back({ 13U, 22U, 5U });
	results.push_back({ 22U, 11U, 0U });

	results.push_back({ 7U, 19U, 5U });		// 5 2 2
	results.push_back({ 19U, 11U, 2U });
	results.push_back({ 11U, 7U, 2U });

	results.push_back({ 7U, 19U, 5U });		// 5 3 1
	results.push_back({ 19U, 13U, 3U });
	results.push_back({ 13U, 7U, 1U });

	results.push_back({ 13U, 38U, 6U });	// 6 0 3
	results.push_back({ 38U, 19U, 0U });
	results.push_back({ 19U, 13U, 3U });

	results.push_back({ 11U, 37U, 6U });	// 6 1 2
	results.push_back({ 37U, 19U, 1U });
	results.push_back({ 19U, 11U, 2U });

	results.push_back({ 11U, 37U, 6U });	// 6 3 0
	results.push_back({ 37U, 22U, 3U });
	results.push_back({ 22U, 11U, 0U });

	std::set<SiteswapPattern> patterns_test;

	auto results_begin = results.begin();

	for (unsigned int i = 0U; i < 7U; i++)
	{
		std::deque<SiteswapGraphConnection> i_deque;
		for (unsigned int j = 0U; j < 3U; j++)
		{
			i_deque.push_back(*results_begin);
			results_begin++;
		}

		patterns_test.insert({ 3U, i_deque });
	}

	auto i_patterns = patterns->begin();
	auto i_patterns_test = patterns_test.begin();

	while (i_patterns != patterns->end())
	{
		BOOST_TEST((*i_patterns) == (*i_patterns_test));
		i_patterns++; i_patterns_test++;
	}

	delete patterns;
}



BOOST_AUTO_TEST_CASE(GetPatterns_Balls4_Throws3_Max7)
{
	auto* patterns = SiteswapGraph(7).GetPatterns(4, 3);
	BOOST_CHECK(patterns != NULL);
	BOOST_TEST(patterns->size() == 9U);

	std::vector<SiteswapGraphConnection> results;

	results.push_back({ 15U, 23U, 5U });		// 5 5 2
	results.push_back({ 23U, 27U, 5U });
	results.push_back({ 27U, 15U, 2U });

	results.push_back({ 23U, 27U, 5U });		// 5 6 1
	results.push_back({ 27U, 45U, 6U });
	results.push_back({ 45U, 23U, 1U });

	results.push_back({ 15U, 39U, 6U });		// 6 3 3
	results.push_back({ 39U, 23U, 3U });
	results.push_back({ 23U, 15U, 3U });

	results.push_back({ 15U, 39U, 6U });		// 6 4 2
	results.push_back({ 39U, 27U, 4U });
	results.push_back({ 27U, 15U, 2U });

	results.push_back({ 27U, 45U, 6U });		// 6 6 0
	results.push_back({ 45U, 54U, 6U });
	results.push_back({ 54U, 27U, 0U });

	results.push_back({ 27U, 77U, 7U });		// 7 1 4
	results.push_back({ 77U, 39U, 1U });
	results.push_back({ 39U, 27U, 4U });

	results.push_back({ 23U, 75U, 7U });		// 7 2 3
	results.push_back({ 75U, 39U, 2U });
	results.push_back({ 39U, 23U, 3U });

	results.push_back({ 23U, 75U, 7U });		// 7 4 1
	results.push_back({ 75U, 45U, 4U });
	results.push_back({ 45U, 23U, 1U });

	results.push_back({ 27U, 77U, 7U });		// 7 5 0
	results.push_back({ 77U, 54U, 5U });
	results.push_back({ 54U, 27U, 0U });

	std::set<SiteswapPattern> patterns_test;

	auto results_begin = results.begin();

	for (unsigned int i = 0U; i < 9U; i++)
	{
		std::deque<SiteswapGraphConnection> i_deque;
		for (unsigned int j = 0U; j < 3U; j++)
		{
			i_deque.push_back(*results_begin);
			results_begin++;
		}

		patterns_test.insert({ 4U, i_deque });
	}

	auto i_patterns = patterns->begin();
	auto i_patterns_test = patterns_test.begin();

	while (i_patterns != patterns->end())
	{
		BOOST_TEST((*i_patterns) == (*i_patterns_test));
		i_patterns++; i_patterns_test++;
	}

	delete patterns;
}



BOOST_AUTO_TEST_CASE(GetPatterns_Balls5_Throws3_Max8)
{
	auto* patterns = SiteswapGraph(8).GetPatterns(5, 3);
	BOOST_CHECK(patterns != NULL);
	BOOST_TEST(patterns->size() == 10U);

	std::vector<SiteswapGraphConnection> results;

	results.push_back({ 31U, 47U, 6U });			// 6 6 3
	results.push_back({ 47U, 55U, 6U });
	results.push_back({ 55U, 31U, 3U });

	results.push_back({ 47U, 55U, 6U });			// 6 7 2
	results.push_back({ 55U, 91U, 7U });
	results.push_back({ 91U, 47U, 2U });

	results.push_back({ 31U, 79U, 7U });			// 7 4 4
	results.push_back({ 79U, 47U, 4U });
	results.push_back({ 47U, 31U, 4U });

	results.push_back({ 31U, 79U, 7U });			// 7 5 3
	results.push_back({ 79U, 55U, 5U });
	results.push_back({ 55U, 31U, 3U });

	results.push_back({ 55U, 91U, 7U });			// 7 7 1
	results.push_back({ 91U, 109U, 7U });
	results.push_back({ 109U, 55U, 1U });

	results.push_back({ 91U, 109U, 7U });			// 7 8 0
	results.push_back({ 109U, 182U, 8U });
	results.push_back({ 182U, 91U, 0U });

	results.push_back({ 55U, 155U, 8U });			// 8 2 5
	results.push_back({ 155U, 79U, 2U });
	results.push_back({ 79U, 55U, 5U });

	results.push_back({ 47U, 151U, 8U });			// 8 3 4
	results.push_back({ 151U, 79U, 3U });
	results.push_back({ 79U, 47U, 4U });

	results.push_back({ 47U, 151U, 8U });			// 8 5 2
	results.push_back({ 151U, 91U, 5U });
	results.push_back({ 91U, 47U, 2U });

	results.push_back({ 55U, 155U, 8U });			// 8 6 1
	results.push_back({ 155U, 109U, 6U });
	results.push_back({ 109U, 55U, 1U });

	std::set<SiteswapPattern> patterns_test;

	auto results_begin = results.begin();

	for (unsigned int i = 0U; i < 10U; i++)
	{
		std::deque<SiteswapGraphConnection> i_deque;
		for (unsigned int j = 0U; j < 3U; j++)
		{
			i_deque.push_back(*results_begin);
			results_begin++;
		}

		patterns_test.insert({ 5U, i_deque });
	}

	auto i_patterns = patterns->begin();
	auto i_patterns_test = patterns_test.begin();

	while (i_patterns != patterns->end())
	{
		BOOST_TEST((*i_patterns) == (*i_patterns_test));
		i_patterns++; i_patterns_test++;
	}

	delete patterns;
}
