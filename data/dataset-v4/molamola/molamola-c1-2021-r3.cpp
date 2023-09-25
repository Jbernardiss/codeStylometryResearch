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

pll operator-(pll a, pll b) { return {a.Fi - b.Fi, a.Se - b.Se}; }
ll operator/(pll a, pll b) { return a.Fi * b.Se - a.Se * b.Fi; }
ll operator*(pll a, pll b) { return a.Fi * b.Fi + a.Se * b.Se; }

int N;
pll P[100010];
int sgn(ll x) { return (x > 0) - (x < 0); }

int meet(pll a, pll b, pll c, pll d) {
	if(sgn((b-a)/(c-a)) * sgn((b-a)/(d-a)) != -1) return 0;
	if(sgn((d-c)/(a-c)) * sgn((d-c)/(b-c)) != -1) return 0;
	return 1;
}

void solve() {
	scanf("%d", &N);
	for(int i=1;i<=N;i++) {
		ll x, y;
		scanf("%lld%lld", &x, &y);
		P[i] = {x, y};
	}
	set <pii> ans;
	vector <pii> opt;
	rep(a, 2) {
		int x, y;
		scanf("%d%d", &x, &y);
		if(x > y) swap(x, y);
		ans.insert({x, y});
	}
	while(1) {
		int can_insert = 0;
		vector <pii> vv;
		for(pii e : ans) vv.pb(e);
		for(int i=1;i<=N && !can_insert;i++) for(int j=1;j<i;j++) {
			if(ans.find(pii(j, i)) != ans.end()) continue;
			int can = 1;
			for(auto [k, u] : vv) {
				if(meet(P[i], P[j], P[k], P[u])) {
					can = 0;
					break;
				}
			}
			if(can) {
				can_insert = 1;
				ans.insert(pii(j, i));
				opt.pb({j, i});
				break;
			}
		}
		if(can_insert == 0) break;
	}
	printf("%d\n", szz(opt));
	for(auto [x, y] : opt) {
		printf("%d %d\n", x, y);
	}
}

int main() {
	int TC = 1; scanf("%d", &TC);
	for(int t = 1; t <= TC; t++) {
		printf("Case #%d: ", t);
		solve();
	}
	return 0;
}
