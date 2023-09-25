#include <bits/stdc++.h>

#define all(x) (x).begin(), (x).end()
#define uniquify(x) sort(all((x))), (x).resize(unique(all((x))) - (x).begin())

using namespace std;

inline int nxt() {
	int x;
	cin >> x;
	return x;
}

vector<int> get_distances(const vector<vector<int>>& a, int from) {
	const int n = a.size();
	vector<int> ds(n, -1);
	queue<int> q;
	q.push(from);
	ds[from] = 0;
	while (!q.empty()) {
		int v = q.front();
		q.pop();
		for (int x : a[v]) {
			if (ds[x] == -1) {
				ds[x] = ds[v] + 1;
				q.push(x);
			}
		}
	}
	return ds;
}

void solve() {
	int n = nxt(), m = nxt();
	int alice_init = nxt() - 1;
	int queen_init = nxt() - 1;

	vector<vector<int>> a(n);
	for (int i = 0; i < m; ++i) {
		int u = nxt() - 1, v = nxt() - 1;
		a[u].push_back(v);
		a[v].push_back(u);
	}

	auto alice_ds = get_distances(a, alice_init);
	auto queen_ds = get_distances(a, queen_init);
	if (alice_ds[queen_init] == -1) {
		cout << "SAFE\n";
		return;
	}

	vector<char> in_cycle(n, false);
	vector<char> used(n, false);
	vector<int> lvl(n);
	vector<int> deg_bridges(n);
	function<int(int, int)> dfs = [&](int v, int p) {
		used[v] = 1;
		int highest = lvl[v];
		for (int x : a[v]) {
			if (x == p) {
				continue;
			}
			if (used[x] == 1) {
				highest = min(highest, lvl[x]);
			}
			if (used[x]) {
				continue;
			}
			lvl[x] = lvl[v] + 1;
			highest = min(highest, dfs(x, v));
		}
		if (highest == lvl[v] && p > -1) {
			deg_bridges[v] += 1;
			deg_bridges[p] += 1;
		}
		used[v] = 2;
		return highest;
	};
	dfs(alice_init, -1);

	for (int i = 0; i < n; ++i) {
		if (alice_ds[i] > -1 && deg_bridges[i] < (int)a[i].size() && alice_ds[i] < queen_ds[i]) {
			cout << "SAFE\n";
			return;
		}
	}
	int ans = 0;
	for (int i = 0; i < n; ++i) {
		if (alice_ds[i] > -1 && alice_ds[i] < queen_ds[i]) {
			ans = max(ans, queen_ds[i]);
		}
	}
	cout << ans * 2 << "\n";
}

int main() {
	int t = nxt();
	for (int i = 1; i <= t; ++i) {
		cout << "Case #" << i << ": ";
		solve();
	}

	return 0;
}