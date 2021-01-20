#include "Functions.h"

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