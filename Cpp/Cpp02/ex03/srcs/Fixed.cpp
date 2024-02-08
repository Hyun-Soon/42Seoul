#include "Fixed.hpp"

Fixed::Fixed() : _value(0) 
{
	//std::cout << "Default constructor called" << std::endl;
}

Fixed::Fixed( const Fixed& other ) : _value(other._value) 
{
	//std::cout << "Copy constructor called" << std::endl;
}

Fixed& Fixed::operator = (const Fixed& other)
{
	//std::cout << "Copy assignment operator called" << std::endl;
	if (this != &other)
		_value = other._value;
	return (*this);
}

Fixed::~Fixed() 
{
	//std::cout << "Destructor called" << std::endl;
}

Fixed::Fixed(const int val)
{
	//std::cout << "Int constructor called" << std::endl;
	_value = val << _point;
}

Fixed::Fixed(const float val)
{
	//std::cout << "Float constructor called" << std::endl;
	_value = roundf(val * (1 << _point));
}

float	Fixed::toFloat( void ) const
{
	return (_value / float(1 << _point));
}

int		Fixed::toInt( void ) const
{
	return (_value >> _point);
}

void	Fixed::setRawBits(int const raw)
{
	//std::cout << "setRawBits member function called" << std::endl;
	_value = raw;
}

int	Fixed::getRawBits( void ) const
{
	//std::cout << "getRawBits member function called" << std::endl;
	return (_value);
}


std::ostream& operator<< (std::ostream& out, const Fixed& fixed)
{
	out << fixed.toFloat();
	return (out);
}

bool Fixed::operator> (const Fixed& obj) const
{
	return (_value > obj.getRawBits());
}

bool Fixed::operator< (const Fixed& obj) const
{
	return (_value < obj.getRawBits());
}

bool Fixed::operator>= (Fixed& obj)
{
	return (_value >= obj.getRawBits());
}

bool Fixed::operator<= (Fixed& obj)
{
	return (_value <= obj.getRawBits());
}

bool Fixed::operator== (Fixed& obj)
{
	return (_value == obj.getRawBits());
}

bool Fixed::operator!= (Fixed& obj)
{
	return (_value != obj.getRawBits());
}

Fixed Fixed::operator+ (const Fixed& obj) const
{
	Fixed	ret;

	ret.setRawBits(_value + obj.getRawBits());
	return (ret);
}

Fixed Fixed::operator- (const Fixed& obj) const
{
	Fixed	ret;

	ret.setRawBits(_value - obj.getRawBits());
	return (ret);
}

Fixed Fixed::operator* (const Fixed& obj) const
{
	Fixed	ret;

	ret.setRawBits((_value * obj.getRawBits()) >> obj.getPoint());
	return (ret);
}

Fixed Fixed::operator/ (const Fixed& obj) const
{
	Fixed	ret;

	ret.setRawBits((_value << obj.getPoint()) / obj.getRawBits());
	return (ret);
}

//pre-increment
Fixed& Fixed::operator++ ()
{
	++_value;
	return (*this);
}

//post-increment
Fixed Fixed::operator++ (int)
{
	Fixed	ret;

	ret = *this;
	++_value;
	return (ret);
}

Fixed&	Fixed::min(Fixed& a, Fixed& b)
{
	return (a < b) ? a : b;
}

const Fixed&	Fixed::min(const Fixed& a, const Fixed& b)
{
	return (a < b) ? a : b;
}

Fixed&	Fixed::max(Fixed& a, Fixed& b)
{
	return (a > b) ? a : b;
}

const Fixed&	Fixed::max(const Fixed& a, const Fixed& b)
{
	return (a > b) ? a : b;
}

int	Fixed::getPoint( void ) const
{
	return (_point);
}