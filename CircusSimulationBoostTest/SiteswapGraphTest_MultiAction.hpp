#ifndef SITESWAP_GRAPH_TEST_MULTI_ACTION_H
#define SITESWAP_GRAPH_TEST_MULTI_ACTION_H



BOOST_AUTO_TEST_SUITE(SiteswapGraphTest_MultiAction)



BOOST_AUTO_TEST_CASE(GetPatterns_Balls2_Actions2_Throws2_Max3)
{
	auto result = SiteswapGraph::GetPatterns(2U, 2U, 2U, 3U);

	BOOST_CHECK(result != NULL);
	BOOST_TEST(result->size() == 8U);

	// Exhaustively check through the data.

	auto i = result->begin();
	const SiteswapGraphConnection* j = NULL;

	/*

	The patterns should come out in this order, according to
	the less-than operator of SiteswapPattern.

	X - -		->		- - -		->		X - -
	X - -		->		X X -		->		X - -

	X - -		->		X - -		->		X - -
	X - -		->		- X -		->		X - -

	X - -		->		- X -		->		X - -
	X - -		->		X - -		->		X - -

	X - -		->		- X -		->		X - -
	X - -		->		- X -		->		X - -

	- X -		->		X - -		->		- X -
	X - -		->		- X -		->		X - -

	X X -		->		X - -		->		X X -
	- - -		->		X - -		->		- - -

	X X -		->		X - X		->		X X -
	- - -		->		- - -		->		- - -

	X - X		->		- X -		->		X - X
	- - -		->		X - -		->		- - -

	*/

	// Pattern 1

	BOOST_TEST(i->num_balls == 2U);
	BOOST_TEST(i->num_actions == 2U);
	BOOST_TEST(i->throws.size() == 2U);

	j = &(i->throws[0]);
	BOOST_TEST(j->state_begin[0] == 1U);
	BOOST_TEST(j->state_begin[1] == 1U);
	BOOST_TEST(j->state_end[0] == 0U);
	BOOST_TEST(j->state_end[1] == 3U);
	BOOST_TEST(j->state_transfer.size() == 2U);
	BOOST_TEST(j->state_transfer[0].index_state_source == 0U);
	BOOST_TEST(j->state_transfer[0].index_state_destination == 1U);
	BOOST_TEST(j->state_transfer[0].state_transfer_throw == 1U);
	BOOST_TEST(j->state_transfer[1].index_state_source == 1U);
	BOOST_TEST(j->state_transfer[1].index_state_destination == 1U);
	BOOST_TEST(j->state_transfer[1].state_transfer_throw == 2U);

	j = &(i->throws[1]);
	BOOST_TEST(j->state_begin[0] == 0U);
	BOOST_TEST(j->state_begin[1] == 3U);
	BOOST_TEST(j->state_end[0] == 1U);
	BOOST_TEST(j->state_end[1] == 1U);
	BOOST_TEST(j->state_transfer.size() == 1U);
	BOOST_TEST(j->state_transfer[0].index_state_source == 1U);
	BOOST_TEST(j->state_transfer[0].index_state_destination == 0U);
	BOOST_TEST(j->state_transfer[0].state_transfer_throw == 1U);

	i++;

	// Pattern 2

	BOOST_TEST(i->num_balls == 2U);
	BOOST_TEST(i->num_actions == 2U);
	BOOST_TEST(i->throws.size() == 2U);

	j = &(i->throws[0]);
	BOOST_TEST(j->state_begin[0] == 1U);
	BOOST_TEST(j->state_begin[1] == 1U);
	BOOST_TEST(j->state_end[0] == 1U);
	BOOST_TEST(j->state_end[1] == 2U);
	BOOST_TEST(j->state_transfer.size() == 2U);
	BOOST_TEST(j->state_transfer[0].index_state_source == 0U);
	BOOST_TEST(j->state_transfer[0].index_state_destination == 0U);
	BOOST_TEST(j->state_transfer[0].state_transfer_throw == 1U);
	BOOST_TEST(j->state_transfer[1].index_state_source == 1U);
	BOOST_TEST(j->state_transfer[1].index_state_destination == 1U);
	BOOST_TEST(j->state_transfer[1].state_transfer_throw == 2U);

	j = &(i->throws[1]);
	BOOST_TEST(j->state_begin[0] == 1U);
	BOOST_TEST(j->state_begin[1] == 2U);
	BOOST_TEST(j->state_end[0] == 1U);
	BOOST_TEST(j->state_end[1] == 1U);
	BOOST_TEST(j->state_transfer.size() == 1U);
	BOOST_TEST(j->state_transfer[0].index_state_source == 0U);
	BOOST_TEST(j->state_transfer[0].index_state_destination == 0U);
	BOOST_TEST(j->state_transfer[0].state_transfer_throw == 1U);

	i++;

	// Pattern 3

	BOOST_TEST(i->num_balls == 2U);
	BOOST_TEST(i->num_actions == 2U);
	BOOST_TEST(i->throws.size() == 2U);

	j = &(i->throws[0]);
	BOOST_TEST(j->state_begin[0] == 1U);
	BOOST_TEST(j->state_begin[1] == 1U);
	BOOST_TEST(j->state_end[0] == 2U);
	BOOST_TEST(j->state_end[1] == 1U);
	BOOST_TEST(j->state_transfer.size() == 2U);
	BOOST_TEST(j->state_transfer[0].index_state_source == 0U);
	BOOST_TEST(j->state_transfer[0].index_state_destination == 0U);
	BOOST_TEST(j->state_transfer[0].state_transfer_throw == 2U);
	BOOST_TEST(j->state_transfer[1].index_state_source == 1U);
	BOOST_TEST(j->state_transfer[1].index_state_destination == 1U);
	BOOST_TEST(j->state_transfer[1].state_transfer_throw == 1U);

	j = &(i->throws[1]);
	BOOST_TEST(j->state_begin[0] == 2U);
	BOOST_TEST(j->state_begin[1] == 1U);
	BOOST_TEST(j->state_end[0] == 1U);
	BOOST_TEST(j->state_end[1] == 1U);
	BOOST_TEST(j->state_transfer.size() == 1U);
	BOOST_TEST(j->state_transfer[0].index_state_source == 1U);
	BOOST_TEST(j->state_transfer[0].index_state_destination == 1U);
	BOOST_TEST(j->state_transfer[0].state_transfer_throw == 1U);

	i++;

	// Pattern 4

	BOOST_TEST(i->num_balls == 2U);
	BOOST_TEST(i->num_actions == 2U);
	BOOST_TEST(i->throws.size() == 2U);

	j = &(i->throws[0]);
	BOOST_TEST(j->state_begin[0] == 1U);
	BOOST_TEST(j->state_begin[1] == 1U);
	BOOST_TEST(j->state_end[0] == 2U);
	BOOST_TEST(j->state_end[1] == 2U);
	BOOST_TEST(j->state_transfer.size() == 2U);
	BOOST_TEST(j->state_transfer[0].index_state_source == 0U);
	BOOST_TEST(j->state_transfer[0].index_state_destination == 0U);
	BOOST_TEST(j->state_transfer[0].state_transfer_throw == 2U);
	BOOST_TEST(j->state_transfer[1].index_state_source == 1U);
	BOOST_TEST(j->state_transfer[1].index_state_destination == 1U);
	BOOST_TEST(j->state_transfer[1].state_transfer_throw == 2U);

	j = &(i->throws[1]);
	BOOST_TEST(j->state_begin[0] == 2U);
	BOOST_TEST(j->state_begin[1] == 2U);
	BOOST_TEST(j->state_end[0] == 1U);
	BOOST_TEST(j->state_end[1] == 1U);
	BOOST_TEST(j->state_transfer.size() == 0U);

	i++;

	// Pattern 5

	BOOST_TEST(i->num_balls == 2U);
	BOOST_TEST(i->num_actions == 2U);
	BOOST_TEST(i->throws.size() == 2U);

	j = &(i->throws[0]);
	BOOST_TEST(j->state_begin[0] == 2U);
	BOOST_TEST(j->state_begin[1] == 1U);
	BOOST_TEST(j->state_end[0] == 1U);
	BOOST_TEST(j->state_end[1] == 2U);
	BOOST_TEST(j->state_transfer.size() == 1U);
	BOOST_TEST(j->state_transfer[0].index_state_source == 1U);
	BOOST_TEST(j->state_transfer[0].index_state_destination == 1U);
	BOOST_TEST(j->state_transfer[0].state_transfer_throw == 2U);

	j = &(i->throws[1]);
	BOOST_TEST(j->state_begin[0] == 1U);
	BOOST_TEST(j->state_begin[1] == 2U);
	BOOST_TEST(j->state_end[0] == 2U);
	BOOST_TEST(j->state_end[1] == 1U);
	BOOST_TEST(j->state_transfer.size() == 1U);
	BOOST_TEST(j->state_transfer[0].index_state_source == 0U);
	BOOST_TEST(j->state_transfer[0].index_state_destination == 0U);
	BOOST_TEST(j->state_transfer[0].state_transfer_throw == 2U);

	i++;

	// Pattern 6

	BOOST_TEST(i->num_balls == 2U);
	BOOST_TEST(i->num_actions == 2U);
	BOOST_TEST(i->throws.size() == 2U);

	j = &(i->throws[0]);
	BOOST_TEST(j->state_begin[0] == 3U);
	BOOST_TEST(j->state_begin[1] == 0U);
	BOOST_TEST(j->state_end[0] == 1U);
	BOOST_TEST(j->state_end[1] == 1U);
	BOOST_TEST(j->state_transfer.size() == 1U);
	BOOST_TEST(j->state_transfer[0].index_state_source == 0U);
	BOOST_TEST(j->state_transfer[0].index_state_destination == 1U);
	BOOST_TEST(j->state_transfer[0].state_transfer_throw == 1U);

	j = &(i->throws[1]);
	BOOST_TEST(j->state_begin[0] == 1U);
	BOOST_TEST(j->state_begin[1] == 1U);
	BOOST_TEST(j->state_end[0] == 3U);
	BOOST_TEST(j->state_end[1] == 0U);
	BOOST_TEST(j->state_transfer.size() == 2U);
	BOOST_TEST(j->state_transfer[0].index_state_source == 0U);
	BOOST_TEST(j->state_transfer[0].index_state_destination == 0U);
	BOOST_TEST(j->state_transfer[0].state_transfer_throw == 1U);
	BOOST_TEST(j->state_transfer[1].index_state_source == 1U);
	BOOST_TEST(j->state_transfer[1].index_state_destination == 0U);
	BOOST_TEST(j->state_transfer[1].state_transfer_throw == 2U);

	i++;

	// Pattern 7

	BOOST_TEST(i->num_balls == 2U);
	BOOST_TEST(i->num_actions == 2U);
	BOOST_TEST(i->throws.size() == 2U);

	j = &(i->throws[0]);
	BOOST_TEST(j->state_begin[0] == 3U);
	BOOST_TEST(j->state_begin[1] == 0U);
	BOOST_TEST(j->state_end[0] == 5U);
	BOOST_TEST(j->state_end[1] == 0U);
	BOOST_TEST(j->state_transfer.size() == 1U);
	BOOST_TEST(j->state_transfer[0].index_state_source == 0U);
	BOOST_TEST(j->state_transfer[0].index_state_destination == 0U);
	BOOST_TEST(j->state_transfer[0].state_transfer_throw == 3U);

	j = &(i->throws[1]);
	BOOST_TEST(j->state_begin[0] == 5U);
	BOOST_TEST(j->state_begin[1] == 0U);
	BOOST_TEST(j->state_end[0] == 3U);
	BOOST_TEST(j->state_end[1] == 0U);
	BOOST_TEST(j->state_transfer.size() == 1U);
	BOOST_TEST(j->state_transfer[0].index_state_source == 0U);
	BOOST_TEST(j->state_transfer[0].index_state_destination == 0U);
	BOOST_TEST(j->state_transfer[0].state_transfer_throw == 1U);

	i++;

	// Pattern 8

	BOOST_TEST(i->num_balls == 2U);
	BOOST_TEST(i->num_actions == 2U);
	BOOST_TEST(i->throws.size() == 2U);

	j = &(i->throws[0]);
	BOOST_TEST(j->state_begin[0] == 5U);
	BOOST_TEST(j->state_begin[1] == 0U);
	BOOST_TEST(j->state_end[0] == 2U);
	BOOST_TEST(j->state_end[1] == 1U);
	BOOST_TEST(j->state_transfer.size() == 1U);
	BOOST_TEST(j->state_transfer[0].index_state_source == 0U);
	BOOST_TEST(j->state_transfer[0].index_state_destination == 1U);
	BOOST_TEST(j->state_transfer[0].state_transfer_throw == 1U);

	j = &(i->throws[1]);
	BOOST_TEST(j->state_begin[0] == 2U);
	BOOST_TEST(j->state_begin[1] == 1U);
	BOOST_TEST(j->state_end[0] == 5U);
	BOOST_TEST(j->state_end[1] == 0U);
	BOOST_TEST(j->state_transfer.size() == 1U);
	BOOST_TEST(j->state_transfer[0].index_state_source == 1U);
	BOOST_TEST(j->state_transfer[0].index_state_destination == 0U);
	BOOST_TEST(j->state_transfer[0].state_transfer_throw == 3U);

	i++;



	delete result;
}



BOOST_AUTO_TEST_SUITE_END()



#endif
