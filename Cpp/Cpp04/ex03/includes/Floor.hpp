#pragma once

#include "AMateria.hpp"

class	Floor
{
	private:
		static AMateria**		floor;
		static size_t			floorSize;
		static size_t			floorCapacity;
		
		static void resizeInven();
	public:
		Floor();
		~Floor();
		static void throwToFloor(AMateria* material);
};