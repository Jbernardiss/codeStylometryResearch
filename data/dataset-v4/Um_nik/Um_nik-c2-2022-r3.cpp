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

const int N = 100100;
int a[N][2];
vector<int> g[N];
int deg[N];
set<pii> setik;
int n;
char let[] = "ACDEHIJKMORST";
int c[N];
int q[N];
char s[N];

void addEdge(int v, int u) {
	g[v].push_back(u);
	g[u].push_back(v);
}
void solve() {
	scanf("%d", &n);
	for (int j = 0; j < 2; j++)
		for (int i = 0; i < n; i++) {
			scanf("%d", &a[i][j]);
			a[i][j]--;
		}
	for (int i = 0; i < n; i++)
		g[i].clear();
	for (int v = 0; v < n; v++) {
		for (int i = 0; i < 2; i++) {
			int u = a[v][i];
			if (v == u) {
				printf("IMPOSSIBLE\n");
				return;
			}
			addEdge(v, u);
			for (int j = 0; j < 2; j++) {
				int w = a[u][j];
				if (v == w) {
					printf("IMPOSSIBLE\n");
					return;
				}
				addEdge(v, w);
			}
		}
	}
	setik.clear();
	for (int v = 0; v < n; v++) {
		deg[v] = (int)g[v].size();
		setik.insert(mp(deg[v], v));
	}
	int m = 0;
	while(!setik.empty()) {
		int v = setik.begin()->second;
		setik.erase(setik.begin());
		q[m++] = v;
		deg[v] = -1;
		for (int u : g[v]) {
			if (deg[u] == -1) continue;
			setik.erase(mp(deg[u], u));
			deg[u]--;
			setik.insert(mp(deg[u], u));
		}
	}
	for (int i = 0; i < n; i++)
		c[i] = -1;
	for (int i = n - 1; i >= 0; i--) {
		int v = q[i];
		int mask = 0;
		for (int u : g[v])
			if (c[u] != -1)
				mask |= 1 << c[u];
		c[v] = 0;
		while((mask >> c[v]) & 1) c[v]++;
		assert(c[v] < 13);
	}
	for (int i = 0; i < n; i++)
		s[i] = let[c[i]];
	s[n] = '\0';
	printf("%s\n", s);
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
