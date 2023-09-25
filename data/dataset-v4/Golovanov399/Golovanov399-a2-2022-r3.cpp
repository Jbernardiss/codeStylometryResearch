#include <bits/stdc++.h>

#define all(x) (x).begin(), (x).end()
#define itn int
#define make_unique(x) sort((x).begin(), (x).end()); (x).erase(unique((x).begin(), (x).end()), (x).end())

using namespace std;

inline int nxt() {
	int x;
	cin >> x;
	return x;
}

void solve(int n, [[maybe_unused]] int& k) {
	while (k--) {
		vector<int> p(n);
		for (int i = 0; i < n; ++i) {
			p[i] = nxt() - 1;
		}
		vector<int> color(n, -1);
		iota(all(color), 0);
		vector<char> used(n);
		for (int i = 0; i < n; ++i) {
			if (used[i]) {
				continue;
			}
			vector<int> cyc;
			for (int v = i; !used[v]; v = p[v]) {
				used[v] = 1;
				cyc.push_back(v);
			}
			if ((int)cyc.size() >= 5) {
				for (int j = 0; j < cyc.size() / 2; ++j) {
					color[cyc[j]] = color[cyc[0]];
				}
				for (int j = cyc.size() / 2; j < (int)cyc.size(); ++j) {
					color[cyc[j]] = color[cyc[cyc.size() / 2]];
				}
			} else {
				for (int j = 1; j < (int)cyc.size(); ++j) {
					color[cyc[j]] = color[cyc[0]];
				}
			}
		}
		for (int i = 0; i < n; ++i) {
			cout << color[i] + 1 << " ";
		}
		cout << endl;

		int resp = nxt();
		if (resp == 1) {
			return;
		}
		assert(resp == 0);
	}
	assert(false);
}

int main() {
	int t = nxt(), n = nxt(), k = nxt();
	for (int i = 1; i <= t; ++i) {
		// cout << "Case #" << i << ": ";
		solve(n, k);
	}
	// cerr << k << "\n";

	return 0;
}
