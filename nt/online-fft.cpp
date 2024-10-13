// calculates c=a*b such that
// a is constructed based on the values of c
// b is fixed

// it's also possible to calculate c=a*a such that
// a is constructed based on the values of c

void calc(int l, int r) {
	if (l == r - 1){
		// finish calculating c[l] and update the respective a[l] here
		return;
	}
	int m = (l + r) / 2;
	calc(l, m);
	if (l == 0) {
		auto tmp = mul(vector<Mint>(a.begin(), a.begin() + m), vector<Mint>(b.begin(), b.begin() + m));
		forn(i, 2 * m - 1)
			c[i] = tmp[i];
	} else {
		auto tmp = mul(vector<Mint>(a.begin() + l, a.begin() + m), vector<Mint>(b.begin(), b.begin() + 2 * (m - l)));
		forn(i, 3 * (m - l) - 1) if (i + l >= m && i + l < r)
			c[i + l] += tmp[i];
		tmp = mul(vector<Mint>(b.begin() + l, b.begin() + m), vector<Mint>(a.begin(), a.begin() + 2 * (m - l)));
		forn(i, 3 * (m - l) - 1) if (i + l >= m && i + l < r)
			c[i + l] += tmp[i];
	}
	calc(m, r);
}