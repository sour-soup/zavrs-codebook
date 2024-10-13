vector<ld> prog(vector<vector<ld>> mat, vector<ld> d) {
	int n = sz(d);
	vector<ld> a(n), b(n), c(n);
	forn(i, n) {
		if (i - 1 >= 0) a[i] = mat[i][i - 1];
		b[i] = -mat[i][i];
		if (i + 1 < n) c[i] = mat[i][i + 1];
	}

	vector<ld> p(n), q(n);

	p[0] = c[0] / b[0];
	q[0] = -d[0] / b[0];

	fore(i, 1, n) {
		p[i] = c[i] / (b[i] - a[i] * p[i - 1]);
		q[i] = (a[i] * q[i - 1] - d[i]) / (b[i] - a[i] * p[i - 1]);
	}

	vector<ld> x(n);
	x[n - 1] = q[n - 1];
	for (int i = n - 2; i >= 0; i--) {
		x[i] = p[i] * x[i + 1] + q[i];
	}

	return x;
}