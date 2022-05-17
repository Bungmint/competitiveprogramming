// Problem: E. Frequency Queries
// Contest: Codeforces - Codeforces Round #759 (Div. 2, based on Technocup 2022 Elimination Round 3)
// URL: https://codeforces.com/contest/1591/problem/E
// Memory Limit: 512 MB
// Time Limit: 4000 ms
// 
// Powered by CP Editor (https://cpeditor.org)

//Copyright © 2022 Youngmin Park. All rights reserved.
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
template <typename T, size_t SZ>
using ar = array<T, SZ>;

#define all(v) (v).begin(), (v).end()
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

inline namespace RecursiveLambda{
	template <typename Fun>
	struct y_combinator_result{
		Fun fun_;
		template <typename T> 
		explicit y_combinator_result(T &&fun): fun_(forward<T>(fun)){}
		template <typename...Args>
		decltype(auto) operator()(Args &&...args){
			return fun_(ref(*this), forward<Args>(args)...);
		}
	};
	template <typename Fun>
	decltype(auto) y_combinator(Fun &&fun){
		return y_combinator_result<decay_t<Fun>>(forward<Fun>(fun));
	}
};

void setIO(string s) // USACO
{
	#ifndef LOCAL
	    freopen((s + ".in").c_str(), "r", stdin);
	    freopen((s + ".out").c_str(), "w", stdout);
	#endif
}

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

const int N = 1e6 + 100;
int a[N];
vi adj[N];
int ans[N];
int freq[N];
unordered_set<int, chash> st[N];
vector<ar<int, 3>> query[N];
int x;

// Uses zero index for the input
template<typename T, int N>
struct BIT{
	int lg = log2(N);
	T bit[N + 1];
	void upd(int i, T v){ 
		for (++i; i <= N; i += i & -i) bit[i] += v;	
	}
	T query(int i){
		T res = 0;
		for (++i; i > 0; i -= i & -i) res += bit[i];
		return res;
	}
	T range_query(int l, int r) {
		return query(r) - query(l - 1);
	}
	int lower_bound(T v){
		T sum = 0, id = 0;
		R0F(i, lg + 1){
			if (id + (1 << i) <= N && sum + bit[id + (1 << i)] < v){
				sum += bit[id + (1 << i)];
				id += (1 << i);
			}
		}
		return id; // Zero index
		// return id+1; // One index
	}
};

BIT<ll, N> bit;


void add(int x) {
	st[freq[x]].erase(x);
	bit.upd(freq[x], -1);
	freq[x]++;
	bit.upd(freq[x], 1);
	st[freq[x]].insert(x);
}
void remove(int x) {
	st[freq[x]].erase(x);
	bit.upd(freq[x], -1);
	freq[x]--;
	bit.upd(freq[x], 1);
	st[freq[x]].insert(x);
}
void dfs(int u, int pu) {
	add(a[u]);
	for (auto &[l, k, id] : query[u]) {
		int q = bit.range_query(0, l - 1);
		dbg(u, pu, q, k, x);
		if (q + k > x) ans[id] = -1;
		else {
			ans[id] = *st[bit.lb(q + k)].begin();
		}
	}
	for (auto &e : adj[u]) {
		if (e != pu) {
			dfs(e, u);
		}
	}
	remove(a[u]);
}

void solve()
{
	int n, q;
	cin >> n >> q;
	set<int> s;
	F0R(i, n) cin >> a[i], st[0].insert(a[i]), s.insert(a[i]);
	bit.upd(0, sz(s));
	x = sz(s);
	FOR(i, 1, n) {
		int p;
		cin >> p;
		p--;
		adj[p].pb(i), adj[i].pb(p);
	}
	F0R(i, q) {
		int v, l, k;
		cin >> v >> l >> k;
		v--;
		query[v].pb({l, k, i});
	}
	dfs(0, -1);
	F0R(i, q) cout << ans[i] << ' ';
	cout << "\n";
	bit.upd(0, -sz(s));
	F0R(i, n) adj[i].clear(), query[i].clear(), freq[a[i]] = 0;
	st[0].clear();
	
}

int main()
{
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);
    int testcase=1;
    cin >> testcase;
    while (testcase--)
    {
        solve();
    }
}