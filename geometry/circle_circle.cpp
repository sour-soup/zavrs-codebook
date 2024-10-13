vector<point> inter(circle a, circle b){
	b.c.x -= a.c.x;
	b.c.y -= a.c.y;
	line l(-2 * b.c.x, -2 * b.c.y, sqr(b.c.x) + sqr(b.c.y) + sqr(a.r) - sqr(b.r));
	auto p = inter(a, l);
	for (auto &it : p) it.x += a.c.x, it.y += a.c.y;
	return p;
}