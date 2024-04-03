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
        int _maxLevel;

	public:
		PmergeMe();
		//PmergeMe(const PmergeMe& other);
		//PmergeMe operator=(const PmergeMe& other);
		~PmergeMe();

		int sort(char** elements, size_t elemSize);
		int parseElements(char** elements, size_t elemSize);
        int getMaxLevel();
        void swapChain(chain_t& orgChain, size_t idx, size_t cmpOffset, size_t halfSize);
		void mergeInsertion(chain_t& orgChain, int level);
        void binaryInsertion(chain_t& orgChain, size_t chainSize);

		// void splitByValue();
		// void makeChains(const pChain_t& orgChain, pChain_t& mainChain, pChain_t& pendingChain);
		// size_t getInsertSize(const size_t& mainSize, const size_t& pendingSize);
		// void binaryInsertion(pChain_t& mainChain, pChain_t& pendingChain, const int& offset, const int& rightLimit);
		// int binarySearch(pChain_t& mainChain, const unsigned int& value, const int& rightLimit);
		// void binaryInsertionPendings(pChain_t& orgChain);
};