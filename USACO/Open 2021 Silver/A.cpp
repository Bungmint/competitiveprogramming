// Problem: Problem 1. Maze Tac Toe
// Contest: USACO - USACO 2021 US Open, Silver
// URL: http://www.usaco.org/index.php?page=viewproblem2&cpid=1134
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


int n;
bool vis[25][25][19863];
bool W[19863], Full[19863];
ar<char,3> grid[25][25];
set<int> ans;

bool hasWon(int mask){
	vi state;
	while(mask||sz(state)<9){
		state.pb(mask%3);
		mask/=3;
	}
	reverse(all(state));
	F0R(r, 3){
		if (state[r*3]==1&&state[r*3+1]==2&&state[r*3+2]==2)return true;
		if (state[r*3]==2&&state[r*3+1]==2&&state[r*3+2]==1)return true;
	}
	F0R(c, 3){
		if (state[c]==1&&state[c+3]==2&&state[c+6]==2)return true;
		if (state[c]==2&&state[c+3]==2&&state[c+6]==1)return true;
	}
	if (state[0]==1&&state[4]==2&&state[8]==2) return true;
	if (state[0]==2&&state[4]==2&&state[8]==1) return true;
	if (state[2]==1&&state[4]==2&&state[6]==2) return true;
	if (state[2]==2&&state[4]==2&&state[6]==1) return true;
	return false;
}
bool isFull(int mask){
	vi state;
	while(mask||sz(state)<9){
		state.pb(mask%3);
		mask/=3;
	}
	reverse(all(state));
	F0R(i, 9) if (!state[i])return false;
	return true;
}

void dfs(int r, int c, int mask){
		if (r<0||c<0||r>=n||c>=n) return;
		if (grid[r][c][0] == '#') return;
		if (grid[r][c][0] != '.' && grid[r][c][0] != 'B'){
			auto [cc, i, j] = grid[r][c]; i-= '0', j -= '0';
			vi state;
			while(mask||sz(state)<9){
				state.pb(mask%3);
				mask/=3;
			}
			reverse(all(state));
			if (!state[3*(i-1)+j-1]) state[3*(i-1)+j-1] = (cc == 'M'? 1:2);
			int val = 1;
			R0F(i, 9) mask += val*state[i], val*=3;
		}
		if (vis[r][c][mask]) return;
		vis[r][c][mask] = 1;
		if (W[mask]){
			ans.insert(mask);
			return;
		}
		if (Full[mask]) return;
		F0R(i,4){
			int nr = r + dx[i], nc = c + dy[i];
			dfs(nr, nc, mask);
		}
	};

void solve()
{
	cin >> n;
	F0R(i, n)F0R(j, n) {auto&[a,b,c] = grid[i][j]; cin >> a >> b >> c;}
	int str = 0, stc = 0;
	int board{};
	F0R(i, n)F0R(j, n) if (grid[i][j][0]=='B') str=i, stc=j;
	F0R(i, 19863){
		W[i] = hasWon(i);
		Full[i] = isFull(i);
	}
	dfs(str, stc, board);
	cout << sz(ans);
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