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
using namespace std;
#define MOD
#define ADD(X,Y) ((X) = ((X) + (Y)%MOD) % MOD)
typedef long long i64; typedef vector<int> ivec; typedef vector<string> svec;

const char cands[14] = "ACDEHIJKMORST";
int TC;
int N, L[101010], R[101010];
set<int> adj[101010];
int ans[101010];
char res[101010];

int main()
{
	scanf("%d", &TC);
	for (int t = 0; t++ < TC;) {
		// input & compute
		scanf("%d", &N);
		for (int i = 0; i < N; ++i) {
			scanf("%d", L + i);
			--L[i];
		}
		for (int i = 0; i < N; ++i) {
			scanf("%d", R + i);
			--R[i];
		}
		for (int i = 0; i < N; ++i) adj[i].clear();
		bool flg = false;
		for (int i = 0; i < N; ++i) {
			set<int> S;
			S.insert(L[i]);
			S.insert(R[i]);
			S.insert(L[L[i]]);
			S.insert(L[R[i]]);
			S.insert(R[L[i]]);
			S.insert(R[R[i]]);
			for (int j : S) {
				if (i == j) flg = true;
				adj[i].insert(j);
				adj[j].insert(i);
			}
		}

		if (flg) {
			printf("Case #%d: IMPOSSIBLE\n", t);
			continue;
		}

		for (int i = 0; i < N; ++i) {
			int used = 0;
			for (int j : adj[i]) {
				if (j < i) used |= 1 << ans[j];
			}
			for (int j = 0; j < 13; ++j) {
				if (!((used >> j) & 1)) {
					ans[i] = j;
					break;
				}
			}
		}
		for (int i = 0; i < N; ++i) res[i] = cands[ans[i]];
		res[N] = 0;

		// output
		printf("Case #%d: %s\n", t, res);

	}

	return 0;
}
