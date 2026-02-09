#include "../inc/readySetBoole.hpp"

const char *readySetBool::InvalidInputException::what() const throw()
{
	return("Error: Invalid input.");
}

