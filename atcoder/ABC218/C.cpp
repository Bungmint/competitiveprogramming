// Problem: C - Shapes
// Contest: AtCoder - AtCoder Beginner Contest 218
// URL: https://atcoder.jp/contests/abc218/tasks/abc218_c
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
char s[201][201], t[201][201], tmp[201][201]; 
int n;


void rotate(){
	F0R(i, n)F0R(j, n){
		tmp[j][n-i-1] = s[i][j];
	}
	F0R(i, n){
		F0R(j, n) s[i][j] = tmp[i][j];
	}
}
bool check(){
	int sCnt = 0, sId = 0, tCnt = 0, tId = 0;
	F0R(i, n){
		int cnt1 = 0;
		int cnt2 = 0;
		F0R(j, n){
			if (s[i][j]=='#') cnt1++;
			if (t[i][j]=='#') cnt2++;
		}
		if (!sCnt&&cnt1) sCnt = cnt1, sId = i;
		if (!tCnt&&cnt2) tCnt = cnt2, tId = i;
	}
	if (sCnt!=tCnt) return 0;
	int x = sId - tId;
	sCnt = tCnt = 0;
	F0R(j, n){
		int cnt1 = 0;
		int cnt2 = 0;
		F0R(i, n){
			if (s[i][j]=='#') cnt1++;
			if (t[i][j]=='#') cnt2++;
		}
		if (!sCnt&&cnt1) sCnt = cnt1, sId = j;
		if (!tCnt&&cnt2) tCnt = cnt2, tId = j;
	}
	if (sCnt!=tCnt) return 0;
	int y = sId - tId;
	dbg(x, y);
	F0R(i, n)F0R(j, n){
		if (t[i][j]=='#'){
			dbg(i, j);
			if (i+x<0||j+y<0||s[i+x][j+y]!='#') return 0;
		}
	}
	
	return 1;
}

void solve()
{
	cin >>n;
	F0R(i, n) F0R(j, n){
		cin >> s[i][j];
	}
	F0R(i, n) F0R(j, n){
		cin >>t[i][j];
	}
	bool ok = 0;
	F0R(i, 4){
		rotate();
		ok |= check();
	}
	
	cout << (ok? "Yes":"No");
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