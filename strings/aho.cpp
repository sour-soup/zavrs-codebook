const int B = 2e5 + 10;
int sz = 0;
map<char, int> nxt[B], go[B];
int cnt[B], pr[B], slink[B];
char prc[B];
int dlink[B];

int create() {
	dlink[sz] = -1;
	slink[sz] = -1;
	pr[sz] = -1;
	cnt[sz] = 0;
	nxt[sz].clear();
	return sz++;
}

void add(string s, int i, int k = 1) {
	int v = 0;
	for (auto x : s) {
		if (!nxt[v].count(x))
			nxt[v][x] = create();
		pr[nxt[v][x]] = v;
		prc[nxt[v][x]] = x;
		v = nxt[v][x];
	}
	cnt[v] += k;
}

int get_slink(int x);

int get_go(int x, char k) {
	if (go[x].count(k)) return go[x][k];
	if (nxt[x].count(k)) return go[x][k] = nxt[x][k];
	if (!x) return go[x][k] = 0;
	return go[x][k] = get_go(get_slink(x), k);
}

int get_slink(int x) {
	if (slink[x] != -1) return slink[x];
	if (x == 0 or pr[x] == 0) return slink[x] = 0;
	return slink[x] = get_go(get_slink(pr[x]), prc[x]);
}

int get_dlink(int x) {
	if (dlink[x] != -1) return dlink[x];
	if (!x) return dlink[x] = 0;
	if (cnt[get_slink(x)]) return dlink[x] = get_slink(x);
	return dlink[x] = get_dlink(get_slink(x));
}