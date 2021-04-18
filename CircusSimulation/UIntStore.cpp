#include <cassert>

#include "UIntStore.h"
#include "Functions.h"



UIntStore::UIntStore(const unsigned int& s, const unsigned int* st) :
	states_size(s == 0U ? 1U : s),
	states(new unsigned int[states_size]),
	bits(0U)
{
	for (unsigned int i = 0U; i < states_size; i++)
	{
		states[i] = (st == NULL ? 0U : st[i]);
		bits += Functions::Bits(states[i]);
	}
}

UIntStore::UIntStore(const unsigned int& st) :
	states_size(1U),
	states(new unsigned int[1U]),
	bits(Functions::Bits(st))
{
	states[0U] = st;
}

UIntStore::UIntStore(const UIntStore& us) :
	states_size(us.states_size),
	states(new unsigned int[states_size]),
	bits(us.bits)
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
	/*
	unsigned int result = 0U;

	for (unsigned int i = 0U; i < states_size; i++)
	{
		result += Functions::Bits(states[i]);
	}

	return result;
	*/

	return bits;
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

	return *this;
}

unsigned int& UIntStore::operator[](const unsigned int& i)
{
	assert(i < states_size);
	return states[i];
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

unsigned int UIntStore::Next()
{
	unsigned int result = 0U;

	for (unsigned int i = 0U; i < states_size; i++)
	{
		if ((states[i] & 1U) > 0)
		{
			result++;
			bits--;
		}

		states[i] = states[i] >> 1U;
	}

	return result;
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
		}
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
		}
	}
}

std::vector<UIntStoreEmptyBit> UIntStore::EmptyBits(const unsigned int& max) const
{
	std::vector<UIntStoreEmptyBit> result;

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

	return result;
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

