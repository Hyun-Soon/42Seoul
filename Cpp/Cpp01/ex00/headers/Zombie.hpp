#pragma once
# include <string>
# include <iostream>

class Zombie {
	public:
		Zombie();
		Zombie(const std::string name);
		~Zombie();
		void announce( void );
		const std::string	&getName() const;
		void	setName( std::string name );

	private:
		std::string	name;
};

Zombie* newZombie( std::string name );
void randomChump( std::string name );