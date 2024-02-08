#include "DiamondTrap.hpp"

DiamondTrap::DiamondTrap() : ClapTrap("_clap_name"), ScavTrap(), FragTrap()
{
	_energyPoint = 50;
	std::cout << "Diamond default constructor called." << std::endl;
}

DiamondTrap::DiamondTrap(std::string name) : ClapTrap(name + "_clap_name"), ScavTrap(), FragTrap(),
	_name(name)
{
	_energyPoint = 50;
	std::cout << "Diamond name constructor called." << std::endl;
}

DiamondTrap::DiamondTrap(const DiamondTrap &other) : ClapTrap(other._name), ScavTrap(other._name), FragTrap(other._name)
{
	_hitPoint = other._hitPoint;
	_energyPoint = other._energyPoint;
	_attackDamage = other._attackDamage;
	std::cout << "DiamondTrap copy constructor called." << std::endl;
}

DiamondTrap& DiamondTrap::operator= (const DiamondTrap& other)
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

DiamondTrap::~DiamondTrap()
{
	std::cout << "Diamond Destructor called." << std::endl;
}

void	DiamondTrap::whoAmI()
{
	if (_hitPoint > 0 && _energyPoint > 0)
	{
		_energyPoint--;
		std::cout << RED << "DiamondTrap name : " << _name << RESET << std::endl;
		std::cout << YELLOW << "ClapTrap name : " << ClapTrap::_name << RESET << std::endl;
	}
}

const std::string& DiamondTrap::getName() const
{
	return (_name);
}

void	DiamondTrap::attack(const std::string& target)
{
	if (_hitPoint > 0 && _energyPoint > 0)
	{
		_energyPoint--;
		std::cout << "DiamondTrap " << _name << " attacks " << target << ", causing " << _attackDamage << " points of damage" << std::endl;
	}
}