#include <iostream>
#include <string>

void	megaphone(int argc, char **argv)
{
	std::string	ret;
	std::string	temp;

	for (int i = 1; i < argc; i++)
	{
		temp = std::string(argv[i]);
		for (size_t j = 0; j < temp.length(); j++)
			ret += toupper(temp[j]);
	}
	ret += '\n';
	std::cout << ret;
}

int main(int argc, char **argv)
{
	if (argc == 1)
		std::cout << "* LOUD AND UNBEARABLE FEEDBACK NOISE *\n";
	else
		megaphone(argc, argv);

	return (0);
}