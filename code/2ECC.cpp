struct graph {
  int n, t, sz;
  vector<vector<int>> adj;
  vector<int> tin, low, cmp;
  graph(int n): n(n),adj(n),tin(n),low(n),cmp(n){}
  void add_edge(int u, int v){
    adj[u].push_back(v);
    adj[v].push_back(u);
  }
  void dfs(int u, int p){
    tin[u]=low[u]=t++;
    int cnt=0;
    for(int v: adj[u]){
      if(v==p and ++cnt <= 1) continue;
      if(tin[v]!=-1)  low[u] = min(low[u], tin[v]);
      else {
        dfs(v,u);
        low[u] = min(low[u], low[v]);
      }
    }
  }
  void dfs2(int u, int p){
    if(p!=-1 and tin[p]>=low[u]) cmp[u] = cmp[p];
    else  cmp[u] = sz++;
    for(int v: adj[u]){
      if(cmp[v]==-1)  dfs2(v,u);
    }
  }
  void process_2ecc(){
    t = 0, sz = 0;
    for (int i = 0; i < n; ++i){
      tin[i] = low[i] = cmp[i] = -1;
    }
    for (int i = 0; i < n; ++i){
      if(tin[i]==-1)  dfs(i,-1);
    }
    for (int i = 0; i < n; ++i){
      if(cmp[i]==-1)  dfs2(i,-1);
    }
  }
};