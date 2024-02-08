#pragma once
# include "Weapon.hpp"

class	HumanA {
	public:
		HumanA(std::string name, Weapon &weapon);
		~HumanA();
		void	attack();

	private:
		HumanA();
		std::string	_name;
		Weapon		&_weapon;
		static Weapon	_defaultWeapon;
};