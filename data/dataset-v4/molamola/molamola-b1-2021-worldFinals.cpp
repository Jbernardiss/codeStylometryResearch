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

mt19937 rng(0x86201);
using ull = unsigned long long;

ull val[30030];

int B, S, N;
ull edge[300030];
map <ull, int> MX;
vector <ull> dw[30030];

void solve() {
	scanf("%d%d%d", &B, &S, &N);
	for(int i=1;i<=B;i++) {
		val[i] = uniform_int_distribution<ull>(0, ULLONG_MAX)(rng);
	}
	ull OUT = 998244354;
	MX.clear();
	for(int i=1;i<=S;i++) {
		int x, y;
		scanf("%d%d", &x, &y);
		edge[i] = OUT * val[x] - val[y];
		MX[edge[i]] = i;
	}
	ull expt = 0;
	for(int i=1;i<=B;i++) expt += (OUT - 1) * val[i];
	for(int i=1;i<=S;i++) {
		int m = S / i;
		dw[i].resize(m + 1);
		dw[i][0] = 0;
		for(int j=1;j<=m;j++) {
			dw[i][j] = dw[i][j-1] + edge[i * j];
		}
	}
	ull v = 0;
	int cnt = 0;
	for(int i=1;i<=N;i++) {
		int l, r, m;
		char ch;
		scanf(" %c%d%d%d", &ch, &l, &r, &m);
		int mu = (ch == 'E' ? 1 : -1);
		l = (l + m - 1) / m;
		r = r / m;
		if(l <= r) {
			v += mu * (dw[m][r] - dw[m][l - 1]);
			cnt += mu * (r - l + 1);
		}
		ull w = expt - v;
		if(cnt != B - 1 || MX.find(w) == MX.end()) printf("X ");
		else printf("%d ", MX[w]);
	} puts("");
}

int main() {
	int T; scanf("%d", &T);
	for(int t = 1; t <= T; t++) {
		printf("Case #%d: ", t);
		solve();
	}
	return 0;
}
