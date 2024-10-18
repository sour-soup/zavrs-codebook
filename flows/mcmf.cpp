struct edge {
	int to, cap, f, cost;
};
int s, t;
vector<edge>ed;
vector<vector<int>>g;
vector<int>p, pe;
vector<int>d;

void add_edge(int x, int y, int cap, int cost) {
	g[x].pb((int)ed.size());
	ed.pb({ y, cap, 0, cost });
	g[y].pb((int)ed.size());
	ed.pb({ x, 0, 0, -cost });
}
int res(int i) {
	return ed[i].cap - ed[i].f;
}
	
bool spfa() {
	p.assign(sz(g), -1);
	pe.assign(sz(g), -1);
	queue<int>q;
	vector<bool>inq(sz(g));
	q.push(s);
	d[s] = 0;
	inq[s] = true;
	while (!q.empty()) {
		int x = q.front();
		q.pop();
		inq[x] = false;
		for (auto e : g[x]) {
			int y = ed[e].to;
			int w = ed[e].cost;
			if (!res(e)) continue;
			if (d[x] + w >= d[y]) continue;
			d[y] = d[x] + w;
			p[y] = x;
			pe[y] = e;
			if (!inq[y]) q.push(y), inq[y] = true;
		}
	}
	return (p[t] != -1);
}

int augment() {
	int mf = INF;
	int cur = t;
	while (cur != s) {
		mf = min(mf, res(pe[cur]));
		cur = p[cur];
	}
	cur = t;
	while (cur != s) {
		int i = pe[cur];
		ed[i].f += mf;
		ed[i ^ 1].f -= mf;
		cur = p[cur];
	}
	return mf;
}

int min_cost() {
	int flow = 0;
	while (spfa()) {
		d.assign(sz(g), INF);
		if (!spfa()) break;
		flow += augment();
	}
	return flow;
}