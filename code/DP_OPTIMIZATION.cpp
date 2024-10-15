## CHT
vector<int> m, c;
// Insert
int mi, ci;  cin >> mi >> ci;
while (sz >= 2) {
  if (1ll*(ci-c[sz-2])*(m[sz-2]-m[sz-1]) <= 1ll*(c[sz-1]-c[sz-2])*(m[sz-2]-mi)) {
    m.pop_back();  c.pop_back();
    sz--;
  } else break;
}
m.push_back(mi);  c.push_back(ci);  sz++;
// Query
int x;  cin >> x;
int lo = 0, hi = sz-1;
while (lo < hi) {
  int mid = lo+hi>>1;
  if (1ll*m[mid]*x+c[mid] > 1ll*m[mid+1]*x+c[mid+1]) lo = mid+1;
  else  hi = mid;
}
cout << 1ll*m[lo]*x+c[lo] << '\n';
## Dynamic CHT
const ll IS_QUERY = -(1LL << 62);
struct line {
  ll m, b;
  mutable function <const line*()> succ;
  bool operator < (const line &rhs) const {
    if (rhs.b != IS_QUERY) return m < rhs.m;
    const line *s = succ();
    if (!s) return 0;
    ll x = rhs.m;
    return b - s -> b < (s -> m - m) * x;
  }
};
struct CHT : public multiset <line> { 
  bool bad (iterator y) {
    auto z = next(y);
    if (y == begin()) {
      if (z == end()) return 0;
      return y -> m == z -> m && y -> b <= z -> b;
    }
    auto x = prev(y);
    if (z == end()) return y -> m == x -> m && y -> b <= x -> b;
    return 1.0 * (x -> b - y -> b) * (z -> m - y -> m) >= 1.0 * (y -> b - z -> b) * (y -> m - x -> m);
  }
  void add (ll m, ll b) {
    auto y = insert({m, b});
    y -> succ = [=] {return next(y) == end() ? 0 : &*next(y);};
    if (bad(y)) {erase(y); return;}
    while (next(y) != end() && bad(next(y))) erase(next(y));
    while (y != begin() && bad(prev(y))) erase(prev(y));
  }

  ll eval (ll x) {
    auto l = *lower_bound((line) {x, IS_QUERY});
    return l.m * x + l.b;
  }
};
// To find maximum
CHT cht;
cht.add(m, c);
y_max = cht.eval(x);
// To find minimum
CHT cht;
cht.add(-m, -c);
y_min = -cht.eval(x);
## DnC
// Divide an array into k parts
// Minimize the sum of squre of each subarray
ll pref[N], dp[N][N];
void compute(int l, int r, int j, int kl, int kr) {
  if (l > r)  return ;
  int m = (l + r) / 2;
  array<ll, 2> best = {LLONG_MAX, -1};
  for (int k = kl; k <= min(m - 1, kr); ++k) {
    best = min(best, {dp[k][j - 1] + (pref[m] - pref[k]) * (pref[m] - pref[k]), k});
  }
  dp[m][j] = best[0];
  compute(l, m - 1, j, kl, best[1]);
  compute(m + 1, r, j, best[1], kr);
}
## Knuth
// Divide an array into n parts.
// Cost of each division is subarray sum
// Minimize the cost
ll dp[n][n], opt[n][n];
for (int i = 0; i < n; ++i) {
  for (int j = 0; j < n; ++j) {
    dp[i][j] = LLONG_MAX;
  }
  opt[i][i] = i;
  dp[i][i] = 0;
}
for (int i = n - 2; i >= 0; --i) {
  for (int j = i + 1; j < n; ++j) {
    for (int k = opt[i][j - 1]; k <= min(j - 1ll, opt[i + 1][j]); ++k) {
      if (dp[i][j] >= dp[i][k] + dp[k + 1][j] + (pref[j + 1] - pref[i])) {
        dp[i][j] = dp[i][k] + dp[k + 1][j] + (pref[j + 1] - pref[i]);
        opt[i][j] = k;
      }
    }
  }
}
cout << dp[0][n - 1] << "\n";
## Lichao Tree
const int N = int(5e4 + 2);
const ll INF = ll(1e17);
vector<vector<ll> > tree(4*N, {0, INF});
ll f(vector<ll> line, int x){
return line[0] * x + line[1];
}
void insert(vector<ll> line, int lo = 1, int hi = N, int i = 1){
  int m = (lo + hi) / 2;
  bool left = f(line, lo) < f(tree[i], lo);
  bool mid = f(line, m) < f(tree[i], m);
  if(mid) swap(tree[i], line);
  if(hi - lo == 1) return;
  else if(left != mid) insert(line, lo, m, 2*i);
  else insert(line, m, hi, 2*i+1);
}
ll query(int x, int lo = 1, int hi = N, int i = 1){
  int m = (lo+hi)/2;
  ll curr = f(tree[i], x);
  if(hi-lo==1) return curr;
  if(x<m) return min(curr, query(x, lo, m, 2*i));
  else return min(curr, query(x, m, hi, 2*i+1));
}