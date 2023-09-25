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

const int INF = (int)1e8;
const int N = 200200;
int n, m;
vector<int> g[N];
int h[N], minH[N];
int ed[N][2];
bool isBridge[N];
bool isSafe[N];
int d[N], dist[N];
int q[N];
int topQ;

int getOther(int id, int v) {
	return ed[id][0] ^ ed[id][1] ^ v;
}

void dfs(int v, int p) {
	//eprintf("dfs %d\n", v);
	minH[v] = h[v];
	for (int id : g[v]) if (id != p) {
		int u = getOther(id, v);
		if (h[u] == -1) {
			h[u] = h[v] + 1;
			dfs(u, id);
			minH[v] = min(minH[v], minH[u]);
			if (minH[u] > h[v]) isBridge[id] = 1;
		} else {
			minH[v] = min(minH[v], h[u]);
		}
	}
}

int solve() {
	int s, t;
	scanf("%d%d%d%d", &n, &m, &s, &t);
	s--;t--;
	for (int i = 0; i < n; i++)
		g[i].clear();
	for (int i = 0; i < m; i++) {
		isBridge[i] = 0;
		for (int j = 0; j < 2; j++) {
			scanf("%d", &ed[i][j]);
			ed[i][j]--;
			g[ed[i][j]].push_back(i);
		}
	}
	for (int v = 0; v < n; v++) {
		h[v] = -1;
		isSafe[v] = 0;
	}
	for (int v = 0; v < n; v++) {
		if (h[v] != -1) continue;
		h[v] = 0;
		dfs(v, -1);
	}
	for (int v = 0; v < n; v++) {
		isSafe[v] = false;
		for (int id : g[v])
			isSafe[v] |= !isBridge[id];
	}
	for (int v = 0; v < n; v++)
		dist[v] = INF;
	dist[t] = 0;
	topQ = 0;
	q[topQ++] = t;
	for (int i = 0; i < topQ; i++) {
		int v = q[i];
		for (int id : g[v]) {
			int u = getOther(id, v);
			if (dist[u] <= dist[v] + 1) continue;
			dist[u] = dist[v] + 1;
			q[topQ++] = u;
		}
	}
	for (int v = 0; v < n; v++) {
		d[v] = dist[v];
		dist[v] = INF;
	}
	dist[s] = 0;
	topQ = 0;
	q[topQ++] = s;
	int ans = 0;
	for (int i = 0; i < topQ; i++) {
		int v = q[i];
		ans = max(ans, d[v]);
		if (dist[v] == d[v]) continue;
		if (isSafe[v]) ans = INF;
		for (int id : g[v]) {
			int u = getOther(id, v);
			if (dist[u] <= dist[v] + 1) continue;
			if (d[u] < dist[v] + 1) continue;
			dist[u] = dist[v] + 1;
			q[topQ++] = u;
		}
	}
	return ans;
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
		int ans = solve();
		if (ans == INF)
			printf("SAFE\n");
		else
			printf("%d\n", ans * 2);
	}

	return 0;
}
