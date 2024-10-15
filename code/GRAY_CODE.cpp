int gc(int n){ return n^(n>>1); }
int gc_to_dec(int g) {
  int d=0;
  while (g) { d ^= g;  g >>= 1; }
  return d;
}