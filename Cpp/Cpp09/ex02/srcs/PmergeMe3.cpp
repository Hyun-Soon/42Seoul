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

void PmergeMe::swapChain(chain_t& orgChain, size_t idx, size_t cmpOffset)
{
    unsigned int temp;

    for (size_t i = 0; i < cmpOffset; i++)
    {
        temp = orgChain[idx];
        orgChain[idx] = orgChain[idx + cmpOffset];
        orgChain[idx + cmpOffset] = temp;
        ++idx;
    }
}

 int PmergeMe::binarySearch(chain_t& orgChain, const unsigned int value, int rightLimit, int pendingSize)
 {
 	int left = 0;
 	int right = rightLimit;
 	int mid;

 	//std::cout << "rightlimit : " << rightLimit << std::endl;
 	while (left <= right)
 	{
 		mid = (left + right) / 2;
 		if (value > orgChain[mid])
 			left = mid + pendingSize;
 		else
 			right = mid - pendingSize;
 	}
 	//std::cout << "ret : " << left << std::endl;
 	return left;
 }

void PmergeMe::insertChain(chain_t& mainChain, chain_t& orgChain, int insertPos, int pendingSize, int presentPendingIdx)
{
	//for (int i = 0; i < pendingSize; i++)
	//{
	mainChain.insert(mainChain.begin() + insertPos, orgChain.begin() + presentPendingIdx, orgChain.begin() + presentPendingIdx + pendingSize);
	//}
}

chain_t PmergeMe::binaryInsertion(chain_t& orgChain, int pairedPendingCnt, int remainPendingCnt, size_t pendingSize)
{
    // 팬딩체인 정렬될 때까지 야콥스탈 수 얻어다가 하기
	//(void)orgChain;
	//(void)chainSize;
	int n = 1;
	//int pendingCnt = orgChain.size() / chainSize;
	int jacobsthal = -1;
	int beforeJacobsthal = 0;
	int totalpendingCnt = pairedPendingCnt + remainPendingCnt;
	chain_t mainChain;
	for (int i = 0; i < pairedPendingCnt; i++)
		for (size_t j = 0; j < pendingSize; j++)
			mainChain.push_back(orgChain[i * pendingSize * 2 + j]);

	//std::cout << "------binary Insertion ------" << std::endl;

	int rightLimitCnt = 1;
	int insertRemainCnt = 0;
	while (jacobsthal != totalpendingCnt)
	{
		printChain_t("mainChain", mainChain);
		jacobsthal = getJacobsthal(++n, totalpendingCnt);
		//std::cout << "jacobsthal : " << jacobsthal << std::endl;

		for (int i = jacobsthal; i > beforeJacobsthal; i--)
		{
			//std::cout << "idx : " << i << std::endl;
			int presentPendingIdx;
			if (i <= pairedPendingCnt)
				presentPendingIdx = (i - 1) * pendingSize * 2 + pendingSize; // == 2i * pendingSize - pendingSize; == pendingSize * (2i - 1);
			else
			{
				presentPendingIdx = pairedPendingCnt * 2 * pendingSize + (i - pairedPendingCnt - 1) * pendingSize;
				++insertRemainCnt;
			}
			std::cout << "presentPendingIdx : " << presentPendingIdx << std::endl;
			std::cout << "present pending head : " << orgChain[presentPendingIdx] << std::endl;
			int insertPos = binarySearch(mainChain, orgChain[presentPendingIdx], pendingSize * (i - 1) + pendingSize * insertRemainCnt, pendingSize); // TODO :: find proper rightLimit
			//int insertPos = binarySearch(mainChain, orgChain[presentPendingIdx], insertCnt + i - 1, pendingSize);
			//std::cout << "insertPos : " << insertPos << std::endl;
			insertChain(mainChain, orgChain, insertPos, pendingSize, presentPendingIdx);
			//printChain_t("inserted mainChain", mainChain);
		}
		beforeJacobsthal = jacobsthal;
		++rightLimitCnt;
		//++insertCnt;
		//std::cout << "new Jacobsthal " << std::endl; 2 1 4 3 8 7
	}

	//printChain_t("after mainChain", mainChain);
	//std::cout << "=====end=====" << std::endl;

	return mainChain;
}

int PmergeMe::getJacobsthal(int n, int pendingCnt)
{	
	int jacobsthal = (pow(2, n) - pow(-1, n)) / 3;
	//debug
	//std::cout << "inside jacob : " << jacobsthal << std::endl;
	return (jacobsthal <= pendingCnt ? jacobsthal : pendingCnt);
}

void PmergeMe::mergeInsertion(chain_t& orgChain, int level)
{
    //1. 메인, 팬딩 체인을 나눈다(크기 비교).
    //2. 다음 mergeInsertion으로 들어가서 메인, 팬딩 체인을 나눈다.(사이즈 2배)
    //3. max level에 도달하면 탈출한다.
    //4. 야콥스탈 수를 따라 이진 삽입을 시작한다.

    if (level == _maxLevel)
        return ;

    size_t cmpOffset = pow(2, level - 1);
    size_t chainSize = cmpOffset * 2; //만들려는 체인의 사이즈
    size_t iteration = orgChain.size() / chainSize;
	//int remainder = ((orgChain.size() / chainSize) % 2) * chainSize + orgChain.size() % chainSize;
	int remainder = orgChain.size() % chainSize;



    for (size_t i = 0; i < iteration; i++)
    {
        size_t idx = i * chainSize;
        if (orgChain[idx] < orgChain[idx + cmpOffset])
            swapChain(orgChain, idx, cmpOffset);
    }

	std::cout << "level : " << level << std::endl;
    printChain_t("merge", orgChain);
	std::cout << std::endl;
	//std::cout << "remainder : " << remainder << std::endl;
    //std::cout << "cmpOffset : " << cmpOffset << std::endl;
    //std::cout << "chainSize : " << chainSize << std::endl;

	chain_t nextChain;
	size_t nextChainSize = orgChain.size() - remainder;
	for (size_t i = 0; i < nextChainSize; i++)
		nextChain.push_back(orgChain[i]);

	mergeInsertion(nextChain, level + 1);

	std::cout << std::endl;
	std::cout << "level : " << level << std::endl;
	for (size_t idx = nextChainSize; idx < orgChain.size(); idx++)
		nextChain.push_back(orgChain[idx]);
	printChain_t("before insertion", nextChain);
	nextChain = binaryInsertion(orgChain, orgChain.size() / chainSize, remainder / cmpOffset, cmpOffset);
	//std::cout << "Warning!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!" << std::endl;
	printChain_t("after insertion", nextChain);
	orgChain = nextChain;
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



//(0 ,2^n -1)




//5 1 4 3 10 9 8 7 18 17
//4 3 5 1 10 9      8 7 18 17


//1 3 2 5 4 11 10 9 8 7 6

//실제 삽입한 원소 수 + 자기 인덱스 - 1= 탐색 범위의 끝

//1 - >0 / 3 -> 1 + 2 = 3 / 2 -> 2 + 2 - 1 = 3


//9
