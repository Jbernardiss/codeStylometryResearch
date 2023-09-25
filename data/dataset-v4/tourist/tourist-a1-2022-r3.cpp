/**
 *    author:  tourist
 *    created: 04.06.2022 19:09:41       
**/
#include <bits/stdc++.h>

using namespace std;

template <typename A, typename B>
string to_string(pair<A, B> p);

template <typename A, typename B, typename C>
string to_string(tuple<A, B, C> p);

template <typename A, typename B, typename C, typename D>
string to_string(tuple<A, B, C, D> p);

string to_string(const string& s) {
  return '"' + s + '"';
}

string to_string(const char* s) {
  return to_string((string) s);
}

string to_string(bool b) {
  return (b ? "true" : "false");
}

string to_string(vector<bool> v) {
  bool first = true;
  string res = "{";
  for (int i = 0; i < static_cast<int>(v.size()); i++) {
    if (!first) {
      res += ", ";
    }
    first = false;
    res += to_string(v[i]);
  }
  res += "}";
  return res;
}

template <size_t N>
string to_string(bitset<N> v) {
  string res = "";
  for (size_t i = 0; i < N; i++) {
    res += static_cast<char>('0' + v[i]);
  }
  return res;
}

template <typename A>
string to_string(A v) {
  bool first = true;
  string res = "{";
  for (const auto &x : v) {
    if (!first) {
      res += ", ";
    }
    first = false;
    res += to_string(x);
  }
  res += "}";
  return res;
}

template <typename A, typename B>
string to_string(pair<A, B> p) {
  return "(" + to_string(p.first) + ", " + to_string(p.second) + ")";
}

template <typename A, typename B, typename C>
string to_string(tuple<A, B, C> p) {
  return "(" + to_string(get<0>(p)) + ", " + to_string(get<1>(p)) + ", " + to_string(get<2>(p)) + ")";
}

template <typename A, typename B, typename C, typename D>
string to_string(tuple<A, B, C, D> p) {
  return "(" + to_string(get<0>(p)) + ", " + to_string(get<1>(p)) + ", " + to_string(get<2>(p)) + ", " + to_string(get<3>(p)) + ")";
}

void debug_out() { cerr << endl; }

template <typename Head, typename... Tail>
void debug_out(Head H, Tail... T) {
  cerr << " " << to_string(H);
  debug_out(T...);
}

#ifdef LOCAL
#define debug(...) cerr << "[" << #__VA_ARGS__ << "]:", debug_out(__VA_ARGS__)
#else
#define debug(...) 42
#endif

int main() {
  ios::sync_with_stdio(false);
  cin.tie(0);
  map<vector<int>, int> ids;
  map<vector<int>, int> memo;
  function<int(vector<pair<int, int>>)> Dfs = [&](vector<pair<int, int>> edges) {
    int n = (int) edges.size() + 1;
    if (n == 1) {
      return 1;
    }
    vector<vector<int>> g(n);
    for (auto& p : edges) {
      g[p.first].push_back(p.second);
      g[p.second].push_back(p.first);
    }
    function<int(int, int)> GetId = [&](int v, int pr) {
      vector<int> children;
      for (int u : g[v]) {
        if (u == pr) {
          continue;
        }
        children.push_back(GetId(u, v));
      }
      sort(children.begin(), children.end());
      auto it = ids.find(children);
      if (it != ids.end()) {
        return it->second;
      }
      int sz = (int) ids.size();
      ids[children] = sz;
      return sz;
    };
    vector<int> state;
    for (int i = 0; i < n; i++) {
      state.push_back(GetId(i, -1));
    }
    sort(state.begin(), state.end());
    auto it = memo.find(state);
    if (it != memo.end()) {
      return it->second;
    }
    set<int> used;
    for (int i = 0; i < n; i++) {
      vector<int> nei;
      vector<int> leaves;
      for (int j : g[i]) {
        if (g[j].size() == 1) {
          leaves.push_back(j);
        } else {
          nei.push_back(j);
        }
      }
      int cnt = (int) nei.size();
      for (int t = 0; t < (1 << cnt); t++) {
        for (int w = 0; w <= (int) leaves.size(); w++) {
          vector<bool> alive(n, true);
          alive[i] = false;
          for (int j = 0; j < cnt; j++) {
            if (t & (1 << j)) {
              alive[nei[j]] = false;
            }
          }
          for (int j = 0; j < w; j++) {
            alive[leaves[j]] = false;
          }
          vector<int> all;
          vector<pair<int, int>> es;
          function<void(int, int)> Trav = [&](int v, int pr) {
            all.push_back(v);
            alive[v] = false;
            for (int u : g[v]) {
              if (u != pr && alive[u]) {
                es.emplace_back(u, v);
                Trav(u, v);
              }
            }
          };
          int x = 0;
          for (int j = 0; j < n; j++) {
            if (alive[j]) {
              all.clear();
              es.clear();
              Trav(j, -1);
              for (auto& p : es) {
                p.first = (int) (find(all.begin(), all.end(), p.first) - all.begin());
                p.second = (int) (find(all.begin(), all.end(), p.second) - all.begin());
              }
              x ^= Dfs(es);
            }
          }
          used.insert(x);
        }
      }
    }
    int res = 0;
    while (used.find(res) != used.end()) {
      res += 1;
    }
    memo[state] = res;
    return res;
  };
  int tt;
  cin >> tt;
  while (tt--) {
    int n;
    cin >> n;
    vector<pair<int, int>> e;
    if (n % 2 == 0) {
      int a = (n >= 36 ? 34 : 28);
      int b = n - a;
      for (int i = 0; i < a - 1; i++) {
        e.emplace_back(i, i + 1);
      }
      for (int i = 0; i < b; i++) {
        e.emplace_back(a - 1, a + i);
      }
    } else {
      for (int i = 0; i < 13; i++) {
        e.emplace_back(i, i + 1);
      }
      e.emplace_back(11, 14);
      e.emplace_back(6, 15);
      e.emplace_back(5, 16);
      for (int i = 17; i < n; i++) {
        e.emplace_back(12, i);
      }
    }
    int res = Dfs(e);
    assert(res == 0);
    for (auto& p : e) {
      cout << p.first + 1 << " " << p.second + 1 << endl;
    }
    vector<vector<int>> g(n);
    for (auto& p : e) {
      g[p.first].push_back(p.second);
      g[p.second].push_back(p.first);
    }
    int ttt;
    cin >> ttt;
    while (ttt--) {
      vector<bool> alive(n, true);
      while (true) {
        int cnt;
        cin >> cnt;
        for (int i = 0; i < cnt; i++) {
          int id;
          cin >> id;
          --id;
          alive[id] = false;
        }
        vector<int> deg(n);
        for (int i = 0; i < n; i++) {
          if (alive[i]) {
            for (int j : g[i]) {
              if (alive[j]) {
                deg[i] += 1;
              }
            }
          }
        }
        vector<int> mv;
        auto backup = alive;
        for (int i = 0; i < n && mv.empty(); i++) {
          if (backup[i]) {
            vector<int> nei;
            vector<int> leaves;
            for (int j : g[i]) {
              if (backup[j]) {
                if (deg[j] == 1) {
                  leaves.push_back(j);
                } else {
                  nei.push_back(j);
                }
              }
            }
            cnt = (int) nei.size();
            for (int t = 0; t < (1 << cnt); t++) {
              if (!mv.empty()) {
                break;
              }
              for (int w = 0; w <= (int) leaves.size(); w++) {
                if (!mv.empty()) {
                  break;
                }
                alive = backup;
                alive[i] = false;
                for (int j = 0; j < cnt; j++) {
                  if (t & (1 << j)) {
                    alive[nei[j]] = false;
                  }
                }
                for (int j = 0; j < w; j++) {
                  alive[leaves[j]] = false;
                }
                vector<int> all;
                vector<pair<int, int>> es;
                function<void(int, int)> Trav = [&](int v, int pr) {
                  all.push_back(v);
                  alive[v] = false;
                  for (int u : g[v]) {
                    if (u != pr && alive[u]) {
                      es.emplace_back(u, v);
                      Trav(u, v);
                    }
                  }
                };
                int x = 0;
                for (int j = 0; j < n; j++) {
                  if (alive[j]) {
                    all.clear();
                    es.clear();
                    Trav(j, -1);
                    for (auto& p : es) {
                      p.first = (int) (find(all.begin(), all.end(), p.first) - all.begin());
                      p.second = (int) (find(all.begin(), all.end(), p.second) - all.begin());
                    }
                    auto got = Dfs(es);
                    x ^= got;
                  }
                }
                if (x == 0) {
                  mv.push_back(i);
                  for (int j = 0; j < cnt; j++) {
                    if (t & (1 << j)) {
                      mv.push_back(nei[j]);
                    }
                  }
                  for (int j = 0; j < w; j++) {
                    mv.push_back(leaves[j]);
                  }
                  break;
                }
              }
            }
          }
        }
        assert(!mv.empty());
        alive = backup;
        cout << mv.size() << endl;
        for (int i = 0; i < (int) mv.size(); i++) {
          if (i > 0) {
            cout << " ";
          }
          cout << mv[i] + 1;
          alive[mv[i]] = false;
        }
        cout << endl;
        bool any = false;
        for (int i = 0; i < n; i++) {
          if (alive[i]) {
            any = true;
            break;
          }
        }
        if (!any) {
          break;
        }
      }
    }
  }
  return 0;
}
