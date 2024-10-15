## Max Suffix Query
// a1 < a2 < ... < and b1 > b2 > ... > bn
map<ll, ll> mp;
void ins(ll a, ll b) {
  auto it = mp.lb(a);
  if (it != end(mp) && it->s >= b) return;
  it = mp.insert(it, {a, b});  it->s = b;
  while (it != begin(mp) && prev(it)->s <= b) mp.erase(prev(it));
}
// Return max b for for a >= x
ll query(ll x) {
  auto it = mp.lb(x);
  return it == end(mp)? 0: it->s;
}
## Max Prefix Query
// a1 < a2 < ... < and b1 < b2 < ... < bn
map<ll, ll> mp;
void ins(ll a, ll b) {
  auto it = mp.ub(a);
  if (it != begin(mp) and prev(it)->s >= b)  return;
  it = mp.insert(it, {a, b});  it->s = b;
  while (next(it) != end(mp) and next(it)->s <= b)  mp.erase(next(it));
}
// Return max b for all a <= x
ll query(ll x) {
  auto it = mp.ub(x);
  return it == begin(mp)? 0: prev(it)->s;
}