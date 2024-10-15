const int Q = 1e5+5;
vector<array<int, 2>> t[4 * Q];
vector<int> ans(Q);
int q;
struct DSU {
  int n, comps;
  vector<int> par, rnk;
  stack<array<int, 4>> ops;
  DSU(){}
  DSU(int n): n(n), comps(n), par(n), rnk(n) {
    iota(par.begin(), par.end(), 0);
  }
  int find(int u) {
    return (par[u] == u)? u: find(par[u]);
  }
  bool unite(int u, int v) {
    u = find(u), v = find(v);
    if (u == v)  return false;
    comps--;
    if (rnk[u] > rnk[v])  swap(u, v);
    ops.push({u, rnk[u], v, rnk[v]});
    par[u] = v;
    if (rnk[u] == rnk[v])  rnk[v]++;
    return true;
  }
  void rollback() {
    if (ops.empty())  return ;
    auto [u, rnku, v, rnkv] = ops.top();  ops.pop();
    par[u] = u, rnk[u] = rnku;
    par[v] = v, rnk[v] = rnkv;
    comps++;
  }
} dsu;
void add(int l, int r, array<int, 2> ed, int u = 1, int s = 0, int e = q) {
  if (r < s or e < l)  return ;
  if (l <= s and e <= r) {
    t[u].push_back(ed);
    return ;
  }
  int v = 2 * u, w = 2 * u + 1, m = (s + e) / 2;
  add(l, r, ed, v, s, m);
  add(l, r, ed, w, m + 1, e);
}
void go(int u = 1, int s = 0, int e = q) {
  int rmv = 0;
  for (auto &ed: t[u])  rmv += dsu.unite(ed[0], ed[1]);
  if (s == e)  ans[s] = dsu.comps;
  else {
    int v = 2 * u, w = 2 * u + 1, m = (s + e) / 2;
    go(v, s, m);
    go(w, m + 1, e);
  }
  while (rmv--)  dsu.rollback();
}