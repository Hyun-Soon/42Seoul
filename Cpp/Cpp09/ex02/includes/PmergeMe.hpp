#pragma once

#include <vector>
#include <string>
#include <iostream>

class PmergeMe
{
	private:
		std::vector<unsigned int> _elements;
		std::vector<unsigned int> _mainChain;
		std::vector<unsigned int> _pendingChain;

	public:
		PmergeMe();
		//PmergeMe(const PmergeMe& other);
		//PmergeMe operator=(const PmergeMe& other);
		~PmergeMe();

		void mergeInsertion(char** elements, size_t elemSize);
		int parseElements(char** elements, size_t elemSize);
		void makeChains(size_t elemSize);
};