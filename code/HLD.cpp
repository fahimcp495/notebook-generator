int tt, tin[N], tout[N], sz[N], par[N][LG], hvc[N];
void dfs(int u, int p) {
  tin[u] = tt++, sz[u] = 1, par[u][0] = p;
  for (int j = 1; j < LG; ++j) {
    par[u][j] = par[par[u][j-1]][j-1];
  }
  int mx = 0;
  for (int &v: adj[u]) {
    if (v != p) {
      dfs(v, u);
      sz[u] += sz[v];
      if (sz[v] > mx) {
        mx = sz[v];
        hvc[u] = v;
      }
    }
  }
  tout[u] = tt-1;
}
int ch_cnt, idx_cnt, chno[N], chd[N], idx[N];
void hld(int u, int p) {
  if(chd[ch_cnt] == -1) {
    chd[ch_cnt] = u;
  }
  chno[u] = ch_cnt, idx[u] = idx_cnt++;
  if(hvc[u] != -1) {
    hld(hvc[u], u);
  }
  for (int &v: adj[u]) {
    if (v != p and v != hvc[u]) {
      ch_cnt++;
      hld(v, u);
    }
  }
}
void ?node_update(int u, int x) {
  ?update(idx[u], x);
}
void ?pupdate_up(int u, int anc) {
  if (chno[u] == chno[anc]) {
    return ?rupdate(idx[anc], idx[u]);
  }
  ?rupdate(idx[chd[chno[u]]], idx[u]);
  ?pupdate_up(par[chd[chno[u]]][0], anc);
}
void ?pupdate(int u, int v) {
  int l = lca(u, v);
  ?pupdate_up(u, l);
  ?pupdate_up(v, l);
}
ll ?node_query(int u) {
  return ?query(idx[u]);
}
int ?pquery_up(int u, int anc) {
  if (chno[u] == chno[anc]) {
    return ?rquery(idx[anc], idx[u]);
  }
  return f(?rquery(idx[chd[chno[u]]], idx[u]), ?pquery_up(par[chd[chno[u]]][0], anc));
}
int ?rquery(int u, int v) {
  int l = lca(u, v);
  return f(?pquery_up(u, l), ?pquery_up(v, l));
}
adj[u].clear(); hvc[u] = -1;
tt = 0; dfs(0, 0);

chd[ch] = -1;
ch_cnt = 0, idx_cnt = 0; hld(0, 0);
