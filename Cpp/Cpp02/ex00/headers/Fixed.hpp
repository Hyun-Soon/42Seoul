#pragma once


# include <iostream>
# include <string>

class	Fixed
{
	public:
		Fixed();
		Fixed( const Fixed& other );
		Fixed& operator = (const Fixed& other);
		~Fixed();
		void	setRawBits(int const raw);
		int	getRawBits( void ) const;
	private:
		int					_value;
		static const int	_point = 8;
};