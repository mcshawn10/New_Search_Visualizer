#include "PQ.h"
#include "Cell.h"


bool PQ::operator(Cell* const& c1, Cell* const& c2)
{
	return c1.height < c2.height;
}

bool PQ::remove(const T& value)
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