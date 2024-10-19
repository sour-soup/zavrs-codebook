int dfs_time = 0;
vector<int> g[N];
int d[N], tin[N], tout[N];
int to[N][LOGN];
void lca_dfs(int v, int p) {
    tin[v] = dfs_time++;
    to[v][0] = p;
    for (int i = 1; i < LOGN; ++i)
        to[v][i] = to[to[v][i - 1]][i - 1];
    for (int u : g[v]) {
        if (u == p) continue;
        d[u] = d[v] + 1;
        lca_dfs(u, v);
    }
    tout[v] = dfs_time;}
bool isParent(int v, int u) { // v isParent u
    return tin[v] <= tin[u] && tout[v] >= tout[u];}
int lca(int v, int u) {
    if (isParent(v, u)) return v;
    if (isParent(u, v)) return u;
    for (int i = LOGN - 1; i >= 0; --i)
        if (!isParent(to[v][i], u))
            v = to[v][i];
    return to[v][0];}