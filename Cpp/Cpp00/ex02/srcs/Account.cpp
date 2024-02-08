#include "../headers/Account.hpp"
#include <iostream>
#include <iomanip>
#include <ctime>
#include <sstream>

int	Account::_nbAccounts;
int	Account::_totalAmount;
int	Account::_totalNbDeposits;
int	Account::_totalNbWithdrawals;

Account::Account( int initial_deposit )
{
	_accountIndex = _nbAccounts;
	_amount = initial_deposit;
	_totalAmount += initial_deposit;
	_displayTimestamp();
	std::cout << "index:" << _nbAccounts++
				<< ";amount:" << initial_deposit
				<< ";created" << std::endl;
}

void	Account::_displayTimestamp( void )
{
	std::time_t currentTime = std::time(nullptr);
    struct std::tm* timeInfo = std::localtime(&currentTime);
    std::stringstream timestampStream;
    timestampStream << "[" << std::put_time(timeInfo, "%Y%m%d_%H%M%S") << "]";
	std::cout << timestampStream.str() << " ";
}

void	Account::displayAccountsInfos( void )
{
	_displayTimestamp();

	std::cout << "accounts:" << _nbAccounts
				<< ";total:" << _totalAmount
				<< ";deposits:" << _totalNbDeposits
				<< ";withdrawals:" << _totalNbWithdrawals << std::endl;
}

void	Account::displayStatus( void ) const
{
	_displayTimestamp();

	std::cout << "index:" << _accountIndex
				<< ";amount:" << _amount
				<< ";deposits:" << _nbDeposits
				<< ";withdrawals:" << _nbWithdrawals << std::endl;
}

void	Account::makeDeposit( int deposit )
{
	_displayTimestamp();

	std::cout << "index:" << _accountIndex
				<< ";p_amount:" << _amount
				<< ";deposit:" << deposit
				<< ";amount:" << _amount + deposit
				<< ";nb_deposits:" << ++_nbDeposits << std::endl;
	
	_amount += deposit;
	_totalAmount += deposit;
	++_totalNbDeposits;
}

bool	Account::makeWithdrawal( int withdrawal )
{
	_displayTimestamp();

	std::cout << "index:" << _accountIndex
				<< ";p_amount:" << _amount;
	if (_amount - withdrawal > 0)
	{
		std::cout << ";withdrawal:" << withdrawal
					<< ";amount:" << _amount - withdrawal
					<< ";nb_withdrawals:" << ++_nbWithdrawals << std::endl;
		_amount -= withdrawal;
		_totalAmount -= withdrawal;
		++_totalNbWithdrawals;
		return (true);
	}
	else
	{
		std::cout << ";withdrawal:refused" << std::endl;
		return (false);
	}
}

Account::~Account( void )
{
	_displayTimestamp();

	std::cout << "index:" << _accountIndex
				<< ";amount:" << _amount
				<< ";closed" << std::endl;
}

int	Account::getNbAccounts( void )
{
	return (_nbAccounts);
}

int	Account::getTotalAmount( void )
{
	return (_totalAmount);
}

int	Account::getNbDeposits( void )
{
	return (_totalNbDeposits);
}

int	Account::getNbWithdrawals( void )
{
	return (_totalNbWithdrawals);
}

int	Account::checkAmount( void ) const
{
	return (_amount);
}