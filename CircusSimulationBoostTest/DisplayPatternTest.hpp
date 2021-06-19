#ifndef DISPLAY_PATTERN_TEST_H
#define DISPLAY_PATTERN_TEST_H



BOOST_DATA_TEST_CASE(DisplayPattern_Constructor_Success,
    boost::unit_test::data::make(
        Data::Data_DisplayPatternTest_DisplayPattern_Constructor_Success()
    ), data)
{
    SiteswapPattern pattern_data = DataConverters::Convert_DisplayPatternTest_DisplayPattern_Constructor_Success(data);
    DisplayPattern pattern_processed(pattern_data);

    BOOST_TEST(pattern_processed.GetTotalLength() > 0U);
}

#endif
