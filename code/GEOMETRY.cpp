## Closest Pair of Points
ll min_dis(vector<array<int, 2>> &pts, int l, int r) {
  if (l + 1 >= r)  return LLONG_MAX;
  int m = (l + r) / 2;
  ll my = pts[m-1][1];
  ll d = min(min_dis(pts, l, m), min_dis(pts, m, r));
  inplace_merge(pts.begin()+l, pts.begin()+m, pts.begin()+r);
  for (int i = l; i < r; ++i) {
    if ((pts[i][1] - my) * (pts[i][1] - my) < d) {
      for (int j = i + 1; j < r and (pts[i][0] - pts[j][0]) * (pts[i][0] - pts[j][0]) < d; ++j) {
        ll dx = pts[i][0] - pts[j][0], dy = pts[i][1] - pts[j][1];
        d = min(d, dx * dx + dy * dy);
      }
    }
  }
  return d;
}
vector<array<int, 2>> pts(n);
sort(pts.begin(), pts.end(), [&] (array<int, 2> a, array<int, 2> b){
  return make_pair(a[1], a[0]) < make_pair(b[1], b[0]);
});
## Angular Sort
inline bool up (point p) {
  return p.y > 0 or (p.y == 0 and p.x >= 0);
}
sort(v.begin(), v.end(), [] (point a, point b) {
  return up(a) == up(b) ? a.x * b.y > a.y * b.x : up(a) < up(b);
});
inline int quad (point p) {
  if (p.y >= 0)  return p.x < 0;
  return 2 + (p.x >= 0);
}
sort(pt.begin(), pt.end(), [] (point a, point b) {
  return quad(a) == quad(b) ? a.x * b.y > a.y * b.x : quad(a) < quad(b);
});
## Convex Hull
struct pt {
  int x, y;
};
ll cross(pt a, pt b, pt c) {  //ab*ac
  return 1ll*(b.x-a.x)*(c.y-a.y) - 1ll*(c.x-a.x)*(b.y-a.y);
}
vector<pt> convexHull(vector<pt>& p) {
  sort(p.begin(), p.end(), [&] (pt a, pt b) {
    return (a.x==b.x? a.y<b.y: a.x<b.x);
  });
  int n = p.size(), m = 0;
  vector<pt> hull(2*n);
  for (int i = 0; i < n; ++i){
    while (m>=2 and cross(hull[m-2], hull[m-1], p[i]) < 0)  --m;
    hull[m++] = p[i];
  }
  for (int i = n-2, l = m; i >= 0; --i) {
    while(m>=l+1 and cross(hull[m-2], hull[m-1], p[i]) < 0)  --m;
    hull[m++] = p[i];
  }
  hull.resize(m-1);
  return hull;
}
