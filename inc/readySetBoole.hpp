#ifndef READYSETBOOLE_HPP
# define READYSETBOOLE_HPP

# include <stack>
# include <set>
# include <vector>
# include <algorithm>
# include <string>
# include <iostream>
# include <stdexcept>
# include <cstdint>
# include <limits>
# include <climits>
# include <utility>
# include <map>
# include <bitset>

# define BIT_SIZE 32

//TODO change strings for string references.

	namespace readySetBool
	{
			unsigned int adder(unsigned int a, unsigned int b);
			unsigned int multiplier(unsigned int a, unsigned int b);
			unsigned int gray_code(unsigned int n);

			bool eval_formula(std::string formula);
			bool optimized_eval_formula(std::string formula, int numProposition,  int *indexArray, int	permutation);
			void print_truth_table(std::string formula);

			int	countPropositionsIndex(std::string formula, int *indexArray);

			std::string negation_formal_norm(std::string formula);
			std::string de_morgan_laws(char op, int position, std::string formula, std::map<std::string, std::string(*)(std::string, std::string)> &negationFormalNormMap);

			std::string conjunctive_normal_form(std::string formula);

			bool sat(std::string formula);

			std::vector<std::vector<int>> powerset(std::vector<int> set);
			std::vector<int> eval_set(std::string &formula, std::vector<std::vector<int>> sets);

			//bonus
			double map(uint16_t x, uint16_t y);
			std::pair<uint16_t, uint16_t> reverse_map(double z);

			class InvalidInputException: public std::exception
			{
				public:
					virtual const char *what() const throw();
			};
	};

#endif
