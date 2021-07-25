// Problem: D. Beautiful Array
// Contest: Codeforces - Educational Codeforces Round 63 (Rated for Div. 2)
// URL: https://codeforces.com/problemset/problem/1155/D
// Memory Limit: 256 MB
// Time Limit: 2000 ms
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

template <typename T>
using pqg = priority_queue<T, vector<T>, greater<T>>;
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

struct custom_hash
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

mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());

const int INF = 1e9;
const ll LINF = 1e18;
const int MOD = 1e9 + 7; //998244353;

void solve()
{
	ll n, x;
	cin >> n>>x;
	vl a(n+1), pref(n+1), sufMax(n+1), prefMax(n+1), val(n+1);
	for (int i=1;i<=n;++i) cin >> a[i];
	for (int i=1;i<=n;++i) pref[i] = pref[i-1] + a[i];
	ll res = 0;
	ll cur = 0;
	// No multiplying
	for (int i=1;i<=n;++i){
		res = max(res, pref[i]-cur);
		cur = min(cur, pref[i]);
	}
	
	for (int i=n;i>=1;--i){
		sufMax[i] = a[i];
		if (i<n&&sufMax[i+1]>0) sufMax[i]+=sufMax[i+1];
	}
	for (int i=1;i<=n;++i){
		prefMax[i] = a[i];
		if (prefMax[i-1]>0) prefMax[i] += prefMax[i-1];
	}
	dbg(prefMax, sufMax);
	
	
	for (int i=1;i<=n;++i){
		ll c = a[i]*x;
		dbg(val[i-1], prefMax[i-1]);
		c +=max(0LL, max(val[i-1], prefMax[i-1]));
		val[i] = c;
		if (i+1<=n&&sufMax[i+1]>0) c+= sufMax[i+1];
		res = max(res, c);
	}
	cout << res << endl;
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