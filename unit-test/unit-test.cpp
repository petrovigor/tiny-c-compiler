#include <lexical_analyser.hpp>
#include <unordered_map>
#include <iostream>

#include "lexical_analyser_tests.hpp"

std::unordered_map<std::string, std::vector<LexicalToken>> all_test_cases;


void add_test_case(const std::string &source, const std::vector<LexicalToken> &expected)
{
	all_test_cases[source] = expected;
}


bool launch_all_tests()
{
	int i = 0;
	int passed = 0;
	for(auto &t : all_test_cases)
	{
		auto test_result = LexicalParse(t.first);
		if(test_result == t.second)
		{
			passed += 1;
		}
		else
		{
			std::cout << "=========================================================================================" << std::endl;
			std::cout << "LexicalParse(" << t.first << ") returned:\n";
			int j = 0;
			for(auto &l : test_result)
			{
				std::cout << l;
				if(j + 1 != test_result.size())
				{
					std::cout << ", ";
				}
				j += 1;
			}
			std::cout << std::endl;

			std::cout << "Expected: " << std::endl;
			j = 0;
			for(auto &l : t.second)
			{
				std::cout << l;
				if(j + 1 != t.second.size())
				{
					std::cout << ", ";
				}
				j += 1;
			}
			std::cout << std::endl << std::endl;
			std::cout << "=========================================================================================" << std::endl;
		}
		i += 1;
	}
	if(i == passed)
	{
		std::cout << "ALL TESTS PASSED!" << std::endl;
	}
	else
	{
		std::cout << "\n\nPASSED " << passed << " of " << i << std::endl;
	}

	return i == passed;
}


int main()
{
	for(const auto &it : lexical_analyser_test_cases)
	{
		add_test_case(it.first, it.second);
	}

	launch_all_tests();
	return 0;
}
