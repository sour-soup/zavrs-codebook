Mint floor_sum(Mint n, Mint m, Mint a, Mint b) {
	Mint ans = 0;
	while (true) {
		if (a >= m) {
			ans += n * (n - 1) / 2 * (a / m);
			a %= m;
		}
		if (b >= m) {
			ans += n * (b / m);
			b %= m;
		}
		Mint y_max = a * n + b;
		if (y_max < m) break;
		n = y_max / m;
		b = y_max % m;
		swap(m, a);
	}
	return ans;
}