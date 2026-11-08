int n, q;
vector<vector<int>> g;
vector<int> p, d, heavy, head, pos;
int cur_pos;
 
int dfs(int v) {
    int size = 1;
    int max_size = 0;
    for (int u : g[v]) {
        if (u == p[v]) continue;
        p[u] = v;
        d[u] = d[v] + 1;
        int s = dfs(u);
        size += s;
        if (s > max_size) {
            max_size = s;
            heavy[v] = u;
        }
    }
    return size;
}
void decompose(int v, int h) {
    head[v] = h; pos[v] = cur_pos++;
    if (heavy[v] != -1) {
        decompose(heavy[v], h);
    }
    for (int u : g[v]) {
        if (u == p[v] || u == heavy[v]) continue;
        decompose(u, u);
    }
}
void init() {
		head.assign(n, 0);
    heavy.assign(n, -1);
    p.assign(n, -1);
    d.assign(n, 0);
    pos.assign(n, 0);
    cur_pos = 0;
    dfs(0);
    decompose(0, 0);
}
// Отвечать на запрос без написания LCA
// Работает за O(N * log^2(N))
int query(int a, int b) {
    int res = segment_tree_query(pos[a], pos[a]);
    for (; head[a] != head[b]; b = parent[head[b]]) {
        if (d[head[a]] > d[head[b]])
            swap(a, b);
        int cur_heavy_path_max = segment_tree_query(pos[head[b]], pos[b]);
        res = max(res, cur_heavy_path_max);
    }
    if (d[a] > d[b])
        swap(a, b);
    int last_heavy_path_max = segment_tree_query(pos[a], pos[b]);
    res = max(res, last_heavy_path_max);
    return res;
}