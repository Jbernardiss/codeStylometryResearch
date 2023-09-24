#include <bits/stdc++.h>
using namespace std;

#define rep(i, a, b) for(int i = a; i < (b); ++i)
#define trav(a, x) for(auto& a : x)
#define all(x) x.begin(), x.end()
#define sz(x) (int)(x).size()
typedef long long ll;
typedef pair<int, int> pii;
typedef vector<int> vi;

bool dfs(int a, int L, vector<vi>& g, vi& btoa, vi& A, vi& B) {
	if (A[a] != L) return 0;
	A[a] = -1;
	trav(b, g[a]) if (B[b] == L + 1) {
		B[b] = 0;
		if (btoa[b] == -1 || dfs(btoa[b], L + 1, g, btoa, A, B))
			return btoa[b] = a, 1;
	}
	return 0;
}

int hopcroftKarp(vector<vi>& g, vi& btoa) {
	int res = 0;
	vi A(g.size()), B(btoa.size()), cur, next;
	for (;;) {
		fill(all(A), 0);
		fill(all(B), 0);
		/// Find the starting nodes for BFS (i.e. layer 0).
		cur.clear();
		trav(a, btoa) if(a != -1) A[a] = -1;
		rep(a,0,sz(g)) if(A[a] == 0) cur.push_back(a);
		/// Find all layers using bfs.
		for (int lay = 1;; lay++) {
			bool islast = 0;
			next.clear();
			trav(a, cur) trav(b, g[a]) {
				if (btoa[b] == -1) {
					B[b] = lay;
					islast = 1;
				}
				else if (btoa[b] != a && !B[b]) {
					B[b] = lay;
					next.push_back(btoa[b]);
				}
			}
			if (islast) break;
			if (next.empty()) return res;
			trav(a, next) A[a] = lay;
			cur.swap(next);
		}
		/// Use DFS to scan for augmenting paths.
		rep(a,0,sz(g))
			res += dfs(a, 0, g, btoa, A, B);
	}
}

vi eulerWalk(vector<vector<pii>>& gr, int nedges, int src=0) {
	int n = sz(gr);
	vi D(n), its(n), eu(nedges), ret, s = {src};
	D[src]++; // to allow Euler paths, not just cycles
	while (!s.empty()) {
		int x = s.back(), y, e, &it = its[x], end = sz(gr[x]);
		if (it == end){ ret.push_back(x); s.pop_back(); continue; }
		tie(y, e) = gr[x][it++];
		if (!eu[e]) {
			D[x]--, D[y]++;
			eu[e] = 1; s.push_back(y);
		}}
	trav(x, D) if (x < 0 || sz(ret) != nedges+1) return {};
	return {ret.rbegin(), ret.rend()};
}

void solve(int t){
	cout << "Case #" << t << ": ";
	int N, M;
	cin >> N >> M;
	vector<vector<int> > edges(N);
	for(int i = 0; i < M; i++){
		int u, v;
		cin >> u >> v;
		u--; v--;
		edges[u].push_back(v);
	}
	vector<int> btoa(N, -1);
	int matching = hopcroftKarp(edges, btoa);
	if(matching != N){
		cout << "IMPOSSIBLE" << '\n';
		return;
	}
	vector<vector<int> > euler_graph(N);
	for(int w = 0; w < N; w++){
		int v = btoa[w];
		euler_graph[v].push_back(w);
	}
	vector<vector<int> > residual(2 * N);
	for(int v = 0; v < N; v++){
		for(int w : edges[v]){
			if(btoa[w] != v){
				residual[v].push_back(w + N);
			} else {
				residual[w + N].push_back(v);
			}
		}
	}
	for(int v = 0; v < N; v++){
		for(int w : edges[v]){
			if(v == btoa[w]) continue;
			int st = w + N;
			int en = v;
			vector<int> par(2 * N, -1);
			vector<int> vis(2 * N, 0);
			queue<int> bfs;
			bfs.push(st);
			vis[st] = true;
			while(!bfs.empty()){
				int c = bfs.front();
				bfs.pop();
				for(int d : residual[c]){
					if(!vis[d]){
						vis[d] = true;
						par[d] = c;
						bfs.push(d);
					}
				}
			}
			if(!vis[en]){
				cout << "IMPOSSIBLE" << '\n';
				return;
			}
			vector<int> new_btoa = btoa;
			new_btoa[w] = v;
			int cur = en;
			while(cur != st){
				int p = par[cur];
				if(cur >= N && p < N){
					new_btoa[cur - N] = p;
				}
				cur = p;
			}
			for(int nw = 0; nw < N; nw++){
				int nv = new_btoa[nw];
				euler_graph[nv].push_back(nw);
			}
		}
	}
	vector<vector<pair<int, int> > > gr(N);
	int ne = 0;
	for(int v = 0; v < N; v++){
		for(int w : euler_graph[v]){
			gr[v].push_back({w, ne});
			ne++;
		}
	}
	vector<int> res = eulerWalk(gr, ne, 0);
	if((int)res.size() < ne + 1){
		cout << "IMPOSSIBLE" << '\n';
		return;
	}
	cout << (int)res.size() << '\n';
	for(int i = 0; i < (int)res.size(); i++){
		if(i > 0) cout << " ";
		cout << (res[i] + 1);
	}
	cout << '\n';
}

int main(){
	ios_base::sync_with_stdio(false), cin.tie(nullptr);
	int T;
	cin >> T;
	for(int t = 1; t <= T; t++){
		solve(t);
		cout << flush;
	}
}