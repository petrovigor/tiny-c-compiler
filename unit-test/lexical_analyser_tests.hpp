#pragma once

#include <unordered_map>
#include <string>

#include <lexical_analyser.hpp>

static std::unordered_map<std::string, std::vector<LexicalToken>> lexical_analyser_test_cases
{
	{
		"int i = 0;",
		{
			{ LexicalTokenType::Name, "int" },
			{ LexicalTokenType::Name, "i" },
			{ LexicalTokenType::Operator, "=" },
			{ LexicalTokenType::Number, "0" },
			{ LexicalTokenType::Operator, ";" }
		}
	},

	{
		"+- /0123 ;",
		{
			{ LexicalTokenType::Operator, "+" },
			{ LexicalTokenType::Operator, "-" },
			{ LexicalTokenType::Operator, "/" },
			{ LexicalTokenType::Number, "123" },
			{ LexicalTokenType::Operator, ";" }
		}
	},

	{
		"0000 0 0001 0000001000",
		{
			{ LexicalTokenType::Number, "0" },
			{ LexicalTokenType::Number, "0" },
			{ LexicalTokenType::Number, "1" },
			{ LexicalTokenType::Number, "1000" },
		}
	},

	{
		"abc_abc_abc+aa+bb*cc+-=",
		{
			{ LexicalTokenType::Name, "abc_abc_abc" },
			{ LexicalTokenType::Operator, "+" },
			{ LexicalTokenType::Name, "aa" },
			{ LexicalTokenType::Operator, "+" },
			{ LexicalTokenType::Name, "bb" },
			{ LexicalTokenType::Operator, "*" },
			{ LexicalTokenType::Name, "cc" },
			{ LexicalTokenType::Operator, "+" },
			{ LexicalTokenType::Operator, "-" },
			{ LexicalTokenType::Operator, "=" }
		}
	},

	{
		"int a=12;//this is comment\nint c=0;",
		{
			{ LexicalTokenType::Name, "int" },
			{ LexicalTokenType::Name, "a" },
			{ LexicalTokenType::Operator, "=" },
			{ LexicalTokenType::Number, "12" },
			{ LexicalTokenType::Operator, ";" },
			{ LexicalTokenType::Name, "int" },
			{ LexicalTokenType::Name, "c" },
			{ LexicalTokenType::Operator, "=" },
			{ LexicalTokenType::Number, "0" },
			{ LexicalTokenType::Operator, ";" }
		}
	}
};
