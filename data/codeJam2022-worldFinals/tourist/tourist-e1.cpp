/**
 *    author:  tourist
 *    created: 05.08.2022 19:42:07       
**/
#include <bits/stdc++.h>

using namespace std;

#ifdef LOCAL
#include "algo/debug.h"
#else
#define debug(...) 42
#endif

template <typename T>
struct TPoint {
  T x;
  T y;
  int id;

  TPoint() : x(0), y(0), id(-1) {}
  TPoint(const T& x_, const T& y_) : x(x_), y(y_), id(-1) {}
  TPoint(const T& x_, const T& y_, int id_) : x(x_), y(y_), id(id_) {}

  static constexpr T eps = static_cast<T>(1e-9);

  inline TPoint operator+(const TPoint& rhs) const { return TPoint(x + rhs.x, y + rhs.y); }
  inline TPoint operator-(const TPoint& rhs) const { return TPoint(x - rhs.x, y - rhs.y); }
  inline TPoint operator*(const T& rhs) const { return TPoint(x * rhs, y * rhs); }
  inline TPoint operator/(const T& rhs) const { return TPoint(x / rhs, y / rhs); }

  friend T smul(const TPoint& a, const TPoint& b) {
    return a.x * b.x + a.y * b.y;
  }

  friend T vmul(const TPoint& a, const TPoint& b) {
    return a.x * b.y - a.y * b.x;
  }

  inline T abs2() const {
    return x * x + y * y;
  }

  inline bool operator<(const TPoint& rhs) const {
    return (y < rhs.y || (y == rhs.y && x < rhs.x));
  }

  inline bool is_upper() const {
    return (y > eps || (abs(y) <= eps && x > eps));
  }

  inline int cmp_polar(const TPoint& rhs) const {
    assert(abs(x) > eps || abs(y) > eps);
    assert(abs(rhs.x) > eps || abs(rhs.y) > eps);
    bool a = is_upper();
    bool b = rhs.is_upper();
    if (a != b) {
      return (a ? -1 : 1);
    }
    long long v = x * rhs.y - y * rhs.x;
    return (v > eps ? -1 : (v < -eps ? 1 : 0));
  }
};

using Point = TPoint<long long>;
//using Point = TPoint<long double>;

template <typename T>
string to_string(const TPoint<T>& p) {
  return "(" + to_string(p.x) + ", " + to_string(p.y) + ")";
}

bool bad[13][13][13][13][13][13];

int main() {
  ios::sync_with_stdio(false);
  cin.tie(0);
  int tt;
  cin >> tt;
  for (int qq = 1; qq <= tt; qq++) {
    cout << "Case #" << qq << ": ";
    int n;
    cin >> n;
    if (n > 12) {
      return 0;
    }
    vector<Point> p(n);
    for (int i = 0; i < n; i++) {
      cin >> p[i].x >> p[i].y;
    }
    auto Signum = [&](long long x) {
      return (x > 0 ? 1 : (x < 0 ? -1 : 0));
    };
    auto Line = [&](int i, int j, int k) {
      long long a = p[j].y - p[i].y;
      long long b = p[i].x - p[j].x;
      long long c = -a * p[i].x - b * p[i].y;
      return (a * p[k].x + b * p[k].y + c == 0);
    };
    auto Get = [&](int i, int j, int k) {
      long long a = p[j].y - p[i].y;
      long long b = p[i].x - p[j].x;
      long long c = -a * p[i].x - b * p[i].y;
      return (a * p[k].x + b * p[k].y + c);
    };
    auto Inter = [&](int i, int j, int ii, int jj) {
      long long a = p[j].y - p[i].y;
      long long b = p[i].x - p[j].x;
      long long c = -a * p[i].x - b * p[i].y;
      if (Signum(a * p[ii].x + b * p[ii].y + c) == 0 && Signum(a * p[jj].x + b * p[jj].y + c) == 0) {
        bool bad = true;
        long long xa = p[i].x;
        long long xb = p[j].x;
        long long xc = p[ii].x;
        long long xd = p[jj].x;
        if (xa > xb) swap(xa, xb);
        if (xc > xd) swap(xc, xd);
        if (xb < xc || xd < xa) {
          bad = false;
        }
        long long ya = p[i].y;
        long long yb = p[j].y;
        long long yc = p[ii].y;
        long long yd = p[jj].y;
        if (ya > yb) swap(ya, yb);
        if (yc > yd) swap(yc, yd);
        if (yb < yc || yd < ya) {
          bad = false;
        }
        if (bad) {
          return true;
        }
      }
      if (Signum(a * p[ii].x + b * p[ii].y + c) * Signum(a * p[jj].x + b * p[jj].y + c) == -1) {
        swap(i, ii);
        swap(j, jj);
        a = p[j].y - p[i].y;
        b = p[i].x - p[j].x;
        c = -a * p[i].x - b * p[i].y;
        if (Signum(a * p[ii].x + b * p[ii].y + c) * Signum(a * p[jj].x + b * p[jj].y + c) == -1) {
          return true;
        }
      }
      return false;
    };
    auto Check = [&](int i, int j, int k, int ii) {
      int p1 = Signum(Get(i, j, ii));
      int p2 = Signum(Get(j, k, ii));
      int p3 = Signum(Get(k, i, ii));
      if (p1 > 0 && p2 > 0 && p3 > 0) {
        return 1;
      }
      if (p1 < 0 && p2 < 0 && p3 < 0) {
        return 1;
      }
      if (p1 >= 0 && p2 >= 0 && p3 >= 0) {
        return 0;
      }
      if (p1 <= 0 && p2 <= 0 && p3 <= 0) {
        return 0;
      }
      return -1;
    };
    auto Same = [&](int i, int j, int k, int ii, int jj, int kk) {
      int pi = Check(i, j, k, ii);
      int pj = Check(i, j, k, jj);
      int pk = Check(i, j, k, kk);
      if (pi >= 0 && pj >= 0 && pk >= 0) {
        return true;
      }
      if (pi <= 0 && pj <= 0 && pk <= 0) {
        return true;
      }
      return false;
    };
    for (int i = 0; i < n; i++) {
      for (int j = i + 1; j < n; j++) {
        for (int k = j + 1; k < n; k++) {
          for (int ii = 0; ii < n; ii++) {
            for (int jj = ii + 1; jj < n; jj++) {
              for (int kk = jj + 1; kk < n; kk++) {
                bad[i][j][k][ii][jj][kk] = false;
                if (i == ii || i == jj || i == kk ||
                    j == ii || j == jj || j == kk ||
                    k == ii || k == jj || k == kk) {
                  bad[i][j][k][ii][jj][kk] = true;
                  continue;
                }
                if (Line(i, j, k) || Line(ii, jj, kk)) {
                  bad[i][j][k][ii][jj][kk] = true;
                  continue;
                }
                if (Inter(i, j, ii, jj) || Inter(i, j, jj, kk) || Inter(i, j, kk, ii) ||
                    Inter(j, k, ii, jj) || Inter(j, k, jj, kk) || Inter(j, k, kk, ii) ||
                    Inter(k, i, ii, jj) || Inter(k, i, jj, kk) || Inter(k, i, kk, ii)) {
                  bad[i][j][k][ii][jj][kk] = true;
                  continue;
                }
                if (!Same(i, j, k, ii, jj, kk) || !Same(ii, jj, kk, i, j, k)) {
                  bad[i][j][k][ii][jj][kk] = true;
                  continue;
                }
              }
            }
          }
        }
      }
    }
    vector<bool> used(n, false);
    vector<array<int, 3>> tris;
    vector<array<int, 3>> best;
    function<void(int)> Dfs = [&](int v) {
      if (v == n) {
        if (tris.size() > best.size()) {
          best = tris;
        }
        return;
      }
      Dfs(v + 1);
      if (!used[v]) {
        for (int j = v + 1; j < n; j++) {
          if (!used[j]) {
            for (int k = j + 1; k < n; k++) {
              if (!used[k]) {
                if (!Line(v, j, k)) {
                  bool ok = true;
                  for (auto& t : tris) {
                    if (bad[t[0]][t[1]][t[2]][v][j][k]) {
                      ok = false;
                      break;
                    }
                  }
                  if (ok) {
                    tris.push_back({v, j, k});
                    used[v] = used[j] = used[k] = true;
                    Dfs(v + 1);
                    used[v] = used[j] = used[k] = false;
                    tris.pop_back();
                  }
                }
              }
            }
          }
        }
      }
    };
    Dfs(0);
    cout << best.size() << '\n';
    for (auto& v : best) {
      cout << v[0] + 1 << " " << v[1] + 1 << " " << v[2] + 1 << '\n';
    }
  }
  return 0;
}
