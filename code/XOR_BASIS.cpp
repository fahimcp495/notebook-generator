ll rnk, basis[D];
void insert_vector(ll mask){
  for (int i = D-1; i >= 0; --i){
    if((mask & (1ll << i)) == 0)  continue;
    if(!basis[i]){
      basis[i] = mask, rnk++;
      return;
    } else  mask ^= basis[i];
  }
}
