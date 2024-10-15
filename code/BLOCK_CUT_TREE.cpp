vector<int> adj[N];
vector<int> tin(N, -1), lo(N), is_ap(N), bcc[N];
stack<int> stk;
int t = 0, tot = 0;

void pop_bcc(int u, int v) {
  bcc[tot].push_back(u);
  while (bcc[tot].back() != v) {
    bcc[tot].push_back(stk.top());
    stk.pop();
  }
  tot++;
}
void dfs (int u, int p) {
  tin[u] = lo[u] = t++;
  stk.push(u);
  int ch = 0;
  for (auto v: adj[u]) {
    if (v != p) {
      if (tin[v] != -1) {
        lo[u] = min(lo[u], tin[v]);
      }
      else {
        ch++;
        dfs(v, u);
        if ((p != -1 or ch > 1) and tin[u] <= lo[v]) {
          // is_ap[u] = 1;
          pop_bcc(u, v);
        }
        lo[u] = min(lo[u], lo[v]);
      }
    }
  }
}
void process_bcc (int n) {
  for (int u = 0; u < n; ++u) {
    tin[u] = -1;
    is_ap[u] = 0;
    bcc[u].clear();
  }
  t = tot = 0;
  for (int u = 0; u < n; ++u) {
    if (tin[u] == -1) {
      dfs(u, -1);
      if (!stk.empty()) {
        while (!stk.empty()) {
          bcc[tot].push_back(stk.top());
          stk.pop();
        }
        tot++;
      }
    }
  }
}
int nn;
vector<int> comp_num(N), bct_adj[N];
void build_bct(int n) {
  process_bcc(n);
  int nn = tot;
  for (int u = 0; u < n; ++u) {
    if (is_ap[u]) {
      comp_num[u] = nn++;
    }
  }
  for (int i = 0; i < tot; ++i) {
    for (auto u: bcc[i]) {
      if (is_ap[u]) {
        u = comp_num[u];
        bct_adj[i].push_back(u);
        bct_adj[u].push_back(i);
      }
      else {
        comp_num[u] = i;
      }
    }
  }
}