using comp = complex<double>;

const int LOGN = 19; // +1 от лога макс степени многочлена
vector<comp> w[LOGN];
vector<int> rv[LOGN];

void prepare() {
	forn(st, LOGN) {
		w[st].resize(1 << st);
		forn(i, 1 << st) {
			ld ang = PI / (1 << st) * i;
			w[st][i] = comp(cosl(ang), sinl(ang));
		}
	}
	forn(st, LOGN) {
		rv[st].resize(1 << st);
		if (st > 0) {
			int h = (1 << (st - 1)) - 1;
			forn(i, 1 << st)
				rv[st][i] = (rv[st - 1][i & h] << 1) | (i > h);
		}
	}
}

void fft(vector<comp>& a, bool inv) {
	int n = sz(a);
	int ln = countr_zero(uint(n));
	forn(i, n) {
		int j = rv[ln][i];
		if (i < j) swap(a[i], a[j]);
	}
	forn(st, ln) {
		int len = 1 << st;
		for(int k = 0; k < n; k += (len << 1)) {
			fore(pos, k, k + len) {
				comp x = a[pos];
				comp y = a[pos + len] * w[st][pos - k];
				a[pos] = x + y;
				a[pos + len] = x - y;
			}
		}
	}
	if (inv) {
		reverse(a.begin() + 1, a.end());
		forn(i, n) a[i] /= n;
	}
}

vector<comp> mul(const vector<comp>& a, const vector<comp>& b) {
	int n = 1 << (32 - countl_zero(uint(sz(a) + sz(b) - 1)));
	vector<comp> aa = a;
	vector<comp> bb = b;
	aa.resize(n);
	bb.resize(n);
	fft(aa, 0);
	fft(bb, 0);
	vector<comp> c(n);
	forn(i, n) c[i] = aa[i] * bb[i];
	fft(c, 1);
	return c;
}

vector<int> mul(const vector<int>& a, const vector<int>& b) {
	vector<comp> aa(sz(a)), bb(sz(b));
	forn(i, sz(a)) aa[i] = comp(a[i], 0);
	forn(i, sz(b)) bb[i] = comp(b[i], 0);
	vector<comp> c = mul(aa, bb);
	vector<int> ans(sz(c));
	forn(i, sz(c))
		ans[i] = llrint(c[i].real());
	return ans;
}