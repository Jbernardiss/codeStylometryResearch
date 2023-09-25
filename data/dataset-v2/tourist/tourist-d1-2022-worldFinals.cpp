/**
 *    author:  tourist
 *    created: 05.08.2022 16:58:01       
**/
#include <bits/stdc++.h>

using namespace std;

#ifdef LOCAL
#include "algo/debug.h"
#else
#define debug(...) 42
#endif

template <typename T>
T inverse(T a, T m) {
  T u = 0, v = 1;
  while (a != 0) {
    T t = m / a;
    m -= t * a; swap(a, m);
    u -= t * v; swap(u, v);
  }
  assert(m == 1);
  return u;
}

template <typename T>
class Modular {
 public:
  using Type = typename decay<decltype(T::value)>::type;

  constexpr Modular() : value() {}
  template <typename U>
  Modular(const U& x) {
    value = normalize(x);
  }

  template <typename U>
  static Type normalize(const U& x) {
    Type v;
    if (-mod() <= x && x < mod()) v = static_cast<Type>(x);
    else v = static_cast<Type>(x % mod());
    if (v < 0) v += mod();
    return v;
  }

  const Type& operator()() const { return value; }
  template <typename U>
  explicit operator U() const { return static_cast<U>(value); }
  constexpr static Type mod() { return T::value; }

  Modular& operator+=(const Modular& other) { if ((value += other.value) >= mod()) value -= mod(); return *this; }
  Modular& operator-=(const Modular& other) { if ((value -= other.value) < 0) value += mod(); return *this; }
  template <typename U> Modular& operator+=(const U& other) { return *this += Modular(other); }
  template <typename U> Modular& operator-=(const U& other) { return *this -= Modular(other); }
  Modular& operator++() { return *this += 1; }
  Modular& operator--() { return *this -= 1; }
  Modular operator++(int) { Modular result(*this); *this += 1; return result; }
  Modular operator--(int) { Modular result(*this); *this -= 1; return result; }
  Modular operator-() const { return Modular(-value); }

  template <typename U = T>
  typename enable_if<is_same<typename Modular<U>::Type, int>::value, Modular>::type& operator*=(const Modular& rhs) {
#ifdef _WIN32
    uint64_t x = static_cast<int64_t>(value) * static_cast<int64_t>(rhs.value);
    uint32_t xh = static_cast<uint32_t>(x >> 32), xl = static_cast<uint32_t>(x), d, m;
    asm(
      "divl %4; \n\t"
      : "=a" (d), "=d" (m)
      : "d" (xh), "a" (xl), "r" (mod())
    );
    value = m;
#else
    value = normalize(static_cast<int64_t>(value) * static_cast<int64_t>(rhs.value));
#endif
    return *this;
  }
  template <typename U = T>
  typename enable_if<is_same<typename Modular<U>::Type, long long>::value, Modular>::type& operator*=(const Modular& rhs) {
    long long q = static_cast<long long>(static_cast<long double>(value) * rhs.value / mod());
    value = normalize(value * rhs.value - q * mod());
    return *this;
  }
  template <typename U = T>
  typename enable_if<!is_integral<typename Modular<U>::Type>::value, Modular>::type& operator*=(const Modular& rhs) {
    value = normalize(value * rhs.value);
    return *this;
  }

  Modular& operator/=(const Modular& other) { return *this *= Modular(inverse(other.value, mod())); }

  friend const Type& abs(const Modular& x) { return x.value; }

  template <typename U>
  friend bool operator==(const Modular<U>& lhs, const Modular<U>& rhs);

  template <typename U>
  friend bool operator<(const Modular<U>& lhs, const Modular<U>& rhs);

  template <typename V, typename U>
  friend V& operator>>(V& stream, Modular<U>& number);

 private:
  Type value;
};

template <typename T> bool operator==(const Modular<T>& lhs, const Modular<T>& rhs) { return lhs.value == rhs.value; }
template <typename T, typename U> bool operator==(const Modular<T>& lhs, U rhs) { return lhs == Modular<T>(rhs); }
template <typename T, typename U> bool operator==(U lhs, const Modular<T>& rhs) { return Modular<T>(lhs) == rhs; }

template <typename T> bool operator!=(const Modular<T>& lhs, const Modular<T>& rhs) { return !(lhs == rhs); }
template <typename T, typename U> bool operator!=(const Modular<T>& lhs, U rhs) { return !(lhs == rhs); }
template <typename T, typename U> bool operator!=(U lhs, const Modular<T>& rhs) { return !(lhs == rhs); }

template <typename T> bool operator<(const Modular<T>& lhs, const Modular<T>& rhs) { return lhs.value < rhs.value; }

template <typename T> Modular<T> operator+(const Modular<T>& lhs, const Modular<T>& rhs) { return Modular<T>(lhs) += rhs; }
template <typename T, typename U> Modular<T> operator+(const Modular<T>& lhs, U rhs) { return Modular<T>(lhs) += rhs; }
template <typename T, typename U> Modular<T> operator+(U lhs, const Modular<T>& rhs) { return Modular<T>(lhs) += rhs; }

template <typename T> Modular<T> operator-(const Modular<T>& lhs, const Modular<T>& rhs) { return Modular<T>(lhs) -= rhs; }
template <typename T, typename U> Modular<T> operator-(const Modular<T>& lhs, U rhs) { return Modular<T>(lhs) -= rhs; }
template <typename T, typename U> Modular<T> operator-(U lhs, const Modular<T>& rhs) { return Modular<T>(lhs) -= rhs; }

template <typename T> Modular<T> operator*(const Modular<T>& lhs, const Modular<T>& rhs) { return Modular<T>(lhs) *= rhs; }
template <typename T, typename U> Modular<T> operator*(const Modular<T>& lhs, U rhs) { return Modular<T>(lhs) *= rhs; }
template <typename T, typename U> Modular<T> operator*(U lhs, const Modular<T>& rhs) { return Modular<T>(lhs) *= rhs; }

template <typename T> Modular<T> operator/(const Modular<T>& lhs, const Modular<T>& rhs) { return Modular<T>(lhs) /= rhs; }
template <typename T, typename U> Modular<T> operator/(const Modular<T>& lhs, U rhs) { return Modular<T>(lhs) /= rhs; }
template <typename T, typename U> Modular<T> operator/(U lhs, const Modular<T>& rhs) { return Modular<T>(lhs) /= rhs; }

template<typename T, typename U>
Modular<T> power(const Modular<T>& a, const U& b) {
  assert(b >= 0);
  Modular<T> x = a, res = 1;
  U p = b;
  while (p > 0) {
    if (p & 1) res *= x;
    x *= x;
    p >>= 1;
  }
  return res;
}

template <typename T>
bool IsZero(const Modular<T>& number) {
  return number() == 0;
}

template <typename T>
string to_string(const Modular<T>& number) {
  return to_string(number());
}

// U == std::ostream? but done this way because of fastoutput
template <typename U, typename T>
U& operator<<(U& stream, const Modular<T>& number) {
  return stream << number();
}

// U == std::istream? but done this way because of fastinput
template <typename U, typename T>
U& operator>>(U& stream, Modular<T>& number) {
  typename common_type<typename Modular<T>::Type, long long>::type x;
  stream >> x;
  number.value = Modular<T>::normalize(x);
  return stream;
}

/*
using ModType = int;

struct VarMod { static ModType value; };
ModType VarMod::value;
ModType& md = VarMod::value;
using Mint = Modular<VarMod>;
*/

constexpr int md = (int) 1e9 + 7;
using Mint = Modular<std::integral_constant<decay<decltype(md)>::type, md>>;

/*vector<Mint> fact(1, 1);
vector<Mint> inv_fact(1, 1);

Mint C(int n, int k) {
  if (k < 0 || k > n) {
    return 0;
  }
  while ((int) fact.size() < n + 1) {
    fact.push_back(fact.back() * (int) fact.size());
    inv_fact.push_back(1 / fact.back());
  }
  return fact[n] * inv_fact[k] * inv_fact[n - k];
}*/

int main() {
  ios::sync_with_stdio(false);
  cin.tie(0);
  int tt;
  cin >> tt;
  for (int qq = 1; qq <= tt; qq++) {
    cout << "Case #" << qq << ": ";
    int n;
    cin >> n;
    string s;
    cin >> s;
    vector<int> a(n);
    for (int i = 0; i < n; i++) {
      cin >> a[i];
      --a[i];
    }
    vector<vector<int>> cnt(n, vector<int>(3, 0));
    for (int i = 0; i < n; i++) {
      int me = (s[i] == '.' ? 0 : (s[i] == 'C' ? 1 : 2));
      cnt[i][me] += 1;
      if (a[i] > i) {
        for (int j = 0; j < 3; j++) {
          cnt[a[i]][j] += cnt[i][j];
        }
      }
    }
    vector<int> root(n);
    for (int i = n - 1; i >= 0; i--) {
      if (a[i] > i) {
        root[i] = root[a[i]];
      } else {
        root[i] = i;
      }
    }
    vector<Mint> p2(n + 1);
    p2[0] = 1;
    for (int i = 1; i <= n; i++) {
      p2[i] = p2[i - 1] * 2;
    }
    int ques = 0;
    for (int i = 0; i < n; i++) {
      if (s[i] == '?') {
        ques += 1;
      }
    }
    vector<bool> is_stealer(n, false);
    vector<bool> ever_at(n, false);
    Mint ans = 0;
    Mint cur = 1;
    int at = n - 1;
    ever_at[at] = true;
    for (int i = n - 1; i >= 0; i--) {
      if (i == at) {
        if (a[i] < i) {
          if (cnt[i][1] > 0) {
            cur *= p2[cnt[i][2]];
          } else {
            cur *= p2[cnt[i][2]] - 1;
          }
          ques -= cnt[i][2];
          at = a[i];
          ever_at[at] = true;
          continue;
        }
        if (is_stealer[root[a[i]]]) {
          // do nothing
        } else {
          if (ever_at[a[i]]) {
            Mint div_by;
            if (cnt[a[i]][1] > 0) {
              div_by = p2[cnt[a[i]][2]];
            } else {
              div_by = p2[cnt[a[i]][2]] - 1;
            }
            ques += cnt[a[i]][2];
            if (div_by == 0) {
              break;
            }
            cur /= div_by;
            if (cnt[i][1] > 0) {
              cur *= p2[cnt[i][2]];
            } else {
              cur *= p2[cnt[i][2]] - 1;
            }
            ques -= cnt[i][2];
            vector<bool> in_my_subtree(n, false);
            in_my_subtree[a[i]] = true;
            for (int j = i - 1; j >= 0; j--) {
              if (a[j] > j && in_my_subtree[a[j]]) {
                in_my_subtree[j] = true;
              }
            }
            vector<int> aux(3);
            for (int j = 0; j < n; j++) {
              if (in_my_subtree[j]) {
                int me = (s[j] == '.' ? 0 : (s[j] == 'C' ? 1 : 2));
                aux[me] += 1;
              }
            }
            if (aux[1] > 0) {
              cur *= p2[aux[2]];
            } else {
              cur *= p2[aux[2]] - 1;
            }
            ques -= aux[2];
            ans += cur * p2[ques];
          } else {
            if (ever_at[root[a[i]]]) {
              Mint div_by;
              if (cnt[root[a[i]]][1] > 0) {
                div_by = p2[cnt[root[a[i]]][2]];
              } else {
                div_by = p2[cnt[root[a[i]]][2]] - 1;
              }
              ques += cnt[root[a[i]]][2];
              if (div_by == 0) {
                break;
              }
              cur /= div_by;
            }
            {
              vector<bool> in_my_subtree(n, false);
              in_my_subtree[a[i]] = true;
              for (int j = i - 1; j >= 0; j--) {
                if (a[j] > j && in_my_subtree[a[j]]) {
                  in_my_subtree[j] = true;
                }
              }
              vector<int> aux(3);
              for (int j = 0; j < n; j++) {
                if (in_my_subtree[j]) {
                  int me = (s[j] == '.' ? 0 : (s[j] == 'C' ? 1 : 2));
                  aux[me] += 1;
                }
              }
              if (aux[1] > 0) {
                cur *= p2[aux[2]];
              } else {
                cur *= p2[aux[2]] - 1;
              }
              ques -= aux[2];
            }
            if (cnt[i][1] > 0) {
              cur *= p2[cnt[i][2]];
            } else {
              cur *= p2[cnt[i][2]] - 1;
            }
            ques -= cnt[i][2];
            ans += cur * p2[ques];
          }
        }
        break;
      }
      if (at < i && a[i] == at) {
        is_stealer[i] = true;
        Mint add = cur;
        if (cnt[i][1] > 0) {
          add *= p2[cnt[i][2]];
        } else {
          add *= p2[cnt[i][2]] - 1;
        }
        ques -= cnt[i][2];
        ans += add * p2[ques];
        if (cnt[i][1] > 0) {
          break;
        }
        continue;
      }
    }
    cout << ans << '\n';
  }
  return 0;
}
