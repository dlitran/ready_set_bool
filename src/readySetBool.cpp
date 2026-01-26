#include "../inc/readySetBool.hpp"

const char *readySetBool::InvalidInputException::what() const throw()
{
	return("Error: Invalid input.");
}

