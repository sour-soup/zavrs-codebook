template<typename T>
T hungarian(const vector<vector<T>>& cost) {
	const T INF = numeric_limits<T>::max();
	int n = sz(cost), m = sz(cost[0]);
	vector<T> u(n + 1), v(m + 1), dist(m + 1);
	vector<int> p(m + 1), way(m + 1), used(m + 1);
	fore(i, 1, n + 1) {
		p[0] = i;
		int j0 = 0;
		fill(all(dist), INF);
		do {
			used[j0] = i;
			int i0 = p[j0], j1 = -1;
			T delta = INF;
			fore(j, 1, m + 1) if (used[j] != i) {
				T cur = cost[i0 - 1][j - 1] - u[i0] - v[j];
				if (cur < dist[j]) dist[j] = cur, way[j] = j0;
				if (dist[j] < delta) delta = dist[j], j1 = j;
			}
			fore(j, 0, m + 1) {
				if (used[j] == i) u[p[j]] += delta, v[j] -= delta;
				else dist[j] -= delta;
			}
			j0 = j1;
		} while (p[j0] != 0);
		for (int j1; j0; j0 = j1)
			p[j0] = p[j1 = way[j0]];
	}
	
	return -v[0];
}