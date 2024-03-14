#include "funcs.hpp"

Base* generate()
{
	int type = rand() % 3;
	Base* ret;

	switch (type)
	{
	case 0:
		ret = new A();
		break;
	case 1:
		ret = new B();
		break;
	default:
		ret = new C();
		break;
	}
	return ret;
}

void identify(Base* p)
{
	std::cout << "Pointer" << std::endl;
	if (dynamic_cast<A*>(p) != NULL)
		std::cout << "Actual type : A" << std::endl;
	else if (dynamic_cast<B*>(p) != NULL)
		std::cout << "Actual type : B" << std::endl;
	else if (dynamic_cast<C*>(p) != NULL)
		std::cout << "Actual type : C" << std::endl;
}

void identify(Base& p)
{
	std::cout << "Reference" << std::endl;
	try
	{
		(void)dynamic_cast<A&>(p);
		std::cout << "Actual type : A" << std::endl;
	}
	catch(const std::exception& e) {}

	try
	{
		(void)dynamic_cast<B&>(p);
		std::cout << "Actual type : B" << std::endl;
	}
	catch(const std::exception& e) {}

	try
	{
		(void)dynamic_cast<C&>(p);
		std::cout << "Actual type : C" << std::endl;
	}
	catch(const std::exception& e) {}
}