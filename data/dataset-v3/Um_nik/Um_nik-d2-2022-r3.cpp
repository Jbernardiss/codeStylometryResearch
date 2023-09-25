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

map<vector<int>, int> G;

int getG(vector<int> a) {
	sort(all(a));
	reverse(all(a));
	while(!a.empty() && a.back() == 0) a.pop_back();
	reverse(all(a));
	if (G.count(a)) return G[a];
	vector<bool> mex(100, false);
	int n = (int)a.size();
	{
		vector<pii> mv;
		for (int x : a) {
			pii p;
			p.first = getG({x - 1});
			if (x >= 2)
				p.second = getG({x - 2});
			else
				p.second = 0;
			mv.push_back(p);
		}
		for (int mask = 0; mask < (1 << n); mask++) {
			int X = 0;
			for (int i = 0; i < n; i++) {
				if ((mask >> i) & 1)
					X ^= mv[i].second;
				else
					X ^= mv[i].first;
			}
			mex[X] = 1;
		}
	}
	for (int i = 0; i < n; i++) {
		if (i != 0 && a[i] == a[i - 1]) continue;
		int X = 0;
		if (a[i] > 1) {
			X = 0;
			for (int j = 0; j < n; j++) {
				if (i == j) {
					if (a[i] > 2) X ^= getG({a[i] - 3});
				} else {
					X ^= getG({a[j] - 1});
				}
			}
			mex[X] = 1;
		}
		for (int l = 1; l <= a[i]; l++)
			for (int r = l; r <= a[i] && r - l <= 2; r++) {
				vector<int> b = a;
				b[i] = l - 1;
				X = getG(b);
				if (r < a[i]) X ^= getG({a[i] - r - 1});
				mex[X] = 1;
			}
	}
	int g = 0;
	while(mex[g]) g++;
	G[a] = g;
	return g;
}

void eprintVec(vector<int> a) {
	eprintf("[");
	for (int x : a)
		eprintf("%d, ", x);
	eprintf("] ");
}

void brute(int sum, int rem, int lst, vector<int> a) {
	getG(a);
	if (rem == 0) return;
	lst = min(lst, sum);
	for (int x = 1; x <= lst; x++) {
		a.push_back(x);
		brute(sum - x, rem - 1, x, a);
		a.pop_back();
	}
}

struct Graph {
	int V;
	vector<vector<int>> branches;

	Graph() : V(-1), branches() {}
	Graph(int _V, vector<vector<int>> _br) : V(_V), branches(_br) {}

	int G() {
		if (V == -1) return 0;
		vector<int> a;
		for (auto t : branches) a.push_back((int)t.size());
		return getG(a);
	}

	void print() {
		for (auto b : branches) {
			assert(!b.empty());
			printf("%d %d\n", V, b[0]);
			for (int i = 1; i < (int)b.size(); i++)
				printf("%d %d\n", b[i - 1], b[i]);
		}
	}

	vector<int> getAllVertices() {
		vector<int> res = {V};
		for (int i = 0; i < (int)branches.size(); i++)
			for (int v : branches[i])
				res.push_back(v);
		return res;
	}
};

Graph makeBamboo(vector<int> a) {
	assert(!a.empty());
	Graph G = Graph();
	G.V = a.back();
	a.pop_back();
	if (!a.empty()) {
		reverse(all(a));
		G.branches.push_back(a);
	}
	return G;
}
vector<Graph> makeMove(Graph G, vector<int> mv) {
	set<int> toDel(all(mv));
	vector<Graph> res;
	Graph nG = Graph();
	nG.V = G.V;
	for (auto b : G.branches) {
		vector<int> L, R;
		bool f = toDel.count(G.V);
		for (int v : b) {
			if (toDel.count(v)) {
				f = 1;
			} else {
				if (f)
					R.push_back(v);
				else
					L.push_back(v);
			}
		}
		if (!L.empty()) nG.branches.push_back(L);
		if (!R.empty()) res.push_back(makeBamboo(R));
	}
	if (!toDel.count(G.V)) res.push_back(nG);
	return res;
}

vector<pair<int, vector<int>>> getAllMoves(Graph G) {
	vector<pair<int, vector<int>>> res;
	vector<int> a;
	for (auto t : G.branches) a.push_back((int)t.size());
	int n = (int)a.size();
	{
		vector<pii> mv;
		for (int x : a) {
			pii p;
			p.first = getG({x - 1});
			if (x >= 2)
				p.second = getG({x - 2});
			else
				p.second = 0;
			mv.push_back(p);
		}
		for (int mask = 0; mask < (1 << n); mask++) {
			int X = 0;
			vector<int> rem = {G.V};
			for (int i = 0; i < n; i++) {
				if ((mask >> i) & 1) {
					X ^= mv[i].second;
					rem.push_back(G.branches[i][0]);
				} else {
					X ^= mv[i].first;
				}
			}
			res.push_back(mp(X, rem));
		}
	}
	for (int i = 0; i < n; i++) {
		if (i != 0 && a[i] == a[i - 1]) continue;
		int X = 0;
		if (a[i] > 1) {
			vector<int> rem = {G.branches[i][0], G.branches[i][1], G.V};
			X = 0;
			for (int j = 0; j < n; j++) {
				if (i == j) {
					if (a[i] > 2) X ^= getG({a[i] - 3});
				} else {
					X ^= getG({a[j] - 1});
				}
			}
			res.push_back(mp(X, rem));
		}
		for (int l = 1; l <= a[i]; l++)
			for (int r = l; r <= a[i] && r - l <= 2; r++) {
				vector<int> b = a;
				b[i] = l - 1;
				X = getG(b);
				if (r < a[i]) X ^= getG({a[i] - r - 1});
				vector<int> rem;
				if (l == r) {
					rem = {G.branches[i][l - 1]};
				} else {
					rem = {G.branches[i][l], G.branches[i][l - 1]};
					if (r == l + 2) rem.push_back(G.branches[i][l + 1]);
				}
				res.push_back(mp(X, rem));
			}
	}
	return res;
}

void solve(Graph G) {
	vector<Graph> graphs = {G};
	while(!graphs.empty()) {
		map<int, int> inWhich;
		for (int i = 0; i < (int)graphs.size(); i++) {
			vector<int> vv = graphs[i].getAllVertices();
			for (int v : vv) inWhich[v] = i;
		}
		vector<int> mv;
		int k;
		scanf("%d", &k);
		while(k--) {
			int v;
			scanf("%d", &v);
			mv.push_back(v);
		}
		assert(inWhich.count(mv[0]));
		int c = inWhich[mv[0]];
		vector<Graph> nG;
		nG = makeMove(graphs[c], mv);
		for (int i = 0; i < (int)graphs.size(); i++) if (i != c)
			nG.push_back(graphs[i]);
		graphs = nG;
		assert(!graphs.empty());
		vector<int> GR;
		int X = 0;
		for (int i = 0; i < (int)graphs.size(); i++) {
			GR.push_back(graphs[i].G());
			X ^= GR.back();
		}
		assert(X != 0);
		bool fnd = false;
		for (int i = 0; !fnd && i < (int)graphs.size(); i++) {
			auto T = getAllMoves(graphs[i]);
			for (auto m : T) {
				if ((X ^ GR[i] ^ m.first) != 0) continue;
				fnd = true;
				printf("%d\n", (int)m.second.size());
				for (int v : m.second)
					printf("%d ", v);
				printf("\n");
				fflush(stdout);
				nG = makeMove(graphs[i], m.second);
				for (int j = 0; j < (int)graphs.size(); j++) if (i != j)
					nG.push_back(graphs[j]);
				graphs = nG;
				break;
			}
		}
		assert(fnd);
	}
}

int main()
{
	startTime = clock();
//	freopen("input.txt", "r", stdin);
//	freopen("output.txt", "w", stdout);

	G[{}] = 1;
	brute(40, 6, 40, {});
	map<int, vector<int>> mapchik;
	for (auto t : G) {
		if (t.second == 0) {
			int sum = 1;
			for (int x : t.first) sum += x;
			mapchik[sum] = t.first;
			//eprintVec(t.first);
			//eprintf(" -- %d\n", t.second);
		}
	}
/*
	for (int n = 30; n <= 40; n++) {
		assert(mapchik.count(n));
		vector<int> a = mapchik[n];
		Graph G = Graph();
		G.V = 1;
		int cur = 2;
		for (int sz : a) {
			vector<int> br;
			for (int i = 0; i < sz; i++) {
				br.push_back(cur);
				cur++;
			}
			G.branches.push_back(br);
		}
		G.print();
	}
	return 0;
*/
	int t;
	scanf("%d", &t);
	while(t--) {
		int n;
		scanf("%d", &n);
		assert(mapchik.count(n));
		vector<int> a = mapchik[n];
		Graph G = Graph();
		G.V = 1;
		int cur = 2;
		for (int sz : a) {
			vector<int> br;
			for (int i = 0; i < sz; i++) {
				br.push_back(cur);
				cur++;
			}
			G.branches.push_back(br);
		}
		G.print();
		fflush(stdout);
		int m;
		scanf("%d", &m);
		while(m--) solve(G);
	}

	return 0;
}
