vec circum_circle(vec A, vec B, vec C) {
	vec b = C - A, c = B - A;
	vec z = b * (c * c) - c * (b * b);
	z = { -z.y, z.x };
	return A + z / (b % c) / 2;
}

pair<vec, ld> mec(vector<vec> p) {
	shuffle(all(p), mt19937(time(0)));
	vec center = p[0];
	ld r = 0, eps = 1 + 1e-8;
	forn(i, sz(p)) if (dist(center - p[i]) > r * eps) {
		center = p[i], r = 0;
		forn(j, i) if (dist(center - p[j]) > r * eps) {
			center = (p[i] + p[j]) / 2;
			r = dist(center - p[i]);
			forn(k, j) if (dist(center - p[k]) > r * eps) {
				center = circum_circle(p[i], p[j], p[k]);
				r = dist(center - p[i]);
			}
		}
	}
	return { center, r };
}