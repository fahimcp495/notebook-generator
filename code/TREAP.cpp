## Typical TEAP
struct node {
  ll val, prior, sz, sum;
  node *l, *r;
  node(int val, int prior, int sz) : val(val), prior(prior), sz(sz), sum(0), l(nullptr), r(nullptr){}
};
using pnode = node*;
pnode root;
pnode new_node(ll val){
  return new node(val, rand(), 1);
}
int get_sz(pnode u){
  return u? u->sz: 0;
}
void update(pnode u){
  if (!u)  return ;
  u->sz = get_sz(u->l) + 1 + get_sz(u->r);
  u->sum = u->val + (u->l? u->l->sum: 0) + (u->r? u->r->sum: 0);
}
void split(pnode u, pnode &l, pnode &r, ll val){
  if(!u)  l = r = NULL;
  else if(val > u->val) split(u->r, u->r, r, val), l = u;
  else split(u->l, l, u->l, val), r = u;
  update(u);
}
void merge(pnode &u, pnode l, pnode r){
  if(!l or !r) u = l? l: r;
  if(l->prior > r->prior) merge(l->r, l->r, r),  u = l;
  else merge(r->l, l, r->l),  u = r;
  update(u);
}
void insert(pnode &u, pnode it){
  if(!u)  u = it;
  else if(it->prior > u->prior) split(u, it->l, it->r, it->val), u = it;
  else insert(it->val <= u->val ? u->l: u->r, it);
  update(u);
}
void erase(pnode &u, ll val){
  if(!u)  return ;
  if(val == u->val)  merge(u, u->l, u->r);
  else  erase(val < u->val ? u->l: u->r, val);
  update(u);
}
bool present(pnode u, int x){
  if(!u)  return false;
  if(u->val == x)  return true;
  if(u->val < x) return present(u->r, x);
  return present(u->l, x);
}
ll kth(pnode u, int k){
  if(get_sz(u) < k) return INT_MIN;
  if(get_sz(u->l) == k-1)  return u->val;
  if(get_sz(u->l) < k-1) return kth(u->r, k - get_sz(u->l) - 1);
  return kth(u->l, k);
}
int cnt_less(pnode u, ll x){
  if(!u)  return 0;
  if(x <= u->val)  return cnt_less(u->l, x);
  return get_sz(u->l) + 1 + cnt_less(u->r, x);
}
ll sum_less(pnode u, ll x) {
  if (!u)  return 0;
  if (x <= u->val)  return sum_less(u->l, x);
  return u->val + (u->l? u->l->sum: 0) + sum_less(u->r, x);
}
## Implicit TREAP
struct node {
  ll val, sum;
  int prior, sz, rev;
  node *l, *r;
  node(){}
  node(ll val): val(val), sum(val), prior(rand()), sz(1), rev(0), l(nullptr), r(nullptr) {}
};
using pnode = node*;
pnode root;
int get_sz(pnode t) {
  return t? t->sz: 0;
}
ll get_sum(pnode t) {
  return t? t->sum: 0;
}
void update(pnode &t) {
  if (!t)  return ;
  t->sz = get_sz(t->l) + 1 + get_sz(t->r);
  t->sum = get_sum(t->l) + t->val + get_sum(t->r);
}
void push(pnode t) {
  if (t and t->rev) {
    swap(t->l, t->r);
    t->rev = 0;
    if (t->l) {
      t->l->rev ^= 1;
    } 

    if (t->r) {
      t->r->rev ^= 1;
    }
  }
}
void merge(pnode &t, pnode l, pnode r){
  push(l);
  push(r);
  if(!l or !r)  t=l?l:r;
  else if(l->prior > r->prior)  merge(l->r, l->r, r), t=l;
  else  merge(r->l,l,r->l) , t=r;
  update(t);
}
void split(pnode t, pnode &l, pnode &r, int pos, int add=0) {
  push(t);
  if(!t)  return void(r=l=NULL);
  int cur_pos = get_sz(t->l)+add;
  if(pos > cur_pos) split(t->r, t->r, r, pos, cur_pos+1), l = t;
  else   split(t->l, l, t->l, pos, add), r=t;
  update(t);
}
void insert(pnode &t, pnode it, int i) {
  pnode t1, t2;
  split(t, t1, t2, i);
  merge(t1, t1, it);
  merge(t, t1, t2);
}
void reverse(pnode &t, int l, int r) {
  pnode lt, mt, rt;
  split(t, t, rt, r + 1);
  split(t, lt, mt, l);
  mt->rev = 1;
  merge(mt, mt, rt);
  merge(t, lt, mt);
}
ll rsum(pnode& t, int l, int r) {
  pnode lt, mt, rt;
  split(t, t, rt, r + 1);
  split(t, lt, mt, l);
  ll ret = mt->sum;
  merge(mt, mt, rt);
  merge(t, lt, mt);
  return ret;
}
int n, q;  cin >> n >> q;
vector<ll> a(n);
for (auto &ai: a) {
  cin >> ai;
}
for (int i = 0; i < n; ++i) {
  insert(root, new node(a[i]), i);
}
while (q--) {
  int tp, l, r;  cin >> tp >> l >> r;  l--, r--;
  if (tp == 1) {
    reverse(root, l, r);
  }
  else {
    cout << rsum(root, l, r) << "\n";
  }
}