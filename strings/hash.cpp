mt19937 rng(29174);

const int MOD1 = int(1e9) + 7;
const int MOD2 = int(1e9) + 9;
//const int BASE = rng() % int(1e5) + int(1e6);
const int BASE = 10;

typedef pair<int, int> hs;
#define x first
#define y second

hs operator+(const hs& a, const hs& b) {
	hs c = hs(a.x + b.x, a.y + b.y);
	if (c.x >= MOD1) c.x -= MOD1;
	if (c.y >= MOD2) c.y -= MOD2;
	if (c.x < 0) c.x += MOD1;
	if (c.y < 0) c.y += MOD2;
	return c;
}
hs operator+(const hs& a, const int m) {
	return a + hs(m, m);
}
hs operator+(const int m, const hs& a) {
	return a + m;
}
hs operator-(const hs& a, const hs& b) {
	return a - hs(-b.x, -b.y);
}

hs operator*(const hs& a, const hs& b) {
	return hs((a.x * 1ll * b.x) % MOD1, (a.y * 1ll * b.y) % MOD2);
}
hs operator*(const hs& a, const int m) {
	return a * hs(m, m);
}
hs operator*(const int m, const hs& a) {
	return a * m;
}

const int N = 1e6 + 10;

int code(char c) {
	return 1 + c - 'a';
}

hs pw[N];

struct hashstr {
	vector<hs> pref;
	vector<hs> suf;

	hashstr(string s) {
		int n = sz(s);
		pref.resize(n + 1);
		suf.resize(n + 1);

		pref[0] = hs(0, 0);
		forn(i, n) pref[i + 1] = pref[i] + pw[i] * code(s[i]);
	}

	hs get_hash() {
		return pref.back();
	}

	hs substring(int l, int r, int up) { // [l, r), up = length of string
		return (pref[r] - pref[l]) * pw[up - l];
	}
};

void precalc() {
	pw[0] = hs(1, 1);
	forn(i, N - 1) pw[i + 1] = pw[i] * BASE;
}