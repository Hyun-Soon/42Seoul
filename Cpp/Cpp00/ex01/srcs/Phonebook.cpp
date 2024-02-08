#include "Phonebook.hpp"

int	Phonebook::get_size()
{
	return (this->size);
}

void	Phonebook::add()
{
	int	idx;

	idx = get_size() % 8;
	this->contacts[idx].set_info();
	this->size++;
};

void	Phonebook::print_tables()
{
	std::cout	<< std::setw(10) << "Idx" << "|"
		<< std::setw(10) << "First Name" << "|"
		<< std::setw(10) << "Last Name" << "|"
		<< std::setw(10) << "Nickname" << "\n";

	for (int i = 0; i < this->size && i < 8; i++)
		this->contacts[i].print_column(i);
}

int	Phonebook::get_idx()
{
	int			int_inp;
	std::string	inp;

	std::cout << "\nChoose index to display : ";

	while (1)
	{
		if (getline(std::cin, inp).fail())
		{
			std::cin.clear();
			clearerr(stdin);
			std::cout << std::endl;
			std::cout << "\nWrong input. \nChoose index to display : ";
		}
		else
		{
			int_inp = std::atoi(inp.c_str());
			if (inp.length() == 1 && (int_inp > 0 && int_inp < 9) && int_inp <= this->size)
				return (int_inp);
			std::cout << "\nWrong input. \nChoose index to display : ";
		}
	}
}

void	Phonebook::search()
{
	int	idx;

	if (this->size == 0)
	{
		std::cout << "\nNo contacts are registred.\n";
		return ;
	}
	print_tables();
	idx = get_idx();
	this->contacts[idx - 1].print_info();
}