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

const i64 INFT = 1LL << 61LL;

struct Mat {
	i64 v[55][55];
};

i64 safemul(i64 a, i64 b) {
	if (a == 0 || b == 0) return 0;
	if (a > INFT / b) return INFT;
	return a * b;
}

Mat matmul(const Mat& a, const Mat& b, int S) {
	Mat ret;
	for (int i = 0; i < S; ++i) {
		for (int j = 0; j < S; ++j) {
			i64 v = 0;
			for (int k = 0; k < S; ++k) {
				v = min(v + safemul(a.v[i][k], b.v[k][j]), INFT);
			}
			ret.v[i][j] = v;
		}
	}
	return ret;
}

int TC;
int N, L[55], R[55];
i64 A, B;

Mat m, pows[62];

i64 depcount(i64 d) {
	Mat m2;
	for (int i = 0; i <= N + 1; ++i) {
		for (int j = 0; j <= N + 1; ++j) {
			m2.v[i][j] = i == j ? 1 : 0;
		}
	}
	for (int i = 0; i < 63; ++i) if ((d >> i) & 1) {
		m2 = matmul(m2, pows[i], N + 2);
	}
	return m2.v[1][N + 1];
}

int main()
{
	scanf("%d", &TC);
	for (int t = 0; t++ < TC;) {
		// input & compute
		scanf("%d%lld%lld", &N, &A, &B);
		for (int i = 1; i <= N; ++i) scanf("%d", L + i);
		for (int i = 1; i <= N; ++i) scanf("%d", R + i);

		if (A != 1) break;

		for (int i = 0; i <= N + 1; ++i) {
			for (int j = 0; j <= N + 1; ++j) {
				m.v[i][j] = 0;
			}
		}
		for (int i = 1; i <= N; ++i) {
			m.v[i][L[i]] += 1;
			m.v[i][R[i]] += 1;
		}
		for (int i = 0; i <= N + 1; ++i) {
			m.v[i][N + 1] += 1;
		}

		pows[0] = m;
		for (int i = 1; i < 62; ++i) pows[i] = matmul(pows[i - 1], pows[i - 1], N + 2);

		// for (int i = 0; i < 5; ++i) printf("%lld ", depcount(i));
		// puts("");
		i64 left = 1, right = INFT;
		while (left < right) {
			i64 mid = (left + right) / 2;
			if (depcount(mid) >= B) {
				right = mid;
			} else {
				left = mid + 1;
			}
		}
		// output
		printf("Case #%d: %lld\n", t, left - 1);

	}

	return 0;
}
