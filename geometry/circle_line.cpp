vector<point> inter(const circle &c, const line &l){
	ld x0 = -l.a*l.c/(l.a*l.a+l.b*l.b),  y0 = -l.b*l.c/(l.a*l.a+l.b*l.b);
	if (l.c*l.c > c.r*c.r*(l.a*l.a+l.b*l.b)+EPS)
		return {};
	else if (abs (l.c*l.c - c.r*c.r*(l.a*l.a+l.b*l.b)) < EPS) {
		return {{x0, y0}};
	}
	else {
		ld d = c.r*c.r - l.c*l.c/(l.a*l.a+l.b*l.b);
		ld mult = sqrt (d / (l.a*l.a+l.b*l.b));
		ld ax,ay,bx,by;
		ax = x0 + l.b * mult;
		bx = x0 - l.b * mult;
		ay = y0 - l.a * mult;
		by = y0 + l.a * mult;
		return {{ax, ay}, {bx, by}};
	}
}