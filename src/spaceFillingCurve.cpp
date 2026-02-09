#include "../inc/readySetBool.hpp"

double readySetBool::map(uint16_t x, uint16_t y)
{
	long int result;
	int i;
	double value;
	std::cout << 8 * sizeof(long int) << std::endl;
	std::cout << 8 * sizeof(uint16_t) << std::endl;
	std::cout << 8 * sizeof(double) << std::endl;

	
	result = 0;
	i = 15;
	while (i >= 0)
	{
		result = result << 1;
		if (y & (1 << i))
			result = result + 1;
		result = result << 1;
		if (x & (1 << i))
			result = result + 1;

		i--;
	}
	// printf("X: %b\n", x);
	// printf("Y: %b\n", y);
	std::cout << "x: " << std::bitset<16>(x) << std::endl;
	std::cout << "y: " << std::bitset<16>(y) << std::endl;
	std::cout << "result: " << std::bitset<16>(result) << std::endl;
	// printf("result: %lb\n", result);
	//std::cout << UINT_MAX << std::endl;
	std::cout << result << std::endl;
	value = (double)result / (double)UINT_MAX;
	return(value);
}

std::pair<uint16_t, uint16_t> readySetBool::reverse_map(double z)
{
	int			i;
	uint16_t	x;
	uint16_t	y;
	long int intermediate;

	i = 15;
	x = 0;
	y = 0;
	intermediate = (long int)(z * UINT_MAX);
	std::cout << intermediate << std::endl;
	while (i >= 0)
	{
		x = x << 1;
		y = y << 1;
		if (intermediate & (1 << 2 * i))
			x = x + 1;
		if (intermediate & (1 << (2 * i + 1)))
			y = y + 1;
		i--;
	}
	std::cout << "x: " << std::bitset<16>(x) << std::endl;
	std::cout << "y: " << std::bitset<16>(y) << std::endl;
	return(std::pair<uint16_t, uint16_t>(x, y));
}