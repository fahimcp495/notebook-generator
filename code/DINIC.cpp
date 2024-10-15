// V^2E, sqrt(E)E, sqrt(V)E(bpm)
// Effective flows are adj[u][3] where adj[u][3] > 0
ll get_max_flow(vector<array<int, 3>> edges, int n, int s, int t) {
  vector<array<ll, 4>> adj[n];
  for (auto [u, v, c]: edges) {
    adj[u].push_back({v, (int)adj[v].size(), c, 0});
    adj[v].push_back({u, (int)adj[u].size() - 1, 0, 0});
  } 

  ll max_flow = 0;
  while (true) {
    queue<int> q;  q.push(s);
    vector<int> dis(n, -1);  dis[s] = 0;
    while (!q.empty()) {
      int u = q.front();  q.pop();
      for (auto [v, idx, c, f]: adj[u]) {
        if (dis[v] == -1 and c > f) {
          q.push(v);
          dis[v] = dis[u] + 1;
        }
      }
    }
    if (dis[t] == -1)  break;
    vector<int> next(n);
    function<ll(int, ll)> dfs = [&] (int u, ll flow) {
      if (u == t)  return flow;
      while (next[u] < adj[u].size()) {
        auto &[v, idx, c, f] = adj[u][next[u]++];
        if (c > f and dis[v] == dis[u] + 1) {
          ll bn = dfs(v, min(flow, c - f));
          if (bn > 0) {
            f += bn;
            adj[v][idx][3] -= bn;
            return bn;
          }
        }
      }
      return 0ll;
    };

    while (ll flow = dfs(s, LLONG_MAX)) {
      max_flow += flow;
    }
  }
  return max_flow;
}