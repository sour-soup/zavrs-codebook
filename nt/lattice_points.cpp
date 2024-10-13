int count_lattices(Fraction k, Fraction b, long long n) {
	auto fk = k.floor();
	auto fb = b.floor();
	auto cnt = 0LL;
	if (k >= 1 || b >= 1) {
		cnt += (fk * (n - 1) + 2 * fb) * n / 2;
		k -= fk;
		b -= fb;
	}
	auto t = k * n + b;
	auto ft = t.floor();
	if (ft >= 1) {
		cnt += count_lattices(1 / k, (t - t.floor()) / k, t.floor());
	}
	return cnt;
}