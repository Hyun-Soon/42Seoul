#pragma once

#include <vector>
#include <deque>
#include <string>
#include <iostream>
#include <ctime>

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

		//both
		int getSize();
		int getMaxLevel();
		int getJacobsthal(int n, int pendingCnt);
		int sort(char** elements, size_t elemSize);

		//std::vector
		int parseElements(char** elements, size_t elemSize);
		void swapChain(uintVec_t& orgChain, size_t idx, size_t cmpOffset);
		void mergeInsertion(uintVec_t& orgChain, size_t truncatedChainSize, int level);
		int binarySearch(chains_t& mainChain, const unsigned int value, int rightLimit);
		chains_t binaryInsertion(uintVec_t& orgChain, size_t truncatedChainSize, size_t chainSize);

		//std::deque

};
