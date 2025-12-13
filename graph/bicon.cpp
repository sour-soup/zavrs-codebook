// bicone - edge, biconv - vertex
vector<vector<int>>g, h, comp;
vector<pair<int,int>> edg;
vector<int>used, lvl, up, st;
void add_comp(int sz) {
	comp.pb({});
  while(st.size() > sz){
    comp.back().pb(st.back());
    st.pop_back();
  }
}

void dfs(int v, int p = -1) {
	used[v] = true;
	up[v] = lvl[v];
	st.pb(v); // bicone
	for (int i : g[v]) {
		auto &e = edg[i];
		int u = e.first ^ e.second ^ v;
		if (u == p) continue;
		// bicone
		if (!used[u]) {
			int t = sz(st);
      lvl[u] = lvl[v] + 1;
			dfs(u, v);
			up[v] = min(up[v], up[u]);
			if (up[u] > lvl[v])
				add_comp(t);
		} else {
			up[v] = min(up[v], lvl[u]);
		}
		// biconv
		if (!used[u]) {
			int t = sz(st);
      lvl[u] = lvl[v] + 1;
			st.pb(i);
			dfs(u, v);
			up[v] = min(up[v], up[u]);
			if (up[u] >= lvl[v])
				add_comp(t);
		} else {
			if (lvl[u] < lvl[v])	
				st.pb(i);
			up[v] = min(up[v], lvl[u]);
		}
	}
	// bicone
	if (p == -1) add_comp(0);
	// biconv
	if (p == -1 && sz(st) > 0) add_comp(0);
}
// Block-cut tree work with biconv
void build(){
  h.resize(n + comp.size());
  used.assign(n + comp.size(), 0);
	int last = n;
	for (auto c : comp){
		for (int i : c){
			used[edg[i].first] = 1;
			used[edg[i].second] = 1;
		}
		for (int i : c){
			if (used[edg[i].first]){
				h[last].pb(edg[i].first);
				used[edg[i].first] = 0;
			}
			if (used[edg[i].second]){
				h[last].pb(edg[i].second);
				used[edg[i].second] = 0;
			}
		}
		++last;
	}
}