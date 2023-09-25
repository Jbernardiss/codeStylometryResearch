//~ while (clock()<=69*CLOCKS_PER_SEC)
//~ #pragma comment(linker, "/stack:200000000")
#ifndef LOCAL
#pragma GCC optimize("O3")
#endif
//~ #pragma GCC optimize("Ofast")
//~ #pragma GCC target("sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx,avx,tune=native")
//~ #pragma GCC optimize("unroll-loops")
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
#define ALL(x) (x).begin(), (x).end()
#define SZ(x) ((int)(x).size())
#define st first
#define nd second

using namespace __gnu_pbds;
using namespace std;
 
template <typename T>
using ordered_set =
  tree<T, null_type, less<T>, rb_tree_tag, tree_order_statistics_node_update>;
 
#define sim template < class c
#define ris return * this
#define dor > debug & operator <<
#define eni(x) sim > typename \
  enable_if<sizeof dud<c>(0) x 1, debug&>::type operator<<(c i) {
sim > struct rge { c b, e; };
sim > rge<c> range(c i, c j) { return rge<c>{i, j}; }
sim > auto dud(c* x) -> decltype(cerr << *x, 0);
sim > char dud(...);
struct debug {
#ifdef LOCAL
~debug() { cerr << endl; }
eni(!=) cerr << boolalpha << i; ris; }
eni(==) ris << range(begin(i), end(i)); }
sim, class b dor(pair < b, c > d) {
  ris << "(" << d.first << ", " << d.second << ")";
}
sim dor(rge<c> d) {
  *this << "[";
  for (auto it = d.b; it != d.e; ++it)
  *this << ", " + 2 * (it == d.b) << *it;
  ris << "]";
}
#else
sim dor(const c&) { ris; }
#endif
};
#define imie(...) " [" << #__VA_ARGS__ ": " << (__VA_ARGS__) << "] "
 
#define shandom_ruffle random_shuffle
 
using ll=__int128_t;
using pii=pair<int,int>;
using pll=pair<ll,ll>;
using vi=vector<int>;
using vll=vector<ll>;

struct Point {
  long long x, y;
  Point operator-(const Point &p) const {
    return {x-p.x, y-p.y};
  }
  ll Cross(const Point &p) const {
    return (ll)x * p.y - (ll)y * p.x;
  }
  ll Dot(const Point &p) const {
    return (ll)x * p.x + (ll)y * p.y;
  }
  friend ostream &operator<<(ostream &os, const Point &P) {
    return os << "(" << P.x << "," << P.y << ")";
  }

  bool operator==(const Point &P) const {
    return x == P.x && y == P.y;
  }
};

inline int Sign(ll X) {
  return (X > 0 ? 1 : (X == 0 ? 0 : -1));
}

ostream &operator<<(ostream os, __int128_t x) {
  if (x < 0) { os << "-"; x = -x; }
  if (x == 0) { return os << "0"; }
  string s;
  while (x) {
    s += '0' + x % 10;
    x /= 10;
  }
  reverse(ALL(s));
  return os << s << "\n";
}

struct Testcase {
  int tidx_;

  Testcase(int idx) : tidx_{idx} {}

  int N;
  vector<Point> pts;
  vector<vector<Point>> triangles;
  int ans = 0;
  vector<bool> is_in;

  int TriangleLoc(const vector<Point> &T, const Point &P) {
    bool has_zero = false;
    bool has_neg = false;
    for (int i = 0; i < 3; ++i) {
      const Point &A = T[i];
      const Point &B = T[(i + 1) % 3];
      const Point &C = T[(i + 2) % 3];
      int dp = Sign((B - A).Cross(P - A));
      has_zero |= (dp == 0);
      if (dp != 0) has_neg |= (dp != Sign((B - A).Cross(C - A)));
    }

    // debug() << imie(T) << imie(P) << imie(has_neg) << imie(has_zero);

    if (has_neg) {
      return -1;
    }
    if (has_zero) {
      return 0;
    }
    return 1;
  }

  bool CheckInOut(const vector<Point> &T1, const vector<Point> &T2) {
    bool has_pos = false, has_neg = false;
    auto Consider = [&](const Point &P) {
      const int loc = TriangleLoc(T1, P);
      if (loc > 0) { has_pos = true; }
      if (loc < 0) { has_neg = true; }
    };
    for (int i = 0; i < SZ(T2); ++i) {
      Consider(T2[i]);
      const int ii = (i + 1) % 3;
      const Point Q{(T2[i].x + T2[ii].x) / 2, (T2[i].y + T2[ii].y) / 2};
      Consider(Q);
    }
    if (has_pos && has_neg) { return false; }
    return true;
  }

  bool SegIntersection(const Point &A1, const Point &A2, const Point &B1, const Point &B2) {
    int sb1 = Sign((A2 - A1).Cross(B1 - A1));
    int sb2 = Sign((A2 - A1).Cross(B2 - A1));
    int sa1 = Sign((B2 - B1).Cross(A1 - B1));
    int sa2 = Sign((B2 - B1).Cross(A2 - B1));
    if (sb1 * sb2 == -1 && sa1 * sa2 == -1) {
      return true;
    }

    if (sb1 != 0 || sb2 != 0) {
      return false;
    }

    ll da1 = 0;
    ll da2 = (A2 - A1).Dot(A2 - A1);
    ll db1 = (A2 - A1).Dot(B1 - A1);
    ll db2 = (A2 - A1).Dot(B2 - A1);
    // debug() << imie(A1) << imie(A2) << imie(B1) << imie(B2)

    if (da1 > da2) { swap(da1, da2); }
    if (db1 > db2) { swap(db1, db2); }

    if (max(da1, db1) < min(da2, db2)) {
      return true;
    }
    return false;
  }

  bool TrianglesOk(const vector<Point> &T1, const vector<Point> &T2) {
    // debug() << "start";
    if (!CheckInOut(T1, T2)) { return false; }
    // debug() << "T1 T2 ok";
    if (!CheckInOut(T2, T1)) { return false; }
    // debug() << "T2 T1 ok";
    for (int i = 0; i < 3; ++i) {
      const int ii = (i + 1) % 3;
      for (int j = 0; j < 3; ++j) {
        const int jj = (j + 1) % 3;
        if (SegIntersection(T1[i], T1[ii], T2[j], T2[jj])) {
          return false;
        }
      }
    }
    
    return true;
  }

  bool CheckLastTriangle() {
    debug() << imie(triangles);
    const auto &T = triangles.back();
    if ((T[1] - T[0]).Cross(T[2] - T[0]) == 0) { return false; }
    for (int i = 0; i < SZ(triangles) - 1; ++i) {
      if (!TrianglesOk(triangles[i], triangles.back())) {
        return false;
      }
    }
    debug() << "ok";
    return true;
  }

  vector<vector<Point>> result;

  void Bt(int idx, int loc) {
    if (idx && idx % 3 == 0) {
      if (!CheckLastTriangle()) {
        return;
      }
      if (SZ(triangles) > ans) {
        ans = SZ(triangles);
        result = triangles;
      }
      loc = 0;
    }

    if (idx % 3 == 0) {
      triangles.emplace_back();
    }

    while (loc < N) {
      if (!is_in[loc]) {
        triangles.back().push_back(pts[loc]);
        is_in[loc] = true;
        Bt(idx + 1, loc + 1);
        is_in[loc] = false;
        triangles.back().pop_back();
      }
      ++loc;
    }

    if (idx % 3 == 0) {
      triangles.pop_back();
    }
  }

  int GetPoint(Point P) {
    for (int i = 0; i < N; ++i) {
      if (pts[i] == P) {
        return i + 1;
      }
    }
    assert(false);
  }

  void Run() {
    // while (true) {
    //   vector<vector<Point>> Ts(2, vector<Point>(3));
    //   for (auto &A : Ts) for (auto &P : A) { cin >> P.x >> P.y; }
    //   cout << TrianglesOk(Ts[0], Ts[1]) << endl;
    // }

    cin >> N;
    pts.resize(N);
    is_in.resize(N);
    for (auto &pt : pts) {
      cin >> pt.x >> pt.y;
      pt.x *= 2;
      pt.y *= 2;
    }
    Bt(0, 0);

    cout << "Case #" << tidx_ << ": " << ans << "\n";
    for (auto triangle : result) {
      for (auto P : triangle) {
        cout << GetPoint(P) << " ";
      }
      cout << "\n";
    }
  }
};

int main() {
  ios_base::sync_with_stdio(0);
  cin.tie(0);
  cout << fixed << setprecision(11);
  cerr << fixed << setprecision(6);

  int T;
  cin >> T;
  for (int i = 1; i <= T; ++i) {
    Testcase{i}.Run();
  }
}
