## Dijkstra
priority_queue<array<ll, 2>> pq;
vector<ll> dis(n, INF), vis(n);
while (!pq.empty()) {
  auto [d, u] = pq.top();  pq.pop();
  if (vis[u])  continue;
  vis[u] = 1;
  for (auto [v, c]: next[u]) {
    if (dis[v] > d + c) {
      dis[v] = d + c;
      pq.push({dis[v], v});
    }
  }
}
## Bellman-ford
vector<int> bellman_ford(int s){
  vector<int> dis(n, I);
  dis[s]=0;
  while(1){
    int any=0;
    for (auto& e: ed){
      if(dis[e.u]<I){
        if(dis[e.u]+e.cost < dis[e.v]){
          dis[e.v] = dis[e.u]+e.cost;
          any=1;
        }
      }
    }
    if(!any)  break;
  }
  return dis;
}
## Floy-Warshall
for (int k = 0; k < n; ++k) {
  for (int i = 0; i < n; ++i) {
    for (int j = 0; j < n; ++j) {
      dis[i][j] = min(dis[i][j], dis[i][k] + dis[k][j]);
    }
  }
}