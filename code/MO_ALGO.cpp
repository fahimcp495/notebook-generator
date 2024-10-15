vector<array<int, 4>> cu(m);
for (int i = 0; i < m; ++i) {
  auto &[b, l, r, idx] = cu[i];
  cin >> l >> r;  l--;
  b = r / B;
  idx = i;
}
sort(cu.begin(), cu.end());

int s = 0, e = -1;
for (auto [b, l, r, i]: cu) {
  while (l < s)  add(--s);
  while (e < r)  add(++e);
  while (s < l)  remove(s++);
  while (r < e)  remove(e--);
  ans[i] = cur_ans;
}