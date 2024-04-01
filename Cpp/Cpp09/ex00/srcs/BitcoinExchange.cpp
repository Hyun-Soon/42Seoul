#include "BitcoinExchange.hpp"

BitcoinExchange::BitcoinExchange()
{
	getData();
}

BitcoinExchange::BitcoinExchange(const BitcoinExchange &other) : _mp(other._mp) {}

BitcoinExchange &BitcoinExchange::operator=(const BitcoinExchange &other)
{
	if (this != &other)
		_mp = other._mp;
	
	return *this;
}

BitcoinExchange::~BitcoinExchange() {}

bool BitcoinExchange::isValidDate(std::string inputKey) const
{
	int year;
	int month;
	int day;

	if (std::sscanf(inputKey.c_str(), "%d-%d-%d", &year, &month, &day) != 3)
		return false;
	else
	{
		if (day < 1)
			return false;
		if (month == 1 || month == 3 || month == 5 || month == 7 || month == 8 || month == 10 || month == 12)
		{
			if (day > 31)
				return false;
		}
		else
		{
			if (month == 2)
			{
				if (month % 4 == 0 && month % 100 != 0 && month % 400 == 0)
				{
					if (day > 29)
						return false;
				}
				else
				{
					if (day > 28)
						return false;
				}
			}
			else if (day > 30)
				return false;
		}
		return true;
	}
}

bool BitcoinExchange::isValidCnt(std::string inputCnt) const
{
	int pointCnt = 0;

	if (inputCnt == ".")
		return false;
	for (size_t i = 0; i < inputCnt.length(); i++)
	{
		if (inputCnt[i] == '.' && pointCnt == 0)
			++pointCnt;
		else if (!(inputCnt[i] >= '0' && inputCnt[i] <= '9'))
			return false;
	}
	return true;
}

void BitcoinExchange::getData()
{
	std::ifstream dFile;

	dFile.open("data.csv");
	if (dFile.is_open())
	{
		std::string line;

		getline(dFile, line);
		while (getline(dFile, line))
		{
			size_t commaPos = line.find(',');
			if (commaPos != std::string::npos)
			{
				std::string date = line.substr(0, commaPos);
				float exchangeRate = strtof(line.substr(commaPos + 1, line.length()).c_str(), NULL);
				
				_mp[date] = exchangeRate;

				////debug
				//std::cout << std::setprecision(8) << date << " " << exchangeRate << std::endl;
			}

		}
		dFile.close();
	}
	else
		std::cerr << "Error: Can't open data file.";
}

float BitcoinExchange::findExchangeRate(std::string inputKey)
{
	for (mpit it = _mp.begin(); it != _mp.end(); it++)
	{
		if (it->first == inputKey)
			return it->second;
		else if (it->first > inputKey)
		{
			if (it == _mp.begin())
				return -1.f;
			return (--it)->second;
		}
	}
	return -1.f;
}

void BitcoinExchange::printResult(std::string inputFilename)
{
	std::ifstream iFile;
	std::stringstream ss;

	iFile.open(inputFilename);
	if (iFile.is_open())
	{
		std::string line;

		getline(iFile, line);
		while (getline(iFile, line))
		{
			size_t vbPos = line.find(" | ");
			if (vbPos != std::string::npos)
			{
				std::string	inputDate = line.substr(0, vbPos);
				std::string strCnt = line.substr(vbPos + 3, line.length());
				float 		inputCnt = std::strtod(strCnt.c_str(), NULL);
				float exchangeRate = findExchangeRate(inputDate);

				if (isValidDate(inputDate) == false)
					ss << "Error: invalid date\n";
				else if (exchangeRate == -1.f || isValidCnt(strCnt) == false)
					ss << "Error: bad input => " << line << '\n';
				else if (inputCnt < 0)
					ss << "Error: not a positive number.\n";
				else if (inputCnt > 1000.f)
					ss << "Error: too large a number.\n";
				else
					ss << inputDate << " => " << inputCnt << " = " << inputCnt * exchangeRate << '\n';
			}
			else
				ss << "Error: bad input => " << line << '\n';
		}
		std::cout << ss.str() << std::endl;
		iFile.close();
	}
	else
		std::cerr << "Error: Can't open input file.";
}
