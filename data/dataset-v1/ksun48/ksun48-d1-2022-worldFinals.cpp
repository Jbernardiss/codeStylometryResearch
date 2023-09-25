#include <bits/stdc++.h>
using namespace std;

template <int MOD_> struct modnum {
	static constexpr int MOD = MOD_;
	static_assert(MOD_ > 0, "MOD must be positive");

private:
	using ll = long long;

	int v;

	static int minv(int a, int m) {
		a %= m;
		assert(a);
		return a == 1 ? 1 : int(m - ll(minv(m, a)) * ll(m) / a);
	}

public:

	modnum() : v(0) {}
	modnum(ll v_) : v(int(v_ % MOD)) { if (v < 0) v += MOD; }
	explicit operator int() const { return v; }
	friend std::ostream& operator << (std::ostream& out, const modnum& n) { return out << int(n); }
	friend std::istream& operator >> (std::istream& in, modnum& n) { ll v_; in >> v_; n = modnum(v_); return in; }

	friend bool operator == (const modnum& a, const modnum& b) { return a.v == b.v; }
	friend bool operator != (const modnum& a, const modnum& b) { return a.v != b.v; }

	modnum inv() const {
		modnum res;
		res.v = minv(v, MOD);
		return res;
	}
	friend modnum inv(const modnum& m) { return m.inv(); }
	modnum neg() const {
		modnum res;
		res.v = v ? MOD-v : 0;
		return res;
	}
	friend modnum neg(const modnum& m) { return m.neg(); }

	modnum operator- () const {
		return neg();
	}
	modnum operator+ () const {
		return modnum(*this);
	}

	modnum& operator ++ () {
		v ++;
		if (v == MOD) v = 0;
		return *this;
	}
	modnum& operator -- () {
		if (v == 0) v = MOD;
		v --;
		return *this;
	}
	modnum& operator += (const modnum& o) {
		v += o.v;
		if (v >= MOD) v -= MOD;
		return *this;
	}
	modnum& operator -= (const modnum& o) {
		v -= o.v;
		if (v < 0) v += MOD;
		return *this;
	}
	modnum& operator *= (const modnum& o) {
		v = int(ll(v) * ll(o.v) % MOD);
		return *this;
	}
	modnum& operator /= (const modnum& o) {
		return *this *= o.inv();
	}

	friend modnum operator ++ (modnum& a, int) { modnum r = a; ++a; return r; }
	friend modnum operator -- (modnum& a, int) { modnum r = a; --a; return r; }
	friend modnum operator + (const modnum& a, const modnum& b) { return modnum(a) += b; }
	friend modnum operator - (const modnum& a, const modnum& b) { return modnum(a) -= b; }
	friend modnum operator * (const modnum& a, const modnum& b) { return modnum(a) *= b; }
	friend modnum operator / (const modnum& a, const modnum& b) { return modnum(a) /= b; }
};

template <typename T> T pow(T a, long long b) {
	assert(b >= 0);
	T r = 1; while (b) { if (b & 1) r *= a; b >>= 1; a *= a; } return r;
}

using num = modnum<int(1e9) + 7>;

struct UF {
    int n;
    vector<int> par;
    UF(int _n) : n(_n) {
        for(int i = 0; i < n; i++) par.push_back(i);
    }
    int find(int a){
        if(a != par[a]) par[a] = find(par[a]);
        return par[a];
    }
    bool join(int a, int b){
        a = find(a);
        b = find(b);
        par[a] = b;
        return (a != b);
    }
};

void solve(int t){
	int N;
	cin >> N;
	string S;
	cin >> S;
	vector<int> f(N);
	for(int& x : f){
		cin >> x;
		x--;
	}
	num tot_ways = 1;
	for(char c : S) if(c == '?') tot_ways *= 2;
	UF uf(N);
	for(int i = 0; i < N; i++){
		uf.join(i, f[i]);
	}
	vector<int> boxes;
	for(int i = 0; i < N; i++){
		if(uf.find(i) == uf.find(N-1)) boxes.push_back(i);
	}
	UF uf2(N);
	int first_cycle = -1;
	for(int i = (int)boxes.size() - 1; i >= 0; i--){
		int b = boxes[i];
		if(!uf2.join(b, f[b])){
			assert(first_cycle == -1);
			first_cycle = b;
		}
	}
	assert(first_cycle >= 0);
	num ans = 0;
	for(int l : {0, 1}){
		for(int r : {0, 1}){
			vector<num> prob(N);
			for(int i = 0; i < N; i++){
				if(S[i] == 'C'){
					prob[i] = 1;
				} else if(S[i] == '?'){
					prob[i] = num(1) / num(2);
				} else if(S[i] == '.'){
					prob[i] = 0;
				} else assert(false);
			}
			num mult;
			for(int b = 0; b < N; b++){
				if(b == first_cycle){
					mult = (l ? prob[b] : (1 - prob[b])) * (r ? prob[f[b]] : (1 - prob[f[b]]));
					prob[b] = l;
					prob[f[b]] = r;
				}
				num x = prob[b];
				num y = prob[f[b]];
				prob[b] = x * y;
				prob[f[b]] = x + y - x * y;
			}
			ans += mult * prob[N-1];
		}
	}

	cout << "Case #" << t << ": ";
	cout << (ans * tot_ways) << '\n';
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