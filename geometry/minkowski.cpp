void reorder_polygon(vector<vec>& P) {
	auto mn = min_element(all(P), [](auto l, auto r) {
		return l.y < r.y or (l.y == r.y and l.x < r.x);
	});
	rotate(P.begin(), mn, P.end());
}

vector<vec> minkowski(vector<vec> P, vector<vec> Q) {
	reorder_polygon(P); reorder_polygon(Q);
	P.push_back(P[0]); P.push_back(P[1]);
	Q.push_back(Q[0]); Q.push_back(Q[1]);
	vector<vec> result;
	int i = 0, j = 0;
	while (i < P.size() - 2 || j < Q.size() - 2) {
		result.push_back(P[i] + Q[j]);
		auto cross = (P[i + 1] - P[i]) % (Q[j + 1] - Q[j]);
		if (cross >= 0 && i < P.size() - 2)
			++i;
		if (cross <= 0 && j < Q.size() - 2)
			++j;
	}
	return result;
}