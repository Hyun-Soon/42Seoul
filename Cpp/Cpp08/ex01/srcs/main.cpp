#include "Span.hpp"
#include <iostream>

int main()
{
	try
	{
		Span a(10000);
		for (int i = 0; i < 10000; i++)
			a.addNumber(i);
		
		std::cout << a.longestSpan() << std::endl;
		std::cout << a.shortestSpan() << std::endl;


		Span b(10000);
		std::vector<int> tempV;
		for (int i = 0; i < 10000; i+=2)
			tempV.push_back(i);
		b.addManyNumbers(tempV);

		std::cout << b.longestSpan() << std::endl;
		std::cout << b.shortestSpan() << std::endl;
		
	}
	catch(const std::exception& e)
	{
		std::cerr << e.what() << '\n';
	}
	




	return 0;
}

//int main()
//{
//Span sp = Span(5);
//Span sp2 = Span(6);
//sp.addNumber(6);
//sp.addNumber(3);
//sp.addNumber(17);
//sp.addNumber(9);
//sp.addNumber(11);
//std::cout << sp.shortestSpan() << std::endl;
//std::cout << sp.longestSpan() << std::endl;
//std::cout << std::endl;
//return 0;
//}