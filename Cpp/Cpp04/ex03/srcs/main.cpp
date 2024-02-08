#include "Character.hpp"
#include "Cure.hpp"
#include "Ice.hpp"
#include "MateriaSource.hpp"
#include "Floor.hpp"

//void check()
//{
//	system("leaks Character");
//}

int main()
{
	//atexit(check);
	IMateriaSource* src = new MateriaSource();
	src->learnMateria(new Ice());
	src->learnMateria(new Cure());
	ICharacter* me = new Character("me");
	AMateria* tmp;
	tmp = src->createMateria("ice");
	me->equip(tmp);
	tmp = src->createMateria("cure");
	me->equip(tmp);
	ICharacter* bob = new Character("bob");
	me->use(6, *bob);
	me->use(1, *bob);
	me->unequip(1);
	delete bob;
	delete me;
	delete src;
	return 0;
}
