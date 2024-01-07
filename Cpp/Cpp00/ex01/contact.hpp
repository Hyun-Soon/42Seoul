#include <iostream>
#include <string>

class	contact {
	private:
		std::string	first_name;
		std::string	last_name;
		std::string	nickname;

	public:
		void	set_first_name(std::string first_name);
		void	set_last_name(std::string second_name);
		void	set_nickname(std::string nickname);
		void	set_info();
		int		get_valid_inp(std::string prompt, std::string& inp)
		void	print_contact();
};