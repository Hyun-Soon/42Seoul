#pragma once

# include "Fixed.hpp"

class	Point
{
	public:
		Point();
		Point( Fixed x, Fixed y );
		Point(const Point& other);
		Point& operator= (const Point& other);
		~Point();
		const Fixed& getX() const;
		const Fixed& getY() const;

	private:
		const Fixed	_x;
		const Fixed	_y;
};

bool bsp( Point const a, Point const b, Point const c, Point const point);
Fixed	getRotDir(Point const a, Point const b, Point const point);