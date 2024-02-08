#include <iostream>

class ClapTrap
{
	public:
		ClapTrap();
		ClapTrap(std::string name);
		ClapTrap(ClapTrap& other);
		ClapTrap& operator= (const ClapTrap& other);
		~ClapTrap();
		void	attack(const std::string& target);
		void	takeDamage(unsigned int amount);
		void	beRepaired(unsigned int amount);
		int		getAttackDamage() const;
		std::string	getName() const;
		void	powerUp(unsigned int amount);

	private:
		std::string	_name;
		int			_hitPoint;
		int			_energyPoint;
		int			_attackDamage;
};

