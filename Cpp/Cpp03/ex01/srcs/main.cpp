#include "ScavTrap.hpp"

int main()
{
	ScavTrap a("a");
	ScavTrap b("b");
	ScavTrap c(a);

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
	a.guardGate();
	b.guardGate();
	c.guardGate();

	return 0;
}