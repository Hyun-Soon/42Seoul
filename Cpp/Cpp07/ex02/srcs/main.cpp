#include <iostream>
#include <Array.hpp>

#define MAX_VAL 750

void check()
{
	system("leaks Iter");
}

int main(int, char**)
{
	atexit(check);
    Array<int> numbers(MAX_VAL);
    int* mirror = new int[MAX_VAL];
    srand(time(NULL));
    for (int i = 0; i < MAX_VAL; i++)
    {
        const int value = rand();
        numbers[i] = value;
        mirror[i] = value;
    }
	std::cout << "numbers[0] : " << numbers[0] << std::endl;
    //SCOPE
    {
		std::cout << "in scope" << std::endl;
		Array<int> tmp = numbers;
		std::cout << "tmp[0] : " << tmp[0] << std::endl;
		Array<int> test(tmp);
		std::cout << "test[0] : " << test[0] << std::endl;
    }
    for (int i = 0; i < MAX_VAL; i++)
    {
        if (mirror[i] != numbers[i])
        {
            std::cerr << "didn't save the same value!!" << std::endl;
            return 1;
        }
    }
    try
    {
        numbers[-2] = 0;
    }
    catch(const std::exception& e)
    {
		std::cerr << "catch 1 : ";
        std::cerr << e.what() << '\n';
    }
    try
    {
        numbers[MAX_VAL] = 0;
    }
    catch(const std::exception& e)
    {
		std::cerr << "catch 2 : ";
        std::cerr << e.what() << '\n';
    }

    for (int i = 0; i < MAX_VAL; i++)
    {
        numbers[i] = rand();
    }
    delete [] mirror;//
	std::cout << std::endl;
    return 0;
}