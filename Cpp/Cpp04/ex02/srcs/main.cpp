#include "Cat.hpp"
#include "Dog.hpp"

#define RED "\033[1;31m"
#define EOC "\033[0;0m"

//void	check()
//{
//	system("leaks DeepCopy");
//}

int main()
{
	//atexit(check);

	//=======================================================
	//const Animal* j = new Dog();
	//const Animal* i = new Cat();
	//delete j;//should not create a leak
	//delete i;

	//return 0;
	//=======================================================

	
	//=======================================================
	Animal*	arr[10];
	Dog		dog;
	Cat		cat;

	dog.setBrain("meet!!");
	cat.setBrain("fish!!");
	for (int idx = 0; idx < 5; idx++)
		arr[idx] = new Dog(dog);
	for (int idx = 5; idx < 10; idx++)
		arr[idx] = new Cat(cat);
	
	for (int i = 0; i < 5; i++)
		static_cast<Dog *>(arr[i])->printFirstIdea();
	for (int i = 5; i < 10; i++)
		static_cast<Cat *>(arr[i])->printFirstIdea();

	std::cout << RED << "================Change Ideas================" << EOC << std::endl;
	dog.setBrain(std::string("changed dog idea"));
	cat.setBrain(std::string("changed cat idea"));
	for (int i = 0; i < 5; i++)
		static_cast<Dog *>(arr[i])->printFirstIdea();
	for (int i = 5; i < 10; i++)
		static_cast<Cat *>(arr[i])->printFirstIdea();

	std::cout << std::endl;
	dog.printFirstIdea();
	cat.printFirstIdea();


	for (int i = 0; i < 10; i++)
		delete arr[i];

	//Animal a;
	//=======================================================

	return 0;
}
