#include "../inc/tester.hpp"

std::vector<int> eval_set(std::string &formula, std::vector<std::vector<int>> sets)
{

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
		conjunction_formal_norm_tester();
		//sat_tester();
		//powerset_tester();
	}
	catch (std::exception &e)
	{
		std::cout << e.what() << std::endl;
	}
	return (0);
}
