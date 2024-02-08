#include "HumanA.hpp"

Weapon	HumanA::_defaultWeapon("default");

HumanA::HumanA() : _name(""), _weapon(_defaultWeapon) {}

HumanA::HumanA(std::string name, Weapon &weapon) : _name(name), _weapon(weapon) {
	std::cout << "HumanA \"" << _name << "\" constructor is called." << std::endl;
}

HumanA::~HumanA() {
	std::cout << "HumanA \"" << _name << "\" destructor executed." << std::endl;
}

void	HumanA::attack()
{
	std::cout << _name << " attacks with their " << _weapon.getType() << std::endl;
}
