//ll or ld !!!
struct vec {
    ll x, y;
	vec operator+(const vec& p) const { return { x + p.x, y + p.y }; }
	vec operator-(const vec& p) const { return { x - p.x, y - p.y }; }
    ll operator*(const vec& p) const { return x * p.x + y * p.y; }
    ll operator%(const vec& p) const { return x * p.y - y * p.x; }

    bool operator<(const vec& p) const { 
        return x < p.x || (x == p.x && y < p.y);
    }
};

struct line {
	ll a, b, c;
	line() {};
	line(const vec& p, const vec& q) {
		a = p.y - q.y;
		b = q.x - p.x;
		c = -(a * p.x + b * p.y);
	}
	line(ll a, ll b, ll c) : a(a), b(b), c(c) {}
};

struct circle : vec {
	ll r;
};