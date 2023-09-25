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
    int d;
    cin >> s >> d;
    int e = 1;
    while (d % 2 == 0) {
      d /= 2;
      e *= 2;
    }
    while (d % 5 == 0) {
      d /= 5;
      e *= 5;
    }
    int n = s.size();
    vector<int> a(n + 1);
    for (int i = 0; i < n; ++i) {
      a[i + 1] = (a[i] * 10 + (s[i] - '0')) % (d * e);
    }
    int inv10 = d == 1 ? 0 : inverse(10, d);
    vector<int> pw(n + 1);
    pw[0] = 1;
    for (int i = 0; i < n; ++i) {
      pw[i + 1] = (long long) pw[i] * inv10 % d;
    }
    vector<int> base(20);
    base[0] = 1;
    for (int i = 0; i + 1 < 20; ++i) {
      base[i + 1] = base[i] * 10 % (d * e);
    }
    vector<num> foo(n + 1), bar(n + 1);
    vector<num> offset_foo(d), offset_bar(d);
    bar[0] = 1;
    num pref = 0;
    for (int i = 0; i <= n; ++i) {
      foo[i] += pref;
      if (a[i] % e == 0) {
        foo[i] += offset_foo[(long long) a[i] * pw[i] % d];
        bar[i] += offset_bar[(long long) a[i] * pw[i] % d];
      }
      pref += bar[i];
      offset_foo[(long long) a[i] * pw[i] % d] -= bar[i];
      offset_bar[(long long) a[i] * pw[i] % d] += foo[i] + bar[i];
      for (int j = i + 1; j <= n && j < i + 20; ++j) {
        if ((a[j] - (long long) a[i] * base[j - i]) % (d * e) == 0) {
          foo[j] -= bar[i];
          bar[j] += foo[i] + bar[i];
        }
        if (a[j] % e == 0 && (long long) a[i] * pw[i] % d == (long long) a[j] * pw[j] % d) {
          foo[j] += bar[i];
          bar[j] -= foo[i] + bar[i];
        }
      }
    }
    cout << foo[n] + bar[n] << "\n";
  }
  return 0;
}
