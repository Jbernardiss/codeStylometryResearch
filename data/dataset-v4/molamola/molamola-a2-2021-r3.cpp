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

char In[44];
ll dp[4000040];

void solve() {
	scanf("%s", In);
	int n = (int)strlen(In);
	int cnt[10] = {};
	for(int i=0;In[i];i++) cnt[In[i] - '0'] += 1;
	if(n % 2 == 1) {
		ll ans = 9e18;
		for(int i=1;i<10;i++) {
			if(cnt[i] == 0) continue;
			for(int j=1;j<10;j++) {
				int rcnt[10];
				rep(k, 10) rcnt[k] = cnt[k];
				--rcnt[i];
				--rcnt[j];
				if(rcnt[i] >= 0 && rcnt[j] >= 0) {
					for(int k=0;k<10;k++) {
						if(rcnt[k] == 0) continue;
						--rcnt[k];
						vector <int> vv;
						rep(a, 10) rep(b, rcnt[a]) vv.pb(a);
						int m = n / 2 - 1;
						ll s1 = 10 * i + k, s2 = j;
						for(int x=0;x<m;x++) { s2 = s2 * 10 + vv.back(); vv.pop_back(); }
						for(int x=0;x<m;x++) { s1 = s1 * 10 + vv[x]; }
						ans = min(ans, s1 - s2);
						++rcnt[k];
					}
				}
			}
		}
		printf("%lld\n", ans);
		return;
	}
	for(int i=1;i<10;i++) while(cnt[i] > 3) cnt[i] -= 2;
	int tt = 1;
	rep(i, 10) tt *= (1 + cnt[i]);
	auto trans = [&](int a[]) {
		int v = 0;
		for(int i=0;i<10;i++) v = v * (cnt[i] + 1) + a[i];
		return v;
	};
	auto rv = [&](int x, int a[]) {
		for(int i=9;i>=0;i--) {
			a[i] = x % (cnt[i] + 1);
			x /= (cnt[i] + 1);
		}
	};
	auto upd = [&](int x, ll v) {
		if(dp[x] == -1 || dp[x] > v) dp[x] = v;
	};
	rep(i, tt + 1) dp[i] = -1;
	for(int i=1;i<10;i++) {
		if(cnt[i] == 0) continue;
		for(int j=1;j<10;j++) {
			int rcnt[10];
			rep(k, 10) rcnt[k] = cnt[k];
			--rcnt[i];
			--rcnt[j];
			if(rcnt[i] >= 0 && rcnt[j] >= 0) {
				upd(trans(rcnt), abs(i - j));
			}
		}
	}
	for(int i=tt;i>=0;i--) {
		if(dp[i] == -1) continue;
		int rr[10];
		rv(i, rr);
		for(int a=0;a<10;a++) {
			if(rr[a] == 0) continue;
			int trr[10];
			rep(k, 10) trr[k] = rr[k];
			trr[a]--;
			rep(b, a+1) {
				if(trr[b] == 0) continue;
				int urr[10];
				rep(k, 10) urr[k] = trr[k];
				--urr[b];
				int tg = trans(urr);
				if(dp[i] == 0) {
					upd(tg, abs(a - b));
				}
				else {
					upd(tg, 10 * dp[i] + b - a);
				}
			}
		}
	}
	printf("%lld\n", dp[0]);
}

int main() {
	int TC = 1; scanf("%d", &TC);
	for(int t = 1; t <= TC; t++) {
		printf("Case #%d: ", t);
		solve();
	}
	return 0;
}
