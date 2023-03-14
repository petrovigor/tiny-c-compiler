//#include <unordered_map>
//#include <map>
//#include <iostream>
//#include <string>
//#include <vector>
//
//#include "lexical_analyser.hpp"
//#include "logger.h"
//
//using namespace std;
//
//
////todo:
//// parse: "x = mul(abc, bbb);"
//// parse: "calc(1,2,3)"
//// parse: "(a + b)" or "(a)-(b)-(c)-(d)" now: "a + b" and "a-b-c-d"
//
//const string program =
//R"lc(
//
//
//int mul(int zxc, int ijk)
//{
//  int c = ((100 - ((100 * (2390))))) * (123/ -231 );
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
//
//
////enum class token_type
////{
////	name,
////	number,
////	op_or_bracket
////};
////
////struct token
////{
////	string data;
////	token_type type;
////};
//
//
//
////struct semantic_in_code
////{
////	//int idxFrom; //[
////	//int idxTo;  //)
////	sem_type type;
////	string data;
////};
//
//#if 0
//
//vector<std::string> global_scope_functions;
////vector<std::string> global_scope_variables;
//
//unordered_map<std::string, std::vector<std::string>> local_variables_in_functions;
//
//int main()
//{
//	auto lexical_tokens = LexicalParse(program);
//
//	DEBUG << "lexical -> semantic convertation started:\n\n" << std::endl;
//
//	// name 'return' -> operator return
//	// name 'int' -> typename int
//
//
//
//
//	std::vector<semantic_table> semanticc;
//	bool expression_started = false;//coubld be expression like: 'a*b-c/(c-d)' or 'int a, bool b, float c, bool a, int d' in func args
//	vector<semantic_table> temp_expression;
//	std::vector<std::pair<string,string>> func_args;
//	std::vector<string> argu_traits;
//
//	std::string last_scope = "::";
//
//	int expression_type; //0 = 'a*b-c/(c-d)'
//											 //1 = 'int a, bool b, float c, bool a, int d'
//
//	for(auto &toks : lexical_tokens)
//	{
//		if(expression_started)
//		{
//			if(toks.type == LexicalTokenType::Operator && (expression_type==0 && toks.data == ";" ) || (expression_type==1 && toks.data == ")"))
//			{
//				if(expression_type==0)
//				{
//
//					//if(semanticc.size() >= 2 && semanticc[semanticc.size() - 1].type == sem_type::name && semanticc[semanticc.size() - 2].type == sem_type::variable_type)
//					//{
//
//					//	semanticc[ semanticc.size() - 2].b_deleted = true;
//					//	semanticc[ semanticc.size() - 1].b_deleted = true;
//					//	semanticc.push_back({  sem_type::variable_declaration, semanticc[ semanticc.size() - 1].data, temp_expression, { {"var_type", semanticc[ semanticc.size() - 2].data} }, false /* deleted */  });
//					//}
//					//else if(semanticc.size() >= 1 && semanticc[semanticc.size() - 1].type == sem_type::oper && semanticc[semanticc.size() - 1].data == "return")
//					//{
//
//					//	//semanticc[ semanticc.size() - 2].b_deleted = true;
//					//	semanticc[ semanticc.size() - 1].b_deleted = true;
//					//	semanticc.push_back({  sem_type::oper, "return", temp_expression, {}, false /* deleted */  });
//					//}
//					//else
//					//{
//					semanticc.push_back({  sem_type::expression, "", temp_expression, {} });
//					//}
//
//
//
//				}
//				else
//				{
//
//					if(semanticc.size() >= 2 && semanticc[ semanticc.size() - 1].type == sem_type::name && semanticc[ semanticc.size() - 2].type == sem_type::variable_type)
//					{
//						semanticc[ semanticc.size() - 2].b_deleted = true;
//						semanticc[ semanticc.size() - 1].b_deleted = true;
//						semantic_table return_val {  sem_type::variable_type, semanticc[ semanticc.size() - 2].data, {}, {}  };
//						semanticc.push_back({  sem_type::function_declaration, semanticc[ semanticc.size() - 1].data, {return_val}, func_args, false /* deleted */ });
//
//						local_variables_in_functions[last_scope].push_back(semanticc[ semanticc.size() - 1].data);
//
//						last_scope = semanticc[ semanticc.size() - 1].data;
//
//					}
//					else if(semanticc.size() >= 1 && semanticc[ semanticc.size() - 1].type == sem_type::name)
//					{
//						semanticc[ semanticc.size() - 1].b_deleted = true;
//						//semantic_table return_val {  sem_type::variable_type, semanticc[ semanticc.size() - 2].data, {}, {}  };
//						//semanticc.push_back({  sem_type::function_declaration, semanticc[ semanticc.size() - 1].data, {return_val}, func_args, false /* deleted */ });
//
//						//local_variables_in_functions[last_scope].push_back(semanticc[ semanticc.size() - 1].data);
//
//						//last_scope = semanticc[ semanticc.size() - 1].data;
//
//
//						semanticc.push_back({  sem_type::function_call, semanticc[ semanticc.size() - 1].data, {}, func_args, false /* deleted */ });
//
//					}
//					else
//					{
//
//
//						semanticc.push_back({  sem_type::function_arguments_expression_declaration, "", {}, func_args, false /* deleted */ });
//					}
//
//				}
//				expression_started = false;
//				temp_expression.clear();
//				func_args.clear();
//			}
//			else
//			{
//#if 0
//				//todo: '+', '*', '(' in the row = compilation error
//				//      'a', 'b', 'c' in the row = compilation error
//				//      '(', '-', 'c' is not an error
//				if(temp_expression.size())
//				{
//					sem_type last_sem = temp_expression[temp_expression.size() - 1].type;
//					if((last_sem ==sem_type::name && token_type::name == toks.type) ||
//						(last_sem ==sem_type::oper && token_type::op_or_bracket == toks.type))
//					{
//						ERROR << "Compilation error: two operators in the row or two names in the row in the expression" << std::endl;
//						return 2;
//					}
//				}
//#endif //0
//
//				if(toks.type == LexicalTokenType::Name || toks.type == LexicalTokenType::Number ||
//					(toks.type == LexicalTokenType::Operator && (toks.data=="*"||toks.data=="/"||toks.data=="-"||toks.data=="+")))
//				{
//					if(expression_type == 0)
//					{
//						temp_expression.push_back({  toks.type == LexicalTokenType::Name ? sem_type::name : sem_type::oper, toks.data, {}  });
//					}
//					else
//					{
//						if(toks.type == LexicalTokenType::Name)
//						{
//
//							argu_traits.push_back(toks.data);
//							if(argu_traits.size() == 2)
//							{
//
//								if(std::find(keywords_type_names.begin(), keywords_type_names.end(), argu_traits[0]) == keywords_type_names.end())
//								{
//									ERROR << "Unknown argument variable type: \"" << argu_traits[0] << "\"" << std::endl;
//									return 4;
//								}
//
//
//								func_args.push_back( { argu_traits[0], argu_traits[1]  } );
//								argu_traits.clear();
//							}
//
//
//						}
//					}
//				}
//			}
//
//		}
//		// x + multiple_call(abc(1,2,3,c()), doit(30, -x)) - 100
//		else if(toks.type == LexicalTokenType::Operator && (toks.data == "=" || toks.data == "return" || toks.data == "("))
//		{
//			if(toks.data=="(")
//			{
//				expression_type=1;
//			}
//			else
//			{
//				expression_type=0;
//			}
//			expression_started = true;
//			temp_expression.clear();
//			func_args.clear();
//			continue;
//		}
//		else if(toks.type == LexicalTokenType::Name)
//		{
//
//			//std::string altered_data = toks.data;
//			bool bDone = false;
//			for(int i = 0; i < keywords_type_names.size(); ++i)
//			{
//				if(toks.data == keywords_type_names[i])
//				{
//					//altered_data = keywords_type_names[i];
//
//					local_variables_in_functions[last_scope].push_back(keywords_type_names[i]);
//					semanticc.push_back({ sem_type::variable_type, keywords_type_names[i], {}, {}, false /* deleted */ });
//					bDone = true;
//					break;
//				}
//			}
//			for(int i = 0; i < keywords_operator_names.size(); ++i)
//			{
//				if(toks.data == keywords_operator_names[i])
//				{
//					semanticc.push_back({ sem_type::oper, keywords_operator_names[i], {}, {}, false /* deleted */ });
//					if(keywords_operator_names[i] == "return")
//					{
//						expression_started = true;
//						expression_type = 0;
//					}
//					bDone = true;
//					break;
//				}
//			}
//			if(!bDone){
//				semanticc.push_back({  sem_type::name, toks.data, {}, {}, false /* deleted */ });
//				local_variables_in_functions[last_scope].push_back(toks.data);
//			}
//		}
//		else
//		{
//			semanticc.push_back({  sem_type::oper, toks.data, {}, {}, false /* deleted */ });
//			//ERROR << "Unexpected token (unhandled)" << std::endl;
//			//return 4;
//		}
//	}
//	if(expression_started)
//	{
//		ERROR << "Operator ';' expected at the end of expression" << std::endl;
//		return 3;
//	}
//
//
//	DEBUG << "first level semantic parsed:\n\n" << std::endl;
//	{
//		int c = 0;
//		for(auto &s: semanticc)
//		{
//			if(s.b_deleted)
//				continue;
//
//			c += 1;
//			DEBUG << "[" << c << "] ";
//
//			if(s.type == sem_type::function_declaration)
//			{
//				DEBUG << "\n\nfunction " << (s.data) << "(";
//				if(!s.func_args.empty())
//				{
//					int d = 0;
//					for(auto &arg : s.func_args)
//					{
//						DEBUG << arg.first << " " << arg.second;
//						if(d + 1 != s.func_args.size())
//						{
//							DEBUG << ", ";
//						}
//						d += 1;
//					}
//				}
//				DEBUG << ") -> " << (s.expression.size() ? s.expression[0].data : " void") << std::endl;
//				continue;
//			}
//
//
//			if(s.type == sem_type::variable_declaration)
//			{
//				DEBUG << "variable " << (!s.func_args.empty() ? s.func_args[0].second : "undefined") << " " << (s.data) << "= ";
//				for(auto &z : s.expression)
//				{
//					DEBUG << "\"" << z.data << "\", ";
//				}
//				DEBUG << std::endl;
//				continue;
//			}
//
//			if(s.type == sem_type::oper)
//			{
//				DEBUG << "oper " << s.data << " ";
//				if(!s.expression.empty())
//				{
//					for(auto &z : s.expression)
//					{
//						DEBUG << "\"" << z.data << "\", ";
//					}
//				}
//				DEBUG << std::endl;
//				continue;
//			}
//
//			if(s.type == sem_type::function_call)
//			{
//				DEBUG << "function_call " << s.data << " (";
//				if(!s.expression.empty())
//				{
//					for(auto &z : s.expression)
//					{
//						DEBUG << "\"" << z.data << "\", ";
//					}
//				}
//				DEBUG << ")" << std::endl;
//				continue;
//			}
//
//			if(s.expression.empty())
//			{
//				DEBUG << s.data << " ";
//				if(s.type == sem_type::name) DEBUG << "name";
//				else if(s.type == sem_type::function_end) DEBUG << "function_end";
//				//else if(s.type == sem_type::oper) DEBUG << "oper";
//				//else if(s.type == sem_type::variable_declaration) DEBUG << "variable_declaration";
//				else if(s.type == sem_type::variable_declaration_empty) DEBUG << "variable_declaration_empty";
//				else if(s.type == sem_type::function_arguments_expression_declaration) { DEBUG << "function_arguments: ";     }
//				else if(s.type == sem_type::function_call) DEBUG << "function_call: ";
//				else if(s.type == sem_type::variable_type) DEBUG << "variable_type";
//			}
//			else
//			{
//				for(auto &z : s.expression)
//				{
//					DEBUG << "\"" << z.data << "\", (expression)";
//				}
//			}
//			if(!s.func_args.empty())
//			{
//				int d = 0;
//				for(auto &arg : s.func_args)
//				{
//					DEBUG << "[" << arg.first << " " << arg.second << "]";
//					if(d + 1 != s.func_args.size())
//					{
//						DEBUG << ", ";
//					}
//					d += 1;
//				}
//			}
//			DEBUG << std::endl;
//		}
//	}
//
//	for(auto f : global_scope_functions)
//	{
//		DEBUG << "Function found \"" << f << "\"" << std::endl;
//	}
//
//	for(auto f : local_variables_in_functions)
//	{
//		DEBUG << "In function \"" << f.first << "\" variables:\"" << std::endl;
//		for(auto i : f.second)
//		{
//			DEBUG << "\t" << i << std::endl;
//		}
//		DEBUG << std::endl;
//	}
//
//
//#if 0
//
//	std::vector<    std::pair<std::vector<semantic_table>, sem_type>     > all_sems
//	{
//		{  {  {sem_type::variable_type, ""}, {sem_type::name, ""}, {sem_type::oper, "{"}  },  sem_type::function_declaration  },
//		{  {  {sem_type::variable_type, ""}, {sem_type::name, ""}, {sem_type::oper, ";"}  },  sem_type::variable_declaration_empty  },
//		{  {  {sem_type::variable_type, ""}, {sem_type::name, ""}, {sem_type::oper, "="}, {sem_type::expression, ""}  },  sem_type::variable_declaration  },
//		{  {  {sem_type::oper, "return"}, {sem_type::expression, ""}, {sem_type::oper, "}"} },  sem_type::function_end  }
//	};
//
//	int token_cur_idx = 0;
//	for(int i = 0; i < v.size(); ++i)
//	{
//		auto & cur_token = v[i];
//
//		for(int j = 0; j < all_sems.size(); ++j)
//		{
//			//if(cur_token.type == all_sems[j].second)
//			//{
//
//			//}
//		}
//	}
//#endif //0
//
//	return 0;
//}
//
//#endif //0
