#include <bits/stdc++.h>

#include <vector>
#include <queue>
#include <limits>
#include <algorithm>

using std::vector, std::queue;

template <typename int_type = int>
class Dinic {
public:
	struct Edge {
		int from, to;
		int_type cap, flow;
	};

	int n;
	vector<Edge> edges;
	vector<vector<int>> eids;

	Dinic(int _n): n(_n), eids(_n) {}

	void add_edge(int u, int v, int_type c, bool bidirectional = false) {
		eids[u].push_back(edges.size());
		edges.push_back({u, v, c, 0});
		eids[v].push_back(edges.size());
		edges.push_back({v, u, bidirectional ? c : 0, 0});
	}

	int_type k_flow(int s, int t, int_type flow_limit) {
		int_type ans = 0;
		while (bfs(s, t)) {
			ptr.assign(n, 0);
			while (int_type new_flow = push_flow(s, t, flow_limit)) {
				ans += new_flow;
				flow_limit -= new_flow;
			}
			if (!flow_limit) {
				break;
			}
		}
		return ans;
	}

	int_type max_flow(int s, int t) {
		return k_flow(s, t, inf);
	}

private:
	vector<int_type> d;
	vector<int> ptr;
	static inline constexpr int_type inf = std::numeric_limits<int_type>::max();

	int_type push_flow(int s, int t, int_type flow_limit) {
		if (!flow_limit) {
			return 0;
		}
		if (s == t) {
			return flow_limit;
		}
		int_type res = 0;
		for (int& i = ptr[s]; i < (int)eids[s].size(); ++i) {
			int eid = eids[s][i];
			if (d[edges[eid].to] != d[s] + 1 || edges[eid].flow == edges[eid].cap) {
				continue;
			}
			int_type added_flow = push_flow(edges[eid].to, t, std::min(edges[eid].cap - edges[eid].flow, flow_limit));
			if (!added_flow) {
				continue;
			}
			edges[eid].flow += added_flow;
			edges[eid ^ 1].flow -= added_flow;
			flow_limit -= added_flow;
			res += added_flow;
			if (!flow_limit) {
				break;
			}
		}
		return res;
	}

	bool bfs(int s, int t) {
		d.assign(n, inf);
		d[s] = 0;
		queue<int> q;
		q.push(s);
		while (!q.empty()) {
			int v = q.front();
			q.pop();
			for (int eid : eids[v]) {
				if (edges[eid].flow == edges[eid].cap) {
					continue;
				}
				int to = edges[eid].to;
				if (d[to] > d[v] + 1) {
					d[to] = d[v] + 1;
					q.push(to);
				}
			}
		}
		return d[t] != inf;
	}
};
#define all(x) (x).begin(), (x).end()
#define uniquify(x) sort(all((x))), (x).resize(unique(all((x))) - (x).begin())

using namespace std;

inline int nxt() {
	int x;
	cin >> x;
	return x;
}

struct Edge {
	int to, id;
};

ostream& operator <<(ostream& ostr, const Edge& e) {
	return ostr << e.to;
}

void solve() {
	int n = nxt(), m = nxt();
	Dinic<int> net(2 * n + 2);
	vector<int> deg_in(n), deg_out(n);
	for (int i = 0; i < m; ++i) {
		int u = nxt() - 1, v = nxt() - 1;
		deg_in[v] += 1;
		deg_out[u] += 1;
		net.add_edge(u + 1, v + n + 1, m - 1);
	}
	for (int i = 0; i < n; ++i) {
		net.add_edge(0, i + 1, m - deg_out[i]);
		net.add_edge(i + n + 1, 2 * n + 1, m - deg_in[i]);
	}
	// cerr << net.max_flow(s_prime, t_prime) << "\n";
	if (net.max_flow(0, 2 * n + 1) != (n - 1) * m) {
		cout << "IMPOSSIBLE\n";
		return;
	}

	vector<vector<Edge>> g(n);
	vector<char> used_edge(n * m);
	vector<int> ptr(n * m);
	vector<int> cycle;

	vector<int> to_by_id;
	for (int i = 0; i < (int)net.edges.size(); i += 2) {
		const auto& e = net.edges[i];
		if (e.from > 0 && e.from <= n && e.to > n && e.to <= 2 * n) {
			for (int j = 0; j < e.flow + 1; ++j) {
				int id = to_by_id.size();
				g[e.from - 1].push_back({e.to - n - 1, id});
				to_by_id.push_back(e.to - n - 1);
			}
		}
	}

	// cerr << g << "\n";

	function<void(int)> euler = [&](int v) {
		while (ptr[v] < (int)g[v].size() && used_edge[g[v][ptr[v]].id]) {
			++ptr[v];
		}
		if (ptr[v] == (int)g[v].size()) {
			return;
		}
		const auto& e = g[v][ptr[v]];
		used_edge[e.id] = true;
		euler(e.to);
		cycle.push_back(e.id);
		euler(v);
	};
	euler(0);

	vector<int> ans;
	vector<int> freq(n);
	for (int i : cycle) {
		freq[to_by_id[i]] += 1;
		ans.push_back(to_by_id[i]);
	}
	ans.push_back(0);
	reverse(all(ans));
	if (ans.back() != 0 || any_of(all(freq), [&](int x) { return x != freq[0]; })) {
		cout << "IMPOSSIBLE\n";
	} else {
		cout << ans.size() << "\n";
		for (int x : ans) {
			cout << x + 1 << " ";
		}
		cout << "\n";
	}
}

int main() {
	int t = nxt();
	for (int i = 1; i <= t; ++i) {
		cout << "Case #" << i << ": ";
		solve();
	}

	return 0;
}
