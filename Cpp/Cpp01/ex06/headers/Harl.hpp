#pragma once
# include <string>
# include <iostream>

class	Harl
{
	public:
		Harl();
		~Harl();
		void	complain( std::string level );
		void	filter( std::string level );

	private:
		int			_cmdCnt;
		std::string _cmd[4];
		void debug( void );
		void info( void );
		void warning( void );
		void error( void );
};