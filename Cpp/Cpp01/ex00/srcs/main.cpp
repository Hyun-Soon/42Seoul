#include "Zombie.hpp"

int main()
{
	std::string	name1 = "hyun";
	std::string	name2 = "soon";

	Zombie	*zombie;

	randomChump(name1);
	zombie = newZombie(name2);
	zombie->announce();
	delete zombie;

	return 0;
}