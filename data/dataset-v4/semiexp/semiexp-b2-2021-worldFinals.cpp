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
#include <bitset>
#include <random>

using namespace std;
#define MOD
#define ADD(X,Y) ((X) = ((X) + (Y)%MOD) % MOD)
typedef long long i64; typedef vector<int> ivec; typedef vector<string> svec;

using Bits = __int128;

int TC;
int V, E, Q;
int S[303030], T[303030];
char Ki[303030]; int L[303030], R[303030], M[303030];

Bits sign[30303];
map<Bits, int> sign2id;
map<pair<int, int>, int> eid;
vector<pair<Bits, Bits>> acc[303030];

void upd(pair<Bits, Bits>& target, const pair<Bits, Bits>& b) {
	target.first ^= b.first;
	target.second ^= b.second;
}

int lookup_sign(Bits b) {
	auto p = sign2id.find(b);
	if (p == sign2id.end()) return -1;
	return p->second;
}

int main()
{
	scanf("%d", &TC);
	for (int t = 0; t++ < TC;) {
		// input & compute
		scanf("%d%d%d", &V, &E, &Q);
		eid.clear();
		for (int i = 1; i <= E; ++i) {
			int x, y;
			scanf("%d%d", &x, &y);
			--x; --y;

			S[i] = x;
			T[i] = y;
			eid[{x, y}] = i;
		}
		for (int i = 0; i < Q; ++i) {
			char ty[2];
			scanf("%s%d%d%d", ty, L + i, R + i, M + i);
			Ki[i] = ty[0];
		}

		mt19937 rng(42);
		uniform_int_distribution<int> udist(0, 0xffff);
		sign2id.clear();
		for (int i = 0; i < V; ++i) {
			Bits b = 0;
			for (int j = 0; j < 8; ++j) {
				b <<= 16;
				b |= udist(rng);
			}
			sign[i] = b;
			sign2id.emplace(b, i);
		}

		for (int i = 1; i <= E; ++i) {
			acc[i].clear();
			acc[i].push_back({0, 0});
			for (int j = i; j <= E; j += i) {
				pair<Bits, Bits>& bk = acc[i].back();

				acc[i].push_back({sign[S[j]] ^ bk.first, sign[T[j]] ^ bk.second});
			}
		}

		vector<int> ans;
		int cnt = 0;
		pair<Bits, Bits> xi{0, 0};
		for (int i = 0; i < V; ++i) {
			xi.first ^= sign[i];
		}
		xi.second = xi.first;

		for (int i = 0; i < Q; ++i) {
			upd(xi, acc[M[i]][R[i] / M[i]]);
			upd(xi, acc[M[i]][(L[i] - 1) / M[i]]);

			if (Ki[i] == 'E') {
				// enable
				cnt += (R[i] / M[i]) - ((L[i] - 1) / M[i]);
			} else {
				// disable
				cnt -= (R[i] / M[i]) - ((L[i] - 1) / M[i]);
			}

			int a = -1;
			if (cnt == V - 1) {
				int s = lookup_sign(xi.first);
				int t = lookup_sign(xi.second);

				if (s >= 0 && t >= 0) {
					if (eid.count({s, t})) {
						a = eid[{s, t}];
					}
				}
			}
			ans.push_back(a);
		}
		
		// output
		printf("Case #%d:", t);
		for (int i = 0; i < ans.size(); ++i) {
			if (ans[i] < 0) printf(" X");
			else printf(" %d", ans[i]);
		}
		puts("");
	}

	return 0;
}
