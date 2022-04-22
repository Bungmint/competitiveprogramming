// Problem: F. Quadratic Set
// Contest: Codeforces - Educational Codeforces Round 120 (Rated for Div. 2)
// URL: https://codeforces.com/contest/1622/problem/F
// Memory Limit: 256 MB
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
mt19937_64 rng(chrono::steady_clock::now().time_since_epoch().count());
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

using ull = unsigned long long;
const int N = 1e6; // Only advised to use it under 1e7 (More Memory)
int lp[N + 1];
ull hsh[N + 1];
vector<int> pr;
void precalc()
{
    for (int i = 2; i <= N; i++)
    {
        if (lp[i] == 0)
        {
            lp[i] = i;
            pr.push_back(i);
        }
        for (int j = 0; j < (int)pr.size() && pr[j] <= lp[i] && i * pr[j] <= N; ++j)
        {
            lp[i * pr[j]] = pr[j];
        }
    }
    for (auto &e : pr) {
    	hsh[e] = rng();
    }
}

void solve()
{
	int n;
	cin >> n;
	ull totH = 0;
	map<ull, int> mp;
	vector<ull> h(n + 1);
	FOR(i, 1, n + 1) {
		int x = i;
		h[i] = h[i - 1];
		while (x > 1) {
			int p = lp[x];
			int c = 0;
			while (x % p == 0) x /= p, h[i] ^= hsh[p];
		}
		totH ^= h[i];
		mp[h[i]] = i;
	}
	ull tot{};
	if (totH == 0) {
		cout << n << '\n';
		FOR(i, 1, n + 1) cout << i << ' ';
		return;
	}
	FOR(i, 1, n + 1) {
		if (h[i] == totH) {
			cout << n - 1 << '\n';
			FOR(j, 1, i) cout << j << ' ';
			FOR(j, i + 1, 1 + n) cout << j << ' ';
			return;
		}
	}
	// ull tot{};
	FOR(i, 1, n + 1) {
		ull x = h[i] ^ totH;
		if (mp.count(x) && mp[x] != i) {
			cout << n - 2 << '\n';
			dbg(x ^ h[i], totH);
			int cnt = 0;
			FOR(j, 1, n + 1) {
				if (j == i || j == mp[x]) continue;
				cout << j << ' ';
				// tot ^= h[j];
			}
			dbg(tot, i, mp[x]);
			return;
		}
	}
	//
	cout << n - 3 << '\n';
	FOR(i, 1, n + 1) {
		if (i == 2 || i == (n - 1) / 2 || i == n) continue;
		cout << i << ' ';
	}
}

int main()
{
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);
    int testcase=1;
    // cin >> testcase;
    precalc();
    while (testcase--)
    {
        solve();
    }
}