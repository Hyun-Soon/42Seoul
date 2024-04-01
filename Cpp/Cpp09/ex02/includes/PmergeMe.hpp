#pragma once

#include <vector>
#include <string>
#include <iostream>

typedef std::vector<unsigned int> chain_t;

class PmergeMe
{
	private:
		chain_t _unsorted;
		chain_t _sorted;
		//chain_t _mainChain;
		//chain_t _pendingChain;

	public:
		PmergeMe();
		//PmergeMe(const PmergeMe& other);
		//PmergeMe operator=(const PmergeMe& other);
		~PmergeMe();

		int sort(char** elements, size_t elemSize);
		int parseElements(char** elements, size_t elemSize);
		void makeChains(const chain_t& orgChain, chain_t& mainChain, chain_t& pendingChain);
		void mergeInsertion(chain_t& chain);
};