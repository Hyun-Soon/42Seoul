#pragma once
# include "Weapon.hpp"

class	HumanB {
	public:
		HumanB();
		HumanB(std::string name);
		~HumanB();
		void	setWeapon(Weapon &weapon);
		void	attack();

	private:
		std::string	_name;
		Weapon		*_weapon;
};