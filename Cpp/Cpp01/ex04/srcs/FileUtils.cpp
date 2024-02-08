#include "FileUtils.hpp"

FileUtils::FileUtils() : _filename("") {}

FileUtils::FileUtils(std::string filename) : _filename(filename) {};

FileUtils::~FileUtils() {}

void	FileUtils::setFilename(std::string filename)
{
	_filename = filename;
}

const std::string	&FileUtils::getFilename() const
{
	return (_filename);
}

std::string	FileUtils::contentReplace(std::string s1, std::string s2)
{
	std::string		line;
	std::string		ret;
	std::ifstream	myfile(_filename);
	std::ofstream	rpfile;

	if (s1 == s2)
		return (ret);

	if (myfile.is_open())
	{
		ret = std::string(_filename).append(".replace");
		rpfile.open(ret);
		while (getline(myfile, line))
		{
			std::string	head, tail;
			size_t	pos = line.find(s1);
			while (pos != std::string::npos)
			{
				head = line.substr(0, pos);
				tail = line.substr(pos + s1.length());
				line = head + s2 + tail;
				pos = line.find(s1);
			}
			rpfile << line + "\n";
		}
		rpfile.close();
	}
	return (ret);
}