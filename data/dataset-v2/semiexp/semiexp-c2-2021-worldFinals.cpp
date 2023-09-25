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

bool AUTO = false;

int TC, N, W;
bool alive[2][110];
vector<pair<int, int>> edges;

int score_map[110][110];

void add_rect(int x0, int y0, int x1, int y1) {
	++x1; ++y1;
	score_map[x0][y0]++;
	score_map[x0][y1]--;
	score_map[x1][y0]--;
	score_map[x1][y1]++;
}

void gen_score_map() {
	for (int i = 0; i <= 2 * N; ++i) {
		for (int j = 0; j <= 2 * N; ++j) {
			score_map[i][j] = 0;
		}
	}
	for (int i = 0; i < edges.size(); ++i) {
		int x = edges[i].first, y = edges[i].second;
		add_rect(0, y + 1, x - 1, 2 * N - 1);
		add_rect(x + 1, 0, 2 * N - 1, y - 1);
	}
	for (int i = 0; i <= 2 * N; ++i) {
		for (int j = 1; j <= 2 * N; ++j) {
			score_map[i][j] += score_map[i][j - 1];
		}
	}
	for (int i = 1; i <= 2 * N; ++i) {
		for (int j = 0; j <= 2 * N; ++j) {
			score_map[i][j] += score_map[i - 1][j];
		}
	}
}

int count_cross(int a, int b) {
	int ret = 0;
	for (int i = 0; i < edges.size(); ++i) {
		int x = edges[i].first, y = edges[i].second;
		if ((a < x && b > y) || (a > x && b < y)) ++ret;
	}
	return ret;
}

int rel_score = 0;
mt19937 opponent(234235);

void answer(int a, int b) {
	alive[0][a] = false;
	alive[1][b] = false;
	if (AUTO) {
		rel_score += count_cross(a, b);
	} else {
		printf("%d %d\n", a + 1, b + 1);
		fflush(stdout);
	}
	edges.push_back({a, b});

	int x, y;
	if (AUTO) {
		gen_score_map();
		vector<pair<int, int>> bests; int bc = -1;
		for (int i = 0; i < 2 * N; ++i) if (alive[0][i]) {
			for (int j = 0; j < 2 * N; ++j) if (alive[1][j]) {
				if (bc <= score_map[i][j]) {
					if (bc < score_map[i][j]) {
						bc = score_map[i][j];
						bests.clear();
					}
					bests.push_back({i, j});
				}
			}
		}
		if (bests.empty()) throw 5;

		int id = uniform_int_distribution<int>(0, bests.size() - 1)(opponent);
		x = bests[id].first + 1;
		y = bests[id].second + 1;
		rel_score -= bc;
	} else {
		scanf("%d%d", &x, &y);
	}
	alive[0][x - 1] = false;
	alive[1][y - 1] = false;
	edges.push_back({x - 1, y - 1});
}

mt19937 rng(42);

int random_choice(int k) {
	vector<int> rem;
	for (int i = 0; i < 2 * N; ++i) if (alive[k][i]) rem.push_back(i);
	return rem[uniform_int_distribution<int>(0, rem.size() - 1)(rng)];
}

int main()
{
	int n_win = 0;
	scanf("%d%d%d", &TC, &N, &W);
	for (int t = 0; t++ < TC;) {
		rel_score = 0;
		for (int i = 0; i < 2 * N; ++i) alive[0][i] = alive[1][i] = true;
		edges.clear();

		for (int i = 0; i < N; ++i) {
			int lcnt[2][100];
			for (int k = 0; k < 2; ++k) {
				for (int i = 0; i < 2 * N; ++i) {
					lcnt[k][i] = alive[k][i] ? 1 : 0;
					if (i > 0) lcnt[k][i] += lcnt[k][i - 1];
				}
			}

			int n_rem = 2 * (N - i);
			pair<int, pair<int, int>> best{-1, {-1, -1}};
			gen_score_map();
			for (int j = 0; j < 2 * N; ++j) if (alive[0][j]) {
				for (int k = 0; k < 2 * N; ++k) if (alive[1][k]) {
					int score = 0;
					score += score_map[j][k] * 1000;

					int future_cross = min(lcnt[0][j] - 1, n_rem - lcnt[1][k]) + min(n_rem - lcnt[0][j], lcnt[1][k] - 1);
					score += (1 - future_cross % 2) * 100;
					score += 100 - future_cross;
					// if (lcnt[0][j] == 1 && lcnt[1][k] == 1) ++score;
					// if (lcnt[0][j] == n_rem && lcnt[1][k] == n_rem) ++score;
					// score += count_cross(j, k) * 100;
					// score += ((lcnt[0][j] & 1) == 0 ? 0 : 1);
					// score += (((lcnt[0][j] & 1) == (lcnt[1][k] & 1)) ? 2 : 0);
					// score += j * 2;
					// score += min(j, 2 * N - j) + min(k, 2 * N - k);
					best = max(best, {score, {j, k}});
				}
			}
			answer(best.second.first, best.second.second);
		}

		if (AUTO) {
			if (rel_score > 0) ++n_win;
		} else {
			scanf("%*d");
		}
	}

	if (AUTO) {
		fprintf(stderr, "# win: %d / %d\n", n_win, TC);
	}

	return 0;
}
