/**
 *    author:  tourist
 *    created: 05.08.2022 18:23:10       
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

template <typename T>
class graph {
 public:
  struct edge {
    int from;
    int to;
    T cost;
  };

  vector<edge> edges;
  vector<vector<int>> g;
  int n;

  graph(int _n) : n(_n) {
    g.resize(n);
  }

  virtual int add(int from, int to, T cost) = 0;
};

template <typename T>
class digraph : public graph<T> {
 public:
  using graph<T>::edges;
  using graph<T>::g;
  using graph<T>::n;

  digraph(int _n) : graph<T>(_n) {
  }

  int add(int from, int to, T cost = 1) {
    assert(0 <= from && from < n && 0 <= to && to < n);
    int id = (int) edges.size();
    g[from].push_back(id);
    edges.push_back({from, to, cost});
    return id;
  }

  digraph<T> reverse() const {
    digraph<T> rev(n);
    for (auto &e : edges) {
      rev.add(e.to, e.from, e.cost);
    }
    return rev;
  }
};

template <typename T>
vector<int> find_scc(const digraph<T> &g, int &cnt) {
  digraph<T> g_rev = g.reverse();
  vector<int> order;
  vector<bool> was(g.n, false);
  function<void(int)> dfs1 = [&](int v) {
    was[v] = true;
    for (int id : g.g[v]) {
      auto &e = g.edges[id];
      int to = e.to;
      if (!was[to]) {
        dfs1(to);
      }
    }
    order.push_back(v);
  };
  for (int i = 0; i < g.n; i++) {
    if (!was[i]) {
      dfs1(i);
    }
  }
  vector<int> c(g.n, -1);
  function<void(int)> dfs2 = [&](int v) {
    for (int id : g_rev.g[v]) {
      auto &e = g_rev.edges[id];
      int to = e.to;
      if (c[to] == -1) {
        c[to] = c[v];
        dfs2(to);
      }
    }
  };
  cnt = 0;
  for (int id = g.n - 1; id >= 0; id--) {
    int i = order[id];
    if (c[i] != -1) {
      continue;
    }
    c[i] = cnt++;
    dfs2(i);
  }
  return c;
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(0);
  int tt;
  cin >> tt;
  for (int qq = 1; qq <= tt; qq++) {
    cout << "Case #" << qq << ": ";
    int n, m, s;
    cin >> n >> m >> s;
    vector<Point> mp(m);
    vector<long long> mt(m);
    for (int i = 0; i < m; i++) {
      cin >> mp[i].x >> mp[i].y >> mt[i];
    }
    vector<int> sa(s);
    vector<int> sb(s);
    vector<Point> sp(s);
    vector<long long> st(s);
    for (int i = 0; i < s; i++) {
      cin >> sa[i] >> sb[i] >> sp[i].x >> sp[i].y >> st[i];
      --sa[i]; --sb[i];
    }
    digraph<int> g(n);
    vector<int> duck(n, 0);
    for (int i = 0; i < s; i++) {
      auto Good = [&](int id) {
        long long dist = (mp[id] - sp[i]).abs2();
        long long delta = abs(mt[id] - st[i]);
        return (dist <= delta * delta);
      };
      int id = (int) (lower_bound(mt.begin(), mt.end(), st[i]) - mt.begin());
      bool bad = false;
      bad |= (id > 0 && !Good(id - 1));
      bad |= (id < m && !Good(id));
      if (bad) {
        g.add(sb[i], sa[i]);
      }
    }
    auto Good = [&](int i, int j) {
      long long dist = (sp[i] - sp[j]).abs2();
      long long delta = abs(st[i] - st[j]);
      return (dist <= delta * delta);
    };
    vector<set<pair<long long, int>>> all(n);
    bool any = false;
    auto Mark = [&](int i) {
      duck[sa[i]] = 1;
      any = true;
    };
    auto Process = [&](int id, int i) {
      auto me = make_pair(st[i], i);
      while (true) {
        auto it = all[id].lower_bound(me);
        if (it == all[id].end()) {
          break;
        }
        if (!Good(it->second, i)) {
          Mark(it->second);
          all[id].erase(it);
        } else {
          break;
        }
      }
      while (true) {
        auto it = all[id].lower_bound(me);
        if (it == all[id].begin()) {
          break;
        }
        it = prev(it);
        if (!Good(it->second, i)) {
          Mark(it->second);
          all[id].erase(it);
        } else {
          break;
        }
      }
      all[id].insert(me);
    };
    for (int i = 0; i < s; i++) {
      Process(sa[i], i);
      Process(sb[i], i);
    }
    if (any) {
      vector<int> que;
      for (int i = 0; i < n; i++) {
        if (duck[i]) {
          que.push_back(i);
        }
      }
      for (int b = 0; b < (int) que.size(); b++) {
        for (int eid : g.g[que[b]]) {
          auto& e = g.edges[eid];
          if (!duck[e.to]) {
            que.push_back(e.to);
            duck[e.to] = 1;
          }
        }
      }
      cout << (int) que.size() << '\n';
    } else {
      int cnt = -1;
      vector<int> c = find_scc(g, cnt);
      vector<int> sz(cnt, 0);
      for (int i = 0; i < n; i++) {
        sz[c[i]] += 1;
      }
      vector<bool> out(cnt, false);
      for (auto& e : g.edges) {
        if (c[e.from] != c[e.to]) {
          out[c[e.from]] = true;
        }
      }
      int ans = n + 1;
      for (int i = 0; i < cnt; i++) {
        if (!out[i]) {
          ans = min(ans, sz[i]);
        }
      }
      cout << ans << '\n';
    }
  }
  return 0;
}
