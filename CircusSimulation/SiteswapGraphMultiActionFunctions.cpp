#include "SiteswapGraphMultiActionFunctions.h"

#include "Settings.h"
#include "ChooseGenerator.h"


void SiteswapGraphMultiAction::StoreValidSpreadsOfBitsAcrossActions(
	std::vector<UIntStore>& result,
	const unsigned int& numberIntegers,
	const unsigned int& maxInteger,
	const unsigned int& sumIntegers)
{
	result.clear();
	
	if (numberIntegers > 0U)
	{
		unsigned int* store_states = new unsigned int[numberIntegers];
		for (unsigned int i = 0U; i < numberIntegers; i++)
		{
			store_states[i] = 0U;
		}

		UIntStore store(numberIntegers, store_states);

		if (store.Spread(0U, maxInteger, sumIntegers))
		{
			result.push_back(store);

			if (numberIntegers > 1U)
			{
				unsigned int index = numberIntegers - 2U;
				unsigned int remaining = store[numberIntegers - 1U] + store[numberIntegers - 2U];
				bool next = true;

				while (next)
				{
					if (store[index] >= 2U && store.Spread(index, store[index] - 1U, remaining))
					{
						result.push_back(store);
						index = numberIntegers - 2U;
						remaining = store[numberIntegers - 1U] + store[numberIntegers - 2U];
					}
					else if (index > 0U)
					{
						remaining += store[--index];
					}
					else
					{
						next = false;
					}
				}
			}
		}

		delete[] store_states;
	}
}



unsigned int SiteswapGraphMultiAction::GetLowestIntegerWithNBits(const unsigned int& n)
{
	return (1U << n) - 1U;
}



void SiteswapGraphMultiAction::BitStates(
	std::vector<UIntStore>& result,
	const UIntStore& bitSpread,
	unsigned int max)
{
	//result.clear();
	
	unsigned int size = bitSpread.Size();

	if (max > Settings::ThrowHeight_Maximum())
	{
		max = Settings::ThrowHeight_Maximum();
	}

	if (size && bitSpread.IsValidBitSpread(max))
	{
		unsigned int* data = new unsigned int[size];

		for (unsigned int i = 0U; i < size; i++)
		{
			data[i] = GetLowestIntegerWithNBits(bitSpread[i]);
		}

		UIntStore store(size, data);

		result.push_back(store);

		unsigned int index = size - 1U;

		bool next = true;

		while (next)
		{
			if (index == 0U)
			{
				if (store.BitNext(index, max))
				{
					// Reset all and store.

					for (unsigned int i = index + 1U; i < size; i++)
					{
						store.Update(i, GetLowestIntegerWithNBits(bitSpread[i]));
					}

					result.push_back(store);
					index = size - 1U;
				}
				else
				{
					next = false;
				}

			}
			else if (bitSpread[index - 1U] > bitSpread[index])
			{
				if (store.BitNext(index, max))
				{
					// Reset all and store.

					for (unsigned int i = index + 1U; i < size; i++)
					{
						store.Update(i, GetLowestIntegerWithNBits(bitSpread[i]));
					}

					result.push_back(store);
					index = size - 1U;
				}
				else
				{
					index--;
				}
			}
			else
			{
				if (store[index - 1U] > store[index] && store.BitNext(index, max))
				{
					// Reset all and store.

					for (unsigned int i = index + 1U; i < size; i++)
					{
						store.Update(i, GetLowestIntegerWithNBits(bitSpread[i]));
					}

					result.push_back(store);
					index = size - 1U;
				}
				else
				{
					index--;
				}
			}
		}

		delete[] data;
	}
}

void SiteswapGraphMultiAction::PopulateValidBeginStates(
	std::vector<UIntStore>& result,
	const unsigned int& length,
	const unsigned int& max,
	const unsigned int& total)
{
	result.clear();

	std::vector<UIntStore> bitSpreads;
	StoreValidSpreadsOfBitsAcrossActions(bitSpreads, length, max, total);

	for (auto i = bitSpreads.begin(); i != bitSpreads.end(); i++)
	{
		BitStates(result, *i, max);
	}
}



void SiteswapGraphMultiAction::PopulateNextStates(
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

