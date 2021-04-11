#ifndef CHOOSE_GENERATOR_H
#define CHOOSE_GENERATOR_H

class ChooseGenerator
{

private:

	unsigned int size;
	unsigned int max;
	unsigned int* data;

public:

	ChooseGenerator(const unsigned int&, const unsigned int&);
	virtual ~ChooseGenerator();

	bool Next();
	void Reset();

	unsigned int Size() const;
	unsigned int MaxValue() const;
	const unsigned int* Data() const;

};

#endif
