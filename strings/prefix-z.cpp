vector<int> pref_func(string s) {
	int n = s.size();
	vector<int> a(n);
	for (int i = 1; i < n; i++) {
		int j = a[i - 1];
		while (j > 0 && s[i] != s[j])
			j = a[j - 1];
		if (s[i] == s[j]) {
			j++;
			a[i] = j;
		}
	}
	return a;
}

vector<int> z_func(string s) {
	int n = s.size();
	vector<int> z(n);
	int l = 0, r = 0;
	for (int i = 1; i < n; i++) {
		if (i <= r)
			z[i] = min(r - i + 1, z[i - l]);
		while (i + z[i] < n and s[z[i]] == s[i + z[i]])
			++z[i];
		if (i + z[i] > r)
			l = i, r = i + z[i] - 1;
	}
	return z;
}