#pragma once

# include <iostream>
#define RED "\033[1;31m"
#define YELLOW "\033[1;33m"
#define RESET "\033[0;0m"
class ClapTrap
{
	public:
		ClapTrap();
		ClapTrap(std::string name);
		ClapTrap(ClapTrap& other);
		ClapTrap& operator= (const ClapTrap& other);
		~ClapTrap();
		virtual void	attack(const std::string& target);
		void	takeDamage(unsigned int amount);
		void	beRepaired(unsigned int amount);
		int		getHitPoint() const;
		int		getEnergyPoint() const;
		int		getAttackDamage() const;
		const std::string&	getName() const;
		void	powerUp(unsigned int amount);

	protected:
		std::string	_name;
		int			_hitPoint;
		int			_energyPoint;
		int			_attackDamage;
};

