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

static constexpr ll BIG = 1000000000000000002;

static ll big_mul(ll x, ll y)
{
    __int128_t p = __int128_t(x) * y;
    if (p > BIG)
        return BIG;
    else
        return p;
}

static ll big_add(ll x, ll y)
{
    return min(x + y, BIG);
}

template<typename T>
class VMatrix
{
private:
    std::vector<std::vector<T> > values;

public:
    typedef T value_type;

    int rows() const { return values.size(); }
    int cols() const { return values[0].size(); }

    VMatrix(int R, int C, T diag = T(1)) : values(R)
    {
        for (int i = 0; i < R; i++)
        {
            values[i].resize(C);
            for (int j = 0; j < C; j++)
                values[i][j] = (i == j) ? diag : T(0);
        }
    }

    explicit VMatrix(int R = 1) : VMatrix(R, R) {}

    VMatrix operator *(const VMatrix &b) const
    {
        assert(cols() == b.rows());
        VMatrix ans(rows(), b.cols());
        for (int i = 0; i < rows(); i++)
            for (int j = 0; j < b.cols(); j++)
            {
                T sum = T();
                for (int k = 0; k < cols(); k++)
                    sum = big_add(sum, big_mul(values[i][k], b.values[k][j]));
                ans.values[i][j] = sum;
            }
        return ans;
    }

    std::vector<T> operator *(const std::vector<T> &b) const
    {
        assert(cols() == int(b.size()));
        std::vector<T> ans(rows());
        for (int i = 0; i < rows(); i++)
        {
            T sum{};
            for (int j = 0; j < cols(); j++)
                sum = big_add(sum, big_mul(values[i][j], b[j]));
            ans[i] = sum;
        }
        return ans;
    }

    VMatrix &operator *=(const VMatrix &b)
    {
        *this = *this * b;
        return *this;
    }

#define ELEMWISE(op, op_eq)                     \
    VMatrix operator op(const VMatrix &b) const \
    {                                           \
        assert(rows() == b.rows());             \
        assert(cols() == b.cols());             \
        VMatrix ans(rows(), cols());            \
        for (int i = 0; i < rows(); i++)        \
            for (int j = 0; j < cols(); j++)    \
                ans.values[i][j] = values[i][j] op b.values[i][j]; \
        return ans;                             \
    }                                           \
    VMatrix &operator op_eq(const VMatrix &b)   \
    {                                           \
        assert(rows() == b.rows());             \
        assert(cols() == b.cols());             \
        for (int i = 0; i < rows(); i++)        \
            for (int j = 0; j < cols(); j++)    \
                values[i][j] op_eq b.values[i][j]; \
        return *this;                           \
    }

    ELEMWISE(+, +=)
    ELEMWISE(-, -=)
#undef ELEMWISE

    VMatrix operator -() const
    {
        VMatrix ans(rows(), cols());
        for (int i = 0; i < rows(); i++)
            for (int j = 0; j < cols(); j++)
                ans.values[i][j] = -values[i][j];
        return ans;
    }

    template<typename P>
    VMatrix power(P exponent) const
    {
        assert(rows() == cols());
        VMatrix ans(rows(), cols());
        VMatrix p2 = *this;
        while (exponent > 0)
        {
            if (exponent & 1)
                ans *= p2;
            p2 *= p2;
            exponent >>= 1;
        }
        return ans;
    }

    bool operator==(const VMatrix &b) const
    {
        if (rows() != b.rows() || cols() != b.cols())
            return false;
        for (int i = 0; i < rows(); i++)
            for (int j = 0; j < cols(); j++)
                if (values[i][j] != b.values[i][j])
                    return false;
        return true;
    }

    bool operator!=(const VMatrix &b) const
    {
        return !(*this == b);
    }

    const std::vector<T> &operator[](int idx) const
    {
        assert(idx >= 0 && idx < rows());
        return values[idx];
    }

    std::vector<T> &operator[](int idx)
    {
        assert(idx >= 0 && idx < rows());
        return values[idx];
    }
};

static void solve_case(int cas)
{
    int N;
    ll A, B;
    cin >> N >> A >> B;
    vi L(N + 1, -1), R(N + 1, -1);
    for (int i = 1; i <= N; i++)
        cin >> L[i];
    for (int i = 1; i <= N; i++)
        cin >> R[i];
    VMatrix<ll> mat(N + 2, N + 2, 0);
    for (int i = 1; i <= N; i++)
    {
        mat[L[i]][i]++;
        mat[R[i]][i]++;
    }
    for (int i = 0; i <= N; i++)
        mat[N + 1][i]++;
    mat[N + 1][N + 1]++;
    ll lo = -1;
    ll hi = BIG;
    vector<ll> init(N + 2);
    init[1] = 1;
    while (hi - lo > 1)
    {
        ll mid = (lo + hi) / 2;
        auto pmat = mat.power(mid);
        ll tot = (pmat * init).back();
        if (tot >= B)
            hi = mid;
        else
            lo = mid;
    }
    cout << "Case #" << cas << ": " << lo << "\n";
}
