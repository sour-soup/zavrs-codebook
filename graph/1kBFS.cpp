void bfs(int s, int k){
  vector<queue<int>> q(k);
  vector<int> d(n, INF);
  q[0].push(s);
  d[s] = 0;
  int cnt = 1, pos = 0;
  while (cnt > 0){
      while(q[pos].empty()) pos = (pos + 1) % k;
      int v = q[pos].front();
      q[pos].pop();
      --cnt;
      for (auto e: g[v]){
        int u = e.u, w = e.weight; // 1 <= w <= k
        if (d[u] > d[v] + w){
          d[u] = d[v] + w;
          q[w].push(u);
          ++cnt;
}}}}