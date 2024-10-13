int generator(int p) {
	auto fact = factorize(p - 1);
	for (int res = 2; res <= p; ++res) {
		bool ok = true;
		for (int i = 0; i < int(fact.size()) && ok; ++i)
			ok &= binpow(res, phi / fact[i], p) != 1;
		if (ok) return res;
	}
	return -1;
}