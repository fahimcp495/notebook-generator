struct graph {
  int n,t=0,cno=0;
  vector<vector<int>> g;
  vector<int> tin, lo, bcomp;
  stack <int> st;
  graph(int n):n(n),g(n),lo(n),bcomp(n){}
  void add_edge(int u, int v){
    g[u].push_back(v);
    g[v].push_back(u);
  }
  void dfs(int v, int p=-1){
    lo[v]=tin[v]=++t;
    st.push(v);
    for(int u:g[v]){
      if(u==p)    continue;
      if(!tin[u]){
        dfs(u, v);
        lo[v]=min(lo[v],lo[u]);
      } else{
        lo[v]=min(lo[v],tin[u]);
      }
    }
    if(tin[v]==lo[v]){
      while (!st.empty()){
        int tp=st.top(); st.pop();
        bcomp[tp]=cno;
        if(tp==v)    break;
      }
      cno++;
    }
  }
  vector<int> bcc(){
    tin.assign(n, 0);
    for (int i = 0; i < n; ++i){
      if(!tin[i])
        dfs(i);
    }
    return bcomp;
  }
};