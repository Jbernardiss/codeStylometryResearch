#include <bits/stdc++.h>

using namespace std;

int main() {
  mt19937 mrand(58);
  int tt;
  cin >> tt;
  int n, w;
  cin >> n >> w;
  int win = 0;
  for (int qq = 1; qq <= tt; ++qq) {
    vector<bool> foo(n * 2), bar(n * 2);
    vector<pair<int, int>> rec;
    int score = 0;
    auto add = [&](pair<int, int> p) {
      rec.push_back(p);
      foo[p.first] = true;
      bar[p.second] = true;
    };
    auto get = [&](pair<int, int> p) {
      int value = 0;
      for (auto q : rec) {
        if ((p.first < q.first && p.second > q.second) || (p.first > q.first && p.second < q.second)) {
          ++value;
        }
      }
      return value;
    };
    auto greedy_random = [&]() {
      int ans = -1;
      vector<pair<int, int>> list;
      for (int i = 0; i < n * 2; ++i) {
        if (!foo[i]) {
          for (int j = 0; j < n * 2; ++j) {
            if (!bar[j]) {
              ans = max(ans, get(make_pair(i, j)));
            }
          }
        }
      }
      for (int i = 0; i < n * 2; ++i) {
        if (!foo[i]) {
          for (int j = 0; j < n * 2; ++j) {
            if (!bar[j]) {
              if (ans == get(make_pair(i, j))) {
                list.emplace_back(i, j);
              }
            }
          }
        }
      }
      return list[mrand() % list.size()];
    };
    auto greedy_by_sum = [&]() {
      int ans = -1;
      pair<int, int> who = make_pair(-1, -1);
      for (int s = 0; s < n * 4; ++s) {
        for (int i = 0; i < n * 2; ++i) {
          if (!foo[i]) {
            int j = s - i;
            if (j >= 0 && j < n * 2 && !bar[j]) {
              int v = get(make_pair(i, j));
              if (v > ans) {
                ans = v;
                who = make_pair(i, j);
              }
            }
          }
        }
      }
      return who;
    };
    auto greedy_by_i = [&]() {
      int ans = -1;
      pair<int, int> who = make_pair(-1, -1);
      for (int i = 0; i < n * 2; ++i) {
        if (!foo[i]) {
          for (int j = 0; j < n * 2; ++j) {
            if (!bar[j]) {
              int v = get(make_pair(i, j));
              if (v > ans) {
                ans = v;
                who = make_pair(i, j);
              }
            }
          }
        }
      }
      return who;
    };
    auto greedy_by_j = [&]() {
      int ans = -1;
      pair<int, int> who = make_pair(-1, -1);
      for (int j = 0; j < n * 2; ++j) {
        if (!bar[j]) {
          for (int i = 0; i < n * 2; ++i) {
            if (!foo[i]) {
              int v = get(make_pair(i, j));
              if (v > ans) {
                ans = v;
                who = make_pair(i, j);
              }
            }
          }
        }
      }
      return who;
    };
    int side = mrand() % 2;
    for (int i = 0, z = 0; i < n; ++i, z = (z + 1) % 3) {
      vector<int> x, y;
      for (int j = 0; j < n * 2; ++j) {
        if (!foo[j]) {
          x.push_back(j);
        }
        if (!bar[j]) {
          y.push_back(j);
        }
      }
      pair<int, int> p = greedy_by_sum();
      if (i < n - 6) {
        if (!z) {
          if (get(make_pair(x[3], y[3])) >= get(p)) {
            p = make_pair(x[3], y[3]);
          } else {
            z = 2;
          }
        } else if (z == 1) {
          if (side == 0) {
            if (get(greedy_by_i()) >= get(p)) {
              p = greedy_by_i();
            }
          } else {
            if (get(greedy_by_j()) >= get(p)) {
              p = greedy_by_j();
            }
          }
        } else {
          if (side == 0) {
            if (get(greedy_by_j()) >= get(p)) {
              p = greedy_by_j();
            }
          } else {
            if (get(greedy_by_i()) >= get(p)) {
              p = greedy_by_i();
            }
          }
        }
      }
      add(p);
      score += get(p);
#ifndef LOCAL
      cout << p.first + 1 << " " << p.second + 1 << endl;
#endif
      pair<int, int> q;
#ifdef LOCAL
      q = greedy_random();
#else
      cin >> q.first >> q.second;
      --q.first; --q.second;
#endif
      add(q);
      score -= get(q);
      if ((q.first < p.first) != (q.second < p.second)) {
        side = q.second < p.second;
      } else {
        side = mrand() % 2;
      }
    }
    if (score > 0) {
      win++;
    }
#ifdef LOCAL
    cout << win << " " << qq << endl;
#endif
    int verdict;
    cin >> verdict;
  }
  return 0;
}
