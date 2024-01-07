#include "contact.hpp"

int	contact::get_valid_inp(std::string prompt, std::string& inp)
{
	std::cout << prompt << '\n';
	while (std::cin >> inp)
	{
		for (size_t i = 0; i < inp.length(); i++)
		{
			if (inp[i] < 32 || inp[i] == 127)
				return (1);
			if (inp.length() == 1 && inp[0] == '\n')
				return (1);
		}
	}
	return (0);
}

void	contact::set_first_name(std::string first_name)
{
	this->first_name = first_name;
}

void	contact::set_last_name(std::string second_name)
{
	this->last_name = second_name;
}

void	contact::set_nickname(std::string nickname)
{
	this->nickname = nickname;
}

void	contact::set_info()
{
	std::string	inp;

	if ()

}

void	contact::print_contact()
{
	std::cout << set
}