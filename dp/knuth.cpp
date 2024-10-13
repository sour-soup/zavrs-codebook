li calc(int l, int r) {
	dp[l][r] = INF64;
	fore(m, opt[l][r - 1], opt[l + 1][r] + 1) {
		li nres = calc(l, m) + calc(m, r) + C(l, r);
		if (dp[l][r] > nres) {
			dp[l][r] = nres;
			opt[l][r] = m;
		}
	}
	return dp[l][r];
}