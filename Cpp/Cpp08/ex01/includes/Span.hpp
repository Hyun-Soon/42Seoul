#pragma once

#include <vector>
#include <exception>
#include <algorithm>

class Span
{
	private:
		Span();
		const unsigned int _maxSize;
		std::vector<int> _v;
	
	public:
		Span(unsigned int N);
		Span(const Span& other);
		Span& operator=(const Span& other);
		~Span();
		void addNumber(unsigned int n);
		unsigned int shortestSpan();
		unsigned int longestSpan();

		template<typename T>
		void addManyNumbers(T& t)
		{
			if (t.size() + _v.size() > _maxSize)
				throw std::exception();
			for (typename T::iterator it = t.begin(); it != t.end(); ++it)
				_v.push_back(*it);
		}
};