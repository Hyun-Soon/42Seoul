#pragma once

#include <algorithm>

template<typename T>
typename T::iterator easyfind(T& t, int target)
{
	return find(t.begin(), t.end(), target);
}