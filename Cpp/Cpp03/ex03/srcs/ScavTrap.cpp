#include "ScavTrap.hpp"

ScavTrap::ScavTrap() : ClapTrap()
{
	_hitPoint = 100;
	_energyPoint = 50;
	_attackDamage = 20;
	std::cout << "ScavTrap default constructor called." << std::endl;
}

ScavTrap::ScavTrap(std::string _name) : ClapTrap(_name)
{
	_hitPoint = 100;
	_energyPoint = 50;
	_attackDamage = 20;
	std::cout << "ScavTrap name constructor called." << std::endl;
}

ScavTrap::ScavTrap(const ScavTrap &other) : ClapTrap(other._name)
{
	_hitPoint = other._hitPoint;
	_energyPoint = other._energyPoint;
	_attackDamage = other._attackDamage;
	std::cout << "ScavTrap copy constructor called." << std::endl;
}

ScavTrap& ScavTrap::operator= (const ScavTrap& other)
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

ScavTrap::~ScavTrap()
{
	std::cout << "ScavTrap Destructor called." << std::endl;
}

void	ScavTrap::guardGate()
{
	if (_energyPoint > 0 && _hitPoint > 0)
	{
		_energyPoint--;
		std::cout << "ScavTrap " << _name << " is now in Gatekeeper mode." << std::endl;
	}
}

void ScavTrap::attack(const std::string &target)
{
	if (_hitPoint > 0 && _energyPoint > 0)
	{
		_energyPoint--;
		std::cout << "ScavTrap " << _name << " attacks " << target << ", causing " << _attackDamage << " points of damage" << std::endl;
	}
}