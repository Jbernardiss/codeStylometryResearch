#include <bits/stdc++.h>
using namespace std;

#define Fi first
#define Se second
typedef long long ll;
typedef pair<int, int> pii;
typedef pair<ll, ll> pll;
#define all(x) (x).begin(), (x).end()
#define pb push_back
#define szz(x) (int)(x).size()
#define rep(i, n) for(int i=0;i<(n);i++)
typedef tuple<int, int, int> t3;

using BigInt = __int128;

const BigInt mod = BigInt(6000000000000000983);
using lint = BigInt;

lint mul(lint x, lint y, lint mod){ return x * y % mod; }
lint ipow(lint x, lint y){
	lint ret = 1, piv = x % mod;
	while(y > 0){
		if(y % 2) ret = mul(ret, piv, mod);
		piv = mul(piv, piv, mod);
		y /= 2;
	}
	return ret;
}

vector<BigInt> berlekamp_massey(vector<BigInt> x){
	vector<BigInt> ls, cur;
	BigInt ld;
	int lf;
	for(int i=0; i<x.size(); i++){
		lint t = 0;
		for(int j=0; j<cur.size(); j++){
			t = (t + x[i-j-1] * cur[j]) % mod;
		}
		if((t - x[i]) % mod == 0) continue;
		if(cur.empty()){
			cur.resize(i+1);
			lf = i;
			ld = (t - x[i]) % mod;
			continue;
		}
		lint k = -(x[i] - t) * ipow(ld, mod - 2) % mod;
		vector<lint> c(i-lf-1, lint(0));
		c.push_back(k);
		for(auto &j : ls) c.push_back(-j * k % mod);
		if(c.size() < cur.size()) c.resize(cur.size());
		for(int j=0; j<cur.size(); j++){
			c[j] = (c[j] + cur[j]) % mod;
		}
		if(i-lf+(int)ls.size()>=(int)cur.size()){
			tie(ls, lf, ld) = make_tuple(cur, i, (t - x[i]) % mod);
		}
		cur = c;
	}
	for(auto &i : cur) i = (i % mod + mod) % mod;
	return cur;
}
lint get_nth(vector<lint> rec, vector<lint> dp, lint n){
	int m = rec.size();
	vector<lint> s(m), t(m);
	s[0] = 1;
	if(m != 1) t[1] = 1;
	else t[0] = rec[0];
	auto mul = [&rec](vector<lint> v, vector<lint> w){
		int m = v.size();
		vector<lint> t(2 * m);
		for(int j=0; j<m; j++){
			for(int k=0; k<m; k++){
				t[j+k] = t[j+k] + v[j] * w[k] % mod;
				if(t[j+k] >= mod) t[j+k] -= mod;
			}
		}
		for(int j=2*m-1; j>=m; j--){
			for(int k=1; k<=m; k++){
				t[j-k] += t[j] * rec[k-1] % mod;
				if(t[j-k] >= mod) t[j-k] -= mod;
			}
		}
		t.resize(m);
		return t;
	};
	while(n > 0){
		if(n % 2) s = mul(s, t);
		t = mul(t, t);
		n /= 2;
	}
	lint ret = 0;
	for(int i=0; i<m; i++) ret += s[i] * dp[i] % mod;
	return ret % mod;
}
lint guess_nth_term(vector<lint> x, ll n){
	if(n < x.size()) return x[n];
	vector<lint> v = berlekamp_massey(x);
	if(v.empty()) return 0;
	return get_nth(v, x, n);
}

int N;
ll A, B;
int L[55], R[55];
ll dp[220020][55], dps[220020];
const ll INF = 2e18;

void solve() {
	scanf("%d%lld%lld", &N, &A, &B);
	for(int i=1;i<=N;i++) scanf("%d", L + i);
	for(int i=1;i<=N;i++) scanf("%d", R + i);
	if(A != 1) return;
	memset(dp, 0, sizeof dp);
	dp[0][1] = 1;
	auto add = [&](ll &a, ll b) {
		a += b;
		if(a > INF) a = INF;
	};
	const int H = 220000;
	for(int i=1;i<=H;i++) {
		for(int j=1;j<=N;j++) {
			add(dp[i][L[j]], dp[i-1][j]);
			add(dp[i][R[j]], dp[i-1][j]);
		}
	}
	for(int i=0;i<=H;i++) {
		dps[i] = (i ? dps[i - 1] : 0);
		for(int j=0;j<=N;j++) add(dps[i], dp[i][j]);
		if(dps[i] >= B) {
			printf("%d\n", i);
			return;
		}
	}
	vector <BigInt> w;
	rep(i, 300) w.push_back(BigInt(dps[i]));
	auto xx = berlekamp_massey(w);
	ll x = H;
	while(get_nth(xx, w, x) <= B) {
		x = x * 1.2;
	}
	ll low = 1, high = x, res = 0;
	while(low <= high) {
		ll mid = (low + high) >> 1;
		if(get_nth(xx, w, mid) >= B) {
			res = mid;
			high = mid - 1;
		}
		else {
			low = mid + 1;
		}
	}
	printf("%lld\n", res);
}

int main() {
	int T; scanf("%d", &T);
	for(int t = 1; t <= T; t++) {
		printf("Case #%d: ", t);
		solve();
	}
	return 0;
}
/*
1 5 1 1000000000000000
0 3 4 2 0
2 0 0 5 0
6000000000000000983
6000000000000000989
 */