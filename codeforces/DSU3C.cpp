// Problem: C. Dynamic Connectivity Offline
// Contest: Codeforces - ITMO Academy: pilot course - Disjoint Sets Union - Step 3
// URL: https://codeforces.com/edu/course/2/lesson/7/3/practice/contest/289392/problem/C
// Memory Limit: 256 MB
// Time Limit: 4000 ms
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

// From the USACO tutorial lol
struct DSU {
	vector<int> e;
	vector<int> mem;
	vector<int> prevCC;
	vector<pair<pii,pii>> ev;
	int cc;
	DSU(int N) { e = vector<int>(N, -1); cc = N;}

	// get representive component (uses path compression)
	// To use rollback, disable path compression
	int get(int x) { return e[x] < 0 ? x : get(e[x]); }
	
	bool same_set(int a, int b) { return get(a) == get(b); }
	
	int size(int x) { return -e[get(x)]; }
	
	bool unite(int x, int y) {  // union by size
		x = get(x), y = get(y);
		if (x == y) return false;
		ev.pb({{x, e[x]}, {y,e[y]}});
		prevCC.pb(cc);
		if (e[x] > e[y]) swap(x, y);
		e[x] += e[y]; e[y] = x;
		cc--;
		return true;
	}
	
	void snapshot(){
		mem.pb(sz(ev));
	}
	
	void rollback(){
		if (mem.empty())return;
		int SZ = mem.back();
		mem.pop_back();
		while(sz(ev)!=SZ){
			pair<pii,pii> p = ev.back();
			e[p.fi.fi] = p.fi.se;
			e[p.se.fi] = p.se.se;
			ev.pop_back();
			cc = prevCC.back();
			prevCC.pop_back();
		}
	}
};

const int MN = 3e5+1;
int ans[MN];

void dc(int l, int r, vi& q1, vector<ar<int,4>>& q2, DSU& dsu){
	if (sz(q1)==0) return;
	if (l+1==r){
		for (auto &q: q1){
			if (q==l) ans[q] = dsu.cc;
		}
		return;
	}
	dsu.snapshot();
	int m = (l+r)/2;
	vector<int> nxt1, nxt3;
	vector<ar<int,4>> nxt2, nxt4;
	for (auto& x:q1){
		if (l<=x&&x<m) nxt1.pb(x);
		if (m<=x&&x<r) nxt3.pb(x);
	}
	for (auto& [u,v,L,R]: q2){
		if (L<=l&&m<=R) {dsu.unite(u, v);continue;}
		if (R>l&&m>L) nxt2.pb({u,v,L,R});
	}
	dc(l, m, nxt1, nxt2, dsu);
	dsu.rollback();
	dsu.snapshot();
	for (auto& [u,v,L,R]: q2){
		if (L<=m&&r<=R) {dsu.unite(u, v);continue;}
		if (R>m&&r>L) nxt4.pb({u,v,L,R});
	}
	dc(m, r, nxt3, nxt4, dsu);
	dsu.rollback();
}

void solve()
{
	int n, m;
	cin >> n >> m;
	DSU dsu(n);
	unordered_map<pii, int, chash> mp;
	vector<int> q1;
	vector<ar<int,4>> q2;
	F0R(i, m){
		char c;
		cin >> c;
		if (c=='?'){
			q1.pb(i);
		}else{
			int u,v;
			cin >> u >> v; u--, v--;
			if (u>v) swap(u, v);
			if (c=='+'){
				mp[{u, v}] = i;
			}else{
				q2.pb({u, v, mp[{u,v}], i+1});
				mp.erase({u,v});
			}
		}
	}
	for (auto x:mp){
		auto [u, v] = x.fi;
		q2.pb({u, v, x.se, INF});
	}
	dc(0, m, q1, q2, dsu);
	F0R(i, m){
		if (ans[i]) cout << ans[i]<<"\n";
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