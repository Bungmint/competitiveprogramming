// Copyright © 2022 Youngmin Park. All rights reserved.
//#pragma GCC optimize("O3")
//#pragma GCC target("avx2")
#include <bits/stdc++.h>
using namespace std;

#pragma region TEMPLATE

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
template <typename T>
using pqg = priority_queue<T, vector<T>, greater<T>>;

#define all(v) (v).begin(), (v).end()
#define pb push_back
#define eb emplace_back
#define sz(x) (int)(x).size()
#define fi first
#define se second
#define lb lower_bound
#define ub upper_bound

constexpr int INF = 1e9;
constexpr ll LINF = 1e18;
const ld PI = acos((ld)-1.0);
constexpr int dx[4] = {1, 0, -1, 0}, dy[4] = {0, 1, 0, -1};
mt19937_64 rng(chrono::steady_clock::now().time_since_epoch().count());
template <typename T>
constexpr bool ckmin(T &a, const T &b) { return b < a ? a = b, 1 : 0; }
template <typename T>
constexpr bool ckmax(T &a, const T &b) { return b > a ? a = b, 1 : 0; }
ll cdiv(ll a, ll b) { return a / b + ((a ^ b) > 0 && a % b); } // divide a by b rounded up
ll fdiv(ll a, ll b) { return a / b - ((a ^ b) < 0 && a % b); } // divide a by b rounded down

#ifdef LOCAL
#include "miscellaneous/debug.h"
#else
#define dbg(...) 42
#endif

inline namespace RecursiveLambda {
	template <typename Fun>
	struct y_combinator_result {
		Fun fun_;
		template <typename T>
		explicit constexpr y_combinator_result(T &&fun) : fun_(forward<T>(fun)) {}
		template <typename... Args>
		constexpr decltype(auto) operator()(Args &&...args) const {
			return fun_(ref(*this), forward<Args>(args)...);
		}
	};
	template <typename Fun>
	decltype(auto) y_combinator(Fun &&fun) {
		return y_combinator_result<decay_t<Fun>>(forward<Fun>(fun));
	}
};

#pragma endregion TEMPLATE


/**
 * Description: modular arithmetic operations 
 * Source: 
	* KACTL
	* https://codeforces.com/blog/entry/63903
	* https://codeforces.com/contest/1261/submission/65632855 (tourist)
	* https://codeforces.com/contest/1264/submission/66344993 (ksun)
	* also see https://github.com/ecnerwala/cp-book/blob/master/src/modnum.hpp (ecnerwal)
 * Verification: 
	* https://open.kattis.com/problems/modulararithmetic
 */

template<int MOD, int RT> struct mint {
	static constexpr int mod = MOD;
	static constexpr mint rt() { return RT; } // primitive root for FFT
	int v; explicit operator int() const { return v; } // explicit -> don't silently convert to int
	constexpr mint() { v = 0; }
	constexpr mint(ll _v) noexcept { v = int((-MOD < _v && _v < MOD) ? _v : _v % MOD);
		if (v < 0) v += MOD; }
	constexpr bool operator==(const mint& o) const noexcept{
		return v == o.v; }
	constexpr friend bool operator!=(const mint& a, const mint& b) noexcept { 
		return !(a == b); }
	constexpr friend bool operator<(const mint& a, const mint& b) noexcept { 
		return a.v < b.v; }
	
	constexpr mint& operator+=(const mint& m) noexcept { 
		if ((v += m.v) >= MOD) v -= MOD; 
		return *this; }
	constexpr mint& operator-=(const mint& m) noexcept { 
		if ((v -= m.v) < 0) v += MOD; 
		return *this; }
	constexpr mint& operator*=(const mint& m) noexcept { 
		v = int((ll)v * m.v % MOD); return *this; }
	constexpr mint& operator/=(const mint& m) noexcept { return (*this) *= inv(m); }
	constexpr friend mint pow(mint a, ll p) noexcept {
		mint ans = 1; assert(p >= 0);
		for (; p; p /= 2, a *= a) if (p & 1) ans *= a;
		return ans; }
	constexpr friend mint inv(const mint& a) noexcept { assert(a.v != 0); 
		return pow(a, MOD - 2); }
		
	constexpr mint operator-() const noexcept { return mint(-v); }
	constexpr mint& operator++() noexcept { return *this += 1; }
	constexpr mint& operator--() noexcept { return *this -= 1; }
	constexpr friend mint operator+(mint a, const mint& b) noexcept { return a += b; }
	constexpr friend mint operator-(mint a, const mint& b) noexcept { return a -= b; }
	constexpr friend mint operator*(mint a, const mint& b) noexcept { return a *= b; }
	constexpr friend mint operator/(mint a, const mint& b) noexcept { return a /= b; }

	friend istream& operator>>(istream& is, mint& o) {
		ll v; is >> v; o = mint(v); return is; }
	friend ostream& operator<<(ostream& os, const mint& o) {
		os << o.v; return os; }
};

template <typename M>
struct Combination {
	static const int mod = M::mod;
	vector<M> fact, inv_fact, inv;
	Combination(int N) noexcept {
		fact.resize(N + 1), inv_fact.resize(N + 1), inv.resize(N + 1);
		fact[0] = 1;
		for (int i = 1; i <= N; i++) {
				fact[i] =  fact[i - 1] * i;
		}
		inv[1] = 1;
		for (int i = 2; i <= N; ++i) {
			inv[i] = mod - (mod / i) * inv[mod % i];
		}
		inv_fact[0] = inv_fact[1] = 1;
		for (int i = 2; i <= N; ++i){
			inv_fact[i] = inv_fact[i - 1] * inv[i];
		}
	}
	constexpr M binom(int n, int k) const noexcept {
		if (n < k || n < 0) return 0;
		return fact[n] * inv_fact[k] * inv_fact[n - k];
	}
};

constexpr int MOD = 1e9 + 7; // 998244353;
using Mint = mint<MOD, 5>; // 5 is primitive root for both common mods
using Combo = Combination<Mint>;
using vmi = vector<Mint>;

map<char, int> col_scheme = {{'w', 0}, {'g', 1}, {'r', 2}, {'o', 3}, {'b', 4}, {'y', 5}};
Mint f[70];
bool is_good[6][6];

void precalc() {
    f[1] = 1;
    for (int i = 2; i <= 64; i++) f[i] = 16 * f[i - 1] * f[i - 1];
    for (int i = 0; i < 6; i++) for (int j = 0; j < 6; j++) {
        is_good[i][j] = i != j && i + j != 5;
    }
}
int get_level(ll x) {
    return 63 - __builtin_clzll(x);
}

void solve() {
    precalc();

    int k, n;
    cin >> k >> n;
    vl a(n);
    set<ll> nodes;
    map<ll, vmi> dp;
    map<ll, int> fixed;
    for (auto &e : a) {
        cin >> e;
        string s;
        cin >> s;
        int col = col_scheme[s[0]];
        fixed[e] = col;
    }
    for (auto e : a) {
        while (e) {
            nodes.insert(e);
            e /= 2;
        } 
    }
    for (auto it = nodes.rbegin(); it != nodes.rend(); it++) {
        ll u = *it;
        dp[u] = vmi(6);
        ll lc = 2 * u, rc = 2 * u + 1;
        if (nodes.count(lc) && nodes.count(rc)) {
            for (int i = 0; i < 6; i++) {
                for (int j = 0; j < 6; j++) {
                    for (int k = 0; k < 6; k++) {
                        if (!is_good[i][j] || !is_good[i][k]) continue;
                        dp[u][i] += dp[lc][j] * dp[rc][k];
                    }
                }
            } 
        }else if (nodes.count(lc) || nodes.count(rc)) {
            if (!nodes.count(lc)) swap(lc, rc);
            for (int i = 0; i < 6; i++) {
                for (int j = 0; j < 6; j++) {
                    if (!is_good[i][j]) continue;
                    dp[u][i] += dp[lc][j] * (4 * f[k - get_level(rc)]);
                }
            }
        }else{
            for (int i = 0; i < 6; i++) {
                dp[u][i] = f[k - get_level(u)];
            }
        }
        if (fixed.count(u)) {
            for (int i = 0; i < 6; i++) {
                if (i != fixed[u]) dp[u][i] = 0;
            }
        }
        dbg(u, dp[u]);
    }
    cout << accumulate(all(dp[1]), Mint(0)) << '\n';
}

int main() {
	cin.tie(0)->sync_with_stdio(0);
	cin.exceptions(cin.failbit);
	int testcase = 1;
	// cin >> testcase;
	while (testcase--) {
		solve();
	}
#ifdef LOCAL
	cerr << "Time elapsed: " << 1.0 * (double)clock() / CLOCKS_PER_SEC << " s.\n";
#endif
}

