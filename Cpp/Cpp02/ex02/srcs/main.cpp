#include "Fixed.hpp"

int main( void ) {
Fixed a;
Fixed const b( Fixed( 1.1f ) * Fixed( 2 ) );
std::cout << a << std::endl;
std::cout << ++a << std::endl;
std::cout << a << std::endl;
std::cout << a++ << std::endl;
std::cout << a << std::endl;
std::cout << "-------------" << std::endl;
std::cout << b.toFloat() << std::endl;
std::cout << Fixed::max( a, b ) << std::endl;
return 0;
}