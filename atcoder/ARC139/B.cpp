// Copyright © 2022 Youngmin Park. All rights reserved.
//#pragma GCC optimize("O3")
//#pragma GCC target("avx2")
#include <bits/stdc++.h>
using namespace std;

using ll = long long;
using vi = vector<int>;
using pii = pair<int, int>;
using vpi = vector<pii>;
using pll = pair<ll, ll>;
using vl = vector<ll>;
using vpl = vector<pll>;
using ld = long double;
template <typename T, size_t SZ>
using ar = array<T, SZ>;

#define all(v) (v).begin(), (v).end()
#define pb push_back
#define sz(x) (int)(x).size()
#define fi first
#define se second
#define lb lower_bound
#define ub upper_bound
#define FOR(i, a, b) for (int i = (a); i < (b); ++i)
#define F0R(i, a) FOR(i, 0, a)
#define ROF(i, a, b) for (int i = (b)-1; i >= (a); --i)
#define R0F(i, a) ROF(i, 0, a)
#define REP(a) F0R(_, a)

const int INF = 1e9;
const ll LINF = 1e18;
const int MOD = 1e9 + 7; // 998244353;
const ld PI = acos((ld)-1.0);
const int dx[4] = {1, 0, -1, 0}, dy[4] = {0, 1, 0, -1};
mt19937_64 rng(chrono::steady_clock::now().time_since_epoch().count());
template <typename T>
using pqg = priority_queue<T, vector<T>, greater<T>>;
template <typename T>
bool ckmin(T &a, const T &b) { return b < a ? a = b, 1 : 0; }
template <typename T>
bool ckmax(T &a, const T &b) { return b > a ? a = b, 1 : 0; }

template <typename A, typename B>
ostream &operator<<(ostream &os, const pair<A, B> &p)
{
    return os << '(' << p.first << ", " << p.second << ')';
}
template <typename T_container, typename T = typename enable_if<!is_same<T_container, string>::value, typename T_container::value_type>::type>
ostream &operator<<(ostream &os, const T_container &v)
{
    os << '{';
    string sep;
    for (const T &x : v)
        os << sep << x, sep = ", ";
    return os << '}';
}
void dbg_out()
{
    cerr << endl;
}
template <typename Head, typename... Tail>
void dbg_out(Head H, Tail... T)
{
    cerr << ' ' << H;
    dbg_out(T...);
}
#ifdef LOCAL
#define dbg(...) cerr << "(" << #__VA_ARGS__ << "):", dbg_out(__VA_ARGS__)
#else
#define dbg(...) 42
#endif

inline namespace RecursiveLambda
{
    template <typename Fun>
    struct y_combinator_result
    {
        Fun fun_;
        template <typename T>
        explicit y_combinator_result(T &&fun) : fun_(forward<T>(fun)) {}
        template <typename... Args>
        decltype(auto) operator()(Args &&...args)
        {
            return fun_(ref(*this), forward<Args>(args)...);
        }
    };
    template <typename Fun>
    decltype(auto) y_combinator(Fun &&fun)
    {
        return y_combinator_result<decay_t<Fun>>(forward<Fun>(fun));
    }
};

void setIO(string s) // USACO
{
#ifndef LOCAL
    freopen((s + ".in").c_str(), "r", stdin);
    freopen((s + ".out").c_str(), "w", stdout);
#endif
}

void solve()
{
    ll n, a, b, x, y, z;
    cin >> n >> a >> b >> x >> y >> z;
    ll ans{n * x};
    ll sq = sqrt(n) + 2;
    if (a >= sq)
    {
        for (ll j = 0; j <= n; j += a)
        {
            ll zz = (j / a) * y + ((n - j) / b) * min(z, b * x) + ((n - j) % b) * x;
            ckmin(ans, zz);
        }
    }
    else if (b >= sq)
    {
        for (ll j = 0; j <= n; j += b)
        {
            ll zz = (j / b) * z + ((n - j) / a) * min(y, a * x) + ((n - j) % a) * x;
            ckmin(ans, zz);
        }
    }
    else
    {
        vector<bool> vis(a), visvis(b);
        for (ll j = (n / b) * b; j >= 0; j -= b)
        {
            ll k = n - j;
            ll r = k % a;
            if (vis[r] == 1)
            {
                break;
            }
            vis[r] = 1;
            ll zz = (j / b) * z + (k / a) * min(y, a * x) + r * x;
            ckmin(ans, zz);
        }
        for (ll j = (n / a) * a; j >= 0; j -= a)
        {
            ll k = n - j;
            ll r = k % b;
            if (visvis[r] == 1)
            {
                break;
            }
            visvis[r] = 1;
            ll zz = (j / a) * y + (k / b) * min(z, b * x) + r * x;
            ckmin(ans, zz);
        }
    }
    cout << ans << '\n';
}

int main()
{
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);
    int testcase = 1;
    cin >> testcase;
    while (testcase--)
    {
        solve();
    }
#ifdef LOCAL
    cerr << "Time elapsed: " << 1.0 * (double)clock() / CLOCKS_PER_SEC << " s.\n";
#endif
}