ld distance_to_the_line(vec p, line l) {
	return abs((l.a * p.x + l.b * p.y + l.c)) / sqrtl(l.c * l.a + l.b * l.b);
}
ld distance_to_the_beam(vec p, vec s, vec f) {
	if ((f - s) * (p - s) >= 0)
		return abs((p - s) % (f - s)) / dist(f - s);
	return dist(p - s);
}
ld distance_to_the_segment(vec p, vec s, vec f) {
	if ((s - f) * (p - f) >= 0 && (f - s) * (p - s) >= 0)
		return abs((p - s) % (f - s)) / dist(f - s);
	return min(dist(p - f), dist(p - s));
}
ld distance_between_the_segments(vec a, vec b, vec c, vec d) {
	if (intersec(a, b, c, d))
		return 0;
	auto dist = distance_to_the_segment;
	return min({ dist(a, c, d), dist(b, c, d), dist(c, a, b), dist(d, a, b) });
}
// 1 - по одну сторону относительно прямой, 0 - по разные стороны
bool position_of_the_points(vec p, vec q, line l) {
	return sign(l.a * p.x + l.b * p.y + l.c) == sign(l.a * q.x + l.b * q.y + l.c);
}