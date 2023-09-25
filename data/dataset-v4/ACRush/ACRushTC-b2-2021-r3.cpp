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

struct Range
{
	int s = 0;
	int t = -1;
	Range() = default;
	Range(int s, int t) : s(s), t(t) { }

	int size() const { return t - s + 1; }
	bool has_overlap(const Range& other_range) const { return s <= other_range.t && t >= other_range.s; }
	bool is_contain(const Range& other_range) const { return s <= other_range.s && t >= other_range.t; }
};

struct Node
{
	Range range;
	Node* left_child;
	Node* right_child;

	// Data
	int add = 0;
	int min_val = 0;
	int min_val_count = 1;

	void init(Range _range)
	{
		range = _range;
		// TODO : initialize the node.
		add = 0;
		min_val = 0;
		min_val_count = 1;
	}
	void pop()
	{
		if (range.s == range.t) { assert(left_child == nullptr && right_child == nullptr); return; }
		assert(left_child != nullptr && right_child != nullptr);
		const Node& l = *left_child;
		const Node& r = *right_child;
		// TODO : update node.info based on children's info.
		min_val = min(l.min_val, r.min_val);
		min_val_count = 0;
		if (l.min_val == min_val) min_val_count += l.min_val_count;
		if (r.min_val == min_val) min_val_count += r.min_val_count;
		min_val += add;
	}
	void push()
	{
		if (range.s == range.t) return;
		assert(left_child != nullptr && right_child != nullptr);
		Node& l = *left_child;
		Node& r = *right_child;
		// TODO : push node.info to children's info.
	}

	int size() const { return range.size(); }
	int mid() const { return (range.s + range.t) / 2; }
};

class IntervalTree
{
public:
	void build(int min_idx, int max_idx)
	{
		assert(min_idx <= max_idx);
		int size = max_idx - min_idx + 1;
		for (; size & (size - 1); size += (size & (-size)));
		reset_buffer(size * 2);
		root = build_internal(min_idx, max_idx);
	}

	template<class Func>
	void traverse(const Range& range, Func func)
	{
		traverse_internal(range, func, 0);
	}

	template<class Func>
	void traverse_in_reverse_order(const Range& range, Func func)
	{
		traverse_internal(range, func, 1);
	}

	template<class Func>
	Node* find_first(const Range& range, Func func)
	{
		return find_first_internal(range, func, 0);
	}

	template<class Func>
	Node* find_last(const Range& range, Func func)
	{
		return find_first_internal(range, func, 1);
	}

	Node* root;

private:
	template<class Func>
	void traverse_internal(const Range& range, Func func, int reverse_order)
	{
		assert(root != nullptr);
		if (!range.has_overlap(root->range)) return;
		traverse_nodes_internal(root, range, func, reverse_order);
	}

	template<class Func>
	void traverse_nodes_internal(Node* p, const Range& range, Func func, int reverse_order)
	{
		if (range.is_contain(p->range)) { func(p); return; }
		p->push();
		int m = p->mid();
		if (reverse_order) 
		{
			if (m < range.t) traverse_nodes_internal(p->right_child, range, func, reverse_order);
			if (m >= range.s) traverse_nodes_internal(p->left_child, range, func, reverse_order);
		}
		else
		{
			if (m >= range.s) traverse_nodes_internal(p->left_child, range, func, reverse_order);
			if (m < range.t) traverse_nodes_internal(p->right_child, range, func, reverse_order);
		}
		p->pop();
	}

	template<class Func>
	Node* find_first_internal(const Range& range, Func func, int reverse_order)
	{
		assert(root != nullptr);
		if (!range.has_overlap(root->range)) return nullptr;
		return find_first_nodes_internal(root, range, func, reverse_order);
	}

	template<class Func>
	Node* find_first_nodes_internal(Node* p, const Range& range, Func func, int reverse_order)
	{
		if (range.is_contain(p->range)) return find_first_nodes_knowly_internal(p, func, reverse_order);
		p->push();
		int m = p->mid();
		if (reverse_order) 
		{
			if (m < range.t) { Node* ret = find_first_nodes_internal(p->right_child, range, func, reverse_order); if (ret != nullptr) return ret; }
			if (m >= range.s) { Node* ret = find_first_nodes_internal(p->left_child, range, func, reverse_order); if (ret != nullptr) return ret; }
		}
		else
		{
			if (m >= range.s) { Node* ret = find_first_nodes_internal(p->left_child, range, func, reverse_order); if (ret != nullptr) return ret; }
			if (m < range.t) { Node* ret = find_first_nodes_internal(p->right_child, range, func, reverse_order); if (ret != nullptr) return ret; }
		}
		p->pop();
		return nullptr;
	}

	template<class Func>
	Node* find_first_nodes_knowly_internal(Node* p, Func func, int reverse_order)
	{
		if (!func(p)) return nullptr;
		if (p->range.s == p->range.t) return p;
		p->push();
		if (reverse_order) 
		{
			Node* ret = find_first_nodes_knowly_internal(p->right_child, func, reverse_order); 
			if (ret != nullptr) return ret;
			ret = find_first_nodes_knowly_internal(p->left_child, func, reverse_order);
			if (ret != nullptr) return ret;
		}
		else
		{
			Node* ret = find_first_nodes_knowly_internal(p->left_child, func, reverse_order);
			if (ret != nullptr) return ret;
			ret = find_first_nodes_knowly_internal(p->right_child, func, reverse_order); 
			if (ret != nullptr) return ret;
		}
		p->pop();
		return nullptr;
	}

	Node* build_internal(int min_idx, int max_idx)
	{
		assert(buffer_pos < buffer.size());
		Node* p = &buffer[buffer_pos++];
		p->init(Range(min_idx, max_idx));
		if (min_idx == max_idx)
			p->left_child = p->right_child = nullptr;
		else
		{
			int m = (min_idx + max_idx) / 2;
			p->left_child = build_internal(min_idx, m);
			p->right_child = build_internal(m + 1, max_idx);
			p->pop();
		}
		return p;
	}

	void reset_buffer(int size)
	{
		buffer_pos = 0;
		buffer.clear();
		buffer.resize(size);
	}

	vector<Node> buffer;
	int buffer_pos;
};

int64 solve_one_case()
{
	int n,m;
	cin>>n>>m;
	VI s(m),t(m);
	REP(i,m) cin>>s[i]>>t[i];
	VI a(n);
	REP(i,n) { cin>>a[i]; --a[i]; }
	VI cnt(m);
	REP(i,n) ++cnt[a[i]];
	REP(i,m)
	{
		s[i]=max(1,s[i]);
		t[i]=min(cnt[i],t[i]);
		if (s[i]>t[i]) s[i]=t[i]=n*2+1;
	}
	REP(i,n) a.push_back(a[i]);
	n=SIZE(a);
	int64 ret=0;

	vector<VI> g(m);
	REP(i,n) g[a[i]].push_back(i);

	IntervalTree tree;
	tree.build(0,n);
	auto update=[&](int s,int t,int delta) {
		if (s>t) return;
		tree.traverse(Range(s,t),[&](Node* node) {
				node->add+=delta;
				node->min_val+=delta;
			});
	};
	update(0,n,1);

	for (int i=n-1;i>=0;i--)
	{
		update(i,i,-1);

		int w=a[i];
		int at=lower_bound(ALL(g[w]),i)-g[w].begin();
		int next=((at+1>=SIZE(g[w]))?n:g[w][at+1]);
		if (s[w]>1) 
		{
			update(i,next-1,1);
			if (at+s[w]-1<SIZE(g[w]))
			{
				int p1=g[w][at+s[w]-1];
				int p2=((at+s[w]>=SIZE(g[w]))?n:g[w][at+s[w]]);
				update(p1,p2-1,-1);
			}
		}
		if (at+t[w]<SIZE(g[w]))
		{
			int p3=g[w][at+t[w]];
			int p4=((at+t[w]+1>=SIZE(g[w]))?n:g[w][at+t[w]+1]);
			update(p3,p4-1,1);
		}
		if (i<n/2)
		{
			// FOR(j,i,n) if (j>i && j-i<n-1 && cbad[j]==0) printf("%d %d\n",i,j);
			Node*p = tree.root;
			if (p->min_val==0) ret+=tree.root->min_val_count;
			// FOR(j,i,n) if (cbad[j]==0) ++ret;
		}
	}

	{
		REP(i,n/2) if (s[a[i]]<=1 && t[a[i]]>=1) --ret;
		int ok=1;
		REP(i,m) if (cnt[i]>0 && (cnt[i]<s[i] || cnt[i]>t[i])) ok=0;
		if (ok) ret-=n/2;
	}
	return ret;
}

int main()
{
#ifdef _MSC_VER
	// freopen("input.txt","r",stdin);
	freopen("big.txt","r",stdin); freopen("output.txt","w",stdout);
#endif
	std::ios::sync_with_stdio(false);
	int testcase;
	cin>>testcase;
	FOR(case_id,1,testcase+1)
	{
		int64 ret=solve_one_case();
		printf("Case #%d: %lld\n",case_id,ret);
	}
	return 0;
}

