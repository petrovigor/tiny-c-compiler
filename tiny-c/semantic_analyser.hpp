#pragma once

#include <vector>
#include <string>
#include <unordered_map>

enum class data_type : uint8_t
{
	void_t,
	int_t
};

enum class operator_type : uint8_t
{
	return_t,
	open_parenthess,
	close_parenthess,
	comma,
	open_body,
	close_body,
	assign,
	plus,
	minus,
	multiply,
	division,
	unary_minus,
	unary_plus
};

static const std::vector<std::pair<std::string, data_type>> keywords_type_names
{
	{ "void", data_type::void_t },
	{ "int",  data_type::int_t  }
};

//keep priority groups order
static const std::vector<std::tuple<std::string, operator_type, int>> keywords_operator_names
{
	//groups from left to right order
	{ "-", operator_type::unary_minus, 1 },
	{ "+", operator_type::unary_plus,  1 },
	{ "*", operator_type::multiply, 2 },
	{ "/", operator_type::division, 2 },
	{ "+", operator_type::plus, 3 },
	{ "-", operator_type::minus, 3 },
	{ "=", operator_type::assign, 4 },

	//priority-independent operators
	{ "return", operator_type::return_t, 0 },
	{ "(", operator_type::open_parenthess, 0 },
	{ ")", operator_type::close_parenthess, 0 },
	{ ",", operator_type::comma, 0 },
	{ "{", operator_type::open_body, 0 },
	{ "}", operator_type::close_body, 0 }
};

enum class SemanticTokenType : uint8_t
{
	name,
	variable_type,
	variable_declaration_empty, //todo: delete
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
	//bool b_deleted; //todo: удалить на уровне алгоритма, а не этой структуры

};


struct Function
{
	std::string name;
	std::string ret_type;
	std::vector<std::pair<std::string, std::string>> args;
	std::vector<local_variable> local_vars;
	std::vector<expression> expressions;
};


struct SemanticPattern
{
	std::vector<SemanticToken> tokens;
};

//алгоритм следующий:
//
// проходимся по лексическим токенам, и ищем ранее заданные секвенции
// добавляем каждый последующий токен в стек.
//
//
//
//

//var_type('int'), name('mul'), op('('), var_type('int'), name('zxc'), comma(), var_type('int'), name('ijk'), op(')')
//
//var_type('int'), name('x'), op('='), val('3'), op(';')
//op('return'), name('zxc'), op('-'), name('ijk'), op('+'), name('c'), op(';')
//
//const std::string program =
//R"lc(
//
//
//int mul(int zxc, int ijk)
//{
//  int x = 3;
//  int c = ((100 - ((100 * (2390))))) * (123/ -231 );
//  c = 100 - foo(c, 2 * x);
//	return zxc - ijk + c;
//}
//
//void foo()
//{
//  int x = 3;
//  int Baxc = 4;
//	int abc = A * B - 430;
//
//	call_external_api();
//
//
//	x = x + multiple_call(abc(1,2,3,c()), doit(30, -x));
//
//  int bbb = abc * a * b * c * d * e * f * g * h      * i              ;
//  x = x * mul(abc, bbb);
//
//	flush(-1500);
//
//}
//
//int main()
//{
//	int i = 23 * (-7 / 1 -140) - 40;
//	int nAMe = 30123;
//	nAMe = nAMe - 4431;
//
//	return i + calc(0, 1, 2, nAMe);
//}
//
//
//)lc";
//





