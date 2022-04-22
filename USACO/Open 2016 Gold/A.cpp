// Problem: Problem 1. Splitting the Field
// Contest: USACO - USACO 2016 US Open Contest, Gold
// URL: http://www.usaco.org/index.php?page=viewproblem2&cpid=645
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

void solve()
{
	int n;
	cin >> n;
	ll tot = 0, x1 = INF, x2 = 0, y1 = INF, y2 = 0;
	vpl Point(n);
	vl xxx, yyy, L, R, T, B;
	for (auto &[x, y]:Point){
		cin >> x >> y;
		ckmin(x1, x), ckmin(y1, y);
		ckmax(x2, x), ckmax(y2, y);
		xxx.pb(x), yyy.pb(y);
	}
	tot = (x2-x1)*(y2-y1);
	ll res = tot;
	sort(all(xxx)); sort(all(yyy));
	xxx.resize(unique(all(xxx))-xxx.begin());
	yyy.resize(unique(all(yyy))-yyy.begin());
	L.resize(sz(xxx)), R.resize(sz(xxx));
	T.resize(sz(yyy)), B.resize(sz(yyy));
	sort(all(Point));
	x1 = INF, x2 = 0, y1 = INF, y2 = 0;
	int j = 0;
	F0R(i, sz(xxx)){
		while(j<n&&Point[j].fi==xxx[i]){
			auto [x, y] = Point[j];
			ckmin(x1, x), ckmin(y1, y);
			ckmax(x2, x), ckmax(y2, y);
			j++;
		}
		L[i] = (x2-x1)*(y2-y1);
	}
	x1 = INF, x2 = 0, y1 = INF, y2 = 0;
	j = n-1;
	R0F(i, sz(xxx)){
		while(j>=0&&Point[j].fi==xxx[i]){
			auto [x, y] = Point[j];
			ckmin(x1, x), ckmin(y1, y);
			ckmax(x2, x), ckmax(y2, y);
			j--;
		}
		R[i] = (x2-x1)*(y2-y1);
	}
	sort(all(Point), [&](pii p, pii q){
		return p.se<q.se;
	});
	x1 = INF, x2 = 0, y1 = INF, y2 = 0;
	j = 0;
	F0R(i, sz(yyy)){
		while(j<n&&Point[j].se==yyy[i]){
			auto [x, y] = Point[j];
			ckmin(x1, x), ckmin(y1, y);
			ckmax(x2, x), ckmax(y2, y);
			j++;
		}
		B[i] = (x2-x1)*(y2-y1);
	}
	x1 = INF, x2 = 0, y1 = INF, y2 = 0;
	j = n-1;
	R0F(i, sz(yyy)){
		while(j>=0&&Point[j].se==yyy[i]){
			auto [x, y] = Point[j];
			ckmin(x1, x), ckmin(y1, y);
			ckmax(x2, x), ckmax(y2, y);
			j--;
		}
		T[i] = (x2-x1)*(y2-y1);
	}
	F0R(i, sz(xxx)) if (i+1<sz(xxx)) ckmin(res,L[i]+R[i+1]);
	F0R(i, sz(yyy)) if (i+1<sz(yyy)) ckmin(res,B[i]+T[i+1]);
	cout << tot - res;
}

int main()
{
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);
    int testcase=1;
    // cin >> testcase;
    #ifndef LOCAL
    	setIO("split");
    #endif
    while (testcase--)
    {
        solve();
    }
}