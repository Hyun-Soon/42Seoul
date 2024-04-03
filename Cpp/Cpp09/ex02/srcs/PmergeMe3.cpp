#include "PmergeMe3.hpp"

//debug
// void printPChain_t(std::string msg, pChain_t& v)
// {
// 	std::cout << msg << " : ";
// 	for (size_t i = 0; i < v.size(); i++)
// 		std::cout << "{" << v[i].first << ", " << v[i].second << "} ";
// 	std::cout << std::endl;	
// }

void printChain_t(std::string msg, chain_t v)
{
	std::cout << msg << " : ";
	for (size_t i = 0; i < v.size(); i++)
		std::cout << v[i] << " ";
	std::cout << std::endl;	
}

PmergeMe::PmergeMe() {}

//TODO :: implement here
//PmergeMe::PmergeMe(const PmergeMe &other)
//{}

//PmergeMe PmergeMe::operator=(const PmergeMe &other)
//{}

PmergeMe::~PmergeMe() {}

void PmergeMe::swapChain(chain_t& orgChain, size_t idx, size_t cmpOffset, size_t halfSize)
{
    unsigned int temp;

    for (size_t i = 0; i < halfSize; i++)
    {
        temp = orgChain[idx];
        orgChain[idx] = orgChain[idx + cmpOffset];
        orgChain[idx + cmpOffset] = temp;
        ++idx;
    }
}

void PmergeMe::binaryInsertion(chain_t& orgChain, size_t chainSize)
{
    (void)orgChain;
    (void)chainSize;
    //TODO :: implement here
    // 팬딩체인 정렬될 때까지 야콥스탈 수 얻어다가 하기

}

void PmergeMe::mergeInsertion(chain_t& orgChain, int level)
{
    //1. 메인, 팬딩 체인을 나눈다(크기 비교).
    //2. 다음 mergeInsertion으로 들어가서 메인, 팬딩 체인을 나눈다.(사이즈 2배)
    //3. max level에 도달하면 탈출한다.
    //4. 야콥스탈 수를 따라 이진 삽입을 시작한다.

    if (level == _maxLevel)
        return ;
    // std::cout << "정렬" << std::endl;
    size_t cmpOffset = pow(2, level - 1);
    size_t chainSize = cmpOffset * 2; //만들려는 체인의 사이즈
    size_t iter = orgChain.size() / chainSize;
    // std::cout << "iter : " << iter << std::endl;
    for (size_t i = 0; i < iter; i++)
    {
        size_t idx = i * chainSize;
        if (orgChain[idx] < orgChain[idx + cmpOffset])
            swapChain(orgChain, idx, cmpOffset, chainSize / 2);
    }
    printChain_t("merge", orgChain);
    mergeInsertion(orgChain, level + 1);

    std::cout << "cmpOffset : " << cmpOffset << std::endl;
    std::cout << "chainSize : " << chainSize << std::endl;
    // binaryInsertion(orgChain, chainSize);
}

int PmergeMe::getMaxLevel()
{//8 -> 4, 7 -> 3
    size_t ret = 1;
    int cnt = 0;
    while (ret <= _unsorted.size())
    {
        ret *= 2;
        ++cnt;
    }
    return cnt;
}

int PmergeMe::sort(char** elements, size_t elemSize)
{
	if (parseElements(elements, elemSize) == 1)
		return 1;

    _maxLevel = getMaxLevel();
	mergeInsertion(_unsorted, 1);







	// if (_remainder)
	// 	_sorted.push_back(std::pair<unsigned int, unsigned int>(0, _remainder));
	// //printPChain_t("first sort result", _sorted);	
	// binaryInsertionPendings(_sorted);

	// std::cout << std::endl;
	// std::cout << "Sort Result : ";
	// size_t end = (_remainder ? _sorted.size() - 1 : _sorted.size());
	// for (size_t i = 0; i < end; i++)
	// 	if (_sorted[i].first != 0)
	// 		std::cout << _sorted[i].first << " ";
	// std::cout << std::endl;
	return 0;
}

int PmergeMe::parseElements(char** elements, size_t elemSize)
{
	double temp;

	for (size_t i = 0; i < elemSize; i++)
	{
		temp = strtod(elements[i], NULL);
		if (temp <= 0.0 || temp != temp || temp > INT_MAX)
			return 1;
		_unsorted.push_back(temp);
	}
	return 0;
}

// void PmergeMe::splitByValue()
// {
// 	size_t halfSize = _unsorted.size() / 2;
// 	for (size_t i = 0; i < halfSize; i++)
// 	{
// 		unsigned int large = std::max(_unsorted[i], _unsorted[i + halfSize]);
// 		unsigned int small = std::min(_unsorted[i], _unsorted[i + halfSize]);

// 		_sorted.push_back(std::pair<unsigned int, unsigned int>(large, small));
// 	}
// 	if (_unsorted.size() % 2 == 1)
// 		_remainder = _unsorted.back();
// }

// void PmergeMe::makeChains(const pChain_t& orgChain, pChain_t& mainChain, pChain_t& pendingChain)
// {
// 	size_t halfSize = orgChain.size() / 2;
// 	for (size_t i = 0; i < halfSize; i++)
// 	{
// 		pUintUint_t large = (orgChain[i].first >= orgChain[i + halfSize].first ? orgChain[i] : orgChain[i + halfSize]);
// 		pUintUint_t small = (orgChain[i].first >= orgChain[i + halfSize].first ? orgChain[i + halfSize] : orgChain[i]);

// 		mainChain.push_back(large);
// 		pendingChain.push_back(small);
// 	}
// 	if (orgChain.size() % 2 == 1)
// 		pendingChain.push_back(orgChain.back());
// }



// size_t PmergeMe::getInsertSize(const size_t& mainSize, const size_t& pendingSize)
// {
// 	size_t jacobsthal = 0;
// 	size_t ret;
// 	int n = 1;

// 	while (jacobsthal <= mainSize)
// 	{
// 		jacobsthal = (pow(2, n) - pow(-1, n)) / 3;
// 		++n;
// 	}
// 	//debug
// 	//std::cout << "inside jacob : " << jacobsthal << std::endl;
// 	ret = jacobsthal - mainSize;
// 	return (ret <= pendingSize ? ret : pendingSize);
// }

// int PmergeMe::binarySearch(pChain_t& mainChain, const unsigned int& value, const int& rightLimit)
// {
// 	int left = 0;
// 	int right = rightLimit;
// 	int mid;

// 	//std::cout << "rightlimit : " << rightLimit << std::endl;
// 	while (left <= right)
// 	{
// 		mid = (left + right) / 2;
// 		if (value > mainChain[mid].first)
// 			left = mid + 1;
// 		else
// 			right = mid - 1;
// 	}
// 	//std::cout << "ret : " << left << std::endl;
// 	return left;
// }

// void PmergeMe::binaryInsertion(pChain_t& mainChain, pChain_t& pendingChain, const int& offset, const int& rightLimit)
// {
// 	int insertPos = binarySearch(mainChain, pendingChain[offset].first, rightLimit);
// 	mainChain.insert(mainChain.begin() + insertPos, pendingChain[offset]);
// 	//printPChain_t("insertionING : ", mainChain);
// }

// void PmergeMe::binaryInsertionPendings(pChain_t& orgChain)
// {
// 	//TODO :: apply Jacobsthal
// 	pChain_t temp = orgChain;
// 	int repeat = orgChain.size() - 1;
// 	for (; repeat >= 0; repeat--)
// 	{
// 		int right = (_remainder ? temp.size() - 2 : temp.size() - 1);
// 		//std::cout << "repeat : " << repeat << std::endl;
// 		int left = 0;
// 		int mid;

// 		//std::cout << "rightlimit : " << rightLimit << std::endl;
// 		while (left <= right)
// 		{
// 			mid = (left + right) / 2;
// 			//std::cout << "temp[repeat] : " << temp[repeat].second << std::endl;
// 			if (temp[repeat].second > orgChain[mid].first)
// 				left = mid + 1;
// 			else
// 				right = mid - 1;
// 		}
// 		orgChain.insert(orgChain.begin() + left, std::pair<unsigned int, unsigned int>(temp[repeat].second, 0));
// 		//printPChain_t("ret : ", orgChain);
// 	}
// }

// void PmergeMe::mergeInsertion(chain_t& orgChain)
// {
// 	//TODO :: 1. swap pendingChain too
// 	//TODO :: 2. modify getInsertSize
// 	// remain pendings = present size - half size;
// 	pChain_t mainChain;
// 	pChain_t pendingChain;

// 	if (orgChain.size() == 1)
// 		return ;
// 	makeChains(orgChain, mainChain, pendingChain);
// 	mergeInsertion(mainChain);

// 	//debug
// 	//std::cout << std::endl;
// 	//printPChain_t("orgChain", orgChain);
// 	//printPChain_t("mainChain", mainChain);
// 	//printPChain_t("pendingChain", pendingChain);

// 	while (pendingChain.size())
// 	{
// 		const int rightLimit = mainChain.size() - 1; //TODO::is it correct??? ㅇㅑ코ㅂ스탈 수열이 필요없다고 한 이유가 혹시 자기 메인체인 앞에값까지만 비교하면 어차피 비교횟수 최대 n이 보장되기 때문인가?
// 		int insertSize = getInsertSize(mainChain.size(), pendingChain.size());
// 		int offset = insertSize - 1;

// 		//deubg
// 		//std::cout << "insertSize : " << insertSize << std::endl;
// 		for (; offset >= 0; offset--)
// 			binaryInsertion(mainChain, pendingChain, offset, rightLimit);

// 		pendingChain.erase(pendingChain.begin(), pendingChain.begin() + insertSize);

// 		//printPChain_t("mainChain here", mainChain);
// 		//printPChain_t("pendingChain here", pendingChain);
// 	}

// 	orgChain = mainChain;
// }