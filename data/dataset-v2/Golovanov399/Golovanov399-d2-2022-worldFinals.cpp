#include <bits/stdc++.h>

#include <cstdint>
#include <istream>
#include <ostream>

using std::istream, std::ostream;

template <uint32_t base>
struct Montgomery {
	using i32 = int32_t;
	using u32 = uint32_t;
	using u64 = uint64_t;

	static constexpr u32 mod() {
		return base;
	}

	static constexpr u32 np = []() {
		u32 x = base;
		for (int i = 0; i < 4; ++i) {
			x *= 2u - base * x;
		}
		return -x;
	}();
	static constexpr u32 r2 = -(u64)(base) % base;

	static_assert(base < (1u << 30));
	static_assert(base * np + 1 == 0);

	static u32 reduce(u64 x) {
		return (x + (u64)((u32)x * np) * base) >> 32;
	}

	u32 x;
	Montgomery(): x(0) {}
	constexpr Montgomery(long long y): x(y ? reduce((u64)(y % base + base) * r2) : 0) {}

	Montgomery& operator +=(const Montgomery& ot) {
		if ((i32)(x += ot.x - 2 * base) < 0) {
			x += 2 * base;
		}
		return *this;
	}

	Montgomery& operator -=(const Montgomery& ot) {
		if ((i32)(x -= ot.x) < 0) {
			x += 2 * base;
		}
		return *this;
	}

	Montgomery& operator *=(const Montgomery& ot) {
		x = reduce((u64)x * ot.x);
		return *this;
	}

	Montgomery& operator /=(const Montgomery& ot) {
		return *this *= ot.inverse();
	}

	friend Montgomery operator +(Montgomery a, const Montgomery& b) {
		a += b;
		return a;
	}

	friend Montgomery operator -(Montgomery a, const Montgomery& b) {
		a -= b;
		return a;
	}

	friend Montgomery operator *(Montgomery a, const Montgomery& b) {
		a *= b;
		return a;
	}

	friend Montgomery operator /(Montgomery a, const Montgomery& b) {
		a /= b;
		return a;
	}

	Montgomery operator -() const {
		return Montgomery() - *this;
	}

	u32 get() const {
		u32 res = reduce(x);
		return res < base ? res : res - base;
	}

	u32 operator ()() const {
		return get();
	}

	Montgomery inverse() const {
		return pow(base - 2);
	}

	Montgomery inv() const {
		return inverse();
	}

	Montgomery pow(int64_t p) const {
		if (p < 0) {
			return pow(-p).inverse();
		}
		Montgomery res = 1;
		Montgomery a = *this;
		while (p) {
			if (p & 1) {
				res *= a;
			}
			p >>= 1;
			a *= a;
		}
		return res;
	}

	friend istream& operator >>(istream& istr, Montgomery& m) {
		long long x;
		istr >> x;
		m = Montgomery(x);
		return istr;
	}

	friend ostream& operator <<(ostream& ostr, const Montgomery& m) {
		return ostr << m.get();
	}

	bool operator ==(const Montgomery& ot) const {
		return (x >= base ? x - base : x) == (ot.x >= base ? ot.x - base : ot.x);
	}

	bool operator !=(const Montgomery& ot) const {
		return (x >= base ? x - base : x) != (ot.x >= base ? ot.x - base : ot.x);
	}

	explicit operator int64_t() const {
		return x;
	}

	explicit operator bool() const {
		return x;
	}
};


#define all(x) (x).begin(), (x).end()
#define uniquify(x) sort(all((x))), (x).resize(unique(all((x))) - (x).begin())

using namespace std;

inline int nxt() {
	int x;
	cin >> x;
	return x;
}

constexpr int mod = 1'000'000'007;
using Mint = Montgomery<mod>;

struct Formula {
	int lhs, rhs;
	char op;
};

void solve() {
	int n = nxt();
	string s;
	cin >> s;
	vector<Formula> a(n, {-1, -1, '\0'});
	vector<int> fids(n);
	iota(all(fids), 0);
	for (int i = 0; i < n; ++i) {
		int j = nxt() - 1;
		int lhs = fids[i];
		int rhs = fids[j];
		fids[j] = a.size();
		a.push_back({lhs, rhs, 'v'});
		fids[i] = a.size();
		a.push_back({lhs, rhs, '^'});
	}

	const int sz = a.size();
	vector<int> freq(sz);
	function<void(int)> rec = [&](int id) {
		if (id == -1) {
			return;
		}
		freq[id] += 1;
		rec(a[id].lhs);
		rec(a[id].rhs);
	};
	rec(fids[n - 1]);

	int cnt_useless_qms = 0;
	for (int i = 0; i < n; ++i) {
		if (!freq[i] && s[i] == '?') {
			++cnt_useless_qms;
		}
	}

	assert(*max_element(all(freq)) <= 2);
	int used_twice = sz - 1;

	auto paired = [&](int v) {
		return v % 2 == n % 2 ? v + 1 : v - 1;
	};

	while (used_twice >= n && freq[used_twice] + freq[paired(used_twice)] < 2) {
		--used_twice;
	}
	if (used_twice < n) {
		used_twice = -1;
	}

	function<void(int)> show_formula = [&](int id) {
		if (id < n) {
			cerr << id;
			return;
		} else {
			cerr << "(";
			show_formula(a[id].lhs);
			cerr << a[id].op;
			show_formula(a[id].rhs);
			cerr << ")";
		}
	};

	vector<array<Mint, 2>> num_ways(sz);
	vector<char> calculated(sz, false);
	function<void(int)> calc_ways = [&](int id) {
		if (id == -1) {
			return;
		}
		if (calculated[id]) {
			return;
		}
		calculated[id] = true;
		num_ways[id].fill(0);
		if (id < n) {
			if (s[id] != 'C') {
				num_ways[id][0] += 1;
			}
			if (s[id] != '.') {
				num_ways[id][1] += 1;
			}
			return;
		}
		calc_ways(a[id].lhs);
		calc_ways(a[id].rhs);
		const auto& lnum = num_ways[a[id].lhs];
		const auto& rnum = num_ways[a[id].rhs];
		if (a[id].op == 'v') {
			num_ways[id][0] = lnum[0] * rnum[0];
			num_ways[id][1] = (lnum[0] + lnum[1]) * (rnum[0] + rnum[1]) - num_ways[id][0];
		} else {
			num_ways[id][1] = lnum[1] * rnum[1];
			num_ways[id][0] = (lnum[0] + lnum[1]) * (rnum[0] + rnum[1]) - num_ways[id][1];
		}
	};
	function<void(int, int, int)> calc_ways_restricted = [&](int id, int x, int y) {
		if (id == used_twice || id == paired(used_twice)) {
			num_ways[id].fill(0);
			if (a[id].op == 'v') {
				num_ways[id][x || y] = num_ways[a[id].lhs][x] * num_ways[a[id].rhs][y];
			} else {
				num_ways[id][x && y] = num_ways[a[id].lhs][x] * num_ways[a[id].rhs][y];
			}
			return;
		}
		num_ways[id].fill(0);
		if (id < n) {
			if (s[id] != 'C') {
				num_ways[id][0] += 1;
			}
			if (s[id] != '.') {
				num_ways[id][1] += 1;
			}
			return;
		}
		calc_ways_restricted(a[id].lhs, x, y);
		calc_ways_restricted(a[id].rhs, x, y);
		const auto& lnum = num_ways[a[id].lhs];
		const auto& rnum = num_ways[a[id].rhs];
		if (a[id].op == 'v') {
			num_ways[id][0] = lnum[0] * rnum[0];
			num_ways[id][1] = (lnum[0] + lnum[1]) * (rnum[0] + rnum[1]) - num_ways[id][0];
		} else {
			num_ways[id][1] = lnum[1] * rnum[1];
			num_ways[id][0] = (lnum[0] + lnum[1]) * (rnum[0] + rnum[1]) - num_ways[id][1];
		}
	};

	// show_formula(fids[n - 1]);
	// cerr << "\n";

	if (used_twice == -1) {
		calc_ways(fids[n - 1]);
	} else {
		calc_ways(a[used_twice].lhs);
		calc_ways(a[used_twice].rhs);
		auto tmp = num_ways;
		Mint val = 0;
		for (int x : {0, 1}) {
			for (int y : {0, 1}) {
				Mint lval = num_ways[a[used_twice].lhs][x];
				Mint rval = num_ways[a[used_twice].rhs][y];
				num_ways[a[used_twice].lhs].fill(0);
				num_ways[a[used_twice].rhs].fill(0);
				num_ways[a[used_twice].lhs][x] = num_ways[a[used_twice].rhs][y] = 1;
				calc_ways_restricted(fids[n - 1], x, y);
				val += num_ways[fids[n - 1]][1] * lval * rval;
				num_ways = tmp;
			}
		}
		num_ways[fids[n - 1]][1] = val;
	}

	Mint ans = num_ways[fids[n - 1]][1];
	cout << ans * Mint(2).pow(cnt_useless_qms) << "\n";
}

int main() {
	int t = nxt();
	for (int i = 1; i <= t; ++i) {
		cout << "Case #" << i << ": ";
		solve();
	}

	return 0;
}
