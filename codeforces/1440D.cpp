// Problem: D. Graph Subset Problem
// Contest: Codeforces - Codeforces Round #684 (Div. 2)
// URL: https://codeforces.com/contest/1440/problem/D
// Memory Limit: 256 MB
// Time Limit: 1000 ms
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

ll nC2(int x){
	if (x<0) return 0;
	return 1LL*x*(x-1)/2LL;
}

void solve()
{
	int n, m, k;
	cin >> n >> m >> k;
	vector<vi> g(n+1);
	REP(m){
		int x, y;
		cin >> x>> y;
		g[x].pb(y), g[y].pb(x);
	}
	FOR(i, 1, n+1) sort(all(g[i]));
	if (k==1){
		cout <<2 << "\n"<< 1 << "\n";
		return;
	}else if (k==2){
		FOR(i, 1, n+1){
			if (sz(g[i])){
				cout <<2 << "\n";
				cout << i << " "<< g[i][0]<<"\n";
				return;
			}
		}
	}
	if (nC2(k)>m){
		cout << -1 << "\n";
		return;
	}
	vi deg(n+1);
	set<pii> st;
	FOR(i,1,n+1){
		deg[i] = sz(g[i]);
		st.insert({sz(g[i]), i});
	}
	vector<bool> erased(n+1);
	while(sz(st)){
		auto [d, v] = *st.begin();
		st.erase({d,v});
		if (d>=k){
			vi ans = {v};
			for (auto [x, y]: st) ans.pb(y);
			cout << 1 << " "<< sz(ans)<<"\n";
			for (auto x:ans)cout << x << " ";
			cout << "\n";
			return;
		}
		if (d==k-1){
			vi check = {v};
			for (auto &e:g[v]){
				if (!erased[e]) check.pb(e);
			}
			dbg(check);
			bool ok = 1;
			F0R(i, sz(check))F0R(j, i){
				auto it = lb(all(g[check[i]]), check[j]);
				if (it==g[check[i]].end()||*it!=check[j]) ok = 0;
			}
			if (ok){
				cout << 2 << "\n";
				F0R(i, sz(check)) cout << check[i]<<" ";
				cout << "\n";
				return;
			}
		}
		for (auto &e:g[v]){
			if (erased[e]) continue;
			auto it = st.lb({deg[e], e});
			if (it==st.end()||it->se!=e) continue;
			st.erase(it);
			deg[e]--;
			st.insert({deg[e], e});
		}
		erased[v] = 1;
	}
	cout << -1 << "\n";
	
	
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