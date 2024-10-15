void calc_sz(int u, int p) {
  sz[u] = 1;
  for (auto v: adj[u]) {
    if (v != p and !is_cen[v]) {
      calc_sz(v, u);
      sz[u] += sz[v];
    }
  }
}
int get_cen(int u, int p, int n) {
  for (auto v: adj[u]) {
    if (v != p and !is_cen[v] and 2 * sz[v] > n)
      return get_cen(v, u, n);
  }
  return u;
}
void decompose(int u=0, int p=-1, int d=0){
  calc_sz(u, p);  int c = get_cen(u, p, sz[u]);
  is_cen[c] = 1, cpar[c] = p, cdep[c] = d;
  for(int v: adj[c]){
    if(!is_cen[v])  decompose(v,c,d+1);
  }
}
decompose();