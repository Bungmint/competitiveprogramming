// Copyright © 2022 Youngmin Park. All rights reserved.
//#pragma GCC optimize("O3")
//#pragma GCC target("avx2")
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
template <typename T>
using pqg = priority_queue<T, vector<T>, greater<T>>;

#define all(v) (v).begin(), (v).end()
#define pb push_back
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

/**
 * Description: Basic I/O for the builtin 128bit integer
 * Source: https://codeforces.com/blog/entry/75044
 * Verification: https://atcoder.jp/contests/abc129/tasks/abc129_f
 */

using i128 = __int128_t;
istream& operator>>(istream& in, i128& num) { 
    i128 x = 0, f = 1;
    char ch = in.peek();
    while (ch < '0' || ch > '9') {
        if (ch == '-') f = -1;
        in.get();
        ch = in.peek();
    }
    while (ch >= '0' && ch <= '9') {
        x = x * 10 + ch - '0';
        in.get();
        ch = in.peek();
    }
    num = x * f;
    return in;
}
ostream& operator<<(ostream& out, i128 num) {
    string res;
    bool neg = num < 0;
    if (neg) num = -num;
    do {
        res += '0' + (num % 10);
        num /= 10;
    }while (num > 0);
    if (num < 0) {
        res += '-';
    }
    reverse(all(res));
    out << res;
    return out;
}

// TODO: Test Imp
/*
 * Basic Modular Operations assuming 0 <= a, b < MOD
 * Source: Own
 * Verification:
 * Time complexity: O(log(min(a, b))) for modular inverse and mod_pow, other operations are O(1)
**/
inline namespace ModUtil {
    int MOD = 1e9 + 7; // 998244353
    int add(int a, const int& b) { 
        a += b;
        if (a >= MOD) a -= MOD;
        return a;
    }
    int mul(const int& a, const int& b) { return 1LL * a * b % MOD; }
    int sub(int a, const int& b) {
        a -= b;
        if (a < 0) a += MOD;
        return a;
    }
    int mod_pow(int a, int b) {
        int r = 1;
        while (b) {
            if (b & 1) r = mul(r, a);
            a = mul(a, a);
            b >>= 1;
        }
        return r;
    }
    template <typename T>
    T inverse(T a, T b) { // Assumes 0 < a < b, could overflow if using 64bit int
        return a > 1 ? b - inverse(b % a, a) * b / a : 1;
    }
}

using ii = pair<i128, i128>;

i128 my_gcd(i128 A, i128 B) {
	return B == 0 ? A : my_gcd(B, A % B);
}
#define gcd my_gcd

ii crt(ii A, ii B) {
	if (A.se == -1 || B.se == -1) return {-1, -1};
	if (A.se == 1 || B.se == 1) return A.se == 1 ? B : A;
	i128 g = gcd(A.se, B.se), l = (A.se / g) * B.se;
	if ((B.fi - A.fi) % g) return {-1, -1};
	i128 a = A.se / g, b = B.se / g;
	i128 mul = (B.fi - A.fi) / g;
	mul = (mul * inverse(a, b)) % b;
	i128 ret = mul * A.se + A.fi;
	ret %= l, ret = (ret + l) % l;
	return {ret, l};
}

const i128 LIM = numeric_limits<ll>::max();

void solve() {
	int b, z;
	cin >> b >> z;
	vi start(b), t_min(z);
	vector<vi> nxt(b, vi(z));
	vector<vpi> equations(z);
	for (int i = 0; i < b; i++) {
		cin >> start[i], start[i]--;
		for (int j = 0; j < z; j++) {
			cin >> nxt[i][j], nxt[i][j]--;
		}
	}
	vi loc = start;
	for (int t = 0; t <= z; t++) { // checks the non-cycle section
		if (count(all(loc), loc.front()) == b) {
			cout << loc.front() + 1 << ' ' << t << '\n';
			return;
		}
		for (int i = 0; i < b; i++) {
			loc[i] = nxt[i][loc[i]];
		}
	}
	/*
		Tortoise & Hare Algorithm
	*/
	auto calc = [&](int u) -> void {
		int st = start[u];
		int x = nxt[u][st], y = nxt[u][nxt[u][st]];
		while (x != y) {
			x = nxt[u][x];
			y = nxt[u][nxt[u][y]];
		}
		x = st;
		int non_cycle{};
		while (x != y) {
			x = nxt[u][x];
			y = nxt[u][y];
			non_cycle++;
		}
		vi cycle{x};
		y = nxt[u][y];
		while (x != y) {
			cycle.pb(y);
			y = nxt[u][y];
		}
		for (int i = 0; i < sz(cycle); i++) {
			equations[cycle[i]].pb({non_cycle % sz(cycle), sz(cycle)});
			ckmax(t_min[cycle[i]], non_cycle);
			non_cycle++;
		}
	};
	for (int i = 0; i < b; i++) calc(i);
	i128 ans = LIM * 2;
	int ind{};
	for (int i = 0; i < z; i++) {
		if (sz(equations[i]) < b) continue;
		ii ret = {0, 1};
		dbg(equations[i]);
		for (auto e : equations[i]) {
			ret = crt(ret, e);
			if (ret.fi == -1) break;
		}
		if (ret.fi != -1) {
			while (ret.fi < t_min[i]) {
				ret.fi += ret.se;
			}
			if (ckmin(ans, ret.fi)) ind = i + 1; 
		}
	}
	if (LIM * 2 == ans) cout << '*' << '\n';
	else cout << ind << ' ' << ans << '\n';
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
