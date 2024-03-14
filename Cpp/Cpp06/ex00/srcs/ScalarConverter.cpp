#include "ScalarConverter.hpp"

ScalarConverter::ScalarConverter() {}

ScalarConverter::ScalarConverter(ScalarConverter& other) {(void)other;}

ScalarConverter& ScalarConverter::operator= (ScalarConverter& other) {(void)other; return *this;}

ScalarConverter::~ScalarConverter() {}

int ScalarConverter::checkType(std::string& inp)
{
	if (inp.length() > 1)
	{
		if (inp == "inf" || inp == "-inf" || inp == "+inf" || inp == "nan" )
			return DOUBLE;
		else if (inp == "inff" || inp == "-inff" || inp == "+inff" || inp == "nanf")
			return FLOAT;
		else if (inp == ".f")
			return ERROR;
		
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
		return DOUBLE;
	}
	else if (inp.length() == 1)
	{
		if (inp[0] >= '0' && inp[0] <= '9')
			return INT;
		return CHAR;
	}
	return ERROR;
}

void ScalarConverter::printError(std::string& inp)
{
	std::cout << inp << " is wrong input. Input another one." << std::endl;
}

void ScalarConverter::printDouble(double& doubleVal)
{
	int intVal = static_cast<int>(doubleVal);
	char charVal = static_cast<char>(doubleVal);
	float floatVal = static_cast<float>(doubleVal);
	bool intFlag = (doubleVal - intVal) ? false : true;
	std::stringstream ss;

	if (intFlag == false
		|| doubleVal < 0.0
		|| doubleVal > 127.0)
		ss << "char : impossible\n";
	else if (intVal < 32 || intVal == 127)
		ss << "char : Non displayable\n";
	else
		ss << "char : '" << charVal << "'\n";

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

void ScalarConverter::printFloat(double& inp)
{
	float floatVal = static_cast<float>(inp);
	int intVal = static_cast<int>(floatVal);
	char charVal = static_cast<char>(floatVal);
	double doubleVal = static_cast<double>(floatVal);
	bool intFlag = (floatVal - intVal) ? false : true;
	std::stringstream ss;

	if (intFlag == false
		|| floatVal < CHAR_MIN
		|| floatVal > CHAR_MAX)
		ss << "char : impossible\n";
	else if (intVal < 32 || intVal == 127)
		ss << "char : Non displayable\n";
	else
		ss << "char : '" << charVal << "'\n";

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

void ScalarConverter::printInt(double& inp)
{
	int intVal = static_cast<int>(inp);
	float floatVal = static_cast<float>(intVal);
	char charVal = static_cast<char>(intVal);
	double doubleVal = static_cast<double>(intVal);
	std::stringstream ss;

	if (inp < INT32_MIN || inp > INT32_MAX)
	{
		ss	<< "char : impossible\n"
			<< "int : impossible\n"
			<< "float : impossible\n"
			<< "double : impossible";
	}
	else
	{
		if (inp < CHAR_MIN || inp > CHAR_MAX)
			ss << "char : impossible\n";
		else if (inp < 32 || inp == 127)
			ss << "char : Non displayable\n";
		else
			ss << "char : '" << charVal << "'\n";

		ss	<< "int : " << intVal << "\n"
			<< "float : " << floatVal << ".0f\n"
			<< "double : " << doubleVal << ".0";
	}

	std::cout << ss.str() << std::endl;
}

void ScalarConverter::printChar(char& charVal)
{
	int intVal = static_cast<int>(charVal);
	float floatVal = static_cast<float>(charVal);
	double doubleVal = static_cast<double>(charVal);
	std::stringstream ss;

	if (charVal < 32 || charVal == 127)
		ss << "char : Non displayable\n";
	else
		ss << "char : '" << charVal << "'\n";

	ss	<< "int : " << intVal << "\n"
		<< "float : " << floatVal << ".0f\n"
		<< "double : " << doubleVal << ".0";

	std::cout << ss.str() << std::endl;
}

void ScalarConverter::convert(std::string inp)
{
	int type = checkType(inp);
	double doubleInp = strtod(inp.c_str(), NULL);

	if (type == ERROR)
		printError(inp);
	else if (type == DOUBLE)
		printDouble(doubleInp);
	else if (type == FLOAT)
		printFloat(doubleInp);
	else if (type == INT)
		printInt(doubleInp);
	else
		printChar(inp[0]);
}
