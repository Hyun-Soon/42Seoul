#pragma once

# include <iostream>
# include <string>
# include <cmath>

class	Fixed
{
	public:
		Fixed();
		Fixed(const int val);
		Fixed(const float val);
		Fixed( const Fixed& other );
		~Fixed();
		Fixed&	operator = (const Fixed& other);
		float	toFloat( void ) const;
		int		toInt( void ) const;
		void	setRawBits(int const raw);
		int		getRawBits( void ) const;
		int		getPoint( void ) const;
		Fixed&	operator << (float& val);
		bool	operator> (const Fixed& obj) const;
		bool	operator< (const Fixed& obj) const;
		bool	operator>= (Fixed& obj);
		bool	operator<= (Fixed& obj);
		bool	operator== (Fixed& obj);
		bool	operator!= (Fixed& obj);
		Fixed	operator+ (const Fixed& obj) const;
		Fixed	operator- (const Fixed& obj) const;
		Fixed	operator* (const Fixed& obj) const;
		Fixed	operator/ (const Fixed& obj) const;
		Fixed&	operator++ ();
		Fixed	operator++ (int);
		static Fixed&		min(Fixed& a, Fixed& b);
		static const Fixed&	min(const Fixed& a, const Fixed& b);
		static Fixed&		max(Fixed& a, Fixed& b);
		static const Fixed&	max(const Fixed& a, const Fixed& b);
		
	private:
		int					_value;
		static const int	_point = 8;
};

std::ostream& operator<< (std::ostream& out, const Fixed& fixed);