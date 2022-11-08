// Problem: Increasing Array Queries
// Contest: CSES - CSES Problem Set
// URL: https://cses.fi/problemset/task/2416
// Memory Limit: 512 MB
// Time Limit: 1000 ms
// 
// Powered by CP Editor (https://cpeditor.org)

#pragma GCC optimize("O3")
#pragma GCC target("sse4")
#include <bits/stdc++.h>
using namespace std;

using ll = long long;
using vi = vector<int>;
using pi = pair<int, int>;
using vpi = vector<pair<int, int>>;
using pl = pair<ll, ll>;
using vl = vector<ll>;
using vpl = vector<pl>;
using ld = long double;

#define all(v) (v).begin(), (v).end()
#define ar array
#define pb push_back
#define sz(x) (int)(x).size()
#define fi first
#define se second
#define lb lower_bound
#define ub upper_bound

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
};

void setIO(string s)
{
    freopen((s + ".in").c_str(), "r", stdin);
    freopen((s + ".out").c_str(), "w", stdout);
}

int n, q;
const int MX =2e5+1, LOG = 20;
pl cost[MX][LOG];

void solve()
{
	cin >> n >> q;
	vl a(n), nxt(n);
	vl pref(n);
	stack<int> sta;
	for (int i=0;i<n;++i)cin >> a[i],pref[i] = (i?pref[i-1]+a[i]:a[i]);
	for (int i=n-1;i>=0;i--){
		while(!sta.empty()&&a[sta.top()]<=a[i]){
			sta.pop();
		}
		nxt[i] = (sta.empty()? n:sta.top());
		sta.push(i);
		ll s = (i? pref[nxt[i]-1]-pref[i-1]:pref[nxt[i]-1]);
		cost[i][0] = {nxt[i], a[i]*(nxt[i]-i)-s};
		dbg(cost[i][0]);
	}
	cost[n][0] = {n, 0};
	for (int j=1;j<LOG;++j) for (int i=0;i<=n;++i){
		auto [x,y] = cost[i][j-1];
		cost[i][j] = {cost[x][j-1].fi, cost[x][j-1].se+y};
		
	}
	for (int i=0;i<q;++i){
		ll x, y;
		cin >> x >> y;
		x--,y--;
		ll ans=0;
		for (int j=LOG-1;j>=0;j--){
			if (cost[x][j].fi<=y) ans += cost[x][j].se, x = cost[x][j].fi;
		}
		dbg(x,y, a[x],pref[y]);
		if (x) ans += (y-x+1)*a[x]-pref[y]+pref[x-1];
		else ans+=(y-x+1)*a[x]-pref[y];
		cout << ans << "\n";
	}
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