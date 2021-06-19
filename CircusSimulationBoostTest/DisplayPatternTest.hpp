#ifndef DISPLAY_PATTERN_TEST_H
#define DISPLAY_PATTERN_TEST_H

unsigned int

    // 3 balls, 1 actions, 3 throws, [5] [3] [1]
    
    // 3 balls, 2 actions, 2 throws, [4 2] [2x 4x]

    data1[] = { 3,	1,	3,	7,	19,	1,	0,	0,	5,	19,	13,	1,	0,	0,	3,	13,	7,	1,	0,	0,	1 },

    data2[] = { 3,	2,	2,	3,	1,	3,	1,	2,	0,	0,	2,	1,	1,	1,	3,	1,	3,	1,	2,	0,	1,	1,	1,	0,	2 };

unsigned int* dataset[] = { data1, data2 };

BOOST_DATA_TEST_CASE(DisplayPattern_Constructor_Success, boost::unit_test::data::make(dataset), data)
{
    SiteswapPattern pattern_data = GenerateDataset(data);
    DisplayPattern pattern_processed(pattern_data);

    BOOST_TEST(pattern_processed.GetTotalLength() > 0U);
}

#endif
