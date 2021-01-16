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
		
		/*
		* Test cases -
		* XXX-----		to		X-XX----		7		to		13		= 2
		* X-XXX--X		to		-X-XX-XX		157		to		218		= 6
		* X------X		to		--X---X-		129		to		68		= 1
		*/

		TEST_METHOD(DeriveShortestPath)
		{
			Assert::AreEqual(2U, SiteswapGraph::DeriveShortestPath(7U, 13U));
			Assert::AreEqual(6U, SiteswapGraph::DeriveShortestPath(157U, 218U));
			Assert::AreEqual(1U, SiteswapGraph::DeriveShortestPath(129U, 68U));
		}
	};
}

