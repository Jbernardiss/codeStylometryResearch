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

const int N = 200100;
int n, m, q;
vector<int> g[N];
bool rat[N];
ll xx[N], yy[N], tt[N];
int auth[N];
vector<int> rg[N];
int col[N];
int ord[N];
int sz;
bool used[N];
int colSz[N];

struct Item {
	ll t, x, y;
	int id;

	Item() : t(), x(), y(), id() {}
	Item(ll _t, ll _x, ll _y, int _id) : t(_t), x(_x), y(_y), id(_id) {}

	bool operator < (const Item &I) const {
		if (t != I.t) return t < I.t;
		return id < I.id;
	}
};
set<Item> items[N];

bool plausibleRat(ll x, ll y, ll t) {
	int p = lower_bound(tt, tt + m, t) - tt;
	if (p < m) {
		ll dx = x - xx[p], dy = y - yy[p], dt = t - tt[p];
		if (dx * dx + dy * dy > dt * dt)
			return false;
	}
	if (p > 0) {
		p--;
		ll dx = x - xx[p], dy = y - yy[p], dt = t - tt[p];
		if (dx * dx + dy * dy > dt * dt)
			return false;
	}
	return true;
}

bool plausiblePair(Item A, Item B) {
	ll dx = A.x - B.x, dy = A.y - B.y, dt = A.t - B.t;
	return dx * dx + dy * dy <= dt * dt;
}
void addItem(int v, ll t, ll x, ll y, int id) {
	Item I = Item(t, x, y, id);
	while(true) {
		auto it = items[v].lower_bound(I);
		if (it == items[v].end()) break;
		if (plausiblePair(I, *it)) break;
		rat[auth[it->id]] = 1;
		items[v].erase(it);
	}
	while(true) {
		auto it = items[v].lower_bound(I);
		if (it == items[v].begin()) break;
		it--;
		if (plausiblePair(I, *it)) break;
		rat[auth[it->id]] = 1;
		items[v].erase(it);
	}
	items[v].insert(I);
}

void markRat(int v) {
	rat[v] = 1;
	for (int u : g[v])
		if (!rat[u])
			markRat(u);
}

void dfsOrd(int v) {
	used[v] = 1;
	for (int u : g[v])
		if (!used[u])
			dfsOrd(u);
	ord[sz++] = v;
}
void dfsCol(int v) {
	col[v] = m;
	for (int u : rg[v])
		if (col[u] == -1)
			dfsCol(u);
}

int solve() {
	scanf("%d%d%d", &n, &m, &q);
	for (int i = 0; i < n; i++) {
		g[i].clear();
		rat[i] = false;
		items[i].clear();
	}
	for (int i = 0; i < m; i++) {
		scanf("%lld%lld%lld", &xx[i], &yy[i], &tt[i]);
	}
	for (int i = 0; i < q; i++) {
		int v, u;
		ll x, y, t;
		scanf("%d%d%lld%lld%lld", &v, &u, &x, &y, &t);
		v--;u--;
		if (!plausibleRat(x, y, t))
			g[u].push_back(v);
		auth[i] = v;
		addItem(v, t, x, y, i);
		addItem(u, t, x, y, i);
	}
	bool fnd = false;
	for (int i = 0; i < n; i++) {
		if (!rat[i]) continue;
		markRat(i);
		fnd = true;
	}
	if (fnd) {
		int res = 0;
		for (int i = 0; i < n; i++)
			res += (int)rat[i];
		return res;
	}
	for (int v = 0; v < n; v++)
		rg[v].clear();
	for (int v = 0; v < n; v++)
		for (int u : g[v])
			rg[u].push_back(v);
	for (int v = 0; v < n; v++) {
		col[v] = -1;
		used[v] = 0;
	}
	sz = 0;
	for (int v = 0; v < n; v++) if (!used[v])
		dfsOrd(v);
	m = 0;
	reverse(ord, ord + sz);
	for (int i = 0; i < sz; i++) {
		int v = ord[i];
		if (col[v] != -1) continue;
		dfsCol(v);
		m++;
	}
	for (int i = 0; i < m; i++)
		colSz[i] = 0;
	for (int v = 0; v < n; v++)
		colSz[col[v]]++;
	for (int v = 0; v < n; v++)
		for (int u : g[v])
			if (col[u] != col[v])
				colSz[col[v]] = -1;
	int res = n;
	for (int i = 0; i < m; i++)
		if (colSz[i] != -1)
			res = min(res, colSz[i]);
	return res;
}

int main()
{
	startTime = clock();
//	freopen("input.txt", "r", stdin);
//	freopen("output.txt", "w", stdout);

	int t;
	scanf("%d", &t);
	for (int i = 1; i <= t; i++) {
		printf("Case #%d: %d\n", i, solve());
	}

	return 0;
}
