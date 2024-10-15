## Floor
ll floor (ll n, ll k) {
  if (n >= 0)  return n / k;
  return  (n - (k - 1)) / k;
}
## Ceil
ll ceil (ll n, ll k) {
  if (n >= 0)  return (n + k - 1) / k;
  return n / k;
}
## Modular Inverse O(N)
inv[1] = 1;
for(int i = 2; i < N; ++i) {
  inv[i] = -(mod / i) * inv[mod % i] % mod;
  inv[i] += mod;
}
## Harmonic Lemma (ceill)
ll i = 1;
while (i < n) {
  ll cval = (n + i - 1) / i;
  ll j = (n + cval - 2) / (cval - 1);
  // ceil(n/i)...ceil(n/(j - 1)) = cval
  i = j;
}
ll egcd(ll a, ll b, ll &x, ll &y){
  if(b == 0) { x=1, y=0; return a;}
  ll g = egcd(b, a%b, y, x);
  y -= a/b*x;  return g;
}
ll mod_inv(ll a, ll m){
  ll x, y;
  ll g = egcd(a, m, x, y);
  if(g != 1)  return -1;  //no solution
  return (x%m+m)%m;
}

## Linear-sieve
int lpf[N], pm[N], pcnt = 0;
for (int i = 2; i < N; ++i) {
  if (!lpf[i])  lpf[i] = i, pm[pcnt++] = i;
  for (int j = 0; j < sz; ++j) {
    int p = pm[j];
    if (lpf[i] < p or i * p >= N)  break;
    lpf[i * p] = p;
  }
}

## Miller-Rabin
bool isp(ll n){
  if(n==2 || n == 3)  return 1;
  if(n<=1 || n%2==0)  return 0;
  for (int k = 0; k < 10; ++k){
    ll a = 2+rand()%(n-2);
    ll s = n-1;
    while(!(s&1)) s>>=1;
    if(powmod(a, s, n) == 1)  continue;
    int iscomp = 1;
    while(s!=n-1){
      if(powmod(a, s, n)==n-1){
        iscomp = 0;
        break;
      }
      s=s<<1;
    }
    if(iscomp) return 0;
  }
  return 1;
}

## Miller-Rabin Deterministic:
bool check_composite(u64 n, u64 a, u64 d, int s) {
  u64 x = binpower(a, d, n);
  if (x == 1 || x == n - 1)
    return false;
  for (int r = 1; r < s; r++) {
    x = (u128)x * x % n;
    if (x == n - 1)
      return false;
  }
  return true;
}

bool isp(u64 n) {
  if (n < 2)
    return false;
  int r = 0;
  u64 d = n - 1;
  while ((d & 1) == 0) {
    d >>= 1;
    r++;
  }

  for (int a : {2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37}) {
    if (n == a)
      return true;
    if (check_composite(n, a, d, r))
      return false;
  }
  return true;
}

## Prime Factorize of large number(Pollard Rho):
ll f(ll x, ll c, ll n){
  return (mulmod(x,x,n)+c)%n;
}
ll pollard_rho(ll n){
  if(n == 1)  return 1;
  if(n%2 == 0)  return 2;
  ll x = rand()%(n-2)+2;
  ll y = x;
  ll c = rand()%(n-1)+1;
  ll g = 1;
  while (g == 1){
    x = f(x, c, n);
    y = f(y, c, n);
    y = f(y, c, n);
    g = __gcd(abs(x-y), n);
  }
  return g;
}
vector<ll> prime_factorize(ll n){
  if(n<=1)  return vector<ll>();
  if(isp(n))  return vector<ll> ({n});
  ll d = pollard_rho(n);
  vector<ll> v = factorize(d);
  vector<ll> w = factorize(n/d);
  v.insert(v.end(), w.begin(), w.end());
  sort(v.begin(), v.end());
  return v;
}
// auto pf = prime_factorize(n);

## Number of divisors of n O(n^1/3):
int nod(ll n){
  sieve();
  int ret = 1;
  for (int i = 2; 1LL*i*i*i <= n; ++i){
    if(isp[i]){
      int e = 0;
      while(n%i == 0){
        e++;
        n /= i;
      }
      ret *= e+1;
    }
  }
  ll sq = sqrt(1.0L*n);
  if(isprime(n))  ret *= 2;
  else if(n == sq*sq and isprime(sq))  ret *= 3;
  else if(n!=1) ret *= 4;
  return ret;
}

## Smallest inverse phi
ll inv_phi(ll phi, ll n, int pc) {
  if (phi == 1)  return n;
  if (pc == -1)  return INF;
  ll ret = inv_phi(phi, n, pc - 1);
  if (phi % (p[pc] - 1) == 0) {
    phi /= (p[pc] - 1);
    n = n / (p[pc] - 1) * p[pc];
    while (phi % p[pc] == 0) {
      phi /= p[pc];
    }
    ret = min(ret, inv_phi(phi, n, pc - 1));
  }
  return ret;
}
ll phi;  cin >> phi;
if (phi & 1) {
  cout << (phi == 1) << "\n";
}
else {
  for (int i = 1; i * i <= phi; ++i) {
    if (phi % i == 0) {
      if (isp(i + 1)) {
        p.push_back(i + 1);
      }
      if (i * i != phi and isp(phi / i + 1)){
        p.push_back(phi / i + 1);
      }
    }
  }
  sort(p.begin(), p.end());
  ll ans = inv_phi(phi, phi, p.size() - 1);
  cout << (ans == INF? 0: ans) << "\n";
}
## GCD sum function from 1 to N:
ll phi[N], g[N];
void pcgsm(){  //pre calculate gcd sum fucntion
  pcphi();
  for (int i = 1; i < N; ++i){
    for (int j = i; j < N; j+=i){
      g[j] += i*phi[j/i];
    }
  }
}
## All Pair gcd sum:
for (int i = 1; i < N; ++i) {
  for (int j = i; j < N; j += i) {
    gcd_sum[j] += 1ll * phi[i] * (j / i);
  }
  gcd_sum[i] -= i;
  pref_gcd_sum[i] = pref_gcd_sum[i - 1] + gcd_sum[i];
}
## LCM sum function of n:
ll lsm(ll n){
  ll ret=0;
  for(ll d=1; d*d<=n; d++){
    if(n%d==0){
      ret += d*phi(d);
      if(n/d!=d)  ret += n/d*phi(n/d);
    }
  }
  return (ret+1)*n/2;
}
## LCM sum function from 1 to N
ll phi[N], l[N];
void pclsm(){  //pre calculate lcm sum function
  pcphi();
  for (int i = 1; i < N; ++i){
    for (int j = i; j < N; j+=i){
      l[j] += i*phi[i];
    }
  }
  for (int i = 1; i < N; ++i){
    l[i] = (l[i]+1)*i/2;
  }
}
## All pair lcm sum:
for (int i = 1; i < N; ++i) {
  for (int j = i; j < N; j += i) {
    lcm_sum[j] += i * phi[i];
  }
  lcm_sum[i]++;
  lcm_sum[i] /= 2;
  lcm_sum[i] *= i;
  lcm_sum[i] -= i;
  pref_lcm_sum[i] = lcm_sum[i];
  pref_lcm_sum[i] += pref_lcm_sum[i - 1];
}
## Number of co-prime pairs of an array:
vector<ll> cnt(A);
for (int xi: x) {
  for (int d = 1; d * d <= xi; ++d) {
    if (xi % d == 0) {
      cnt[d]++;
      if (xi / d != d) {
        cnt[xi / d]++;
      }
    }
  }
}
ll ans = 0;
for (int i = 1; i < A; ++i) {
  if (!sq_free[i])  continue;
  ll ways = cnt[i] * (cnt[i] - 1) / 2;
  if (pf[i].size() & 1 ^ 1)  ans += ways;
  else  ans -= ways;
}
## All pair gcd sum of an array:
vector<ll> cnt(A);
for (auto ai: a) {
  for (int d = 1; d * d <= ai; ++d) {
    if (ai % d == 0) {
      cnt[d]++;
      if (ai / d != d) {
        cnt[ai / d]++;
      }
    }
  }
}
ll sum = 0;
vector<ll> left(A);
iota(left.begin(), left.end(), 0);
for (int i = 1; i < A; ++i) {
  ll add = left[i] * cnt[i] * (cnt[i] - 1) / 2;
  sum += add;
  for (int j = 2 * i; j < A; j += i) {
    left[j] -= left[i];
  }
}
## Count elements ai s.t. gcd(x, ai) = g
for (auto d: divs[x / g]) {
  f += mu[d] * cnt[d * g];
}
## CRT
ll crt(ll r1, ll m1, ll r2, ll m2){
  if(m1<m2) swap(r1, r2), swap(m1, m2);
  ll p, q, g = egcd(m1, m2, p, q);
  if((r2-r1)%g !=0 )  return -1;  //no solution
  ll x = (r2-r1)%m2*p%m2*m1/g + r1;
  return x<0? x+m1*m2/g: x;
}
ll crt(vector<ll>& r, vector<ll>& m){
  ll x = r[0], M=m[0];
  for (int i = 1; i < r.size(); ++i){
    x = crt(x, M, r[i], m[i]);
    ll g = __gcd(M, m[i]);
    M = (M/g)*(m[i]/g);
  }
  return x;
}
## Discrete Logarithm
ll discrete_log(ll a, ll b, ll m) {
  a %= m, b %= m;
  if(a == 0){
    return (b == 0? 1: -1);
  }

  ll k = 1, add = 0, g;
  while ((g = __gcd(a, m)) > 1) {
    if (b == k)  return add;
    if (b % g)  return -1;
    b /= g, m /= g, k = (k * a / g) % m, ++add;
  }
  int n = sqrt(m) + 1;
  unordered_map<int, int> vals;
  for (ll q = 0, cur = b; q <= n; ++q) {
    vals[cur] = q;
    cur = (cur * a) % m;
  }
  ll an = 1;
  for (int i = 0; i < n; ++i) {
    an = (an * a) % m;
  }
  for (ll p = 1, cur = k; p <= n; ++p) {
    cur = (cur * an) % m;
    if (vals.count(cur)) {
      return n * p - vals[cur] + add;
    }
  }
  return -1;
}
## Primitive Root
int get_gen(int p) {
  int n = p - 1;
  vector<int> pfs;
  for (int i = 2; i * i <= n; ++i) {
    if (n % i == 0) {
      pfs.push_back(i);
      while (n % i == 0) n /= i;
    }
  }
  if (n > 1) pfs.push_back(n);
  n = p - 1;
  for (int g = 2; g < p; ++g) {
    int ok = 1;
    for (auto pf: pfs) {
      if (poww(g, n / pf, p) == 1) {
        ok = 0;
        break;
      }
    }
    if (ok) return g;
  }
  return -1;
}
