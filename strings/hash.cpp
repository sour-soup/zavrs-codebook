const int K = 2;
using my_hash = array<int, K>;
mt19937 rnd(time(0));
my_hash A, M;
bool is_prime(int x) {
	for (int i = 2; i * 1ll * i <= x; i++)
		if (x % i == 0) return false;
	return true;
}
int next_prime(int x) {
	while (!is_prime(x)) ++x; 
	return x;
}
int random_prime(int l, int r) {
	return next_prime(uniform_int_distribution<int>(l, r)(rnd));
}
void prepare_primes() {
	forn(i, K) A[i] = random_prime(30, 200), M[i] = random_prime(1e9, 1e9 + 1e5);
}
// operator +, -, *, inv(), zero(), one()

my_hash get_hash(char c) {
	my_hash res; forn(i, K) res[i] = (c - 'a') + 1;
	return res;
}
my_hash get_hash(const string& s) {
	my_hash res = zero(); forrn(i, sz(s)) res = (res * A) + get_hash(s[i]);
	return res;
}
struct pref_hash {
	vector<my_hash> p;
	vector<my_hash> inv_a;
	pref_hash(string s = "") {
		int n = sz(s) + 1;
		p.assign(n + 1, zero());
		inv_a.assign(n + 1, one());
		my_hash INV_A = inv(A);
		my_hash cur = one();
		forn(i, n) {
			p[i + 1] = p[i] + get_hash(s[i]) * cur;
			inv_a[i + 1] = inv_a[i] * INV_A;
			cur = cur * A;
		}
	}
	my_hash substr(int l, int r) { return (p[r] - p[l]) * inv_a[l]; }
};
vector<my_hash> deg_a;
void prepare_degrees(int n) {
	deg_a.assign(n + 1, one());
	forn(i, n) deg_a[i + 1] = deg_a[i] * A;
}
my_hash concat(my_hash l, my_hash r, int len) { return l + r * deg_a[len]; }