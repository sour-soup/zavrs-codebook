uli get_factor(uli n) {
	auto f = [n](uli x){ return mod_mul(x, x, n) + 1; };
	uli x = 0, y = 0, t = 30, prd = 2, i = 1, q;
	while (t ++ % 40 || gcd(prd, n) == 1) {
		if (x == y) x = ++ i, y = f(x);
		if (q = mod_mul(prd, max(x, y) - min(x, y), n)) prd = q;
		x = f(x), y = f(f(y));
	}
	return gcd(prd, n);
}
vector<uli> factorize(uli n) {
	if (n == 1) return {};
	if (isprime(n)) return {n};
	uli x = get_factor(n);
	auto l = factorize(x), r = factorize(n / x);
	l.insert(l.end(), r.begin(), r.end());
	return l;
}