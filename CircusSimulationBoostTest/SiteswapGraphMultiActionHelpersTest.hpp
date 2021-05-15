#ifndef SITESWAP_GRAPH_MULTI_ACTION_HELPERS_TEST_H
#define SITESWAP_GRAPH_MULTI_ACTION_HELPERS_TEST_H



BOOST_AUTO_TEST_SUITE(SiteswapGraphMultiActionHelpersTest)



BOOST_AUTO_TEST_CASE(StoreValidBeginStates_Example_1)
{
	unsigned int bits = 3U;
	unsigned int max = 5U;

	UIntStore store(1U, &bits);
	std::vector<UIntStore> result;
	SiteswapGraphMultiActionHelpers::StoreValidBeginStates(result, store, max);

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



BOOST_AUTO_TEST_CASE(StoreValidBeginStates_Example_2)
{
	unsigned int* data = new unsigned int[2];
	data[0] = 4U;
	data[1] = 0U;

	UIntStore store(2U, data);
	std::vector<UIntStore> result;
	SiteswapGraphMultiActionHelpers::StoreValidBeginStates(result, store, 4U);

	BOOST_TEST(result.size() == 1U);
	
	BOOST_TEST(result[0][0] == 15U);
	BOOST_TEST(result[0][1] == 0U);

	delete[] data;
}



BOOST_AUTO_TEST_CASE(StoreValidBeginStates_Example_3)
{
	unsigned int* data = new unsigned int[2];
	data[0] = 3U;
	data[1] = 1U;

	UIntStore store(2U, data);
	std::vector<UIntStore> result;
	SiteswapGraphMultiActionHelpers::StoreValidBeginStates(result, store, 4U);

	BOOST_TEST(result.size() == 16U);

	// ---

	BOOST_TEST(result[0][0] == 7U);
	BOOST_TEST(result[0][1] == 1U);

	BOOST_TEST(result[1][0] == 7U);
	BOOST_TEST(result[1][1] == 2U);

	BOOST_TEST(result[2][0] == 7U);
	BOOST_TEST(result[2][1] == 4U);

	BOOST_TEST(result[3][0] == 7U);
	BOOST_TEST(result[3][1] == 8U);

	// ---

	BOOST_TEST(result[4][0] == 11U);
	BOOST_TEST(result[4][1] == 1U);

	BOOST_TEST(result[5][0] == 11U);
	BOOST_TEST(result[5][1] == 2U);

	BOOST_TEST(result[6][0] == 11U);
	BOOST_TEST(result[6][1] == 4U);

	BOOST_TEST(result[7][0] == 11U);
	BOOST_TEST(result[7][1] == 8U);

	// ---

	BOOST_TEST(result[8][0] == 13U);
	BOOST_TEST(result[8][1] == 1U);

	BOOST_TEST(result[9][0] == 13U);
	BOOST_TEST(result[9][1] == 2U);

	BOOST_TEST(result[10][0] == 13U);
	BOOST_TEST(result[10][1] == 4U);

	BOOST_TEST(result[11][0] == 13U);
	BOOST_TEST(result[11][1] == 8U);

	// ---

	BOOST_TEST(result[12][0] == 14U);
	BOOST_TEST(result[12][1] == 1U);

	BOOST_TEST(result[13][0] == 14U);
	BOOST_TEST(result[13][1] == 2U);

	BOOST_TEST(result[14][0] == 14U);
	BOOST_TEST(result[14][1] == 4U);

	BOOST_TEST(result[15][0] == 14U);
	BOOST_TEST(result[15][1] == 8U);

	// ---

	delete[] data;
}



BOOST_AUTO_TEST_CASE(StoreValidBeginStates_Example_4)
{
	unsigned int* data = new unsigned int[2];
	data[0] = 2U;
	data[1] = 2U;

	UIntStore store(2U, data);
	std::vector<UIntStore> result;
	SiteswapGraphMultiActionHelpers::StoreValidBeginStates(result, store, 4U);

	BOOST_TEST(result.size() == 21U);

	// ---

	BOOST_TEST(result[0][0] == 3U);
	BOOST_TEST(result[0][1] == 3U);

	BOOST_TEST(result[1][0] == 5U);
	BOOST_TEST(result[1][1] == 3U);

	BOOST_TEST(result[2][0] == 5U);
	BOOST_TEST(result[2][1] == 5U);

	BOOST_TEST(result[3][0] == 6U);
	BOOST_TEST(result[3][1] == 3U);

	// ---

	BOOST_TEST(result[4][0] == 6U);
	BOOST_TEST(result[4][1] == 5U);

	BOOST_TEST(result[5][0] == 6U);
	BOOST_TEST(result[5][1] == 6U);

	BOOST_TEST(result[6][0] == 9U);
	BOOST_TEST(result[6][1] == 3U);

	BOOST_TEST(result[7][0] == 9U);
	BOOST_TEST(result[7][1] == 5U);

	// ---

	BOOST_TEST(result[8][0] == 9U);
	BOOST_TEST(result[8][1] == 6U);

	BOOST_TEST(result[9][0] == 9U);
	BOOST_TEST(result[9][1] == 9U);

	BOOST_TEST(result[10][0] == 10U);
	BOOST_TEST(result[10][1] == 3U);

	BOOST_TEST(result[11][0] == 10U);
	BOOST_TEST(result[11][1] == 5U);

	// ---

	BOOST_TEST(result[12][0] == 10U);
	BOOST_TEST(result[12][1] == 6U);

	BOOST_TEST(result[13][0] == 10U);
	BOOST_TEST(result[13][1] == 9U);

	BOOST_TEST(result[14][0] == 10U);
	BOOST_TEST(result[14][1] == 10U);

	BOOST_TEST(result[15][0] == 12U);
	BOOST_TEST(result[15][1] == 3U);

	// ---

	BOOST_TEST(result[16][0] == 12U);
	BOOST_TEST(result[16][1] == 5U);

	BOOST_TEST(result[17][0] == 12U);
	BOOST_TEST(result[17][1] == 6U);

	BOOST_TEST(result[18][0] == 12U);
	BOOST_TEST(result[18][1] == 9U);

	BOOST_TEST(result[19][0] == 12U);
	BOOST_TEST(result[19][1] == 10U);

	// ---

	BOOST_TEST(result[20][0] == 12U);
	BOOST_TEST(result[20][1] == 12U);

	delete[] data;
}



BOOST_AUTO_TEST_CASE(StoreValidBeginStates_Example_5)
{
	unsigned int* data = new unsigned int[3];
	data[0] = 2U;
	data[1] = 1U;
	data[2] = 1U;

	UIntStore store(3U, data);
	std::vector<UIntStore> result;
	SiteswapGraphMultiActionHelpers::StoreValidBeginStates(result, store, 3U);

	BOOST_TEST(result.size() == 18U);

	// ---

	BOOST_TEST(result[0][0] == 3U);
	BOOST_TEST(result[0][1] == 1U);
	BOOST_TEST(result[0][2] == 1U);

	BOOST_TEST(result[1][0] == 3U);
	BOOST_TEST(result[1][1] == 2U);
	BOOST_TEST(result[1][2] == 1U);

	BOOST_TEST(result[2][0] == 3U);
	BOOST_TEST(result[2][1] == 2U);
	BOOST_TEST(result[2][2] == 2U);

	// ---

	BOOST_TEST(result[3][0] == 3U);
	BOOST_TEST(result[3][1] == 4U);
	BOOST_TEST(result[3][2] == 1U);

	BOOST_TEST(result[4][0] == 3U);
	BOOST_TEST(result[4][1] == 4U);
	BOOST_TEST(result[4][2] == 2U);

	BOOST_TEST(result[5][0] == 3U);
	BOOST_TEST(result[5][1] == 4U);
	BOOST_TEST(result[5][2] == 4U);

	// ---

	BOOST_TEST(result[6][0] == 5U);
	BOOST_TEST(result[6][1] == 1U);
	BOOST_TEST(result[6][2] == 1U);

	BOOST_TEST(result[7][0] == 5U);
	BOOST_TEST(result[7][1] == 2U);
	BOOST_TEST(result[7][2] == 1U);

	BOOST_TEST(result[8][0] == 5U);
	BOOST_TEST(result[8][1] == 2U);
	BOOST_TEST(result[8][2] == 2U);

	// ---

	BOOST_TEST(result[9][0] == 5U);
	BOOST_TEST(result[9][1] == 4U);
	BOOST_TEST(result[9][2] == 1U);

	BOOST_TEST(result[10][0] == 5U);
	BOOST_TEST(result[10][1] == 4U);
	BOOST_TEST(result[10][2] == 2U);

	BOOST_TEST(result[11][0] == 5U);
	BOOST_TEST(result[11][1] == 4U);
	BOOST_TEST(result[11][2] == 4U);

	// ---

	BOOST_TEST(result[12][0] == 6U);
	BOOST_TEST(result[12][1] == 1U);
	BOOST_TEST(result[12][2] == 1U);

	BOOST_TEST(result[13][0] == 6U);
	BOOST_TEST(result[13][1] == 2U);
	BOOST_TEST(result[13][2] == 1U);

	BOOST_TEST(result[14][0] == 6U);
	BOOST_TEST(result[14][1] == 2U);
	BOOST_TEST(result[14][2] == 2U);

	// ---

	BOOST_TEST(result[15][0] == 6U);
	BOOST_TEST(result[15][1] == 4U);
	BOOST_TEST(result[15][2] == 1U);

	BOOST_TEST(result[16][0] == 6U);
	BOOST_TEST(result[16][1] == 4U);
	BOOST_TEST(result[16][2] == 2U);

	BOOST_TEST(result[17][0] == 6U);
	BOOST_TEST(result[17][1] == 4U);
	BOOST_TEST(result[17][2] == 4U);

	// ---

	delete[] data;
}



BOOST_AUTO_TEST_CASE(StoreValidSpreadsOfBitsAcrossActions_Case_1)
{
	std::vector<UIntStore> results;
	SiteswapGraphMultiActionHelpers::StoreValidSpreadsOfBitsAcrossActions(results, 4U, 4U, 10U);

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
	SiteswapGraphMultiActionHelpers::StoreValidSpreadsOfBitsAcrossActions(results, 5U, 4U, 15U);

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
	SiteswapGraphMultiActionHelpers::StoreValidSpreadsOfBitsAcrossActions(results, 3U, 7U, 7U);

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



BOOST_AUTO_TEST_SUITE_END()



#endif