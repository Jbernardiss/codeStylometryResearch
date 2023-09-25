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

// Undefined sign for negative inputs
template<typename T> static constexpr T gcd(T a, T b) { return b ? gcd(b, a % b) : a; }
template<typename T> static constexpr T wrap_pos(T a, T m) { return a < 0 ? a + m : a; }
template<typename T> static constexpr T sqr(T a) { return a * a; }
// m must be positive
template<typename T> static constexpr T mod(T a, T m) { return wrap_pos(a % m, m); }

template<typename T>
static constexpr T inverse2(T a, T m) { return a <= 1 ? a : mod((1 - inverse2(m % a, a) * m) / a, m); }

// a must be relatively prime to m, m > 0
template<typename T>
static constexpr T inverse(T a, T m) { return inverse2(mod(a, m), m); }

template<typename T, typename P>
static constexpr T power(T a, P b) { return b == 0 ? T(1) : (b % 2) ? power(a, b - 1) * a : sqr(power(a, b / 2)); }

template<typename T, typename C, T Modulus>
class MR
{
private:
    struct tag_plus {}; // indicates value is in range [0, 2 * Modulus)
    struct tag_minus {}; // indicates value is in range (-Modulus, Modulus)
    struct tag_good {}; // indicates value is in range

    T value;

    static_assert(std::numeric_limits<C>::max() / Modulus / Modulus > 0, "compute type is too small");
    static_assert(Modulus < std::numeric_limits<T>::max() / 2, "storage type is too small");

    static constexpr T reduce(T value, tag_plus)
    {
        return value >= Modulus ? value - Modulus : value;
    }

    static constexpr T reduce(T value, tag_minus)
    {
        return value < 0 ? value + Modulus : value;
    }

    static constexpr T reduce(T value, tag_good) { return value; }

public:
    typedef T value_type;
    typedef C compute_type;
    static constexpr T modulus = Modulus;

    constexpr MR() : value(0) {}
    constexpr MR(C value) : value(reduce(value % Modulus, tag_minus())) {}
    template<typename tag_t>
    constexpr MR(T value, tag_t tag) : value(reduce(value, tag)) {}

    MR &operator=(C value) { this->value = reduce(value % Modulus, tag_minus()); return *this; }

    constexpr MR operator +(MR b) const { return MR(value + b.value, tag_plus()); }
    constexpr MR operator -(MR b) const { return MR(value - b.value, tag_minus()); }
    constexpr MR operator *(MR b) const { return MR(C(value) * C(b.value) % Modulus, tag_good()); }
    constexpr MR operator -() const { return MR(-value, tag_minus()); }

    MR &operator +=(MR b) { value = reduce(value + b.value, tag_plus()); return *this; }
    MR &operator -=(MR b) { value = reduce(value - b.value, tag_minus()); return *this; }
    MR &operator *=(MR b) { value = C(value) * C(b.value) % Modulus; return *this; }

    constexpr bool operator==(MR b) const { return value == b.value; }
    constexpr bool operator!=(MR b) const { return value != b.value; }

    constexpr T get() const { return value; }

    // These are only valid if the dividend is relatively prime to the modulus
    constexpr MR inverse() const
    {
        return MR(::inverse(C(value), C(Modulus)), tag_good());
    }
    constexpr MR operator /(MR b) const { return *this * b.inverse(); }
    MR &operator /=(MR b) { return *this *= b.inverse(); }
};

template<typename T, typename C, T Modulus>
static inline std::ostream &operator<<(std::ostream &o, MR<T, C, Modulus> mr)
{
    return o << mr.get();
}

typedef MR<int, ll, 1000000007> mr;

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
                    sum += values[i][k] * b.values[k][j];
                ans.values[i][j] = sum;
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

template<typename T>
static inline std::ostream &operator<<(std::ostream &o, const VMatrix<T> &m)
{
    for (int i = 0; i < m.rows(); i++)
    {
        for (int j = 0; j < m.cols(); j++)
            o << m[i][j] << '\t';
        o << '\n';
    }
    return o;
}

static inline ll bit(int x)
{
    return 1LL << x;
}

static vector<mr> invert(VMatrix<mr> &mat, vector<mr> &b)
{
    int N = SZ(b);
    for (int i = 0; i < N; i++)
    {
        int p = i;
        while (p < N && mat[p][i] == 0)
            p++;
        assert(p < N);
        swap(mat[p], mat[i]);
        swap(b[p], b[i]);
        mr scale = mr(1) / mat[i][i];
        for (int j = i; j < N; j++)
            mat[i][j] *= scale;
        b[i] *= scale;
        for (int r = i + 1; r < N; r++)
        {
            scale = mat[r][i];
            for (int j = i; j < N; j++)
                mat[r][j] -= scale * mat[i][j];
            b[r] -= scale * b[i];
        }
    }

    vector<mr> out(N);
    for (int i = N - 1; i >= 0; i--)
    {
        out[i] = b[i];
        for (int j = i + 1; j < N; j++)
            out[i] -= mat[i][j] * out[j];
    }
    return out;
}

static vector<mr> psum_poly(mr M, int d, int p)
{
    VMatrix<mr> mat(d + 2, d + 2);
    for (int i = 0; i <= d + 1; i++)
        for (int j = 0; j <= d + 1; j++)
            mat[i][j] = power(mr(i), j);
    vector<mr> b(d + 2);
    b[0] = power(mr(0), d - p) * power(M, p);
    for (int i = 1; i <= d + 1; i++)
        b[i] = b[i - 1] + power(mr(i), d - p) * power(M - i, p);

    return invert(mat, b);
}

static void solve_case(int cas)
{
    int N, L;
    ll M;
    cin >> N >> M >> L;
    int L2 = 1 << L;
    vi a(L2);
    for (int i = 0; i < L2; i++)
    {
        cin >> a[i];
        a[i]--;
    }

    vi taps(N);
    vll tapms(N);
    for (int i = 0; i < L2; i++)
    {
        taps[a[i]]++;
        tapms[a[i]] |= bit(i);
    }
    vi shared;
    int missing = 0;
    for (int i = 0; i < N; i++)
        if (taps[i] > 1)
            shared.push_back(i);
        else if (taps[i] == 0)
            missing++;
    ll share_mask = 0;
    for (int i = 0; i < L2; i++)
        if (taps[a[i]] > 1)
            share_mask |= bit(i);
    ll share_mask_pop = __builtin_popcountll(share_mask);

    vll scores(N + 1);
    for (ll sm = 0; sm < bit(SZ(shared)); sm++)
    {
        vector<vector<pll>> rscores(2 * L2, vector<pll>(L2 + 1));
        ll sm_pop = __builtin_popcountll(sm);
        ll base = 0;
        for (int i = 0; i < SZ(shared); i++)
            if (sm & bit(i))
                base |= tapms[shared[i]];

        for (int i = 0; i < L2; i++)
        {
            if (share_mask & bit(i))
            {
                rscores[L2 + i][0] = (base & bit(i)) ? pll(0, 1) : pll(1, 0);
                rscores[L2 + i][1] = pll(0, 0);
            }
            else
            {
                rscores[L2 + i][0] = pll(1, 0);
                rscores[L2 + i][1] = pll(0, 1);
            }
        }

        for (int r = L - 1; r >= 0; r--)
        {
            int m = bit(L - 1 - r);
            for (int i = bit(r); i < bit(r + 1); i++)
                for (int p = 0; p <= m; p++)
                    for (int q = 0; q <= m; q++)
                    {
                        pll a = rscores[2 * i][p];
                        pll b = rscores[2 * i + 1][q];
                        pll c;
                        ll total = (a.first + a.second) * (b.first + b.second);
                        if (r & 1)
                        {
                            c.second = a.second * b.second;
                            c.first = total - c.second;
                        }
                        else
                        {
                            c.first = a.first * b.first;
                            c.second = total - c.first;
                        }
                        rscores[i][p + q].first += c.first;
                        rscores[i][p + q].second += c.second;
                    }
        }

        for (int i = 0; i <= L2 - share_mask_pop; i++)
            scores[i + sm_pop] += rscores[1][i].second;
    }

    mr ans = 0;
    N -= missing;
    for (int p = 1; p <= N; p++)
    {
        auto ps = psum_poly(M, N, p);
        mr s = 0;
        for (int i = 0; i < SZ(ps); i++)
            s += power(mr(M - 1), i) * ps[i];
        ans += s * scores[p];
        //for (ll i = 0; i < M; i++)
        //    ans += power(mr(M - i), p) * power(mr(i), N - p) * scores[p];
    }
    ans *= power(mr(M), missing);

    cout << "Case #" << cas << ": " << ans << "\n";
}
