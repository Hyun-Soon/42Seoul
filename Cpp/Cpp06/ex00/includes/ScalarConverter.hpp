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
	~ScalarConverter();
	static std::string& ltrim(std::string& s);
	static int checkType(std::string& inp);
	static void printError(std::string& inp);
	static void printPseudoLiteral(std::string& inp);
	static void printDouble(std::string& inp);
	static void printFloat(std::string& inp);
	static void printInt(std::string& inp);
	static void printChar(std::string& inp);

public:
	static void convert(std::string inp);
};
