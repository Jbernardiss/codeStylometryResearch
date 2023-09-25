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

static void solve_case(int cas)
{
    int B, S, N;
    cin >> B >> S >> N;
    vector<pii> slides(S);
    vi in_deg(N), out_deg(N);
    map<pii, int> rev;
    for (int i = 0; i < S; i++)
    {
        int x, y;
        cin >> x >> y;
        x--;
        y--;
        rev[pii(x, y)] = i;
        slides[i] = pii(x, y);
    }

    cout << "Case #" << cas << ":";
    for (int i = 0; i < N; i++)
    {
        char A;
        int L, R, M;
        cin >> A >> L >> R >> M;
        L--;
        int d = (A == 'E') ? 1 : -1;
        while ((L + 1) % M != 0)
            L++;
        for (int i = L; i < R; i += M)
        {
            in_deg[slides[i].second] += d;
            out_deg[slides[i].first] += d;
        }

        int out = -1, in = -1;
        for (int i = 0; i < B; i++)
        {
            if (in_deg[i] == 0)
            {
                if (in != -1)
                    goto bad;
                in = i;
            }
            else if (in_deg[i] != 1)
                goto bad;

            if (out_deg[i] == 0)
            {
                if (out != -1)
                    goto bad;
                out = i;
            }
            else if (out_deg[i] != 1)
                goto bad;
        }
        if (in == -1 || out == -1 || !rev.count(pii(out, in)))
            goto bad;
        cout << ' ' << rev[pii(out, in)] + 1;
        continue;

bad:
        cout << " X";
    }
    cout << '\n';
}
