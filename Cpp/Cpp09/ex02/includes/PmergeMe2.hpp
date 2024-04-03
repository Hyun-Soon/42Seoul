#pragma once

#include <vector>
#include <string>
#include <iostream>
#include <utility>

typedef std::pair<unsigned int, unsigned int> pUintUint_t;
typedef std::vector<unsigned int> chain_t;
typedef std::vector<pUintUint_t> pChain_t;

class PmergeMe
{
	private:
		chain_t _unsorted;
		pChain_t _sorted;
		unsigned int _remainder;

	public:
		PmergeMe();
		//PmergeMe(const PmergeMe& other);
		//PmergeMe operator=(const PmergeMe& other);
		~PmergeMe();

		int sort(char** elements, size_t elemSize);
		void splitByValue();
		int parseElements(char** elements, size_t elemSize);
		void makeChains(const pChain_t& orgChain, pChain_t& mainChain, pChain_t& pendingChain);
		void mergeInsertion(pChain_t& orgChain);
		size_t getInsertSize(const size_t& mainSize, const size_t& pendingSize);
		void binaryInsertion(pChain_t& mainChain, pChain_t& pendingChain, const int& offset, const int& rightLimit);
		int binarySearch(pChain_t& mainChain, const unsigned int& value, const int& rightLimit);
		void binaryInsertionPendings(pChain_t& orgChain);
};