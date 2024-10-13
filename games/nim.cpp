namespace Nimber64{
	uli multiply_powers_of_2(uli, uli);

	uli multiply(uli a, uli b) {
	   uli ans = 0;
	   forn(p1, 64) if ((a >> p1) & 1)
		   forn(p2, 64) if ((b >> p2) & 1)
			  ans ^= multiply_powers_of_2(1ULL << p1, 1ULL << p2);
	   return ans;
	}
	uli multiply_powers_of_2(uli a, uli b) {
		if (a == 1 or b == 1) return a * b;
		int n = __lg(__lg(max(a,b)));
		uli power = 1ULL << (1 << n);
		if (a >= power and b >= power) {
			return multiply(power * 3 / 2, multiply_powers_of_2(a / power, b / power));
		} else if (a >= power) {
			return multiply_powers_of_2(a / power, b) * power;
		} else {
			return multiply_powers_of_2(a, b / power) * power;
		}
	}
	struct precalc {
		uli tmp[64][64];
		unsigned char x[256][256];
		uli y[8][8][256];
		template<int len>
		uli multfast(uli a, uli b) {
			uli c = 0;
			forn(i, len) if ((a >> i) & 1)
				forn(j, len) if ((b >> j) & 1)
					c ^= tmp[i][j];
			return c;
		}
		precalc(): tmp(), x(), y() {
			forn(i, 64) forn(j, 64) tmp[i][j] = multiply_powers_of_2(1ULL << i, 1ULL << j);
			forn(i, 256) forn(j, 256) x[i][j] = multfast<8>(i, j);
			forn(i, 8) forn(j, i + 1) forn(k, 256)
				y[i][j][k] = multfast<64>(tmp[i * 8][j * 8], k);
		}
		uli multfast2(uli a, uli b) const {
			uli res = 0;
			forn(i, 8){
				forn(j, i){
					res ^= y[i][j][
					x[(a >> (i * 8)) & 255][(b >> (j * 8)) & 255] ^
					x[(a >> (j * 8)) & 255][(b >> (i * 8)) & 255]];
				}
				res ^= y[i][i][x[(a >> (i * 8)) & 255][(b >> (i * 8)) & 255]];
			}
			return res;
		}
	};
	const precalc buf;
	
	struct nim{
		uli v;
		nim(uli vv = 0): v(vv) {}
		nim& operator +=(const nim& rhs){ v ^= rhs.v; return *this; }
		nim& operator *=(const nim& rhs){ v = buf.multfast2(v, rhs.v); return *this; }
		nim operator +(const nim& rhs) const { return nim(*this) += rhs; }
		nim operator *(const nim& rhs) const { return nim(*this) *= rhs; }
	};
}
using nim=Nimber64::nim;