T cdiv(T x, T y) { return (x + y - 1) / y; }
long long f(long long p, long long a, long long l, long long r) { 
	if (a == 0) return l == 0 ? 0 : -1;
	long long c = cdiv((T)l, (T)a); 
	if (a * c <= r) return c;
	long long b = p % a;
	auto y = f(a, b, a - r % a, a - l % a); 
	return y == -1 ? y : cdiv(l + (T)b * y, a) + p / a * y;
}