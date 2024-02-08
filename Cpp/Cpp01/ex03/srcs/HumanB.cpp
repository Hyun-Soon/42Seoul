#include "HumanB.hpp"

HumanB::HumanB() {
	_name = "";
	_weapon = NULL;
}

HumanB::HumanB(std::string name) : _name(name), _weapon(NULL) {
	std::cout << "HumanB \"" << _name << "\" constructor is called." << std::endl;
}

HumanB::~HumanB() {
	std::cout << "HumanB \"" << _name << "\" destructor called." << std::endl;
}

void	HumanB::setWeapon(Weapon &weapon) {
	_weapon = &weapon;
}

void	HumanB::attack()
{
	if (_weapon == NULL)
	{
		std::cout << "there's no weapon." << std::endl;
		return ;
	}
	std::cout << _name << " attacks with their " << _weapon->getType() << std::endl;
}