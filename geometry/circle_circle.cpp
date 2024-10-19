// circle A centered at (0, 0)
vector<vec> inter(circle a, circle b) {
	b.x -= a.x;
	b.y -= a.y;
	line l(-2 * b.x, -2 * b.y, sqr(b.x) + sqr(b.y) + sqr(a.r) - sqr(b.r));
	auto p = inter(a, l);
	for (auto& it : p) it.x += a.x, it.y += a.y;
	return p;
}