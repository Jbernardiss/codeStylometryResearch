/**
 *    author:  tourist
 *    created: 05.08.2022 17:42:45       
**/
#include <bits/stdc++.h>

using namespace std;

#ifdef LOCAL
#include "algo/debug.h"
#else
#define debug(...) 42
#endif

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
class undigraph : public graph<T> {
 public:
  using graph<T>::edges;
  using graph<T>::g;
  using graph<T>::n;

  undigraph(int _n) : graph<T>(_n) {
  }

  int add(int from, int to, T cost = 1) {
    assert(0 <= from && from < n && 0 <= to && to < n);
    int id = (int) edges.size();
    g[from].push_back(id);
    g[to].push_back(id);
    edges.push_back({from, to, cost});
    return id;
  }
};

template <typename T>
class dfs_undigraph : public undigraph<T> {
 public:
  using undigraph<T>::edges;
  using undigraph<T>::g;
  using undigraph<T>::n;

  vector<int> pv;
  vector<int> pe;
  vector<int> order;
  vector<int> pos;
  vector<int> end;
  vector<int> sz;
  vector<int> root;
  vector<int> depth;
  vector<int> min_depth;
  vector<T> dist;
  vector<int> was;
  int attempt;

  dfs_undigraph(int _n) : undigraph<T>(_n) {
  }

  void init() {
    pv = vector<int>(n, -1);
    pe = vector<int>(n, -1);
    order.clear();
    pos = vector<int>(n, -1);
    end = vector<int>(n, -1);
    sz = vector<int>(n, 0);
    root = vector<int>(n, -1);
    depth = vector<int>(n, -1);
    min_depth = vector<int>(n, -1);
    dist = vector<T>(n);
    was = vector<int>(n, -1);
    attempt = 0;
  }

  void clear() {
    pv.clear();
    pe.clear();
    order.clear();
    pos.clear();
    end.clear();
    sz.clear();
    root.clear();
    depth.clear();
    min_depth.clear();
    dist.clear();
    was.clear();
  }

 private:
  void do_dfs(int v) {
    was[v] = attempt;
    pos[v] = (int) order.size();
    order.push_back(v);
    sz[v] = 1;
    min_depth[v] = depth[v];
    for (int id : g[v]) {
      if (id == pe[v]) {
        continue;
      }
      auto &e = edges[id];
      int to = e.from ^ e.to ^ v;
      if (was[to] == attempt) {
        min_depth[v] = min(min_depth[v], depth[to]);
        continue;
      }
      depth[to] = depth[v] + 1;
      dist[to] = dist[v] + e.cost;
      pv[to] = v;
      pe[to] = id;
      root[to] = (root[v] != -1 ? root[v] : to);
      do_dfs(to);
      sz[v] += sz[to];
      min_depth[v] = min(min_depth[v], min_depth[to]);
    }
    end[v] = (int) order.size() - 1;
  }

  void do_dfs_from(int v) {
    ++attempt;
    depth[v] = 0;
    dist[v] = T{};
    root[v] = v;
    pv[v] = pe[v] = -1;
    do_dfs(v);
  }

 public:
  void dfs(int v, bool clear_order = true) {
    if (pv.empty()) {
      init();
    } else {
      if (clear_order) {
        order.clear();
      }
    }
    do_dfs_from(v);
  }

  void dfs_all() {
    init();
    for (int v = 0; v < n; v++) {
      if (depth[v] == -1) {
        do_dfs_from(v);
      }
    }
    assert((int) order.size() == n);
  }
};

template <typename T>
vector<bool> find_bridges(dfs_undigraph<T> &g) {
  g.dfs_all();
  vector<bool> bridge(g.edges.size(), false);
  for (int i = 0; i < g.n; i++) {
    if (g.pv[i] != -1 && g.min_depth[i] == g.depth[i]) {
      bridge[g.pe[i]] = true;
    }
  }
  return bridge;
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(0);
  int tt;
  cin >> tt;
  for (int qq = 1; qq <= tt; qq++) {
    cout << "Case #" << qq << ": ";
    int n, m, v0, v1;
    cin >> n >> m >> v0 >> v1;
    --v0; --v1;
    dfs_undigraph<int> g(n);
    vector<vector<int>> gr(n);
    for (int i = 0; i < m; i++) {
      int x, y;
      cin >> x >> y;
      --x; --y;
      g.add(x, y);
      gr[x].push_back(y);
      gr[y].push_back(x);
    }
    auto is_bridge = find_bridges(g);
    vector<bool> lies(n, false);
    for (int i = 0; i < m; i++) {
      if (!is_bridge[i]) {
        auto& e = g.edges[i];
        lies[e.from] = lies[e.to] = true;
      }
    }
    const int inf = (int) 1e9;
    auto BFS = [&](int start) {
      vector<int> d(n, inf);
      vector<int> que(1, start);
      d[start] = 0;
      for (int b = 0; b < (int) que.size(); b++) {
        for (int u : gr[que[b]]) {
          if (d[u] == inf) {
            que.push_back(u);
            d[u] = d[que[b]] + 1;
          }
        }
      }
      return d;
    };
    auto d0 = BFS(v0);
    auto d1 = BFS(v1);
    int ans = 0;
    for (int i = 0; i < n; i++) {
      if (d0[i] < d1[i]) {
        if (lies[i] || d1[i] == inf) {
          ans = -1;
          break;
        }
        ans = max(ans, d1[i]);
      }
    }
    if (ans == -1) {
      cout << "SAFE" << '\n';
    } else {
      cout << 2 * ans << '\n';
    }
  }
  return 0;
}
