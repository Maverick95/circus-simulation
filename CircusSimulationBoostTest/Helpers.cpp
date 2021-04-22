#include "Helpers.h"



std::vector<UIntStoreTransferBit> GenerateTransfer(
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
		state_transfer_throw > 0U ? GenerateTransfer(0U, 0U, state_transfer_throw) : GenerateEmptyTransfer()
	};
}




std::vector<UIntStoreTransferBit> GenerateTransfer(
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