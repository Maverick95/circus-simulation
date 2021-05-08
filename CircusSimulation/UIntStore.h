#ifndef U_INT_STORE_H
#define U_INT_STORE_H

#include "stdafx.h"
#include <ostream>
#include <string>
#include <vector>

struct UIntStoreEmptyBit
{
	unsigned int index_state;
	unsigned int index_bit;
};

struct UIntStoreTransferBit
{
	unsigned int index_state_source;
	unsigned int index_state_destination;
	unsigned int state_transfer_throw;
};

class UIntStore
{

private:

	unsigned int states_size;
	unsigned int* states;
	unsigned int bits;
	unsigned int hash;

	void Rehash();

public:

	UIntStore(const unsigned int&, const unsigned int*);
	UIntStore(const unsigned int&);
	UIntStore(const UIntStore&);

	virtual ~UIntStore();

	bool Spread(const unsigned int&, const unsigned int&, unsigned int);

	unsigned int operator()() const;

	unsigned int Bits() const;
	unsigned int Hash() const;

	bool IsValidBitSpread(const unsigned int&) const;

	unsigned int Size() const;

	std::vector<unsigned int> Next();
	bool Previous(const unsigned int& max);

	bool BitNext(const unsigned int& index, unsigned int max);

	void Populate(const UIntStoreEmptyBit&);
	void Update(const unsigned int& index, const unsigned int& value);

	void Empty(const UIntStoreEmptyBit&);

	void EmptyBits(std::vector<UIntStoreEmptyBit>& result, const unsigned int& max) const;

	UIntStore& operator=(const UIntStore&);

	const unsigned int& operator[](const unsigned int&) const;

	friend bool operator==(const UIntStore&, const UIntStore&);
	friend bool operator!=(const UIntStore&, const UIntStore&);
	friend bool operator<(const UIntStore&, const UIntStore&);
	friend bool operator>(const UIntStore&, const UIntStore&);
	friend std::ostream& operator<<(std::ostream&, const UIntStore&);

};

typedef UIntStore SiteswapState;
typedef UIntStore SiteswapThrow;

bool operator==(const UIntStore&, const UIntStore&);
bool operator!=(const UIntStore&, const UIntStore&);
bool operator<(const UIntStore&, const UIntStore&);
bool operator>(const UIntStore&, const UIntStore&);
std::ostream& operator<<(std::ostream&, const UIntStore&);

bool operator==(const UIntStoreTransferBit&, const UIntStoreTransferBit&);
bool operator!=(const UIntStoreTransferBit&, const UIntStoreTransferBit&);
bool operator<(const UIntStoreTransferBit&, const UIntStoreTransferBit&);
bool operator>(const UIntStoreTransferBit&, const UIntStoreTransferBit&);
std::ostream& operator<<(std::ostream&, const UIntStoreTransferBit&);

class UIntStoreHash
{
public:
	unsigned int operator()(const UIntStore& input) const;
};

#endif
