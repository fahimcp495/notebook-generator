void dfs(int u, int p) {
  node[tt] = u;
  tin[u] = tt++, sz[u] = 1, hc[u] = -1;
  for (auto v: adj[u]) {
    if (v != p) {
      dfs(v, u);
      sz[u] += sz[v];
      if (hc[u] == -1 or sz[hc[u]] < sz[v]) {
        hc[u] = v;
      }
    }
  }
  tout[u] = tt - 1;
}
void dsu(int u, int p, int keep) {
  for (int v: adj[u]) {
    if (v != p and v != hc[u]) {
      dsu(v, u, 0);
    }
  }
  if (hc[u] != -1) {
    dsu(hc[u], u, 1);
  }
  for (auto v: adj[u]) {
    if (v != p and v != hc[u]) {
      for (int i = tin[v]; i <= tout[v]; ++i) {
        int w = node[i];
        // get ans in case of ans is related to simple path or pair
      }
      for (int i = tin[v]; i <= tout[v]; ++i) {
        int w = node[i];
        // Add contribution of node w
      }

    }
  }
  // Add contribution of node u
  // get ans in case ans is related to subtree
  if (!keep) {
    for (int i = tin[u]; i <= tout[u]; ++i) {
      int w = node[i];
      // remove contribution of node w
    }
    // Data structure in initial state (empty contribution)
  }
}
dfs(0, 0);  dsu(0, 0, 0);