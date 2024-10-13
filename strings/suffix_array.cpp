struct suffix_array {
	vector<int> c, pos;
	vector<pair<pt, int>> p, nw;
	vector<int> cnt;
	int n;
	
	void radix_sort(int max_al) {
		cnt.assign(max_al, 0);
		forn(i, n) ++cnt[p[i].x.y];
		fore(i, 1, max_al) cnt[i] += cnt[i - 1];
		nw.resize(n);
		forn(i, n) nw[--cnt[p[i].x.y]] = p[i];
		cnt.assign(max_al, 0);
		forn(i, n) ++cnt[nw[i].x.x];
		fore(i, 1, max_al) cnt[i] += cnt[i - 1];
		for (int i = n - 1; i >= 0; --i) p[--cnt[nw[i].x.x]] = nw[i];
	}
	
	vector<int> lcp;
	sparse_table st;
	
	int get_lcp(int l, int r) {
		l = c[l], r = c[r];
		if (l > r) swap(l, r);
		return st.get(l, r);
	}
	
	suffix_array(const string &s) {
		n = sz(s);
		c = vector<int>(all(s));
		int max_al = *max_element(all(c)) + 1;
		p.resize(n);
		for (int k = 1; k < n; k <<= 1) {
			for (int i = 0, j = k; i < n; ++i, j = (j + 1 == n ? 0 : j + 1))
				p[i] = mp(mp(c[i], c[j]), i);
			radix_sort(max_al);
			c[p[0].y] = 0;
			fore(i, 1, n) c[p[i].y] = c[p[i - 1].y] + (p[i].x != p[i - 1].x);
			max_al = c[p.back().y] + 1;
		}
		lcp.resize(n);
		int l = 0;
		forn(i, n) {
			l = max(0, l - 1);
			if (c[i] == n - 1)
				continue;
			while (i + l < n && p[c[i] + 1].y + l < n && s[i + l] == s[p[c[i] + 1].y + l])
				++l;
			lcp[c[i]] = l;
		}
		pos.resize(n);
		forn(i, n)
			pos[i] = p[i].y;
		st = sparse_table(lcp);
	}
};