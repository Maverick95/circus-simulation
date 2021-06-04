#include "Settings.h"

// Here are your program settings.

double GetProportionRatio(const double & r)
{
	return
		r < 0.0 ? 0.0 :
		r > 1.0 ? 1.0 :
		r;
}

static const unsigned int SETTINGS_NUMBER_BALLS_MINIMUM = 3;
static const unsigned int SETTINGS_NUMBER_BALLS_MAXIMUM = 9;
static const unsigned int SETTINGS_NUMBER_THROWS_MAXIMUM = 10;
static const unsigned int SETTINGS_THROW_HEIGHT_MAXIMUM = 15;

static const wxSize SETTINGS_WINDOW_SIZE_INITIAL(400, 400);

static const unsigned int SETTINGS_SCREEN_UPDATES_PER_SECOND = 100;

static const double SETTINGS_DISPLAY_PATTERN_PADDING_TOP = 0.25;
static const double SETTINGS_DISPLAY_PATTERN_PADDING_LEFT = 0.25;
static const double SETTINGS_DISPLAY_PATTERN_PADDING_RIGHT = 0.25;
static const double SETTINGS_DISPLAY_PATTERN_PADDING_BOTTOM = 0.25;

static const double SETTINGS_DISPLAY_PATTERN_PADDING[4] =
{
	GetProportionRatio(SETTINGS_DISPLAY_PATTERN_PADDING_TOP),
	GetProportionRatio(SETTINGS_DISPLAY_PATTERN_PADDING_LEFT),
	GetProportionRatio(SETTINGS_DISPLAY_PATTERN_PADDING_RIGHT),
	GetProportionRatio(SETTINGS_DISPLAY_PATTERN_PADDING_BOTTOM)
};

static const long SETTINGS_PATTERN_BEAT_TIME_MILLISECONDS = 500L;

static const unsigned int SETTINGS_PATTERN_MAX_HEIGHT_PIXELS = 100;
static const unsigned int SETTINGS_PATTERN_MAX_WIDTH_PIXELS = 50;

static const SiteswapGraphShortestPathMethod SETTINGS_GRAPH_SP_METHOD = SiteswapGraphShortestPathMethod::METHOD_DERIVED;


// Function definitions.

unsigned int Settings::NumberBalls_Minimum()
{
	return SETTINGS_NUMBER_BALLS_MINIMUM == 0 ? 1 : SETTINGS_NUMBER_BALLS_MINIMUM;
}

unsigned int Settings::NumberBalls_Maximum()
{
	unsigned int s = Settings::NumberBalls_Minimum();
	return SETTINGS_NUMBER_BALLS_MAXIMUM < s ? s : SETTINGS_NUMBER_BALLS_MAXIMUM;
}

unsigned int Settings::NumberThrows_Maximum()
{
	return SETTINGS_NUMBER_THROWS_MAXIMUM == 0U ? 1U : SETTINGS_NUMBER_THROWS_MAXIMUM;
}

unsigned int Settings::ThrowHeight_Maximum()
{
	unsigned int s = Settings::NumberBalls_Maximum();
	return SETTINGS_THROW_HEIGHT_MAXIMUM < s ? s : SETTINGS_THROW_HEIGHT_MAXIMUM;
}

const wxSize& Settings::WindowSize_Initial()
{
	return SETTINGS_WINDOW_SIZE_INITIAL;
}

unsigned int Settings::ScreenUpdates_PerSecond()
{
	return
		SETTINGS_SCREEN_UPDATES_PER_SECOND == 0 ? 1 :
		SETTINGS_SCREEN_UPDATES_PER_SECOND > 1000 ? 1000 :
		SETTINGS_SCREEN_UPDATES_PER_SECOND;
}

unsigned int Settings::Milliseconds_PerScreenUpdate()
{
	return 1000 / Settings::ScreenUpdates_PerSecond();
}

const double * Settings::DisplayPattern_Padding()
{
	return SETTINGS_DISPLAY_PATTERN_PADDING;
}

long Settings::Pattern_BeatTime_Milliseconds()
{
	return SETTINGS_PATTERN_BEAT_TIME_MILLISECONDS == 0L ? 1L : SETTINGS_PATTERN_BEAT_TIME_MILLISECONDS;
}

unsigned int Settings::Pattern_MaxHeight_Pixels()
{
	return SETTINGS_PATTERN_MAX_HEIGHT_PIXELS == 0 ? 1 : SETTINGS_PATTERN_MAX_HEIGHT_PIXELS;
}

unsigned int Settings::Pattern_MaxWidth_Pixels()
{
	return SETTINGS_PATTERN_MAX_WIDTH_PIXELS == 0 ? 1 : SETTINGS_PATTERN_MAX_WIDTH_PIXELS;
}

SiteswapGraphShortestPathMethod Settings::SiteswapGraph_ShortestPathMethod()
{
	return SETTINGS_GRAPH_SP_METHOD;
}