// Problem: B. Nastya and Scoreboard
// Contest: Codeforces - Codeforces Round #637 (Div. 1) - Thanks, Ivan Belonogov!
// URL: https://codeforces.com/contest/1340/problem/B
// Memory Limit: 256 MB
// Time Limit: 1000 ms
// 
// Powered by CP Editor (https://cpeditor.org)

#pragma GCC optimize("O3")
#pragma GCC target("sse4")
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

string s[] = {"1110111", "0010010", "1011101", "1011011", "0111010", "1101011", "1101111", "1010010", "1111111", "1111011"};
int digit[10];
pii dp[2001][2001];
pii par[2001][2001];
void solve()
{
	int n, K;
	cin >> n >> K;
	F0R(i, 2001) F0R(j, 2001) dp[i][j] = {-1, -1};
	dp[0][0] = {0,0};
	FOR(i, 1, n+1){
		string t;
		cin >> t;
		vpi tt;
		F0R(j, K+1) tt.pb(dp[i-1][j]);
		sort(all(tt));
		int mask = 0;
		F0R(j, sz(t)){
			mask += (t[j]-'0')*(1<<(sz(t)-1-j));
		}
		F0R(j, 10){
			if ((digit[j]&mask)!=mask) continue;
			int cnt = __builtin_popcount((digit[j]^mask));
			dbg(cnt);
			F0R(k, K+1){
				if (cnt+k>K) break;
				if (dp[i-1][k].fi==-1) continue;
				pii &res = dp[i][cnt+k];
				int id = lb(all(tt), dp[i-1][k])-begin(tt);
				if (ckmax(res.fi, id)){
					res.se = j;
					par[i][cnt+k] = {i-1, k};
				}else if (res.fi==id&&ckmax(res.se,j)) par[i][cnt+k] = {i-1, k};
			}
		}
	}
	pii ans = dp[n][K];
	if (ans.fi==-1){
		cout << -1 << "\n";
		return;
	}
	vi num;
	int pos = n, x = K;
	while(pos){
		num.pb(dp[pos][x].se);
		tie(pos, x) = par[pos][x];
	}
	reverse(all(num));
	assert(sz(num)==n);
	F0R(i, sz(num)) cout << num[i];
}

int main()
{
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);
    F0R(i, 10){
    	F0R(j, sz(s[i])){
    		digit[i] += (s[i][j]-'0')*(1<<(sz(s[i])-j-1));
    	}
    	dbg(digit[i]);
    }
    int testcase=1;
    // cin >> testcase;
    while (testcase--)
    {
        solve();
    }
}