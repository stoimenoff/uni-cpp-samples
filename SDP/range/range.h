#ifndef _RANGE_H_
#define _RANGE_H_

#include <cmath>
using std::abs;

class range
{
	class range_iterator
	{
		private:
			int n;
			int step;
		public:
			range_iterator(int n) : n(n), step(1) {}
			range_iterator(int n, int step) : n(n), step(step) {}
			int operator*() const
			{
				return n;
			}
			range_iterator& operator++()
			{
				n += step;
				return *this;
			}
			range_iterator operator++(int)
			{
				n += step;
				return *this;
			}
			bool operator==(const range_iterator &other) const
			{
				return n == other.n;
			}
			bool operator!=(const range_iterator &other) const
			{
				return !(*this == other);
			}

	};

	private:
		int from;
		int to;
		int step;
	public:
		range(int to) : from(0), to(to), step(1) {}
		range(int from, int to) : from(from), to(to), step(1) {}
		range(int from, int to, int step) : from(from), to(to), step(step) {}
		range_iterator begin() const
		{
			return range_iterator(from, step);
		}

		range_iterator end() const
		{
			int span = abs(to - from);
			return range_iterator((span % step == 0) ? to : from + (abs(span/step) + 1) * step);
		}


};

#endif
