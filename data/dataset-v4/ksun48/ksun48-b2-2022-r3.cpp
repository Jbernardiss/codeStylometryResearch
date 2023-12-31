#include <bits/stdc++.h>
using namespace std;

namespace atcoder {

namespace internal {

// @param n `0 <= n`
// @return minimum non-negative `x` s.t. `n <= 2**x`
int ceil_pow2(int n) {
    int x = 0;
    while ((1U << x) < (unsigned int)(n)) x++;
    return x;
}

// @param n `1 <= n`
// @return minimum non-negative `x` s.t. `(n & (1 << x)) != 0`
constexpr int bsf_constexpr(unsigned int n) {
    int x = 0;
    while (!(n & (1 << x))) x++;
    return x;
}

// @param n `1 <= n`
// @return minimum non-negative `x` s.t. `(n & (1 << x)) != 0`
int bsf(unsigned int n) {
#ifdef _MSC_VER
    unsigned long index;
    _BitScanForward(&index, n);
    return index;
#else
    return __builtin_ctz(n);
#endif
}

}  // namespace internal

}  // namespace atcoder

namespace atcoder {

template <class S,
          S (*op)(S, S),
          S (*e)(),
          class F,
          S (*mapping)(F, S),
          F (*composition)(F, F),
          F (*id)()>
struct lazy_segtree {
  public:
    lazy_segtree() : lazy_segtree(0) {}
    explicit lazy_segtree(int n) : lazy_segtree(std::vector<S>(n, e())) {}
    explicit lazy_segtree(const std::vector<S>& v) : _n(int(v.size())) {
        log = internal::ceil_pow2(_n);
        size = 1 << log;
        d = std::vector<S>(2 * size, e());
        lz = std::vector<F>(size, id());
        for (int i = 0; i < _n; i++) d[size + i] = v[i];
        for (int i = size - 1; i >= 1; i--) {
            update(i);
        }
    }

    void set(int p, S x) {
        assert(0 <= p && p < _n);
        p += size;
        for (int i = log; i >= 1; i--) push(p >> i);
        d[p] = x;
        for (int i = 1; i <= log; i++) update(p >> i);
    }

    S get(int p) {
        assert(0 <= p && p < _n);
        p += size;
        for (int i = log; i >= 1; i--) push(p >> i);
        return d[p];
    }

    S prod(int l, int r) {
        assert(0 <= l && l <= r && r <= _n);
        if (l == r) return e();

        l += size;
        r += size;

        for (int i = log; i >= 1; i--) {
            if (((l >> i) << i) != l) push(l >> i);
            if (((r >> i) << i) != r) push((r - 1) >> i);
        }

        S sml = e(), smr = e();
        while (l < r) {
            if (l & 1) sml = op(sml, d[l++]);
            if (r & 1) smr = op(d[--r], smr);
            l >>= 1;
            r >>= 1;
        }

        return op(sml, smr);
    }

    S all_prod() { return d[1]; }

    void apply(int p, F f) {
        assert(0 <= p && p < _n);
        p += size;
        for (int i = log; i >= 1; i--) push(p >> i);
        d[p] = mapping(f, d[p]);
        for (int i = 1; i <= log; i++) update(p >> i);
    }
    void apply(int l, int r, F f) {
        assert(0 <= l && l <= r && r <= _n);
        if (l == r) return;

        l += size;
        r += size;

        for (int i = log; i >= 1; i--) {
            if (((l >> i) << i) != l) push(l >> i);
            if (((r >> i) << i) != r) push((r - 1) >> i);
        }

        {
            int l2 = l, r2 = r;
            while (l < r) {
                if (l & 1) all_apply(l++, f);
                if (r & 1) all_apply(--r, f);
                l >>= 1;
                r >>= 1;
            }
            l = l2;
            r = r2;
        }

        for (int i = 1; i <= log; i++) {
            if (((l >> i) << i) != l) update(l >> i);
            if (((r >> i) << i) != r) update((r - 1) >> i);
        }
    }

    template <bool (*g)(S)> int max_right(int l) {
        return max_right(l, [](S x) { return g(x); });
    }
    template <class G> int max_right(int l, G g) {
        assert(0 <= l && l <= _n);
        assert(g(e()));
        if (l == _n) return _n;
        l += size;
        for (int i = log; i >= 1; i--) push(l >> i);
        S sm = e();
        do {
            while (l % 2 == 0) l >>= 1;
            if (!g(op(sm, d[l]))) {
                while (l < size) {
                    push(l);
                    l = (2 * l);
                    if (g(op(sm, d[l]))) {
                        sm = op(sm, d[l]);
                        l++;
                    }
                }
                return l - size;
            }
            sm = op(sm, d[l]);
            l++;
        } while ((l & -l) != l);
        return _n;
    }

    template <bool (*g)(S)> int min_left(int r) {
        return min_left(r, [](S x) { return g(x); });
    }
    template <class G> int min_left(int r, G g) {
        assert(0 <= r && r <= _n);
        assert(g(e()));
        if (r == 0) return 0;
        r += size;
        for (int i = log; i >= 1; i--) push((r - 1) >> i);
        S sm = e();
        do {
            r--;
            while (r > 1 && (r % 2)) r >>= 1;
            if (!g(op(d[r], sm))) {
                while (r < size) {
                    push(r);
                    r = (2 * r + 1);
                    if (g(op(d[r], sm))) {
                        sm = op(d[r], sm);
                        r--;
                    }
                }
                return r + 1 - size;
            }
            sm = op(d[r], sm);
        } while ((r & -r) != r);
        return 0;
    }

  private:
    int _n, size, log;
    std::vector<S> d;
    std::vector<F> lz;

    void update(int k) { d[k] = op(d[2 * k], d[2 * k + 1]); }
    void all_apply(int k, F f) {
        d[k] = mapping(f, d[k]);
        if (k < size) lz[k] = composition(f, lz[k]);
    }
    void push(int k) {
        all_apply(2 * k, lz[k]);
        all_apply(2 * k + 1, lz[k]);
        lz[k] = id();
    }
};

}  // namespace atcoder

using ll = int64_t;

using S = pair<ll, ll>; // max, cnt
using F = ll;
S e(){ return S{ll(-1e9), ll(0)}; }
S op(S l, S r) {
	if(l.first > r.first) return l;
	if(r.first > l.first) return r;
	return {l.first, l.second + r.second};
}
S mapping(F l, S r) { return {l + r.first, r.second}; }
F composition(F l, F r) { return l + r; }
F id() { return 0; }

void solve(int t){
	int n, C;
	cin >> n >> C;
	vector<int> a(C), b(C);
	for(int i = 0; i < C; i++){
		cin >> a[i] >> b[i];
		if(a[i] == 0) a[i]++;
	}
	vector<int> p(n);
	for(int i = 0; i < n; i++){
		cin >> p[i];
		p[i]--;
	}
	for(int i = 0; i < n; i++){
		p.push_back(p[i]);
	}
	vector<vector<int> > locs(C);
	for(int i = 0; i < 2 * n; i++) locs[p[i]].push_back(i);
	vector<tuple<int, int, int, int> > rects;
	int N = 2*n;
	for(int c = 0; c < C; c++){
		vector<int> flocs = locs[c];
		flocs.insert(flocs.begin(), -1);
		flocs.insert(flocs.end(), N);
		{
			for(int i = 0; i + 1 < (int)flocs.size(); i++){
				rects.push_back({flocs[i] + 1, flocs[i+1], flocs[i] + 1, flocs[i+1]});
			}
		}
		if(a[c] <= b[c]){
			assert(a[c] != 0);
			for(int i = 0; i + a[c] < (int)flocs.size(); i++){
				int l = flocs[i + a[c]] + 1;
				int r = flocs[min(i + b[c] + 1, (int)flocs.size() - 1)];
				if(l <= r){
					rects.push_back({flocs[i] + 1, flocs[i+1], l, r});
				}
			}
		}
	}
	vector<vector<tuple<int, int, int> >> events(N+2);
	for(auto [xa, xb, ya, yb] : rects){
		events[xa].push_back({1, ya, yb+1});
		events[xb+1].push_back({-1, ya, yb+1});
	}
	atcoder::lazy_segtree<S, op, e, F, mapping, composition, id> seg(vector<S>(N + 2, S{0, 1}));
	ll ans = 0;
	for(int l = 0; l < n; l++){
		for(auto [sgn, ya, yb] : events[l]){
			seg.apply(ya, yb, sgn);
		}
		S res = seg.prod(l+2, l+n-1 + 1);
		assert(res.first <= C);
		if(res.first == C) ans += res.second;
		// for(int r = l + 2; r <= l + n-1; r++){
		// 	int cnt = 0;
		// 	for(auto [xa, xb, ya, yb] : rects){
		// 		if(l >= xa && l <= xb && r >= ya && r <= yb) cnt++;
		// 	}
		// 	assert(cnt <= C);
		// 	if(cnt == C) ans++;
		// }
	}
	cout << "Case #" << t << ": " << ans << '\n';
}

int main(){
	ios_base::sync_with_stdio(false), cin.tie(nullptr);
	int T;
	cin >> T;
	for(int t = 1; t <= T; t++){
		solve(t);
		cout << flush;
	}
}