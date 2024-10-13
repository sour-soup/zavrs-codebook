int h[N], pcd[N];
int dfs(int v, int s, int &cd, int p = -1){
	int sum = 1;
	for (auto it : g[v]) if (h[it.u] == -1 && it.u != p)
		sum += dfs(it.u, s, cd, v);
	if (cd == -1 && (2 * sum >= s || p == -1))
		cd = v;
	return sum;
}
void build(int v, int s, int d, int p = -1){
	int cd = -1;
	dfs(v, s, cd);
	h[cd] = d;
	pcd[cd] = p;
	for (auto it : g[cd]) if (h[it.u] == -1)
		build(it.u, s / 2, d + 1, cd);
}
void solve() {
	memset(h, -1, sizeof(h));
	build(0, n, 0);
}