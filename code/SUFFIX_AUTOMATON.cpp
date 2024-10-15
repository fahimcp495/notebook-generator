int len[2 * N], lnk[2 * N]{-1}, last, sz = 1;
map<char, int> to[2 * N];
int deg[2 * N];
ll cnt[2 * N], dp[2 * N];
void init(int n) {
  fill(deg, deg + sz, 0);
  fill(cnt, cnt + sz, 0);
  while (sz) to[--sz].clear();
  last = 0, sz = 1;
}
void add (char c, int i) {
  int cur = sz++;
  len[cur] = len[last] + 1;
  cnt[cur] = 1;
  dp[cur] = i;
  int u = last;
  while (u != -1 and !to[u].count(c)) {
    to[u][c] = cur;
    u = lnk[u];
  }
  if (u == -1) {
    lnk[cur] = 0;
  }
  else {
    int v = to[u][c];
    if (len[u] + 1 == len[v]) {
      lnk[cur] = v;
    }
    else {
      int w = sz++;
      len[w] = len[u] + 1, lnk[w] = lnk[v], to[w] = to[v];
      while (u != -1 and to[u][c] == v) {
        to[u][c] = w, u = lnk[u];
      }
      lnk[cur] = lnk[v] = w;
    }
  }
  last = cur;
}

void build() {
  for (int u = 1; u < sz; ++u) {
    deg[lnk[u]]++;
  }
  queue<int> q;
  for (int u = 0; u < sz; ++u) {
    if (!deg[u]) {
      q.push(u);
    }
  }
  while (!q.empty()) {
    int u = q.front(); q.pop();
    int v = lnk[u];
    cnt[v] += cnt[u]; // DP on suffix link tree
    for (auto [c, v]: to[u]) { // DP on DAG
      dp[u] = max(dp[u], dp[v]);
    }
    deg[v]--;
    if (!deg[v]) {
      q.push(v);
    }
  }
}
## Count number of occurrence for each k length substring of s in SA
ll count(string s, int k) {
  ll ret = 0;
  int u = 0, L = 0;
  for (auto c: s) {
    while (u != -1 and !to[u].count(c)) {
      u = lnk[u];
      L = len[u];
    }
    if (u == -1) break;
    u = to[u][c];
    L++;
    while (u and len[lnk[u]] >= k) u = lnk[u], L = len[u];
    if (k <= len[u] and k <= L) {
      ret += cnt[u];
    }
  }
  return ret;
}