#include "../inc/readySetBoole.hpp"

const char *readySetBoole::InvalidInputException::what() const throw()
{
	return("Error: Invalid input.");
}

