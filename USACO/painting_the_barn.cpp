// Problem: Problem 3. Painting the Barn
// Contest: USACO - USACO 2019 February Contest, Gold
// URL: http://www.usaco.org/index.php?page=viewproblem2&cpid=923
// Memory Limit: 256 MB
// Time Limit: 4000 ms
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

int cnt[201][201], prefX[201][201], prefY[201][201];
int xF[201], xB[201], yF[201], yB[201];


void solve()
{
	int n, k;
	cin >> n >> k;
	F0R(i,n){
		int x, y, z, w;
		cin >> x >> y >> z >> w;
		z--, w--;
		cnt[x][y]++;
		if(w+1<=199) cnt[x][w+1]--;
		if (z+1<=199) cnt[z+1][y]--;
		if (z+1<=199&&w+1<=199) cnt[z+1][w+1]++;
	}
	F0R(i, 200)F0R(j, 200){
		if (i) cnt[i][j] += cnt[i-1][j];
		if (j) cnt[i][j] += cnt[i][j-1];
		if (i&&j) cnt[i][j]-=cnt[i-1][j-1];
	}
	int total = 0;
	F0R(i, 200)F0R(j, 200){
		if (cnt[i][j]==k-1) cnt[i][j] = 1;
		else if (cnt[i][j]==k) cnt[i][j] = -1, total++;
		else cnt[i][j] = 0;
		prefX[i][j] = cnt[i][j];
		prefY[i][j] = cnt[i][j];
		if (i) prefX[i][j] += prefX[i-1][j];
		if (j) prefY[i][j] += prefY[i][j-1];
	}
	// Forward
	int mx = 0;
	F0R(x, 200){
		F0R(L, x+1){
			int sum = 0;
			F0R(y, 200){
				int k = prefX[x][y];
				if (L) k-= prefX[L-1][y];
				sum = max(0, sum + k);
				ckmax(mx, sum);
			}
		}
		xF[x] = mx;
		dbg(mx);
	}
	mx = 0;
	R0F(x, 200){
		FOR(L, x, 200){
			int sum = 0;
			F0R(y, 200){
				int k = prefX[L][y];
				if (x) k-= prefX[x-1][y];
				sum = max(0, sum + k);
				ckmax(mx, sum);
			}
		}
		xB[x] = mx;
		dbg(xB[x], xF[x]);
	}
	mx = 0;
	F0R(x, 200){
		F0R(L, x+1){
			int sum = 0;
			F0R(y, 200){
				int k = prefY[y][x];
				if (L) k-= prefY[y][L-1];
				sum = max(0, sum + k);
				ckmax(mx, sum);
			}
		}
		yF[x] = mx;
	}
	mx = 0;
	R0F(x, 200){
		FOR(L, x, 200){
			int sum = 0;
			F0R(y, 200){
				int k = prefY[y][L];
				if (x) k-= prefY[y][x-1];
				sum = max(0, sum + k);
				ckmax(mx, sum);
			}
		}
		yB[x] = mx;
	}
	int ans = 0;
	F0R(x, 201){
		if (x==0) ckmax(ans, max(xB[0], yB[0]));
		else if (x==200) ckmax(ans, max(yF[0], xF[0]));
		else{
			ckmax(ans, max(yF[x-1]+yB[x], xF[x-1]+xB[x]));
		}
	}
	dbg(ans);
	cout << ans+total << "\n";
	
	
}

int main()
{
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);
    int testcase=1;
    #ifndef LOCAL
    	setIO("paintbarn");
    #endif
    // cin >> testcase;
    while (testcase--)
    {
        solve();
    }
}