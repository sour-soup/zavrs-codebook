template<class T>
int gauss(vector<valarray<T>> a, vector<T> &ans) {
	int n = sz(a);
	int m = sz(a[0]) - 1;
	vector<int> where(m, -1);
	for (int col = 0, row = 0; col < m && row < n; ++col) {
		int sel = row;
		fore(i, row, n) if (abs(a[i][col]) > abs(a[sel][col]))
			sel = i;
		if (fabsl(a[sel][col]) < EPS) continue;
		swap(a[sel], a[row]);
		where[col] = row;
		forn(i, n) if (i != row) {
			T c = a[i][col] / a[row][col];
			a[i] -= a[row] * c;
		}
		++row;
	}
	ans.assign(m, 0);
	forn(i, m) if (where[i] != -1)
		ans[i] = a[where[i]][m] / a[where[i]][i];
	forn(i, n) {
		T sum = 0;
		forn(j, m) sum += ans[j] * a[i][j];
		if (fabsl(sum - a[i][m]) > EPS) return 0;
	}
	forn(i, m) if (where[i] == -1) return INF;
	return 1;
}