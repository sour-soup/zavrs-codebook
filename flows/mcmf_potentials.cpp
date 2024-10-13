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
	vector<C> d, add;
	vector<bool> inq;
	vector<vector<edge>> g;
	
	mincost() {}
	mincost(int n, int s, int t) : n(n), s(s), t(t) {
		g.resize(n);
		d.resize(n);
		add.resize(n);
		p.resize(n);
		inq.resize(n);
		flow = 0;
		cost = 0;
	}
	void add_edge(int v, int u, T cap, C cost) {
		g[v].pb({u, sz(g[u]), cap, 0, cost});
		g[u].pb({v, sz(g[v]) - 1, 0, 0, -cost});
	}
	void init_dag() {
		fill(all(add), MAX_COST);
		vector<int> ind(n);
		queue<int> q({s});
		forn(v, n) for (auto& e : g[v]) {
			if (e.cap > e.flow)
				++ind[e.u];
		}
		add[s] = 0;
		while (!q.empty()) {
			int v = q.front(); q.pop();
			for (auto& e : g[v]) {
				int u = e.u;
				if (e.cap > e.flow) {
					add[u] = min(add[u], add[v] + e.cost);
					--ind[u];
					if (ind[u] == 0)
						q.push(u);
				}
			}
		}
	}
	void init_fb() {
		fill(all(add), MAX_COST);
		add[s] = 0;
		forn(_, n - 1) {
			forn(v, n) for (auto& e : g[v]) {
				add[e.u] = min(add[e.u], add[v] + e.cost);
			}
		}
	}
	T push(T lim) {
		fill(all(d), MAX_COST);
		d[s] = 0;
		priority_queue<pair<C, int>> q;
		q.push({-d[s], s});
		while (!q.empty()) {
			int v = q.top().y;
			C curd = -q.top().x;
			q.pop();	
			if (curd > d[v])
				continue;
			for (auto& e : g[v]) {
				int u = e.u;
				C w = e.cost + add[v] - add[u];
				if (e.cap > e.flow && d[u] > d[v] + w) {
					d[u] = d[v] + w;
					p[u] = &e;
					q.push({-d[u], u});
				}
			}
		}
		forn(v, n) {
			add[v] += d[v];
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
		T add_flow = 0;
		while ((add_flow = push(k - flow)) > 0) {
			flow += add_flow;
			cost += (add[t] - add[s]) * add_flow;
		}
	}
};
