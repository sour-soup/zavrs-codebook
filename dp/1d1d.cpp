auto w = [&](int j, int i) { return b[j] * 1LL * a[i]; };
dp[0] = 0;
deque<pair<int, int>> k = {{0, 1}};
for (int i = 1; i < n; ++i) {
	dp[i] = dp[k[0].first] + w(k[0].first, i);
	if (i == n - 1) {
		break;
	}
	++k[0].second;
	if (sz(k) >= 2 && k[0].second == k[1].second) {
		k.pop_front();
	}
	while (!k.empty() && dp[k.back().first] + w(k.back().first, k.back().second) >= dp[i] + w(i, k.back().second)) {
		k.pop_back();
	}
	if (k.empty()) {
		k.push_back({i, i + 1});
	} else if (dp[k.back().first] + w(k.back().first, n - 1) >= dp[i] + w(i, n - 1)) {
		int l = k.back().second, r = n - 1;
		while (r - l > 1) {
			int m = (l + r) / 2;
			if (dp[k.back().first] + w(k.back().first, m) >= dp[i] + w(i, m))
				r = m;
			else
				l = m;
		}
		k.push_back({i, right});
	}
}