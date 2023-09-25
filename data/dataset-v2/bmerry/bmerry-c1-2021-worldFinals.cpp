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

static void solve_case(int cas, int N, int W);

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
    int N, W;
    cin >> cases >> N >> W;
    for (int cas = 1; cas <= cases; cas++)
        solve_case(cas, N, W);
    return 0;
}

/*** END OF TEMPLATE CODE ***/

static pii play(int a, int b)
{
    cout << a + 1 << ' ' << b + 1 << endl;
    int c, d;
    cin >> c;
    if (c == -1)
        exit(1);
    cin >> d;
    c--;
    d--;
    return {c, d};
}

static void solve_case(int cas, int N, int W)
{
    N *= 2;
    vector<bool> used[2];
    used[0].resize(N);
    used[1].resize(N);
    int c = -1, d = -1;
    vector<pii> ropes;
    for (int i = 0; i < N / 2; i++)
    {
        int a = 0, b = 0;
        if (c == d)
        {
            int best = -1;
            int u = -1;
            for (int j = 0; j < N; j++)
            {
                if (used[0][j])
                    continue;
                int score = 0;
                for (auto [p, q] : ropes)
                    if ((p < j && q > j) || (p > j && q < j))
                        score++;
                if (score > best)
                {
                    best = score;
                    u = j;
                }
            }
            a = b = u;
        }
        else
        {
            a = d;
            b = c;
        }
        assert(!used[0][a]);
        assert(!used[1][b]);
        used[0][a] = true;
        used[1][b] = true;
        tie(c, d) = play(a, b);
        used[0][c] = true;
        used[1][d] = true;
        ropes.emplace_back(a, b);
        ropes.emplace_back(c, d);
    }
    int ret;
    cin >> ret;
}
