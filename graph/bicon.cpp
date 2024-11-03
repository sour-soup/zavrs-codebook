// bicone - edge, biconv - vertex
vector<vector<int>>g, h, comp;
vector<pair<int,int>> edg;
vector<int>used, lvl, f, st;
void add_comp(int sz) {
	comp.pb({});
  while(st.size() > sz){
    comp.back().pb(st.back());
    st.pop_back();
}}

void dfs(int v, int p = -1) {
	used[v] = true;
	up[v] = lvl[v];
  st.pb(v); //bicone
	for (int i : g[v]){
    int u = edg[i].first ^ edg[i].second ^ v;
    if (u == p) continue;
    if (!used[u]) { //bicone
				int sz = st.size();
        lvl[u] = lvl[v] + 1;
				dfs(u, v);
				up[v] = min(up[v], up[u]);
				if (fup[u] > tin[v])
					add_comp(sz);
			} else {
				up[v] = min(up[v], lvl[u]);
			} 
    if (!used[u]){ // biconv
      int sz = st.size();
      lvl[u] = lvl[v] + 1;
      st.pb(i);
      dfs(u, v);
      up[u] = min(up[u], up[v]);
      if (up[u] >= lvl[v]){ add_comp(sz);
      }else{
      if (lvl[u] < lvl[v]) st.pb(i);
      up[v] = min(up[v], lvl[u]);
      }
  }
  if (p == -1 && !st.empty()) add_comp(0);
}