#pragma once

#include <string>
#include <vector>
#include <ostream>

enum class LexicalTokenType : uint8_t
{
	Name, Number, Operator
};

struct LexicalToken
{
	LexicalTokenType	type;
	std::string				data;
};

static bool operator==(const LexicalToken &lhs, const LexicalToken &rhs)
{
	return lhs.data == rhs.data && lhs.type == rhs.type;
}

std::vector<LexicalToken> LexicalParse(const std::string &source);

static std::ostream& operator<<(std::ostream &strm, LexicalToken &token)
{
	std::string token_type_name;
	switch(token.type)
	{
	case LexicalTokenType::Name:			token_type_name = "name";			break;
	case LexicalTokenType::Number:		token_type_name = "number";		break;
	case LexicalTokenType::Operator:	token_type_name = "operator";	break;
	}

	return strm << token_type_name << " : " << token.data;
}
