/**
 *    author:  tourist
 *    created: 05.08.2022 17:49:12       
**/
#include <bits/stdc++.h>

using namespace std;

#ifdef LOCAL
#include "algo/debug.h"
#else
#define debug(...) 42
#endif

template <typename T>
class flow_graph {
 public:
  static constexpr T eps = (T) 1e-9;

  struct edge {
    int from;
    int to;
    T c;
    T f;
  };

  vector<vector<int>> g;
  vector<edge> edges;
  int n;
  int st;
  int fin;
  T flow;

  flow_graph(int _n, int _st, int _fin) : n(_n), st(_st), fin(_fin) {
    assert(0 <= st && st < n && 0 <= fin && fin < n && st != fin);
    g.resize(n);
    flow = 0;
  }

  void clear_flow() {
    for (const edge &e : edges) {
      e.f = 0;
    }
    flow = 0;
  }
   
  int add(int from, int to, T forward_cap, T backward_cap) {
    assert(0 <= from && from < n && 0 <= to && to < n);
    int id = (int) edges.size();
    g[from].push_back(id);
    edges.push_back({from, to, forward_cap, 0});
    g[to].push_back(id + 1);
    edges.push_back({to, from, backward_cap, 0});
    return id;
  }
};

template <typename T>
class dinic {
 public:
  flow_graph<T> &g;

  vector<int> ptr;
  vector<int> d;
  vector<int> q;

  dinic(flow_graph<T> &_g) : g(_g) {
    ptr.resize(g.n);
    d.resize(g.n);
    q.resize(g.n);
  }

  bool expath() {
    fill(d.begin(), d.end(), -1);
    q[0] = g.fin;
    d[g.fin] = 0;
    int beg = 0, end = 1;
    while (beg < end) {
      int i = q[beg++];
      for (int id : g.g[i]) {
        const auto &e = g.edges[id];
        const auto &back = g.edges[id ^ 1];
        if (back.c - back.f > g.eps && d[e.to] == -1) {
          d[e.to] = d[i] + 1;
          if (e.to == g.st) {
            return true;
          }
          q[end++] = e.to;
        }
      }
    }
    return false;
  }
   
  T dfs(int v, T w) {
    if (v == g.fin) {
      return w;
    }
    int &j = ptr[v];
    while (j >= 0) {
      int id = g.g[v][j];
      const auto &e = g.edges[id];
      if (e.c - e.f > g.eps && d[e.to] == d[v] - 1) {
        T t = dfs(e.to, min(e.c - e.f, w));
        if (t > g.eps) {
          g.edges[id].f += t;
          g.edges[id ^ 1].f -= t;
          return t;
        }
      }
      j--;
    }
    return 0;
  }

  T max_flow() {
    while (expath()) {
      for (int i = 0; i < g.n; i++) {
        ptr[i] = (int) g.g[i].size() - 1;
      }
      T big_add = 0;
      while (true) {
        T add = dfs(g.st, numeric_limits<T>::max());
        if (add <= g.eps) {
          break;
        }
        big_add += add;
      }
      if (big_add <= g.eps) {
        break;
      }
      g.flow += big_add;
    }
    return g.flow;
  }

  vector<bool> min_cut() {
    max_flow();
    vector<bool> ret(g.n);
    for (int i = 0; i < g.n; i++) {
      ret[i] = (d[i] != -1);
    }
    return ret;
  }
};

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
vector<int> find_eulerian_path(const graph<T> &g, int &root) {
  // in_deg and out_deg are fake for undigraph!
  vector<int> in_deg(g.n, 0);
  vector<int> out_deg(g.n, 0);
  int cnt_edges = 0;
  for (int id = 0; id < (int) g.edges.size(); id++) {
    cnt_edges++;
    auto &e = g.edges[id];
    out_deg[e.from]++;
    in_deg[e.to]++;
  }
  root = -1;
  int odd = 0;
  for (int i = 0; i < g.n; i++) {
    if ((in_deg[i] + out_deg[i]) % 2 == 1) {
      odd++;
      if (root == -1 || out_deg[i] - in_deg[i] > out_deg[root] - in_deg[root]) {
        root = i;
      }
    }
  }
  if (odd > 2) {  
    root = -1;
    return vector<int>();
  }
  if (root == -1) {
    root = 0;
    while (root < g.n && in_deg[root] + out_deg[root] == 0) {
      root++;
    }
    if (root == g.n) {
      // an empty path
      root = 0;
      return vector<int>();
    }
  }
  vector<bool> used(g.edges.size(), false);
  vector<int> ptr(g.n, 0);
  vector<int> balance(g.n, 0);
  vector<int> res(cnt_edges);
  int stack_ptr = 0;
  int write_ptr = cnt_edges;
  int v = root;
  while (true) {
    bool found = false;
    while (ptr[v] < (int) g.g[v].size()) {
      int id = g.g[v][ptr[v]++];
      if (used[id]) {
        continue;
      }
      used[id] = true;
      res[stack_ptr++] = id;
      auto &e = g.edges[id];
      balance[v]++;
      v ^= e.from ^ e.to;
      balance[v]--;
      found = true;
      break;
    }
    if (!found) {
      if (stack_ptr == 0) {
        break;
      }
      int id = res[--stack_ptr];
      res[--write_ptr] = id;
      auto &e = g.edges[id];
      v ^= e.from ^ e.to;
    }
  }
  int disbalance = 0;
  for (int i = 0; i < g.n; i++) {
    disbalance += abs(balance[i]);
  }
  if (write_ptr != 0 || disbalance > 2) {
    root = -1;
    return vector<int>();
  }
  return res;
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(0);
  int tt;
  cin >> tt;
  for (int qq = 1; qq <= tt; qq++) {
    cout << "Case #" << qq << ": ";
    int n, m;
    cin >> n >> m;
    vector<vector<int>> g(n, vector<int>(n, 0));
    vector<int> out_deg(n);
    vector<int> in_deg(n);
    for (int i = 0; i < m; i++) {
      int x, y;
      cin >> x >> y;
      --x; --y;
      g[x][y] += 1;
      out_deg[x] += 1;
      in_deg[y] += 1;
    }
    vector<vector<int>> pr(n, vector<int>(n, -1));
    const int inf = (int) 1e9;
    auto BFS = [&](int start, vector<int>& p) {
      vector<int> d(n, inf);
      vector<int> que(1, start);
      d[start] = 0;
      p[start] = -1;
      for (int b = 0; b < (int) que.size(); b++) {
        for (int u = 0; u < n; u++) {
          if (g[que[b]][u] > 0) {
            if (d[u] == inf) {
              que.push_back(u);
              d[u] = d[que[b]] + 1;
              p[u] = que[b];
            }
          }
        }
      }
    };
    for (int i = 0; i < n; i++) {
      BFS(i, pr[i]);
    }
    bool ok = true;
    for (int i = 0; i < n; i++) {
      for (int j = 0; j < n; j++) {
        if (i != j && pr[i][j] == -1) {
          ok = false;
        }
      }
    }
    if (!ok) {
      cout << "IMPOSSIBLE" << '\n';
      continue;
    }
    int k = (int) 1e6 / n;
    flow_graph<int> f(2 * n + 2, 2 * n, 2 * n + 1);
    vector<vector<int>> ids(n, vector<int>(n, -1));
    for (int i = 0; i < n; i++) {
      for (int j = 0; j < n; j++) {
        if (g[i][j]) {
          ids[i][j] = f.add(i, n + j, k, 0);
        }
      }
    }
    int goal = 0;
    for (int i = 0; i < n; i++) {
      f.add(f.st, i, k - out_deg[i], 0);
      f.add(n + i, f.fin, k - in_deg[i], 0);
      goal += k - out_deg[i];
    }
    dinic<int> d(f);
    if (d.max_flow() != goal) {
      cout << "IMPOSSIBLE" << '\n';
      continue;
    }
    for (int i = 0; i < n; i++) {
      for (int j = 0; j < n; j++) {
        if (g[i][j]) {
          g[i][j] += f.edges[ids[i][j]].f;
        }
      }
    }
    digraph<int> dg(n);
    for (int i = 0; i < n; i++) {
      for (int j = 0; j < n; j++) {
        for (int q = 0; q < g[i][j]; q++) {
          dg.add(i, j);
        }
      }
    }
    int root = 0;
    auto res = find_eulerian_path(dg, root);
    cout << res.size() + 1 << '\n';
    cout << 1;
    int ver = 0;
    for (int eid : res) {
      ver = dg.edges[eid].to;
      cout << " " << ver + 1;
    }
    cout << '\n';
  }
  return 0;
}
