#ifndef SITESWAP_GRAPH_MULTI_ACTION_TEST_H
#define SITESWAP_GRAPH_MULTI_ACTION_TEST_H



BOOST_AUTO_TEST_SUITE(SiteswapGraphMultiActionTest)



BOOST_AUTO_TEST_CASE(StoreValidBeginStates_Case_Edge)
{
	std::vector<UIntStore> result;
	SiteswapGraphMultiAction::StoreValidBeginStates(result, 2U, 2U, 5U);
	BOOST_TEST(result.size() == 0U);
}



BOOST_AUTO_TEST_CASE(StoreValidBeginStates_Case_1)
{
	std::vector<UIntStore> result;
	SiteswapGraphMultiAction::StoreValidBeginStates(result, 1U, 5U, 3U);
	BOOST_TEST(result.size() == 10U);

	BOOST_TEST(result[0U]() == 7U);
	BOOST_TEST(result[1U]() == 11U);
	BOOST_TEST(result[2U]() == 13U);
	BOOST_TEST(result[3U]() == 14U);
	BOOST_TEST(result[4U]() == 19U);
	BOOST_TEST(result[5U]() == 21U);
	BOOST_TEST(result[6U]() == 22U);
	BOOST_TEST(result[7U]() == 25U);
	BOOST_TEST(result[8U]() == 26U);
	BOOST_TEST(result[9U]() == 28U);
}



BOOST_AUTO_TEST_CASE(StoreValidBeginStates_Case_2)
{
	std::vector<UIntStore> result;
	SiteswapGraphMultiAction::StoreValidBeginStates(result, 2U, 3U, 3U);
	BOOST_TEST(result.size() == 10U);

	BOOST_TEST(result[0U][0U] == 7U);
	BOOST_TEST(result[0U][1U] == 0U);

	BOOST_TEST(result[1U][0U] == 3U);
	BOOST_TEST(result[1U][1U] == 1U);

	BOOST_TEST(result[2U][0U] == 3U);
	BOOST_TEST(result[2U][1U] == 2U);

	BOOST_TEST(result[3U][0U] == 3U);
	BOOST_TEST(result[3U][1U] == 4U);

	BOOST_TEST(result[4U][0U] == 5U);
	BOOST_TEST(result[4U][1U] == 1U);

	BOOST_TEST(result[5U][0U] == 5U);
	BOOST_TEST(result[5U][1U] == 2U);

	BOOST_TEST(result[6U][0U] == 5U);
	BOOST_TEST(result[6U][1U] == 4U);

	BOOST_TEST(result[7U][0U] == 6U);
	BOOST_TEST(result[7U][1U] == 1U);

	BOOST_TEST(result[8U][0U] == 6U);
	BOOST_TEST(result[8U][1U] == 2U);

	BOOST_TEST(result[9U][0U] == 6U);
	BOOST_TEST(result[9U][1U] == 4U);
}



BOOST_AUTO_TEST_CASE(StoreValidBeginStates_Case_3)
{
	std::vector<UIntStore> result;
	SiteswapGraphMultiAction::StoreValidBeginStates(result, 3U, 3U, 4U);
	BOOST_TEST(result.size() == 27U);

	// Combo 1.

	BOOST_TEST(result[0U][0U] == 7U);
	BOOST_TEST(result[0U][1U] == 1U);
	BOOST_TEST(result[0U][2U] == 0U);
	
	BOOST_TEST(result[1U][0U] == 7U);
	BOOST_TEST(result[1U][1U] == 2U);
	BOOST_TEST(result[1U][2U] == 0U);

	BOOST_TEST(result[2U][0U] == 7U);
	BOOST_TEST(result[2U][1U] == 4U);
	BOOST_TEST(result[2U][2U] == 0U);

	// Combo 4.

	BOOST_TEST(result[3U][0U] == 3U);
	BOOST_TEST(result[3U][1U] == 3U);
	BOOST_TEST(result[3U][2U] == 0U);

	BOOST_TEST(result[4U][0U] == 5U);
	BOOST_TEST(result[4U][1U] == 3U);
	BOOST_TEST(result[4U][2U] == 0U);

	BOOST_TEST(result[5U][0U] == 5U);
	BOOST_TEST(result[5U][1U] == 5U);
	BOOST_TEST(result[5U][2U] == 0U);

	// Combo 7.

	BOOST_TEST(result[6U][0U] == 6U);
	BOOST_TEST(result[6U][1U] == 3U);
	BOOST_TEST(result[6U][2U] == 0U);

	BOOST_TEST(result[7U][0U] == 6U);
	BOOST_TEST(result[7U][1U] == 5U);
	BOOST_TEST(result[7U][2U] == 0U);

	BOOST_TEST(result[8U][0U] == 6U);
	BOOST_TEST(result[8U][1U] == 6U);
	BOOST_TEST(result[8U][2U] == 0U);

	// Combo 10.

	BOOST_TEST(result[9U][0U] == 3U);
	BOOST_TEST(result[9U][1U] == 1U);
	BOOST_TEST(result[9U][2U] == 1U);

	BOOST_TEST(result[10U][0U] == 3U);
	BOOST_TEST(result[10U][1U] == 2U);
	BOOST_TEST(result[10U][2U] == 1U);

	BOOST_TEST(result[11U][0U] == 3U);
	BOOST_TEST(result[11U][1U] == 2U);
	BOOST_TEST(result[11U][2U] == 2U);

	// Combo 13.

	BOOST_TEST(result[12U][0U] == 3U);
	BOOST_TEST(result[12U][1U] == 4U);
	BOOST_TEST(result[12U][2U] == 1U);

	BOOST_TEST(result[13U][0U] == 3U);
	BOOST_TEST(result[13U][1U] == 4U);
	BOOST_TEST(result[13U][2U] == 2U);

	BOOST_TEST(result[14U][0U] == 3U);
	BOOST_TEST(result[14U][1U] == 4U);
	BOOST_TEST(result[14U][2U] == 4U);

	// Combo 16.

	BOOST_TEST(result[15U][0U] == 5U);
	BOOST_TEST(result[15U][1U] == 1U);
	BOOST_TEST(result[15U][2U] == 1U);

	BOOST_TEST(result[16U][0U] == 5U);
	BOOST_TEST(result[16U][1U] == 2U);
	BOOST_TEST(result[16U][2U] == 1U);

	BOOST_TEST(result[17U][0U] == 5U);
	BOOST_TEST(result[17U][1U] == 2U);
	BOOST_TEST(result[17U][2U] == 2U);

	// Combo 19.

	BOOST_TEST(result[18U][0U] == 5U);
	BOOST_TEST(result[18U][1U] == 4U);
	BOOST_TEST(result[18U][2U] == 1U);

	BOOST_TEST(result[19U][0U] == 5U);
	BOOST_TEST(result[19U][1U] == 4U);
	BOOST_TEST(result[19U][2U] == 2U);

	BOOST_TEST(result[20U][0U] == 5U);
	BOOST_TEST(result[20U][1U] == 4U);
	BOOST_TEST(result[20U][2U] == 4U);

	// Combo 22.

	BOOST_TEST(result[21U][0U] == 6U);
	BOOST_TEST(result[21U][1U] == 1U);
	BOOST_TEST(result[21U][2U] == 1U);

	BOOST_TEST(result[22U][0U] == 6U);
	BOOST_TEST(result[22U][1U] == 2U);
	BOOST_TEST(result[22U][2U] == 1U);

	BOOST_TEST(result[23U][0U] == 6U);
	BOOST_TEST(result[23U][1U] == 2U);
	BOOST_TEST(result[23U][2U] == 2U);

	// Combo 25.

	BOOST_TEST(result[24U][0U] == 6U);
	BOOST_TEST(result[24U][1U] == 4U);
	BOOST_TEST(result[24U][2U] == 1U);

	BOOST_TEST(result[25U][0U] == 6U);
	BOOST_TEST(result[25U][1U] == 4U);
	BOOST_TEST(result[25U][2U] == 2U);

	BOOST_TEST(result[26U][0U] == 6U);
	BOOST_TEST(result[26U][1U] == 4U);
	BOOST_TEST(result[26U][2U] == 4U);
}



BOOST_AUTO_TEST_CASE(StoreValidSpreadsOfBitsAcrossActions_Case_1)
{
	std::vector<UIntStore> results;
	SiteswapGraphMultiAction::StoreValidSpreadsOfBitsAcrossActions(results, 4U, 4U, 10U);

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



BOOST_AUTO_TEST_CASE(StoreValidSpreadsOfBitsAcrossActions_Case_2)
{
	std::vector<UIntStore> results;
	SiteswapGraphMultiAction::StoreValidSpreadsOfBitsAcrossActions(results, 5U, 4U, 15U);

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



BOOST_AUTO_TEST_CASE(StoreValidSpreadsOfBitsAcrossActions_Case_3)
{
	std::vector<UIntStore> results;
	SiteswapGraphMultiAction::StoreValidSpreadsOfBitsAcrossActions(results, 3U, 7U, 7U);

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



BOOST_AUTO_TEST_CASE(GetLowestIntegerWithNBits)
{
	unsigned int
		result_1 = SiteswapGraphMultiAction::GetLowestIntegerWithNBits(0U),
		result_2 = SiteswapGraphMultiAction::GetLowestIntegerWithNBits(1U),
		result_3 = SiteswapGraphMultiAction::GetLowestIntegerWithNBits(2U),
		result_4 = SiteswapGraphMultiAction::GetLowestIntegerWithNBits(3U),
		result_5 = SiteswapGraphMultiAction::GetLowestIntegerWithNBits(4U),
		result_6 = SiteswapGraphMultiAction::GetLowestIntegerWithNBits(5U);

	BOOST_TEST(result_1 == 0U);
	BOOST_TEST(result_2 == 1U);
	BOOST_TEST(result_3 == 3U);
	BOOST_TEST(result_4 == 7U);
	BOOST_TEST(result_5 == 15U);
	BOOST_TEST(result_6 == 31U);
}

BOOST_AUTO_TEST_SUITE_END()



#endif
