// (-1) - clockwise, (1) - counterclockwise, (0) - collinear
int orient(vec a, vec b, vec c) {
	return sign(a.x * (b.y - c.y) + b.x * (c.y - a.y) + c.x * (a.y - b.y));
}

vector<vec> convex_hull(vector<vec> a) {
	if (a.size() == 1)  return;
	sort(a.begin(), a.end());
	vec p1 = a[0], p2 = a.back();
	vector<vec> up, down;
	up.push_back(p1);
	down.push_back(p1);
	for (size_t i = 1; i < a.size(); ++i) {
		if (i == a.size() - 1 || orient(p1, a[i], p2) < 0) {
			while (up.size() >= 2 && orient(up[up.size() - 2], up[up.size() - 1], a[i]) >= 0)
				up.pop_back();
			up.push_back(a[i]);
		}
		if (i == a.size() - 1 || orient(p1, a[i], p2) > 0) {
			while (down.size() >= 2 && orient(down[down.size() - 2], down[down.size() - 1], a[i]) <= 0)
				down.pop_back();
			down.push_back(a[i]);
		}
	}
	a.clear();
	forn(i, sz(up))
		a.push_back(up[i]);
	forn(i, sz(down))
		a.push_back(down[i]);
	return a;
}