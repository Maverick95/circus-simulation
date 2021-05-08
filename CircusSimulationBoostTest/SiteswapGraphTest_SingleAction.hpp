#ifndef SITESWAP_GRAPH_TEST_SINGLE_ACTION_H
#define SITESWAP_GRAPH_TEST_SINGLE_ACTION_H



BOOST_AUTO_TEST_SUITE(SiteswapGraphTest_SingleAction)



/*
* Test cases - 8 bits
*
* XXX-----		to		X-XX----		7		to		13		= 2
* X-XXX--X		to		-X-XX-XX		157		to		218		= 6
* X------X		to		--X---X-		129		to		68		= 1
* -X-XX-X-		to		XXXX----		90		to		15		= 3
*/



BOOST_AUTO_TEST_CASE(DoesPathExist_8bit)
{
	struct DeriveShortestPathTest
	{
		UIntStore state_begin, state_end;
		unsigned int path_length;
	};

	std::vector<DeriveShortestPathTest> tests;
	tests.push_back({ UIntStore(7U), UIntStore(13U), 2U });
	tests.push_back({ UIntStore(157U), UIntStore(218U), 6U });
	tests.push_back({ UIntStore(129U), UIntStore(68U), 1U });
	tests.push_back({ UIntStore(90U), UIntStore(15U), 3U });

	for (auto i = tests.begin(); i != tests.end(); i++)
	{
		BOOST_TEST(SiteswapGraph::DoesPathExist(i->state_begin, i->state_end, i->path_length) == true);
		BOOST_TEST(SiteswapGraph::DoesPathExist(i->state_begin, i->state_end, i->path_length - 1U) == false);
	}
}



BOOST_AUTO_TEST_CASE(GetPatterns_Balls3_Throws3_Max6)
{
	auto* patterns = SiteswapGraph::GetPatterns(3U, 1U, 3U, 6U);
	BOOST_CHECK(patterns != NULL);
	BOOST_TEST(patterns->size() == 7U);

	std::vector<SiteswapGraphConnection> results;

	// 4 4 1
	results.push_back(GenerateSingleActionConnection(7U, 11U, 4U));
	results.push_back(GenerateSingleActionConnection(11U, 13U, 4U));
	results.push_back(GenerateSingleActionConnection(13U, 7U, 1U));

	// 4 5 0
	results.push_back(GenerateSingleActionConnection(11U, 13U, 4U));
	results.push_back(GenerateSingleActionConnection(13U, 22U, 5U));
	results.push_back(GenerateSingleActionConnection(22U, 11U, 0U));

	// 5 2 2
	results.push_back(GenerateSingleActionConnection(7U, 19U, 5U));
	results.push_back(GenerateSingleActionConnection(19U, 11U, 2U));
	results.push_back(GenerateSingleActionConnection(11U, 7U, 2U));

	// 5 3 1
	results.push_back(GenerateSingleActionConnection(7U, 19U, 5U));
	results.push_back(GenerateSingleActionConnection(19U, 13U, 3U));
	results.push_back(GenerateSingleActionConnection(13U, 7U, 1U));

	// 6 0 3
	results.push_back(GenerateSingleActionConnection(13U, 38U, 6U));
	results.push_back(GenerateSingleActionConnection(38U, 19U, 0U));
	results.push_back(GenerateSingleActionConnection(19U, 13U, 3U));

	// 6 1 2
	results.push_back(GenerateSingleActionConnection(11U, 37U, 6U));
	results.push_back(GenerateSingleActionConnection(37U, 19U, 1U));
	results.push_back(GenerateSingleActionConnection(19U, 11U, 2U));

	// 6 3 0
	results.push_back(GenerateSingleActionConnection(11U, 37U, 6U));
	results.push_back(GenerateSingleActionConnection(37U, 22U, 3U));
	results.push_back(GenerateSingleActionConnection(22U, 11U, 0U));

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

		patterns_test.insert({ 3U, 1U, i_deque });
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
	auto* patterns = SiteswapGraph::GetPatterns(4U, 1U, 3U, 7U);
	BOOST_CHECK(patterns != NULL);
	BOOST_TEST(patterns->size() == 9U);

	std::vector<SiteswapGraphConnection> results;

	// 5 5 2
	results.push_back(GenerateSingleActionConnection(15U, 23U, 5U));
	results.push_back(GenerateSingleActionConnection(23U, 27U, 5U));
	results.push_back(GenerateSingleActionConnection(27U, 15U, 2U));

	// 5 6 1
	results.push_back(GenerateSingleActionConnection(23U, 27U, 5U));
	results.push_back(GenerateSingleActionConnection(27U, 45U, 6U));
	results.push_back(GenerateSingleActionConnection(45U, 23U, 1U));

	// 6 3 3
	results.push_back(GenerateSingleActionConnection(15U, 39U, 6U));
	results.push_back(GenerateSingleActionConnection(39U, 23U, 3U));
	results.push_back(GenerateSingleActionConnection(23U, 15U, 3U));

	// 6 4 2
	results.push_back(GenerateSingleActionConnection(15U, 39U, 6U));
	results.push_back(GenerateSingleActionConnection(39U, 27U, 4U));
	results.push_back(GenerateSingleActionConnection(27U, 15U, 2U));

	// 6 6 0
	results.push_back(GenerateSingleActionConnection(27U, 45U, 6U));
	results.push_back(GenerateSingleActionConnection(45U, 54U, 6U));
	results.push_back(GenerateSingleActionConnection(54U, 27U, 0U));

	// 7 1 4
	results.push_back(GenerateSingleActionConnection(27U, 77U, 7U));
	results.push_back(GenerateSingleActionConnection(77U, 39U, 1U));
	results.push_back(GenerateSingleActionConnection(39U, 27U, 4U));

	// 7 2 3
	results.push_back(GenerateSingleActionConnection(23U, 75U, 7U));
	results.push_back(GenerateSingleActionConnection(75U, 39U, 2U));
	results.push_back(GenerateSingleActionConnection(39U, 23U, 3U));

	// 7 4 1
	results.push_back(GenerateSingleActionConnection(23U, 75U, 7U));
	results.push_back(GenerateSingleActionConnection(75U, 45U, 4U));
	results.push_back(GenerateSingleActionConnection(45U, 23U, 1U));

	// 7 5 0
	results.push_back(GenerateSingleActionConnection(27U, 77U, 7U));
	results.push_back(GenerateSingleActionConnection(77U, 54U, 5U));
	results.push_back(GenerateSingleActionConnection(54U, 27U, 0U));

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

		patterns_test.insert({ 4U, 1U, i_deque });
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
	auto* patterns = SiteswapGraph::GetPatterns(5U, 1U, 3U, 8U);
	BOOST_CHECK(patterns != NULL);
	BOOST_TEST(patterns->size() == 10U);

	std::vector<SiteswapGraphConnection> results;

	// 6 6 3
	results.push_back(GenerateSingleActionConnection(31U, 47U, 6U));
	results.push_back(GenerateSingleActionConnection(47U, 55U, 6U));
	results.push_back(GenerateSingleActionConnection(55U, 31U, 3U));

	// 6 7 2
	results.push_back(GenerateSingleActionConnection(47U, 55U, 6U));
	results.push_back(GenerateSingleActionConnection(55U, 91U, 7U));
	results.push_back(GenerateSingleActionConnection(91U, 47U, 2U));

	// 7 4 4
	results.push_back(GenerateSingleActionConnection(31U, 79U, 7U));
	results.push_back(GenerateSingleActionConnection(79U, 47U, 4U));
	results.push_back(GenerateSingleActionConnection(47U, 31U, 4U));

	// 7 5 3
	results.push_back(GenerateSingleActionConnection(31U, 79U, 7U));
	results.push_back(GenerateSingleActionConnection(79U, 55U, 5U));
	results.push_back(GenerateSingleActionConnection(55U, 31U, 3U));

	// 7 7 1
	results.push_back(GenerateSingleActionConnection(55U, 91U, 7U));
	results.push_back(GenerateSingleActionConnection(91U, 109U, 7U));
	results.push_back(GenerateSingleActionConnection(109U, 55U, 1U));

	// 7 8 0
	results.push_back(GenerateSingleActionConnection(91U, 109U, 7U));
	results.push_back(GenerateSingleActionConnection(109U, 182U, 8U));
	results.push_back(GenerateSingleActionConnection(182U, 91U, 0U));

	// 8 2 5
	results.push_back(GenerateSingleActionConnection(55U, 155U, 8U));
	results.push_back(GenerateSingleActionConnection(155U, 79U, 2U));
	results.push_back(GenerateSingleActionConnection(79U, 55U, 5U));

	// 8 3 4
	results.push_back(GenerateSingleActionConnection(47U, 151U, 8U));
	results.push_back(GenerateSingleActionConnection(151U, 79U, 3U));
	results.push_back(GenerateSingleActionConnection(79U, 47U, 4U));

	// 8 5 2
	results.push_back(GenerateSingleActionConnection(47U, 151U, 8U));
	results.push_back(GenerateSingleActionConnection(151U, 91U, 5U));
	results.push_back(GenerateSingleActionConnection(91U, 47U, 2U));

	// 8 6 1
	results.push_back(GenerateSingleActionConnection(55U, 155U, 8U));
	results.push_back(GenerateSingleActionConnection(155U, 109U, 6U));
	results.push_back(GenerateSingleActionConnection(109U, 55U, 1U));

	std::set<SiteswapPattern> patterns_test;

	auto results_begin = results.begin();

	for (auto i = 0U; i < 10U; i++)
	{
		std::deque<SiteswapGraphConnection> i_deque;
		for (auto j = 0U; j < 3U; j++)
		{
			i_deque.push_back(*results_begin);
			results_begin++;
		}

		patterns_test.insert({ 5U, 1U, i_deque });
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



BOOST_AUTO_TEST_SUITE_END()



#endif