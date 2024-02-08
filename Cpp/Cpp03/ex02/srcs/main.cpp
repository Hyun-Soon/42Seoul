#include "FragTrap.hpp"

int main()
{
	FragTrap a("a");
	FragTrap b("b");
	FragTrap c(a);

	a.attack(b.getName());
	b.takeDamage(a.getAttackDamage());
	b.powerUp(200);
	b.attack(a.getName());
	a.takeDamage(b.getAttackDamage());
	a.beRepaired(100);
	b.beRepaired(20);

	std::cout << "here\n" << std::endl;
	for (int i = 0; i < 50; i++)
		b.beRepaired(1);

	std::cout << std::endl;
	a.highFivesGuys();
	b.highFivesGuys();
	c.highFivesGuys();

	return 0;
}