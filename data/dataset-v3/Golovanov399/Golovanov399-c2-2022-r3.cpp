#include <bits/stdc++.h>

#define all(x) (x).begin(), (x).end()
#define itn int
#define make_unique(x) sort((x).begin(), (x).end()); (x).erase(unique((x).begin(), (x).end()), (x).end())

using namespace std;

inline int nxt() {
	int x;
	scanf("%d", &x);
	return x;
}

void solve() {
	int n = nxt();
	vector<vector<int>> a(n);
	for (int i = 0; i < n; ++i) {
		a[i].push_back(nxt() - 1);
	}
	for (int i = 0; i < n; ++i) {
		a[i].push_back(nxt() - 1);
	}
	vector<vector<int>> outer_guys(n);
	vector<vector<int>> inner_guys(n);
	for (int i = 0; i < n; ++i) {
		bool ok = true;
		for (int x : a[i]) {
			outer_guys[i].push_back(x);
			inner_guys[x].push_back(i);
			ok &= x != i;
			for (int y : a[x]) {
				outer_guys[i].push_back(y);
				inner_guys[y].push_back(i);
				ok &= y != i;
			}
		}
		if (!ok) {
			cout << "IMPOSSIBLE\n";
			return;
		}
	}
	vector<vector<int>> ar(n);
	for (int i = 0; i < n; ++i) {
		for (int j : a[i]) {
			ar[j].push_back(i);
		}
	}

	set<pair<int, int>> S;
	vector<int> inner(n);
	for (int i = 0; i < n; ++i) {
		inner[i] = inner_guys[i].size();
	}
	for (int i = 0; i < n; ++i) {
		S.insert({inner[i], i});
	}
	vector<int> order;
	vector<char> used(n);
	while (!S.empty()) {
		int v = S.begin()->second;
		S.erase(S.begin());
		used[v] = 1;
		order.push_back(v);
		for (int x : outer_guys[v]) {
			if (used[x]) {
				continue;
			}
			S.erase({inner[x], x});
			--inner[x];
			S.insert({inner[x], x});
		}
	}
	reverse(all(order));
	vector<int> ans(n, -1);
	for (int v : order) {
		int mask = 0;
		for (int x : outer_guys[v]) {
			if (ans[x] > -1) {
				mask |= 1 << ans[x];
			}
		}
		for (int x : inner_guys[v]) {
			if (ans[x] > -1) {
				mask |= 1 << ans[x];
			}
		}
		ans[v] = __builtin_ctz(~mask);
	}
	const string alphabet = "ACDEHIJKMORST";
	string s = "";
	for (int x : ans) {
		s += alphabet[x];
	}
	cout << s << "\n";
}

int main() {
	int t = nxt();
	for (int i = 1; i <= t; ++i) {
		cout << "Case #" << i << ": ";
		solve();
	}

	return 0;
}
