struct node {
  node *nxt[2];
  node() { fill(nxt, nxt + 2, nullptr); }
};
node* add(node *prev, int x) {
  node *new_root = new node();
  node * cur = new_root;;
  for (int idx = IDX - 1; idx >= 0; --idx) {
    int f = (x >> idx) & 1;
    if (prev and prev->nxt[!f])  cur->nxt[!f] = prev->nxt[!f];
    cur->nxt[f] = new node();
    cur = cur->nxt[f];
    if (prev)  prev = prev->nxt[f];
  }
  return new_root;
}
int get_max(node *root, int x) {
  if (!root)  return 0;
  node *u = root;
  int ret = 0;
  for (int idx = IDX - 1; idx >= 0; --idx) {
    int f = (x >> idx) & 1;
    if (u->nxt[!f])  ret += (1 << idx), u = u->nxt[!f];
    else  u = u->nxt[f];
  }
  return ret;
}