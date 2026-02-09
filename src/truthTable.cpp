#include "../inc/readySetBoole.hpp"

void	binary_bitwise_operation(std::stack<bool>	&bitStack, std::map<std::string, bool(*)(bool, bool)> &bitwiseOperationMap, char	operation)
{
	bool	bit1;
	bool	bit2;

	if (operation == '!')
	{
		if (bitStack.size() < 1)
			throw readySetBool::InvalidInputException();
		bit1 = bitStack.top();
		bitStack.pop();
		bitStack.push(!bit1);
		return ;
	}
	else
	{
		if (bitStack.size() < 2)
			throw readySetBool::InvalidInputException();
		bit1 = bitStack.top();
		bitStack.pop();
		bit2 = bitStack.top();
		bitStack.pop();
		bitStack.push(bitwiseOperationMap.at(std::string(1, operation))(bit1, bit2));
		return ;
	}
}

bool	logicAND(bool	bit1, bool	bit2)
{
	return(bit1 && bit2);
}

bool	logicOR(bool	bit1, bool	bit2)
{
	return(bit1 || bit2);
}

bool	logicXOR(bool	bit1, bool	bit2)
{
	return(bit1 ^ bit2);
}

bool	logicConditional(bool	bit1, bool	bit2)
{
	if (bit2 == true && bit1 == false)
		return(false);
	else
		return(true);
}

bool	logicBiconditional(bool	bit1, bool	bit2)
{
	return(!(bit1 ^ bit2));
}

void	initializeBitwiseOperationMap(std::map<std::string, bool(*)(bool, bool)> &bitwiseOperationMap)
{
	bitwiseOperationMap["&"] = &logicAND;
	bitwiseOperationMap["|"] = &logicOR;
	bitwiseOperationMap["^"] = &logicXOR;
	bitwiseOperationMap[">"] = &logicConditional;
	bitwiseOperationMap["="] = &logicBiconditional;
	return ;
}

bool readySetBool::eval_formula(std::string formula) //Add possibility of multiple equal letters.
{
	std::stack<bool> bitStack;
	std::map<std::string, bool(*)(bool, bool)> bitwiseOperationMap;

	initializeBitwiseOperationMap(bitwiseOperationMap);
	for (int it = 0; it < (int)formula.length(); it++)
	{
		if (formula[it] == '1')
			bitStack.push(true);
		else if (formula[it] == '0')
			bitStack.push(false);
		else
			binary_bitwise_operation(bitStack, bitwiseOperationMap, formula[it]);
	}
	if (bitStack.size() != 1)
		throw readySetBool::InvalidInputException();
	return (bitStack.top());
}

bool readySetBool::optimized_eval_formula(std::string formula, int numProposition,  int *indexArray, int	permutation) //Add possibility of multiple equal letters.
{
	std::stack<bool> bitStack;
	std::map<std::string, bool(*)(bool, bool)> bitwiseOperationMap;
	int	position;

	initializeBitwiseOperationMap(bitwiseOperationMap);
	for (int it = 0; it < (int)formula.length(); it++)
	{
		if (isupper(formula[it]))
		{
			position = numProposition - indexArray[(int)formula[it]];
			if (permutation & (1 << position))
				bitStack.push(true);
			else
				bitStack.push(false);
		}
		else
			binary_bitwise_operation(bitStack, bitwiseOperationMap, formula[it]);
	}
	if (bitStack.size() != 1)
		throw readySetBool::InvalidInputException();
	return (bitStack.top());
}

int	readySetBool::countPropositionsIndex(std::string formula, int *indexArray)
{
	int	numProposition;

	numProposition = 0;
	for (std::string::iterator it = formula.begin(); it != formula.end(); it++)
	{
		if (isupper(*it) && indexArray[(int)(*it)] == 0)
		{
            indexArray[(int)*it] = numProposition + 1;
			numProposition++;
		}
	}
	return( numProposition);
}

void	print_header(int    *indexArray, int numProposition)
{
	int	i;

	std::cout << "| ";
    for (int it1 = 1; it1 <= numProposition; it1++)
    {
	    for (int it2 = 0; it2 < 128; it2++)
        {
            if (indexArray[it2] == it1)
            {
                std::cout << (char)(indexArray + it2 - indexArray) << " | ";
                continue;
            }
        }
    }
	std::cout << "= |" << std::endl;
	i = 0;
	while (i < (numProposition + 1))
	{
		std::cout << "|---";
		i++;
	}
	std::cout << "|" << std::endl;
}

void	print_permutation(int	numProposition, int	permutation)
{
	int	it;

	it = numProposition -1;
	std::cout << "|";
	while (it >= 0)
	{
		if (permutation & (1 << it))
			std::cout << " 1";
		else
			std::cout << " 0";
		std::cout << " |";
		it--; //No sé por qué lo hice así, pero no lo voy a cambiar.
	}
}

//TODO: la truth table ahora mismo tiene una complejidad de 2^N * (N(std::find en el vector) * N(transformar formula) * L(eval_formula) + N(imprimir cosas))
//TODO: std::find en el vector -> std::find en un set. (quitaria la N)
//TODO: transformar la fórmula ->
void readySetBool::print_truth_table(std::string formula)
{
	int	numProposition;
	int	permutation;
    int indexArray[128] = {}; //Inicializa en 0. Contiene en las posiciones ascii determinadas el número del orden en el que aparecene en el header.
    //por ejemplo, para la fórmula AB&, el indexArray será: indexArray[65] = 1, indexArray[66] = 2. 
    // Así luego al evaluar la fórmula, cuando nos encontramos con la A accedemos rápido a su posición en el header O(1).
    //Es una mejora de eficiencia respecto al find O(N).

	numProposition = countPropositionsIndex(formula, indexArray); //Cuenta las proposiciones en la fórmula (sin repetición) y inicializa el indexArray.
	print_header(indexArray, numProposition);
	permutation = 0;
	while (permutation < (1 << numProposition)) //The power of two of numProposition -> i iterates 000, 001, 010, 011... up to 10000 (with as many 0 as propositions).
	{
		print_permutation(numProposition, permutation);
		std::cout << " " << readySetBool::optimized_eval_formula(formula, numProposition,  indexArray, permutation) << " |" << std::endl;
		permutation++;
	}
}
