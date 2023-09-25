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


using Int = int64;

struct Point 
{
	Point() = default;
	Point(Int x, Int y) : x(x), y(y) {}
	Int x = 0;
	Int y = 0;

	Int length_sqr() const { return x * x + y * y; }
};

Point operator-(const Point& a, const Point& b);
Int distance_sqr(const Point& a, const Point& b)
{
	return (a - b).length_sqr();
}
Point operator+(const Point& a, const Point& b)
{
	return Point(a.x + b.x, a.y + b.y);
}
Point operator-(const Point& a, const Point& b) 
{
	return Point(a.x - b.x, a.y - b.y);
}
Point operator*(const Point& a, Int b)
{
	return Point(a.x * b, a.y * b);
}
Point operator/(const Point& a, Int b)
{
	return Point(a.x / b, a.y / b);
}
Int inner(const Point& a, const Point& b)
{
	return a.x * b.x + a.y * b.y;
}
Int inner_sign(const Point& a, const Point& b)
{
	Int t = inner(a, b);
	return (t == 0 ? 0 : (t < 0) ? -1 : 1);
}
Int inner(const Point& a, const Point& b, const Point& c)
{
	return inner(b - a, c - a);
}
Int inner_sign(const Point& a, const Point& b, const Point& c)
{
	Int t = inner(a, b, c);
	return (t == 0 ? 0 : (t < 0) ? -1 : 1);
}
Int outer(const Point& a, const Point& b)
{
	return a.x * b.y - a.y * b.x;
}
int outer_sign(const Point& a, const Point& b)
{
	Int t = outer(a, b);
	return (t == 0 ? 0 : (t < 0) ? -1 : 1);
}
Int outer(const Point& a, const Point& b, const Point& c)
{
	return outer(b - a, c - a);
}
int outer_sign(const Point& a, const Point& b, const Point& c)
{
	Int t = outer(a, b, c);
	return (t == 0 ? 0 : (t < 0) ? -1 : 1);
}
bool is_intersect(const Point& a, const Point& b, const Point& c, const Point& d)
{
	int c1 = outer_sign(a, b, c);
	if (c1 == 0 && inner_sign(c, a, b) <= 0) return true;
	int c2 = outer_sign(a, b, d);
	if (c2 == 0 && inner_sign(d, a, b) <= 0) return true;
	if (c1 * c2 > 0) return false;
	int c3 = outer_sign(c, d, a);
	if (c3 == 0 && inner_sign(a, c, d) <= 0) return true;
	int c4 = outer_sign(c, d, b);
	if (c4 == 0 && inner_sign(b, c, d) <= 0) return true;
	if (c3 * c4 > 0) return false;
	return true;
}

bool operator<(const Point& a, const Point& b)
{
	return a.x < b.x || a.x == b.x && a.y < b.y;
}
bool operator>(const Point& a, const Point& b)
{
	return a.x > b.x || a.x == b.x && a.y > b.y;
}
bool operator<=(const Point& a, const Point& b)
{
	return a.x < b.x || a.x == b.x && a.y <= b.y;
}
bool operator>=(const Point& a, const Point& b)
{
	return a.x > b.x || a.x == b.x && a.y >= b.y;
}
bool operator==(const Point& a, const Point& b)
{
	return a.x == b.x && a.y == b.y;
}
bool operator!=(const Point& a, const Point& b)
{
	return a.x != b.x || a.y != b.y;
}

int sign_of_direction(const Point& a, const Point& b)
{
	double t = (double)a.x * (double)b.y - (double)a.y * (double)b.x;
	if (abs(t) > 1e9) return (t < 0 ? -1 : 1);
	Int d = outer(a, b);
	return (d == 0 ? 0 : (d < 0 ? -1 : 1));
}
int sign_of_direction(const Point& a, const Point& b, const Point& c) 
{
	return sign_of_direction(b - a, c - a);
}
int is_middle(const Point& a, const Point& b, const Point& c) 
{
	return outer(a, b, c) == 0 && inner(a, b, c) >= 0 && inner(c, b, a) >= 0;
}

int n;
vector<Point> a;
int c[12][12][12][12][12][12];

int is_middle(int x,int y,int z) { return is_middle(a[x],a[y],a[z]); }
int is_inside(int x,int y,int z,int w)
{
	if (outer(a[x],a[y],a[z])<0) swap(y,z);
	return outer(a[x],a[y],a[w])>=0 && outer(a[y],a[z],a[w])>=0 && outer(a[z],a[x],a[w])>=0;
}
int outer_sign(int x,int y,int z) { return outer_sign(a[x],a[y],a[z]); }

int calc(int a1,int b1,int c1,int a2,int b2,int c2)
{
	int& ret=c[a1][b1][c1][a2][b2][c2];
	if (ret>=0) return ret;
	for (auto p1:vector<pair<int,int>>{{a1,b1},{b1,c1},{c1,a1}})
		for (auto p2:vector<pair<int,int>>{{a2,b2},{b2,c2},{c2,a2}})
		{
			if (is_middle(p1.first,p2.first,p1.second)+is_middle(p1.first,p2.second,p1.second)+
				is_middle(p2.first,p1.first,p2.second)+is_middle(p2.first,p1.second,p2.second)>=2) return ret=0;
			if (outer_sign(p1.first,p1.second,p2.first)*outer_sign(p1.first,p1.second,p2.second)<0 && 
				outer_sign(p2.first,p2.second,p1.first)*outer_sign(p2.first,p2.second,p1.second)<0) return ret=0;
		}
	if (!is_inside(a1,b1,c1,a2) && !is_inside(a1,b1,c1,b2) && !is_inside(a1,b1,c1,c2)) return ret=1;
	if (!is_inside(a2,b2,c2,a1) && !is_inside(a2,b2,c2,b1) && !is_inside(a2,b2,c2,c1)) return ret=1;
	return ret=0;
}
int ck(int p1,int p2,int p3,const vector<VI>& p)
{
	if (outer_sign(p1,p2,p3)==0) return 0;
	for (auto w:p) if (!calc(p1,p2,p3,w[0],w[1],w[2])) return 0;
	return 1;
}

vector<VI> ret;

void dfs(int cur,int mask,vector<VI>& p)
{
	if (SIZE(p)>SIZE(ret)) ret=p;
	FOR(i,cur,n) if (CKBIT(mask,i)) 
		FOR(j,i+1,n) if (CKBIT(mask,j)) 
			FOR(k,j+1,n) if (CKBIT(mask,k)) 
				if (ck(i,j,k,p))
				{
					p.push_back({i,j,k});
					dfs(cur+1,mask-POW2(i)-POW2(j)-POW2(k),p);
					p.pop_back();
				}
}

vector<VI> solve_one_case()
{
	cin>>n;
	a=vector<Point>(n);
	REP(i,n) cin>>a[i].x>>a[i].y;
	vector<VI> p;
	memset(c,255,sizeof(c));
	ret.clear();
	dfs(0,POW2(n)-1,p);
	return ret;
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
		vector<VI> ret=solve_one_case();
		printf("Case #%d: %d\n",case_id,SIZE(ret));
		for (auto p:ret) printf("%d %d %d\n",p[0]+1,p[1]+1,p[2]+1);
	}
	return 0;
}

