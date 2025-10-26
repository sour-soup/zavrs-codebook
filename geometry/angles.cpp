ld angle(vec a) { //Полярный угол точки [0, 2pi)
	ld ang = atan2l(a.y, a.x);
	if (ang < 0) ang += 2 * PI;
	return ang;
}

// acosl ломается на аргументах вне [-1, 1]!
ld angle(vec a, vec b) { //Угол между векторами [0, pi]
	return acosl((a * b) / sqrtl(a * a) / sqrtl(b * b));
}

ld angle(vec a, vec b) { // Угол между двумя точками на одной окружности (сфере)
	ld z = 1 - euclid(a, b) / (2 * r * r);
	return acosl(max(-1.l, min(z, 1.l)));	
}