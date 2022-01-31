// Problem: E. Staircases
// Contest: Codeforces - Educational Codeforces Round 115 (Rated for Div. 2)
// URL: https://codeforces.com/contest/1598/problem/E
// Memory Limit: 256 MB
// Time Limit: 2000 ms
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

int grid[1000][1000];
int dd[1000][1000];
int rr[1000][1000];
ll res = 0;

void solve()
{
	int n, m, q;
	cin >> n >> m >> q;
	R0F(i, n)R0F(j, m){
		if (i==n-1&&j==m-1);
		else if (i==n-1){
			rr[i][j] = 1+dd[i][j+1];
		}else if (j==m-1){
			dd[i][j] = 1+ rr[i+1][j];
		}else{
			rr[i][j] = 1+ dd[i][j+1], dd[i][j] = 1+ rr[i+1][j];
		}
		res += 1+ dd[i][j]+rr[i][j];
	}
	dbg(res);
	F0R(i, q){
		int x, y;
		cin >> x >> y;
		x--,y--;
		grid[x][y]^=1;
		vpi a;
		FOR(i, 1, 2*max(x,y)+1){
			if (i&1){
				pii p= {x-i/2, y-i/2-1};
				pii q = {x-i/2-1, y-i/2};
				if ((p.fi<0||p.se<0)&&(q.fi<0||q.se<0)) break;
				if (p.fi<0||p.se<0) a.pb(q);
				else if (q.fi<0||q.se<0) a.pb(p);
				else a.pb(p), a.pb(q);
			}else{
				pii q = {x-i/2, y-i/2};
				if (q.fi<0||q.se<0) break;
				a.pb(q);
			}
		}
		if (!grid[x][y]){
			//turn it on
			if (x+1<n&&!grid[x+1][y]) dd[x][y] = 1+rr[x+1][y];
			if (y+1<m&&!grid[x][y+1]) rr[x][y] = 1+dd[x][y+1];
			res += 1+ dd[x][y] + rr[x][y];
			for (auto [nx, ny]:a){
				if (grid[nx][ny]) continue;
				res -= 1+ dd[nx][ny] + rr[nx][ny];
				dd[nx][ny] = rr[nx][ny] = 0;
				if (nx+1<n&&!grid[nx+1][ny]) dd[nx][ny] = 1+rr[nx+1][ny];
				if (ny+1<m&&!grid[nx][ny+1]) rr[nx][ny] = 1+dd[nx][ny+1];
				res += 1+ dd[nx][ny] + rr[nx][ny];
			}
		}else{
			//turn it off
			res -= 1+dd[x][y]+rr[x][y];
			rr[x][y] = dd[x][y] = 0;
			for (auto [nx, ny]:a){
				if (grid[nx][ny]) continue;
				res -= 1+ dd[nx][ny] + rr[nx][ny];
				dd[nx][ny] = rr[nx][ny] = 0;
				if (nx+1<n&&!grid[nx+1][ny]) dd[nx][ny] = 1+rr[nx+1][ny];
				if (ny+1<m&&!grid[nx][ny+1]) rr[nx][ny] = 1+dd[nx][ny+1];
				res += 1+ dd[nx][ny] + rr[nx][ny];
			}
			
		}
		cout << res << "\n";
	}
}

int main()
{
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);
    int testcase=1;
    // cin >> testcase;
    while (testcase--)
    {
        solve();
    }
}