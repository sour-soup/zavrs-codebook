vector<int> d (n, INF), p(n, -1);
d[v] = 0;
int x;
forn(i, n){
	x = -1;
	forn(j, m)
		if (d[e[j].v] < INF && d[e[j].u] > d[e[j].v] + e[j].cost){
				d[e[j].u] = max (-INF, d[e[j].v] + e[j].cost);
				p[e[j].u] = e[j].v;
				x = e[j].u;
    }}
if (x != -1) { // have negative cycle
	int y = x;
	for (int i = 0; i < n; ++i) y = p[y];
	vector<int> path; // path = negative cycle
	for (int cur=y; ; cur=p[cur]) {
		path.push_back (cur);
		if (cur == y && path.size() > 1)  break;
	}
	reverse (path.begin(), path.end());
}