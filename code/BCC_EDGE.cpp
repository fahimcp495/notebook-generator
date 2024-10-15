vector<array<int, 2>> edges, adj[N];
vector <int> tin(N), lo(N), is_ap(N), bcc[N], bcc_ed[N];
int t = 0, tot = 0;
stack<int> stk;

void pop_bcc(int e) {
  do {
    bcc_ed[tot].push_back(stk.top());  stk.pop();
  } while (bcc_ed[tot].back() != e);
  tot++;
}

void dfs(int u, int p = -1) {
  int ch = 0;
  tin[u] = lo[u] = t++;
  for(auto [v, e] : adj[u]) {
    if (v == p)  continue;
    if (tin[v] != -1) {
      if (tin[u] > tin[v]) {
        lo[u] = min(lo[u], tin[v]);
        stk.push(e);
      }
    }
    else {
      ch++;
      stk.push(e);
      dfs(v, u);
      if ((p != -1 or ch > 1) and tin[u] <= lo[v]) {
        is_ap[u] = 1;
        pop_bcc(e);
      }
      lo[u] = min(lo[u], lo[v]);
    }
  }
}

void procces_bcc(int n) {
  for (int i = 0; i < n; ++i) {
    tin[i] = -1, is_ap[i] = 0;
    bcc_ed[i].clear();
    bcc[i].clear();
  }
  t = tot = 0;

  for (int u = 0; u < n; ++u) {
    if (tin[u] == -1) {
      dfs(u, -1);
      if (!stk.empty()) {
        while (!stk.empty()) {
          bcc_ed[tot].push_back(stk.top());  stk.pop();
        }
        tot++;
      }
    }
  }

  for (int i = 0; i < tot; ++i) {
    for (auto e: bcc_ed[i]) {
      auto [u, v] = edges[e];
      bcc[i].push_back(u);
      bcc[i].push_back(v);
    }
  }

  for (int i = 0; i < tot; ++i) {
    sort(bcc[i].begin(), bcc[i].end());
    bcc[i].erase(unique(bcc[i].begin(), bcc[i].end()), bcc[i].end());
  }
}