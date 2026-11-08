// (-1) - clockwise, (1) - counterclockwise, (0) - collinear
int orient(vec a, vec b, vec c) {
	return sign(a % b + b % c + c % a);
}

vector<vec> convex_hull(vector<vec> a) {
	if (sz(a) <= 1) return {};
	sort(all(a));
	vec p1 = a.front(), p2 = a.back();
	vector<vec> up, down;
	up.pb(p1); down.pb(p1);
	for (size_t i = 1; i < a.size(); ++i) {
		if (i + 1 == sz(a) || orient(p1, a[i], p2) < 0) {
			while (sz(up) >= 2 and orient(up[sz(up) - 2], up[sz(up) - 1], a[i]) >= 0)
				up.pop_back();
			up.push_back(a[i]);
		}
		if (i + 1 == sz(a) || orient(p1, a[i], p2) > 0) {
			while (sz(down) >= 2 and orient(down[sz(down) - 2], down[sz(down) - 1], a[i]) <= 0)
				down.pop_back();
			down.push_back(a[i]);
		}
	}
	a.clear();
	forn(i, sz(up))
		a.push_back(up[i]);
	for(int i = sz(down) - 2; i > 0; --i)
		a.push_back(down[i]);
	return a;
}