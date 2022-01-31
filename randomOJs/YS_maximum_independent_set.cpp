// Problem: Maximum Independent Set
// Contest: Library Checker
// URL: https://judge.yosupo.jp/problem/maximum_independent_set
// Memory Limit: 1024 MB
// Time Limit: 5000 ms
// 
// Powered by CP Editor (https://cpeditor.org)

#pragma GCC optimize("O3")
#pragma GCC target("sse4")
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
#define dbg(...)
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

int dp1[1<<20];
int maxDP[1<<20];
int dp2[1<<20];

void solve()
{
	int n, m;
	cin >>n >> m;
	vector<vi> g(n);
	REP(m){
		int u, v;
		cin >> u >> v;
		g[u].pb(v), g[v].pb(u);
	}
	int n0 = n/2, n1 = n - n0;
	F0R(mask, (1<<n0)){
		dp1[mask] = mask;
		bitset<20> forb = {};
		F0R(i, n0) if (mask&(1<<i)) for (int e:g[i]) if (e<n0) forb[e]=1;
		F0R(i, n0) if((mask&(1<<i))&&forb[i]) dp1[mask]=0;
	}
	F0R(mask, (1<<n0)){
		if (dp1[mask]>=0) maxDP[mask] = dp1[mask];
		int cnt = __builtin_popcount(maxDP[mask]);
		F0R(i, n0) if (mask&(1<<i)){
			int prevM = mask-(1<<i);
			int cur = __builtin_popcount(maxDP[prevM]);
			if (ckmax(cnt, cur)) maxDP[mask] = maxDP[prevM];
		}
	}
	int mx = 0, id1=0, id2=0;
	F0R(mask, (1<<n1)){
		bitset<20> forb2 = {};
		dp2[mask] = mask;
		int curM = (1<<n0)-1;
		F0R(i, n1) if (mask&(1<<i)){
			for (int e:g[i+n0]){
				if (e<n0) curM &= ((1<<n0)-1 -(1<<e));
				else forb2[e] = 1;
			}
		}
		F0R(i, n1) if ((mask&(1<<i))&&forb2[i+n0]) dp2[mask]=0;
		if (dp2[mask]==mask){
			int cnt = __builtin_popcount(mask)+__builtin_popcount(maxDP[curM]);
			if (ckmax(mx, cnt)){
				id1 = maxDP[curM], id2 = mask;
			}
		}
	}
	cout << mx << endl;
	F0R(i, n0) if (id1&(1<<i)) cout << i << " ";
	F0R(i, n1) if (id2&(1<<i)) cout << n0+i << " ";
}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int testcase=1;
    // cin >> testcase;
    while (testcase--)
    {
        solve();
    }
}