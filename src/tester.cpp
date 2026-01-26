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

void eval_formula_tester(void)
{
	bool statement;

	// statement = readySetBool::eval_formula("0!1^");
	// if (statement == true)
	// 	std::cout << "the statement is true" << std::endl;
	// else
	// 	std::cout << "the statement is false" << std::endl;
	// statement = readySetBool::eval_formula("01>");
	// if (statement == true)
	// 	std::cout << "the statement is true" << std::endl;
	// else
	// 	std::cout << "the statement is false" << std::endl;
	statement = readySetBool::eval_formula("001||1>");
	if (statement == true)
		std::cout << "the statement is true" << std::endl;
	else
		std::cout << "the statement is false" << std::endl;

}

void print_truth_table_tester(void)
{
	readySetBool::print_truth_table("ABC&|DE!|F=!=!!");
}

void negation_formal_norm_tester(void)
{
	std::string	formula;
	std::string	norm;

	formula = "ABC&|DE!|F=!=!";
	std::cout << "before: " << formula << std::endl;
	norm = readySetBool::negation_formal_norm(formula);
	std::cout << "after: " << norm << std::endl;
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
	readySetBool::print_truth_table(formula);
	result = readySetBool::conjunctive_normal_form(formula);
	std::cout << result << std::endl;
	readySetBool::print_truth_table(result);
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