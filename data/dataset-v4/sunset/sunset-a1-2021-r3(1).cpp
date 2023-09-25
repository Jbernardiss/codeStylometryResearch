#include <bits/stdc++.h>

using namespace std;

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
    string s;
    cin >> s;
    int n = s.size();
    vector<int> cnt(10);
    for (int i = 0; i < n; ++i) {
      cnt[s[i] - '0']++;
    }
    vector<long long> power(n / 2 + 1);
    power[0] = 1;
    for (int i = 1; i <= n / 2; ++i) {
      power[i] = power[i - 1] * 10;
    }
    long long ans = LLONG_MAX;
    function<void(int, long long)> solve = [&](int digit, long long diff) {
      if (digit == -1) {
        ans = min(ans, diff);
        return;
      }
      int i = 0, j = 9;
      while (!cnt[i]) {
        i++;
      }
      while (!cnt[j]) {
        j--;
      }
      cnt[i]--; cnt[j]--;
      solve(digit - 1, diff - (j - i) * power[digit]);
      cnt[i]++; cnt[j]++;
    };
    auto check = [&](int t) {
      int eq = 0;
      for (int i = 0; i < 10; ++i) {
        eq += cnt[i] / 2;
      }
      return eq >= t && (!t || eq > cnt[0] / 2);
    };
    if (n % 2 == 1) {
      for (int i = 1; i < 10; ++i) {
        if (cnt[i]) {
          cnt[i]--;
          solve(n / 2 - 1, i * power[n / 2]); 
          break;
        }
      }
    } else {
      bool zero = true;
      for (int i = 0; i < 10; ++i) {
        if (cnt[i] % 2) {
          zero = false;
        }
      }
      if (zero) {
        ans = 0;
      } else {
        for (int i = 0; i < 10; ++i) {
          if (cnt[i]) {
            cnt[i]--;
            for (int j = 0; j < i; ++j) {
              if (cnt[j]) {
                cnt[j]--;
                for (int who = 0; who < n / 2; ++who) {
                  if (who == n / 2 - 1 && (!i || !j)) {
                    continue;
                  }
                  if (check(n / 2 - 1 - who)) {
                    function<void(int, int, long long)> go = [&](int digit, int need, long long diff) {
                      if (digit == -1) {
                        ans = min(ans, diff);
                        return;
                      }
                      bool ok = false;
                      for (int sub = 9; sub >= 0; sub--) {
                        for (int i = 0; i + sub < 10; ++i) {
                          if (cnt[i] && cnt[i + sub]) {
                            cnt[i]--;
                            cnt[i + sub]--;
                            if (check(need)) {
                              go(digit - 1, need, diff - sub * power[digit]);
                              ok = true;
                            }
                            cnt[i]++;
                            cnt[i + sub]++;
                          }
                          if (ok) {
                            break;
                          }
                        }
                        if (ok) {
                          break;
                        }
                      }
                    };
                    go(who - 1, n / 2 - 1 - who, (i - j) * power[who]);
                  }
                }
                cnt[j]++;
              }
            }
            cnt[i]++;
          }
        }
      }
    }
    cout << ans << "\n";
  }
  return 0;
}
