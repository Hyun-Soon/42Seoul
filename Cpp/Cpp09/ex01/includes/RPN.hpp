#pragma once

#include <stack>
#include <iostream>

class RPN
{
	private:
		std::stack<int> _stk;

	public:
		RPN();
		RPN(const RPN& other);
		RPN operator=(const RPN& other);
		~RPN();
		void calculate(std::string expression);
		int arithmetic(char oper);
};