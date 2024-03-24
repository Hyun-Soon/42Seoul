#pragma once

#include <stack>

template<typename T>
class MutantStack
{
	private:
		std::stack<T> stk;
	public:
		MutantStack();
		MutantStack(const MutantStack& other);
		MutantStack& operator=(const MutantStack& other);
		~MutantStack();
		const T& top() const;
		bool empty() const;
		size_t size() const;
		void push( const T& value );
		void push_range( R&& rg ); //TODO :: study this function
		//TODO :: what is &&?
		//TODO :: add member funcs
};
