## FFT
struct cplx {
  ld a, b;
  cplx(ld a=0, ld b=0):a(a), b(b) {}
  const cplx operator + (const cplx &z) const { return cplx(a+z.a, b+z.b); }
  const cplx operator - (const cplx &z) const { return cplx(a-z.a, b-z.b); }
  const cplx operator * (const cplx &z) const { return cplx(a*z.a-b*z.b, a*z.b+b*z.a); }
  const cplx operator / (const ld &k) const { return cplx(a/k, b/k); }
};

const ld PI=acos(-1);
vector<int> rev;

void pre(int sz){
  if(rev.size()==sz)  return ;
  rev.resize(sz);
  rev[0]=0;
  int lg_n = __builtin_ctz(sz);
  for (int i = 1; i < sz; ++i)  rev[i] = (rev[i>>1] >> 1) | ((i&1)<<(lg_n-1));
}
void fft(vector<cplx> &a, bool inv){
  int n = a.size();
  for (int i = 1; i < n-1; ++i) if(i<rev[i])  swap(a[i], a[rev[i]]);
  for (int len = 2; len <= n; len <<= 1){
    ld t = 2*PI/len*(inv? -1: 1);
    cplx wlen = {cosl(t), sinl(t)};
    int st = 0;
    for (int st = 0; st < n; st += len){
      cplx w(1);
      for (int i = 0; i < len/2; ++i){
        cplx ev = a[st+i];
        cplx od = a[st+i+len/2]*w;
        a[st+i] = ev+od;
        a[st+i+len/2] = ev-od;
        w = w*wlen;
      }
    }
  }
  if(inv){
    for(cplx &z: a){
      z = z/n;
    }
  }
}

vector<ll> mul(vector<ll> &a, vector<ll> &b){
  int n = a.size(), m = b.size(), sz = 1;
  while (sz < n+m-1)  sz <<= 1;
  vector<cplx> x(sz), y(sz), z(sz);
  for (int i = 0; i < sz; ++i){
    x[i] = cplx(i<n? a[i]: 0, 0);
    y[i] = cplx(i<m? b[i]: 0, 0);
  }
  pre(sz);
  fft(x, 0);
  fft(y, 0);
  for (int i = 0; i < sz; ++i){
    z[i] = x[i] * y[i];
  }
  fft(z, 1);
  vector<ll> c(n+m-1);
  for (int i = 0; i < n+m-1; ++i){
    c[i] = round(z[i].a);
  }
  return c;
}

## NTT
const int mod = 998244353;
const int root = 15311432;
const int k = 1 << 23;

int root_1;
vector<int> rev;

ll bigmod(ll a, ll b, ll mod){
  a %= mod;
  ll ret = 1;
  while(b){
    if(b&1) ret = ret*a%mod;
    a = a*a%mod;
    b >>= 1;
  }
  return ret;
}

void pre(int sz){
  root_1 = bigmod(root, mod-2, mod);
  if(rev.size()==sz)  return ;
  rev.resize(sz);
  rev[0]=0;
  int lg_n = __builtin_ctz(sz);
  for (int i = 1; i < sz; ++i)  rev[i] = (rev[i>>1] >> 1) | ((i&1)<<(lg_n-1));
}

void fft(vector<int> &a, bool inv){
  int n = a.size();

  for (int i = 1; i < n-1; ++i) if(i<rev[i])  swap(a[i], a[rev[i]]);

  for (int len = 2; len <= n; len <<= 1) {
    int wlen = inv ? root_1 : root;
    for (int i = len; i < k; i <<= 1){
      wlen = 1ll*wlen*wlen%mod;
    }
    for (int st = 0; st < n; st += len) {
      int w = 1;
      for (int j = 0; j < len / 2; j++) {
        int ev = a[st+j];
        int od = 1ll*a[st+j+len/2]*w%mod;
        a[st+j] = ev + od < mod ? ev + od : ev + od - mod;
        a[st+j+len/2] = ev - od >= 0 ? ev - od : ev - od + mod;
        w = 1ll * w * wlen % mod;
      }
    }
  }

  if (inv) {
    int n_1 = bigmod(n, mod-2, mod);
    for (int & x : a)
      x = 1ll*x*n_1%mod;
  }
}

vector<int> mul(vector<int> &a, vector<int> &b){
  int n = a.size(), m = b.size(), sz = 1;
  while (sz < n+m-1)  sz <<= 1;
  vector<int> x(sz), y(sz), z(sz);
  for (int i = 0; i < sz; ++i){
    x[i] = i<n? a[i]: 0;
    y[i] = i<m? b[i]: 0;
  }
  pre(sz);
  fft(x, 0);
  fft(y, 0);
  for (int i = 0; i < sz; ++i){
    z[i] = 1ll* x[i] * y[i] % mod;
  }
  fft(z, 1);
  z.resize(n+m-1);
  return z;
}

## Any mod
const int N = 3e5 + 9, mod = 998244353;

struct base {
  double x, y;
  base() { x = y = 0; }
  base(double x, double y): x(x), y(y) { }
};
inline base operator + (base a, base b) { return base(a.x + b.x, a.y + b.y); }
inline base operator - (base a, base b) { return base(a.x - b.x, a.y - b.y); }
inline base operator * (base a, base b) { return base(a.x * b.x - a.y * b.y, a.x * b.y + a.y * b.x); }
inline base conj(base a) { return base(a.x, -a.y); }
int lim = 1;
vector<base> roots = {{0, 0}, {1, 0}};
vector<int> rev = {0, 1};
const double PI = acosl(- 1.0);
void ensure_base(int p) {
  if(p <= lim) return;
  rev.resize(1 << p);
  for(int i = 0; i < (1 << p); i++) rev[i] = (rev[i >> 1] >> 1) + ((i & 1)  <<  (p - 1));
  roots.resize(1 << p);
  while(lim < p) {
    double angle = 2 * PI / (1 << (lim + 1));
    for(int i = 1 << (lim - 1); i < (1 << lim); i++) {
      roots[i << 1] = roots[i];
      double angle_i = angle * (2 * i + 1 - (1 << lim));
      roots[(i << 1) + 1] = base(cos(angle_i), sin(angle_i));
    }
    lim++;
  }
}
void fft(vector<base> &a, int n = -1) {
  if(n == -1) n = a.size();
  assert((n & (n - 1)) == 0);
  int zeros = __builtin_ctz(n);
  ensure_base(zeros);
  int shift = lim - zeros;
  for(int i = 0; i < n; i++) if(i < (rev[i] >> shift)) swap(a[i], a[rev[i] >> shift]);
  for(int k = 1; k < n; k <<= 1) {
    for(int i = 0; i < n; i += 2 * k) {
      for(int j = 0; j < k; j++) {
        base z = a[i + j + k] * roots[j + k];
        a[i + j + k] = a[i + j] - z;
        a[i + j] = a[i + j] + z;
      }
    }
  }
}
//eq = 0: 4 FFTs in total
//eq = 1: 3 FFTs in total
vector<int> multiply(vector<int> &a, vector<int> &b, int eq = 0) {
  int need = a.size() + b.size() - 1;
  int p = 0;
  while((1 << p) < need) p++;
  ensure_base(p);
  int sz = 1 << p;
  vector<base> A, B;
  if(sz > (int)A.size()) A.resize(sz);
  for(int i = 0; i < (int)a.size(); i++) {
    int x = (a[i] % mod + mod) % mod;
    A[i] = base(x & ((1 << 15) - 1), x >> 15);
  }
  fill(A.begin() + a.size(), A.begin() + sz, base{0, 0});
  fft(A, sz);
  if(sz > (int)B.size()) B.resize(sz);
  if(eq) copy(A.begin(), A.begin() + sz, B.begin());
  else {
    for(int i = 0; i < (int)b.size(); i++) {
      int x = (b[i] % mod + mod) % mod;
      B[i] = base(x & ((1 << 15) - 1), x >> 15);
    }
    fill(B.begin() + b.size(), B.begin() + sz, base{0, 0});
    fft(B, sz);
  }
  double ratio = 0.25 / sz;
  base r2(0,  - 1), r3(ratio, 0), r4(0,  - ratio), r5(0, 1);
  for(int i = 0; i <= (sz >> 1); i++) {
    int j = (sz - i) & (sz - 1);
    base a1 = (A[i] + conj(A[j])), a2 = (A[i] - conj(A[j])) * r2;
    base b1 = (B[i] + conj(B[j])) * r3, b2 = (B[i] - conj(B[j])) * r4;
    if(i != j) {
      base c1 = (A[j] + conj(A[i])), c2 = (A[j] - conj(A[i])) * r2;
      base d1 = (B[j] + conj(B[i])) * r3, d2 = (B[j] - conj(B[i])) * r4;
      A[i] = c1 * d1 + c2 * d2 * r5;
      B[i] = c1 * d2 + c2 * d1;
    }
    A[j] = a1 * b1 + a2 * b2 * r5;
    B[j] = a1 * b2 + a2 * b1;
  }
  fft(A, sz); fft(B, sz);
  vector<int> res(need);
  for(int i = 0; i < need; i++) {
    long long aa = A[i].x + 0.5;
    long long bb = B[i].x + 0.5;
    long long cc = A[i].y + 0.5;
    res[i] = (aa + ((bb % mod) << 15) + ((cc % mod) << 30))%mod;
  }
  return res;
}

vector<int> pow(vector<int>& a, int p) {
  vector<int> res;
  res.emplace_back(1);
  while(p) {
    if(p & 1) res = multiply(res, a);
    a = multiply(a, a, 1);
    p >>= 1;
  }
  return res;
}
int main() {
  int n, k; cin >> n >> k;
  vector<int> a(10, 0);
  while(k--) {
    int m; cin >> m;
    a[m] = 1;
  }
  vector<int> ans = pow(a, n / 2);
  int res = 0;
  for(auto x: ans) res = (res + 1LL * x * x % mod) % mod;
  cout << res << '\n';
  return 0;
}

## Online NTT
void solve() {
  f[0]=1; // base case
  for(int i=0; i<=MAX; i++) {
    // Doing the part 1
    f[i+1]=(f[i+1]+f[i]*A[0])%mod;
    f[i+2]=(f[i+2]+f[i]*A[1])%mod;
    if(!i) continue;
    // part 2
    int limit=(i&-i);
    for(int p=2; p<=limit; p*=2) {
      convolve(i-p,i-1,p,min(2*p-1,MAX));
    }
  }
}
void convolve(int l1, int r1, int l2, int r2) {
  int n=max(r1-l1+1,r2-l2+1);
  int t=1;
  while(t<n) t<<=1;
  n=t;
  vector<ll> a(n), b(n);
  for(int i=l1; i<=r1; i++) a[i-l1]=f[i];
  for(int i=l2; i<=r2; i++) b[i-l2]=A[i];
  vector<ll> ret=fft::multiply(a,b);
    for(int i=0; i<ret.size(); i++) {
    int idx=i+l1+l2+1;
    if(idx>MAX) break;
    // adding to the appropriate entry
    f[idx]+=ret[i];
    f[idx]%=mod;
  }
}

## FWHT (AND, OR, XOR)
- Time complexity: O(nlogn)
- AND, OR works for any modulo, XOR works for only prime
- All works without mod
- size must be power of two

const int mod = 998244353;

void fwht(vector<int> &a, int inv, int f) {
  int sz = a.size();
  for (int len = 1; 2 * len <= sz; len <<= 1) {
    for (int i = 0; i < sz; i += 2 * len) {
      for (int j = 0; j < len; j++) {
        int x = a[i + j];
        int y = a[i + j + len];

        if (f == 0) {
          if (!inv)  a[i + j] = y, a[i + j + len] = add(x,  y);
          else  a[i + j] = sub(y, x), a[i + j + len] = x;
        }
        else if (f == 1) {
          if (!inv)  a[i + j + len] = add(x, y);
          else  a[i + j + len] = sub(y, x);
        }
        else {
          a[i + j] = add(x, y);
          a[i + j + len] = sub(x, y);
        }
      }   
    }
  }
}

vector<int> mul(vector<int> a, vector<int> b, int f) { // 0:AND, 1:OR, 2:XOR
  int sz = a.size();
  fwht(a, 0, f);  fwht(b, 0, f);
  vector<int> c(sz);
  for (int i = 0; i < sz; ++i) {
    c[i] = 1ll * a[i] * b[i] % mod;
  }
  fwht(c, 1, f);
  if (f) {
    int sz_inv = poww(sz, mod - 2, mod);
    for (int i = 0; i < sz; ++i) {
      c[i] = 1ll * c[i] * sz_inv % mod;
    }
  }
  return c;
}

## subset convolution
vector<int> subset_conv (vector<int> a, vector<int> b) {
  int n = a.size();
  int lg = log2(n);
  vector<int> cnt(n);
  vector<vector<int>> fa(lg + 1, vector<int> (n)), fb(lg + 1, vector<int> (n)), g(lg + 1, vector<int> (n));
  for (int i = 0; i < n; ++i) {
    cnt[i] = cnt[i >> 1] + (i & 1);
    fa[cnt[i]][i] = a[i] % mod;
    fb[cnt[i]][i] = b[i] % mod;
  }
  for (int k = 0; k <= lg; ++k) {
    fwht(fa[k], 0, 1);  fwht(fb[k], 0, 1);
  }
  for (int k = 0; k <= lg; ++k) {
    for (int j = 0; j <= k; ++j) {
      for (int i = 0; i < n; ++i) {
        g[k][i] = add(g[k][i], 1ll * fa[j][i] * fb[k - j][i] % mod);
      }
    }
  }
  for (int k = 0; k <= lg; ++k) {
    fwht(g[k], 1, 1);
  }
  vector<int> c(n);
  for (int i = 0; i < n; ++i) {
    c[i] = g[cnt[i]][i];
  }
  return c;
}
