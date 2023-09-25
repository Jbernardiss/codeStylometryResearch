#include <bits/stdc++.h>

using namespace std;

const long long INF = 1ll << 60;

struct matrix {
  vector<vector<long long>> a;
  int n;

  matrix(int _n = 0) : n(_n) {
    a = vector<vector<long long>>(n, vector<long long>(n));
  }
};

matrix operator*(const matrix& lhs, const matrix& rhs) {
  int n = lhs.n;
  matrix res(n);
  for (int k = 0; k < n; ++k) {
    for (int i = 0; i < n; ++i) {
      for (int j = 0; j < n; ++j) {
        if (rhs.a[k][j] && lhs.a[i][k] > INF / rhs.a[k][j]) {
          res.a[i][j] = INF;
        } else {
          res.a[i][j] = min(INF, res.a[i][j] + lhs.a[i][k] * rhs.a[k][j]);
        }
      }
    }
  }
  return res;
}

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
    int n;
    long long a, b;
    cin >> n >> a >> b;
    vector<int> l(n + 1), r(n + 1);
    for (int i = 1; i <= n; ++i) {
      cin >> l[i];
    }
    for (int i = 1; i <= n; ++i) {
      cin >> r[i];
    }
    matrix base(n + 2);
    base.a[0][n + 1]++;
    for (int i = 1; i <= n; ++i) {
      base.a[i][n + 1]++;
      base.a[i][l[i]]++;
      base.a[i][r[i]]++;
    }
    base.a[n + 1][n + 1]++;
    matrix ans(n + 2);
    for (int i = 0; i <= n + 1; ++i) {
      ans.a[i][i] = 1;
    }
    vector<matrix> power(60);
    power[0] = base;
    for (int i = 1; i < 60; ++i) {
      power[i] = power[i - 1] * power[i - 1];
    }
    long long d = 0;
    for (int i = 59; ~i; --i) {
      matrix t = ans * power[i];
      if (t.a[1][n + 1] < b) {
        ans = t;
        d |= 1ll << i;
      }
    }
    cout << d << "\n";
  }
  return 0;
}
