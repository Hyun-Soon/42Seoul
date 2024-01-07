#include "contact.hpp"

class	phonebook
{
	private:
		int		idx;
		int		size;
		contact	contacts[8];

	public:
		void	add()
		{
			contact		temp;
			std::string	inp;

			std::cin >> inp;
			temp.set_first_name(inp);
			std::cin >> inp;
			temp.set_last_name(inp);
			std::cin >> inp;
			temp.set_nickname(inp);

			this->size++;
		};

		void	search()
		{

		};
};
