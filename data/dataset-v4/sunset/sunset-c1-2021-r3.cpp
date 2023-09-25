#include <bits/stdc++.h>

using namespace std;

#include <bits/stdc++.h>

using namespace std;

typedef double ld;

const ld eps = 1e-6;
const ld pi = acos(-1);

int sign(ld k) {
  if (k > eps) {
    return 1;
  } else if (k < -eps) {
    return -1;
  } else {
    return 0;
  }
}

int cmp(ld k1, ld k2) { return sign(k1 - k2); }

int inmid(ld k1, ld k2, ld k3) {
  return sign(k1 - k3) * sign(k2 - k3) <= 0;  // k3 在 [k1,k2] 内
}
struct point {
  ld x, y;
  point operator+(const point &k1) const { return (point){k1.x + x, k1.y + y}; }
  point operator-(const point &k1) const { return (point){x - k1.x, y - k1.y}; }
  point operator*(ld k1) const { return (point){x * k1, y * k1}; }
  point operator/(ld k1) const { return (point){x / k1, y / k1}; }
  int operator==(const point &k1) const {
    return cmp(x, k1.x) == 0 && cmp(y, k1.y) == 0;
  }
  // 逆时针旋转
  point turn(ld k1) {
    return (point){x * cos(k1) - y * sin(k1), x * sin(k1) + y * cos(k1)};
  }
  point turn90() { return (point){-y, x}; }
  bool operator<(const point k1) const {
    int a = cmp(x, k1.x);
    if (a == -1)
      return 1;
    else if (a == 1)
      return 0;
    else
      return cmp(y, k1.y) == -1;
  }
  ld abs() { return sqrt(x * x + y * y); }
  ld abs2() { return x * x + y * y; }
  ld dis(point k1) { return ((*this) - k1).abs(); }
  point unit() {
    ld w = abs();
    return (point){x / w, y / w};
  }
  void scan() {
    double k1, k2;
    scanf("%lf%lf", &k1, &k2);
    x = k1;
    y = k2;
  }
  void print() { printf("%.11lf %.11lf\n", x, y); }
  ld getw() { return atan2(y, x); }
  point getdel() {
    if (sign(x) == -1 || (sign(x) == 0 && sign(y) == -1))
      return (*this) * (-1);
    else
      return (*this);
  }
  int getP() const { return sign(y) == 1 || (sign(y) == 0 && sign(x) == -1); }
};
int inmid(point k1, point k2, point k3) {
  return inmid(k1.x, k2.x, k3.x) && inmid(k1.y, k2.y, k3.y);
}
ld cross(point k1, point k2) { return k1.x * k2.y - k1.y * k2.x; }
ld dot(point k1, point k2) { return k1.x * k2.x + k1.y * k2.y; }
ld rad(point k1, point k2) { return atan2(cross(k1, k2), dot(k1, k2)); }
// -pi -> pi
int compareangle(point k1, point k2) {
  return k1.getP() < k2.getP() ||
         (k1.getP() == k2.getP() && sign(cross(k1, k2)) > 0);
}
point proj(point k1, point k2, point q) {  // q 到直线 k1,k2 的投影
  point k = k2 - k1;
  return k1 + k * (dot(q - k1, k) / k.abs2());
}
point reflect(point k1, point k2, point q) { return proj(k1, k2, q) * 2 - q; }
int clockwise(point k1, point k2,
              point k3) {  // k1 k2 k3 逆时针 1 顺时针 -1 否则 0
  return sign(cross(k2 - k1, k3 - k1));
}
int checkLL(point k1, point k2, point k3,
            point k4) {  // 求直线 (L) 线段 (S)k1,k2 和 k3,k4 的交点
  return cmp(cross(k3 - k1, k4 - k1), cross(k3 - k2, k4 - k2)) != 0;
}
point getLL(point k1, point k2, point k3, point k4) {
  ld w1 = cross(k1 - k3, k4 - k3), w2 = cross(k4 - k3, k2 - k3);
  return (k1 * w2 + k2 * w1) / (w1 + w2);
}
int intersect(ld l1, ld r1, ld l2, ld r2) {
  if (l1 > r1) swap(l1, r1);
  if (l2 > r2) swap(l2, r2);
  return cmp(r1, l2) != -1 && cmp(r2, l1) != -1;
}
int checkSS(point k1, point k2, point k3, point k4) {
  return intersect(k1.x, k2.x, k3.x, k4.x) &&
         intersect(k1.y, k2.y, k3.y, k4.y) &&
         sign(cross(k3 - k1, k4 - k1)) * sign(cross(k3 - k2, k4 - k2)) <= 0 &&
         sign(cross(k1 - k3, k2 - k3)) * sign(cross(k1 - k4, k2 - k4)) <= 0;
}
ld disSP(point k1, point k2, point q) {
  point k3 = proj(k1, k2, q);
  if (inmid(k1, k2, k3))
    return q.dis(k3);
  else
    return min(q.dis(k1), q.dis(k2));
}
ld disSS(point k1, point k2, point k3, point k4) {
  if (checkSS(k1, k2, k3, k4))
    return 0;
  else
    return min(min(disSP(k1, k2, k3), disSP(k1, k2, k4)),
               min(disSP(k3, k4, k1), disSP(k3, k4, k2)));
}
int onS(point k1, point k2, point q) {
  return inmid(k1, k2, q) && sign(cross(k1 - q, k2 - k1)) == 0;
}
struct circle {
  point o;
  ld r;
  void scan() {
    o.scan();
    scanf("%lf", &r);
  }
  int inside(point k) { return cmp(r, o.dis(k)); }
};
struct line {
  // p[0]->p[1]
  point p[2];
  line(point k1, point k2) {
    p[0] = k1;
    p[1] = k2;
  }
  point &operator[](int k) { return p[k]; }
  int include(point k) { return sign(cross(p[1] - p[0], k - p[0])) > 0; }
  point dir() { return p[1] - p[0]; }
  line push() {  // 向外 ( 左手边 ) 平移 eps
    const ld eps = 1e-6;
    point delta = (p[1] - p[0]).turn90().unit() * eps;
    return {p[0] - delta, p[1] - delta};
  }
};
point getLL(line k1, line k2) { return getLL(k1[0], k1[1], k2[0], k2[1]); }
int checkLL(line k1, line k2) { return checkLL(k1[0], k1[1], k2[0], k2[1]); }
int parallel(line k1, line k2) { return sign(cross(k1.dir(), k2.dir())) == 0; }
int sameDir(line k1, line k2) {
  return parallel(k1, k2) && sign(dot(k1.dir(), k2.dir())) == 1;
}
int operator<(line k1, line k2) {
  if (sameDir(k1, k2)) return k2.include(k1[0]);
  return compareangle(k1.dir(), k2.dir());
}
int checkpos(line k1, line k2, line k3) { return k3.include(getLL(k1, k2)); }
vector<line> getHL(
    vector<line> &L) {  // 求半平面交 , 半平面是逆时针方向 , 输出按照逆时针
  sort(L.begin(), L.end());
  deque<line> q;
  for (int i = 0; i < (int)L.size(); i++) {
    if (i && sameDir(L[i], L[i - 1])) continue;
    while (q.size() > 1 && !checkpos(q[q.size() - 2], q[q.size() - 1], L[i]))
      q.pop_back();
    while (q.size() > 1 && !checkpos(q[1], q[0], L[i])) q.pop_front();
    q.push_back(L[i]);
  }
  while (q.size() > 2 && !checkpos(q[q.size() - 2], q[q.size() - 1], q[0]))
    q.pop_back();
  while (q.size() > 2 && !checkpos(q[1], q[0], q[q.size() - 1])) q.pop_front();
  vector<line> ans;
  for (int i = 0; i < q.size(); i++) ans.push_back(q[i]);
  return ans;
}
ld closepoint(vector<point> &A, int l,
              int r) {  // 最近点对 , 先要按照 x 坐标排序
  if (r - l <= 5) {
    ld ans = 1e20;
    for (int i = l; i <= r; i++)
      for (int j = i + 1; j <= r; j++) ans = min(ans, A[i].dis(A[j]));
    return ans;
  }
  int mid = l + r >> 1;
  ld ans = min(closepoint(A, l, mid), closepoint(A, mid + 1, r));
  vector<point> B;
  for (int i = l; i <= r; i++)
    if (abs(A[i].x - A[mid].x) <= ans) B.push_back(A[i]);
  sort(B.begin(), B.end(), [](point k1, point k2) { return k1.y < k2.y; });
  for (int i = 0; i < B.size(); i++)
    for (int j = i + 1; j < B.size() && B[j].y - B[i].y < ans; j++)
      ans = min(ans, B[i].dis(B[j]));
  return ans;
}
int checkposCC(circle k1, circle k2) {  // 返回两个圆的公切线数量
  if (cmp(k1.r, k2.r) == -1) swap(k1, k2);
  ld dis = k1.o.dis(k2.o);
  int w1 = cmp(dis, k1.r + k2.r), w2 = cmp(dis, k1.r - k2.r);
  if (w1 > 0)
    return 4;
  else if (w1 == 0)
    return 3;
  else if (w2 > 0)
    return 2;
  else if (w2 == 0)
    return 1;
  else
    return 0;
}
vector<point> getCL(circle k1, point k2,
                    point k3) {  // 沿着 k2->k3 方向给出 , 相切给出两个
  point k = proj(k2, k3, k1.o);
  ld d = k1.r * k1.r - (k - k1.o).abs2();
  if (sign(d) == -1) return {};
  point del = (k3 - k2).unit() * sqrt(max((ld)0.0, d));
  return {k - del, k + del};
}
vector<point> getCC(circle k1,
                    circle k2) {  // 沿圆 k1 逆时针给出 , 相切给出两个
  int pd = checkposCC(k1, k2);
  if (pd == 0 || pd == 4) return {};
  ld a = (k2.o - k1.o).abs2(), cosA = (k1.r * k1.r + a - k2.r * k2.r) /
                                      (2 * k1.r * sqrt(max(a, (ld)0.0)));
  ld b = k1.r * cosA, c = sqrt(max((ld)0.0, k1.r * k1.r - b * b));
  point k = (k2.o - k1.o).unit(), m = k1.o + k * b, del = k.turn90() * c;
  return {m - del, m + del};
}
vector<point> TangentCP(circle k1, point k2) {  // 沿圆 k1 逆时针给出
  ld a = (k2 - k1.o).abs(), b = k1.r * k1.r / a,
     c = sqrt(max((ld)0.0, k1.r * k1.r - b * b));
  point k = (k2 - k1.o).unit(), m = k1.o + k * b, del = k.turn90() * c;
  return {m - del, m + del};
}
vector<line> TangentoutCC(circle k1, circle k2) {
  int pd = checkposCC(k1, k2);
  if (pd == 0) return {};
  if (pd == 1) {
    point k = getCC(k1, k2)[0];
    return {(line){k, k}};
  }
  if (cmp(k1.r, k2.r) == 0) {
    point del = (k2.o - k1.o).unit().turn90().getdel();
    return {(line){k1.o - del * k1.r, k2.o - del * k2.r},
            (line){k1.o + del * k1.r, k2.o + del * k2.r}};
  } else {
    point p = (k2.o * k1.r - k1.o * k2.r) / (k1.r - k2.r);
    vector<point> A = TangentCP(k1, p), B = TangentCP(k2, p);
    vector<line> ans;
    for (int i = 0; i < A.size(); i++) ans.push_back((line){A[i], B[i]});
    return ans;
  }
}
vector<line> TangentinCC(circle k1, circle k2) {
  int pd = checkposCC(k1, k2);
  if (pd <= 2) return {};
  if (pd == 3) {
    point k = getCC(k1, k2)[0];
    return {(line){k, k}};
  }
  point p = (k2.o * k1.r + k1.o * k2.r) / (k1.r + k2.r);
  vector<point> A = TangentCP(k1, p), B = TangentCP(k2, p);
  vector<line> ans;
  for (int i = 0; i < A.size(); i++) ans.push_back((line){A[i], B[i]});
  return ans;
}
vector<line> TangentCC(circle k1, circle k2) {
  int flag = 0;
  if (k1.r < k2.r) swap(k1, k2), flag = 1;
  vector<line> A = TangentoutCC(k1, k2), B = TangentinCC(k1, k2);
  for (line k : B) A.push_back(k);
  if (flag)
    for (line &k : A) swap(k[0], k[1]);
  return A;
}
ld getarea(circle k1, point k2, point k3) {
  // 圆 k1 与三角形 k2 k3 k1.o 的有向面积交
  point k = k1.o;
  k1.o = k1.o - k;
  k2 = k2 - k;
  k3 = k3 - k;
  int pd1 = k1.inside(k2), pd2 = k1.inside(k3);
  vector<point> A = getCL(k1, k2, k3);
  if (pd1 >= 0) {
    if (pd2 >= 0) return cross(k2, k3) / 2;
    return k1.r * k1.r * rad(A[1], k3) / 2 + cross(k2, A[1]) / 2;
  } else if (pd2 >= 0) {
    return k1.r * k1.r * rad(k2, A[0]) / 2 + cross(A[0], k3) / 2;
  } else {
    int pd = cmp(k1.r, disSP(k2, k3, k1.o));
    if (pd <= 0) return k1.r * k1.r * rad(k2, k3) / 2;
    return cross(A[0], A[1]) / 2 +
           k1.r * k1.r * (rad(k2, A[0]) + rad(A[1], k3)) / 2;
  }
}
circle getcircle(point k1, point k2, point k3) {
  ld a1 = k2.x - k1.x, b1 = k2.y - k1.y, c1 = (a1 * a1 + b1 * b1) / 2;
  ld a2 = k3.x - k1.x, b2 = k3.y - k1.y, c2 = (a2 * a2 + b2 * b2) / 2;
  ld d = a1 * b2 - a2 * b1;
  point o =
      (point){k1.x + (c1 * b2 - c2 * b1) / d, k1.y + (a1 * c2 - a2 * c1) / d};
  return (circle){o, k1.dis(o)};
}
circle getScircle(vector<point> A) {
  random_shuffle(A.begin(), A.end());
  circle ans = (circle){A[0], 0};
  for (int i = 1; i < A.size(); i++)
    if (ans.inside(A[i]) == -1) {
      ans = (circle){A[i], 0};
      for (int j = 0; j < i; j++)
        if (ans.inside(A[j]) == -1) {
          ans.o = (A[i] + A[j]) / 2;
          ans.r = ans.o.dis(A[i]);
          for (int k = 0; k < j; k++)
            if (ans.inside(A[k]) == -1) ans = getcircle(A[i], A[j], A[k]);
        }
    }
  return ans;
}
ld area(vector<point> A) {  // 多边形用 vector<point> 表示 , 逆时针
  ld ans = 0;
  for (int i = 0; i < A.size(); i++) ans += cross(A[i], A[(i + 1) % A.size()]);
  return ans / 2;
}
int checkconvex(vector<point> A) {
  int n = A.size();
  A.push_back(A[0]);
  A.push_back(A[1]);
  for (int i = 0; i < n; i++)
    if (sign(cross(A[i + 1] - A[i], A[i + 2] - A[i])) == -1) return 0;
  return 1;
}
int contain(vector<point> A, point q) {  // 2 内部 1 边界 0 外部
  int pd = 0;
  for (int i = 1; i < A.size(); i++) {
    point u = A[i - 1], v = A[i];
    if (onS(u, v, q)) return 1;
    if (cmp(u.y, v.y) > 0) swap(u, v);
    if (cmp(u.y, q.y) >= 0 || cmp(v.y, q.y) < 0) continue;
    if (sign(cross(u - v, q - v)) < 0) pd ^= 1;
  }
  return pd << 1;
}

int main() {
#ifdef LOCAL
  freopen("input.txt", "r", stdin);
#endif
  ios::sync_with_stdio(false);
  cin.tie(0);
  int tt;
  cin >> tt;
  for (int qq = 1; qq <= tt; ++qq) {
    cout << "Case #" << qq << ": ";
    int n;
    cin >> n;
    vector<point> p(n);
    for (int i = 0; i < n; ++i) {
      cin >> p[i].x >> p[i].y;
    }
    vector<pair<int, int>> taken;
    for (int i = 0; i < 2; ++i) {
      int foo, bar;
      cin >> foo >> bar;
      --foo; --bar;
      if (foo > bar) {
        swap(foo, bar);
      }
      taken.emplace_back(foo, bar);
    }
    auto check = [&](int i, int j, int ii, int jj) {
      if (i == ii && j == jj) {
        return false;
      }
      if (i == ii || i == jj || j == ii || j == jj) {
        return true;
      }
      return !checkSS(p[i], p[j], p[ii], p[jj]);
    };
    for (int i = 0; i < n; ++i) {
      for (int j = i + 1; j < n; ++j) {
        bool bad = false;
        for (auto p : taken) {
          if (!check(i, j, p.first, p.second)) {
            bad = true;
            break;
          }
        }
        if (!bad) {
          taken.emplace_back(i, j);
        }
      }
    }
    cout << taken.size() - 2 << "\n";
    for (int i = 2; i < (int) taken.size(); ++i) {
      cout << taken[i].first + 1 << " " << taken[i].second + 1 << "\n";
    }
  }
  return 0;
}
