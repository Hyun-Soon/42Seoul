#include "Fixed.hpp"

Fixed::Fixed() : _value(0) 
{
	std::cout << "Default constructor called" << std::endl;
}

Fixed::Fixed( const Fixed& other ) : _value(other._value) 
{
	std::cout << "Copy constructor called" << std::endl;
}

Fixed& Fixed::operator = (const Fixed& other)
{
	std::cout << "Copy assignment operator called" << std::endl;
	if (this != &other)
		_value = other._value;
	return (*this);
}

Fixed::~Fixed() 
{
	std::cout << "Destructor called" << std::endl;
}

Fixed::Fixed(const int val)
{
	std::cout << "Int constructor called" << std::endl;
	_value = val << _point;
}

Fixed::Fixed(const float val)
{
	std::cout << "Float constructor called" << std::endl;
	_value = roundf(val * (1 << _point));
}

float	Fixed::toFloat( void ) const
{
	return (float(_value) / (1 << _point));
}

int		Fixed::toInt( void ) const
{
	return (_value >> _point);
}

void	Fixed::setRawBits(int const raw)
{
	std::cout << "setRawBits member function called" << std::endl;
	_value = raw;
}

int	Fixed::getRawBits( void ) const
{
	std::cout << "getRawBits member function called" << std::endl;
	return (_value);
}

std::ostream& operator<< (std::ostream& out, const Fixed& fixed)
{
	out << fixed.toFloat();
	return (out);
}