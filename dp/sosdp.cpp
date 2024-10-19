forn(i, LOGN) forn(j, N) if ((j & (1 << i)) == 0)
		dp[j | (1 << i)] += dp[j];