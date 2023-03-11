#include <unordered_map>
#include <map>
#include <iostream>
#include <string>
#include <vector>

using namespace std;


//todo:
// parse: "x = mul(abc, bbb);"
// parse: "calc(1,2,3)"
// parse: "(a + b)" or "(a)-(b)-(c)-(d)" now: "a + b" and "a-b-c-d"

const string program =
R"lc(


int mul(int zxc, int ijk)
{
  int c = ((100 - ((100 * (2390))))) * (123/ -231 );
	return zxc - ijk + c;
}

void foo()
{
  int x = 3;
  int Baxc = 4;
	int abc = A * B - 430;

	call_external_api();


	x = x + multiple_call(abc(1,2,3,c()), doit(30, -x));

  int bbb = abc * a * b * c * d * e * f * g * h      * i              ;
  x = x * mul(abc, bbb);

	flush(-1500);

}

int main()
{
	int i = 23 * (-7 / 1 -140) - 40;
	int nAMe = 30123;
	nAMe = nAMe - 4431;

	return i + calc(0, 1, 2, nAMe);
}


)lc";

const std::vector<string> keywords_type_names
{
	"void", "int"//, "bool"
};
const std::vector<string> keywords_operator_names
{
	"return"
};

enum class token_type
{
	name,
	number,
	op_or_bracket
};

struct token
{
	string data;
	token_type type;
};

enum class sem_type
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

struct semantic_table
{
	sem_type type;
	string data;
	vector<semantic_table> expression; //only for sem_type::expression
	vector<std::pair<string,string>> func_args;
	bool b_deleted;

};

//struct semantic_in_code
//{
//	//int idxFrom; //[
//	//int idxTo;  //)
//	sem_type type;
//	string data;
//};

vector<std::string> global_scope_functions;
//vector<std::string> global_scope_variables;

unordered_map<std::string, std::vector<std::string>> local_variables_in_functions;

int main()
{
	vector<token> v;

	int count = 0;
	int last = 0;
	int n = program.size();
	token_type tt = token_type::name;

	cout << "lexical parsing started\n\n" << std::endl;
	for(int i = 0; i < n; ++i)
	{
		token after;
		bool flush = false;
		char c = program[i];
		int next_count = 0;
		if(c == ' ' || c == '\n' || c == '\t')
		{
			flush=true;
		}
		else if((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z') || (c >= '0' && c <= '9') || c == '_')
		{
			if(count == 0)
			{
				if((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z') || c == '_')
				{
					tt = token_type::name;
				}
				else if(c >= '0' && c <= '9')
				{
					tt = token_type::number;
				}
				else
				{
					return 1;
				}
			}
			count += 1;
		}
		else if(c == '{' || c == '}' || c == '*' || c == '/' || c == ';' || c == '=' ||
			c == '+' || c == '-' || c == '(' || c == ')' || c == ',') //|| c == '\"'
		{
			after = token{ std::string{c}, token_type::op_or_bracket };
			//v.emplace_back(
			flush = true;
		}
		else
		{
			return 2;
		}
		if(i + 1 == n)
		{
			flush = true;
		}
		if(flush)
		{
			if(count)
			{
				v.emplace_back(program.substr(last, count), tt);
				count = 0;
			}
			last = i + 1;
			if(!after.data.empty())
			{
				v.push_back(after);
			}
		}
	}

	std::cout << "lexical tokens found:\n\n" << std::endl;
	{
		int c = 0;
		for(auto i : v)
		{
			c += 1;
			std::string txt;
			if(i.type == token_type::name) txt ="name";
			if(i.type == token_type::number) txt ="number";
			if(i.type == token_type::op_or_bracket) txt ="op_or_bracket";
			std::cout << "[" << c << "] = \"" << i.data << "\" (" << txt << ")" << std::endl;
		}
	}

	std::cout << "lexical -> semantic convertation started:\n\n" << std::endl;

	// name 'return' -> operator return
	// name 'int' -> typename int




	std::vector<semantic_table> semanticc;
	bool expression_started = false;//coubld be expression like: 'a*b-c/(c-d)' or 'int a, bool b, float c, bool a, int d' in func args
	vector<semantic_table> temp_expression;
	std::vector<std::pair<string,string>> func_args;
	std::vector<string> argu_traits;

	std::string last_scope = "::";

	int expression_type; //0 = 'a*b-c/(c-d)'
											 //1 = 'int a, bool b, float c, bool a, int d'

	for(auto &toks : v)
	{
		if(expression_started)
		{
			if(toks.type == token_type::op_or_bracket && (expression_type==0 && toks.data == ";" ) || (expression_type==1 && toks.data == ")"))
			{
				if(expression_type==0)
				{

					//if(semanticc.size() >= 2 && semanticc[semanticc.size() - 1].type == sem_type::name && semanticc[semanticc.size() - 2].type == sem_type::variable_type)
					//{

					//	semanticc[ semanticc.size() - 2].b_deleted = true;
					//	semanticc[ semanticc.size() - 1].b_deleted = true;
					//	semanticc.push_back({  sem_type::variable_declaration, semanticc[ semanticc.size() - 1].data, temp_expression, { {"var_type", semanticc[ semanticc.size() - 2].data} }, false /* deleted */  });
					//}
					//else if(semanticc.size() >= 1 && semanticc[semanticc.size() - 1].type == sem_type::oper && semanticc[semanticc.size() - 1].data == "return")
					//{

					//	//semanticc[ semanticc.size() - 2].b_deleted = true;
					//	semanticc[ semanticc.size() - 1].b_deleted = true;
					//	semanticc.push_back({  sem_type::oper, "return", temp_expression, {}, false /* deleted */  });
					//}
					//else
					//{
					semanticc.push_back({  sem_type::expression, "", temp_expression, {} });
					//}



				}
				else
				{

					if(semanticc.size() >= 2 && semanticc[ semanticc.size() - 1].type == sem_type::name && semanticc[ semanticc.size() - 2].type == sem_type::variable_type)
					{
						semanticc[ semanticc.size() - 2].b_deleted = true;
						semanticc[ semanticc.size() - 1].b_deleted = true;
						semantic_table return_val {  sem_type::variable_type, semanticc[ semanticc.size() - 2].data, {}, {}  };
						semanticc.push_back({  sem_type::function_declaration, semanticc[ semanticc.size() - 1].data, {return_val}, func_args, false /* deleted */ });

						local_variables_in_functions[last_scope].push_back(semanticc[ semanticc.size() - 1].data);

						last_scope = semanticc[ semanticc.size() - 1].data;

					}
					else if(semanticc.size() >= 1 && semanticc[ semanticc.size() - 1].type == sem_type::name)
					{
						semanticc[ semanticc.size() - 1].b_deleted = true;
						//semantic_table return_val {  sem_type::variable_type, semanticc[ semanticc.size() - 2].data, {}, {}  };
						//semanticc.push_back({  sem_type::function_declaration, semanticc[ semanticc.size() - 1].data, {return_val}, func_args, false /* deleted */ });

						//local_variables_in_functions[last_scope].push_back(semanticc[ semanticc.size() - 1].data);

						//last_scope = semanticc[ semanticc.size() - 1].data;


						semanticc.push_back({  sem_type::function_call, semanticc[ semanticc.size() - 1].data, {}, func_args, false /* deleted */ });

					}
					else
					{


						semanticc.push_back({  sem_type::function_arguments_expression_declaration, "", {}, func_args, false /* deleted */ });
					}

				}
				expression_started = false;
				temp_expression.clear();
				func_args.clear();
			}
			else
			{
#if 0
				//todo: '+', '*', '(' in the row = compilation error
				//      'a', 'b', 'c' in the row = compilation error
				//      '(', '-', 'c' is not an error
				if(temp_expression.size())
				{
					sem_type last_sem = temp_expression[temp_expression.size() - 1].type;
					if((last_sem ==sem_type::name && token_type::name == toks.type) ||
						(last_sem ==sem_type::oper && token_type::op_or_bracket == toks.type))
					{
						std::cerr << "Compilation error: two operators in the row or two names in the row in the expression" << std::endl;
						return 2;
					}
				}
#endif //0

				if(toks.type == token_type::name || toks.type == token_type::number ||
					(toks.type == token_type::op_or_bracket && (toks.data=="*"||toks.data=="/"||toks.data=="-"||toks.data=="+")))
				{
					if(expression_type == 0)
					{
						temp_expression.push_back({  toks.type == token_type::name ? sem_type::name : sem_type::oper, toks.data, {}  });
					}
					else
					{
						if(toks.type == token_type::name)
						{

							argu_traits.push_back(toks.data);
							if(argu_traits.size() == 2)
							{

								if(std::find(keywords_type_names.begin(), keywords_type_names.end(), argu_traits[0]) == keywords_type_names.end())
								{
									std::cerr << "Unknown argument variable type: \"" << argu_traits[0] << "\"" << std::endl;
									return 4;
								}


								func_args.push_back( { argu_traits[0], argu_traits[1]  } );
								argu_traits.clear();
							}


						}
					}
				}
			}

		}
		// x + multiple_call(abc(1,2,3,c()), doit(30, -x)) - 100
		else if(toks.type == token_type::op_or_bracket && (toks.data == "=" || toks.data == "return" || toks.data == "("))
		{
			if(toks.data=="(")
			{
				expression_type=1;
			}
			else
			{
				expression_type=0;
			}
			expression_started = true;
			temp_expression.clear();
			func_args.clear();
			continue;
		}
		else if(toks.type == token_type::name)
		{

			//std::string altered_data = toks.data;
			bool bDone = false;
			for(int i = 0; i < keywords_type_names.size(); ++i)
			{
				if(toks.data == keywords_type_names[i])
				{
					//altered_data = keywords_type_names[i];

					local_variables_in_functions[last_scope].push_back(keywords_type_names[i]);
					semanticc.push_back({ sem_type::variable_type, keywords_type_names[i], {}, {}, false /* deleted */ });
					bDone = true;
					break;
				}
			}
			for(int i = 0; i < keywords_operator_names.size(); ++i)
			{
				if(toks.data == keywords_operator_names[i])
				{
					semanticc.push_back({ sem_type::oper, keywords_operator_names[i], {}, {}, false /* deleted */ });
					if(keywords_operator_names[i] == "return")
					{
						expression_started = true;
						expression_type = 0;
					}
					bDone = true;
					break;
				}
			}
			if(!bDone){
				semanticc.push_back({  sem_type::name, toks.data, {}, {}, false /* deleted */ });
				local_variables_in_functions[last_scope].push_back(toks.data);
			}
		}
		else
		{
			semanticc.push_back({  sem_type::oper, toks.data, {}, {}, false /* deleted */ });
			//std::cerr << "Unexpected token (unhandled)" << std::endl;
			//return 4;
		}
	}
	if(expression_started)
	{
		std::cerr << "Operator ';' expected at the end of expression" << std::endl;
		return 3;
	}


	std::cout << "first level semantic parsed:\n\n" << std::endl;
	{
		int c = 0;
		for(auto &s: semanticc)
		{
			if(s.b_deleted)
				continue;

			c += 1;
			std::cout << "[" << c << "] ";

			if(s.type == sem_type::function_declaration)
			{
				std::cout << "\n\nfunction " << (s.data) << "(";
				if(!s.func_args.empty())
				{
					int d = 0;
					for(auto &arg : s.func_args)
					{
						std::cout << arg.first << " " << arg.second;
						if(d + 1 != s.func_args.size())
						{
							std::cout << ", ";
						}
						d += 1;
					}
				}
				std::cout << ") -> " << (s.expression.size() ? s.expression[0].data : " void") << std::endl;
				continue;
			}


			if(s.type == sem_type::variable_declaration)
			{
				std::cout << "variable " << (!s.func_args.empty() ? s.func_args[0].second : "undefined") << " " << (s.data) << "= ";
				for(auto &z : s.expression)
				{
					std::cout << "\"" << z.data << "\", ";
				}
				std::cout << std::endl;
				continue;
			}

			if(s.type == sem_type::oper)
			{
				std::cout << "oper " << s.data << " ";
				if(!s.expression.empty())
				{
					for(auto &z : s.expression)
					{
						std::cout << "\"" << z.data << "\", ";
					}
				}
				std::cout << std::endl;
				continue;
			}

			if(s.type == sem_type::function_call)
			{
				std::cout << "function_call " << s.data << " (";
				if(!s.expression.empty())
				{
					for(auto &z : s.expression)
					{
						std::cout << "\"" << z.data << "\", ";
					}
				}
				std::cout << ")" << std::endl;
				continue;
			}

			if(s.expression.empty())
			{
				std::cout << s.data << " ";
				if(s.type == sem_type::name) std::cout << "name";
				else if(s.type == sem_type::function_end) std::cout << "function_end";
				//else if(s.type == sem_type::oper) std::cout << "oper";
				//else if(s.type == sem_type::variable_declaration) std::cout << "variable_declaration";
				else if(s.type == sem_type::variable_declaration_empty) std::cout << "variable_declaration_empty";
				else if(s.type == sem_type::function_arguments_expression_declaration) { std::cout << "function_arguments: ";     }
				else if(s.type == sem_type::function_call) std::cout << "function_call: ";
				else if(s.type == sem_type::variable_type) std::cout << "variable_type";
			}
			else
			{
				for(auto &z : s.expression)
				{
					std::cout << "\"" << z.data << "\", (expression)";
				}
			}
			if(!s.func_args.empty())
			{
				int d = 0;
				for(auto &arg : s.func_args)
				{
					std::cout << "[" << arg.first << " " << arg.second << "]";
					if(d + 1 != s.func_args.size())
					{
						std::cout << ", ";
					}
					d += 1;
				}
			}
			std::cout << std::endl;
		}
	}

	for(auto f : global_scope_functions)
	{
		std::cout << "Function found \"" << f << "\"" << std::endl;
	}

	for(auto f : local_variables_in_functions)
	{
		std::cout << "In function \"" << f.first << "\" variables:\"" << std::endl;
		for(auto i : f.second)
		{
			std::cout << "\t" << i << std::endl;
		}
		std::cout << std::endl;
	}


#if 0

	std::vector<    std::pair<std::vector<semantic_table>, sem_type>     > all_sems
	{
		{  {  {sem_type::variable_type, ""}, {sem_type::name, ""}, {sem_type::oper, "{"}  },  sem_type::function_declaration  },
		{  {  {sem_type::variable_type, ""}, {sem_type::name, ""}, {sem_type::oper, ";"}  },  sem_type::variable_declaration_empty  },
		{  {  {sem_type::variable_type, ""}, {sem_type::name, ""}, {sem_type::oper, "="}, {sem_type::expression, ""}  },  sem_type::variable_declaration  },
		{  {  {sem_type::oper, "return"}, {sem_type::expression, ""}, {sem_type::oper, "}"} },  sem_type::function_end  }
	};

	int token_cur_idx = 0;
	for(int i = 0; i < v.size(); ++i)
	{
		auto & cur_token = v[i];

		for(int j = 0; j < all_sems.size(); ++j)
		{
			//if(cur_token.type == all_sems[j].second)
			//{

			//}
		}
	}
#endif //0

	return 0;
}
