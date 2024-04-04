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
		void swapChain(chain_t& orgChain, size_t idx, size_t cmpOffset);
		void mergeInsertion(chain_t& orgChain, int level);
		void insertChain(chain_t& mainChain, chain_t& orgChain, int insertPos, int pendingSize, int presentPendingIdx);
		int binarySearch(chain_t& orgChain, const unsigned int value, int rightLimit, int pendingSize);
		chain_t binaryInsertion(chain_t& orgChain, int pairedPendingCnt, int remainPendingCnt, size_t pendingSize);
		int getJacobsthal(int n, int pendingCnt);
};