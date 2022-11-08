// Problem: Problem 3. Mooyo Mooyo
// Contest: USACO - USACO 2018 December Contest, Silver
// URL: http://www.usaco.org/index.php?page=viewproblem2&cpid=860
// Memory Limit: 256 MB
// Time Limit: 4000 ms
// 
// Powered by CP Editor (https://cpeditor.org)

//Copyright © 2021 Youngmin Park. All rights reserved.
// #pragma GCC optimize("O3")
// #pragma GCC target("avx2")
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

void dfs(int r, int c, int reg, vector<vector<char>>&grid, vector<vector<bool>>&vis, vpi&tmp){
	if (r<0||c<0||r>=sz(grid)||c>=10) return;
	if (grid[r][c]=='0'||grid[r][c]!=reg||vis[r][c]) return;
	vis[r][c] = 1;
	F0R(i, 4){
		int nr = r + dx[i], nc = c + dy[i];
		dfs(nr, nc, reg, grid, vis, tmp);
	}	
	tmp.pb({r, c});
}

void pushdown(vector<vector<char>>&grid){
	F0R(c, 10){
		R0F(r, sz(grid)){
			int rr = r;
			while(rr<sz(grid)-1&&grid[rr+1][c]=='0'){
				swap(grid[rr][c], grid[rr+1][c]);
				rr++;
			}
		}
	}
}

// void func(vector<vector<char>>& grid){
	// for (auto&v:grid){
		// for (auto&e:v) cerr<< e;
		// cerr << "\n";
	// }
	// cerr << "\n";
// }

void solve()
{
	int n, k;
	cin >> n >> k;
	vector<vector<char>> grid(n, vector<char>(10));
	vector<vector<bool>> vis(n, vector<bool>(10));
	vpi todo;
	for (auto&v:grid) for (auto&e:v) cin >> e;
	while(true){
		todo.clear();
		F0R(i, n) fill(all(vis[i]), 0);
		F0R(i, n) F0R(j, 10){
			if (!vis[i][j]){
				vpi tmp;
				dfs(i, j, grid[i][j], grid, vis, tmp);
				if (sz(tmp)>=k)for(auto&e:tmp) todo.pb(e);
			}
		}
		if (todo.empty()) break;
		for (auto &[r, c]: todo) grid[r][c] = '0';
		// func(grid);
		pushdown(grid);
	}
	for (auto&v:grid){
		for (auto&e:v) cout << e;
		cout << "\n";
	}
}

int main()
{
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);
    int testcase=1;
    #ifndef LOCAL
    	setIO("mooyomooyo");
    #endif
    // cin >> testcase;
    while (testcase--)
    {
        solve();
    }
}