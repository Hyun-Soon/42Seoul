#pragma once

#include <stack>

template<typename T>
class MutantStack : public std::stack<T>
{
	public:
		typedef typename std::stack<T>::container_type							container_type;
		typedef typename std::stack<T>::container_type::iterator				iterator;
		//typedef typename std::stack<T>::container_type::const_iterator			const_iterator;
		typedef typename std::stack<T>::container_type::reverse_iterator		reverse_iterator;
		//typedef typename std::stack<T>::container_type::const_reverse_iterator	const_reverse_iterator;

		MutantStack() {}

		MutantStack(const MutantStack& other) : std::stack<T>(other) {}

		MutantStack& operator=(const MutantStack& other)
		{
			if (this != &other)
				std::stack<T>::operator=(other);
			return *this;
		}

		~MutantStack() {}

		iterator begin()
		{
			return this->c.begin();
		}

		//const_iterator cbegin()
		//{
		//	return this->c.cbegin();
		//}

		reverse_iterator rbegin()
		{
			return this->c.rbegin();
		}

		//const_reverse_iterator crbegin()
		//{
		//	return this->c.crbegin();
		//}

		iterator end()
		{
			return this->c.end();
		}

		//const_iterator cend()
		//{
		//	return this->c.cend();
		//}

		reverse_iterator rend()
		{
			return this->c.rend();
		}

		//const_reverse_iterator crend()
		//{
		//	return this->c.crend();
		//}
};