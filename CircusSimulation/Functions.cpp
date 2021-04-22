#include <map>

#include "Functions.h"


std::map<unsigned int, unsigned int>* PrimeFactorise(unsigned int n);

void PrimeFactorise_Multiply(std::map<unsigned int, unsigned int>* p1, std::map<unsigned int, unsigned int>* p2);

void PrimeFactorise_Divide(std::map<unsigned int, unsigned int>* p1, std::map<unsigned int, unsigned int>* p2);



unsigned int Functions::Choose(const unsigned int& n, unsigned int k)
{
	// Choose values are reflective, choose the smallest value if necessary.

	if (k > (n >> 1))
	{
		k = n - k;
	}

	// Deal with the easy option.

	if (k == 1)
	{
		return n;
	}

	// Otherwise head into prime factorisation.

	std::map<unsigned int, unsigned int> p_numerator, p_denominator;

	for (unsigned int i = 0; i < k - 1; i++)
	{
		std::map<unsigned int, unsigned int>* p_loop_numerator = PrimeFactorise(n - i),
			* p_loop_denominator = PrimeFactorise(k - i);

		PrimeFactorise_Multiply(&p_numerator, p_loop_numerator);
		PrimeFactorise_Multiply(&p_denominator, p_loop_denominator);

		delete p_loop_numerator;
		delete p_loop_denominator;
	}

	// Insert the final denominator multiplication.

	std::map<unsigned int, unsigned int>* p_final_numerator = PrimeFactorise(n - k + 1);
	PrimeFactorise_Multiply(&p_numerator, p_final_numerator);
	delete p_final_numerator;

	// Run the division.

	PrimeFactorise_Divide(&p_numerator, &p_denominator);

	// Compute the final result.

	unsigned int choose_return = 1;

	for (auto i = p_numerator.begin(); i != p_numerator.end(); i++)
	{
		for (unsigned int j = 0; j < i->second; j++)
		{
			choose_return *= i->first;
		}
	}

	return choose_return;
}



unsigned int Functions::LowestCommonMultiple(const std::vector<unsigned int>& s)
{
	if (!s.empty())
	{
		auto* data = new unsigned int[s.size()];
		
		for (auto i = 0U; i < s.size(); i++)
		{
			data[i] = s[i];
		}

		auto result = LowestCommonMultiple(data, s.size());
		delete[] data;
		return result;
	}

	return 0U;
}



unsigned int Functions::LowestCommonMultiple(unsigned int * a, const unsigned int & l)
{
	unsigned int return_value = 0;

	if (a != NULL && l > 0)
	{
		// Obtain lcm_counter, the number of integers > 1.
		// Also exit if any of the numbers include 0.

		bool is_valid = true;
		unsigned int lcm_counter = 0;

		for (unsigned int i = 0; i < l; i++)
		{
			if (a[i] == 0)
			{
				is_valid = false;
				break;
			}
			else if (a[i] > 1)
			{
				lcm_counter++;
			}
		}

		if (is_valid)
		{
			return_value = 1;

			if (lcm_counter > 0)
			{
				while (lcm_counter > 0)
				{
					for (unsigned int i = 0; i < l; i++)
					{
						if (a[i] > 1)
						{
							unsigned int divisor = 2;
							while (a[i] % divisor > 0) { divisor++; }

							// Apply divisor to integer plus all following integers where possible.

							return_value *= divisor;
							a[i] /= divisor;
							if (a[i] == 1) { lcm_counter--; }

							for (unsigned int j = i + 1; j < l; j++)
							{
								if (a[j] % divisor == 0)
								{
									a[j] /= divisor;
									if (a[j] == 1) { lcm_counter--; }
								}
							}

							break;
						}
					}
				}
			}
		}
	}

	return return_value;
}



unsigned int Functions::Bits(unsigned int s)
{
	unsigned int result = 0U;

	while (s)
	{
		if (s & 1U)
		{
			result++;
		}

		s >>= 1U;
	}

	return result;
}



/* ### Helper functions. ### */



std::map<unsigned int, unsigned int>* PrimeFactorise(unsigned int n)
{
	std::map<unsigned int, unsigned int>* return_map = new std::map<unsigned int, unsigned int>;

	unsigned int divisor = 2;

	while (n > 1)
	{
		bool divisor_used = false;

		while (n % divisor == 0)
		{
			if (divisor_used)
			{
				(*return_map)[divisor] += 1;
			}
			else
			{
				(*return_map)[divisor] = 1;
				divisor_used = true;
			}

			n /= divisor;
		}

		divisor++;
	}

	return return_map;
}



void PrimeFactorise_Multiply(std::map<unsigned int, unsigned int>* p1, std::map<unsigned int, unsigned int>* p2)
{
	for (auto i = p2->begin(); i != p2->end(); i++)
	{
		if (p1->find(i->first) != p1->end())
		{
			(*p1)[i->first] += i->second;
		}
		else
		{
			(*p1)[i->first] = i->second;
		}
	}
}



void PrimeFactorise_Divide(std::map<unsigned int, unsigned int>* p1, std::map<unsigned int, unsigned int>* p2)
{
	for (auto i = p2->begin(); i != p2->end(); i++)
	{
		(*p1)[i->first] -= i->second;
	}
}