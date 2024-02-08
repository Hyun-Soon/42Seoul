#include "../headers/Zombie.hpp"

Zombie::Zombie() {
	this->name = "";
}

Zombie::Zombie(const std::string name) {
	this->name = name;
}

void Zombie::announce( void ) {
	std::cout << this->name << ": BraiiiiiiinnnzzzZ..." << std::endl;
	return ;
}

const std::string	&Zombie::getName() const{
	return (this->name);
}

void	Zombie::setName( std::string name ) {
	this->name = name;
	return ;
}

Zombie::~Zombie()
{
	std::cout << this->name << " died..." << std::endl;
}