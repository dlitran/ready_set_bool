#include "../inc/tester.hpp"
#include <stdio.h>
#include <iomanip>

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
	int numProposition = readySetBoole::countPropositionsIndex(formula, indexArray);
	std::cout << substitute_formula(formula, indexArray, numProposition, 2) << std::endl;
}

int main(void)
{
	try
	{
		// adder_tester();
		// multiplier_tester();
		// gray_code_tester();
		// eval_formula_tester();
		// print_truth_table_tester();
		// negation_formal_norm_tester();
		// conjunction_formal_norm_tester();
		// sat_tester();
		// powerset_tester();
		eval_set_tester();
		// spaceFillingCurve_tester();
		
	}
	catch (std::exception &e)
	{
		std::cout << e.what() << std::endl;
	}
	return (0);
}
