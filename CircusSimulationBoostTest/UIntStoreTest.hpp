#ifndef UINT_STORE_TEST_H
#define UINT_STORE_TEST_H



BOOST_AUTO_TEST_SUITE(UIntStoreTest)



BOOST_AUTO_TEST_CASE(UIntStore_Single)
{
	const unsigned int state = 7U;

	UIntStore ss(state);
	BOOST_TEST(ss() == state);
}



BOOST_AUTO_TEST_CASE(UIntStore_Multi)
{
	const unsigned int state = 7U;
	const unsigned int state_size = 3U;

	unsigned int* states = new unsigned int[state_size];
	states[0U] = state;
	states[1U] = 0U;
	states[2U] = 0U;

	UIntStore ss(state_size, states);
	BOOST_TEST(ss() == state);
}



BOOST_AUTO_TEST_SUITE_END()



#endif
