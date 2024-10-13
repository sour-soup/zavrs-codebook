template<typename T>
struct CRT {
	typedef pair<T, T> pt;
	vector<pt> rems;

	// need exgcd
	
	bool normalize() {
		map<T, vector<T>> pws, nrems;
		for (pt &it : rems) {
			T r = it.x;
			T x = it.y;
			for (T i = 2; i * i <= x; ++i) if (x % i == 0) {
				T cur = 1;
				while (x % i == 0) {
					cur *= i;
					x /= i;
				}
				pws[i].pb(cur);
				nrems[cur].pb(r % cur);
			}
			if (x > 1) {
				pws[x].pb(x);
				nrems[x].pb(r % x);
			}
		}
		
		vector<pt> res;
		for (auto &it : pws) {
			sort(all(it.y), greater<pt>());
			it.y.resize(unique(all(it.y)) - it.y.begin());
			T rm = -1;
			for (auto &pw : it.y) {
				for (auto &x : nrems[pw]) {
					if (rm != -1 && rm % pw != x)
						return false;
					if (rm == -1)
						rm = x;
				}
			}
			if (!it.y.empty()) {
				res.pb(mp(rm, it.y[0]));
			}
		}
		
		rems = res;
		return true;
	}
	
	vector<pt> calc() {
		int k = sz(rems);
		vector<vector<T>> r(k, vector<T>(k));
		
		forn(i, k) forn(j, k) if (i != j) {
			T x, y;
			T g = exgcd(rems[i].y, rems[j].y, x, y);
			assert(g == 1);
			x = (x % rems[j].y + rems[j].y) % rems[j].y;
			r[i][j] = x;
		}
	
		vector<T> x(k);
		forn(i, k) {
			x[i] = rems[i].x;
			forn(j, i) {
				// Beware of overflow
				x[i] = r[j][i] * (x[i] - x[j]) % rems[i].y;
    		    if (x[i] < 0)
        		    x[i] += rems[i].y;
		    }
		}
		
		return x;
	}
};