#include "../inc/tester.hpp"

void adder_tester(void)
{
	unsigned int	num;
	unsigned int	a;
	unsigned int	b;
	int				i;

	//test normal value
	a = 100009;
	b = 60;
	num = readySetBool::adder(a, b);
	std::cout << num << std::endl;
	i = 31;
	while (i >= 0)
	{
		if (num & 1 << i)
			std::cout << "1";
		else
			std::cout << "0";
		i--;
	}
	std::cout << std::endl;
	if (num == (a + b))
		std::cout << "everything fine" << std::endl;

	//test out of limit values
	a = UINT_MAX;
	b = UINT_MAX;
	num = readySetBool::adder(a, b);
	std::cout << num << std::endl;
	i = 31;
	while (i >= 0)
	{
		if (num & 1 << i)
			std::cout << "1";
		else
			std::cout << "0";
		i--;
	}
	std::cout << std::endl;
	if (num == (a + b))
		std::cout << "everything fine" << std::endl;

	srand(static_cast<unsigned int>(time(NULL)));
	std::cout << "RAND_MAX is: " << RAND_MAX << std::endl;
	for (int it = 0; it < 100; it++)
	{
		a = rand();
		b = rand();
		//std::cout << "a: " << a << " b: " << b << std::endl;
		if (readySetBool::adder(a, b) != (a + b))
		{
			std::cout << "something failed" << std::endl;
		}
	}
	std::cout << "everything fine" << std::endl;
	//Test all possible values
	// for (unsigned int it = 0; it <= UINT_MAX; it++)
	// {
	// 	for (unsigned int it2 = 99999999; it2 <= UINT_MAX; it2++)
	// 	{
	// 		num = readySetBool::adder(it, it2);
	// 		if (num != (it + it2))
	// 		{
	// 			std::cout << "Different values" << std::endl;
	// 			return;
	// 		}
	// 	}
	// }
	// std::cout << "Everything is fine" << std::endl;
}

void multiplier_tester(void)
{
	unsigned int	num;
	int				i;

	num = readySetBool::multiplier(105, 6);
	std::cout << num << std::endl;
	i = 31;
	while (i >= 0)
	{
		if (num & 1 << i)
			std::cout << "1";
		else
			std::cout << "0";
		i--;
	}
	std::cout << std::endl;
}

void gray_code_tester(void)
{
	unsigned int	gray;
	unsigned int	num;
	int	i;

	//Max unsigned interger
	num = UINT_MAX;
	std::cout << "Max unsigned int: " << num << std::endl;
	i = 31;
	while (i >= 0)
	{
		if (num & 1 << i)
			std::cout << "1";
		else
			std::cout << "0";
		i--;
	}
	std::cout << std::endl;
	gray = readySetBool::gray_code(num);
	i = 31;
	while (i >= 0)
	{
		if (gray & 1 << i)
			std::cout << "1";
		else
			std::cout << "0";
		i--;
	}
	std::cout << std::endl;

	//From 0 to 20:
	for (int it = 0; it <= 20 ; it++)
	{
		num = it;
		std::cout << "Number: " << num << std::endl;
		i = 31;
		while (i >= 0)
		{
			if (num & 1 << i)
				std::cout << "1";
			else
				std::cout << "0";
			i--;
		}
		std::cout << std::endl;
		gray = readySetBool::gray_code(num);
		std::cout << "Number after transformation: " << gray << std::endl;
		i = 31;
		while (i >= 0)
		{
			if (gray & 1 << i)
				std::cout << "1";
			else
				std::cout << "0";
			i--;
		}
		std::cout << std::endl;
	}

}

void	testFormula(std::string &formula)
{
	bool statement;

	std:: cout << "\033[34m" << formula << "\033[0m";
	statement = readySetBool::eval_formula(formula);
	if (statement == true)
		std::cout << ": \033[32mtrue\033[0m" << std::endl;
	else
		std::cout << ": \033[31mfalse\033[0m" << std::endl;
}

void eval_formula_tester(void)
{
	std::string	formula;

	formula = "0!1^";
	testFormula(formula);
	formula = "01>";
	testFormula(formula);
	formula = "001||1>";
	testFormula(formula);
	formula = "001||1>!";
	testFormula(formula);
}

void print_truth_table_tester(void)
{
	//readySetBool::print_truth_table("AB>");
	readySetBool::print_truth_table("AZB&&");
	// readySetBool::print_truth_table("AB=");
	// readySetBool::print_truth_table("AB&");
	// readySetBool::print_truth_table("AB&C|");
	// readySetBool::print_truth_table("ABC&|DE!|F=!=!!");
}

std::vector<bool>	testEquivalence(std::string formula)
{
	int	numProposition;
	int	permutation;
    int indexArray[128] = {};
	std::vector<bool> result;

	numProposition = readySetBool::countPropositionsIndex(formula, indexArray);
	permutation = 0;
	while (permutation < (1 << numProposition))
	{
		result.insert(result.end(), readySetBool::optimized_eval_formula(formula, numProposition,  indexArray, permutation));
		permutation++;
	}
	return (result);
}

void	testNorm(std::string formula, bool formalNorm)
{
	std::string	norm;
	std::vector<bool> vectorFormula;
	std::vector<bool> vectorNorm;

	std::cout << "before: " << formula << std::endl;
	vectorFormula = testEquivalence(formula);
	if (formalNorm == 0)
		norm = readySetBool::negation_formal_norm(formula);
	else
		norm = readySetBool::conjunctive_normal_form(formula);
	vectorNorm = testEquivalence(norm);
	std::cout << "after: " << norm << std::endl;
	if (vectorFormula ==  vectorNorm)
		std::cout << "\033[32mCorrect\033[0m" << std::endl;
	else
		std::cout << "\033[31mIncorrect\033[0m" << std::endl;
	// for (std::vector<bool>::iterator it = vectorNorm.begin(); it != vectorNorm.end(); it++)
	// 	std::cout << *it << ", ";
	// std::cout << std::endl;
	// for (std::vector<bool>::iterator it = vectorFormula.begin(); it != vectorFormula.end(); it++)
	// 	std::cout << *it << ", ";
	// std::cout << std::endl;
}

void negation_formal_norm_tester(void)
{
	std::string	formula;

	formula = "AB=!";
	testNorm(formula, 0);

	formula = "BA|";
	testNorm(formula, 0);

	formula = "AB&";
	testNorm(formula, 0);

	formula = "AB^";
	testNorm(formula, 0);

	formula = "AB=";
	testNorm(formula, 0);

	formula = "AB>";
	testNorm(formula, 0);

	formula = "A!";
	testNorm(formula, 0);

	formula = "AB|C&";
	testNorm(formula, 0);

	formula = "ABC&|";
	testNorm(formula, 0);

	formula = "AB|C^";
	testNorm(formula, 0);

	formula = "AB&!C|";
	testNorm(formula, 0);

	formula = "AB=!C&";
	testNorm(formula, 0);

	formula = "AB>C>";
	testNorm(formula, 0);

	formula = "ABC||";
	testNorm(formula, 0);

	formula = "ABC&&";
	testNorm(formula, 0);

	formula = "AB&!C>!";
	testNorm(formula, 0);

	formula = "AB|C^D&";
	testNorm(formula, 0);

	formula = "ABCD&&|";
	testNorm(formula, 0);

	formula = "AB^C=!D|";
	testNorm(formula, 0);

	formula = "AB>!C&D=";
	testNorm(formula, 0);

	formula = "ABCD>>>";
	testNorm(formula, 0);

	formula = "AB^C=";
	testNorm(formula, 0);

	formula = "ABC!&!!|DE!|F=!=!A!&";
	testNorm(formula, 0);

	formula = "AB>BC>&AC>>";
	testNorm(formula, 0);

	formula = "AB|!A!B!&>A!B!&AB|!>&";
	testNorm(formula, 0);

	formula = "AB|C>CD>AD>>&";
	testNorm(formula, 0);

	formula = "AB>!AB!&>";
	testNorm(formula, 0);

	formula = "AB^AC>BC>&C>>";
	testNorm(formula, 0);

	// formula = "!";
	// testNorm(formula, 0);
}

void sat_tester(void)
{
	std::string formula;

	formula = "AA!&";
	if (readySetBool::sat(formula) == true)
		std::cout << "satisfiable" << std::endl;
	else
		std::cout << "not satisfiable" << std::endl;

	formula = "ABC||A!B!C!&&&";
	if (readySetBool::sat(formula) == true)
		std::cout << "satisfiable" << std::endl;
	else
		std::cout << "not satisfiable" << std::endl;

	formula = "ABC&|DE!|F=!=!!";
	if (readySetBool::sat(formula) == true)
		std::cout << "satisfiable" << std::endl;
	else
		std::cout << "not satisfiable" << std::endl;
}

void powerset_tester(void)
{
	std::vector<int> set = {1, 2, 3, 4, 5, 6};
		std::vector<std::vector<int>> powerSet = readySetBool::powerset(set);
		for (std::vector<std::vector<int>>::iterator it1 = powerSet.begin(); it1 != powerSet.end(); it1++)
		{
			std::cout << "{ ";
			for (std::vector<int>::iterator it2 = (*it1).begin(); it2 != (*it1).end(); it2++)
			{
				std::cout << *it2 << " ";
			}
			std::cout << "}" << std::endl;
		}
}

void conjunction_formal_norm_tester(void)
{
	std::string		formula;
	std::string		result;

	// formula = "ABC!&^";
	// readySetBool::print_truth_table(formula);
	// result = readySetBool::conjunctive_normal_form(formula);
	// std::cout << result << std::endl;
	// readySetBool::print_truth_table(result);

	formula = "A!B&CA!&AB|=^!";
	testNorm(formula, 1);

	formula = "AB=!";
	testNorm(formula, 1);

	formula = "BA|";
	testNorm(formula, 1);

	formula = "AB&";
	testNorm(formula, 1);

	formula = "AB^";
	testNorm(formula, 1);

	formula = "AB=";
	testNorm(formula, 1);

	formula = "AB>";
	testNorm(formula, 1);

	formula = "A!";
	testNorm(formula, 1);

	formula = "AB|C&";
	testNorm(formula, 1);

	formula = "ABC&|";
	testNorm(formula, 1);

	formula = "AB|C^";
	testNorm(formula, 1);

	formula = "AB&!C|";
	testNorm(formula, 1);

	formula = "AB=!C&";
	testNorm(formula, 1);

	formula = "AB>C>";
	testNorm(formula, 1);

	formula = "ABC||";
	testNorm(formula, 1);

	formula = "ABC&&";
	testNorm(formula, 1);

	formula = "AB&!C>!";
	testNorm(formula, 1);

	formula = "AB|C^D&";
	testNorm(formula, 1);

	formula = "ABCD&&|";
	testNorm(formula, 1);

	formula = "AB^C=!D|";
	testNorm(formula, 1);

	formula = "AB>!C&D=";
	testNorm(formula, 1);

	formula = "ABCD>>>";
	testNorm(formula, 1);

	formula = "AB^C=";
	testNorm(formula, 1);

	formula = "ABC!&!!|DE!|F=!=!A!&";
	testNorm(formula, 1);

	formula = "AB>BC>&AC>>";
	testNorm(formula, 1);

	formula = "AB|!A!B!&>A!B!&AB|!>&";
	testNorm(formula, 1);

	formula = "AB|C>CD>AD>>&";
	testNorm(formula, 1);

	formula = "AB>!AB!&>";
	testNorm(formula, 1);

	formula = "AB^AC>BC>&C>>";
	testNorm(formula, 1);

	// formula = "!";
	// testNorm(formula, 1);
	
}

void	eval_set_tester(void)
{
	std::string formula;
	formula = "AB&";
	std::vector<int> result;
	std::vector<std::vector<int>> sets;
	sets = {{1, 3, 4, 18}, {1, 2, 3, 4, 5}, {3, 6, 9, 12, 15, 18}};
	result = readySetBool::eval_set(formula, sets);
	for(std::vector<int>::iterator it = result.begin(); it < result.end(); it++)
		std::cout << *it << " ";
	std::cout << std::endl;
}