#include "Contact.hpp"

void	Contact::get_valid_inp(std::string prompt, std::string& inp)
{
	std::cout << prompt << '\n';
	while (1)
	{
		if (getline(std::cin, inp).fail())
		{
			std::cin.clear();
			clearerr(stdin);
			std::cout << std::endl;
			std::cout << "Wrong input.\n" << prompt << "\n";
		}
		else
		{
			int	err_flag = 0;
			if (inp.length() == 0)
				err_flag = 1;
			for (size_t i = 0; i < inp.length() && err_flag == 0; i++)
			{
				if (inp[i] < 32 || inp[i] >= 127)
					err_flag = 1;
			}
			if (err_flag == 0)
				return ;
			std::cout << "Wrong input.\n" << prompt;
		}
	}

}

void	Contact::set_first_name(std::string first_name)
{
	this->first_name = first_name;
}

void	Contact::set_last_name(std::string last_name)
{
	this->last_name = last_name;
}

void	Contact::set_nickname(std::string nickname)
{
	this->nickname = nickname;
}

void	Contact::set_phone_number(std::string phone_number)
{
	this->phone_number = phone_number;
}
void	Contact::set_darkest_secret(std::string darkest_secret)
{
	this->darkest_secret = darkest_secret;
}

void	Contact::set_info()
{
	std::string	inp;

	get_valid_inp("\nType first name : ", inp);
	set_first_name(inp);
	get_valid_inp("Type last name : ", inp);
	set_last_name(inp);
	get_valid_inp("Type nickname : ", inp);
	set_nickname(inp);
	get_valid_inp("Type phone number : ", inp);
	set_phone_number(inp);
	get_valid_inp("Type darkest secret : ", inp);
	set_darkest_secret(inp);
	std::cout << "\n";
}

std::string	Contact::get_first_name()
{
	return (this->first_name);
}

std::string	Contact::get_last_name()
{
	return (this->last_name);
}

std::string	Contact::get_nickname()
{
	return (this->nickname);
}

std::string	Contact::get_phone_number()
{
	return (this->phone_number);
}
std::string	Contact::get_darkest_secret()
{
	return (this->darkest_secret);
}

void	Contact::print_column(int idx)
{
	std::string	temp;

	idx += 1;
	std::cout << std::setw(10) << idx << "|";
	temp = first_name;
	if (first_name.length() > 10)
	{
		temp = first_name.substr(0, 10);
		temp.replace(temp.end() - 1, temp.end(), ".");
	}
	std::cout << std::setw(10) << temp << "|";

	temp = last_name;
	if (last_name.length() > 10)
	{
		temp = last_name.substr(0, 10);
		temp.replace(temp.end() - 1, temp.end(), ".");
	}
	std::cout << std::setw(10) << temp << "|";
	
	temp = nickname;
	if (nickname.length() > 10)
	{
		temp = nickname.substr(0, 10);
		temp.replace(temp.end() - 1, temp.end(), ".");
	}
	std::cout << std::setw(10) << temp << "\n";
}

void	Contact::print_info()
{
	std::cout << "first name : " << get_first_name() << "\n";
	std::cout << "last name : " << get_last_name() << "\n";
	std::cout << "nickname : " << get_nickname() << "\n";
	std::cout << "phone number : " << get_phone_number() << "\n";
	std::cout << "darkest secret : " << get_darkest_secret() << "\n\n";
}
