#include "../inc/readySetBoole.hpp"

unsigned int readySetBoole::adder(unsigned int a, unsigned int b)
{
	int i;
	int remainder;
	unsigned int result;

	i = 0;
	result = 0;
	remainder = 0;
	while (i < BIT_SIZE)
	{
		//std::cout << "iteration " << i << std::endl;
		result = result | (((a & 1 << i) ^ (b & 1 << i)) ^ (remainder << i));
		if (result & 1 << i) //new digit is 1.
		{
			if ((a & 1 << i) & (b & 1 << i) & (remainder << i)) // all of them are 1.
				remainder = 1;
			else
				remainder = 0;
			i++;
			continue;
		}
		if ((a & 1 << i) | (b & 1 << i) | (remainder << i)) //new digit is 0
			remainder = 1;
		else
			remainder = 0;
		i++;
	}
	return (result);
}

unsigned int readySetBoole::multiplier(unsigned int a, unsigned int b)
{
	unsigned int num;
	unsigned int tmp;
	int i;

	num = 0;
	tmp = 0;
	i = 0;
	while (i < BIT_SIZE)
	{
		tmp = 0;
		if (b & (1 << i)) //if the second number in the position i has a 1.
			tmp = a;
		//std::cout << "iteration: " << i << " tmp value: " << tmp << std::endl;
		num = adder(num, tmp << i);
		i++;
	}
	return (num);
}

/*
Created by frank gray. Also called reflected binary code, cyclic code, unweighted code, unit distance doce, minimum error code.
Two successive values differ in only one bit
Less error-prone
Reduce switching operation
Formed by recursive reflexion.
*/
unsigned int readySetBoole::gray_code(unsigned int n)
{
	int	i;
	unsigned int comparison;
	unsigned int	gray;

	comparison = n >> 1;
	gray = 0;
	i = 31;
	while (i >= 0)
	{
		if ((n & (1 << i)) != 0)
			break ;
		i--;
	}
	gray = n & (1 << i);
	if (i > 0)
		i--;
	while (i >= 0)
	{
		//std::cout << "n: " << (n & (1 << i)) << std::endl;
		//std::cout << "comparison: " << (comparison & (1 << i)) << std::endl;
		gray = gray | ((n & (1 << i)) ^ (comparison & (1 << i)));
		i--;
	}
	return (gray);
}
