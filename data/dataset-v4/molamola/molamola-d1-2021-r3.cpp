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

const ll mod = 1e9 + 7;
int N, M, L, A[100];
ll C[120][120];

void solve() {
	scanf("%d%d%d", &N, &M, &L);
	rep(i, 1<<L) scanf("%d", A + i);
	if(N > 8) return;
	int perm[10] = {};
	for(int i=1;i<=N;i++) perm[i] = i;
	ll ans = 0;
	int dp[6][32];
	auto Get = [&](int c, int x) {
		if(x < 0) return 0ll;
		return C[c+x-1][c];
	};
	do {
		rep(i, 1<<L) dp[0][i] = perm[A[i]];
		for(int x=1;x<=L;x++) {
			for(int i=0;i<1<<L;i+=(1<<x)) {
				int j = i + (1<<(x-1));
				if((L-x) % 2 == 0) dp[x][i] = max(dp[x-1][i], dp[x-1][j]);
				else dp[x][i] = min(dp[x-1][i], dp[x-1][j]);
			}
		}
		int v = dp[L][0];
		int rp[10];
		for(int i=1;i<=N;i++) rp[perm[i]] = i;
		int xl = 0, xr = 0;
		for(int i=1;i<N;i++) if(rp[i + 1] > rp[i]) {
			if(i+1 <= v) ++xl;
			else ++xr;
		}
		for(int x=1;x<=M;x++) {
			ll vl = Get(v - 1, x - xl);
			ll vr = Get(N - v, M - (x - 1) - xr);
			ans = (ans + vl * vr % mod * x) % mod;
		}
	} while(next_permutation(perm + 1, perm + 1 + N));
	printf("%lld\n", ans);
}

int main() {
	rep(i, 120) {
		C[i][0] = 1;
		for(int j=1;j<=i;j++) C[i][j] = (C[i-1][j-1] + C[i-1][j]) % mod;
	}
	int TC = 1; scanf("%d", &TC);
	for(int t = 1; t <= TC; t++) {
		printf("Case #%d: ", t);
		solve();
	}
	return 0;
}
