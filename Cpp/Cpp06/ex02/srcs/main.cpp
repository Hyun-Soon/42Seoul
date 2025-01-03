#include "A.hpp"
#include "B.hpp"
#include "C.hpp"
#include "funcs.hpp"
#include <iostream>
#include <unistd.h>

int main()
{
	srand(time(NULL));
	for (int i = 0; i < 5; i++)
	{
		Base* basePtr = generate();
		Base& baseRef = *basePtr;
		identify(basePtr);
		identify(baseRef);
		delete basePtr;
		sleep(1);
	}
	return 0;
}