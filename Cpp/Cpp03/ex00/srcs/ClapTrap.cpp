#include "ClapTrap.hpp"

ClapTrap::ClapTrap() : _name(""), _hitPoint(10), _energyPoint(10), _attackDamage(0)
{
	std::cout << "ClapTrap default constructor called." << std::endl;
}

ClapTrap::ClapTrap(std::string name) : _name(name), _hitPoint(10), _energyPoint(10), _attackDamage(0)
{
	std::cout << "ClapTrap name Constructor called." << std::endl;
}

ClapTrap::ClapTrap(ClapTrap& other) : _name(other._name), _hitPoint(other._hitPoint), _energyPoint(other._energyPoint), _attackDamage(other._attackDamage)
{
	std::cout << "ClapTrap Copy constructor called." << std::endl;
}


ClapTrap& ClapTrap::operator= (const ClapTrap& other)
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

ClapTrap::~ClapTrap()
{
	std::cout << "ClapTrap Destructor called." << std::endl;
}

void ClapTrap::attack(const std::string& target)
{
	if (_hitPoint > 0 && _energyPoint > 0)
	{
		_energyPoint--;
		std::cout << "ClapTrap " << _name << " attacks " << target << ", causing " << _attackDamage << " points of damage" << std::endl;
	}
}

void ClapTrap::takeDamage(unsigned int amount)
{
	if (_hitPoint > 0)
	{
		_hitPoint -= amount;
		std::cout << "ClapTrap " << _name << "'s energy point decreased to " << _hitPoint << std::endl;
		if (_hitPoint <= 0)
			std::cout << "ClapTrap " << _name << " died" << std::endl;
	}
}

void ClapTrap::beRepaired(unsigned int amount)
{
	if (_hitPoint > 0 && _energyPoint > 0)
	{
		_energyPoint--;
		_hitPoint += amount;
		std::cout << "ClapTrap " << _name << "'s hp restored to " << _hitPoint << std::endl;
	}
}

std::string	ClapTrap::getName() const
{
	return (_name);
}

int	ClapTrap::getAttackDamage() const
{
	return (_attackDamage);
}

void	ClapTrap::powerUp(unsigned int amount)
{
	if (_hitPoint > 0 && _energyPoint > 0)
	{
		_attackDamage += amount;
		std::cout << "ClapTrap " << _name << "'s attack damage increased to " << _attackDamage << std::endl;
	}
}