template<typename T>
struct lichao_tree {
	int n;
	vector<pair<T, T>> lines;
	lichao_tree(int n): n(n) {
		lines.resize(4 * n, {0, -numeric_limits<T>::max()});
	}
	inline T eval(pair<T, T> line, int x) {
		return line.x * x + line.y;
	}
	void add_line(int v, int l, int r, pair<T, T> cur) {
		int m = (l + r) >> 1;
		bool lft = eval(cur, l) > eval(lines[v], l);
		bool mid = eval(cur, m) > eval(lines[v], m);
		if (mid) swap(lines[v], cur);
		if (l + 1 == r) return;
		else if (lft != mid) add_line(v * 2 + 1, l, m, cur);
		else add_line(v * 2 + 2, m, r, cur);
	}
	void add_line(pair<T, T> cur) {
		add_line(0, 0, n, cur);
	}
	T get(int v, int l, int r, int x) {
		T res = eval(lines[v], x);
		if (l + 1 == r) return res;
		int m = (l + r) >> 1;
		if (x < m) return max(res, get(v * 2 + 1, l, m, x));
		else return max(res, get(v * 2 + 2, m, r, x));
	}
	T get(int x) {
		return get(0, 0, n, x);
	}
};