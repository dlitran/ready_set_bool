#include "../inc/tester.hpp"
#include <stdio.h>
#include <iomanip>

void	spaceFillingCurve_tester(void)
{
	double a;
	std::pair<uint16_t, uint16_t> reverse_a;
	a = readySetBool::map(std::numeric_limits<uint16_t>::max() - 1, std::numeric_limits<uint16_t>::max());
	std::cout << std::fixed << std::setprecision(20) << (double)a << std::endl;
	reverse_a = readySetBool::reverse_map(a);
	std::cout << "first: " << reverse_a.first << std::endl;
	std::cout << "second: " << reverse_a.second << std::endl;
	std::cout << std::numeric_limits<uint16_t>::max() << std::endl;
}

std::string	substitute_formula(std::string formula, int *indexArray, int numProposition, int permutation)
{
	std::string result;
	int	position;

	result = formula;
	for (int it = 0; it < (int)result.length(); it++)
	{
		if (isupper(formula[it]))
		{
			position = numProposition - indexArray[(int)formula[it]];
			if (permutation & (1 << position))
					result[it] = '1';
				else
					result[it] = '0';
		}
	}
	return(result);
}

void	randomTest(void)
{
	int	indexArray[128];
	std::string formula = "AB&";
	int numProposition = readySetBool::countPropositionsIndex(formula, indexArray);
	std::cout << substitute_formula(formula, indexArray, numProposition, 2) << std::endl;
}

int main(void)
{
	try
	{
		// adder_tester();
		// gray_code_tester();
		// eval_formula_tester();
		// print_truth_table_tester();
		// negation_formal_norm_tester();
		// conjunction_formal_norm_tester();
		sat_tester();
		powerset_tester();
		eval_set_tester();
		
	}
	catch (std::exception &e)
	{
		std::cout << e.what() << std::endl;
	}
	return (0);
}
