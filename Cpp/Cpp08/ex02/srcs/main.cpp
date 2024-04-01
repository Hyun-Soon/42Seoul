#include "MutantStack.hpp"
#include <iostream>

int main()
{
MutantStack<int> mstack;
mstack.push(5);
mstack.push(17);
std::cout << mstack.top() << std::endl;
mstack.pop();
std::cout << mstack.size() << std::endl;
mstack.push(3);
mstack.push(5);
mstack.push(737);
//[...]
mstack.push(0);
MutantStack<int>::iterator it = mstack.begin();
MutantStack<int>::iterator ite = mstack.end();
++it;
--it;
while (it != ite)
{
std::cout << *it << std::endl;
++it;
}
std::stack<int> s(mstack);

std::cout << std::endl;

MutantStack<int> mstack2(mstack);
MutantStack<int>::iterator it2 = mstack2.begin();
MutantStack<int>::iterator ite2 = mstack2.end();
++it2;
--it2;
while (it2 != ite2)
{
std::cout << *it2 << std::endl;
++it2;
}

std::cout << std::endl;

mstack2.push(999);
mstack2.push(998);
mstack2.push(997);
mstack2.push(996);

mstack = mstack2;

it = mstack.begin();
ite = mstack.end();
++it;
--it;
while (it != ite)
{
std::cout << *it << std::endl;
++it;
}

return 0;
}