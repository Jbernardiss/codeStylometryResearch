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

int n, Q;
const int N = 105;
int a[N];
int c[N];

void read() {
#ifndef LOCAL
	for (int i = 0; i < n; i++) {
		scanf("%d", &a[i]);
		a[i]--;
	}
#endif
}
int query() {
	Q--;
#ifdef LOCAL
	map<int, vector<int>> mm;
	for (int i = 0; i < n; i++)
		mm[c[i]].push_back(i);
	vector<int> nw(n);
	for (auto t : mm) {
		vector<int> aa = t.second;
		vector<int> bb = aa;
		shuffle(all(bb), rng);
		for (int i = 0; i < (int)aa.size(); i++) {
			nw[bb[i]] = a[aa[i]];
		}
	}
	bool ok = true;
	for (int i = 0; i < n; i++) {
		a[i] = nw[i];
		ok &= a[i] == i;
	}
	return (int)ok;
#endif
	for (int i = 0; i < n; i++)
		printf("%d ", c[i]);
	printf("\n");
	fflush(stdout);
	int x;
	scanf("%d", &x);
	return (int)(x == 1);
}

void solve() {
#ifdef LOCAL
	for (int i = 0; i < n; i++)
		a[i] = i;
	while(true) {
		bool ok = false;
		for (int i = 0; i < n; i++)
			ok |= a[i] != i;
		if (ok) break;
		shuffle(a, a + n, rng);
	}
#endif
	while(true) {
		read();
		int m = 0;
		for (int i = 0; i < n; i++)
			c[i] = 0;
		for (int i = 0; i < n; i++) {
			if (c[i] != 0) continue;
			vector<int> cyc;
			m++;
			int v = i;
			while(c[v] == 0) {
				cyc.push_back(v);
				c[v] = m;
				v = a[v];
			}
			/*
			int sz = (int)cyc.size();
			if (sz > 3) {
				for (int i = 1; i < sz / 2; i++) {
					m++;
					c[cyc[i]] = c[cyc[i + sz / 2]] = m;
				}
			}
			*/
		}
		if (query()) {
			break;
		}
	}
}

int main()
{
	startTime = clock();
//	freopen("input.txt", "r", stdin);
//	freopen("output.txt", "w", stdout);

	int t;
	scanf("%d%d%d", &t, &n, &Q);
	while(t--) solve();
	eprintf("Q = %d\n", Q);

	return 0;
}
