#include "SiteswapGraphMultiActionHelpers.h"
#include "Settings.h"



unsigned int GetLowestIntegerWithNBits(const unsigned int& n);



void SiteswapGraphMultiActionHelpers::StoreValidSpreadsOfBitsAcrossActions(
	std::vector<UIntStore>& result,
	const unsigned int& numberActions,
	const unsigned int& maxThrow,
	const unsigned int& numberBits)
{
	result.clear();

	if (numberActions > 0U)
	{
		unsigned int* store_states = new unsigned int[numberActions];
		for (unsigned int i = 0U; i < numberActions; i++)
		{
			store_states[i] = 0U;
		}

		UIntStore store(numberActions, store_states);

		if (store.Spread(0U, maxThrow, numberBits))
		{
			result.push_back(store);

			if (numberActions > 1U)
			{
				unsigned int index = numberActions - 2U;
				unsigned int remaining = store[numberActions - 1U] + store[numberActions - 2U];
				bool next = true;

				while (next)
				{
					if (store[index] >= 2U && store.Spread(index, store[index] - 1U, remaining))
					{
						result.push_back(store);
						index = numberActions - 2U;
						remaining = store[numberActions - 1U] + store[numberActions - 2U];
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



unsigned int GetLowestIntegerWithNBits(const unsigned int& n)
{
	return (1U << n) - 1U;
}



void SiteswapGraphMultiActionHelpers::StoreValidBeginStates(
	std::vector<UIntStore>& result,
	const UIntStore& numberBits,
	unsigned int maxThrow)
{
	unsigned int size = numberBits.Size();

	if (maxThrow > Settings::ThrowHeight_Maximum())
	{
		maxThrow = Settings::ThrowHeight_Maximum();
	}

	if (size && numberBits.IsValidBitSpread(maxThrow))
	{
		unsigned int* data = new unsigned int[size];

		for (unsigned int i = 0U; i < size; i++)
		{
			data[i] = GetLowestIntegerWithNBits(numberBits[i]);
		}

		UIntStore store(size, data);

		result.push_back(store);

		unsigned int index = size - 1U;

		bool next = true;

		while (next)
		{
			if (index == 0U)
			{
				if (store.BitNext(index, maxThrow))
				{
					// Reset all and store.

					for (unsigned int i = index + 1U; i < size; i++)
					{
						store.Update(i, GetLowestIntegerWithNBits(numberBits[i]));
					}

					result.push_back(store);
					index = size - 1U;
				}
				else
				{
					next = false;
				}

			}
			else if (numberBits[index - 1U] > numberBits[index])
			{
				if (store.BitNext(index, maxThrow))
				{
					// Reset all and store.

					for (unsigned int i = index + 1U; i < size; i++)
					{
						store.Update(i, GetLowestIntegerWithNBits(numberBits[i]));
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
				if (store[index - 1U] > store[index] && store.BitNext(index, maxThrow))
				{
					// Reset all and store.

					for (unsigned int i = index + 1U; i < size; i++)
					{
						store.Update(i, GetLowestIntegerWithNBits(numberBits[i]));
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


