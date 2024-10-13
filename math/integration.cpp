ld sq(ld l, ld r) {
	ld d = r - l;
	return d / 6 * (f(l) + 4 * f((l + r) / 2) + f(r));
//	return d / 2 * (f(l) + f(r));
}
ld integral(ld l, ld r) {
	ld mid = (l + r) / 2;
	ld sl = sq(l, mid);
	ld sr = sq(mid, r);
	ld sa = sq(l, r);
	if (fabsl((sa - (sl + sr)) / (sl + sr)) < EPS)
		return sl + sr;
	return integral(l, mid) + integral(mid, r);
}