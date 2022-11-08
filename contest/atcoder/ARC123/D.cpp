// Problem: D - Inc, Dec - Decomposition
// Contest: AtCoder - AtCoder Regular Contest 123
// URL: https://atcoder.jp/contests/arc123/tasks/arc123_d
// Memory Limit: 1024 MB
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
ll a[200011], dif[200101];
int n;

ll f(ll x){
	ll cur = 0;
	ll b = x;
	for (int i=0;i<n;++i){
		b+=dif[i];
		cur += llabs(b) + llabs(a[i]-b);
		
	}
	return cur;
}

void solve()
{
	cin >>n;
	for (int i=0;i<n;++i) cin >> a[i];
	for (int i=1;i<n;++i){
		dif[i] = max(a[i]-a[i-1], 0LL);
	}
	ll ans = LLONG_MAX;
	ll l = -LINF, r =LINF;
	while(l+4<r){
		ll m = l +(r-l)/2;
		ll v1 = f(m), v2 = f(m+1);
		if (v1<=v2){
			r = m;
		}else{
			l = m+1;
		}
	}
	for (ll i=l-100;i<=r+100;++i){
		ll cur = 0;
		ll b = i;
		for (int j=0;j<n;++j){
			b+=dif[j];
			cur += llabs(b) + llabs(a[j]-b);
		}
		dbg(i, cur);
		ans = min(ans, cur);
	}
	cout << ans;
	
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