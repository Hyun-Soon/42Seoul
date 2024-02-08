#include "../headers/FileUtils.hpp"

int main(int argc, char **argv)
{
	std::string	ret;
	std::string	s1, s2;

	if (argc != 4) {
		std::cout << "Wrong args." << std::endl;
		return (1);
	}
	FileUtils	fileUtils(argv[1]);

	s1 = argv[2];
	s2 = argv[3];


	ret = fileUtils.contentReplace(s1, s2);
	if (ret.empty())
		std::cout << "err occured." << std::endl;
	else
		std::cout << "result filename : " << ret << std::endl;
	
	return (0);
}