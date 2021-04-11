#include "ChooseGenerator.h"

ChooseGenerator::ChooseGenerator(const unsigned int& s, const unsigned int& m) :
	size(s == 0U ? 1U : s),
	max(m < size ? size : m),
	data(new unsigned int[size])
{
	for (unsigned int i = 0U; i < size; i++)
	{
		data[i] = i;
	}
}

ChooseGenerator::~ChooseGenerator()
{
	delete[] data;
}

bool ChooseGenerator::Next()
{
	for (auto i = 1U; i <= size; i++)
	{
		if (data[size - i] < max - i)
		{
			data[size - i]++;

			for (auto j = 1U; j < i; j++)
			{
				data[size - i + j] = data[size - i] + j;
			}

			return true;
		}
	}

	return false;
}

void ChooseGenerator::Reset()
{
	for (unsigned int i = 0U; i < size; i++)
	{
		data[i] = i;
	}
}

unsigned int ChooseGenerator::Size() const
{
	return size;
}

unsigned int ChooseGenerator::MaxValue() const
{
	return max;
}

const unsigned int* ChooseGenerator::Data() const
{
	return data;
}