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

char S[100010];
int N, D;
int dv[1010][1010], dp[1010][2];
const int mod = 1e9 + 7;

void solve() {
	scanf("%s", S + 1);
	N = (int)strlen(S + 1);
	scanf("%d", &D);
	if(N > 1000) return;
	for(int i=1;i<=N;i++) {
		dv[i][i] = (S[i] - '0') % D;
		for(int j=i+1;j<=N;j++) {
			dv[i][j] = (dv[i][j-1] * 10 + S[j] - '0') % D;
		}
	}
	auto add = [&](int &a, int b) { a = (a + b) % mod; };
	memset(dp, 0, sizeof dp);
	dp[0][0] = 1;
	for(int i=1;i<=N;i++) {
		for(int j=i;j;j--) {
			int c = dv[j][i] != 0;
			add(dp[i][c], dp[j-1][0]);
			if(c == 0) add(dp[i][c], dp[j-1][1]);
		}
	}
	int ans = dp[N][0];
	add(ans, dp[N][1]);
	printf("%d\n", ans);
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
 */