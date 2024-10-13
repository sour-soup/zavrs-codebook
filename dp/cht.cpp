struct Line {
	li k, m;
	mutable li p;
	bool operator<(const Line& o) const {
		return k < o.k;
	}
	bool operator<(const li&x) const {
		return p < x;
	}
};
template<bool GET_MAX = true>
struct LineContainer : multiset<Line, less<>> {
	// (for doubles, use inf = 1/.0, div(a,b) = a/b)
	const li inf = numeric_limits<li>::max();
	li div(li a, li b) { // floored division
		return a / b - ((a ^ b) < 0 && a % b);
	}
	bool isect(iterator x, iterator y) {
		if (y == end()) { x->p = inf; return false; }
		if (x->k == y->k) x->p = x->m > y->m ? inf : -inf;
		else x->p = div(y->m - x->m, x->k - y->k);
		return x->p >= y->p;
	}
	void add(li k, li m) {
		if(!GET_MAX) k = -k, m = -m;
		auto z = insert({k, m, 0}), y = z++, x = y;
		while (isect(y, z)) z = erase(z);
		if (x != begin() && isect(--x, y)) isect(x, y = erase(y));
		while ((y = x) != begin() && (--x)->p >= y->p)
			isect(x, erase(y));
	}
	li query(li x) {
		assert(!empty());
		auto l = *lower_bound(x);
		return (l.k * x + l.m) * (GET_MAX ? 1 : -1);
	}
};