// comp - struc of complex number
vector<comp> w[LOGN];
vector<int> rv[LOGN];
void prepare() {
	forn(st, LOGN - 1) {
		w[st].resize(1 << st);
		forn(i, 1 << st) {
			ld ang = PI / (1 << st) * i;
			w[st][i] = comp(cosl(ang), sinl(ang));
		}}
	forn(st, LOGN) {
		rv[st].resize(1 << st);
		if (st > 0) {
			int h = (1 << (st - 1)) - 1;
			forn(i, 1 << st)
				rv[st][i] = (rv[st - 1][i & h] << 1) | (i > h);
}}}
void fft(vector<comp> &a, bool inv) {
	int n = sz(a);
	int ln = __builtin_ctz(n);
	forn(i, n) {
		int ni = rv[ln][i];
		if (i < ni) swap(a[i], a[ni]);
	}
	forn(st, ln) {
		int len = 1 << st;
		for (int k = 0; k < n; k += (len << 1)) {
			fore(pos, k, k + len) {
				comp l = a[pos];
				comp r = a[pos + len] * w[st][pos - k];
				a[pos] = l + r;
				a[pos + len] = l - r;
			}}}
	if (inv) {
		forn(i, n)
			a[i] = a[i] / n;
		reverse(a.begin() + 1, a.end());
}}
vector<ll> mul(vector<int> a, vector<int> b) {
	int cnt = 1 << (32 - __builtin_clz(sz(a) + sz(b) - 1));
	vector<comp> c(cnt), tmpa(cnt), tmpb(cnt);
	forn(i, cnt) c[i] = comp(i < sz(a) ? a[i] : 0, i < sz(b) ? b[i] : 0);
	fft(c, false);
	forn(i, cnt) {
		tmpa[i] = (c[i] + c[(cnt - i) % cnt].conj()) / comp(2, 0);
		tmpb[i] = (c[i] - c[(cnt - i) % cnt].conj()) / comp(0, 2);
	}
	forn(i, cnt) c[i] = tmpa[i] * tmpb[i];
	fft(c, true);
	vector<ll> ans(cnt);
	forn(i, cnt) ans[i] = llrint(c[i].x);
	return ans;
}