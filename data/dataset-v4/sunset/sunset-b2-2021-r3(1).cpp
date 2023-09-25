#include <bits/stdc++.h>

using namespace std;

using cap_t = int;
const cap_t cap_inf = 0x3f3f3f3f;

namespace flow {
struct edge {
  int to, rev;
  cap_t cap;
  edge(int t, cap_t c, int r) { to = t; cap = c; rev = r; }
};

vector<vector<edge>> g;
vector<int> ptr, dist;
int n, src, snk;
cap_t ans;

void init(int v, int s, int t) {
  n = v; ans = 0; src = s; snk = t;
  g.clear(); g.resize(n);
  ptr.resize(n); dist.resize(n);
}

void add(int v, int u, cap_t c, cap_t rev_c = 0) {
  g[v].emplace_back(u, c, g[u].size());
  g[u].emplace_back(v, rev_c, g[v].size() - 1);
}

bool bfs() {
  queue<int> q;
  for (int i = 0; i < n; ++i) dist[i] = -1;
  dist[src] = 0; q.push(src);
  while (!q.empty()) {
    int v = q.front(); q.pop();
    for (edge e : g[v]) if (e.cap && !~dist[e.to]) {
      dist[e.to] = dist[v] + 1; q.push(e.to);
      if (e.to == snk) return true;
    }
  }
  return false;
}

cap_t dfs(int v, cap_t f) {
  if (v == snk) return f;
  for (int& i = ptr[v]; ~i; --i) {
    edge& e = g[v][i];
    if (e.cap && dist[e.to] == dist[v] + 1) {
      cap_t w = dfs(e.to, min(e.cap, f));
      if (w) {
        e.cap -= w; g[e.to][e.rev].cap += w;
        return w;
      }
    }
  }
  return 0;
}

cap_t max_flow() {
  while (bfs()) {
    for (int i = 0; i < n; ++i) ptr[i] = g[i].size() - 1;
    while (true) {
      cap_t flow = dfs(src, cap_inf);
      if (!flow) break;
      ans += flow;
    }
  }
  return ans;
}

vector<bool> min_cut() {
  max_flow();
  vector<bool> res(n);
  for (int i = 0; i < n; ++i) res[i] = !~dist[i];
  return res;
}
}

using flow::src;
using flow::snk;
using flow::add;
using flow::init;
using flow::min_cut;
using flow::max_flow;

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
    int n, m;
    cin >> n >> m;
    vector<int> a(n);
    vector<int> b(m);
    for (int i = 0; i < n; ++i) {
      cin >> a[i];
    }
    for (int i = 0; i < m; ++i) {
      cin >> b[i];
    }
    int s = 0, t = 0;
    for (int i = 0; i < n; ++i) {
      s += a[i];
    }
    for (int i = 0; i < m; ++i) {
      t += b[i];
    }
    init(n + m + 2, n + m, n + m + 1);
    for (int i = 0; i < n; ++i) {
      add(src, i, a[i]);
    }
    for (int i = 0; i < m; ++i) {
      add(i + n, snk, b[i]);
    }
    for (int i = 0; i < n; ++i) {
      for (int j = 0; j < m; ++j) {
        add(i, j + n, 1);
      }
    }
    if (max_flow() != max(s, t)) {
      cout << "IMPOSSIBLE" << "\n";
      continue;
    }
    vector<vector<int>> ans(n, vector<int>(m));
    for (int i = 0; i < n; ++i) {
      for (auto e : flow::g[i]) {
        int j = e.to;
        if (j >= n && j < n + m && !e.cap) {
          ans[i][j - n] = 1;
        }
      }
    }
    while (true) {
      bool found = false;
      for (int i = 0; i + 1 < n; ++i) {
        for (int j = 0; j < m; ++j) {
          if (ans[i][j] && !ans[i + 1][j]) {
            for (int k = j + 1; k < m; ++k) {
              if (!ans[i][k] && ans[i + 1][k]) {
                ans[i][j] = ans[i + 1][k] = 0;
                ans[i + 1][j] = ans[i][k] = 1;
                found = true;
                j = k = m;
                i = n;
              }
            }
          }
        }
      }
      if (!found) {
        break;
      }
    }
    cout << "POSSIBLE" << "\n";
    for (int i = 0; i < n; ++i) {
      for (int j = 0; j < m; ++j) {
        if (ans[i][j]) {
          cout << "/";
        } else {
          cout << "\\";
        }
      }
      cout << "\n";
    }
  }
  return 0;
}
