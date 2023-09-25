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

const int N = 1 << 19;
const int NN = N + 5;

struct Node {
	int l, r;
	pii val;
	int toAdd;

	Node() : l(), r(), val(mp(-1, 0)), toAdd(0) {}
	Node(int _l, int _r) : l(_l), r(_r), val(mp(0, _r - _l)), toAdd(0) {}

	void add(int x) {
		toAdd += x;
		val.first += x;
	}
};
Node tree[2 * N + 5];
void build() {
	for (int i = 0; i < N; i++)
		tree[N + i] = Node(i, i + 1);
	for (int i = N - 1; i > 0; i--)
		tree[i] = Node(tree[2 * i].l, tree[2 * i + 1].r);
}
void push(int v) {
	assert(v < N);
	if (tree[v].toAdd == 0) return;
	for (int u = 2 * v; u < 2 * v + 2; u++)
		tree[u].add(tree[v].toAdd);
	tree[v].toAdd = 0;
}
pii merge(pii v, pii u) {
	if (v.first != u.first) return max(v, u);
	return mp(v.first, v.second + u.second);
}
void update(int v) {
	assert(v < N);
	tree[v].val = merge(tree[2 * v].val, tree[2 * v + 1].val);
}

void addOnSegm(int v, int l, int r, int x) {
	if (l <= tree[v].l && tree[v].r <= r) {
		tree[v].add(x);
		return;
	}
	if (l >= tree[v].r || tree[v].l >= r) return;
	push(v);
	for (int u = 2 * v; u < 2 * v + 2; u++)
		addOnSegm(u, l, r, x);
	update(v);
}
pii getSegm(int v, int l, int r) {
	if (l <= tree[v].l && tree[v].r <= r) return tree[v].val;
	if (l >= tree[v].r || tree[v].l >= r) return mp(-1, 0);
	push(v);
	return merge(getSegm(2 * v, l, r), getSegm(2 * v + 1, l, r));
}

int n, m;
int a[NN];
int b[NN][2];
vector<int> pos[NN];
int ptr[NN];

void addOne(int c, int l, int r, int x) {
	l = min(l, (int)pos[c].size() - 1);
	r = min(r, (int)pos[c].size() - 1);
	if (l >= r) return;
	l = pos[c][l] + 1;
	r = pos[c][r] + 1;
	//eprintf("addSegm %d %d %d\n", l, r, x);
	addOnSegm(1, l, r, x);
}
void addCol(int c, int x) {
	addOne(c, ptr[c], ptr[c] + 1, x);
	addOne(c, ptr[c] + b[c][0], ptr[c] + b[c][1] + 1, x);
}
ll solve() {
	//eprintf("SOLVE\n");
	scanf("%d%d", &n, &m);
	for (int i = 0; i < m; i++) {
		scanf("%d%d", &b[i][0], &b[i][1]);
		if (b[i][0] == 0) b[i][0]++;
		pos[i].clear();
		pos[i].push_back(-1);
	}
	for (int i = 0; i < n; i++) {
		scanf("%d", &a[i]);
		a[i]--;
	}
	for (int i = 0; i < n; i++)
		a[n + i] = a[i];
	for (int i = 0; i < 2 * n; i++)
		pos[a[i]].push_back(i);
	build();
	for (int i = 0; i < m; i++) {
		pos[i].push_back(2 * n);
		ptr[i] = 0;
		addCol(i, 1);
	}
	ll ans = 0;
	for (int l = 0; l < n; l++) {
		//eprintf("l = %d\n", l);
		pii cur = getSegm(1, l + 2, l + n);
		//eprintf("cur = (%d %d)\n", cur.first, cur.second);
		if (cur.first == m) ans += cur.second;
		addCol(a[l], -1);
		ptr[a[l]]++;
		addCol(a[l], 1);
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
		printf("Case #%d: %lld\n", i, solve());
	}

	return 0;
}
