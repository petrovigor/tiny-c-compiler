#include "lexical_analyser.hpp"
#include "logger.h"

std::vector<LexicalToken> LexicalParse(const std::string &source)
{
	std::vector<LexicalToken> v;

	int count = 0;
	int last = 0;
	int n = source.size();
	LexicalTokenType tt = LexicalTokenType::Name;

#if 0
	DEBUG << "lexical parsing started\n\n" << std::endl;
#endif //0

	bool commentStarted = false;

	for(int i = 0; i < n; ++i)
	{
		LexicalToken after;
		bool flush = false;
		char c = source[i];
		int next_count = 0;
		if(c == ' ' || c == '\n' || c == '\t')
		{
			if(c == '\n')
			{
				commentStarted=false;
			}
			flush=true;


		}
		else if((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z') || (c >= '0' && c <= '9') || c == '_')
		{
			if(commentStarted)
			{
				continue;
			}
			if(count == 0)
			{
				if((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z') || c == '_')
				{
					tt = LexicalTokenType::Name;
				}
				else if(c >= '0' && c <= '9')
				{
					tt = LexicalTokenType::Number;
				}
				else
				{
					const std::string error = "Lexical token 'name' can't start with symbol: " + c;
					throw std::runtime_error(error);
				}
			}
			count += 1;
		}
		else if(c == '{' || c == '}' || c == '*' || c == '/' || c == ';' || c == '=' ||
						c == '+' || c == '-' || c == '(' || c == ')' || c == ',')
		{
			if(commentStarted)
			{
				continue;
			}
			if(c == '/' && (i + 1) < n && source[i + 1] == '/')
			{
				flush = true;
				commentStarted = true;
				i += 1;
				continue;
			}

			after = LexicalToken{ LexicalTokenType::Operator, std::string{c} };
			flush = true;
		}
		else
		{
			const std::string error = "Unexpected symbol: " + c;
			throw std::runtime_error(error);
		}
		if(i + 1 == n)
		{
			flush = true;
		}
		if(flush)
		{
			if(count)
			{
				if(tt == LexicalTokenType::Number)
				{
					//delete leading zeroes for numbers, but leave one '0'
					// 000001 -> 1
					// 00000 -> 0
					// 0000000100000 -> 100000
					// 1000000100000 -> 1000000100000
					int cc = last;
					int zeroes = 0;
					int digits_total = count;
					while(cc < last + count && source[cc] == '0')
					{
						zeroes += 1;
						cc += 1;
					}
					if(zeroes == digits_total)
					{
						//std::cout << "only zeroes! returns \"0\"" << std::endl;
						v.push_back(LexicalToken{ LexicalTokenType::Number, "0" });
					}
					else
					{
						//std::cout << "ZEROES: " << zeroes << " in: " << source.substr(last, count) << std::endl;
						v.push_back(LexicalToken{ LexicalTokenType::Number, source.substr(last+zeroes, count-zeroes) });
					}
					//int offset = digits_total - zeroes;
					//if(offset == 0)
					//	offset = 1;
					//if(zeroes == 1)
					//	zeroes = 0;
				}
				else
				{
					v.push_back(LexicalToken{ tt, source.substr(last, count) });
				}
				count = 0;
			}
			last = i + 1;
			if(!after.data.empty())
			{
				v.push_back(after);
			}
		}
	}

#if 0
	DEBUG << "lexical tokens found:\n\n" << std::endl;
	{
		int c = 0;
		for(auto i : v)
		{
			c += 1;
			std::string txt;
			if(i.type == LexicalTokenType::Name) txt ="name";
			if(i.type == LexicalTokenType::Number) txt ="number";
			if(i.type == LexicalTokenType::Operator) txt ="op_or_bracket";
			DEBUG << "[" << c << "] = \"" << i.data << "\" (" << txt << ")" << std::endl;
		}
	}
#endif //0

	return v;
}
