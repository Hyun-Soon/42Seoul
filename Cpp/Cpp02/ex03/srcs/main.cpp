#include "Point.hpp"

int main()
{
	// ---in the triangle---
	Point const a(Fixed(0.0f), Fixed(0.0f));
	Point const b(Fixed(2.0f), Fixed(0.0f));
	Point const c(Fixed(1.0f), Fixed(1.0f));
	Point const point(Fixed(1.0f), Fixed(0.3f));

	//---not in the triangle---
	//Point const a(Fixed(0.0f), Fixed(0.0f));
	//Point const b(Fixed(2.0f), Fixed(0.0f));
	//Point const c(Fixed(1.0f), Fixed(1.0f));
	//Point const point(Fixed(2.0f), Fixed(0.5f));

	if (bsp(a, b, c, point))
		std::cout << "the point IS IN the triangle." << std::endl;
	else
		std::cout << "the point IS NOT IN the triangle." << std::endl;

	return 0;
}