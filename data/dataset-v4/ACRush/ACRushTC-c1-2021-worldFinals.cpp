#ifdef _MSC_VER
#define _CRT_SECURE_NO_WARNINGS
#endif

#include <bits/stdc++.h>

using namespace std;

#define POW2(X) (1<<(X))
#define CKBIT(S,X) (((S)&POW2(X))!=0)
const double pi=acos(-1.0);
const double eps=1e-11;
template<class T> inline void ckmin(T &a,T b){ a=min(a,b); }
template<class T> inline void ckmax(T &a,T b){ a=max(a,b); }
template<class T> inline T sqr(T x){ return x*x; }
#define SIZE(A) ((int)A.size())
#define LENGTH(A) ((int)A.length())
#define MP(A,B) make_pair(A,B)
#define PB(X) push_back(X)
#define FOR(i,a,b) for(int i=(a);i<(b);++i)
#define REP(i,a) for(int i=0;i<(a);++i)
#define ALL(A) A.begin(),A.end()
using uint=unsigned int;
using int64=long long;
using uint64=unsigned long long;
using ipair=pair<int,int>;
using VI=vector<int>;
using VD=vector<double>;

using Int = int;
class Dinic
{
public:
	struct Edge
	{
		int point = 0;
		Int flow = 0;
		Int capa = 0;
		Edge* next = nullptr;
		Edge* anti = nullptr;
	};
	int node = 0;
	vector<Edge*> head;
	vector<int> dist;
	vector<int> q;
	vector<Edge*> work;

	Dinic(int _node)
	{
		node = _node;
		head.resize(node);
		dist.resize(node);
		q.resize(node);
		work.resize(node);
		for (int i = 0; i < node; i++) head[i] = nullptr;
	}
	pair<Edge*, Edge*> addedge(int u, int v, Int c1, Int c2 = 0)
	{
		Edge *e1 = newedge();
		Edge *e2 = newedge();
		e1->point = v;
		e1->capa = c1;
		e1->flow = 0;
		e1->next = head[u];
		head[u] = e1;
		e1->anti = e2;
		e2->point = u;
		e2->capa = c2;
		e2->flow = 0;
		e2->next = head[v];
		head[v] = e2;
		e2->anti = e1;
		return make_pair(e1, e2);
	}

	void clear()
	{
		for (int i = 0; i < node; ++i)
			for (Edge* e = head[i]; e != nullptr; e = e->next)
				e->flow = 0;
	}

	Int flow(int src, int dest)
	{
		Int result = 0;
		while (dinic_bfs(src, dest))
		{
			for (int i = 0; i < node; ++i) work[i] = head[i];
			result += dinic_dfs(src, std::numeric_limits<Int>::max(), dest);
		}
		return result;
	}

private:
	int buffer_pos = 0;
	vector<vector<Edge>> buffer;

	Edge * newedge()
	{
		if (buffer.empty() || buffer_pos >= static_cast<int>(buffer.back().size()))
		{
			int size = (buffer.empty() ? 16 : buffer.back().size() * 2);
			buffer.emplace_back(vector<Edge>(size));
			buffer_pos = 0;
		}
		return &buffer.back()[buffer_pos++];
	}
	bool dinic_bfs(int src, int dest)
	{
		for (int i = 0; i < node; i++) dist[i] = -1;
		dist[src] = 0;
		int sizeQ = 0;
		q[sizeQ++] = src;
		for (int cl = 0; cl < sizeQ; cl++)
			for (Edge* e = head[q[cl]]; e != nullptr; e = e->next)
				if (e->flow < e->capa && dist[e->point] < 0)
				{
					dist[e->point] = dist[q[cl]] + 1;
					q[sizeQ++] = e->point;
				}
		return dist[dest] >= 0;
	}
	Int dinic_dfs(int x, Int exp, int dest)
	{
		if (x == dest) return exp;
		Int res = 0, tmp;
		for (Edge *&e = work[x]; e != nullptr; e = e->next)
			if (e->flow < e->capa && dist[e->point] == dist[x] + 1 && (tmp = dinic_dfs(e->point, min(exp, e->capa - e->flow), dest)) > 0)
			{
				e->flow += tmp;
				e->anti->flow -= tmp;
				res += tmp;
				exp -= tmp;
				if (exp == 0) break;
			}
		return res;
	}
};

void dfs(vector<VI>& g,int cur,VI& ret)
{
	while (!g[cur].empty())
	{
		int next=g[cur].back();
		g[cur].pop_back();
		dfs(g,next,ret);
	}
	ret.push_back(cur);
}

VI solve_one_case()
{
	int n,m;
	cin>>n>>m;
	vector<ipair> edges(m);
	VI in_deg(n);
	VI out_deg(n);
	REP(i,m)
	{
		int x,y;
		cin>>x>>y; --x; --y;
		edges[i]={x,y};
		++out_deg[x];
		++in_deg[y];
	}

	VI c(n);
	REP(i,n) c[i]=i;
	REP(step,n) for (ipair e:edges)
	{
		int x=c[e.first];
		int y=c[e.second];
		if (x==y) continue;
		REP(i,n) if (c[i]==x) c[i]=y;
	}
	REP(i,n) if (c[i]!=c[0]) return {};
	Dinic dinic(n*2+2);
	int src=n*2;
	int dst=n*2+1;
	vector<Dinic::Edge*> ext;

	int d=0;
	REP(i,n) ckmax(d,max(in_deg[i],out_deg[i]));

	REP(i,n)
	{
		ext.push_back(dinic.addedge(src,i,d-out_deg[i]).first);
		ext.push_back(dinic.addedge(i+n,dst,d-in_deg[i]).first);
	}
	for (auto e:edges)
		dinic.addedge(e.first,e.second+n,10000000);
	for (;d*n<=1000000;d++)
	{
		dinic.flow(src,dst);
		int ok=1;
		for (auto* p=dinic.head[src];p!=nullptr;p=p->next)
		{
			if (p->flow!=p->capa)
			{
				ok=0;
				break;
			}
		}
		if (ok)
		{
			vector<VI> g(n);
			for (auto e:edges) g[e.first].push_back(e.second);
			set<ipair> set_edges(ALL(edges));
			REP(i,n) for (auto* p=dinic.head[i];p!=nullptr;p=p->next)
				if (p->point!=src)
				{
					assert(set_edges.count({i,p->point-n}));
					REP(cl,p->flow) g[i].push_back(p->point-n);
				}
			VI ret;
			dfs(g,0,ret);
			reverse(ALL(ret));
			return ret;
		}
		for (Dinic::Edge* e:ext) ++e->capa;
	}
	return {};
}

int main()
{
#ifdef _MSC_VER
	freopen("input.txt","r",stdin);
#endif
	std::ios::sync_with_stdio(false);
	int testcase;
	cin>>testcase;
	FOR(case_id,1,testcase+1)
	{
		VI ret=solve_one_case();
		if (ret.empty())
			printf("Case #%d: IMPOSSIBLE\n",case_id);
		else
		{
			printf("Case #%d: %d\n",case_id,SIZE(ret));
			REP(i,SIZE(ret))
			{
				if (i>0) printf(" ");
				printf("%d",ret[i]+1);
			}
			printf("\n");
		}
	}
	return 0;
}

