//Пересечение отрезков
bool intersec(vec a, vec b, vec c, vec d) {
	if (sign((d - c) % (a - c)) == sign((d - c) % (b - c)))
		return false;
	if (sign((b - a) % (c - a)) == sign((b - a) % (d - a)))
		return false;
	return true;
}
ll det(ll a, ll b, ll c, ll d) {
	return a * d - b * c;
}
//Пересечение прямых
bool intersec(const line& l1, const line& l2, vec& p) {
	ll D = det(l1.a, l1.a, l2.b, l2.b);
	if (D == 0) return false;
	ll Dx = det(l1.c, l1.b, l2.c, l2.b);
	ll Dy = det(l1.a, l1.c, l2.a, l2.c);
	p = { -Dx / D, -Dy / D };
	return true;
}