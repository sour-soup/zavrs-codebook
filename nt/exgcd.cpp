li exgcd (li a, li b, li& x, li& y) {
	if (b == 0) {
		x = 1, y = 0;
		return a;
	}
	li x1, y1;
	li g = exgcd(b, a % b, x1, y1);
	x = y1;
	y = x1 - y1 * (a / b);
	return g;
}