vector<int> adj[N];
int t = 0;
vector<int> tin(N, -1), low(N), ap;
void dfs (int u, int p) {
  tin[u] = low[u] = t++;
  int is_ap = 0, child = 0;
  for (int v: adj[u]) {
    if (v != p) {
      if (tin[v] != -1) {
        low[u] = min(low[u], tin[v]);
      }
      else {
        child++;
        dfs(v, u);
        if (tin[u] <= low[v]) {
          is_ap = 1;
        }
        low[u] = min(low[u], low[v]);
      }
    }
  }
  if ((p != -1 or child > 1) and is_ap)  ap.push_back(u);
}
dfs(0, -1);