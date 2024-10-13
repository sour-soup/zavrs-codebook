template<class T>
struct linear_recurrence{
	int n;
	vector<T> init, coef;
	linear_recurrence(const vector<T> &init, const vector<T> &coef): n((int)coef.size()), init(init), coef(coef){
		assert((int)coef.size() == (int)init.size());
	}
	linear_recurrence(const vector<T> &s){
		assert(!s.empty());
		int sz = (int)s.size();
		n = 0;
		vector<T> B(sz), C;
		coef.resize(sz);
		coef[0] = B[0] = 1;
		T b = 1;
		for(auto i = 0, m = 0; i < sz; ++ i){
			++ m;
			T d = s[i];
			for(auto j = 1; j <= n; ++ j) d += coef[j] * s[i - j];
			if(!d) continue;
			C = coef;
			T c = d / b;
			for(auto j = m; j < sz; ++ j) coef[j] -= c * B[j - m];
			if(2 * n > i) continue;
			n = i + 1 - n, B = C, b = d, m = 0;
		}
		n = max(n, 1);
		coef.resize(n + 1), coef.erase(coef.begin());
		for(auto &x: coef) x = -x;
		reverse(coef.begin(), coef.end());
		init.resize(n);
		for(auto i = 0; i < n; ++ i) init[i] = s[i];
	}
	T operator[](long long i) const{
		assert(0 <= i);
		auto combine = [&](const vector<T> &a, const vector<T> &b){
			vector<T> res(2 * n + 1);
			for(auto i = 0; i <= n; ++ i) for(auto j = 0; j <= n; ++ j) res[i + j] += a[i] * b[j];
			for(auto i = n << 1; i > n; -- i) for(auto j = 0; j < n; ++ j) res[i - 1 - j] += res[i] * coef[n - 1 - j];
			res.resize(n + 1);
			return res;
		};
		vector<T> pol(n + 1), e(pol);
		pol[0] = e[1] = 1;
		for(++ i; i; i >>= 1, e = combine(e, e)) if(i & 1) pol = combine(pol, e);
		T res = 0;
		for(auto i = 0; i < n; ++ i) res += pol[i + 1] * init[i];
		return res;
	}
};