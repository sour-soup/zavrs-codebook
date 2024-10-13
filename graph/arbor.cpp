struct edge {
	int x, y, w, id;
};

int relax(int v, vector<vector<int>>& g, vector<pt>& in) {
	int& ans = in[v].x;
	if (ans != -1)
		return ans;
	ans = in[v].y;
	for (auto u : g[v])
		ans ^= relax(u, g, in);
	return ans;
}

vector<int> arborescence(int root, int n, vector<edge> e) {
	vector<pt> in(sz(e), mp(-1, 0));
	vector<vector<int>> g(sz(e));
	vector<bool> rem(n, true);
	
	rem[root] = false;
	forn(i, sz(e)) e[i].id = i;
	
	while (true) {
		vector<int> p(n, -1), pw(n, INF);
		forn(i, sz(e)) {
			int v = e[i].y;
			if (v != root && pw[v] > e[i].w) {
				pw[v] = e[i].w;
				p[v] = i;
			}
		}
		
		forn(i, n) if (rem[i] && p[i] == -1)
			return vector<int>();
			
		int c = 0;
		vector<int> cycle, comp(n, -1);
		forn(i, n) {
			if (comp[i] == -1) {
				int v = i;
				while (v != -1 && comp[v] == -1) {
					cycle.pb(v);
					comp[v] = c;
					v = p[v] == -1 ? -1 : e[p[v]].x;
				}
				if (v != -1 && comp[v] == c) {
					int idx = find(all(cycle), v) - cycle.begin();
					forn(j, idx) comp[cycle[j]] = -1;
					cycle.erase(cycle.begin(), cycle.begin() + idx);
					break;
				}
				cycle.clear();
				c++;
			}
		}
		
		if (cycle.empty()) {
			forn(i, n) if (p[i] != -1)
				in[e[p[i]].id].y ^= 1;
			break;
		}
		
		int mv = INF, mp = -1;
		forn(i, sz(cycle)) {
			edge& cure = e[p[cycle[i]]];
			in[cure.id].y ^= 1;
			if (mv > cure.w) {
				mv = cure.w;
				mp = cure.id;
			}
			rem[cycle[i]] = (i == 0);
		}
		in[mp].y ^= 1;
		forn(i, sz(e)) if (comp[e[i].x] != c || comp[e[i].y] != c) {
			if (comp[e[i].y] == c) {
				e[i].w -= pw[e[i].y];
				e[i].w += mv;
				g[e[p[e[i].y]].id].pb(e[i].id);
				g[mp].pb(e[i].id);
			}
			if (comp[e[i].x] == c) e[i].x = cycle[0];
			if (comp[e[i].y] == c) e[i].y = cycle[0];
		}
		forn(i, sz(e)) {
			if (comp[e[i].x] == c && comp[e[i].y] == c) {
				swap(e[i], e.back());
				e.pop_back();
				i--;
			}
		}
	}
	
	vector<int> res;
	forn(i, sz(in)) if (relax(i, g, in))
		res.pb(i);
		
	return res;
}