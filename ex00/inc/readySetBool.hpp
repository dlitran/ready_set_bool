#ifndef READYSETBOOL_HPP
# define READYSETBOOL_HPP

# include <stack>
# include <set>
# include <vector>
# include <algorithm>
# include <string>
# include <iostream>
# include <stdexcept>

# define BIT_SIZE 32

	class readySetBool
	{
		public:
			readySetBool();
			~readySetBool();
			readySetBool(const readySetBool &src);
			readySetBool &operator=(const readySetBool &rhs);

			unsigned int adder(unsigned int a, unsigned int b);
			unsigned int multiplier(unsigned int a, unsigned int b);
			unsigned int gray_code(unsigned int n);
			bool eval_formula(std::string formula);
			void print_truth_table(std::string formula);

			std::string negation_formal_norm(std::string formula);
			std::string de_morgan_laws(char op, int position, std::string formula);

			bool sat(std::string formula);
			std::vector<std::vector<int>> powerset(std::vector<int> set);

			class InvalidInputException: public std::exception
			{
				public:
					virtual const char *what() const throw();
			};
	};

#endif
