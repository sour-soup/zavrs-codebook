ld polygon_area(vector<vec>a) { //Площадь многоугольника
	ll res = 0;
	vec last = a.back();
	for (auto cur : a) {
		res += (cur.y + last.y) * (cur.x - last.x);
		last = cur;
	}
	return abs(res) / 2.l;
}
ld triangle_area(vec a, vec b, vec c) { //Площадь треугольника
	return abs((b - a) % (c - a)) / 2.l;
}