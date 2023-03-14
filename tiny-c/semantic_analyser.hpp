#if 0

#pragma once

#include <vector>
#include <string>

static const std::vector<std::string> keywords_type_names
{
	"void", "int"
};

static const std::vector<std::string> keywords_operator_names
{
	"return"
};

enum class SemanticTokenType : uint8_t
{
	name,
	variable_type,
	variable_declaration_empty,
	variable_declaration,
	function_declaration,
	function_end,
	function_arguments_expression_declaration,
	function_call,
	expression,
	oper
};

struct SemanticToken
{
	SemanticTokenType type;
	std::string data;
	std::vector<SemanticToken> expression; //only for sem_type::expression
	std::vector<std::pair<std::string, std::string>> func_args;
	bool b_deleted;

};

#endif //0
