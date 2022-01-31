// Problem: D2. Mocha and Diana (Hard Version)
// Contest: Codeforces - Codeforces Round #738 (Div. 2)
// URL: https://codeforces.com/contest/1559/problem/D2
// Memory Limit: 256 MB
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

// From the USACO tutorial lol
struct DSU {
	vector<int> e;
	vector<int> mem;
	vector<pair<pii,pii>> ev;
	DSU(int N) { e = vector<int>(N, -1); }

	// get representive component (uses path compression)
	// To use rollback, disable path compression
	int get(int x) { return e[x] < 0 ? x : e[x] = get(e[x]); }
	
	bool same_set(int a, int b) { return get(a) == get(b); }
	
	int size(int x) { return -e[get(x)]; }
	
	bool unite(int x, int y) {  // union by size
		x = get(x), y = get(y);
		if (x == y) return false;
		ev.pb({{x, e[x]}, {y,e[y]}});
		if (e[x] > e[y]) swap(x, y);
		e[x] += e[y]; e[y] = x;
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
		}
	}
};

void solve()
{
	int n, m1, m2;
	cin >> n>>m1 >>m2;
	vpi ans;
	DSU dsu1(n), dsu2(n);
	stack<int> s1, s2;
	REP(m1){
		int u, v;
		cin  >> u >> v;
		u--,v--;
		dsu1.unite(u,v);
	}
	REP(m2){
		int u, v;
		cin  >> u >> v;
		u--,v--;
		dsu2.unite(u, v);
	}
	F0R(i, n){
		if (!dsu1.same_set(0, i)&&!dsu2.same_set(0,i)) dsu1.unite(0, i), dsu2.unite(0,i), ans.pb({0,i});
	}
	F0R(i, n){
		if (dsu1.same_set(0,i)&&!dsu2.same_set(0,i)) s1.push(i);
		else if (dsu2.same_set(0,i)&&!dsu1.same_set(0,i)) s2.push(i);
	}
	while(sz(s1)&&sz(s2)){
		int x = s1.top(), y = s2.top();
		dbg(x,y);
		if (dsu2.same_set(0, x)&&dsu1.same_set(0,x)){ s1.pop();continue;}
		if (dsu1.same_set(0, y)&&dsu2.same_set(0,y)){ s2.pop(); continue;}
		if (!dsu2.same_set(0,x)&&!dsu1.same_set(0,y)) ans.pb({x,y}), dsu1.unite(x,y), dsu2.unite(x,y), s1.pop(), s2.pop();
	}
	
	
	
	cout << sz(ans)<<"\n";
	for (auto [x,y]: ans) cout << x+1 << " "<< y+1 << "\n";
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