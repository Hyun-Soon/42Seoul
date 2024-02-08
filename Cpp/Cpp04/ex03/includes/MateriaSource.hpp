#pragma once

#include "IMateriaSource.hpp"

class MateriaSource : public IMateriaSource
{
	private:
		AMateria*	materials[LIMIT];
		int			matSize;
		const int	limit;

		int	findEmptySlot();
		int	findSameMat(std::string const &type);

	public:
		MateriaSource();
		MateriaSource(const MateriaSource& other);
		MateriaSource& operator= (const MateriaSource& other);
		virtual ~MateriaSource();
		void deepCopyMat(AMateria *const * Mat);
		virtual void learnMateria(AMateria*);
		virtual AMateria* createMateria(std::string const & type);
};