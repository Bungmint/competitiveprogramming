// Problem: F2. Nearest Beautiful Number (hard version)
// Contest: Codeforces - Codeforces Round #739 (Div. 3)
// URL: https://codeforces.com/contest/1560/problem/F2
// Memory Limit: 256 MB
// Time Limit: 1000 ms
// 
// Powered by CP Editor (https://cpeditor.org)

#pragma GCC optimize("Ofast")
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
#define dbg(...)
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

int dp[1024][11][2];
int popcount[1024];
vi num;
int n, k;
int power[10];

int dping(int pos, bool flag, int mask){
	int&res = dp[mask][pos][flag];
	if (res!=-1) return res;
	if (popcount[mask]>k) return res = 2*INF;
	if (pos==sz(num)){
		return res = 0;
	}
	int LMT = (flag? 0:num[pos]);
	res = 2*INF;
	
		FOR(i, LMT, 10){
		int v = dping(pos+1, flag|(i>LMT),( mask|(1LL<<i)));
		if (v!=2*INF&&!(i>=2&&sz(num)-pos-1==9)&&ckmin(res, v+power[sz(num)-pos-1]*i)) return res;
		}
	
	return res;
}

void solve()
{
	cin >> n >> k;
	num.clear();
	set<int> st;
	int n1 = n;
	while(n){
		num.pb(n%10);
		st.insert(n%10);
		n/=10;
	}
	if (sz(st)<=k){
		cout << n1 << "\n";
		return;
	}
	memset(dp, -1, sizeof(dp));
	reverse(all(num));
	cout << dping(0, 0, 0)<<"\n";
}

signed main()
{
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);
    power[0] = 1;
    F0R(i, 1024) popcount[i] = __builtin_popcount(i);
    FOR(i,1, 10) power[i] = power[i-1]*10;
    int testcase=1;
    cin >> testcase;
    while (testcase--)
    {
        solve();
    }
}