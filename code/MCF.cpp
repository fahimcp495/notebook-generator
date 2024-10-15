struct MCF {
  int n;
  vector<vector<array<ll, 5>>> adj;    // v, pos of u in v, cap, cost, flow
  vector<ll> dis, par, pos;
  MCF(int n): n(n), adj(n), dis(n), par(n), pos(n) {}
  void add_edge(int u, int v, int cap, int cost) {
    adj[u].push_back({v, adj[v].size(), cap, cost, 0});
    adj[v].push_back({u, adj[u].size() - 1, 0, -cost, 0});
  }
  ll spfa(int s, int t) {
    dis.assign(n, INF);
    vector<ll> mn_cap(n, INF), inq(n);
    queue<int> q;
    q.push(s), inq[s] = 1, dis[s] = 0;
    while (!q.empty()) {
      int u = q.front();  q.pop();
      inq[u] = 0;
      for (int i = 0; i < adj[u].size(); ++i) {
        auto [v, idx, cap, cost, flow] = adj[u][i];
        if (cap > flow and dis[v] > dis[u] + cost) {
          dis[v] = dis[u] + cost;
          par[v] = u;
          pos[v] = i;
          mn_cap[v] = min(mn_cap[u], cap - flow);
          q.push(v);
          inq[v] = 1;
        }
      }
    }
    return (mn_cap[t] == INF? 0: mn_cap[t]);
  }
  array<ll, 2> get(int s, int t, ll max_flow = INF) {
    ll flow = 0, mc = 0;
    while (ll f = min(spfa(s, t), max_flow - flow)) {
      flow += f;
      mc += f * dis[t];
      int u = t;
      while (u != s) {
        int p = par[u];
        adj[p][pos[u]][4] += f;
        adj[u][adj[p][pos[u]][1]][4] -= f;
        u = p;
      }
    }
    return {flow, mc};
  }
};

