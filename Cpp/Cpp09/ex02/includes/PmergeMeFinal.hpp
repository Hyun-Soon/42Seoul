#pragma once

#include <vector>
#include <string>
#include <iostream>

typedef std::vector<unsigned int> uintVec_t;
typedef std::vector<std::vector<unsigned int> > chains_t;

class PmergeMe
{
	private:
		uintVec_t _unsorted;
		uintVec_t _sorted;
		int _maxLevel;

	public:
		PmergeMe();
		//PmergeMe(const PmergeMe& other);
		//PmergeMe operator=(const PmergeMe& other);
		~PmergeMe();

		int sort(char** elements, size_t elemSize);
		int parseElements(char** elements, size_t elemSize);
		int getMaxLevel();
		void swapChain(uintVec_t& orgChain, size_t idx, size_t cmpOffset);
		void mergeInsertion(uintVec_t& orgChain, size_t truncatedChainSize, int level);
		int binarySearch(chains_t& mainChain, const unsigned int value, int rightLimit);
		int getJacobsthal(int n, int pendingCnt);
		chains_t binaryInsertion(uintVec_t& orgChain, size_t truncatedChainSize, size_t chainSize);
};
