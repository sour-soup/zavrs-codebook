struct twosat {
	int n;
	digraph g;
	vector<bool> vals;
	twosat(int n = 0) : n(n), g(2 * n) {
		vals.resize(n);
	}
	void either(int x, int y) {
		x = max(2 * x, -1 - 2 * x);
		y = max(2 * y, -1 - 2 * y);
		g.add_edge(x ^ 1, y);
		g.add_edge(y ^ 1, x);
	}
	void implies(int x, int y) {
		either(~x, y);
	}
	void must(int x) {
		either(x, x);
	}	
	bool solve() {
		auto comp = scc(g).comp;
		forn(i, n) {
			if (comp[2 * i] == comp[2 * i + 1])
				return false;
			vals[i] = (comp[2 * i] < comp[2 * i + 1]);
		}
		return true;
	}
};