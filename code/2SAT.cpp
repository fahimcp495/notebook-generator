//CNF: (a | b) ^ (c | d) means (!a -> b) ^ (!b -> a)
// (!a or b) = (-a, b), 1-based indexing
string two_sat(int n, vector<array<int, 2>> clauses) {
  vector<int> adj[2 * n];
  for (auto [a, b]: clauses) {
    if (a > 0)  a = 2 * a - 2;
    else  a = 2 * -a - 1;
    if (b > 0)  b = 2 * b - 2;
    else  b = 2 * -b - 1;
    adj[a ^ 1].push_back(b), adj[b ^ 1].push_back(a);
  }
  vector<vector<int>> sccs = get_sccs(2 * n, adj);
  int tot_scc = sccs.size();
  vector<int> scc_no(2 * n);
  for (int i = 0; i < tot_scc; ++i) {
    for (int u: sccs[i]) {
      scc_no[u] = i;
    }
  }
  string assignment;
  for (int u = 0; u < n; u++) {
    if (scc_no[2 * u] == scc_no[2 * u + 1]) {
      return "";
    }
    if (scc_no[2 * u] < scc_no[2 * u + 1]) {
      assignment += '-';
    }
    else {
      assignment += '+';
    }
  }
  return assignment;
}