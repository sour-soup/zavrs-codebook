extern const int MOD = 998244353;
const int g = 3;

vector<Mint> w[LOGN];
vector<int> rv[LOGN];

void prepare() {
	Mint wb = Mint(g).pow((MOD - 1) / (1 << LOGN));
	forn(st, LOGN - 1) {
		w[st].assign(1 << st, 1);
		Mint bw = wb.pow(1 << (LOGN - st - 1));
		Mint cw = 1;
		forn(k, 1 << st) {
			w[st][k] = cw;
			cw *= bw;
		}
	}
	forn(st, LOGN) {
		rv[st].assign(1 << st, 0);
		if (st == 0) {
			rv[st][0] = 0;
			continue;
		}
		int h = (1 << (st - 1));
		forn(k, 1 << st)
			rv[st][k] = (rv[st - 1][k & (h - 1)] << 1) | (k >= h);
	}
}