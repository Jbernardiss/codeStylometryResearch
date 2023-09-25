#include <bits/stdc++.h>

using namespace std;
typedef long long ll;
#define rep(i, a, b) for(int i = a; i < (b); ++i)
#define all(x) begin(x), end(x)
#define sz(x) (int)(x).size()
typedef long long ll;
typedef pair<int, int> pii;
typedef vector<int> vi;

template <class T> int sgn(T x) { return (x > 0) - (x < 0); }
template<class T>
struct Point {
    typedef Point P;
    T x, y;
    explicit Point(T x=0, T y=0) : x(x), y(y) {}
    bool operator<(P p) const { return tie(x,y) < tie(p.x,p.y); }
    bool operator==(P p) const { return tie(x,y)==tie(p.x,p.y); }
    P operator+(P p) const { return P(x+p.x, y+p.y); }
    P operator-(P p) const { return P(x-p.x, y-p.y); }
    P operator*(T d) const { return P(x*d, y*d); }
    P operator/(T d) const { return P(x/d, y/d); }
    T dot(P p) const { return x*p.x + y*p.y; }
    T cross(P p) const { return x*p.y - y*p.x; }
    T cross(P a, P b) const { return (a-*this).cross(b-*this); }
    T dist2() const { return x*x + y*y; }
    double dist() const { return sqrt((double)dist2()); }
    // angle to x-axis in interval [-pi, pi]
    double angle() const { return atan2(y, x); }
    P unit() const { return *this/dist(); } // makes dist()=1
    P perp() const { return P(-y, x); } // rotates +90 degrees
    P normal() const { return perp().unit(); }
    // returns point rotated 'a' radians ccw around the origin
    P rotate(double a) const {
        return P(x*cos(a)-y*sin(a),x*sin(a)+y*cos(a)); }
    friend ostream& operator<<(ostream& os, P p) {
        return os << "(" << p.x << "," << p.y << ")"; }
};

template<class P> bool onSegment(P s, P e, P p) {
    return p.cross(s, e) == 0 && (s - p).dot(e - p) <= 0;
}

template<class P> vector<P> segInter(P a, P b, P c, P d) {
    auto oa = c.cross(d, a), ob = c.cross(d, b),
         oc = a.cross(b, c), od = a.cross(b, d);
    // Checks if intersection is single non-endpoint point.
    if (sgn(oa) * sgn(ob) < 0 && sgn(oc) * sgn(od) < 0)
        return {(a * ob - b * oa) / (ob - oa)};
    set<P> s;
    if (onSegment(c, d, a)) s.insert(a);
    if (onSegment(c, d, b)) s.insert(b);
    if (onSegment(a, b, c)) s.insert(c);
    if (onSegment(a, b, d)) s.insert(d);
    return {all(s)};
}

const int MAXN = 110;
int N;
Point <long long> p[MAXN];

vector <pair <int, int> > seg;

void gogo()
{
    cin >> N;
    for (int i = 0; i < N; i++)
        cin >> p[i].x >> p[i].y;

    seg.clear();

    for (int i = 0; i < 2; i++)
    {
        int a, b;
        cin >> a >> b;
        a--, b--;
        if (a > b) swap (a, b);
        seg.push_back (make_pair (a, b));
    }

    for (int i = 0; i < N; i++)
        for (int j = i + 1; j < N; j++)
        {
            bool bad = false;
            for (int k = 0; k < seg.size(); k++)
            {
                if (seg[k].first == i && seg[k].second == j)
                {
                    bad = true;
                    break;
                }
                int u = seg[k].first, v = seg[k].second;
                if ( i == u || i == v || j == u || j == v) continue;
                if (segInter (p[i], p[j], p[u], p[v]).size() > 0)
                {
                    bad = true;
                    break;
                }

            }
            if (bad) continue;

            seg.push_back (make_pair (i, j));
        }

    cout << seg.size() - 2 << "\n";
    for (int i = 2; i < seg.size(); i++)
    {
        cout << seg[i].first + 1 << " " << seg[i].second + 1 << "\n";
    }
}

int main()
{
    int T; cin >> T;

    for (int t = 0; t < T; t++)
    {
        cout << "Case #" << t + 1 << ": ";
        gogo();
    }
}