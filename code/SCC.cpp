void dfs1(int u, vector<int> *adj, vector<int> &vis, vector<int> &order) {
  vis[u] = 1;
  for (int &v: adj[u]) {
    if (!vis[v]) {
      dfs1(v, adj, vis, order);
    }
  }
  order.emplace_back(u);
}
void dfs2(int u, vector<int> *rev_adj, vector<int> &vis, vector<int> &scc) {
  scc.emplace_back(u);
  vis[u] = 1;
  for (int &v: rev_adj[u]) {
    if (!vis[v]) {
      dfs2(v, rev_adj, vis, scc);
    }
  }
}
vector<vector<int>> get_sccs(int n, vector<int> *adj) {
  vector<int> vis(n), order;
  for (int u = 0; u < n; ++u) {
    if (!vis[u]) {
      dfs1(u, adj, vis, order);
    }
  }
  vector<int> rev_adj[n];
  for (int u = 0; u < n; ++u) {
    for (int v: adj[u]) {
      rev_adj[v].emplace_back(u);
    }
  }
  vector<vector<int>> sccs;
  reverse(order.begin(), order.end());
  vis.assign(n, 0);
  for (int u: order) {
    if (!vis[u]) {
      sccs.emplace_back(0);
      dfs2(u, rev_adj, vis, sccs.back());
    }
  }
  return sccs;
}
vector<vector<int>> sccs = get_sccs(n, adj);
int tot_scc = sccs.size();
vector<int> scc_no(n);
for (int i = 0; i < tot_scc; ++i) {
  for (int u: sccs[i]) {
    scc_no[u] = i;
  }
}
