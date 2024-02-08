#include "Zombie.hpp"

int main()
{
	Zombie *zombies;
	int		n;

	n = 8;
	zombies = zombieHorde(n, std::string("zombie"));

	for (int i = 0; i < n; i++)
		zombies[i].announce();

	delete[] zombies;
	return 0;
}