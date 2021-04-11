#include "SiteswapGraphMultiActionFunctions.h"

#include "Settings.h"
#include "ChooseGenerator.h"


std::vector<UIntStore> SiteswapGraphMultiAction::BitSpread(const unsigned int& length, const unsigned int& max, const unsigned int& total)
{
	std::vector<UIntStore> result;

	if (length > 0U)
	{
		unsigned int* store_states = new unsigned int[length];
		for (unsigned int i = 0U; i < length; i++)
		{
			store_states[i] = 0U;
		}

		UIntStore store(length, store_states);

		if (store.Spread(0U, max, total))
		{
			result.push_back(store);

			if (length > 1U)
			{
				unsigned int index = length - 2U;
				unsigned int remaining = store[length - 1U] + store[length - 2U];
				bool next = true;

				while (next)
				{
					if (store[index] >= 2U && store.Spread(index, store[index] - 1U, remaining))
					{
						result.push_back(store);
						index = length - 2U;
						remaining = store[length - 1U] + store[length - 2U];
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

	return result;
}



unsigned int SiteswapGraphMultiAction::BitLowest(const unsigned int& bits)
{
	return (1U << bits) - 1U;
}



bool SiteswapGraphMultiAction::BitNext(unsigned int& current, unsigned int max)
{
	if (current > 0U && max > 1U)
	{
		if (max > Settings::ThrowHeight_Maximum())
		{
			max = Settings::ThrowHeight_Maximum();
		}

		unsigned int bits_found = 0U;

		for (unsigned int i = 0U; i < max - 1U; i++)
		{
			// Current digit needs to be 1, next up is 0.

			if ((current & (1U << i)))
			{
				if (!(current & (1U << (i + 1U))))
				{
					// Shift bit up by 1.

					current &= ~(1U << i);
					current |= (1U << (i + 1U));

					// Copy found bits down to end.

					current &= ~((1U << i) - 1U);
					current |= ((1U << bits_found) - 1U);

					return true;
				}
				else
				{
					bits_found++;
				}
			}
		}
	}

	return false;
}



std::vector<UIntStore> SiteswapGraphMultiAction::BitStates(const UIntStore& bitSpread, unsigned int max)
{
	auto result = std::vector<UIntStore>();

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
			data[i] = BitLowest(bitSpread[i]);
		}

		UIntStore store(size, data);

		result.push_back(store);

		unsigned int index = size - 1U;

		bool next = true;

		while (next)
		{
			if (index == 0U)
			{
				if (BitNext(store[index], max))
				{
					// Reset all and store.

					for (unsigned int i = index + 1U; i < size; i++)
					{
						store[i] = BitLowest(bitSpread[i]);
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
				if (BitNext(store[index], max))
				{
					// Reset all and store.

					for (unsigned int i = index + 1U; i < size; i++)
					{
						store[i] = BitLowest(bitSpread[i]);
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
				if (store[index - 1U] > store[index] && BitNext(store[index], max))
				{
					// Reset all and store.

					for (unsigned int i = index + 1U; i < size; i++)
					{
						store[i] = BitLowest(bitSpread[i]);
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

	return result;
}


std::vector<UIntStore> SiteswapGraphMultiAction::AllStates(const unsigned int& length, const unsigned int& max, const unsigned int& total)
{
	std::vector<UIntStore> result;

	auto bitSpreads = BitSpread(length, max, total);

	for (auto i = bitSpreads.begin(); i != bitSpreads.end(); i++)
	{
		auto bitStates = BitStates(*i, max);

		for (auto j = bitStates.begin(); j != bitStates.end(); j++)
		{
			result.push_back(*j);
		}
	}

	return result;
}



std::forward_list<SiteswapGraphConnection> SiteswapGraphMultiAction::NextStates(const UIntStore& current, const unsigned int& max)
{
	std::forward_list<SiteswapGraphConnection> result;

	UIntStore next(current);
	auto next_bits = next.Next();

	if (next_bits > 0U)
	{
		auto next_spaces = next.EmptyBits(max);

		if (next_spaces.size() >= next_bits)
		{
			ChooseGenerator choose(next_bits, next_spaces.size());

			do
			{
				for (unsigned int i = 0U; i < choose.Size(); i++)
				{
					auto& space = next_spaces[*(choose.Data() + i)];
					next.Populate(space);
				}

				result.push_front(
					{
						UIntStore(current),
						UIntStore(next),
						next_spaces[*(choose.Data())].index_bit + 1U		// Placeholder value to retain current functionality.
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
				0U		// Placeholder value to retain current functionality.
			});
	}

	return result;
}

