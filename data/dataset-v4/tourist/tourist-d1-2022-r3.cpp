/**
 *    author:  tourist
 *    created: 04.06.2022 18:14:24       
**/
#include <bits/stdc++.h>

using namespace std;

/*#ifdef LOCAL
#include "algo/debug.h"
#else
#define debug(...) 42
#endif*/

int main() {
  ios::sync_with_stdio(false);
  cin.tie(0);
  int tt, n, k;
  cin >> tt >> n >> k;
  int Q = 0;
  while (tt--) {
    while (true) {
      Q += 1;
      vector<int> a(n);
      for (int i = 0; i < n; i++) {
        cin >> a[i];
        --a[i];
      }
      vector<int> c(n, -1);
      int id = 0;
      for (int i = 0; i < n; i++) {
        if (c[i] != -1) {
          continue;
        }
        vector<int> v;
        int x = i;
        while (c[x] == -1) {
          c[x] = -2;
          v.push_back(x);
          x = a[x];
        }
        int sz = (int) v.size();
        if (sz == 1) {
          c[v[0]] = id++;
          continue;
        }
        if (sz % 2 == 1) {
          c[v[0]] = c[v[1]] = c[v[2]] = id++;
          v.erase(v.begin(), v.begin() + 3);
          sz -= 3;
        }
        if (sz % 4 == 2) {
          c[v[0]] = c[v[1]] = id++;
          v.erase(v.begin(), v.begin() + 2);
          sz -= 2;
        }
        for (int j = 0; j < sz; j += 4) {
          c[v[j]] = c[v[j + 1]] = c[v[j + 2]] = c[v[j + 3]] = id++;
        }
      }
      for (int i = 0; i < n; i++) {
        if (i > 0) {
          cout << " ";
        }
        cout << c[i] + 1;
      }
      cout << endl;
      int res;
      cin >> res;
      if (res == 1) {
        break;
      }
    }
  }
  return 0;
}
