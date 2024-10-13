const int N = 1 << LOGN;
int mat[2][2] = {{+1, +1}, {+1, +0}};
int imt[2][2] = {{+0, +1}, {+1, -1}};
bool divneed = 0;

//XOR
//Mat = {{+1, +1}, {+1, -1}}
//iMt = {{+1, +1}, {+1, -1}}
//det(Mt) = 2 -> divneed = 1
//AND
//Mat = {{+0, +1}, {+1, +1}}
//iMt = {{-1, +1}, {+1, +0}}
//det(Mt) = 1 -> divneed = 0;
//OR
//Mat = {{+1, +1}, {+1, +0}}
//iMt = {{+0, +1}, {+1, -1}}
//det(Mt) = 1 -> divneed = 0;

inline void fwh(int a[N], int n, bool inv, int mod) {
	for(int st = 0; (1 << st) < n; st++) {
		int len = (1 << st);
		for(int k = 0; k < n; k += (len << 1)) {
			for(int pos = k; pos < k + len; pos++) {
				int l = a[pos], r = a[pos + len];
				if(!inv) {
					a[pos]       = norm(mat[0][0] * l + mat[0][1] * r, mod);
					a[pos + len] = norm(mat[1][0] * l + mat[1][1] * r, mod);
				} else {
					a[pos]       = norm(imt[0][0] * l + imt[0][1] * r, mod);
					a[pos + len] = norm(imt[1][0] * l + imt[1][1] * r, mod);
				}
			}
		}
	}
	if(divneed && inv) {
		int in = binPow(n, mod - 2, mod);
		forn(i, n) a[i] = mul(a[i], in, mod);
	}
}
int aa[N], bb[N];
inline void xorCon(int a[N], int b[N], int c[N], int logn, int mod) {
	assert((1 << logn) <= N);
	forn(i, 1 << logn)
		aa[i] = a[i], bb[i] = b[i];
	fwh(aa, 1 << logn, false, mod);
	fwh(bb, 1 << logn, false, mod);
	forn(mask, 1 << logn)
		c[mask] = mul(aa[mask], bb[mask], mod);
	fwh(c, 1 << logn, true, mod);
}