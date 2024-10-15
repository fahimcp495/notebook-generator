// p[0][i] = half length of longest even palindrome around pos i-1, i and starts at i-p[0][i] and ends at i+p[0][i]-1
// p[1][i] = longest odd (half rounded down) palindrome around pos i and starts at i-p[1][i] and ends at i+p[1][i]
vector<vector<int>> manacher(string &s) {
  int n = s.size();
  vector<vector<int>> p(2, vector<int> (n));
  for (int z = 0; z < 2; ++z) {
    for (int i=0, l=0, r=0; i<n; ++i) {
      int t = r-i+!z;
      if (i<r) {
        p[z][i] = min(t, p[z][l+t]);
      }
      int L = i-p[z][i], R = i+p[z][i]-!z;
      while (L>=1 and R+1<n and s[L-1]==s[R+1]) {
        p[z][i]++, L--, R++;
      }
      if (R>r) {
        l=L, r=R;
      }
    }
  }
  return p;
}