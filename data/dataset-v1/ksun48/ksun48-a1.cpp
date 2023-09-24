#include <bits/stdc++.h>
using namespace std;

struct UF {
    int n;
    vector<int> par;
    UF(int _n) : n(_n) {
        for(int i = 0; i < n; i++) par.push_back(i);
    }
    int find(int a){
        if(a != par[a]) par[a] = find(par[a]);
        return par[a];
    }
    bool join(int a, int b){
        a = find(a);
        b = find(b);
        par[a] = b;
        return (a != b);
    }
};

void solve(int t){
	cout << "Case #" << t << ": ";
	int N, M, A, Q;
	cin >> N >> M >> A >> Q;
	A--; Q--;
	vector<vector<int> > edges(N);
	for(int i = 0; i < M; i++){
		int u, v;
		cin >> u >> v;
		u--; v--;
		edges[u].push_back(v);
		edges[v].push_back(u);
	}
	UF uf(N);
	for(int v = 0; v < N; v++){
		for(int w : edges[v]){
			uf.join(v, w);
		}
	}
	if(uf.find(A) != uf.find(Q)){
		cout << "SAFE";
		cout << '\n';
		return;
	}
	vector<int> leaf_only(N, false);
	{
		vector<int> deg(N);
		for(int i = 0; i < N; i++) deg[i] = (int)edges[i].size();
		queue<int> seen;
		for(int i = 0; i < N; i++){
			if(deg[i] <= 1){
				leaf_only[i] = true;
				seen.push(i);
			}
		}
		while(!seen.empty()){
			int v = seen.front();
			seen.pop();
			for(int w : edges[v]){
				deg[w]--;
				if(deg[w] <= 1 && !leaf_only[w]){
					leaf_only[w] = true;
					seen.push(w);
				}
			}
		}
	}
	vector<vector<int> > dists(2);
	const int INF = int(1e8);
	for(int type = 0; type < 2; type ++){
		int st = vector<int>{A, Q}[type];
		vector<int> dist(N, INF);
		dist[st] = 0;
		queue<int> bfs;
		bfs.push(st);
		while(!bfs.empty()){
			int v = bfs.front();
			bfs.pop();
			for(int w : edges[v]){
				if(dist[w] == INF){
					dist[w] = dist[v] + 1;
					bfs.push(w);
				}
			}
		}
		dists[type] = dist;
	}
	for(int v = 0; v < N; v++){
		if(!leaf_only[v] && dists[0][v] < dists[1][v]){
			cout << "SAFE" << '\n';
			return;
		}
	}
	int ans = 0;
	for(int v = 0; v < N; v++){
		if(dists[0][v] < dists[1][v]){
			ans = max(ans, dists[1][v]);
		}
	}
	cout << (2 * ans) << '\n';
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