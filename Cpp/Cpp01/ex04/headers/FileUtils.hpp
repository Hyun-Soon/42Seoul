#pragma once
# include <iostream>
# include <fstream>
# include <string>

class	FileUtils
{
	public:
		FileUtils();
		FileUtils(std::string filename);
		~FileUtils();
		void	setFilename(std::string filename);
		const std::string	&getFilename() const;
		std::string	contentReplace(std::string s1, std::string s2);

	private:
		std::string	_filename;
};