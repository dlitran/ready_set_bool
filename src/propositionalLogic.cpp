#include "../inc/readySetBool.hpp"

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
		std::cout << " " << readySetBool::eval_formula(tmpFormula) << " |" << std::endl;
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
		if (readySetBool::eval_formula(tmpFormula) == false)
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
		if (readySetBool::eval_formula(tmpFormula) == true)
		{
			std::cout << tmpFormula << std::endl;
			return (true);
		}
		i++;
	}
	return (false);
}