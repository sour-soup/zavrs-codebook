vector<pt> minkowski_sum(vector<pt> &a, vector<pt> &b) {
	int n = (int)a.size(), m = (int)b.size();
	int i = 0, j = 0; //assuming a[i] and b[j] both are (left, bottom)-most points
	vector<pt> c;
	c.push_back(a[i] + b[j]);
	while (i + 1 < n || j + 1 < m){
		pt p1 = a[i] + b[(j + 1) % m];
		pt p2 = a[(i + 1) % n] + b[j];
		int t = orientation(c.back(), p1, p2);
		if (t >= 0) j = (j + 1) % m;
		if (t <= 0) i = (i + 1) % n, p1 = p2;
		if (t == 0) p1 = a[i] + b[j];
		if (p1 == c[0]) break;
		c.push_back(p1);
	}
	return c;
}