//#pragma GCC optimize("Ofast")
#include <bits/stdc++.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/time.h>
#include <sys/resource.h>

using namespace std;

/*** START OF TEMPLATE CODE ***/

typedef vector<string> vs;
typedef long long ll;
typedef complex<double> pnt;
typedef vector<int> vi;
typedef vector<ll> vll;
typedef pair<int, int> pii;
typedef pair<ll, ll> pll;

#define RA(x) begin(x), end(x)
#define FE(i, x) for (auto i = begin(x); i != end(x); ++i)
#define SZ(x) ((ll) (x).size())

template<class T>
vector<T> splitstr(const string &s)
{
    istringstream in(s);
    vector<T> out;
    copy(istream_iterator<T>(in), istream_iterator<T>(), back_inserter(out));
    return out;
}

template<class T> T gcd(T a, T b) { return b ? gcd(b, a % b) : a; }

static void solve_case(int cas);

int main(int argc, char * const *argv)
{
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    struct rlimit stack_limit;
    getrlimit(RLIMIT_STACK, &stack_limit);
    stack_limit.rlim_cur = 1024 * 1024 * 1024;
    setrlimit(RLIMIT_STACK, &stack_limit);

    if (argc >= 2)
    {
        int fd = open(argv[1], O_RDONLY);
        if (fd == -1) { perror(argv[1]); exit(1); }
        if (-1 == dup2(fd, 0)) { perror(argv[1]); exit(1); }
        if (-1 == close(fd)) { perror(argv[1]); exit(1); }
    }
    if (argc >= 3)
    {
        int fd = open(argv[2], O_WRONLY | O_CREAT, 0666);
        if (fd == -1) { perror(argv[2]); exit(1); }
        if (-1 == dup2(fd, 1)) { perror(argv[2]); exit(1); }
        if (-1 == close(fd)) { perror(argv[2]); exit(1); }
    }
    cin.exceptions(ios::failbit | ios::badbit);

    int cases;
    cin >> cases;
    for (int cas = 1; cas <= cases; cas++)
        solve_case(cas);
    return 0;
}

/*** END OF TEMPLATE CODE ***/

template<typename EdgeType>
struct SimpleNode
{
    typedef EdgeType Edge;
    std::vector<Edge> edges;
};

template<typename EdgeType, typename NodeType = SimpleNode<EdgeType> >
class GraphBase
{
public:
    typedef EdgeType Edge;
    typedef NodeType Node;

    std::vector<Node> nodes;

    int size() const { return nodes.size(); }

    int size(int id) const
    {
        assert(0 <= id && id < size());
        return nodes[id].edges.size();
    }

    NodeType &operator[](int id)
    {
        assert(0 <= id && id < size());
        return nodes[id];
    }

    const NodeType &operator[](int id) const
    {
        assert(0 <= id && id < size());
        return nodes[id];
    }

    explicit GraphBase(std::size_t size = 0) : nodes(size) {}
};

template<typename T = int>
struct MFEdge
{
    typedef T flow_type;

    int trg;
    T flow;
    T cap;
    int dual;

    MFEdge() {}
    MFEdge(int trg, T cap, int dual) : trg(trg), flow(0), cap(cap), dual(dual) {}
};

template<typename T = int>
class MFGraph : public GraphBase<MFEdge<T> >
{
private:
    struct pqitem
    {
        int trg;
        T prio;

        pqitem() {}
        pqitem(int trg, T prio) : trg(trg), prio(prio) {}

        bool operator<(const pqitem &b) const
        {
            return prio < b.prio;
        }
    };
public:
    typedef typename MFEdge<T>::flow_type flow_type;
    typedef typename GraphBase<MFEdge<T> >::Edge Edge;
    typedef typename GraphBase<MFEdge<T> >::Node Node;

    void add(int a, int b, T cap, T rcap)
    {
        assert(a >= 0 && a < this->size() && b >= 0 && b < this->size());
        if (a == b)
            return; // no use in network flow, and complicates this function
        int da = this->size(a);
        int db = this->size(b);
        this->nodes[a].edges.push_back(Edge(b, cap, db));
        this->nodes[b].edges.push_back(Edge(a, rcap, da));
    }

    T augment(int source, int sink)
    {
        const int N = this->size();
        const T big = std::numeric_limits<T>::max();

        std::vector<T> prio(N);
        std::vector<int> preve(N);
        std::priority_queue<pqitem> q;

        prio[source] = big;
        q.push(pqitem(source, big));
        while (!q.empty())
        {
            int cur = q.top().trg;
            T p = q.top().prio;
            q.pop();
            if (p != prio[cur])
                continue;
            if (cur == sink)
                break;
            for (int i = 0; i < this->size(cur); i++)
            {
                const Edge &e = this->nodes[cur].edges[i];
                T p2 = std::min(p, e.cap - e.flow);
                if (p2 > prio[e.trg])
                {
                    prio[e.trg] = p2;
                    preve[e.trg] = e.dual;
                    q.push(pqitem(e.trg, p2));
                }
            }
        }

        T up = prio[sink];
        if (up > 0)
        {
            int cur = sink;
            while (cur != source)
            {
                Edge &ed = this->nodes[cur].edges[preve[cur]];
                Edge &e = this->nodes[ed.trg].edges[ed.dual];
                e.flow += up;
                ed.flow -= up;
                cur = ed.trg;
            }
        }
        return up;
    }

    T make_flow(int source, int sink)
    {
        for (int i = 0; i < this->size(); i++)
            for (int j = 0; j < this->size(i); j++)
                this->nodes[i].edges[j].flow = 0;

        T flow = 0;
        T up;
        while ((up = augment(source, sink)) != 0)
            flow += up;
        return flow;
    }

    // Returns all vertices on the source side of the cut. Call this
    // immediately after make_flow
    std::set<int> cut_vertices(int source) const
    {
        std::stack<int> st;
        st.push(source);
        std::set<int> reach;
        reach.insert(source);
        while (!st.empty())
        {
            int cur = st.top();
            st.pop();
            for (int i = 0; i < this->size(cur); i++)
            {
                const Edge &e = this->nodes[cur].edges[i];
                if (e.flow != e.cap && !reach.count(e.trg))
                {
                    st.push(e.trg);
                    reach.insert(e.trg);
                }
            }
        }
        return reach;
    }

    explicit MFGraph(std::size_t size = 0) : GraphBase<MFEdge<T> >(size) {}
};


static void solve_case(int cas)
{
    cout << "Case #" << cas << ": ";

    int R, C;
    cin >> R >> C;
    vi Rn(R), Cn(C);
    for (int i = 0; i < R; i++)
        cin >> Rn[i];
    for (int i = 0; i < C; i++)
        cin >> Cn[i];

    int V = R + C + 2;
    int src = V - 2;
    int sink = V - 1;
    MFGraph<> g(V);
    for (int i = 0; i < R; i++)
        g.add(src, i, Rn[i], 0);
    for (int i = 0; i < C; i++)
        g.add(i + R, sink, Cn[i], 0);
    for (int i = 0; i < R; i++)
        for (int j = 0; j < C; j++)
            g.add(i, j + R, 1, 0);
    int flow = g.make_flow(src, sink);
    if (flow != accumulate(RA(Rn), 0)
        || flow != accumulate(RA(Cn), 0))
    {
        cout << "IMPOSSIBLE\n";
        return;
    }

    vector<vector<bool>> grid(R, vector<bool>(C, false));
    for (int i = 0; i < R; i++)
        for (int j = 0; j < g.size(i); j++)
        {
            int trg = g[i].edges[j].trg - R;
            if (trg >= 0 && trg < C)
                grid[i][trg] = g[i].edges[j].flow > 0;
        }

    bool more = true;
    while (more)
    {
        more = false;
        for (int r0 = 0; r0 < R; r0++)
        {
            for (int c0 = 0; c0 < C; c0++)
                if (grid[r0][c0])
                    for (int c1 = c0 + 1; c1 < C; c1++)
                        if (!grid[r0][c1])
                        {
                            for (int r1 = r0 + 1; r1 < R; r1++)
                                if (!grid[r1][c0] && grid[r1][c1])
                                {
                                    grid[r0][c0] = false;
                                    grid[r0][c1] = true;
                                    grid[r1][c0] = true;
                                    grid[r1][c1] = false;
                                    more = true;
                                    goto skip;
                                }
                        }
        }
skip:;
    }

    cout << "POSSIBLE\n";
    for (int i = 0; i < R; i++)
    {
        for (int j = 0; j < C; j++)
            cout << (grid[i][j] ? '/' : '\\');
        cout << '\n';
    }
}
