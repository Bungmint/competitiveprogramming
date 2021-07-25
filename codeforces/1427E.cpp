// Problem: E. Xum
// Contest: Codeforces - Codeforces Global Round 11
// URL: https://codeforces.com/contest/1427/problem/E
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

ll gcd(ll a, ll b, ll& x, ll& y) {
    if (b == 0) {
        x = 1;
        y = 0;
        return a;
    }
    ll x1, y1;
    ll d = gcd(b, a % b, x1, y1);
    x = y1;
    y = x1 - y1 * (a / b);
    return d;
}

ll bin_pow(ll x, ll a){
	ll r = 1;
	while(a){
		if (a&1) r *= x;
		a/=2;
		x *= x;
	}
	return r;
}

void solve()
{
	ll x;
	cin >> x;
	int k = log2(x);
	ll y = x;
	vector<pair<pl,char>> ans;
	for (int i=0;i<k;++i){
		ans.pb({{y,y}, '+'});
		y *= 2;
	}
	ans.pb({{y,x}, '^'});
	y ^= x;
	dbg(y,x);
	ll a,b;
	gcd(x, -y, a, b);
	dbg(x*a-b*y);
	if (x*a-b*y==-1) a = -a, b=-b;
	if (a<0||b<0||b%2==1){
		while(a<0||b<0||b%2==1){
			a += y;
			b += x;
		}
	}
	dbg(a,b);
	ll alog = log2(a);
	for (int i=0;i<alog;++i) ans.pb({{x*(1LL<<i), x*(1LL<<i)}, '+'});
	ll ax = x*(1LL<<alog);
	for (int i=alog-1;i>=0;i--){
		if ((1LL<<i)&a){
			ans.pb({{ax, x*(1LL<<i)}, '+'});
			ax += x*(1LL<<i);
		}
	}
	ll blog = log2(b);
	for (int i=0;i<blog;++i) ans.pb({{y*(1LL<<i), y*(1LL<<i)}, '+'});
	ll by = y*(1LL<<blog);
	for (int i=blog-1;i>=0;i--){
		if ((1LL<<i)&b){
			ans.pb({{by, y*(1LL<<i)}, '+'});
			by += y*(1LL<<i);
		}
	}
	ans.pb({{ax, by}, '^'});
	dbg(ax^by, a*x-b*y);
	cout << sz(ans)<<endl;
	for (int i=0;i<sz(ans);++i){
		cout << ans[i].fi.fi << " "<< ans[i].se << " "<< ans[i].fi.se << "\n";
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