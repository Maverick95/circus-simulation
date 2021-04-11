#ifndef CHOOSE_GENERATOR_TEST_H
#define CHOOSE_GENERATOR_TEST_H



#include "ChooseGenerator.h"



BOOST_AUTO_TEST_SUITE(ChooseGeneratorTest)



BOOST_AUTO_TEST_CASE(ChooseGenerator_Data)
{
	ChooseGenerator gen(5U, 9U);

	BOOST_TEST(gen.Data()[0] == 0U);
	BOOST_TEST(gen.Data()[1] == 1U);
	BOOST_TEST(gen.Data()[2] == 2U);
	BOOST_TEST(gen.Data()[3] == 3U);
	BOOST_TEST(gen.Data()[4] == 4U);
}



BOOST_AUTO_TEST_CASE(ChooseGenerator_Next_Reset)
{
	/*
	Next() should return true 9 times (10 combinations).
	The complete combinations list is
	0 1 2
	0 1 3
	0 1 4
	0 2 3
	0 2 4
	0 3 4
	1 2 3
	1 2 4
	1 3 4
	2 3 4
	*/

	ChooseGenerator gen(3U, 5U);

	BOOST_TEST(gen.Data()[0] == 0U);
	BOOST_TEST(gen.Data()[1] == 1U);
	BOOST_TEST(gen.Data()[2] == 2U);

	// 0

	BOOST_TEST(gen.Next() == true);
	BOOST_TEST(gen.Data()[0] == 0U);
	BOOST_TEST(gen.Data()[1] == 1U);
	BOOST_TEST(gen.Data()[2] == 3U);

	BOOST_TEST(gen.Next() == true);
	BOOST_TEST(gen.Data()[0] == 0U);
	BOOST_TEST(gen.Data()[1] == 1U);
	BOOST_TEST(gen.Data()[2] == 4U);

	BOOST_TEST(gen.Next() == true);
	BOOST_TEST(gen.Data()[0] == 0U);
	BOOST_TEST(gen.Data()[1] == 2U);
	BOOST_TEST(gen.Data()[2] == 3U);

	// 3

	BOOST_TEST(gen.Next() == true);
	BOOST_TEST(gen.Data()[0] == 0U);
	BOOST_TEST(gen.Data()[1] == 2U);
	BOOST_TEST(gen.Data()[2] == 4U);

	BOOST_TEST(gen.Next() == true);
	BOOST_TEST(gen.Data()[0] == 0U);
	BOOST_TEST(gen.Data()[1] == 3U);
	BOOST_TEST(gen.Data()[2] == 4U);

	BOOST_TEST(gen.Next() == true);
	BOOST_TEST(gen.Data()[0] == 1U);
	BOOST_TEST(gen.Data()[1] == 2U);
	BOOST_TEST(gen.Data()[2] == 3U);

	// 6

	BOOST_TEST(gen.Next() == true);
	BOOST_TEST(gen.Data()[0] == 1U);
	BOOST_TEST(gen.Data()[1] == 2U);
	BOOST_TEST(gen.Data()[2] == 4U);

	BOOST_TEST(gen.Next() == true);
	BOOST_TEST(gen.Data()[0] == 1U);
	BOOST_TEST(gen.Data()[1] == 3U);
	BOOST_TEST(gen.Data()[2] == 4U);

	BOOST_TEST(gen.Next() == true);
	BOOST_TEST(gen.Data()[0] == 2U);
	BOOST_TEST(gen.Data()[1] == 3U);
	BOOST_TEST(gen.Data()[2] == 4U);

	// End

	BOOST_TEST(gen.Next() == false);
	BOOST_TEST(gen.Data()[0] == 2U);
	BOOST_TEST(gen.Data()[1] == 3U);
	BOOST_TEST(gen.Data()[2] == 4U);

	gen.Reset();

	BOOST_TEST(gen.Data()[0] == 0U);
	BOOST_TEST(gen.Data()[1] == 1U);
	BOOST_TEST(gen.Data()[2] == 2U);
}




BOOST_AUTO_TEST_SUITE_END()



#endif
