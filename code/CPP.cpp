## GNU Pbds
#include <ext/pb_ds/assoc_container.hpp>
#include<ext/pb_ds/tree_policy.hpp>
using namespace __gnu_pbds;
template <typename T> using oset = tree<T, null_type, less<T>, rb_tree_tag, tree_order_statistics_node_update>;
template <typename T, typename R> using omap = tree<T, R, less<T>, rb_tree_tag, tree_order_statistics_node_update>;

## unordered_map
struct chash{
  size_t operator()(const pair<int,int>&x)const{
    return hash<long long>()(((long long)x.first)^(((long long)x.second)<<32));
  }
};
struct chash {
  static uint64_t splitmix64(uint64_t x) {
    x += 0x9e3779b97f4a7c15;
    x = (x ^ (x >> 30)) * 0xbf58476d1ce4e5b9;
    x = (x ^ (x >> 27)) * 0x94d049bb133111eb;
    return x ^ (x >> 31);
  }
  size_t operator()(uint64_t x) const {
    static const uint64_t FIXED_RANDOM = chrono::steady_clock::now().time_since_epoch().count();
    return splitmix64(x + FIXED_RANDOM);
  }
};
gp_hash_table<ii, int, chash> cnt;
## set custom operator
struct comp {
  bool operator()(const int& a, const int& b) const {
    return a < b;
  }
};
set<int, comp> st;
## Random Number
mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());
int x = rng() % 495;
## Running time
clock_t st = clock();
double t = (clock() - st) / (1.0 * CLOCKS_PER_SEC);
string line;  getline(cin, line);
istringstream iss;
string word;
while (iss >> word) {
  cout << word << "\n";
}
merge(t[v].begin(), t[v].end(), t[w].begin(), t[w].end(), back_inserter(t[u]));
#pragma GCC optimize("O3", "unroll-loops")
#pragma GCC target("avx2", "popcnt")
ulimit -s 65532
## Rollback
vector<pair<int*, int>> cng[N];
cng[i].push_back({&x, x});
for (auto [x, y]: cng[i]) {
  *x = y;
}

