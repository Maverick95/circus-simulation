#ifndef U_INT_STORE_H
#define U_INT_STORE_H

#include "stdafx.h"
#include <ostream>
#include <vector>

struct UIntStoreEmptyBit
{
	unsigned int index_state;
	unsigned int index_bit;
};

class UIntStore
{

private:

	unsigned int states_size;
	unsigned int* states;

public:

	UIntStore(const unsigned int&, const unsigned int*);
	UIntStore(const unsigned int&);
	UIntStore(const UIntStore&);

	virtual ~UIntStore();

	bool Spread(const unsigned int&, const unsigned int&, unsigned int);

	unsigned int operator()() const;

	unsigned int Bits() const;

	bool IsValidBitSpread(const unsigned int&) const;

	unsigned int Size() const;

	unsigned int Next();

	void Populate(const UIntStoreEmptyBit&);

	void Empty(const UIntStoreEmptyBit&);

	std::vector<UIntStoreEmptyBit> EmptyBits(const unsigned int&) const;

	UIntStore& operator=(const UIntStore&);

	unsigned int& operator[](const unsigned int&);

	const unsigned int& operator[](const unsigned int&) const;

	friend bool operator==(const UIntStore&, const UIntStore&);
	friend bool operator!=(const UIntStore&, const UIntStore&);
	friend bool operator<(const UIntStore&, const UIntStore&);
	friend bool operator>(const UIntStore&, const UIntStore&);
	friend std::ostream& operator<<(std::ostream&, const UIntStore&);
	
	/*
	friend UIntStore operator+(const UIntStore&, const UIntStore&);
	friend UIntStore& operator+=(UIntStore&, const UIntStore&);
	*/

};

typedef UIntStore SiteswapState;
typedef UIntStore SiteswapThrow;

bool operator==(const UIntStore&, const UIntStore&);
bool operator!=(const UIntStore&, const UIntStore&);
bool operator<(const UIntStore&, const UIntStore&);
bool operator>(const UIntStore&, const UIntStore&);
std::ostream& operator<<(std::ostream&, const UIntStore&);

/*
UIntStore operator+(const UIntStore&, const UIntStore&);
UIntStore& operator+=(UIntStore&, const UIntStore&);
*/

#endif
