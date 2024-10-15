const int N = 1e5+5, A = 26;
int to[N][A], cnt[N], node[N], tot = 1;
vector<int> idx[N];
void add(string &p, int i) {
  int u = 0;
  for (auto c: p) {
    c -= 'a';
    if (!to[u][c]) to[u][c] = tot++;
    u = to[u][c];
  }
  cnt[u]++;
  node[i] = u;
  idx[u].push_back(i);
}
vector<int> slnk(N), olnk(N), adj[N], order;
void build() {
  queue<int> q; q.push(0);
  while (!q.empty()) {
    int u = q.front(); q.pop();
    order.push_back(u);
    for (int c = 0; c < A; ++c) {
      int v = to[u][c];
      if (!v) continue;
      q.push(v);
      dp2[v] = cnt[v];
      if (!u) continue;
      int cur = slnk[u];
      while (cur and !to[cur][c]) cur = slnk[cur];
      slnk[v] = to[cur][c];
      if (cnt[lnk[v]]) olnk[v] = lnk[v];
      else olnk[v] = olnk[lnk[v]];
      adj[to[cur][c]].push_back(v);
      dp2[v] += dp2[slnk[v]];
    }
  }
}

vector<int> idx2[N];
void trav(string &s) {
  int u = 0;
  vector<int> dp(tot);
  for (int i = 0; i < s.size(); ++i) {
    int c = s[i] - 'a';
    while (u and !to[u][c]) u = slnk[u];
    u = to[u][c];
    dp[u]++, idx2[u].push_back(i);
    ans[i] = dp2[i];
    for (int v = u; v; v = olnk[v]) {
      for (auto j: idx[v]) {
        // jth pattern ends at ith position of s
      }
    }
  }
  // Count positions
  reverse(order.begin(), order.end());
  for (auto u: order) {
    dp[slnk[u]] += dp[u];
  }
}
// Find positions of a pattern
int pos[N], f;
void go(int u) {
  for (auto i: idx2[u]) pos[f++] = i;
  for (auto v: adj[u]) go(v);
}
// add(p[i], i); build(); trav(s);
// dp[node[i]] = counts of occurrence of the ith pattern in the text
// go(node[i]) finds the occurrences of the ith pattern in the text
// dp2[i] = number of patterns that ends at ith position of the Text
