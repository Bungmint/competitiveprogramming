// Problem: D. Professional layer
// Contest: Codeforces - Codeforces Round #534 (Div. 1)
// URL: https://codeforces.com/contest/1103/problem/D
// Memory Limit: 512 MB
// Time Limit: 3000 ms
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


const int N = 1e6; // Only advised to use it under 1e7 (More Memory)
int e[N];
ll a[N];
ar<ll, 12> stor[N];
set<pii> minmask[1 << 11];
vi best[N];
ll dp[12][1 << 11];



void solve()
{
	memset(dp, 0x3f, sizeof(ll) * 12 * (1 << 11));
	dp[0][0] = 0;
	ll n, k;
	cin >> n >> k;
	ll g = -1;
	F0R(i, n) {
		cin >> a[i];
		if (g == -1) g = a[i];
		else g = gcd(g, a[i]);
	}
	F0R(i, n) cin >> e[i];
	if (g == 1) {
		cout << 0 << '\n';
		return;
	}
	vl primes;
	for (ll p = 2; p * p <= g; p++) {
		if (g % p == 0) {
			while (g % p == 0) g /= p;
			primes.pb(p);
		}
	}
	if (g > 1) primes.pb(g);
	F0R(i, n) {
		ll x = a[i];
		int co{};
		for (auto &p : primes) {
			ll pp = 1;
			while (x % p == 0) {
				x /= p;
				pp *= p;
			}
			stor[i][co++] = pp;
		}
		stor[i][sz(primes)] = e[i];
	}
	sort(stor, stor + n);
	F0R(i, n) {
		vector<int> todo = {i};
		ar<ll, 12> cur = stor[i];
		while (i + 1 < n) {
			bool ok = 1;
			F0R(j, sz(primes)) {
				ok &= (stor[i][j] == stor[i + 1][j]);
			}
			if (!ok) break;
			if (sz(todo) < sz(primes)) todo.pb(i + 1);
			i++;
		}
		FOR(mask, 1, 1 << sz(primes)) {
			ll x = 1;
			F0R(j, sz(primes)) {
				if (mask & (1 << j)) x *= cur[j];
			}
			if (x <= k) {
				dbg(x, mask, todo);
				for (auto &v : todo) {
					if (sz(minmask[mask]) < sz(primes)) minmask[mask].insert({stor[v][sz(primes)], v});
					else if ((*--minmask[mask].end()).fi > stor[v][sz(primes)]) {
						minmask[mask].erase(--minmask[mask].end());
						minmask[mask].insert({stor[v][sz(primes)], v});
					}
				}
			}
		}
	}
	F0R(mask, 1 << sz(primes)) {
		for (auto &[ex, id] : minmask[mask]) {
			best[id].pb(mask);
		}
	}
	F0R(i, n) {
		if (sz(best[i]) == 0) continue;
		dbg(best[i]);
		ROF(s, 1, sz(primes) + 1) {
			for (auto &nmask : best[i]) {
				int all = (1 << sz(primes)) - 1 - nmask;
				dbg(all);
				for (int mask = all; ; mask = (mask - 1) & all) {
					ckmin(dp[s][mask ^ nmask], dp[s - 1][mask] + stor[i][sz(primes)]);
					if (mask == all && dp[s][mask ^ nmask] < LINF) dbg(dp[s][mask ^ nmask]);
					if (mask == 0) break;
				}
			}
		}
	}
	ll ans{LINF};
	FOR(i, 1, 1 + sz(primes)) {
		if (dp[i][(1 << sz(primes)) - 1] < LINF) {
			ckmin(ans, 1LL * i * dp[i][(1 << (sz(primes))) - 1]);
		}
	}
	cout << (ans == LINF ? -1 : ans) << '\n';
}

int32_t main()
{
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);
    int testcase=1;
    // cin >> testcase;
    // linsieve();
    // debug();
    // calc();
    while (testcase--)
    {
        solve();
    }
}