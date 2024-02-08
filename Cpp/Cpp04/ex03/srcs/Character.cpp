#include "Character.hpp"

Character::Character() : name("hyuim"), invenSize(0), limit(LIMIT)
{
	for (int i = 0; i < limit; i++)
		inventory[i] = NULL;
}

Character::Character(std::string name) : name(name), invenSize(0), limit(LIMIT)
{
	for (int i = 0; i < limit; i++)
		inventory[i] = NULL;
}

Character::Character(const Character &other) : name(other.name), invenSize(other.invenSize), limit(other.limit)
{
	deepCopyInven(other.inventory);
}

const Character &Character::operator=(const Character &other)
{
	if (this != &other)
	{
		name = other.name;
		deepCopyInven(other.inventory);
		invenSize = other.invenSize;
	}
	return (*this);
}

Character::~Character()
{
	for (int i = 0; i < limit; i++)
		if (inventory[i])
			delete inventory[i];
}

const std::string &Character::getName() const
{
	return (name);
}

int	Character::findEmptySlot()
{
	int	i;

	for (i = 0; i < limit; i++)
		if (inventory[i] == NULL)
			return (i);
	return (-1);
}

void Character::deepCopyInven(AMateria *const * inven)
{
	for (int i = 0; i < limit; i++)
	{
		if (inven[i])
		{
			if (inven[i]->getType() == "ice")
				inventory[i] = new Ice();
			else
				inventory[i] = new Cure();
		}
		else
			inventory[i] = NULL;
	}
}

void Character::equip(AMateria *m)
{
	int	emptyIdx;

	if (invenSize >= limit)
	{
		std::cerr << "Inventory is full." << std::endl;
		return ;
	}

	emptyIdx = findEmptySlot();
	inventory[emptyIdx] = m;
	std::cout << m->getType() << " equipped at " << emptyIdx << " slot." << std::endl;
	if (++invenSize == limit)
		std::cout << "Inventory is now full." << std::endl;
}

void Character::unequip(int idx)
{
	std::string	unequipType;

	if (idx >= limit || idx >= invenSize || inventory[idx] == NULL)
	{
		std::cout << "Wrong idx." << std::endl;
		return ;
	}
	Floor::throwToFloor(inventory[idx]);
	unequipType = inventory[idx]->getType();
	inventory[idx] = NULL;
	--invenSize;

	std::cout << name << " unequipped " << unequipType << std::endl; 
}

void Character::use(int idx, ICharacter &target)
{	
	if (idx < 0 || idx >= limit)
		std::cout << "Wrong idx." << std::endl;
	else if (inventory[idx])
	{
		std::cout << name << " uses " << inventory[idx]->getType() << std::endl;
		inventory[idx]->use(target);
	}
	else
		std::cout << idx << " slot is empty." << std::endl;
}
