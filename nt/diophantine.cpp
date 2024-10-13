array<li, 6> solve_linear_diophantine(li a, li b, li c, li xlow, li xhigh, li ylow, li yhigh){
	li x, y, g = exgcd(a >= 0 ? a : -a, b >= 0 ? b : -b, x, y);
	array<li, 6> no_sol{0, 0, 0, 0, 0, g};
	if(c % g) return no_sol;
	x *= c / g, y *= c / g;
	if(a < 0) x = -x;
	if(b < 0) y = -y;
	a /= g, b /= g, c /= g;
	auto shift = [&](li &x, li &y, li a, li b, li cnt){ x += cnt * b, y -= cnt * a; };
	int sign_a = a > 0 ? 1 : -1, sign_b = b > 0 ? 1 : -1;
	shift(x, y, a, b, (xlow - x) / b);
	if(x < xlow) shift(x, y, a, b, sign_b);
	if(x > xhigh) return no_sol;
	li lx1 = x;
	shift(x, y, a, b, (xhigh - x) / b);
	if(x > xhigh) shift(x, y, a, b, -sign_b);
	li rx1 = x;
	shift(x, y, a, b, -(ylow - y) / a);
	if(y < ylow) shift(x, y, a, b, -sign_a);
	if(y > yhigh) return no_sol;
	li lx2 = x;
	shift(x, y, a, b, -(yhigh - y) / a);
	if(y > yhigh) shift(x, y, a, b, sign_a);
	li rx2 = x;
	if(lx2 > rx2) swap(lx2, rx2);
	li lx = max(lx1, lx2), rx = min(rx1, rx2);
	if(lx > rx) return no_sol;
	return {(rx - lx) / (b >= 0 ? b : -b) + 1, lx, (c - lx * a) / b, rx, (c - rx * a) / b, g};
}