// Hashing
// Hashvalue(l...r) = hsh[l] - hsh[r + 1] * base ^ (r - l + 1);
// Must call preprocess
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const int MAX = 100009;
ll mods[2] = {1000000007, 1000000009};
//Some back-up primes: 1072857881, 1066517951, 1040160883
ll bases[2] = {137, 281};
ll pwbase[3][MAX];

void Preprocess(){
  pwbase[0][0] = pwbase[1][0] = 1;
  for(ll i = 0; i < 2; i++){
    for(ll j = 1; j < MAX; j++){
      pwbase[i][j] = (pwbase[i][j - 1] * bases[i]) % mods[i];
    }
  }
}
struct Hashing{
  ll hsh[2][MAX];
  string str;
  Hashing(){}
  Hashing(string _str) {str = _str; memset(hsh, 0, sizeof(hsh)); build();}
  void Build(){
    for(ll i = str.size() - 1; i >= 0; i--){
      for(int j = 0; j < 2; j++){
        hsh[j][i] = (hsh[j][i + 1] * bases[j] + str[i]) % mods[j];
        hsh[j][i] = (hsh[j][i] + mods[j]) % mods[j];
      }
    }
  }

  pair<ll,ll> GetHash(ll i, ll j){
    assert(i <= j);
    ll tmp1 = (hsh[0][i] - (hsh[0][j + 1] * pwbase[0][j - i + 1]) % mods[0]) % mods[0];
    ll tmp2 = (hsh[1][i] - (hsh[1][j + 1] * pwbase[1][j - i + 1]) % mods[1]) % mods[1];
    if(tmp1 < 0) tmp1 += mods[0];
    if(tmp2 < 0) tmp2 += mods[1];
    return make_pair(tmp1, tmp2);
  }
};

/***
    * Everything is 0 based
    * Call precal() once in the program
    * Call update(1,0,n-1,i,j,val) to update the value of position
      i to j to val, here n is the length of the string
    * Call query(1,0,n-1,L,R) to get a node containing hash
      of the position [L:R]
    * Before any update/query
        - Call init(str) where str is the string to be hashed
        - Call build(1,0,n-1)
***/

namespace strhash {
  int n;
  const int MAX = 100010;
  int ara[MAX];
  const int MOD[] = {2078526727, 2117566807};
  const int BASE[] = {1572872831, 1971536491};

  int BP[2][MAX], CUM[2][MAX];

  void init(char *str) {
    n = strlen(str);
    for(int i=0;i<n;i++) ara[i] = str[i]-'0'+1; /// scale str[i] if needed
  }

  void precal() {
    BP[0][0] = BP[1][0] = 1;
    for(int i=1;i<MAX;i++) {
      BP[0][i] = ( BP[0][i-1] * (long long) BASE[0] ) % MOD[0];
      BP[1][i] = ( BP[1][i-1] * (long long) BASE[1] ) % MOD[1];
    }
  }

  struct node {
    int sz;
    int h[2];
    node() {}
  } tree[4*MAX];

  int lazy[4*MAX];
  inline node Merge(node a,node b) {
    node ret;
    ret.h[0] = ( ( a.h[0] * (long long) BP[0][b.sz] ) + b.h[0] ) % MOD[0];
    ret.h[1] = ( ( a.h[1] * (long long) BP[1][b.sz] ) + b.h[1] ) % MOD[1];
    ret.sz = a.sz + b.sz;
    return ret;
  }

  inline void build(int n,int st,int ed) {
    if(st==ed) {
      tree[n].h[0] = tree[n].h[1] = ara[st];
      tree[n].sz = 1;
      return;
    }
    int mid = (st+ed)>>1;
    build(n+n,st,mid);
    build(n+n+1,mid+1,ed);

    tree[n] = Merge(tree[n+n],tree[n+n+1]);
  }

  inline void update(int n,int st,int ed,int id,int v) {
    if(st>id or ed<id) return;
    if(st==ed and ed==id) {
      tree[n].h[0] = tree[n].h[1] = v;
      return;
    }
    int mid = (st+ed)>>1;
    update(n+n,st,mid,id,v);
    update(n+n+1,mid+1,ed,id,v);
    tree[n] = Merge(tree[n+n],tree[n+n+1]);
  }
  inline node query(int n,int st,int ed,int i,int j){
    if(st>=i and ed<=j) return tree[n];
    int mid = (st+ed)/2;
    if(mid<i) return query(n+n+1,mid+1,ed,i,j);
    else if(mid>=j) return query(n+n,st,mid,i,j);
    else return Merge(query(n+n,st,mid,i,j),query(n+n+1,mid+1,ed,i,j));
  }
}
