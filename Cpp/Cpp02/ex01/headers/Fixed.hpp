#pragma once

# include <iostream>
# include <string>
# include <cmath>

class	Fixed
{
	public:
		Fixed();
		Fixed( const Fixed& other );
		Fixed& operator = (const Fixed& other);
		~Fixed();
		Fixed(const int val);
		Fixed(const float val);
		float	toFloat( void ) const;
		int		toInt( void ) const;
		void	setRawBits(int const raw);
		int	getRawBits( void ) const;
		Fixed& operator << (float& val);
	private:
		int					_value;
		static const int	_point = 8;
};

std::ostream& operator<< (std::ostream& out, const Fixed& fixed);