#include "Weapon.hpp"

Weapon::Weapon(std::string type) {
	_type = type;
	
	std::cout << "Weapon \"" << _type << "\" constructor is called." << std::endl;
}

Weapon::Weapon(const Weapon &other) {
	_type = other._type;

	std::cout << "Weapon copy constructor is called." << std::endl;
}

Weapon::~Weapon() {
	std::cout << "Weapon \"" << _type << "\" destructor is called." << std::endl;
}

const std::string	&Weapon::getType() const {
	return (_type);
}

void	Weapon::setType( std::string type) {
	_type = type;
}