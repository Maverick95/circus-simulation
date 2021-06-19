#include "Helpers.h"



std::vector<UIntStoreTransferBit> GenerateSingleTransfer(
	const unsigned int& index_state_source,
	const unsigned int& index_state_destination,
	const unsigned int& state_transfer_throw);

std::vector<UIntStoreTransferBit> GenerateEmptyTransfer();



SiteswapGraphConnection GenerateSingleActionConnection(
	const unsigned int& state_source,
	const unsigned int& state_destination,
	const unsigned int& state_transfer_throw)
{
	return
	{
		SiteswapState(state_source),
		SiteswapState(state_destination),
		state_transfer_throw > 0U ? GenerateSingleTransfer(0U, 0U, state_transfer_throw) : GenerateEmptyTransfer()
	};
}




std::vector<UIntStoreTransferBit> GenerateSingleTransfer(
	const unsigned int& index_state_source,
	const unsigned int& index_state_destination,
	const unsigned int& state_transfer_throw)
{
	std::vector<UIntStoreTransferBit> result;
	result.push_back({ index_state_source, index_state_destination, state_transfer_throw });
	return result;
}

std::vector<UIntStoreTransferBit> GenerateEmptyTransfer()
{
	return std::vector<UIntStoreTransferBit>();
}

SiteswapPattern GenerateDataset(const unsigned int* data)
{
	/*
	
	[0]		balls
	[1]		actions
	[2]		throws

	[3]						-		[3 + (actions - 1)]										state_begin of first throw
	[3 + actions]			-		[3 + (2 * actions) - 1]									state_end of first throw
	[3 + (2 * actions)]																		number of state_transfer elements (num_state_transfer)
	[3 + (2 * actions) + 1]	-		[3 + (2 * actions) + (3 * num_state_transfer)]			state_transfer details

	and then next throw
	
	*/

	std::deque<SiteswapGraphConnection> connections;

	const unsigned int balls = data[0], actions = data[1], throws = data[2];
	int index = 3;

	for (unsigned int i = 0U; i < throws; i++)
	{
		SiteswapState state_begin(actions, &(data[index]));
		index += actions;
		SiteswapState state_end(actions, &(data[index]));
		index += actions;
		unsigned int state_transfer_size = data[index];
		index++;

		std::vector<UIntStoreTransferBit> state_transfer;
		for (unsigned int j = 0U; j < state_transfer_size; j++)
		{
			state_transfer.push_back(
				{
					data[index],
					data[index + 1],
					data[index + 2]
				});

			index += 3;
		}

		connections.push_back(
			{
				state_begin,
				state_end,
				state_transfer
			});
	}

	return { balls, actions, connections };
}