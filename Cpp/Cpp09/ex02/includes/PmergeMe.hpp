#pragma once

#include <vector>
#include <deque>
#include <string>
#include <iostream>
#include <ctime>

#define VECTOR 1
#define DEQUE 2

typedef std::vector<unsigned int> uintVec_t;
typedef std::vector<std::vector<unsigned int> > chainsV_t;

typedef std::deque<unsigned int> uintDeq_t;
typedef std::deque<std::deque<unsigned int> > chainsD_t;


class PmergeMe
{
	private:
		PmergeMe(const PmergeMe& other);
		PmergeMe operator=(const PmergeMe& other);
		
		uintVec_t _unsortedV;
		uintVec_t _sortedV;
		uintDeq_t _unsortedD;
		uintDeq_t _sortedD;
		int _maxLevel;

	public:
		PmergeMe();
		~PmergeMe();

		//both
		int getSize();
		int getMaxLevel();
		int getJacobsthal(int n, int pendingCnt);
		void sort(int type);

		//std::vector
		void printUintVec_t();
		int parseElements(char** elements, size_t elemSize);
		void swapChain(uintVec_t& orgChain, size_t idx, size_t cmpOffset);
		void mergeInsertion(uintVec_t& orgChain, size_t truncatedChainSize, int level);
		int binarySearch(chainsV_t& mainChain, const unsigned int value, int rightLimit);
		chainsV_t binaryInsertion(uintVec_t& orgChain, size_t truncatedChainSize, size_t chainSize);

		//std::deque
		void printUintDeq_t();
		void mergeInsertion(uintDeq_t& orgChain, size_t truncatedChainSize, int level);
		void swapChain(uintDeq_t& orgChain, size_t idx, size_t cmpOffset);
		chainsD_t binaryInsertion(uintDeq_t& orgChain, size_t truncatedChainSize, size_t chainSize);
		int binarySearch(chainsD_t& mainChain, const unsigned int value, int rightLimit);
};
