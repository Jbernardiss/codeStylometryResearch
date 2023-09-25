#include <bits/stdc++.h>

using namespace std;

template <typename T>
T power(T a, long long b) {
  T r = 1;
  while (b) {
    if (b & 1) {
      r *= a;
    }
    a *= a;
    b >>= 1;
  }
  return r;
}

template <typename T>
T inverse(T a, T m) {
  a %= m;
  if (a < 0) {
    a += m;
  }
  T b = m, u = 0, v = 1;
  while (a) {
    T t = b / a;
    b -= a * t;
    swap(a, b);
    u -= v * t;
    swap(u, v);
  }
  if (u < 0) {
    u += m;
  }
  return u;
}

template <int _P>
struct modnum {
  static constexpr int P = _P;

 private:
  int v;

 public:
  modnum() : v(0) {
  }

  modnum(long long _v) {
    v = _v % P;
    if (v < 0) {
      v += P;
    }
  }

  explicit operator int() const {
    return v;
  }

  bool operator==(const modnum& o) const {
    return v == o.v;
  }

  bool operator!=(const modnum& o) const {
    return v != o.v;
  }

  modnum inverse() const {
    return modnum(::inverse(v, P));
  }

  modnum operator-() const {
    return modnum(v ? P - v : 0);
  }
  
  modnum operator+() const {
    return *this;
  }

  modnum& operator++() {
    v++;
    if (v == P) {
      v = 0;
    }
    return *this;
  }
  
  modnum& operator--() {
    if (v == 0) {
      v = P;
    }
    v--;
    return *this;
  }

  modnum operator++(int) {
    modnum r = *this;
    ++*this;
    return r;
  }
  
  modnum operator--(int) {
    modnum r = *this;
    --*this;
    return r;
  }

  modnum& operator+=(const modnum& o) {
    v += o.v;
    if (v >= P) {
      v -= P;
    }
    return *this;
  }

  modnum operator+(const modnum& o) const {
    return modnum(*this) += o;
  }

  modnum& operator-=(const modnum& o) {
    v -= o.v;
    if (v < 0) {
      v += P;
    }
    return *this;
  }

  modnum operator-(const modnum& o) const {
    return modnum(*this) -= o;
  }

  modnum& operator*=(const modnum& o) {
    v = (int) ((long long) v * o.v % P);
    return *this;
  }

  modnum operator*(const modnum& o) const {
    return modnum(*this) *= o;
  }
  
  modnum& operator/=(const modnum& o) {
    return *this *= o.inverse();
  }

  modnum operator/(const modnum& o) const {
    return modnum(*this) /= o;
  }
};

template <int _P>
ostream& operator<<(ostream& out, const modnum<_P>& n) {
  return out << int(n);
}

template <int _P>
istream& operator>>(istream& in, modnum<_P>& n) {
  long long _v;
  in >> _v;
  n = modnum<_P>(_v);
  return in;
}

using num = modnum<1000000007>;

const int md = 1e9 + 7;

inline void add(int &x, int y) {
  x += y;
  if (x >= md) {
    x -= md;
  }
}

inline void sub(int &x, int y) {
  x -= y;
  if (x < 0) {
    x += md;
  }
}

inline int mul(int x, int y) {
  return (int) ((long long) x * y % md);
}

inline int inv(int a) {
  int b = md, u = 0, v = 1;
  while (a) {
    int t = b / a;
    b -= t * a;
    swap(a, b);
    u -= t * v;
    swap(u, v);
  }
  if (u < 0) {
    u += md;
  }
  return u;
}

vector<int> bm(vector<int> a) {
  vector<int> last(1, 1);
  vector<int> cur(1, 1);
  int len = 1, value = 1;
  for (int i = 0; i < (int) a.size(); ++i) {
    int diff = 0;
    for (int j = 0; j < (int) cur.size(); ++j) {
      add(diff, mul(cur[j], a[i - j]));
    }
    if (diff) {
      int coef = md - mul(diff, inv(value));
      vector<int> old = cur;
      if (cur.size() < last.size() + len) {
        cur.resize(last.size() + len);
      }
      for (int j = 0; j < (int) last.size(); ++j) {
        add(cur[j + len], mul(coef, last[j]));
      }
      if (2 * ((int) old.size() - 1) <= i) {
        last = old;
        len = 0;
        value = diff;
      }
    }
    ++len;
  }
  cur.erase(cur.begin());
  return cur;
}

int rec(int m, vector<int> a, vector<int> f) {
  reverse(a.begin(), a.end());
  vector<int> res(1, 1);
  int n = a.size();
  int high = 0;
  while (1 << (high + 1) <= m) {
    ++high;
  }
  for (; ~high; --high) {
    vector<int> temp(res.size() * 2, 0);
    for (int i = 0; i < (int) res.size(); ++i) {
      for (int j = 0; j < (int) res.size(); ++j) {
        add(temp[i + j], mul(res[i], res[j]));
      }
    }
    for (int i = temp.size() - 1; i >= n; --i, temp.pop_back()) {
      if (temp[i]) {
        for (int j = 1; j <= n; ++j) {
          sub(temp[i - j], mul(temp[i], a[n - j]));
        }
      }
    }
    res = temp;
    if (m >> high & 1) {
      vector<int> temp(res.size() + 1, 0);
      for (int i = 0; i < (int) res.size(); ++i) {
        temp[i + 1] = res[i];
      }
      for (int i = temp.size() - 1; i >= n; --i, temp.pop_back()) {
        for (int j = 1; j <= n; ++j) {
          sub(temp[i - j], mul(temp[i], a[n - j]));
        }
      }
      res = temp;
    }
  }
  int ans = 0;
  for (int i = 0; i < n && i < (int) res.size(); ++i) {
    add(ans, mul(f[i], res[i]));
  }
  return ans;
}

int solve(vector<int> a, int n) {
  vector<int> b = bm(a);
  return rec(n, b, vector<int>(a.begin(), a.begin() + b.size()));
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
    int n, m, l;
    cin >> n >> m >> l;
    vector<int> a(1 << l);
    for (int i = 0; i < 1 << l; ++i) {
      cin >> a[i];
      --a[i];
    }
    unsigned left = 0;
    unsigned right = 0;
    for (int i = 0; i < 1 << (l - 1); ++i) {
      left |= 1u << a[i];
    }
    for (int i = 0; i < 1 << (l - 1); ++i) {
      right |= 1u << a[i | (1 << (l - 1))];
    }
    unsigned common = left & right;
    map<unsigned, vector<int>> l0;
    map<unsigned, vector<int>> l1;
    map<unsigned, vector<int>> r0;
    map<unsigned, vector<int>> r1;
    for (unsigned s = left; ; s = (s - 1) & left) {
      function<bool(int, int, bool)> get = [&](int l, int r, bool alice) {
        if (l == r - 1) {
          return (bool) (s >> a[l] & 1);
        }
        int y = (l + r) >> 1;
        if (alice) {
          return get(l, y, !alice) || get(y, r, !alice);
        } else {
          return get(l, y, !alice) && get(y, r, !alice);
        }
      };
      if (get(0, 1 << (l - 1), false)) {
        l1[s & common].push_back(__builtin_popcount(s));
      } else {
        l0[s & common].push_back(__builtin_popcount(s));
      }
      if (!s) {
        break;
      }
    }
    for (unsigned s = right; ; s = (s - 1) & right) {
      function<bool(int, int, bool)> get = [&](int l, int r, bool alice) {
        if (l == r - 1) {
          return (bool) (s >> a[l] & 1);
        }
        int y = (l + r) >> 1;
        if (alice) {
          return get(l, y, !alice) || get(y, r, !alice);
        } else {
          return get(l, y, !alice) && get(y, r, !alice);
        }
      };
      if (get(1 << (l - 1), 1 << l, false)) {
        r1[s & common].push_back(__builtin_popcount(s) - __builtin_popcount(s & common));
      } else {
        r0[s & common].push_back(__builtin_popcount(s) - __builtin_popcount(s & common));
      }
      if (!s) {
        break;
      }
    }
    vector<num> ways(n + 1);
    for (unsigned s = common; ; s = (s - 1) & common) {
      vector<num> f0(n + 1);
      vector<num> f1(n + 1);
      vector<num> g0(n + 1);
      vector<num> g1(n + 1);
      for (int i : l0[s]) {
        f0[i]++;
      }
      for (int i : l1[s]) {
        f1[i]++;
      }
      for (int i : r0[s]) {
        g0[i]++;
      }
      for (int i : r1[s]) {
        g1[i]++;
      }
      for (int i = 0; i <= n; ++i) {
        for (int j = 0; j + i <= n; ++j) {
          ways[i + j] += (f1[i] + f0[i]) * (g1[j] + g0[j]) - f0[i] * g0[j];
        }
      }
      if (!s) {
        break;
      }
    }
    int var = __builtin_popcount(left | right);
    num ans = 0;
    for (int i = 0; i <= var; ++i) {
      vector<int> w;
      for (int t = 0; t <= 40; ++t) {
        num v = 0;
        for (int j = 1; j <= t; ++j) {
          v += power((num) (t - j + 1), i) * power((num) (j - 1), var - i);
        }
        w.push_back((int) v);
      }
      ans += ways[i] * solve(w, m);
    }
    cout << ans * power((num) m, n - var) << "\n";
  }
  return 0;
}
