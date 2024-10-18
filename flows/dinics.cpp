struct edge {
	int to, cap, f;
};
int s, t;
vector<edge>ed;
vector<vector<int>>g;
vector<int>d, lst;

void add_edge(int x, int y, int cap) {
	g[x].pb((int)ed.size());
	ed.pb({ y, cap, 0 });
	g[y].pb((int)ed.size());
	ed.pb({ x, 0, 0 });
}
int res(int i) {
	return ed[i].cap - ed[i].f;
}

bool bfs() {
	d.assign(sz(g), INF);
	d[s] = 0;
	queue<int> q;
	q.push(s);
	while (!q.empty()) {
		int v = q.front();
		q.pop();
		for (int e : g[v]) {
			if (res(e) == 0) continue;
			int u = ed[e].to;
			if (d[u] > d[v] + 1) {
				d[u] = d[v] + 1;
				q.push(u);
			}
		}
	}
	return d[t] < INF;
}

int dfs(int v, int mf) {
	if (v == t) return mf;
	int sum = 0;
	for (; lst[v] < g[v].size(); lst[v]++) {
		int e = g[v][lst[v]];
		int u = ed[e].to;
		if (res(e) == 0 || d[u] != d[v] + 1) continue;
		int push = dfs(u, min(mf - sum, res(e)));
		sum += push;
		ed[e].f += push;
		ed[e ^ 1].f -= push;
		if (sum == mf) break;
	}
	return sum;
}

int dinic() {
	int flow = 0;
	while (true)
	{
		if (!bfs()) break;
		lst.assign(sz(g), 0);
		while (true)
		{
			int f = dfs(s, INF);
			if (!f) break;
			flow += f;
		}
	}
	return flow;
}