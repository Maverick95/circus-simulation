#include "CppUnitTest.h"
#include "CppUnitTestAssert.h"

#include <deque>
#include <forward_list>
#include <map>

#include "Struct.h"
#include "SiteswapGraph.h"


using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace CircusSimulationTests
{
	TEST_CLASS(SiteswapGraphTests)
	{

	public:
		
		TEST_METHOD(Patterns_3balls_5height_4length)
		{
			SiteswapGraph sg(3U, 5U);
			SiteswapPattern** sp = sg.GetPatterns(4U);
			Assert::IsNotNull(sp);

			// TODO - memory leak here.
		}
	};
}

