vector<vec> seq;
vec translation;
int n;

bool pointInTriangle(vec a, vec b, vec c, vec point) {
    ll s1 = abs((b - a) % (c - a));
    ll s2 = abs((a - point) % (b - point)) + abs((b - point) % (c - point)) + abs((c - point) % (a - point));
    return s1 == s2;
}

void prepare(vector<vec>& points) {
    n = points.size();
    auto mn = min_element(all(points));
    rotate(points.begin(), mn, points.end());
    n--;
    seq.resize(n);
    for (int i = 0; i < n; i++)
        seq[i] = points[i + 1] - points[0];
    translation = points[0];
}

bool pointInConvexPolygon(vec point) {
    point = point - translation;
    if (seq[0] % point and sign(seq[0] % point != sign(seq[0] % seq[n - 1])))
        return false;
    if (seq[n - 1] % point and sign(seq[n - 1] % point) != sign(seq[n - 1] % seq[0]))
        return false;
    if (seq[0] % point == 0)
        return seq[0] * seq[0] >= point * point;

    int l = 0, r = n - 1;
    while (r - l > 1) {
        int mid = (l + r) / 2;
        int pos = mid;
        if (seq[pos] % point >= 0)
            l = mid;
        else
            r = mid;
    }
    int pos = l;
    return pointInTriangle(seq[pos], seq[pos + 1], vec(0, 0), point);
}