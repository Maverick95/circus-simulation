#ifndef SITESWAP_GRAPH_MULTI_ACTION_TEST_H
#define SITESWAP_GRAPH_MULTI_ACTION_TEST_H



#include "SiteswapGraphMultiActionFunctions.h"



BOOST_AUTO_TEST_SUITE(SiteswapGraphMultiActionTest)



BOOST_AUTO_TEST_CASE(BitSpread_Case_1)
{
	std::vector<UIntStore> results;
	SiteswapGraphMultiAction::BitSpread(results, 4U, 4U, 10U);

	BOOST_TEST(results.size() == 7U);

	BOOST_TEST(results[0U][0U] == 4U);
	BOOST_TEST(results[0U][1U] == 4U);
	BOOST_TEST(results[0U][2U] == 2U);
	BOOST_TEST(results[0U][3U] == 0U);

	BOOST_TEST(results[1U][0U] == 4U);
	BOOST_TEST(results[1U][1U] == 4U);
	BOOST_TEST(results[1U][2U] == 1U);
	BOOST_TEST(results[1U][3U] == 1U);

	BOOST_TEST(results[2U][0U] == 4U);
	BOOST_TEST(results[2U][1U] == 3U);
	BOOST_TEST(results[2U][2U] == 3U);
	BOOST_TEST(results[2U][3U] == 0U);

	BOOST_TEST(results[3U][0U] == 4U);
	BOOST_TEST(results[3U][1U] == 3U);
	BOOST_TEST(results[3U][2U] == 2U);
	BOOST_TEST(results[3U][3U] == 1U);

	BOOST_TEST(results[4U][0U] == 4U);
	BOOST_TEST(results[4U][1U] == 2U);
	BOOST_TEST(results[4U][2U] == 2U);
	BOOST_TEST(results[4U][3U] == 2U);

	BOOST_TEST(results[5U][0U] == 3U);
	BOOST_TEST(results[5U][1U] == 3U);
	BOOST_TEST(results[5U][2U] == 3U);
	BOOST_TEST(results[5U][3U] == 1U);

	BOOST_TEST(results[6U][0U] == 3U);
	BOOST_TEST(results[6U][1U] == 3U);
	BOOST_TEST(results[6U][2U] == 2U);
	BOOST_TEST(results[6U][3U] == 2U);
}



BOOST_AUTO_TEST_CASE(BitSpread_Case_2)
{
	std::vector<UIntStore> results;
	SiteswapGraphMultiAction::BitSpread(results, 5U, 4U, 15U);

	BOOST_TEST(results.size() == 6U);

	BOOST_TEST(results[0U][0U] == 4U);
	BOOST_TEST(results[0U][1U] == 4U);
	BOOST_TEST(results[0U][2U] == 4U);
	BOOST_TEST(results[0U][3U] == 3U);
	BOOST_TEST(results[0U][4U] == 0U);

	BOOST_TEST(results[1U][0U] == 4U);
	BOOST_TEST(results[1U][1U] == 4U);
	BOOST_TEST(results[1U][2U] == 4U);
	BOOST_TEST(results[1U][3U] == 2U);
	BOOST_TEST(results[1U][4U] == 1U);

	BOOST_TEST(results[2U][0U] == 4U);
	BOOST_TEST(results[2U][1U] == 4U);
	BOOST_TEST(results[2U][2U] == 3U);
	BOOST_TEST(results[2U][3U] == 3U);
	BOOST_TEST(results[2U][4U] == 1U);

	BOOST_TEST(results[3U][0U] == 4U);
	BOOST_TEST(results[3U][1U] == 4U);
	BOOST_TEST(results[3U][2U] == 3U);
	BOOST_TEST(results[3U][3U] == 2U);
	BOOST_TEST(results[3U][4U] == 2U);

	BOOST_TEST(results[4U][0U] == 4U);
	BOOST_TEST(results[4U][1U] == 3U);
	BOOST_TEST(results[4U][2U] == 3U);
	BOOST_TEST(results[4U][3U] == 3U);
	BOOST_TEST(results[4U][4U] == 2U);

	BOOST_TEST(results[5U][0U] == 3U);
	BOOST_TEST(results[5U][1U] == 3U);
	BOOST_TEST(results[5U][2U] == 3U);
	BOOST_TEST(results[5U][3U] == 3U);
	BOOST_TEST(results[5U][4U] == 3U);
}



BOOST_AUTO_TEST_CASE(BitSpread_Case_3)
{
	std::vector<UIntStore> results;
	SiteswapGraphMultiAction::BitSpread(results, 3U, 7U, 7U);

	BOOST_TEST(results.size() == 8U);

	BOOST_TEST(results[0U][0U] == 7U);
	BOOST_TEST(results[0U][1U] == 0U);
	BOOST_TEST(results[0U][2U] == 0U);

	BOOST_TEST(results[1U][0U] == 6U);
	BOOST_TEST(results[1U][1U] == 1U);
	BOOST_TEST(results[1U][2U] == 0U);

	BOOST_TEST(results[2U][0U] == 5U);
	BOOST_TEST(results[2U][1U] == 2U);
	BOOST_TEST(results[2U][2U] == 0U);

	BOOST_TEST(results[3U][0U] == 5U);
	BOOST_TEST(results[3U][1U] == 1U);
	BOOST_TEST(results[3U][2U] == 1U);

	BOOST_TEST(results[4U][0U] == 4U);
	BOOST_TEST(results[4U][1U] == 3U);
	BOOST_TEST(results[4U][2U] == 0U);

	BOOST_TEST(results[5U][0U] == 4U);
	BOOST_TEST(results[5U][1U] == 2U);
	BOOST_TEST(results[5U][2U] == 1U);

	BOOST_TEST(results[6U][0U] == 3U);
	BOOST_TEST(results[6U][1U] == 3U);
	BOOST_TEST(results[6U][2U] == 1U);

	BOOST_TEST(results[7U][0U] == 3U);
	BOOST_TEST(results[7U][1U] == 2U);
	BOOST_TEST(results[7U][2U] == 2U);
}



BOOST_AUTO_TEST_CASE(BitLowest)
{
	unsigned int
		result_1 = SiteswapGraphMultiAction::BitLowest(0U),
		result_2 = SiteswapGraphMultiAction::BitLowest(1U),
		result_3 = SiteswapGraphMultiAction::BitLowest(2U),
		result_4 = SiteswapGraphMultiAction::BitLowest(3U),
		result_5 = SiteswapGraphMultiAction::BitLowest(4U),
		result_6 = SiteswapGraphMultiAction::BitLowest(5U);

	BOOST_TEST(result_1 == 0U);
	BOOST_TEST(result_2 == 1U);
	BOOST_TEST(result_3 == 3U);
	BOOST_TEST(result_4 == 7U);
	BOOST_TEST(result_5 == 15U);
	BOOST_TEST(result_6 == 31U);
}

/*

BOOST_AUTO_TEST_CASE(BitNext_Invalid)
{
	// All cases should return false, integer unaltered.

	unsigned int
		input_1 = 0U,		// 0 0 0 0 0 0 
		input_2 = 56U;		// 0 0 0 1 1 1

	unsigned int
		max_1 = 0U,
		max_2 = 6U;

	BOOST_TEST(SiteswapGraphMultiAction::BitNext(input_1, max_1) == false);
	BOOST_TEST(input_1 == 0U);

	BOOST_TEST(SiteswapGraphMultiAction::BitNext(input_2, max_2) == false);
	BOOST_TEST(input_2 == 56U);
}



BOOST_AUTO_TEST_CASE(BitNext_Valid)
{
	// All cases should update integers to intended results.

	unsigned int
		input_1 = 56U,		// 0 0 0 1 1 1 0
		input_2 = 13U,		// 1 0 1 1 0 0 0
		input_3 = 47U;		// 1 1 1 1 0 1 0

	unsigned int
		max_1 = 7U,
		max_2 = 5U,
		max_3 = 7U;

	unsigned int
		output_1 = 67U,
		output_2 = 14U,
		output_3 = 55U;

	BOOST_TEST(SiteswapGraphMultiAction::BitNext(input_1, max_1) == true);
	BOOST_TEST(input_1 == output_1);

	BOOST_TEST(SiteswapGraphMultiAction::BitNext(input_2, max_2) == true);
	BOOST_TEST(input_2 == output_2);

	BOOST_TEST(SiteswapGraphMultiAction::BitNext(input_3, max_3) == true);
	BOOST_TEST(input_3 == output_3);
}

*/

BOOST_AUTO_TEST_SUITE_END()



#endif
