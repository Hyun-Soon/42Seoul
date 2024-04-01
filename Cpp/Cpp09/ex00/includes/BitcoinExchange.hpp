#pragma once

#include <fstream>
#include <map>
#include <iostream>
#include <string>
#include <sstream>
#include <cstdio>

typedef std::map<std::string, float>::iterator mpit;

class BitcoinExchange
{
	private:
		std::map<std::string, float> _mp;

		BitcoinExchange(const BitcoinExchange& other);
		BitcoinExchange& operator=(const BitcoinExchange& other);
		void	getData();
		float	findExchangeRate(std::string inputKey);
		bool	isValidDate(std::string inputKey) const;
		bool	isValidCnt(std::string inputCnt) const;

	public:
		BitcoinExchange();
		~BitcoinExchange();
		void printResult(std::string inputFilename);
};