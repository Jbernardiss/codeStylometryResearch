/**
 *    author:  tourist
 *    created: 04.06.2022 18:20:25       
**/
#include <bits/stdc++.h>

using namespace std;

#ifdef LOCAL
#include "algo/debug.h"
#else
#define debug(...) 42
#endif

int main() {
  ios::sync_with_stdio(false);
  cin.tie(0);
  int tt;
  cin >> tt;
  for (int qq = 1; qq <= tt; qq++) {
    cout << "Case #" << qq << ": ";
    int n;
    cin >> n;
    vector<vector<int>> link(n, vector<int>(2));
    for (int j = 0; j < 2; j++) {
      for (int i = 0; i < n; i++) {
        cin >> link[i][j];
        --link[i][j];
      }
    }
    vector<vector<int>> g(n);
    vector<vector<int>> gr(n);
    bool ok = true;
    for (int i = 0; i < n; i++) {
      g[i] = {link[i][0], link[i][1], link[link[i][0]][0], link[link[i][0]][1], link[link[i][1]][0], link[link[i][1]][1]};
      if (find(g[i].begin(), g[i].end(), i) != g[i].end()) {
        ok = false;
        break;
      }
      for (int j : g[i]) {
        gr[j].push_back(i);
      }
    }
    if (!ok) {
      cout << "IMPOSSIBLE" << '\n';
      continue;
    }
    vector<int> deg(n);
    for (int i = 0; i < n; i++) {
      deg[i] = (int) gr[i].size();
    }
    set<pair<int, int>> s;
    for (int i = 0; i < n; i++) {
      s.emplace(deg[i], i);
    }
    vector<bool> alive(n, true);
    vector<int> order;
    while (!s.empty()) {
      int i = s.begin()->second;
      s.erase(s.begin());
      order.push_back(i);
      alive[i] = false;
      for (int j : g[i]) {
        if (alive[j]) {
          s.erase(make_pair(deg[j], j));
          deg[j] -= 1;
          s.emplace(deg[j], j);
        }
      }
    }
    const string let = "ACDEHIJKMORST";
    string res(n, 'Y');
    reverse(order.begin(), order.end());
    for (int i : order) {
      vector<bool> used(26, false);
      for (int j : g[i]) {
        used[(int) (res[j] - 'A')] = true;
      }
      for (int j : gr[i]) {
        used[(int) (res[j] - 'A')] = true;
      }
      for (char c : let) {
        if (!used[(int) (c - 'A')]) {
          res[i] = c;
          break;
        }
      }
      assert(res[i] != 'Y');
    }
    cout << res << '\n';
  }
  return 0;
}
