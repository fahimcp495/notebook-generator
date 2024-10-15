vector<int> get_pi(string& s){
 int n = s.size();
 vector<int> pi(n);
 for (int k = 0, i = 1; i < n; ++i){
   if(s[i] == s[k])  pi[i] = ++k;
   else if(k == 0) pi[i] = 0;
   else  k = pi[k-1], --i;
 }
 return pi;
}
// Period =  n % (n - pi.back() == 0)? n - pi.back(): n
// Borders = pi.back(), pi[pi.back() - 1], ...
// Prefix palindrome: s + "#" + rev(s)
//  Number of occurrences of each prefix:
vector<int> pref_occur(vector<int> &pi) {
  int n = pi.size();
  vector<int> pref_occur(n + 1);
  for (int i = 0; i < n; ++i) {
    pref_occur[pi[i]]++;
  }
  for (int len = n; len > 0; --len) {
    pref_occur[pi[len - 1]] += pref_occur[len];
    pref_occur[len]++;
  }
  return pref_occur;
}
// Find the length of the longest proper suffix of a suffix which also its prefix
// Reverse -> Find prefix function -> Reverse
// Find minimum length string such that given strings occur as substring