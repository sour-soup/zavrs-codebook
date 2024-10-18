vector<vector<int>>g, gt;
vector<int>used;
vector<int>order;
vector<int>color;
void add_or(int x, int y) {
	g[x ^ 1].pb(y);
	g[y ^ 1].pb(x);
	gt[y].pb(x ^ 1);
	gt[x].pb(y ^ 1);
}
void add_im(int x, int y) {
	add_or(x ^ 1, y);
}
void add_xor0(int u, int v) {
	add_or(2 * u, 2 * v + 1);
	add_or(2 * u + 1, 2 * v);
}
void add_xor1(int u, int v) {
	add_or(2 * u, 2 * v);
	add_or(2 * u + 1, 2 * v + 1);
}
void topsort(int x) {
	used[x] = true;
	for (auto y : g[x])
		if (!used[y]) topsort(y);
	order.pb(x);
}
void css(int x, int col) {
	color[x] = col;
	for (auto y : gt[x]) {
		if (!color[y]) css(y, col);
	}
}

void init(int n) {
	order.clear();
	g.assign(2 * n, {});
	gt.assign(2 * n, {});
	used.assign(2 * n, 0);
	color.assign(2 * n, 0);
}
int32_t main() {
	/// строим граф ///
	forn(i, 2 * n) if (!used[i]) {
		topsort(i);
	}
	reverse(all(order));
	int col = 1;
	for (auto x : order) if (!color[x]) {
		css(x, col++);
	}
	forn(i, n) {
		if (color[2 * i] == color[2 * i + 1]) {
			cout << "FALSE" << endl;
			return;
		}
		// нужно перебрать < и > //
	}
}