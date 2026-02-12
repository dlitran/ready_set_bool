#include "../inc/tester.hpp"

void	print_binary(unsigned int num)
{
	int i = 31;
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

void adder_tester(void)
{
	unsigned int	result;
	unsigned int	a;
	unsigned int	b;

	std::cout << "\033[34mAdder tester:\033[0m" << std::endl;

	//test normal value
	a = 100329;
	b = 60;
	result = readySetBool::adder(a, b);
	std::cout << a << " + " << b  << " = " << result << std::endl;
	print_binary(result);
	if (result == (a + b))
		std::cout <<  "\033[32mCorrect\033[0m" << std::endl;

	//test out of limit values
	a = UINT_MAX;
	b = UINT_MAX;
	result = readySetBool::adder(a, b);
	std::cout << a << " + " << b  << " = " << result << std::endl;
	print_binary(result);
	if (result == (a + b))
		std::cout << "\033[32mCorrect\033[0m" << std::endl;
	else
		std::cout << "\033[31mIncorrect\033[0m" << std::endl;

	//test a hundred random values
	srand(static_cast<unsigned int>(time(NULL)));
	// std::cout << "RAND_MAX is: " << RAND_MAX << std::endl;
	std::cout << "100 random values" << std::endl;
	for (int it = 0; it < 100; it++)
	{
		a = rand();
		b = rand();
		//std::cout << "a: " << a << " b: " << b << std::endl;
		if (readySetBool::adder(a, b) != (a + b))
		{
			std::cout << "\033[31mIncorrect\033[0m" << std::endl;
			return ;
		}
	}
	std::cout << "\033[32mCorrect\033[0m" << std::endl;
}

void multiplier_tester(void)
{
	unsigned int	result;
	unsigned int	a;
	unsigned int	b;

	std::cout << "\033[34mMultipilier tester:\033[0m" << std::endl;

	//test normal value
	a = 105;
	b = 6;
	result = readySetBool::multiplier(a, b);
	std::cout << a << " * " << b  << " = " << result << std::endl;
	print_binary(result);
	if (result == (a * b))
		std::cout <<  "\033[32mCorrect\033[0m" << std::endl;

	//test out of limit values
	a = UINT_MAX;
	b = UINT_MAX;
	result = readySetBool::multiplier(a, b);
	std::cout << a << " * " << b  << " = " << result << std::endl;
	print_binary(result);
	if (result == (a * b))
		std::cout << "\033[32mCorrect\033[0m" << std::endl;
	else
		std::cout << "\033[31mIncorrect\033[0m" << std::endl;

	//test a hundred random values
	srand(static_cast<unsigned int>(time(NULL)));
	// std::cout << "RAND_MAX is: " << RAND_MAX << std::endl;
	std::cout << "100 random values" << std::endl;
	for (int it = 0; it < 100; it++)
	{
		a = rand();
		b = rand();
		// std::cout << "a: " << a << " b: " << b << std::endl;
		if (readySetBool::multiplier(a, b) != (a * b))
		{
			std::cout << "\033[31mIncorrect\033[0m" << std::endl;
			return ;
		}
	}
	std::cout << "\033[32mCorrect\033[0m" << std::endl;
}

void gray_code_tester(void)
{
	unsigned int	gray;
	unsigned int	num;

	std::cout << "\033[34mGray code tester:\033[0m" << std::endl;
	//Max unsigned interger
	num = UINT_MAX;
	std::cout << "Max unsigned int: " << num << std::endl;
	print_binary(num);
	gray = readySetBool::gray_code(num);
	print_binary(gray);

	//From 0 to 20:
	std::cout << "First 17 values" << std::endl;
	for (int it = 0; it <= 16 ; it++)
	{
		num = it;
		// std::cout << "Number: " << num << std::endl;
		// print_binary(num);
		gray = readySetBool::gray_code(num);
		// std::cout << "Gray code: " << std::endl;
		print_binary(gray);
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

	std::cout << "\033[34mBoolean evaluation tester:\033[0m" << std::endl;
	std::cout << "OR" << std::endl;
	formula = "00|";
	testFormula(formula);
	formula = "01|";
	testFormula(formula);
	formula = "10|";
	testFormula(formula);
	formula = "11|";
	testFormula(formula);

	std::cout << "AND" << std::endl;
	formula = "00&";
	testFormula(formula);
	formula = "01&";
	testFormula(formula);
	formula = "10&";
	testFormula(formula);
	formula = "11&";
	testFormula(formula);

	std::cout << "Negation" << std::endl;
	formula = "1!";
	testFormula(formula);
	formula = "0!";
	testFormula(formula);

	std::cout << "XOR" << std::endl;
	formula = "00^";
	testFormula(formula);
	formula = "01^";
	testFormula(formula);
	formula = "10^";
	testFormula(formula);
	formula = "11^";
	testFormula(formula);

	std::cout << "Conditional" << std::endl;
	formula = "00>";
	testFormula(formula);
	formula = "01>";
	testFormula(formula);
	formula = "10>";
	testFormula(formula);
	formula = "11>";
	testFormula(formula);

	std::cout << "Biconditional" << std::endl;
	formula = "00=";
	testFormula(formula);
	formula = "01=";
	testFormula(formula);
	formula = "10=";
	testFormula(formula);
	formula = "11=";
	testFormula(formula);

	std::cout << "Random" << std::endl;
	formula = "0!1^";
	testFormula(formula);
	formula = "01>";
	testFormula(formula);
	formula = "001||1>";
	testFormula(formula);
	formula = "001||1>!";
	testFormula(formula);
	formula = "001||1>11!1^=!&";
	testFormula(formula);
	formula = "001||1>11!1^=!&!";
	testFormula(formula);
	// formula = "11&&";
	// testFormula(formula);
}

void print_truth_table_tester(void)
{
	std::string formula;

	std::cout << "\033[34mTruth table tester:\033[0m" << std::endl;
	formula = "AB>";
	std::cout << formula << std::endl;
	readySetBool::print_truth_table(formula);

	formula = "AZB&&";
	std::cout << formula << std::endl;
	readySetBool::print_truth_table(formula);

	formula = "AB=";
	std::cout << formula << std::endl;
	readySetBool::print_truth_table(formula);

	formula = "AB&";
	std::cout << formula << std::endl;
	readySetBool::print_truth_table(formula);

	formula = "AB&C|";
	std::cout << formula << std::endl;
	readySetBool::print_truth_table(formula);

	formula = "ABC&|DE!|F=!=!!";
	std::cout << formula << std::endl;
	readySetBool::print_truth_table(formula);
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

	std::cout << "\033[34mNegation Normal Form tester:\033[0m" << std::endl;
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

void conjunction_formal_norm_tester(void)
{
	std::string		formula;
	std::string		result;

	std::cout << "\033[34mConjunctive Normal Form tester:\033[0m" << std::endl;

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

void sat_tester(void)
{
	std::string formula;

	std::cout << "\033[34mSAT tester:\033[0m" << std::endl;
	formula = "AA!&";
	std::cout << formula << ": ";
	if (readySetBool::sat(formula) == true)
		std::cout << "\033[32msatisfiable\033[0m" << std::endl;
	else
		std::cout << "\033[31mnot satisfiable\033[0m" << std::endl;

	formula = "ABC||A!B!C!&&&";
	std::cout << formula << ": ";
	if (readySetBool::sat(formula) == true)
		std::cout << "\033[32msatisfiable\033[0m" << std::endl;
	else
		std::cout << "\033[31mnot satisfiable\033[0m" << std::endl;

	formula = "ABC&|DE!|F=!=!!";
	std::cout << formula << ": ";
	if (readySetBool::sat(formula) == true)
		std::cout << "\033[32msatisfiable\033[0m" << std::endl;
	else
		std::cout << "\033[31mnot satisfiable\033[0m" << std::endl;
}

void powerset_tester(void)
{
	std::cout << "\033[34mPowerset tester:\033[0m" << std::endl;
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

void print_result_set(std::string formula, std::vector<std::vector<int>> sets)
{
	std::vector<int> result;

	std::cout << "\033[30m" << formula << "\033[0m" << std::endl;
	result = readySetBool::eval_set(formula, sets);
	std::cout << "{ ";
	for(std::vector<int>::iterator it = result.begin(); it < result.end(); it++)
	{
		std::cout << *it;
		if (it + 1 != result.end())
			std::cout << ", ";
	}
	std::cout <<  " }" << std::endl;
}

void	eval_set_tester(void)
{
	std::string formula;
	std::vector<std::vector<int>> sets;
	int i = 65;

	std::cout << "\033[34mSet evaluation tester:\033[0m" << std::endl;

	sets = {{1, 3, 4, 18}, {1, 2, 3, 4, 5}, {3, 6, 9, 12, 15, 18}};
	for(std::vector<std::vector<int>>::iterator it1 = sets.begin(); it1 != sets.end(); it1++)
	{
		std::cout << "\033[31m" << (char)i << ": \033[0m{ ";
		for(std::vector<int>::iterator it2 = (*it1).begin(); it2 < (*it1).end(); it2++)
		{
			std::cout << *it2;
			if (it2 + 1 != (*it1).end())
				std::cout << ", ";
		}
		std::cout << " }" << std::endl;
		i++;
	}

	formula = "AB&";
	sets = {{1, 3, 4, 18}, {1, 2, 3, 4, 5}, {3, 6, 9, 12, 15, 18}};
	print_result_set(formula, sets);

	formula = "AB|";
	sets = {{1, 3, 4, 18}, {1, 2, 3, 4, 5}, {3, 6, 9, 12, 15, 18}};
	print_result_set(formula, sets);

	formula = "A!B|";
	sets = {{1, 3, 4, 18}, {1, 2, 3, 4, 5}, {3, 6, 9, 12, 15, 18}};
	print_result_set(formula, sets);

	formula = "AB=";
	sets = {{1, 3, 4, 18}, {1, 2, 3, 4, 5}, {3, 6, 9, 12, 15, 18}};
	print_result_set(formula, sets);

	formula = "AB^";
	sets = {{1, 3, 4, 18}, {1, 2, 3, 4, 5}, {3, 6, 9, 12, 15, 18}};
	print_result_set(formula, sets);

	formula = "AB&&";
	sets = {{1, 3, 4, 18}, {1, 2, 3, 4, 5}, {3, 6, 9, 12, 15, 18}};
	print_result_set(formula, sets);
	
}

void	spaceFillingCurve_tester(void)
{
	double a;
	std::pair<uint16_t, uint16_t> reverse_a;
	a = readySetBool::map(std::numeric_limits<uint16_t>::max() - 1, std::numeric_limits<uint16_t>::max());
	// std::cout << std::fixed << std::setprecision(20) << (double)a << std::endl;
	std::cout << std::fixed << (double)a << std::endl;
	reverse_a = readySetBool::reverse_map(a);
	std::cout << "first: " << reverse_a.first << std::endl;
	std::cout << "second: " << reverse_a.second << std::endl;
	std::cout << std::numeric_limits<uint16_t>::max() << std::endl;
}