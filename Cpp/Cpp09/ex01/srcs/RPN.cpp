#include "RPN.hpp"

RPN::RPN() {}

RPN::RPN(const RPN &other) : _stk(other._stk)
{}

RPN RPN::operator=(const RPN &other)
{
	if (this != &other)
		_stk = other._stk;

	return *this;
}

RPN::~RPN() {}

void RPN::calculate(std::string expression)
{
	std::string temp;

	if (expression.length() == 0)
	{
		std::cout << "Error" << std::endl;
		return ;
	}

	for (size_t i = 0; i < expression.length(); i++)
	{
		if (expression[i] >= '0' && expression[i] <= '9')
			temp += expression[i];
		else if (_stk.size() >= 2 && (expression[i] == '+' || expression[i] == '-' || expression[i] == '*' || expression[i] == '/'))
		{
			if (arithmetic(expression[i]))
				return ;
		}
		else if (expression[i] == ' ')
		{
			if (temp.length())
			{
				_stk.push(strtod(temp.c_str(), NULL));
				temp = "";
			}
		}
		else
		{
			std::cout << "Error" << std::endl;
			return ;
		}
	}

	size_t stkSize = _stk.size();
	if (stkSize == 1 && temp == "")
		std::cout << _stk.top() << std::endl;
	else
		std::cout << "Error" << std::endl;
	
	while (stkSize--)
		_stk.pop();
}

int RPN::arithmetic(char oper)
{
	int operand1;
	int operand2;
	int ret;


	operand2 = _stk.top();
	_stk.pop();
	operand1 = _stk.top();
	_stk.pop();

	if (oper == '+')
		ret = operand1 + operand2;
	else if (oper == '-')
		ret = operand1 - operand2;
	else if (oper == '*')
		ret = operand1 * operand2;
	else
	{
		if (operand2 == 0)
		{
			std::cout << "Error: divided by zero" << std::endl;
			return 1;
		}
		ret = operand1 / operand2;
	}
	
	_stk.push(ret);
	return 0;
}
