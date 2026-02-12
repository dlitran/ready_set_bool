#include "../inc/readySetBoole.hpp"

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

void	create_global_set(std::vector<std::vector<int>> &sets, std::vector<int> &globalSet)
{
	for (std::vector<std::vector<int>>::iterator it1 = sets.begin(); it1 != sets.end(); it1++)
	{
		for (std::vector<int>::iterator it2 = (*it1).begin(); it2 != (*it1).end(); it2++)
		{
			if (std::find(globalSet.begin(),globalSet.end(), *it2) == globalSet.end())
				globalSet.push_back(*it2);
		}
	}
	// for (std::set<int>::iterator it = globalSet.begin(); it != globalSet.end(); it++)
	// {
	// 	std::cout << *it << std::endl;
	// }
}

std::vector<int>	logicAND(std::vector<int>	tmp1, std::vector<int>	tmp2, std::vector<int>	globalSet)
{
	std::vector<int>	tmpSet;

	(void)globalSet;
	tmpSet = {};
	for (std::vector<int>::iterator it2 = tmp1.begin(); it2 != tmp1.end(); it2++)
	{
		if (std::find(tmp2.begin(), tmp2.end(), *it2) != tmp2.end())
		{
			tmpSet.push_back(*it2);
		}
	}
	return(tmpSet);
}

std::vector<int>	logicOR(std::vector<int>	tmp1, std::vector<int>	tmp2, std::vector<int>	globalSet)
{
	std::vector<int> tmpSet;

	(void)globalSet;
	tmpSet = tmp1;
	for (std::vector<int>::iterator it2 = tmp2.begin(); it2 != tmp2.end(); it2++)
	{
		if (std::find(tmpSet.begin(), tmpSet.end(), *it2) == tmpSet.end())
		{
			tmpSet.push_back(*it2);
		}
	}
	return(tmpSet);
}

std::vector<int>	logicXOR(std::vector<int>	tmp1, std::vector<int>	tmp2, std::vector<int>	globalSet)
{
	std::vector<int>	tmpSet;
	
	(void)globalSet;
	tmpSet = tmp1;
	for (std::vector<int>::iterator it2 = tmp2.begin(); it2 != tmp2.end(); it2++)
	{
		if (std::find(tmpSet.begin(), tmpSet.end(), *it2) == tmpSet.end())
		{
			tmpSet.push_back(*it2);
		}
		else
		{
			tmpSet.erase(std::find(tmpSet.begin(), tmpSet.end(), *it2));
		}
	}
	return(tmpSet);
}

std::vector<int>	logicConditional(std::vector<int>	tmp1, std::vector<int>	tmp2, std::vector<int>	globalSet)
{
	std::vector<int>	tmpSet;

	tmpSet = globalSet;
	for (std::vector<int>::iterator it2 = globalSet.begin(); it2 != globalSet.end(); it2++)
	{
		if (std::find(tmp2.begin(), tmp2.end(), *it2) != tmp2.end() && std::find(tmp1.begin(), tmp1.end(), *it2) == tmp1.end())
		{
			tmpSet.erase(std::find(tmpSet.begin(), tmpSet.end(), *it2));
		}
	}
	return(tmpSet);
}

std::vector<int>	logicBiconditional(std::vector<int>	tmp1, std::vector<int>	tmp2,  std::vector<int>	globalSet)
{
	std::vector<int>	tmpSet;
	
	(void)globalSet;
	tmpSet = {};
	for (std::vector<int>::iterator it2 = globalSet.begin(); it2 != globalSet.end(); it2++)
	{
		if (std::find(tmp2.begin(), tmp2.end(), *it2) != tmp2.end() && std::find(tmp1.begin(), tmp1.end(), *it2) != tmp1.end())
		{
			tmpSet.push_back(*it2);
		}
		else if (std::find(tmp2.begin(), tmp2.end(), *it2) == tmp2.end() && std::find(tmp1.begin(), tmp1.end(), *it2) == tmp1.end())
		{
			tmpSet.push_back(*it2);
		}
	}
	return(tmpSet);
}

std::map<std::string, std::vector<int>(*)(std::vector<int>, std::vector<int>, std::vector<int>)>	initializeSetOperationMap(void)
{
	std::map<std::string, std::vector<int>(*)(std::vector<int>, std::vector<int>, std::vector<int>)> setOperationMap;
	setOperationMap["&"] = &logicAND;
	setOperationMap["|"] = &logicOR;
	setOperationMap["^"] = &logicXOR;
	setOperationMap[">"] = &logicConditional;
	setOperationMap["="] = &logicBiconditional;
	return (setOperationMap);
}

void	set_logic(std::stack<std::vector<int>> &setStack, std::map<std::string, std::vector<int>(*)(std::vector<int>, std::vector<int>, std::vector<int>)> &setOperationMap, char operation, std::vector<int>	&globalSet)
{
	std::vector<int> tmpSet;
	std::vector<int> tmp1;
	std::vector<int> tmp2;

	if (operation == '!')
	{
		if (setStack.size() < 1)
			throw readySetBool::InvalidInputException();
		tmp1 = setStack.top();
		setStack.pop();
		tmpSet = globalSet;
		for (std::vector<int>::iterator it2 = tmp1.begin(); it2 != tmp1.end(); it2++)
		{
			if (std::find(tmpSet.begin(), tmpSet.end(), *it2) != tmpSet.end())
				tmpSet.erase(std::find(tmpSet.begin(), tmpSet.end(), *it2));
		}
		setStack.push(tmpSet);
	}
	else 
	{
		if (setStack.size() < 2)
			throw readySetBool::InvalidInputException();
		tmp1 = setStack.top();
		setStack.pop();
		tmp2 = setStack.top();
		setStack.pop();
		setStack.push(setOperationMap.at(std::string(1, operation))(tmp1, tmp2, globalSet));
	}
}

std::vector<int> readySetBool::eval_set(std::string &formula, std::vector<std::vector<int>> sets)
{
	std::vector<int> globalSet;
	std::map<std::string, std::vector<int>(*)(std::vector<int>, std::vector<int>, std::vector<int>)> setOperationMap;
	std::vector<char> setPropositions;
	std::stack<std::vector<int>> setStack;


	setOperationMap = initializeSetOperationMap();
	create_global_set(sets,globalSet);
	readySetBool::countPropositions(formula, setPropositions);

	for (std::string::iterator it = formula.begin(); it != formula.end(); it++)
	{
		// if (*it != '!' && *it != '|' && *it != '&' && *it != '>' && *it != '=' && *it != '^')
		// 	setStack.push(*it);
		if (std::isupper(*it))
		{
			int position = (int)(std::find(setPropositions.begin(), setPropositions.end(), *it) - setPropositions.begin());
			setStack.push(sets[position]);
			//std::cout << "position: " << position << std::endl;
		}
		else
			set_logic(setStack, setOperationMap, *it, globalSet);
	}
	//print_truth_table(formula);
	if (setStack.size() != 1)
		throw readySetBool::InvalidInputException();
	return(setStack.top());
}