template<typename T, typename C> struct mincost {
	const C MAX_COST = numeric_limits<C>::max();

	struct edge {
		int u, rev;
		T cap, flow;
		C cost;
	};
	int n, s, t;
	T flow;
	C cost;
	vector<edge*> p;
	vector<C> d;
	vector<bool> inq;
	vector<vector<edge>> g;
	
	mincost() {}
	mincost(int n, int s, int t) : n(n), s(s), t(t) {
		g.resize(n);
		d.resize(n);
		p.resize(n);
		inq.resize(n);
		flow = 0;
		cost = 0;
	}
	void add_edge(int v, int u, T cap, C cost) {
		g[v].pb({u, sz(g[u]), cap, 0, cost});
		g[u].pb({v, sz(g[v]) - 1, 0, 0, -cost});
	}
	T push(T lim) {
		fill(all(d), MAX_COST);
		d[s] = 0;
		queue<int> q({s});
		while (!q.empty()) {
			int v = q.front(); q.pop();
			inq[v] = false;
			for (auto& e : g[v]) {
				int u = e.u;
				if (e.cap > e.flow && d[u] > d[v] + e.cost) {
					d[u] = d[v] + e.cost;
					p[u] = &e;
					if (!inq[u]) {
						inq[u] = true;
						q.push(u);
					}
				}
			}
		}
		if (d[t] == MAX_COST) {
			return 0;
		}
		T cur_flow = lim;
		int v = t;
		while (v != s) {
			auto e = *p[v];
			cur_flow = min(cur_flow, e.cap - e.flow);
			v = g[v][e.rev].u;
		}
		v = t;
		while (v != s) {
			auto e = *p[v];
			p[v]->flow += cur_flow;
			g[v][e.rev].flow -= cur_flow;
			v = g[v][e.rev].u;
		}
		return cur_flow;
	}
	void calc(T k = numeric_limits<T>::max()) {
		T add = 0;
		while ((add = push(k - flow)) > 0) {
			flow += add;
			cost += d[t] * add;
		}
	}
};