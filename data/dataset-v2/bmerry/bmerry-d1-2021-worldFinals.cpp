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

template<typename T, typename C>
class FastDiv
{
private:
    T d, inv;
    int shift;

public:
    typedef T value_type;

    explicit FastDiv(T d) : d(d), inv(0), shift(0)
    {
        assert(d > 1);

        constexpr int C_bits = sizeof(C) * CHAR_BIT;
        constexpr int T_bits = sizeof(T) * CHAR_BIT;
        static_assert(!std::numeric_limits<T>::is_signed, "T must be unsigned");
        static_assert(!std::numeric_limits<C>::is_signed, "C must be unsigned");
        static_assert(C_bits == T_bits * 2);

        constexpr C big = C(1) << (C_bits - 1);
        C inv1 = (big + d - 1) / d;
        int s = C_bits - 1;
        while (inv1 > std::numeric_limits<T>::max())
        {
            s--;
            inv1 = (inv1 + 1) >> 1;
        }
        inv = inv1;
        shift = s - std::numeric_limits<T>::digits;
        assert(shift >= 0 && shift < T_bits);
    }

    template<typename T2, typename C2>
    friend T2 operator /(typename FastDiv<T2, C2>::value_type x, const FastDiv<T2, C2> &y);
    template<typename T2, typename C2>
    friend T2 operator %(typename FastDiv<T2, C2>::value_type x, const FastDiv<T2, C2> &y);
};

template<typename T, typename C>
T operator /(typename FastDiv<T, C>::value_type x, const FastDiv<T, C> &y)
{
    T hi = (C(x) * y.inv) >> std::numeric_limits<T>::digits;
    return hi >> y.shift;
}

template<typename T, typename C>
T operator %(typename FastDiv<T, C>::value_type x, const FastDiv<T, C> &y)
{
    T q = x / y;
    return x - q * y.d;
}

typedef FastDiv<std::uint64_t, __uint128_t> FastDiv64;
typedef FastDiv<std::uint32_t, std::uint64_t> FastDiv32;

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

    static constexpr T multiply(T a, T b)
    {
        using UC = typename std::make_unsigned<C>::type;
        return UC(a) * UC(b) % Modulus;
    }

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
    constexpr MR operator *(MR b) const { return MR(multiply(value, b.value), tag_good()); }
    constexpr MR operator -() const { return MR(-value, tag_minus()); }

    MR &operator +=(MR b) { value = reduce(value + b.value, tag_plus()); return *this; }
    MR &operator -=(MR b) { value = reduce(value - b.value, tag_minus()); return *this; }
    MR &operator *=(MR b) { value = multiply(value, b.value); return *this; }

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


static void solve_case(int cas)
{
    string S;
    int D;
    cin >> S >> D;
    int N = SZ(S);
    mr ans;
    if (D == 1)
    {
        ans = power(mr(2), N - 1);
    }
    else
    {
        FastDiv64 Df(D);
        vector<mr> dpg(N + 1), dpb(N + 1);
        dpg[N] = dpb[N] = 1;
        for (int i = N - 1; i >= 0; i--)
        {
            int v = 0;
            for (int j = i + 1; j <= N; j++)
            {
                v = (v * 10 + (S[j - 1] - '0')) % Df;
                if (v == 0)
                {
                    dpg[i] += dpg[j];
                    dpb[i] += dpg[j];
                }
                else
                    dpg[i] += dpb[j];
            }
        }
        ans = dpg[0];
    }
    cout << "Case #" << cas << ": " << ans << "\n";
}
