#include "../inc/tester.hpp"
#include <stdio.h>
#include <iomanip>

int main(void)
{
	try
	{
		//adder_tester();
		//gray_code_tester();
		//eval_formula_tester();
		//print_truth_table_tester();
		//negation_formal_norm_tester();
		//conjunction_formal_norm_tester();
		//sat_tester();
		//powerset_tester();
		//eval_set_tester();
		double a;
		std::pair<uint16_t, uint16_t> reverse_a;
		a = readySetBool::map(std::numeric_limits<uint16_t>::max() - 1, std::numeric_limits<uint16_t>::max());
		std::cout << std::fixed << std::setprecision(20) << (double)a << std::endl;
		reverse_a = readySetBool::reverse_map(a);
		std::cout << "first: " << reverse_a.first << std::endl;
		std::cout << "second: " << reverse_a.second << std::endl;
		std::cout << std::numeric_limits<uint16_t>::max() << std::endl;
		
	}
	catch (std::exception &e)
	{
		std::cout << e.what() << std::endl;
	}
	return (0);
}
