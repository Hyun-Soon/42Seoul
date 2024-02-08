#include "Point.hpp"

Point::Point() : _x(0), _y(0)
{
	//std::cout << "Default constructor called" << std::endl;
}

Point::Point( Fixed x, Fixed y ) : _x(x), _y(y)
{
	//std::cout << "Fixed constructor called" << std::endl;
}

Point::Point(const Point& other) : _x(other._x), _y(other._y)
{
	//std::cout << "Copy constructor called" << std::endl;
}

Point& Point::operator= (const Point& other)
{
	Fixed*	xPointer;
	Fixed*	yPointer;

	xPointer = const_cast<Fixed*>(&(this->_x));
	yPointer = const_cast<Fixed*>(&(this->_y));
	*xPointer = other._x;
	*yPointer = other._y;
	return (*this);
}

Point::~Point()
{
	//std::cout << "Default destructor called" << std::endl;
}

const Fixed& Point::getX() const
{
	return (_x);
}

const Fixed& Point::getY() const
{
	return (_y);
}