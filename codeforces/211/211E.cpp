// Problem: E - Red Polyomino
// Contest: AtCoder - AtCoder Beginner Contest 211
// URL: https://atcoder.jp/contests/abc211/tasks/abc211_e
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
using ull = unsigned long long;
int n, k;
int dx[] = {0,0,-1,1}, dy[] = {-1, 1, 0,0};
char grid[8][8];
map<ull, int> cache;


bool good(int x, int y){
	return (x>=0&&x<n&&y>=0&&y<n&&grid[x][y]=='.');
}

int dp(ull mask){
	if (__builtin_popcountll(mask)==k) return cache[mask] = 1;
	if (cache.count(mask)) return cache[mask];
	vector<bool> used(n*n, false);
	int res = 0;
	for (int i=0;i<n*n;++i){
		if ((mask)&((ull)(1)<<i)){
			int x = i/n, y = i - x*n;
			if (mask==3) dbg(x, y);
			for (int j=0;j<4;++j){
				int nx = x+dx[j], ny = y+dy[j];
				if (mask==3) dbg(nx, ny);
				if (good(nx, ny)&&!used[nx*n+ny]&&!((mask)&((ull)(1)<<(nx*n+ny)))){
					if (mask==3) dbg(nx, ny);
					used[nx*n+ny] = 1;
					res += dp(mask|((ull)(1)<<(nx*n+ny)));
				}
			}
		}
	}
	return cache[mask] = res;
}

void solve()
{
	cin>> n>>k;
	for (int i=0;i<n;++i) for (int j=0;j<n;++j) cin >> grid[i][j];
	for (int i=0;i<n;++i){
		for (int j=0;j<n;++j){
			if (good(i,j)){
				dp((ull)(1)<<(i*n+j));
			}
		}
	}
	ll ans = 0;
	for (auto [mask, cnt]:cache){
		dbg(mask);
		if (__builtin_popcountll(mask)==k){
			dbg(mask);
			ans++;
		}
	}
	cout << ans << endl;
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