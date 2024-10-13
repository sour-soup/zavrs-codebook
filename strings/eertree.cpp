template<int AL>
struct eertree {
	struct node {
		int nxt[AL];
		int len, suf;
		
		node(int len = -1, int suf = -1) : len(len), suf(suf) {
			memset(nxt, -1, sizeof(nxt));
		}
	};
	
	vector<node> nodes;
	
	eertree(const string& s) {
		nodes.reserve(sz(s) + 2);
		nodes.pb(node(-1, 0));
		nodes.pb(node(0, 0));
		int v = 1;
		forn(i, sz(s)) {
			int c = s[i] - 'a';
			while (i - nodes[v].len - 1 < 0 || s[i - nodes[v].len - 1] != s[i])
				v = nodes[v].suf;
			if (nodes[v].nxt[c] == -1) {
				int len = nodes[v].len + 2;
				int suf = 1;
				if (len != 1) {
					int u = nodes[v].suf;
					while (i - nodes[u].len - 1 < 0 || s[i - nodes[u].len - 1] != s[i])
						u = nodes[u].suf;
					suf = nodes[u].nxt[c];
				}
				nodes[v].nxt[c] = sz(nodes);
				nodes.pb(node(len, suf));
			}
			v = nodes[v].nxt[c];
		}
	}
};