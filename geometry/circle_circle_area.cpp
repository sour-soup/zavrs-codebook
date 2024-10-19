ld circle_circle_area(vec a, int r1, vec b, int r2) {
	ld d = sqrtl(sqr(a.x - b.x) + sqr(a.y - b.y));
	if (r1 + r2 < d + EPS) return 0;
	if (r1 + d < r2 + EPS) return PI * r1 * r1;
	if (r2 + d < r1 + EPS) return PI * r2 * r2;
	ld theta_1 = acos((r1 * r1 + d * d - r2 * r2) / (2 * r1 * d)),
		theta_2 = acos((r2 * r2 + d * d - r1 * r1) / (2 * r2 * d));
	return r1 * r1 * (theta_1 - sin(2 * theta_1) / 2.) + r2 * r2 * (theta_2 - sin(2 * theta_2) / 2.);
}