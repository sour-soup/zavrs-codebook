ld angle(vec a) { //Полярный угол точки [0, 2pi)
	ld ang = atan2l(a.y, a.x);
	if (ang < 0) ang += 2 * PI;
	return ang;
}
ld angle(vec a, vec b) { //Угол между векторами [0, pi]
	return acosl((a * b) / sqrtl(a * a) / sqrtl(b * b));
}