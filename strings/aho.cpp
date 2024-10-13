int go(int v, int c) {
	if (nodes[v].go[c] != -1)
		return nodes[v].go[c];
	if (nodes[v].nxt[c] != -1)
		return nodes[v].go[c] = nodes[v].nxt[c];
	if (v == 0)
		return nodes[v].go[c] = 0;
	return nodes[v].go[c] = go(suf(v), c);
}
int suf(int v) {
	if (nodes[v].suf != -1)
		return nodes[v].suf;
	if (v == 0 || nodes[v].p == 0)
		return nodes[v].suf = 0;
	return nodes[v].suf = go(suf(nodes[v].p), nodes[v].pch);
}
int ssuf(int v) {
	if (nodes[v].ssuf != -1)
		return nodes[v].ssuf;
	if (v == 0 || nodes[v].p == 0)
		return nodes[v].ssuf = 0;
	int s = suf(v);
	if (nodes[s].term)
		return nodes[v].ssuf = s;
	return nodes[v].ssuf = ssuf(s);
}