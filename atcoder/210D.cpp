// Problem: D - National Railway
// Contest: AtCoder - AtCoder Beginner Contest 210
// URL: https://atcoder.jp/contests/abc210/tasks/abc210_d
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



void solve()
{
	ll h, w, c;
	cin >> h >> w>>c;
	vector<vl> grid(h+1, vl(w+1)), mi(h+1, vl(w+1,LINF)), mi2(h+1, vl(w+1,LINF));
	for (int i=1;i<=h;++i) for (int j=1;j<=w;++j) cin >> grid[i][j];
	ll ans = LINF;
	for (int i=1;i<=h;++i) for (int j=1;j<=w;++j){
		ll cur = grid[i][j]+ c*(i+j);
		if (mi[i-1][j]!=LINF||mi[i][j-1]!=LINF){
			cur = min(mi[i-1][j], mi[i][j-1]) + cur;
			ans = min(ans, cur);
		}
		mi[i][j] = min(grid[i][j]-c*(i+j), min(mi[i-1][j], mi[i][j-1]));
	}
	dbg(ans);
	for (int i=1;i<=h;++i) for (int j=w;j>=1;--j){
		ll cur = grid[i][j] + c*(i-j);
		ans = min(ans, cur + mi2[i-1][j]);
		mi2[i][j] = min(mi2[i-1][j], grid[i][j]-c*(i-j));
		if (j<w) ans = min(ans, cur+mi2[i][j+1]), mi2[i][j] = min(mi2[i][j], mi2[i][j+1]);
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