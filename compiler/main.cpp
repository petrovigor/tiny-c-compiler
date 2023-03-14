#include <iostream>

#include <lexical_analyser.hpp>

int main(int argc, char **argv)
{
	if(argc != 3)
	{
		std::cerr << "Usage: compiler <INPUT_SOURCE_CODE_FILE> <OUTPUT_MACHINE_CODE_FILE>" << std::endl;
		return 1;
	}



	return 0;
}
