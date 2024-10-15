// Rerooting Technique
vector<array<ll, 2>> down(N), up(N);
void dfs() {
  // calculate down dp
}
void dfs2() {
  ll pref = ?;
  for (auto v: adj[u]) {
    // update up[v] and pref
  }
  reverse(adj[u].begin(), adj[u].end());
  ll suf = ?;
  for (auto v: adj[u]) {
    // update up[v] and suf
  }
  for (auto v: adj[u]) {
    dfs2(v)
  }
}