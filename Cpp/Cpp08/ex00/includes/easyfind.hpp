#pragma once

template<typename T>
typename T::iterator easyfind(T& t, int target)
{
	typename T::iterator it = t.begin();

	for (; it != t.end(); ++it)
		if (*it == target)
			break;
	return it;
}