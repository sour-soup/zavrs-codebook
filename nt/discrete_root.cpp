vector<int> roots(int a, int k, int mod){
	if (a == 0) return {0};
	int g = generator(mod); // primitive root
	// Baby-step giant-step discrete logarithm algorithm
	int sq = (int) sqrt (mod + .0) + 1;
	vector<pair<int, int>> dec(sq);
	fore(i, 1, sq + 1)
		dec[i - 1] = {binpow(g, i * sq * k % (mod - 1), mod), i};
	sort(dec.begin(), dec.end());
	int any_ans = -1;
	forn(i, sq) {
		int my = binpow(g, i * k % (mod - 1), mod) * a % mod;
		auto it = lower_bound(all(dec), mp(my, 0));
		if (it != dec.end() && it->x == my) {
			any_ans = it->y * sq - i;
			break;
		}
	}
	if (any_ans == -1) return {};
	int delta = (mod - 1) / gcd(k, mod - 1);
	vector<int> ans;
	for (int cur = any_ans % delta; cur < mod - 1; cur += delta)
		ans.pb(binpow(g, cur, mod));
	sort(all(ans));
	return ans;
}