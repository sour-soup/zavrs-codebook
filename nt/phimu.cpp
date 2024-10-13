int lst[N], mu[N], phi[N];
void sieve() {
	forn(i, N) lst[i] = phi[i] = i;
	mu[1] = 1;
	for (int i = 2; i < N; ++i) {
		if (lst[i] == lst[i / lst[i]])
			mu[i] = 0;
		else
			mu[i] = -mu[i / lst[i]];
		if (lst[i] != i) continue;
		for (int j = i; j < N; j += i) {
			phi[j] -= phi[j] / i;
			lst[j] = min(lst[j], i);
		}
	}
}