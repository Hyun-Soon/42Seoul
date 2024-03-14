#include "Serializer.hpp"

int main()
{
	Data a(123);
	Data b(456);

	std::cout << a.getData() << std::endl;
	uintptr_t serializeRet = Serializer::serialize(&a);
	Data* deserializeRet = Serializer::deserialize(serializeRet);
	std::cout << deserializeRet->getData() << std::endl;


	std::cout << b.getData() << std::endl;
	uintptr_t serializeRet2 = Serializer::serialize(&b);
	Data* deserializeRet2 = Serializer::deserialize(serializeRet2);
	std::cout << deserializeRet2->getData() << std::endl;

	return 0;
}