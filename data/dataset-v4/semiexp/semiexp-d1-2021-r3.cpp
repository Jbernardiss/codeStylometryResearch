#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <stack>
#include <queue>
#include <set>
#include <map>
#include <cmath>
#include <random>
using namespace std;
#define MOD
#define ADD(X,Y) ((X) = ((X) + (Y)%MOD) % MOD)
typedef long long i64; typedef vector<int> ivec; typedef vector<string> svec;

int TC;
int N;

vector<int> adj[50];
map<i64, int> memo;

void visit(int p, i64 mask, i64& vis) {
	if ((vis >> p) & 1) return;
	if (((mask >> p) & 1) == 0) return;
	vis |= 1LL << (i64)p;
	for (int q : adj[p]) visit(q, mask, vis);
}

vector<i64> split_components(i64 mask) {
	vector<i64> ret;
	for (int i = 0; i < N; ++i) if ((mask >> i) & 1) {
		i64 sub = 0;
		visit(i, mask, sub);
		ret.push_back(sub);
		mask ^= sub;
	}
	return ret;
}

int compute_grundy(i64 mask) {
	if (mask == 0) return 0;
	if (memo.count(mask)) return memo[mask];

	vector<int> subs;
	for (int i = 0; i < N; ++i) if ((mask >> i) & 1) {
		vector<int> nbs;
		for (int j : adj[i]) if ((mask >> j) & 1) {
			nbs.push_back(j);
		}
		for (int m = 0; m < (1 << nbs.size()); ++m) {
			i64 mask2 = mask ^ (1LL << (i64)i);
			for (int j = 0; j < nbs.size(); ++j) if ((m >> j) & 1) {
				mask2 ^= 1LL << (i64)nbs[j];
			}
			auto sep = split_components(mask2);
			i64 g = 0;
			for (i64 s : sep) g ^= compute_grundy(s);
			subs.push_back(g);
		}
	}
	subs.push_back(-1);
	subs.push_back(subs.size() + 5);
	sort(subs.begin(), subs.end());

	for (int i = 1; i < subs.size(); ++i) {
		if (subs[i] - subs[i - 1] >= 2) {
			return memo[mask] = subs[i - 1] + 1;			
		}
	}
	return -1;
}

int compute_grundy_general(i64 mask) {
	vector<i64> sep = split_components(mask);
	i64 ret = 0;
	for (auto s : sep) ret ^= compute_grundy(s);
	return ret;
}

int solve(vector<pair<int, int>> edges) {
	for (int i = 0; i < N; ++i) adj[i].clear();
	for (auto& [i, j] : edges) {
		adj[i].push_back(j);
		adj[j].push_back(i);
	}
	memo.clear();
	return compute_grundy((1LL << (i64)N) - 1);
}

random_device dev;
mt19937 rng(dev());

vector<pair<int, int>> random_graph() {
	vector<pair<int, int>> e;
	vector<int> degs(N, 0);
	for (int i = 1; i < N; ++i) {
		vector<int> choices;
		for (int j = 0; j < i; ++j) if (degs[j] < 5) choices.push_back(j);
		int c = choices[uniform_int_distribution<int>(0, choices.size() - 1)(rng)];
		e.push_back({i, c});
		++degs[i];
		++degs[c];
	}
	return e;
}

vector<pair<int, int>> graph = {{1,0},{2,1},{3,2},{4,3},{5,1},{6,3},{7,0},{8,5},{9,8},{10,7},{11,0},{12,10},{13,12},{14,12},{15,3},{16,5},{17,7},{18,0},{19,6},{20,19},{21,20},{22,9},{23,14},{24,4},{25,15},{26,18},{27,6},{28,26},{29,2}};

int M;

vector<int> winning_turn(i64 mask) {
	for (int i = 0; i < N; ++i) if ((mask >> i) & 1) {
		vector<int> nbs;
		for (int j : adj[i]) if ((mask >> j) & 1) {
			nbs.push_back(j);
		}
		for (int m = 0; m < (1 << nbs.size()); ++m) {
			i64 mask2 = mask ^ (1LL << (i64)i);
			for (int j = 0; j < nbs.size(); ++j) if ((m >> j) & 1) {
				mask2 ^= 1LL << (i64)nbs[j];
			}
			if (compute_grundy_general(mask2) == 0) {
				vector<int> ret;
				ret.push_back(i);
				for (int j = 0; j < nbs.size(); ++j) if ((m >> j) & 1) {
					ret.push_back(nbs[j]);
				}
				return ret;
			}
		}
	}
	return {};
}

int main()
{
	scanf("%d", &TC);
	for (int t = 0; t++ < TC;) {
		// input & compute
		scanf("%d", &N);
		if (N != 30) break;
		solve(graph);
		for (int i = 0; i < N - 1; ++i) {
			printf("%d %d\n", graph[i].first + 1, graph[i].second + 1);
		}
		fflush(stdout);
		scanf("%d", &M);
		for (;M--;) {
			i64 rem = (1LL << (i64)N) - 1;
			for (;;) {
				int K;
				scanf("%d", &K);
				if (K == -1) exit(5);
				vector<int> As;
				for (;K--;) {
					int a;
					scanf("%d", &a);
					As.push_back(a - 1);
				}
				for (int a : As) rem ^= 1LL << (i64)a;

				auto turn = winning_turn(rem);
				if (turn.empty()) exit(6);
				printf("%d\n", (int)turn.size());
				for (int i = 0; i < turn.size(); ++i) printf("%d%c", turn[i] + 1, i + 1 == turn.size() ? '\n' : ' ');
				for (int i = 0; i < turn.size(); ++i) rem ^= 1LL << (i64)turn[i];
				fflush(stdout);
				if (rem == 0) break;
			}
		}

	}

	return 0;
}
