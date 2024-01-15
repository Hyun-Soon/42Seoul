#include "Fixed.hpp"

int main( void ) {
	Fixed a;
	Fixed b( a );
	Fixed c(3.03f);
	//c = b;
	std::cout << a.getRawBits() << std::endl;
	std::cout << b.getRawBits() << std::endl;
	std::cout << c.getRawBits() << std::endl;
	//c.setRawBits(3);
	//std::cout << c.getRawBits() << std::endl;
	std::cout << "here : " << c.toFloat() << std::endl;
	//std::cout << c.toFloat() << std::endl;
	return 0;
}