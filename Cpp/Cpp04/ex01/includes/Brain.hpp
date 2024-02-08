#pragma once

#include <string>
#include <iostream>

class Brain
{
	private:
		std::string	_ideas[100];
	public:
		Brain();
		Brain(const Brain& other);
		const Brain& operator= (const Brain& other);
		~Brain();
		const std::string*	getIdeas() const;
		void				setIdeas(const std::string idea);
};

