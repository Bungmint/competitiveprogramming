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
    int n, m;
    cin >> n >> m;
    bool fl = 0;
    vpi ans;
    if (n > m)
        swap(n, m), fl = 1;
    vector<vi> unused(8);
    vi t = {0, 3, 6, 1, 4, 7, 2, 5};
    FOR(i, 4, n + 3 * m + 1)
    {
        unused[i % 8].pb(i);
    }
    for (auto &v : unused)
        reverse(all(v));
    FOR(i, 4, 3 * n + m + 1)
    {
        int r = i % 8;
        int targ = t[r];
        while (sz(unused[targ]))
        {
            int z = unused[targ].back();
            int x = (3 * i - z) / 8;
            int y = (3 * z - i) / 8;
            if (x > n || y > m || x <= 0 || y <= 0)
            {
                if (y < 0 || x > n)
                    unused[targ].pop_back();
                else if (x < 0 || y > m)
                    break;
            }
            else
            {
                unused[targ].pop_back();
                // dbg(x, y, z, i);
                ans.pb({x, y});
                break;
            }
        }
    }
    cout << sz(ans) << '\n';
    set<int> st1, st2;
    for (auto &[l, r] : ans)
    {
        if (fl)
            swap(l, r);
        assert(st1.count(3 * l + r) == 0 && st2.count(3 * r + l) == 0);
        st1.insert(3 * l + r), st2.insert(3 * r + l);
        cout << l << ' ' << r << '\n';
    }
}

int main()
{
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);
    int testcase = 1;
    // cin >> testcase;
    while (testcase--)
    {
        solve();
    }
#ifdef LOCAL
    cerr << "Time elapsed: " << 1.0 * (double)clock() / CLOCKS_PER_SEC << " s.\n";
#endif
}