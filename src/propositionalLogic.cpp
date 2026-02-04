#include "../inc/readySetBool.hpp"

int	countPropositions(std::string formula, std::vector<char> &setPropositions)
{
	int	numProposition;

	numProposition = 0;
	for (std::string::iterator it = formula.begin(); it != formula.end(); it++)
	{
		if (isupper(*it) && (std::find(setPropositions.begin(), setPropositions.end(), *it) == setPropositions.end()))
		{
			setPropositions.push_back(*it);
			numProposition++; //set a limit.
		}
	}
	return( numProposition);
}

std::string	logicAND(std::string	bit1, std::string	bit2)
{
	return(bit2 + bit1 + "&");
}

std::string	logicOR(std::string	bit1, std::string	bit2)
{
	return(bit2 + bit1 + "|");
}

std::string	logicXOR(std::string	bit1, std::string	bit2)
{
	return(readySetBool::negation_formal_norm(bit1 + bit2 + "!&" + bit1 + "!" + bit2 + "&|")); //TODO Lo mismo que el conditional
}

std::string	logicConditional(std::string	bit1, std::string	bit2)
{
	return(readySetBool::negation_formal_norm(bit2 + "!" + bit1 + "|")); //TODO No sé por que lo vuelvo a mandar a negation_formal_norm
}

std::string	logicBiconditional(std::string	bit1, std::string	bit2)
{
	return(readySetBool::negation_formal_norm(bit2 + bit1 + ">" + bit1 + bit2 + ">" + "&"));
}

std::map<std::string, std::string(*)(std::string, std::string)>	initializeNegationFormalNormMap(void)
{
	std::map<std::string, std::string(*)(std::string, std::string)> negationFormalNormMap;

	negationFormalNormMap["&"] = &logicAND;
	negationFormalNormMap["|"] = &logicOR;
	negationFormalNormMap["^"] = &logicXOR;
	negationFormalNormMap[">"] = &logicConditional;
	negationFormalNormMap["="] = &logicBiconditional;
	return (negationFormalNormMap);
}

void	binary_proposition_operation(std::stack<std::string>	&formulaStack, std::map<std::string, std::string(*)(std::string, std::string)> &negationFormalNormMap, char	operation)
{
	std::string	bit1;
	std::string	bit2;

	if (formulaStack.size() < 2)
		throw readySetBool::InvalidInputException();
	bit1 = formulaStack.top();
	formulaStack.pop();
	bit2 = formulaStack.top();
	formulaStack.pop();
	formulaStack.push(negationFormalNormMap.at(std::string(1, operation))(bit1, bit2));
	return ;

}

std::string readySetBool::de_morgan_laws(char op, int position, std::string formula, std::map<std::string, std::string(*)(std::string, std::string)> &negationFormalNormMap)
{
	std::stack<std::string> formulaStack;
	std::string	tmp1;
	std::string	tmp2;
	for (int i = 0; i < position; i++)
	{
		if (isupper(formula[i]))
		{
			formulaStack.push(std::string(&formula[i], 1));
		}
		else if (formula[i] != '!')
		{
			binary_proposition_operation(formulaStack, negationFormalNormMap, formula[i]);
		}
		else if (formula[i] == '!')
		{
			tmp1 = formulaStack.top();
			formulaStack.pop();
			if (tmp1[tmp1.size() - 1] == '!') //Double negation
				tmp1.erase(tmp1.size() - 1);
			else //Add negation
				tmp1 += '!';
			formulaStack.push(negation_formal_norm(tmp1));
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
	static std::map<std::string, std::string(*)(std::string, std::string)> negationFormalNormMap = initializeNegationFormalNormMap();

	if (formula.size() <= 2)
		return (formula);
	for (int i = 0; i < (int)formula.size(); i++)
	{
		if (isupper(formula[i]))
		{
			formulaStack.push(std::string(&formula[i], 1));
		}
		else if (formula[i] != '!')
		{
			binary_proposition_operation(formulaStack, negationFormalNormMap, formula[i]);
		}
		else if (formula[i] == '!')
		{
			tmp1 = formulaStack.top();
			formulaStack.pop();
			if (tmp1[tmp1.size() - 1] == '!') //Double negation
				tmp1.erase(tmp1.size() - 1);
			else //Add negation
				tmp1 += '!';
			//De Morgan laws
			if (tmp1.size() > 2 && tmp1[tmp1.size() - 2] == '|')
			{
				tmp1 = de_morgan_laws('|', (int)(tmp1.size() - 2), tmp1, negationFormalNormMap);
			}
			else if (tmp1.size() > 2 && tmp1[tmp1.size() - 2] == '&')
			{
				tmp1 = de_morgan_laws('&', (int)(tmp1.size() - 2), tmp1, negationFormalNormMap);
			}
			formulaStack.push(negation_formal_norm(tmp1));
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
	numProposition = countPropositions(formula, setPropositions);
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
	int	permutation;
	int indexArray[128] = {};

	numProposition = countPropositions2(formula, indexArray);
	permutation = 0;
	while (permutation < (1 << numProposition))
	{
		if (readySetBool::optimized_eval_formula(formula, numProposition,  indexArray, permutation) == true)
			return (true);
		permutation++;
	}
	return (false);
}