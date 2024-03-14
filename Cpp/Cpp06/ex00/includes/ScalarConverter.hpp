#pragma once

#include <iostream>
#include <limits>
#include <sstream>

class ScalarConverter
{
private:
	enum TYPE
	{
		ERROR, PSEUDOLITERAL, CHAR, INT, FLOAT, DOUBLE,
	};

	ScalarConverter();
	ScalarConverter(ScalarConverter& other);
	ScalarConverter& operator= (ScalarConverter& other);
	~ScalarConverter();
	static int checkType(std::string& inp);
	static void printError(std::string& inp);
	static void printDouble(double& inp);
	static void printFloat(double& inp);
	static void printInt(double& inp);
	static void printChar(char& inp);

public:
	static void convert(std::string inp);
};
