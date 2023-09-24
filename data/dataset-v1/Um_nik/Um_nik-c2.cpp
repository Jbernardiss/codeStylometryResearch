#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <algorithm>
#include <cmath>
#include <vector>
#include <set>
#include <map>
#include <unordered_set>
#include <unordered_map>
#include <queue>
#include <ctime>
#include <cassert>
#include <complex>
#include <string>
#include <cstring>
#include <chrono>
#include <random>
#include <bitset>
#include <array>
using namespace std;

#ifdef LOCAL
	#define eprintf(...) {fprintf(stderr, __VA_ARGS__);fflush(stderr);}
#else
	#define eprintf(...) 42
#endif

using ll = long long;
using ld = long double;
using uint = unsigned int;
using ull = unsigned long long;
template<typename T>
using pair2 = pair<T, T>;
using pii = pair<int, int>;
using pli = pair<ll, int>;
using pll = pair<ll, ll>;
mt19937_64 rng(chrono::steady_clock::now().time_since_epoch().count());
ll myRand(ll B) {
	return (ull)rng() % B;
}

#define pb push_back
#define mp make_pair
#define all(x) (x).begin(),(x).end()
#define fi first
#define se second

clock_t startTime;
double getCurrentTime() {
	return (double)(clock() - startTime) / CLOCKS_PER_SEC;
}


const ll INF = (ll)1e18;
const ll C = (ll)1e15;

struct Dinic {
	struct Edge {
		int v, to;
		ll cap;

		Edge() : v(), to(), cap() {}
		Edge (int _v, int _to, ll _cap) : v(_v), to(_to), cap(_cap) {}
	};
	vector<Edge> ed;
	vector<vector<int>> g;
	int S, T;
	int n;
	vector<int> dist;
	vector<int> idx;

	Dinic() : ed(), g(), S(), T() {}
	Dinic(int _n, int _S, int _T) {
		n = _n;
		S = _S;
		T = _T;
		g.resize(n);
		for (int i = 0; i < n; i++)
			g[i].clear();
		ed = vector<Edge>();
	}

	void addEdge(int v, int to, ll cap) {
		g[v].push_back((int)ed.size());
		ed.push_back(Edge(v, to, cap));
		g[to].push_back((int)ed.size());
		ed.push_back(Edge(to, v, 0));
	}

	bool BFS() {
		dist.resize(n);
		vector<int> q;
		for (int i = 0; i < n; i++)
			dist[i] = n;
		q.push_back(S);
		dist[S] = 0;
		for (int i = 0; i < (int)q.size(); i++) {
			int v = q[i];
			for (int id : g[v]) {
				Edge e = ed[id];
				if (e.cap <= 0) continue;
				int u = e.to;
				if (dist[u] <= dist[v] + 1) continue;
				dist[u] = dist[v] + 1;
				q.push_back(u);
			}
		}
		return dist[T] < n;
	}

	ll dfs(int v, ll flow) {
		if (v == T || flow == 0) return flow;
		ll res = 0;
		for (int &i = idx[v]; i < (int)g[v].size(); i++) {
			int id = g[v][i];
			Edge e = ed[id];
			int to = e.to;
			if (dist[to] != dist[v] + 1) continue;
			ll df = dfs(to, min(flow, e.cap));
			flow -= df;
			res += df;
			ed[id].cap -= df;
			ed[id ^ 1].cap += df;
			if (flow == 0) return res;
		}
		return res;
	}

	ll Flow() {
		idx.resize(n);
		ll res = 0;
		while(BFS()) {
			for (int i = 0; i < n; i++)
				idx[i] = 0;
			res += dfs(S, INF);
		}
		return res;
	}
} G;

const int SZ = (int)1e6 + 77;
const int N = 203;
vector<int> g[N];
int d[N][2];
int n, m;
int ord[SZ];

void dfs(int v) {
	while(!g[v].empty()) {
		int u = g[v].back();
		g[v].pop_back();
		dfs(u);
	}
	ord[m++] = v;
}

void solve() {
	scanf("%d%d", &n, &m);
	int s = 2 * n, t = 2 * n + 1;
	G = Dinic(2 * n + 2, s, t);
	for (int i = 0; i < n; i++) {
		d[i][0] = d[i][1] = m;
	}
	for (int i = 0; i < m; i++) {
		int v, u;
		scanf("%d%d", &v, &u);
		v--;u--;
		d[v][0]--;
		d[u][1]--;
		//G.addEdge(s2, 2 * u + 1, 1);
		//G.addEdge(2 * v, t2, 1);
		G.addEdge(2 * v, 2 * u + 1, C);
	}
	for (int i = 0; i < n; i++) {
		G.addEdge(s, 2 * i, d[i][0]);
		G.addEdge(2 * i + 1, t, d[i][1]);
	}
	if (G.Flow() != (n - 1) * m) {
		printf("IMPOSSIBLE\n");
		return;
	}
	for (int i = 0; i < n; i++)
		g[i].clear();
	for (int i = 0; i < (int)G.ed.size(); i += 2) {
		int v = G.ed[i].v, u = G.ed[i].to;
		if (v >= 2 * n || u >= 2 * n) continue;
		int w = C - G.ed[i].cap + 1;
		v /= 2;
		u /= 2;
		//eprintf("edge %d %d %d\n", v, u, w);
		while(w--) g[v].push_back(u);
	}
	int want = n * m + 1;
	m = 0;
	dfs(0);
	/*
	for (int i = 0; i < m; i++)
		eprintf("%d ", ord[i]);
	eprintf("\n");
	*/
	//printf("want = %d, m = %d\n", want, m);
	if (m != want) {
		printf("IMPOSSIBLE\n");
		return;
	}
	reverse(ord, ord + m);
	printf("%d\n", m);
	for (int i = 0; i < m; i++)
		printf("%d ", ord[i] + 1);
	printf("\n");
}

int main()
{
	startTime = clock();
//	freopen("input.txt", "r", stdin);
//	freopen("output.txt", "w", stdout);

	int t;
	scanf("%d", &t);
	for (int i = 1; i <= t; i++) {
		printf("Case #%d: ", i);
		solve();
	}

	return 0;
}
