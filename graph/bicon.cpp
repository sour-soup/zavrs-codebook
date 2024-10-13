struct bicone {
	const undigraph &g;
	vector<bool> used;
	int T;
	vector<int> tin, fup;
	int comps_count;
	vector<int> st, comp;

	bicone(const undigraph& g) : g(g) {
		used.resize(g.n, 0);
		T = 0;
		tin.resize(g.n);
		fup.resize(g.n);
		comps_count = 0;
		// bicone
		comp.resize(g.n);
		// biconv
		comp.resize(sz(g.edges));
		forn(v, g.n) if (!used[v]) 
			dfs(v);
	}
	
	void add_comp(int t) {
		while (sz(st) != t) {
			comp[st.back()] = comps_count;
			st.pop_back();
		}
		++comps_count;
	}
	
	void dfs(int v, int p = -1) {
		used[v] = true;
		tin[v] = fup[v] = T++;
		st.pb(v);
		for (int i : g[v]) {
			auto &e = g.edges[i];
			int u = e.v ^ e.u ^ v;
			if (u == p) continue;
			// bicone
			if (!used[u]) {
				int t = sz(st);
				dfs(u, v);
				fup[v] = min(fup[v], fup[u]);
				if (fup[u] > tin[v])
					add_comp(t);
			} else {
				fup[v] = min(fup[v], tin[u]);
			}
			// biconv
			if (!used[u]) {
				int t = sz(st);
				st.pb(i);
				dfs(u, v);
				fup[v] = min(fup[v], fup[u]);
				if (fup[u] >= tin[v])
					add_comp(t);
			} else {
				if (tin[u] < tin[v])	
					st.pb(i);
				fup[v] = min(fup[v], tin[u]);
			}
		}
		// bicone
		if (p == -1) add_comp(0);
		// biconv
		if (p == -1 && sz(st) > 0) add_comp(0);
	}
};