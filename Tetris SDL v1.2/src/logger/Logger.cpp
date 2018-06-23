


#include "../../include/logger/Logger.h"

#include <iostream>
#include <fstream>


void Logger::print(std::string text)
{
	std::ofstream outfile("___DEBUG__LOG.txt");
	outfile << text.c_str() << std::endl;
	outfile.close();
}
