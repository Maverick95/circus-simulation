#include <cassert>

#include <functional>
#include <string>

#include "UIntStore.h"
#include "Functions.h"
#include "Settings.h"



static const std::hash<std::string> uintstore_hash;



void UIntStore::Rehash()
{
	std::string hash_str((const char*)states, sizeof(unsigned int) * states_size);
	hash = uintstore_hash(hash_str);
}


UIntStore::UIntStore(const unsigned int& s, const unsigned int* st) :
	states_size(s == 0U ? 1U : s),
	states(new unsigned int[states_size]),
	bits(0U),
	hash(0U)
{
	for (unsigned int i = 0U; i < states_size; i++)
	{
		states[i] = (st == NULL ? 0U : st[i]);
		bits += Functions::Bits(states[i]);
	}

	//Rehash();
}

UIntStore::UIntStore(const unsigned int& st) :
	states_size(1U),
	states(new unsigned int[1U]),
	bits(Functions::Bits(st)),
	hash(0U)
{
	states[0U] = st;
	//Rehash();
}

UIntStore::UIntStore(const UIntStore& us) :
	states_size(us.states_size),
	states(new unsigned int[states_size]),
	bits(us.bits),
	hash(us.hash)
{
	for (unsigned int i = 0U; i < states_size; i++)
	{
		states[i] = us.states[i];
	}
}

UIntStore::~UIntStore()
{
	delete[] states;
}

bool UIntStore::Spread(const unsigned int& s, const unsigned int& m, unsigned int t)
{
	if (s < states_size && (states_size - s) * m >= t)
	{
		for (unsigned int i = s; i < states_size; i++)
		{
			unsigned int v = t < m ? t : m;
			bits -= Functions::Bits(states[i]);
			states[i] = v;
			bits += Functions::Bits(v);
			t -= v;
		}

		//Rehash();
		return true;
	}

	return false;
}

unsigned int UIntStore::operator()() const
{
	return states[0U];
}

unsigned int UIntStore::Bits() const
{
	return bits;
}

unsigned int UIntStore::Hash() const
{
	std::string hash_str((const char*)states, sizeof(unsigned int) * states_size);
	return uintstore_hash(hash_str);
}

UIntStore& UIntStore::operator=(const UIntStore& us)
{
	if (states_size != us.states_size)
	{
		states_size = us.states_size;
		delete[] states;
		states = new unsigned int[us.states_size];
	}

	for (unsigned int i = 0U; i < states_size; i++)
	{
		states[i] = us.states[i];
	}

	bits = us.bits;
	hash = us.hash;

	return *this;
}

bool UIntStore::BitNext(const unsigned int& index, unsigned int max)
{
	if (index < states_size)
	{
		unsigned int& current = states[index];
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

						//Rehash();
						return true;
					}
					else
					{
						bits_found++;
					}
				}
			}
		}
	}

	return false;
}

const unsigned int& UIntStore::operator[](const unsigned int& i) const
{
	assert(i < states_size);
	return states[i];
}

bool UIntStore::IsValidBitSpread(const unsigned int& m) const
{
	if (m < states[0U])
	{
		return false;
	}

	for (unsigned int i = 1U; i < states_size; i++)
	{
		if (states[i] > states[i - 1U])
		{
			return false;
		}
	}

	return true;
}

unsigned int UIntStore::Size() const
{
	return states_size;
}

std::vector<unsigned int> UIntStore::Next()
{
	std::vector<unsigned int> result;

	for (unsigned int i = 0U; i < states_size; i++)
	{
		if ((states[i] & 1U) > 0)
		{
			result.push_back(i);
			bits--;
		}

		states[i] = states[i] >> 1U;
	}

	//Rehash();
	return result;
}

bool UIntStore::Previous(const unsigned int& max)
{
	if (max > 0U)
	{
		unsigned int states_upperBound = 1U << max;
		for (unsigned int i = 0U; i < states_size; i++)
		{
			if (states[i] >= states_upperBound)
			{
				return false;
			}
		}
		for (unsigned int i = 0U; i < states_size; i++)
		{
			states[i] <<= 1U;
		}

		return true;
	}

	return false;
}

void UIntStore::Populate(const UIntStoreEmptyBit& bit)
{
	if (bit.index_state < states_size)
	{
		unsigned int mask = (1U << bit.index_bit);

		if ((~states[bit.index_state]) & mask)
		{
			states[bit.index_state] |= mask;
			bits++;
			//Rehash();
		}
	}
}

void UIntStore::Update(const unsigned int& index, const unsigned int& value)
{
	if (index < states_size)
	{
		bits -= Functions::Bits(states[index]);
		states[index] = value;
		bits += Functions::Bits(value);
		//Rehash();
	}
}

void UIntStore::Empty(const UIntStoreEmptyBit& bit)
{
	if (bit.index_state < states_size)
	{
		unsigned int mask = (1U << bit.index_bit);

		if (states[bit.index_state] & mask)
		{
			states[bit.index_state] &= ~(mask);
			bits--;
			//Rehash();
		}
	}
}

void UIntStore::EmptyBits(std::vector<UIntStoreEmptyBit>& result, const unsigned int& max) const
{
	result.clear();

	for (auto i = 0U; i < states_size; i++)
	{
		for (auto j = 0U; j < max && (1U << j) > 0U; j++)
		{
			if ((~states[i] & (1U << j)) > 0U)
			{
				result.push_back({ i, j });
			}
		}
	}
}

bool operator==(const UIntStore& us1, const UIntStore& us2)
{
	if (us1.states_size != us2.states_size)
	{
		return false;
	}

	for (unsigned int i = 0U; i < us1.states_size; i++)
	{
		if (us1.states[i] != us2.states[i])
		{
			return false;
		}
	}

	return true;
}

bool operator!=(const UIntStore& us1, const UIntStore& us2)
{
	return !(us1 == us2);
}

bool operator<(const UIntStore& us1, const UIntStore& us2)
{
	if (us1.states_size < us2.states_size)
	{
		return true;
	}
	else if (us1.states_size == us2.states_size)
	{
		for (unsigned int i = 0U; i < us1.states_size; i++)
		{
			if (us1.states[i] < us2.states[i])
			{
				return true;
			}
			else if (us1.states[i] > us2.states[i])
			{
				return false;
			}
		}
	}

	return false;
}

bool operator>(const UIntStore& us1, const UIntStore& us2)
{
	if (us1.states_size > us2.states_size)
	{
		return true;
	}
	else if (us1.states_size == us2.states_size)
	{
		for (unsigned int i = 0U; i < us1.states_size; i++)
		{
			if (us1.states[i] > us2.states[i])
			{
				return true;
			}
			else if (us1.states[i] < us2.states[i])
			{
				return false;
			}
		}
	}

	return false;
}

std::ostream& operator<<(std::ostream& os, const UIntStore& us)
{
	os << "[";
	for (unsigned int i = 0U; i < us.states_size; i++)
	{
		os << us.states[i] << ",";
	}

	os << "]";
	return os;
}

bool operator==(const UIntStoreTransferBit& tb1, const UIntStoreTransferBit& tb2)
{
	return
		tb1.index_state_source == tb2.index_state_source &&
		tb1.index_state_destination == tb2.index_state_destination &&
		tb1.state_transfer_throw == tb2.state_transfer_throw;
}

bool operator!=(const UIntStoreTransferBit& tb1, const UIntStoreTransferBit& tb2)
{
	return !(tb1 == tb2);
}

bool operator<(const UIntStoreTransferBit& tb1, const UIntStoreTransferBit& tb2)
{
	return
		tb1.index_state_source < tb2.index_state_source ||
		tb1.index_state_destination < tb2.index_state_destination ||
		tb1.state_transfer_throw < tb2.state_transfer_throw;
}

bool operator>(const UIntStoreTransferBit& tb1, const UIntStoreTransferBit& tb2)
{
	return
		tb1.index_state_source > tb2.index_state_source ||
		tb1.index_state_destination > tb2.index_state_destination ||
		tb1.state_transfer_throw > tb2.state_transfer_throw;
}

std::ostream& operator<<(std::ostream& os, const UIntStoreTransferBit& tb)
{
	os << "[" << tb.index_state_source << "," << tb.index_state_destination << "," << tb.state_transfer_throw << "]";
	return os;
}



unsigned int UIntStoreHash::operator()(const UIntStore& input) const
{
	return input.Hash();
};