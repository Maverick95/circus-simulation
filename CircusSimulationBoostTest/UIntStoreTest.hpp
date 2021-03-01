#ifndef UINT_STORE_TEST_H
#define UINT_STORE_TEST_H



#include "UIntStore.h"

#include <sstream>


BOOST_AUTO_TEST_SUITE(UIntStoreTest)



BOOST_AUTO_TEST_CASE(Operator_Equality)
{
	auto* states_1 = new unsigned int[3U];
	auto* states_2 = new unsigned int[3U];
	auto* states_3 = new unsigned int[4U];

	states_1[0U] = 1U;
	states_1[1U] = 2U;
	states_1[2U] = 3U;

	states_2[0U] = 1U;
	states_2[1U] = 2U;
	states_2[2U] = 3U;

	states_3[0U] = 1U;
	states_3[1U] = 2U;
	states_3[2U] = 3U;
	states_3[3U] = 4U;

	UIntStore u1(3U, states_1), u2(3U, states_2), u3(4U, states_3);

	BOOST_TEST(u1 == u2);
	BOOST_TEST(u1 != u3);
	BOOST_TEST(u2 != u3);

	delete[] states_1;
	delete[] states_2;
	delete[] states_3;
}



BOOST_AUTO_TEST_CASE(Operator_Assignment)
{
	auto* states = new unsigned int[5U];

	states[0U] = 1U;
	states[1U] = 2U;
	states[2U] = 3U;
	states[3U] = 4U;
	states[4U] = 5U;

	UIntStore u1(5U, states);
	UIntStore u2 = u1;

	BOOST_TEST(u1 == u2);

	delete[] states;
}


BOOST_AUTO_TEST_CASE(Operator_Brackets)
{
	const unsigned int state = 7U;

	UIntStore ss1(state);
	BOOST_TEST(ss1() == state);

	const unsigned int state_size = 3U;

	unsigned int* states = new unsigned int[state_size];
	states[0U] = state;
	states[1U] = 0U;
	states[2U] = 0U;

	UIntStore ss2(state_size, states);
	BOOST_TEST(ss2() == state);

	delete[] states;
}



BOOST_AUTO_TEST_CASE(Operator_Comparison)
{
	auto* states_1 = new unsigned int[2];
	auto* states_2 = new unsigned int[3];
	auto* states_3 = new unsigned int[3];

	states_1[0] = 1U;
	states_1[1] = 2U;

	states_2[0] = 1U;
	states_2[1] = 2U;
	states_2[2] = 3U;

	states_3[0] = 1U;
	states_3[1] = 2U;
	states_3[2] = 4U;

	UIntStore ss1(2U, states_1), ss2(3U, states_2), ss3(3U, states_3);

	BOOST_TEST(ss1 < ss2);
	BOOST_TEST(ss1 < ss3);
	BOOST_TEST(ss2 < ss3);

	BOOST_TEST(ss2 > ss1);
	BOOST_TEST(ss3 > ss1);
	BOOST_TEST(ss3 > ss2);

	delete[] states_1;
	delete[] states_2;
	delete[] states_3;
}



BOOST_AUTO_TEST_CASE(Operator_OStream)
{
	auto* states = new unsigned int[3];

	states[0] = 1U;
	states[1] = 2U;
	states[2] = 3U;

	UIntStore ss1(1U), ss2(3U, states);

	std::string str1, str2;
	std::ostringstream stream;
	
	stream << ss1;
	BOOST_TEST(stream.str() == "[1,]");
	stream.str("");

	stream << ss2;
	BOOST_TEST(stream.str() == "[1,2,3,]");
	stream.str("");

	delete[] states;
}



BOOST_AUTO_TEST_CASE(Bits)
{
	// Line up a few test cases.

	auto* states = new unsigned int[5U];
	
	states[0] = 3U;			// 1 1 0 0 0	2 bits
	states[1] = 7U;			// 1 1 1 0 0	3 bits
	states[2] = 6U;			// 0 1 1 0 0	2 bits
	states[3] = 9U;			// 1 0 0 1 0	2 bits
	states[4] = 25U;		// 1 0 0 1 1	3 bits

	BOOST_TEST(UIntStore(1U, states).Bits() == 2U);
	BOOST_TEST(UIntStore(2U, states).Bits() == 5U);
	BOOST_TEST(UIntStore(3U, states).Bits() == 7U);
	BOOST_TEST(UIntStore(4U, states).Bits() == 9U);
	BOOST_TEST(UIntStore(5U, states).Bits() == 12U);

	delete[] states;
}



BOOST_AUTO_TEST_CASE(Spread_False)
{
	auto* states = new unsigned int[5U];

	states[0] = 1U;			
	states[1] = 1U;
	states[2] = 1U;
	states[3] = 1U;
	states[4] = 1U;

	UIntStore store(5U, states);

	BOOST_TEST(store.Spread(2U, 5U, 17U) == false);
	BOOST_TEST(store.Spread(5U, 5U, 17U) == false);

	delete[] states;
}



BOOST_AUTO_TEST_CASE(Spread_True_All_Positive)
{
	auto* states = new unsigned int[5U];

	states[0] = 1U;
	states[1] = 1U;
	states[2] = 1U;
	states[3] = 1U;
	states[4] = 1U;

	UIntStore store(5U, states);

	BOOST_TEST(store.Spread(2U, 5U, 14U) == true);
	BOOST_TEST(store[2U] == 5U);
	BOOST_TEST(store[3U] == 5U);
	BOOST_TEST(store[4U] == 4U);

	delete[] states;
}



BOOST_AUTO_TEST_CASE(Spread_True_Some_Positive)
{
	auto* states = new unsigned int[5U];

	states[0] = 1U;
	states[1] = 1U;
	states[2] = 1U;
	states[3] = 1U;
	states[4] = 1U;

	UIntStore store(5U, states);

	BOOST_TEST(store.Spread(2U, 8U, 14U) == true);
	BOOST_TEST(store[2U] == 8U);
	BOOST_TEST(store[3U] == 6U);
	BOOST_TEST(store[4U] == 0U);

	delete[] states;
}



BOOST_AUTO_TEST_SUITE_END()



#endif
