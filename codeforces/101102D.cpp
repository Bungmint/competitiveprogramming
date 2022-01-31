// Problem: D. Rectangles
// Contest: Codeforces - 2016 ACM Amman Collegiate Programming Contest
// URL: https://codeforces.com/gym/101102/problem/D
// Memory Limit: 256 MB
// Time Limit: 5000 ms
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

int grid[1000][1000];

void solve()
{
	int r,c;
	cin >> r >> c;
	F0R(i, r) F0R(j, c)cin >> grid[i][j];
	vector<vi> maxC(r, vi(c));
	F0R(j, c) F0R(i, r){
		if (i==0){
			maxC[i][j] = 1;
		}else{
			maxC[i][j] = (grid[i-1][j]==grid[i][j]? maxC[i-1][j]+1:1);
		}
	}
	dbg(maxC);
	ll ans = 0;
	F0R(i, r){// Top row
		stack<int> s1,s2;
		vi L(c), R(c), dupe(c, -1);
		F0R(j, c){
			while(sz(s1)&&maxC[i][s1.top()]>=maxC[i][j]&&grid[i][s1.top()]==grid[i][j]){
				if (maxC[i][s1.top()]==maxC[i][j]) {dupe[j]=s1.top();break;}
				s1.pop();
			}
			L[j] = (sz(s1)? s1.top():-1);
			s1.push(j);
		}
		R0F(j, c){
			while(sz(s2)&&maxC[i][s2.top()]>=maxC[i][j]&&grid[i][s2.top()]==grid[i][j]){
				s2.pop();
			}
			R[j] = (sz(s2)? s2.top():c);
			s2.push(j);
		}
		dbg(L, R);
		F0R(j, c){
			if (dupe[j]==-1){
				ans += (ll)(R[j]-j)*(ll)(j-L[j])*(maxC[i][j]);
			}else{
				ans += (ll)(R[j]-j)*(ll)(j-dupe[j])*(maxC[i][j]);
			}
		}
	}
	cout << ans << "\n";
}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int testcase=1;
    cin >> testcase;
    while (testcase--)
    {
        solve();
    }
}