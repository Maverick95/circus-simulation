#include "CppUnitTest.h"
#include "CppUnitTestAssert.h"

#include <deque>
#include <forward_list>
#include <map>
#include <set>

#include "Struct.h"
#include "SiteswapGraph.h"


using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace CircusSimulationTests
{
	TEST_CLASS(SiteswapGraphTests)
	{

	public:
		
		/*
		* Test cases - 8 bits
		* 
		* XXX-----		to		X-XX----		7		to		13		= 2
		* X-XXX--X		to		-X-XX-XX		157		to		218		= 6
		* X------X		to		--X---X-		129		to		68		= 1
		* -X-XX-X-		to		XXXX----		90		to		15		= 3
		*/

		TEST_METHOD(DeriveShortestPath_8bit)
		{
			Assert::AreEqual(2U, SiteswapGraph::DeriveShortestPath(7U, 13U));
			Assert::AreEqual(6U, SiteswapGraph::DeriveShortestPath(157U, 218U));
			Assert::AreEqual(1U, SiteswapGraph::DeriveShortestPath(129U, 68U));
			Assert::AreEqual(3U, SiteswapGraph::DeriveShortestPath(90U, 15U));
		}

		/*
		* Test cases
		* Siteswap graph with Balls = 3, Height = 5, Throws = 2
		* Should return 42 and 51 in that order
		*/

		TEST_METHOD(GetPatterns_Balls3_Height5_Throws2)
		{
			SiteswapGraph sg(3U, 5U);
			auto* paths = sg.GetPatterns(2U);

			Assert::IsNotNull(paths);
			Assert::AreEqual(2U, paths->size(), L"Incorrect number of paths");

			unsigned int index = 0U;
			unsigned int results[2U][2U] = { {4U, 2U}, {5U, 1U} };

			for (auto i = paths->begin(); i != paths->end(); i++)
			{
				Assert::AreEqual(3U, i->num_balls);

				for (unsigned int j = 0U; j < 2U; j++)
				{
					Assert::AreEqual(results[index][j], i->throws[j].state_transfer_throw);
				}
				index++;
			}

			delete paths;
		}

		/* Further tests involve understanding how the patterns are returned, e.g. for 3 balls, 531, 315, 153, which one comes back? */

	};
}

