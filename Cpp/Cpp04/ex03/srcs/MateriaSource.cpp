#include "MateriaSource.hpp"

MateriaSource::MateriaSource() : matSize(0), limit(LIMIT)
{
	for (int i = 0; i < limit; i++)
		materials[i] = NULL;
}

MateriaSource::MateriaSource(const MateriaSource &other) : matSize(other.matSize), limit(other.limit)
{
	deepCopyMat(other.materials);
}

MateriaSource &MateriaSource::operator=(const MateriaSource &other)
{
	if (this != &other)
	{
		matSize = other.matSize;
		deepCopyMat(other.materials);
	}
	return (*this);
}

MateriaSource::~MateriaSource()
{
	for (int i = 0; i < limit; i++)
		if (materials[i])
			delete materials[i];
}

void MateriaSource::deepCopyMat(AMateria *const * Mat)
{
	for (int i = 0; i < limit; i++)
	{
		if (Mat[i])
		{
			if (Mat[i]->getType() == "ice")
				materials[i] = new Ice();
			else
				materials[i] = new Cure();
		}
		else
			materials[i] = NULL;
	}
}

void MateriaSource::learnMateria(AMateria *m)
{
	int emptyIdx;

	if (matSize >= limit)
	{
		std::cerr << "Can't learn more Materia." << std::endl;
		return ;
	}
	emptyIdx = findEmptySlot();
	materials[emptyIdx] = m;
	std::cout << "Slot[" << emptyIdx << "] : " << m->getType() << " learned." << std::endl;
	if (++matSize == limit)
		std::cout << "MateriaSource's slot is now full." << std::endl;
}

AMateria *MateriaSource::createMateria(std::string const &type)
{
	int	idx = findSameMat(type);

	if (idx == -1)
	{
		std::cerr << "Haven't learned " << type << "." << std::endl;
		return NULL;
	}

	return (materials[idx]->clone());
}

int	MateriaSource::findEmptySlot()
{
	int	i;

	for (i = 0; i < limit; i++)
		if (materials[i] == NULL)
			return (i);
	return (-1);
}

int	MateriaSource::findSameMat(std::string const &type)
{
	int	i;

	for (i = 0; i < limit; i++)
		if (materials[i] && materials[i]->getType() == type)
			return (i);
	return (-1);
}


