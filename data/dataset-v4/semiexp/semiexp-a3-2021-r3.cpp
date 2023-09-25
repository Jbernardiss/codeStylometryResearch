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

int TC, N, K;
int X[110], Q[110];
bool used[110];

void read_seq() {
	for (int i = 0; i < N; ++i) {
		scanf("%d", X + i);
		--X[i];
	}
}

bool query() {
	for (int i = 0; i < N; ++i) printf("%d%c", Q[i] + 1, i == N - 1 ? '\n' : ' ');
	fflush(stdout);
	int ret;
	scanf("%d", &ret);
	return ret;
}

int main()
{
	scanf("%d%d%d", &TC, &N, &K);
	for (int t = 0; t++ < TC;) {
		for (;;) {
			read_seq();
			int col = 0;
			for (int i = 0; i < N; ++i) used[i] = false;
			for (int i = 0; i < N; ++i) {
				if (used[i]) continue;
				int p = i;
				vector<int> chain;
				do {
					used[p] = true;
					chain.push_back(p);
					p = X[p];
					if (chain.size() > 1000) throw 42;
				} while (p != i);
				if (chain.size() <= 4) {
					Q[chain[0]] = col++;
					for (int i = 1; i < chain.size(); ++i) Q[chain[i]] = Q[chain[i - 1]];
				} else {
					if (chain.size() % 3 == 1) {
						int l = chain.size();
						Q[chain[l - 1]] = col;
						Q[chain[l - 2]] = col++;
						chain.pop_back();
						chain.pop_back();
					}
					if (chain.size() % 3 == 2) {
						int l = chain.size();
						Q[chain[l - 1]] = col;
						Q[chain[l - 2]] = col++;
						chain.pop_back();
						chain.pop_back();
					}
					for (int j = 0; j < chain.size(); ++j) {
						if (j % 3 == 0) Q[chain[j]] = col++;
						else Q[chain[j]] = Q[chain[j - 1]];
					}
				}
			}
			if (query()) break;
		}
	}

	return 0;
}
