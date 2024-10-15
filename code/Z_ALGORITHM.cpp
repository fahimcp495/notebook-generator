vector<int> get_z(string s){
  int n=s.size(), l=1, r=0;
  vector<int> z(n); z[0]=n;
  s+='#';
  for (int i = 1; i < n; ++i){
    if(i<=r)  z[i]=min(z[i-l], r-i+1);
    while(s[i+z[i]]==s[z[i]]) z[i]++;
    if(i+z[i]-1>r)  l=i, r=i+z[i]-1;
  }
  return z;
}