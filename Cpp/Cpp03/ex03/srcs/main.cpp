#include "DiamondTrap.hpp"

int main()
{
	DiamondTrap	a("a");
	DiamondTrap b("b");

	a.whoAmI();
	a.attack("b");
	//std::cout << RED << "ClapTrap pointer name : " << ct->getName() << RESET << std::endl;
	//std::cout << RED << "Diamond name : " << a.getName()<< RESET << std::endl;
	//std::cout << "Diamond hitPoint : " << a.getHitPoint() << std::endl;
	//std::cout << "Diamond energyPoint : " << a.getEnergyPoint() << std::endl;
	//std::cout << "Diamond attackDamage : " << a.getAttackDamage() << std::endl;
	b.takeDamage(a.getAttackDamage());
	b.takeDamage(a.getAttackDamage());
	b.takeDamage(a.getAttackDamage());
	b.takeDamage(a.getAttackDamage());
	b.takeDamage(a.getAttackDamage());
	



	return 0;
}