vector<vector<int>> d(n, vector<int>(n));
forn(i,n) d[i][i] = 0;
forn(k,n) forn(i,n) forn(j, n)
			if (d[i][k] < INF && d[k][j] < INF)
				d[i][j] = min (d[i][j], d[i][k] + d[k][j]);