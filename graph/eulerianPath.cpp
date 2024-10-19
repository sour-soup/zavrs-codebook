set<int> g[N]
void euler(int v) {
    while (!g[v].empty()) {
        int u = *g[v].begin();
        g[v].erase(u);
        g[u].erase(v);
        euler(u);}
    ans.push_back(v + 1);}
