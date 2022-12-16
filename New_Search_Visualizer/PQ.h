#pragma once


#include "stl_inc.h"
#include <queue>
#include <set>

template<typename T>
class PQ : public std::priority_queue<T, vector<T>> {
public:
	PQ();
	bool operator()(Cell* const& c1, Cell* const& c2);
}
	bool remove(const T& value);

	~PQ();
	
};

template<typename T>
inline bool PQ<T>::operator()(Cell* const& c1, Cell* const& c2)
{
	return false;
}
