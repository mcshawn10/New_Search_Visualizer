#pragma once

#include "stl_inc.h"
#include <queue>
#include <set>

template<typename T>
class PQ : public std::priority_queue<T, vector<T>> {
public:

	bool remove(const T& value)
	{

		auto it = std::find(this->c.begin(), this->c.end(), value);

		if (it == this->c.end()) return false;

		if (it == this->c.begin()) this->pop();
		
		else {
			this->c.erase(it);
			std::make_heap(this->c.begin(), this->c.end(), this->comp);
		}

		return true;
	}
};