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

namespace MaxFlow{
	const int MV = 220;
	const int ME = 40040;
	const int INF = 1e9;
	int dis[MV];
	int st[MV], en[ME<<1], nxt[ME<<1], flow[ME<<1], ce;
	int start[MV];
	void init() {
		memset(st, 0, sizeof st);
		ce = 1;
	}
	void addE(int s, int e, int f = 1) {
		++ce; nxt[ce] = st[s]; st[s] = ce; en[ce] = e; flow[ce] = f;
		++ce; nxt[ce] = st[e]; st[e] = ce; en[ce] = s; flow[ce] = 0;
	}
	int que[MV];
	int bfs(int N, int S, int E) {
		for(int i=1;i<=N;i++) dis[i] = -1;
		dis[S] = 0;
		int *fr = que, *re = que;
		*fr++ = S;
		while(fr != re) {
			int t = *re++;
			for(int i=st[t];i;i=nxt[i]) if(flow[i] > 0 && dis[en[i]] == -1) {
					dis[en[i]] = dis[t] + 1;
					*fr++ = en[i];
				}
		}
		return dis[E] != -1;
	}

	int dfs(int x, int E, int f) {
		if(x == E) return f;
		for(int &i=start[x],t;i;i=nxt[i]) if(flow[i] > 0 && dis[en[i]] == dis[x] + 1 && (t = dfs(en[i], E, min(f, flow[i]))) > 0){
				flow[i] -= t;
				flow[i^1] += t;
				return t;
			}
		return 0;
	}

	int Get(int N, int S, int E) {
		int res = 0;
		while(bfs(N, S, E)) {
			for(int i=1;i<=N;i++) start[i] = st[i];
			while(1) {
				int t = dfs(S, E, INF);
				if(t == 0) break;
				res += t;
			}
		}
		return res;
	}

	void trace(int N, int S, int E, int chk[]) {
		bfs(N, S, E);
		for(int i=1;i<=N;i++) chk[i] = (dis[i] != -1);
	}
}

int n, m;
int a[22], b[22];

void solve() {
	scanf("%d%d", &n, &m);
	for(int i=1;i<=n;i++) scanf("%d", a + i);
	for(int i=1;i<=m;i++) scanf("%d", b + i);
	int s = 0;
	for(int i=1;i<=n;i++) s += a[i];
	for(int i=1;i<=m;i++) s -= b[i];
	if(s != 0) {
		puts("IMPOSSIBLE");
		return;
	}
	MaxFlow::init();
	int ST = n + m + 1, EN = ST + 1;
	int rest = 0;
	for(int i=1;i<=n;i++) rest += a[i];
	for(int k=1;k<=n;k++) MaxFlow::addE(ST, k, a[k]);
	for(int k=1;k<=m;k++) MaxFlow::addE(n + k, EN, b[k]);
	for(int k=1;k<=n;k++) for(int u=1;u<=m;u++) MaxFlow::addE(k, n + u);
	if(rest != MaxFlow::Get(EN, ST, EN)) {
		puts("IMPOSSIBLE");
		return;
	}

	puts("POSSIBLE");
	char ans[22][22] = {};
	for(int i=1;i<=n;i++) {
		for(int j=1;j<=m;j++) {
			ans[i][j] = '\\';
			MaxFlow::init();
			ST = n + m + 1, EN = ST + 1;
			for(int k=1;k<=n;k++) for(int u=1;u<=m;u++) {
				if(ans[k][u] == 0) {
					MaxFlow::addE(k, n + u);
				}
			}
			for(int k=1;k<=n;k++) MaxFlow::addE(ST, k, a[k]);
			for(int k=1;k<=m;k++) MaxFlow::addE(n + k, EN, b[k]);
			if(rest != MaxFlow::Get(EN, ST, EN)) {
				ans[i][j] = '/';
				--a[i];
				--b[j];
				--rest;
			}
		}
	}
	for(int i=1;i<=n;i++) printf("%s\n", ans[i] + 1);
}

int main() {
	int TC = 1; scanf("%d", &TC);
	for(int t = 1; t <= TC; t++) {
		printf("Case #%d: ", t);
		solve();
	}
	return 0;
}
