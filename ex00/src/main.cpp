#include "../inc/tester.hpp"

std::string conjunctive_normal_form(std::string formula)
{
	int					i;
	int					j;
	int					numProposition;
	std::vector<char>	setPropositions;
	std::string			tmpFormula;
	std::string			cnf;

	i = 0;
	numProposition = 0;
	while (i < formula.length())
	{
		if (issupper(formula[i]) && std::find(setPropositions.begin(), setPropositions.end(), formula[i]))
		{
			numProposition++;
			setPropositions.push_back(formula[i]);
		}
	}
	i = 0;
	while (i < (1 << numProposition))
	{
		tmpFormula = formula;
		for (std::string::iterator it = tmpFormula.begin(); it != tmpFormula.end(); it++)
		{
			if (std::find(setPropositions.begin(), setPropositions.end(), *it) != setPropositions.end())
			{
				j = (numProposition - 1)- (std::find(setPropositions.begin(), setPropositions.end(), *it)- setPropositions.begin());
				if (i & (1 << j))
					*it = '1';
				else
					*it = '0';
			}
		}
		if (obj.eval_formula(tmpFormula) == false)
		{
			cnf = cnf + 
		}
		i++;
	}
}

int main(void)
{
	try
	{
		//adder_tester();
		//gray_code_tester();
		//eval_formula_tester();
		//print_truth_table_tester();
		//negation_formal_norm_tester();
		//sat_tester();
		//powerset_tester();
	}
	catch (std::exception &e)
	{
		std::cout << e.what() << std::endl;
	}
	return (0);
}
