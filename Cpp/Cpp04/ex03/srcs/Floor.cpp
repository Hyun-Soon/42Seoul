#include "Floor.hpp"

AMateria**	Floor::floor = new AMateria*[10];
size_t		Floor::floorSize = 0;
size_t		Floor::floorCapacity = 10;

Floor::Floor() {}

Floor::~Floor()
{
	for (size_t i = 0; i < floorCapacity; i++)
		if (floor[i])
			delete floor[i];
	delete[] floor;
}

void Floor::throwToFloor(AMateria *material)
{
	if (floorSize >= floorCapacity)
		resizeInven();
	floor[floorSize++] = material;
}

void Floor::resizeInven()
{
	AMateria**	temp;
	size_t		i;

	floorCapacity *= 2;
	temp = new AMateria*[floorCapacity];
	for (i = 0; i < floorSize; i++)
		temp[i] = floor[i];
	for (; i < floorCapacity; i++)
		temp[i] = NULL;
	delete[] floor;
	floor = temp;
}

