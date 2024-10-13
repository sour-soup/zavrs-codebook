ld dist(vector<ld>& a, vector<ld>& b) {
	ld res = 0;
	forn(i, sz(a)) res += (a[i] - b[i]) * (a[i] - b[i]);
	return res;
}
vector<ld> fixed_point(vector<vector<ld>> aa, vector<ld> bb) {
	int n = sz(aa);
	vector<vector<ld>> a(n, vector<ld>(n, 0));
	vector<ld> b(n, 0);
	forn(i, n) {
		if (fabsl(aa[i][i]) < EPS)
			return vector<ld>();
		forn(j, n) if (i != j)
			a[i][j] = -aa[i][j] / aa[i][i];
		b[i] = bb[i] / aa[i][i]; 
	}
	vector<ld> x(n, 0);
	forn(ITERATION, 200) {
		vector<ld> nx(n, 0);
		forn(i, n) forn(j, n) if (i != j)
			nx[i] += a[i][j] * x[j];
		forn(i, n) nx[i] += b[i];
		if (dist(x, nx) < EPS)
			break;
		x = nx; 
	}
	return x;
}