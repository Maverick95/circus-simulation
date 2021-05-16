#include "SiteswapGraphMultiAction.h"
#include "SiteswapGraphMultiActionHelpers.h"

#include "Settings.h"
#include "ChooseGenerator.h"



bool IsDestinationExtensionOfSource(const UIntStore& source, const UIntStore& destination);



void SiteswapGraphMultiAction::StoreValidBeginStates(
	std::vector<UIntStore>& result,
	const unsigned int& numberActions,
	const unsigned int& maxThrow,
	const unsigned int& numberBits)
{
	result.clear();

	std::vector<UIntStore> bitSpreads;
	SiteswapGraphMultiActionHelpers::StoreValidSpreadsOfBitsAcrossActions(bitSpreads, numberActions, maxThrow, numberBits);

	for (auto i = bitSpreads.begin(); i != bitSpreads.end(); i++)
	{
		SiteswapGraphMultiActionHelpers::StoreValidBeginStates(result, *i, maxThrow);
	}
}



void SiteswapGraphMultiAction::StoreNextStates(
	std::forward_list<SiteswapGraphConnection>& result,
	const UIntStore& current,
	const unsigned int& max)
{
	result.clear();

	UIntStore next(current);
	auto next_bits = next.Next();
	std::vector<UIntStoreEmptyBit> next_spaces;

	if (!next_bits.empty())
	{
		next.EmptyBits(next_spaces, max);

		if (next_spaces.size() >= next_bits.size())
		{
			ChooseGenerator choose(next_bits.size(), next_spaces.size());

			do
			{
				std::vector<UIntStoreTransferBit> transfer;

				for (unsigned int i = 0U; i < choose.Size(); i++)
				{
					auto& space = next_spaces[*(choose.Data() + i)];
					next.Populate(space);
					transfer.push_back(
						{
							next_bits[i],
							space.index_state,
							space.index_bit + 1U
						});
				}

				result.push_front(
					{
						UIntStore(current),
						UIntStore(next),
						transfer
					});

				for (unsigned int i = 0U; i < choose.Size(); i++)
				{
					auto& space = next_spaces[*(choose.Data() + i)];
					next.Empty(space);
				}

			} while (choose.Next());
		}
	}
	else
	{
		result.push_front(
			{
				UIntStore(current),
				UIntStore(next),
				std::vector<UIntStoreTransferBit>()
			});
	}
}



bool SiteswapGraphMultiAction::DoesPathExist(
	const UIntStore& stateBegin,
	const UIntStore& stateEnd,
	const unsigned int& maxSteps)
{
	if (stateBegin == stateEnd)
	{
		return true;
	}

	if (stateBegin.Bits() == stateEnd.Bits())
	{
		UIntStore state_start_copy = stateBegin;

		for (unsigned int i = 0U; i < maxSteps; i++)
		{
			state_start_copy.Next();

			if (IsDestinationExtensionOfSource(state_start_copy, stateEnd))
			{
				return true;
			}
		}

		return false;
	}

	return false;
}



bool IsDestinationExtensionOfSource(const UIntStore& source, const UIntStore& destination)
{
	if (source.Size() != destination.Size())
	{
		return false;
	}

	for (unsigned int i = 0U; i < source.Size(); i++)
	{
		if (source[i] & ~destination[i])
		{
			return false;
		}
	}

	return true;
}

