#pragma once

#include "ICharacter.hpp"
#include "Ice.hpp"
#include "Cure.hpp"
#include "Floor.hpp"

#define LIMIT 4

class	Character : public ICharacter
{
	private:
		Character();
		std::string		name;
		AMateria*		inventory[LIMIT];
		int				invenSize;
		const int		limit;

		int				findEmptySlot();
		void			deepCopyInven(AMateria *const * inven);

	public:
		Character(std::string name);
		Character(const Character& other);
		const Character& operator= (const Character& other);
		~Character();

		const std::string& getName() const;
		void equip(AMateria* m);
		void unequip(int idx);
		void use(int idx, ICharacter& target);
};
