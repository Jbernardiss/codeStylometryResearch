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

template <typename Node>
class SegTree {
public:
	explicit SegTree(int _n) {
		n = 1;
		while (n < _n) {
			n *= 2;
		}
		a.resize(n + n);
		for (int i = n - 1; i > 0; --i) {
			a[i] = merge(a[i + i], a[i + i + 1]);
		}
	}

	template <typename T>
	explicit SegTree(const vector<T>& ar) {
		n = 1;
		while (n < (int)ar.size()) {
			n *= 2;
		}
		a.resize(n + n);
		for (int i = 0; i < (int)ar.size(); ++i) {
			a[n + i] = Node(ar[i]);
		}
		for (int i = n - 1; i > 0; --i) {
			a[i] = merge(a[i + i], a[i + i + 1]);
		}
	}

	Node get(int l, int r) {
		return get(1, 0, n, l, r);
	}

	template <typename... Args>
	void update_point(int pos, Args&&... args) {
		{
			int v = 1, l = 0, r = n;
			while (v < n) {
				push(v);
				int m = (l + r) / 2;
				if (pos < m) {
					v *= 2;
					r = m;
				} else {
					v = v * 2 + 1;
					l = m;
				}
			}
		}
		pos += n;
		a[pos].update(std::forward<Args>(args)...);
		while (pos > 1) {
			pos /= 2;
			a[pos] = merge(a[pos * 2], a[pos * 2 + 1]);
		}
	}

	template <typename... Args>
	void update(int l, int r, Args&&... args) {
		_update(1, 0, n, l, r, std::forward<Args>(args)...);
	}

protected:
	int n;
	vector<Node> a;

	void push(int v) {
		if (v + v < n + n) {
			for (int t : {0, 1}) {
				a[v].push(a[v + v + t]);
			}
			a[v].clear_after_push();
		}
	}

private:
	Node get(int v, int l1, int r1, int l, int r) {
		if (l >= r1 || l1 >= r) {
			return Node{};
		}
		if (l <= l1 && r >= r1) {
			return a[v];
		}
		push(v);
		int m = (l1 + r1) / 2;
		return merge(get(v + v, l1, m, l, r), get(v + v + 1, m, r1, l, r));
	}

	template <typename... Args>
	void _update(int v, int l1, int r1, int l, int r, Args&&... args) {
		if (l >= r1 || l1 >= r) {
			return;
		}
		if (l <= l1 && r >= r1) {
			a[v].update(std::forward<Args>(args)...);
			return;
		}
		push(v);
		int m = (l1 + r1) / 2;
		_update(v + v, l1, m, l, r, std::forward<Args>(args)...);
		_update(v + v + 1, m, r1, l, r, std::forward<Args>(args)...);
		a[v] = merge(a[v + v], a[v + v + 1]);
	}
};

struct Node {
	int mn;
	int cnt_mn;
	int add;

	Node(): mn(0), cnt_mn(0), add(0) {}
	Node(int x): mn(x), cnt_mn(1), add(0) {}
	Node(int _mn, int _cnt, int _add): mn(_mn), cnt_mn(_cnt), add(_add) {}
	void push(Node& ot) const {
		ot.mn += add;
		ot.add += add;
	}
	void clear_after_push() {
		add = 0;
	}
	void update(int x) {
		mn += x;
		add += x;
	}
};

Node merge(const Node& a, const Node& b) {
	return {
		min(a.mn, b.mn),
		(a.mn <= b.mn ? a.cnt_mn : 0) + (b.mn <= a.mn ? b.cnt_mn : 0),
		0
	};
}

struct Event {
	int l, r, x;
};

void solve() {
	int n = nxt(), c = nxt();
	vector<vector<int>> positions(c);
	vector<pair<int, int>> restr(c);
	for (int i = 0; i < c; ++i) {
		restr[i].first = nxt();
		restr[i].second = nxt();
	}
	vector<int> a(n);
	for (int i = 0; i < n; ++i) {
		a[i] = nxt() - 1;
		positions[a[i]].push_back(i);
	}

	vector<vector<Event>> evs(2 * n + 1);
	auto ban_rectangle = [&](int l1, int r1, int l2, int r2) {
		evs[l1].push_back({l2, r2, 1});
		evs[r1].push_back({l2, r2, -1});
	};

	for (int i = 0; i < c; ++i) {
		const int sz = positions[i].size();
		for (int j = 0; j < sz; ++j) {
			int x = positions[i][j];
			positions[i].push_back(x + n);
		}
		if (positions[i].empty()) {
			continue;
		}
		const auto& r = restr[i];
		// cannot allow [1, r.first - 1] and [r.second + 1, oo]
		if (r.first - 1 >= 1) {
			int last = -1;
			for (int j = 0; j < (int)positions[i].size(); ++j) {
				ban_rectangle(last + 1, positions[i][j] + 1, positions[i][j] + 1, j + r.first - 1 < (int)positions[i].size() ? positions[i][j + r.first - 1] + 1 : 2 * n);
				last = positions[i][j];
			}
		}
		{
			int last = -1;
			for (int j = 0; j + r.second < (int)positions[i].size(); ++j) {
				ban_rectangle(last + 1, positions[i][j] + 1, positions[i][j + r.second] + 1, 2 * n);
			}
		}
	}
	// evs[0].push_back({n + 1, 2 * n, 1});
	// for (int i = 1; i < n; ++i) {
	// 	evs[i].push_back({n + i, n + i + 1, -1});
	// }
	// for (int i = 0; i < n; ++i) {
	// 	evs[i].push_back({i, i + 1, 1});
	// }

	SegTree<Node> tree(vector<int>(2 * n, 0));
	long long ans = 0;
	for (int i = 0; i < n; ++i) {
		// cerr << i << ": ";
		for (auto [l, r, x] : evs[i]) {
			tree.update(l, r, x);
			// cerr << l << " " << r << " " << x << "\n";
		}
		// for (auto nd : tree.a) {
		// 	cerr << nd.mn << " " << nd.cnt_mn << ", ";
		// }
		// cerr << "\n";
		auto nd = tree.get(i + 2, i + n);
		if (nd.mn == 0) {
			ans += nd.cnt_mn;
		}
	}
	cout << ans << "\n";
}

int main() {
	int t = nxt();
	for (int i = 1; i <= t; ++i) {
		cout << "Case #" << i << ": ";
		solve();
	}

	return 0;
}
