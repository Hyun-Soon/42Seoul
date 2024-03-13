#include "ScalarConverter.hpp"

std::string& ltrim(std::string& s)
{
	s.erase(0, s.find_first_not_of("0"));
	return s; //TODO :: here
}

int ScalarConverter::checkType(std::string& inp)
{
	if (inp == "inf" || inp == "inff"
		|| inp == "-inf" || inp == "+inf"
		|| inp == "-inff" || inp == "+inff"
		|| inp == "nan" || inp == "nanf")
		return PSEUDOLITERAL;
	else if (inp.length() > 1)
	{
		int cnt = 0;
		for (size_t i = 0; i < inp.length(); i++)
		{
			if (inp[i] == '.' && cnt == 0)
				++cnt;
			else if (inp[i] == 'f' && i == inp.length() - 1)
				return FLOAT;
			else if (inp[i] < '0' || inp[i] > '9')
				return ERROR;
		}
		if (cnt == 0)
			return INT;
		else
			return DOUBLE;
	}
	else if (inp.length() == 1)
	{
		if (inp[0] >= '0' && inp[0] <= '9')
			return INT;
		else
			return CHAR;
	}
	return ERROR;
}

void ScalarConverter::printError(std::string& inp)
{
	std::cout << inp << " is wrong input. Input another one." << std::endl;
}

void ScalarConverter::printPseudoLiteral(std::string& inp)
{
	std::cout	<< "char : impossible\n"
				<< "int : impossible\n"
				<< "float : " << inp << "\n"
				<< "double : " << inp
				<< std::endl;
}

void ScalarConverter::printDouble(std::string& inp)
{
	double doubleVal = strtod(inp.c_str(), NULL);
	int intVal = static_cast<int>(doubleVal);
	char charVal = static_cast<char>(doubleVal);
	float floatVal = static_cast<float>(doubleVal);
	bool intFlag = (doubleVal - intVal) ? false : true;
	std::stringstream ss;

	if (doubleVal == INFINITY || doubleVal == -INFINITY
		|| intFlag == false
		|| doubleVal < 0.0
		|| doubleVal > 127.0)
		ss << "char : impossible\n";
	else if (intVal < 32 || intVal == 127)
		ss << "char : Non displayable\n";
	else
		ss << "char : " << charVal << "\n";

	if (doubleVal < INT32_MIN || doubleVal > INT32_MAX)
		ss << "int : impossible\n";
	else
		ss << "int : " << intVal << "\n";
	
	if (doubleVal < std::numeric_limits<float>::min() || doubleVal > std::numeric_limits<float>::max())
		ss << "float : impossible\n";
	else
		ss << "float : " << floatVal;
	
	if (intFlag)
		ss << ".0";
	ss << "f\n";
	
	ss << "double : " << doubleVal;
	if (intFlag)
		ss << ".0";
	std::cout << ss.str() << std::endl;
}

void ScalarConverter::printFloat(std::string& inp)
{
	float floatVal = strtof(inp.c_str(), NULL);
	int intVal = static_cast<int>(floatVal);
	char charVal = static_cast<char>(floatVal);
	double doubleVal = static_cast<double>(floatVal);
	bool intFlag = (floatVal - intVal) ? false : true;
	std::stringstream ss;

	if (floatVal == INFINITY || floatVal == -INFINITY
		|| intFlag == false
		|| floatVal < 0.0
		|| floatVal > 127.0)
		ss << "char : impossible\n";
	else if (intVal < 32 || intVal == 127)
		ss << "char : Non displayable\n";
	else
		ss << "char : " << charVal << "\n";

	if (floatVal < INT32_MIN || floatVal > INT32_MAX)
		ss << "int : impossible\n";
	else
		ss << "int : " << intVal << "\n";
	
	ss << "float : " << floatVal;
	if (intFlag)
		ss << ".0";
	ss << "f\n";

	ss << "double : " << doubleVal;
	if (intFlag)
		ss << ".0";

	std::cout << ss.str() << std::endl;
}

void ScalarConverter::printInt(std::string& inp)
{
	int intVal = atoi(inp.c_str());
	float floatVal = static_cast<float>(intVal);
	char charVal = static_cast<char>(intVal);
	double doubleVal = static_cast<double>(intVal);
	std::stringstream ss;

	if (intVal < CHAR_MIN || intVal > CHAR_MAX)
		ss << "char : impossible\n";
	else if (intVal < 32 || intVal == 127)
		ss << "char : Non displayable\n";
	else
		ss << "char : " << charVal << "\n";

	if (floatVal < INT32_MIN || floatVal > INT32_MAX)
		ss << "int : impossible\n";
	else
		ss << "int : " << intVal << "\n";
	
	ss << "float : " << floatVal;
	if (intFlag)
		ss << ".0";
	ss << "f\n";

	ss << "double : " << doubleVal;
	if (intFlag)
		ss << ".0";

	std::cout << ss.str() << std::endl;
}

void ScalarConverter::convert(std::string inp)
{
	int type = checkType(inp);

	if (type == ERROR)
		printError(inp);
	else if (type == PSEUDOLITERAL)
		printPseudoLiteral(inp);
	else if (type == DOUBLE)
		printDouble(inp);
	else if (type == FLOAT)
		printFloat(inp);
	else if (type == INT)
		printInt(inp);
	//else
	//	printChar(inp);

	//std::stringstream ss(inp);

	//char d;
	//ss >> d;
	//std::cout << d << std::endl;
	//ss.clear();
	//ss.seekg(0);
	//float a;
	//ss >> a;
	//std::cout << a << std::endl;
	//ss.clear();
	//ss.seekg(0);
	//int b;
	//ss >> b;
	//std::cout << b << std::endl;
	//ss.clear();
	//ss.seekg(0);
	//double c;
	//ss >> c;
	//std::cout << c << std::endl;
	//ss.clear();
	//ss.seekg(0);
}
