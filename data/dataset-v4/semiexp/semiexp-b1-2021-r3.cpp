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

int TC;
int N, C, lo[101010], hi[101010], P[101010];

i64 naive() {
	if (N > 1000) throw 42;

	int cnt[1010];
	int ans = 0;
	for (int i = 0; i < N; ++i) {
		for (int j = 0; j < C; ++j) cnt[j] = 0;
		int unmet = 0;

		for (int j = 0; j < N - 1; ++j) {
			int p = (i + j) % N;

			int col = P[p];
			if (cnt[col] == 0) ++unmet;
			if (cnt[col] == hi[col]) ++unmet;
			if (cnt[col] == lo[col] - 1) --unmet;
			++cnt[col];
			if (unmet == 0 && j >= 1) ++ans;
		}
	}
	return ans;
}

int main()
{
	scanf("%d", &TC);
	for (int t = 0; t++ < TC;) {
		// input & compute
		scanf("%d%d", &N, &C);
		for (int i = 0; i < C; ++i) {
			scanf("%d%d", lo + i, hi + i);
			if (lo[i] == 0) lo[i] = 1;
		}
		for (int i = 0; i < N; ++i) {
			scanf("%d", P + i);
			--P[i];
		}

		// output
		printf("Case #%d: %lld\n", t, naive());

	}

	return 0;
}
