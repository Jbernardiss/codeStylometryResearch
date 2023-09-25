#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <stack>
#include <queue>
#include <set>
#include <map>
#include <cmath>
using namespace std;
#define MOD
#define ADD(X,Y) ((X) = ((X) + (Y)%MOD) % MOD)
typedef long long i64; typedef vector<int> ivec; typedef vector<string> svec;

using i32 = int;
using u32 = unsigned int;
using i64 = long long;
using u64 = unsigned long long;

template <u32 Mod> class ModInt {
    using Self = ModInt<Mod>;
    static_assert(Mod <= std::numeric_limits<i32>::max());
public:
    ModInt(i64 value = 0) {
        if (value < 0) {
            value_ = (Mod - (-value % Mod)) % Mod;
        } else {
            value_ = value % Mod;
        }
    }

    ModInt(const Self& other) : value_(other.value_) {}

    operator i32() const {
        return value_;
    }

    operator i64() const {
        return value_;
    }

    Self operator+(const Self& other) const {
        Self res(*this);
        res += other;
        return res;
    }

    Self operator-(const Self& other) const {
        Self res(*this);
        res -= other;
        return res;
    }

    Self operator*(const Self& other) const {
        Self res(*this);
        res *= other;
        return res;
    }

    Self operator/(const Self& other) const {
        Self res(*this);
        res /= other;
        return res;
    }

    Self operator-() const {
        Self res(0);
        res -= *this;
        return res;
    }

    Self pow(i64 power) const {
        Self ret(1), p(*this);
        if (power < 0) {
            power *= -1;
            p = p.inv();
        }
        for (i64 i = 0; (1 << i) <= power; ++i) {
            if ((power >> i) & 1) ret *= p;
            p *= p;
        }
        return ret;
    }

    Self& operator+=(const Self& other) {
        value_ += other.value_;
        if (value_ >= Mod) value_ -= Mod;
        return *this;
    }

    Self& operator-=(const Self& other) {
        value_ += Mod - other.value_;
        if (value_ >= Mod) value_ -= Mod;
        return *this;
    }

    Self& operator*=(const Self& other) {
        value_ = (u32)(((u64)value_ * other.value_) % Mod);
        return *this;
    }

    Self& operator/=(const Self& other) {
        *this *= other.inv();
        return *this;
    }

    Self inv() const {
        if (value_ < inv_tbl_.size()) return inv_tbl_[value_];
        else return pow(Mod - 2);
    }

private:
    u32 value_;
    static const std::vector<Self> inv_tbl_;
};

template <u32 Mod>
std::vector<ModInt<Mod>> create_inv_tbl_(u32 n) {
    std::vector<ModInt<Mod>> res;
    res.reserve(n + 1);
    res.push_back(0);
    res.push_back(1);
    for (u32 i = 2; i <= n; ++i) {
        // MOD / i == 0
        // MOD // i + (MOD % i) / i == 0
        // 1 / i == -(MOD // i) / (MOD % i)
        res.push_back(res[Mod % i] * ModInt<Mod>(Mod - (Mod / i)));
    }
    return res;
}

template <u32 Mod>
const std::vector<ModInt<Mod>> ModInt<Mod>::inv_tbl_ = create_inv_tbl_<Mod>(1000000);

template <class T, u32 Mod>
ModInt<Mod> operator+(T x, ModInt<Mod> y) {
    return ModInt<Mod>(x) + y;
}

template <class T, u32 Mod>
ModInt<Mod> operator-(T x, ModInt<Mod> y) {
    return ModInt<Mod>(x) - y;
}

template <class T, u32 Mod>
ModInt<Mod> operator*(T x, ModInt<Mod> y) {
    return ModInt<Mod>(x) * y;
}

template <class T, u32 Mod>
ModInt<Mod> operator/(T x, ModInt<Mod> y) {
    return ModInt<Mod>(x) / y;
}

template <class T, u32 Mod>
ModInt<Mod> operator+(ModInt<Mod> x, T y) {
    return x + ModInt<Mod>(y);
}

template <class T, u32 Mod>
ModInt<Mod> operator-(ModInt<Mod> x, T y) {
    return x - ModInt<Mod>(y);
}

template <class T, u32 Mod>
ModInt<Mod> operator*(ModInt<Mod> x, T y) {
    return x * ModInt<Mod>(y);
}

template <class T, u32 Mod>
ModInt<Mod> operator/(ModInt<Mod> x, T y) {
    return x / ModInt<Mod>(y);
}

using mint = ModInt<1000000007>;

int TC;
char S[101010];
int N, D;

i64 pows[101010];
i64 acc[101010];

mint naive() {
	mint dp1[1010], dp2[1010];
	for (int i = 0; i <= N; ++i) dp1[i] = dp2[i] = 0;
	dp1[0] = 1;

	for (int i = 1; i <= N; ++i) {
		for (int j = 0; j < i; ++j) {
			i64 v = (acc[i] - acc[j] * pows[i - j] % D + D) % D;
			if (v == 0) {
				dp1[i] += dp1[j] + dp2[j];
			} else {
				dp2[i] += dp1[j];
			}
		}
	}

	mint ans = dp1[N] + dp2[N];
	return ans;
}

mint dpg[101010], dpb[101010];
mint tbla[1010101], tblb[1010101];
i64 invpow[101010];
i64 acc2[101010];

mint fast() {
	int D2 = D;
	while (D2 % 2 == 0) D2 /= 2;
	while (D2 % 5 == 0) D2 /= 5;
	int Drem = D / D2;

	i64 inv = -1;
	for (int i = 0; i < D2; ++i) {
		if ((10 * i) % D2 == 1 % D2) inv = i;
	}

	acc2[0] = 0;
	for (int i = 1; i <= N; ++i) acc2[i] = (acc2[i - 1] * 10 + (S[i - 1] - '0')) % D2;
	
	invpow[0] = 1 % D;
	for (int i = 1; i <= N; ++i) invpow[i] = invpow[i - 1] * inv % D;

	for (int i = 0; i < D; ++i) tbla[i] = tblb[i] = 0;

	for (int i = 0; i <= N; ++i) dpg[i] = dpb[i] = 0;
	dpg[0] = 1;

	mint dpg_acc = 1;

	const int X = 20;

	for (int i = 1; i <= N; ++i) {
		mint good = 0, bad = dpg_acc;
		for (int j = max(0, i - X); j < i; ++j) {
			i64 v = (acc[i] - acc[j] * pows[i - j] % D + D) % D;
			if (v == 0) {
				good += dpg[j] + dpb[j];
				bad -= dpg[j];
			}
		}
		if (acc[i] % Drem == 0) {
			i64 aa = acc2[i];
			int target = aa * invpow[i] % D2;

			good += tbla[target];
			bad -= tblb[target];
			// printf("%d from %d\n", i, target);
		}
		dpg[i] = good;
		dpb[i] = bad;
		dpg_acc += dpg[i];
		if (i >= X) {
			int idx = (acc2[i - X] * invpow[i - X]) % D2;
			tbla[idx] += dpg[i - X] + dpb[i - X];
			tblb[idx] += dpg[i - X];
			// printf("%d idx %d\n", i - X, idx);
		}
	}

	mint ans = dpg[N] + dpb[N];
	return ans;
}

int main()
{
	pows[0] = 1;
	for (int i = 1; i <= 100000; ++i) pows[i] = pows[i - 1] * 10;

	scanf("%d", &TC);
	for (int t = 0; t++ < TC;) {
		// input & compute
		scanf("%s%d", S, &D);
		N = strlen(S);
		pows[0] = 1 % D;
		for (int i = 1; i <= N; ++i) pows[i] = pows[i - 1] * 10 % D;

		acc[0] = 0;
		for (int i = 1; i <= N; ++i) acc[i] = (acc[i - 1] * 10 + (S[i - 1] - '0')) % D;

		// mint ans = naive();
		mint ans2 = fast();
		// output
		printf("Case #%d: %d\n", t, (int)ans2);

	}

	return 0;
}
