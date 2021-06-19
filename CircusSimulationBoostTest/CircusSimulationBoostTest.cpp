#define BOOST_TEST_MODULE CircusSimulationBoostTest

#include <boost/test/included/unit_test.hpp>
#include <boost/test/data/test_case.hpp>
#include <boost/test/data/monomorphic.hpp>

#include <sstream>
#include <vector>

#include "Enum.h"
#include "Helpers.h"
#include "Struct.h"
#include "SiteswapGraph.h"
#include "UIntStore.h"
#include "DisplayPattern.h"
#include "ChooseGenerator.h"
#include "SiteswapGraphMultiAction.h"
#include "SiteswapGraphMultiActionHelpers.h"

#include "Data.h"
#include "DataConverters.h"

#include "ChooseGeneratorTest.hpp"
#include "DisplayPatternTest.hpp"
#include "SiteswapGraphMultiActionHelpersTest.hpp"
#include "SiteswapGraphMultiActionTest.hpp"
#include "SiteswapGraphTest_SingleAction.hpp"
#include "SiteswapGraphTest_MultiAction.hpp"
#include "UIntStoreTest.hpp"
