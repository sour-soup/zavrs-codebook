// n1 - number of vertices of the first part, n2 - second part
// switch n1, n2 if n1 > n2!
vector<int> used(n1);
vector<vector<int>>  g(n1); 
vector<int> to(n2, -1); //-1 if no matching edge comes out of i
bool kuhn(int v){
  if(used[v]) return false;
  used[v] = 1;
  for (int u : g[v]){
    if (to[u] == -1){
      to[u] = v;
      return true;
    }}
  for (int u : g[v]){
    if (kuhn(to[u])){
      to[u] = v;
      return true;
    }}
  return false;}
//======================
forn(i, n1){
  if (kuhn(i)){
    //...
    used.assign(n,0);}
}
