#include <bits/stdc++.h>

using namespace std;

using ull = unsigned long long;

int main() {
#ifdef LOCAL
  freopen("input.txt", "r", stdin);
#endif
  ios::sync_with_stdio(false);
  cin.tie(0);
  mt19937_64 mrand(58);
  int tt;
  cin >> tt;
  for (int qq = 1; qq <= tt; ++qq) {
    cout << "Case #" << qq << ":";
    int n, m, q;
    cin >> n >> m >> q;
    vector<ull> w(n);
    for (int i = 0; i < n; ++i) {
      w[i] = mrand();
    }
    sort(w.begin(), w.end());
    vector<ull> foo(m + 1), bar(m + 1);
    map<pair<ull, ull>, int> id;
    for (int i = 1; i <= m; ++i) {
      int from, to;
      cin >> from >> to;
      foo[i] = w[--from];
      bar[i] = w[--to];
      id[make_pair(w[from], w[to])] = i;
    }
    vector<int> st(m + 1);
    vector<ull> pref_foo(1, 0);
    vector<ull> pref_bar(1, 0);
    for (int i = 1; i <= m; ++i) {
      st[i] = pref_foo.size() - 1;
      for (int j = i; j <= m; j += i) {
        pref_foo.push_back(pref_foo.back() + foo[j]);
        pref_bar.push_back(pref_bar.back() + bar[j]);
      }
    }
    ull sum_foo = 0;
    ull sum_bar = 0;
    for (int i = 0; i < n; ++i) {
      sum_foo += w[i];
      sum_bar += w[i];
    }
    while (q--) {
      string type;
      cin >> type;
      int l, r, m;
      cin >> l >> r >> m;
      if (type == "E") {
       sum_foo -= pref_foo[st[m] + r / m] - pref_foo[st[m] + (l - 1) / m];
       sum_bar -= pref_bar[st[m] + r / m] - pref_bar[st[m] + (l - 1) / m];
      } else {
       sum_foo += pref_foo[st[m] + r / m] - pref_foo[st[m] + (l - 1) / m];
       sum_bar += pref_bar[st[m] + r / m] - pref_bar[st[m] + (l - 1) / m];
      }
      if (id.count(make_pair(sum_foo, sum_bar))) {
        cout << " " << id[make_pair(sum_foo, sum_bar)];
      } else {
        cout << " X";
      }
    }
    cout << "\n";
  }
  return 0;
}
