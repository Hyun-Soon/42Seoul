#pragma once
# include <string>
# include <iostream>


class Weapon {
	public:
		Weapon(std::string type);
		Weapon(const Weapon &other);
		~Weapon();
		const std::string	&getType() const;
		void	setType( std::string type);

	private:
		Weapon();
		std::string	_type;
};