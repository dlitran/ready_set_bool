#include "../inc/readySetBool.hpp"

readySetBool::readySetBool()
{

}

readySetBool::~readySetBool()
{

}

readySetBool::readySetBool(const readySetBool &src)
{
	(void)src;
	//*this = src;
	//Not best practices but works.
}

readySetBool &readySetBool::operator=(const readySetBool &rhs)
{
	// if (this != &rhs)
	// {
	(void)rhs;
	// }
	return (*this);
}

unsigned int readySetBool::adder(unsigned int a, unsigned int b)
{
	int i;
	int rest;
	unsigned int num;

	i = 0;
	num = 0;
	rest = 0;
	while (i < BIT_SIZE)
	{
		//std::cout << "iteration " << i << std::endl;
		num = num | (((a & 1 << i) ^ (b & 1 << i)) ^ (rest << i));
		if (num & 1 << i) //new digit is 1.
		{
			if ((a & 1 << i) & (b & 1 << i) & (rest << i)) // all of them are 1.
				rest = 1;
			else
				rest = 0;
			i++;
			continue;
		}
		if ((a & 1 << i) | (b & 1 << i) | (rest << i)) //new digit is 0
			rest = 1;
		else
			rest = 0;
		i++;
	}
	return (num);
}

unsigned int readySetBool::multiplier(unsigned int a, unsigned int b)
{
	unsigned int num;
	unsigned int tmp;
	int i;

	num = 0;
	tmp = 0;
	i = 0;
	while (i < BIT_SIZE)
	{
		tmp = 0;
		if (b & (1 << i)) //if the second number in the position i has a 1.
			tmp = a;
		//std::cout << "iteration: " << i << " tmp value: " << tmp << std::endl;
		num = adder(num, tmp << i);
		i++;
	}
	return (num);
}

/*
Created by frank gray. Also called reflected binary code, cyclic code, unweighted code, unit distance doce, minimum error code.
Two successive values differ in only one bit
Less error-prone
Reduce switching operation
Formed by recursive reflexion.
*/
unsigned int readySetBool::gray_code(unsigned int n)
{
	int	i;
	unsigned int comparison;
	unsigned int	gray;

	comparison = n >> 1;
	gray = 0;
	i = 31;
	while (i >= 0)
	{
		if ((n & (1 << i)) != 0)
			break ;
		i--;
	}
	gray = n & (1 << i);
	if (i > 0)
		i--;
	while (i >= 0)
	{
		//std::cout << "n: " << (n & (1 << i)) << std::endl;
		//std::cout << "comparison: " << (comparison & (1 << i)) << std::endl;
		gray = gray | ((n & (1 << i)) ^ (comparison & (1 << i)));
		i--;
	}
	return (gray);
}

bool readySetBool::eval_formula(std::string formula) //Add possibility of multiple equal letters.
{
	std::stack<bool> formulaStack;
	bool	tmp1;
	bool	tmp2;

	for (int it = 0; it < (int)formula.length(); it++)
	{
		if (formula[it] != '1' && formula[it] != '0')
		{
			if (formula[it] == '!')
			{
				if (formulaStack.size() < 1)
					throw readySetBool::InvalidInputException();
				tmp1 = formulaStack.top();
				formulaStack.pop();
				formulaStack.push(!tmp1);
			}
			else
			{
				if (formulaStack.size() < 2)
					throw readySetBool::InvalidInputException();
				if (formula[it] == '&')
				{
					tmp1 = formulaStack.top();
					formulaStack.pop();
					tmp2 = formulaStack.top();
					formulaStack.pop();
					//std::cout << "check" << "tmp1: " << tmp1 << "tmp2: " << tmp2 << std::endl;
					formulaStack.push(tmp1 && tmp2);
				}
				else if (formula[it] == '|')
				{
					tmp1 = formulaStack.top();
					formulaStack.pop();
					tmp2 = formulaStack.top();
					formulaStack.pop();
					formulaStack.push(tmp1 || tmp2);
				}
				else if (formula[it] == '^')
				{
					tmp1 = formulaStack.top();
					formulaStack.pop();
					tmp2 = formulaStack.top();
					formulaStack.pop();
					formulaStack.push(tmp1 ^ tmp2);
				}
				else if (formula[it] == '>')
				{
					tmp1 = formulaStack.top();
					formulaStack.pop();
					tmp2 = formulaStack.top();
					formulaStack.pop();
					if (tmp2 == true && tmp1 == false)
						formulaStack.push(false);
					else
						formulaStack.push(true);
				}
				else if (formula[it] == '=')
				{
					tmp1 = formulaStack.top();
					formulaStack.pop();
					tmp2 = formulaStack.top();
					formulaStack.pop();
					formulaStack.push(!(tmp1 ^ tmp2));
				}
				else
					throw readySetBool::InvalidInputException();
			}
			// else
			// 	throw

		}
		if (formula[it] == '1')
			formulaStack.push(true);
		if (formula[it] == '0')
			formulaStack.push(false);
	}
	if (formulaStack.size() != 1)
		throw readySetBool::InvalidInputException();
	return (formulaStack.top());
}

void readySetBool::print_truth_table(std::string formula)
{
	int	numProposition;
	int	i;
	int	j;
	std::string	tmpFormula;
	std::vector<char> setPropositions;
	readySetBool obj;

	numProposition = 0;
	for (std::string::iterator it = formula.begin(); it != formula.end(); it++)
	{
		if (isupper(*it) && (std::find(setPropositions.begin(), setPropositions.end(), *it) == setPropositions.end()))
		{
			setPropositions.push_back(*it);
			numProposition++; //set a limit.
		}
	}
	//std::cout << "number of propositions: " << numProposition << std::endl;
	i = 0;
	std::cout << "| ";
	for (std::vector<char>::iterator it = setPropositions.begin(); it != setPropositions.end(); it++)
		std::cout << *it << " | ";
	std::cout << "= |" << std::endl;
	j = 0;
	while (j < (numProposition + 1))
	{
		std::cout << "|---";
		j++;
	}
	std::cout << "|" << std::endl;
	while (i < (1 << numProposition)) //The power of two of numProposition
	{
		j = numProposition -1;
		std::cout << "|";
		while (j >= 0)
		{
			if (i & (1 << j))
				std::cout << " 1";
			else
				std::cout << " 0";
			std::cout << " |";
			j--;
		}
		//j = numProposition -1;
		tmpFormula = formula;
		for (std::string::iterator it = tmpFormula.begin(); it != tmpFormula.end(); it++)
		{
			if (std::find(setPropositions.begin(), setPropositions.end(), *it) != setPropositions.end())
			{
				j = (numProposition - 1) - (std::find(setPropositions.begin(), setPropositions.end(), *it) - setPropositions.begin());
				if (i & (1 << j))
					*it = '1';
				else
					*it = '0';
				//j--;
			}
		}
		//std::cout << std::endl;
		//std::cout << std::endl << formula << std::endl;
		//std::cout << std::endl << tmpFormula << std::endl;
		std::cout << " " << obj.eval_formula(tmpFormula) << " |" << std::endl;
		i++;
	}
}

std::string readySetBool::de_morgan_laws(char op, int position, std::string formula)
{
	std::stack<std::string> formulaStack;
	std::string	tmp1;
	std::string	tmp2;
	for (int i = 0; i < position; i++)
	{
		if (isupper(formula[i]))
		{
			formulaStack.push(std::string(&formula[i], 1));
			//std::cout << "upper" << std::endl;
		}
		else if (formula[i] == '|')
		{
			tmp1 = formulaStack.top();
			formulaStack.pop();
			tmp2 = formulaStack.top();
			formulaStack.pop();
			formulaStack.push(tmp2 + tmp1 + "|");
			//std::cout << "or" << std::endl;
		}
		else if (formula[i] == '&')
		{
			tmp1 = formulaStack.top();
			formulaStack.pop();
			tmp2 = formulaStack.top();
			formulaStack.pop();
			formulaStack.push(tmp2 + tmp1 + "&");
			//std::cout << "and" << std::endl;
		}
		else if (formula[i] == '=')
		{
			//std::cout << "=" << std::endl;
			tmp1 = formulaStack.top();
			formulaStack.pop();
			tmp2 = formulaStack.top();
			formulaStack.pop();
			formulaStack.push(negation_formal_norm(tmp2 + tmp1 + ">" + tmp1 + tmp2 + ">" + "&"));
			//std::cout << "=" << std::endl;
		}
		else if (formula[i] == '>')
		{
			//std::cout << ">" << std::endl;
			tmp1 = formulaStack.top();
			formulaStack.pop();
			tmp2 = formulaStack.top();
			formulaStack.pop();
			formulaStack.push(negation_formal_norm(tmp2 + "!" + tmp1 + "|"));
			//std::cout << ">" << std::endl;
		}
		else if (formula[i] == '!')
		{
			//std::cout << "!" << std::endl;
			tmp1 = formulaStack.top();
			formulaStack.pop();
			if (tmp1[tmp1.size() - 1] == '!') //Double negation
				tmp1.erase(tmp1.size() - 1);
			else //Add negation
				tmp1 += '!';
			formulaStack.push(negation_formal_norm(tmp1));
			//std::cout << "!" << std::endl;
		}
	}
	tmp1 = formulaStack.top();
	formulaStack.pop();
	tmp2 = formulaStack.top();
	formulaStack.pop();
	if (op == '|')
		return (tmp2 + "!" + tmp1 + "!&");
	else
		return (tmp2 + "!" + tmp1 + "!|");
}

std::string readySetBool::negation_formal_norm(std::string formula)
{
	std::stack<std::string> formulaStack;
	std::string	tmp1;
	std::string	tmp2;

	if (formula.size() <= 2)
		return (formula);
	for (int i = 0; i < (int)formula.size(); i++)
	{

		if (isupper(formula[i]))
		{
			formulaStack.push(std::string(&formula[i], 1));
			//std::cout << "upper" << std::endl;
		}
		else if (formula[i] == '|')
		{
			tmp1 = formulaStack.top();
			formulaStack.pop();
			tmp2 = formulaStack.top();
			formulaStack.pop();
			formulaStack.push(tmp2 + tmp1 + "|");
			//std::cout << "or" << std::endl;
		}
		else if (formula[i] == '&')
		{
			tmp1 = formulaStack.top();
			formulaStack.pop();
			tmp2 = formulaStack.top();
			formulaStack.pop();
			formulaStack.push(tmp2 + tmp1 + "&");
			//std::cout << "and" << std::endl;
		}
		else if (formula[i] == '=')
		{
			//std::cout << "=" << std::endl;
			tmp1 = formulaStack.top();
			formulaStack.pop();
			tmp2 = formulaStack.top();
			formulaStack.pop();
			formulaStack.push(negation_formal_norm(tmp2 + tmp1 + ">" + tmp1 + tmp2 + ">" + "&"));
			//std::cout << "=" << std::endl;
		}
		else if (formula[i] == '>')
		{
			//std::cout << ">" << std::endl;
			tmp1 = formulaStack.top();
			formulaStack.pop();
			tmp2 = formulaStack.top();
			formulaStack.pop();
			formulaStack.push(negation_formal_norm(tmp2 + "!" + tmp1 + "|")); // a -> b <-> !b | A is a tautology
			//std::cout << ">" << std::endl;
		}
		else if (formula[i] == '!')
		{
			//std::cout << "!" << std::endl;
			tmp1 = formulaStack.top();
			formulaStack.pop();
			if (tmp1[tmp1.size() - 1] == '!') //Double negation
				tmp1.erase(tmp1.size() - 1);
			else //Add negation
				tmp1 += '!';
			//De Morgan laws
			if (tmp1[tmp1.size() - 2] == '|')
				tmp1 = de_morgan_laws('|', (int)(tmp1.size() - 2), tmp1);
			else if (tmp1[tmp1.size() - 2] == '&')
				tmp1 = de_morgan_laws('&', (int)(tmp1.size() - 2), tmp1);

			formulaStack.push(negation_formal_norm(tmp1));
			//std::cout << "!" << std::endl;
		}
	}
	return (formulaStack.top());
}

std::string readySetBool::conjunctive_normal_form(std::string formula)
{
	readySetBool		obj;
	int					i;
	int					j;
	int					conjunction_count;
	int					numProposition;
	std::vector<char>	setPropositions;
	std::string			tmpFormula;
	std::string			cnf;

	i = 0;
	conjunction_count = 0;
	numProposition = 0;
	for (std::string::iterator it = formula.begin(); it != formula.end(); it++)
	{
		if (isupper(*it) && std::find(setPropositions.begin(), setPropositions.end(), *it) == setPropositions.end())
		{
			setPropositions.push_back(*it);
			numProposition++;
		}
	}
	i = 0;
	cnf = "";
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
			conjunction_count++;
			for (int it = 0 ; it < numProposition; it++)
			{
					j = (numProposition - 1)- it;
					if (i & (1 << j))
						cnf = cnf + setPropositions[it] +  "!"; //when it's true, false (morgan's law)
					else
						cnf = cnf + setPropositions[it];
			}
			for (int iterator = 0; iterator < (numProposition - 1); iterator++)
				cnf = cnf + "|";
		}
		i++;
	}
	for (int iterator = 0; iterator < (conjunction_count - 1); iterator++)
		cnf = cnf + "&";
	//TODO Further optimization can be done here.
	return(cnf);
}

bool readySetBool::sat(std::string formula)
{
	int	numProposition;
	int	i;
	int	j;
	std::vector<char> setPropositions;
	std::string tmpFormula;
	readySetBool obj;

	numProposition = 0;
	for (std::string::iterator it = formula.begin(); it != formula.end(); it++)
	{
		if (isupper(*it) && std::find(setPropositions.begin(), setPropositions.end(), *it) == setPropositions.end())
		{
			setPropositions.push_back(*it);
			numProposition++;
		}
	}
	i = 0;
	j = 0;
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
				//j--;
			}
		}
		//std::cout << std::endl;
		//std::cout << std::endl << formula << std::endl;
		//std::cout << std::endl << tmpFormula << std::endl;
		if (obj.eval_formula(tmpFormula) == true)
		{
			std::cout << tmpFormula << std::endl;
			return (true);
		}
		i++;
	}
	return (false);
}


std::vector<std::vector<int>> readySetBool::powerset(std::vector<int> set)
{
	/*to calculate the powerset we consider that each element has two possible states: include or excluede.*/
	int	cardinal;
	int	i;
	int powerSetCardinal;
	std::vector<int> tmp;
	std::vector<std::vector<int>> powerSet;

	cardinal = set.size();
	powerSetCardinal = (1 << cardinal);
	i = 0;
	while (i < powerSetCardinal)
	{
		for (int j = 0; j < cardinal; j++)
		{
			if (i & (1 << j))
				tmp.push_back(set[j]);
		}
		powerSet.push_back(tmp);
		tmp.clear();
		i++;
	}
	return(powerSet);

}

const char *readySetBool::InvalidInputException::what() const throw()
{
	return("Error: Invalid input.");
}
