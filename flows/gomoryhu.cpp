typedef array<ll, 3> Edge;
vector<Edge> gomoryHu(int n, vector<Edge> ed) {
	vector<Edge> tree;
	vector<int> par(n);
	fore(i, 1, n) {
		dinic D(n, i, par[i]);
		for (Edge t : ed) D.add_edge(t[0], t[1], t[2], false);
		tree.pb({i, par[i], D.calc()});
		fore(j, i + 1, n)
			if (par[j] == par[i] && D.leftOfMinCut(j)) par[j] = i;
	}
	return tree;
}