#include "ClapTrap.hpp"

//TODO :: implement attack funcs for scav, frag, diamond and check OCCF

int main()
{
	ClapTrap	a("a");
	ClapTrap	b("b");
	ClapTrap	c("c");

	a.beRepaired(90);
	b.beRepaired(190);
	c.powerUp(110);
	c.attack(a.getName());
	a.takeDamage(c.getAttackDamage());
	c.attack(b.getName());
	b.takeDamage(c.getAttackDamage());
	c.attack(b.getName());
	b.takeDamage(c.getAttackDamage());
	return (0);
}