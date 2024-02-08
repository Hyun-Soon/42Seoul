#include "FragTrap.hpp"

FragTrap::FragTrap() : ClapTrap()
{
	_hitPoint = 100;
	_energyPoint = 100;
	_attackDamage = 30;
	std::cout << "FragTrap default constructor called." << std::endl;
}

FragTrap::FragTrap(std::string _name) : ClapTrap(_name)
{
	_hitPoint = 100;
	_energyPoint = 100;
	_attackDamage = 30;
	std::cout << "FragTrap name constructor called." << std::endl;
}

FragTrap::FragTrap(const FragTrap &other) : ClapTrap(other._name)
{
	_name = other._name;
	_hitPoint = other._hitPoint;
	_energyPoint = other._energyPoint;
	_attackDamage = other._attackDamage;
	std::cout << "FragTrap Copy constructor called." << std::endl;
}

FragTrap& FragTrap::operator= (const FragTrap& other)
{
	if (this != &other)
	{
		_name = other._name;
		_hitPoint = other._hitPoint;
		_energyPoint = other._energyPoint;
		_attackDamage = other._attackDamage;
	}
	return (*this);
}

FragTrap::~FragTrap()
{
	std::cout << "FragTrap Destructor called." << std::endl;
}

void	FragTrap::highFivesGuys()
{
	if (_hitPoint > 0 && _energyPoint > 0)
	{
		std::cout << "Let's high five!" << std::endl;
		_energyPoint--;
	}
}

void	FragTrap::attack(const std::string &target)
{
	if (_hitPoint > 0 && _energyPoint > 0)
	{
		_energyPoint--;
		std::cout << "FragTrap " << _name << " attacks " << target << ", causing " << _attackDamage << " points of damage" << std::endl;
	}
}