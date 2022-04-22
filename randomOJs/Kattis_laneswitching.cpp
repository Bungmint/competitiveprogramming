// Problem: Problem H - Lane Switching
// Contest: Kattis - Alberta Collegiate Programming Contest 2017 — Open Division
// URL: https://open.kattis.com/contests/acpc17open/problems/laneswitching
// Memory Limit: 1024 MB
// Time Limit: 1000 ms
// 
// Powered by CP Editor (https://cpeditor.org)

//Copyright © 2021 Youngmin Park. All rights reserved.
#pragma GCC optimize("O3")
#pragma GCC target("avx2")
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

#define all(v) (v).begin(), (v).end()
#define ar array
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
const int MOD = 1e9 + 7; //998244353;
const ld PI = acos((ld)-1.0);
const int dx[4] = {1, 0, -1, 0}, dy[4] = {0, 1, 0, -1};
mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());
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

struct chash
{
    static uint64_t splitmix64(uint64_t x)
    {
        x += 0x9e3779b97f4a7c15;
        x = (x ^ (x >> 30)) * 0xbf58476d1ce4e5b9;
        x = (x ^ (x >> 27)) * 0x94d049bb133111eb;
        return x ^ (x >> 31);
    }

    size_t operator()(uint64_t x) const
    {
        static const uint64_t FIXED_RANDOM = chrono::steady_clock::now().time_since_epoch().count();
        return splitmix64(x + FIXED_RANDOM);
    }
    size_t operator()(pair<uint64_t,uint64_t> x) const {
        static const uint64_t FIXED_RANDOM = chrono::steady_clock::now().time_since_epoch().count();
        return splitmix64(x.first + FIXED_RANDOM)^(splitmix64(x.second + FIXED_RANDOM) >> 1);
    }
};

void setIO(string s)
{
    freopen((s + ".in").c_str(), "r", stdin);
    freopen((s + ".out").c_str(), "w", stdout);
}

pii combine(pii a, pii b){
    if (a.fi>b.se||b.fi>a.se) return {-1, -1};
    return b;
}

void solve()
{
    int n, m, R;
    cin >> n >> m >> R;
    R*=2;
    vector<vpi> lanes(n);
    pii p;
    cin >> p.fi >> p.se >> p.fi;
    p.se += p.fi;
    p.se*=2, p.fi*=2;
    int plen = p.se-p.fi;
    REP(m-1){
        int i, len, st;
        cin >> i >> len >> st;
        len*=2, st*=2;
        lanes[i].pb({st, st+len});
    }
    F0R(i, n) sort(all(lanes[i]));
    dbg(lanes);
    int l = 0, r = R, ans = -1;
    for (auto&[x, y]:lanes[0]){
        if (y<=p.fi) ckmin(r, p.fi-y);
        else ckmin(r, x-p.se);
    }
    ckmin(r, p.fi), ckmin(r, R-p.se);
    while(l<=r){
        int mid = (l+r)/2;
        set<pair<int,pii>> st;
        function<void(int, pii)> dfs = [&](int i, pii region){
            if (st.count(make_pair(i, region))) return;
            st.insert({i, region});
            if (i==n-1)return;
            F0R(j, sz(lanes[i+1])+1){
                pii nxt;
                if (j==sz(lanes[i+1])&&j==0){
                    nxt = {mid, R-mid-plen};
                }else if (j==sz(lanes[i+1])){
                    auto [x, y] = lanes[i+1][j-1];
                    nxt = {y+mid, R-mid-plen};
                }else if (!j){
                    auto [x, y] = lanes[i+1][j];
                    nxt = {mid, x-mid-plen};
                }else if (j<sz(lanes[i+1])){
                    auto [x, y] = lanes[i+1][j-1];
                    auto [z, w] = lanes[i+1][j];
                    nxt = {y+mid, z-mid-plen};
                }
                if (nxt.fi>nxt.se) continue;
                nxt = combine(region, nxt);
                if (nxt.fi>=0) dfs(i+1, nxt);
            }
            if (i){
            	F0R(j, sz(lanes[i-1])+1){
	                pii nxt;
	                if (j==sz(lanes[i-1])&&j==0){
	                    nxt = {mid, R-mid-plen};
	                }else if (j==sz(lanes[i-1])){
	                    auto [x, y] = lanes[i-1][j-1];
	                    nxt = {y+mid, R-mid-plen};
	                }else if (!j){
	                    auto [x, y] = lanes[i-1][j];
	                    nxt = {mid, x-mid-plen};
	                }else if (j<sz(lanes[i-1])){
	                    auto [x, y] = lanes[i-1][j-1];
	                    auto [z, w] = lanes[i-1][j];
	                    nxt = {y+mid, z-mid-plen};
	                }
	                if (nxt.fi>nxt.se) continue;
	                nxt = combine(region, nxt);
	                if (nxt.fi>=0) dfs(i-1, nxt);
	            }
            }
        };
        pii startRegion = {mid, R-mid-plen};
        for (auto&[x, y]:lanes[0]){
            if (y<=p.fi) ckmax(startRegion.fi, y+mid);
            else ckmin(startRegion.se, x-mid-plen);
        }
        dfs(0, startRegion);
        dbg(st, mid);
        if (sz(st)&&(*--st.end()).fi==n-1) ans = mid, l = mid + 1;
        else r = mid -1;
    }
    if (ans == -1) cout << "Impossible";
    else cout << (ld)ans/2LL;
}

int main()
{
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);
    cout << fixed << setprecision(1);
    int testcase=1;
    // cin >> testcase;
    while (testcase--)
    {
        solve();
    }
}