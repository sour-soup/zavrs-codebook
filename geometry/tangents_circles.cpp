void tangents(vec c, ld r1, ld r2, vector<line>& ans) {
	ld r = r2 - r1;
	ld z = sqr(c.x) + sqr(c.y);
	ld d = z - sqr(r);
	if (d < -EPS) return;
	d = sqrtl(abs(d));
	line l;
	l.a = (c.x * r + c.y * d) / z;
	l.b = (c.y * r - c.x * d) / z;
	l.c = r1;
	ans.pb(l);
}
vector<line> tangents(circle a, circle b) {
	vector<line> ans;
	for (int i = -1; i <= 1; i += 2)
		for (int j = -1; j <= 1; j += 2)
			tangents(b - a, a.r * i, b.r * j, ans);
	forn(i, sz(ans))
		ans[i].c -= ans[i].a * a.x + ans[i].b * a.y;
	return ans;
}