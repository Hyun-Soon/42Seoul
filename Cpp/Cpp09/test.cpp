#include <vector>
#include <iostream>

using namespace std;

int main()
{
	vector<unsigned int> uintv;
	uintv.push_back(1);
	vector<unsigned int> uintv2;
	uintv.push_back(2);
	vector<unsigned int> uintv3;
	uintv.push_back(3);

	vector<vector<unsigned int> > chains;
	chains.push_back(uintv);
	chains.push_back(uintv2);
	chains.push_back(uintv3);

	vector<vector<unsigned int>::iterator> itVec;
	itVec.push_back(chains.begin() + 1);
}