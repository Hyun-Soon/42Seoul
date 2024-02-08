#pragma once
# include "Contact.hpp"

class	Phonebook
{
	private :
		int			size;
		Contact		contacts[8];

		void		print_tables();
		int			get_idx();

	public :
		int			get_size();
		void		add();
		void		search();
};
