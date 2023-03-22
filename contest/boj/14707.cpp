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

template <typename T>
vector<T> operator+(const vector<T>& a, const vector<T>& b) {
    vector<T> res(sz(a));
    for (int i = 0; i < sz(a); i++) res[i] = a[i] + b[i];
    return res;
}
template <typename T>
vector<T> operator-(const vector<T>& a, const vector<T>& b) {
    vector<T> res(sz(a));
    for (int i = 0; i < sz(a); i++) res[i] = a[i] - b[i];
    return res;
}
vl karatsuba(const vi& a, const vi& b) {
    int n = sz(a);
    vl res(2 * n - 1);
    if (n <= 64) {
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                res[i + j] += 1LL * a[i] * b[j];
            }
        }
    }else{
        vi a_lo(a.begin(), a.begin() + n / 2), a_hi(a.begin() + n / 2, a.end());
        vi b_lo(b.begin(), b.begin() + n / 2), b_hi(b.begin() + n / 2, b.end());
        vl lolo = karatsuba(a_lo, b_lo); 
        vl hihi = karatsuba(a_hi, b_hi);
        vl lohi = karatsuba(a_lo + a_hi, b_lo + b_hi) - lolo - hihi;
        for (int i = 0; i < sz(lolo); i++) res[i] += lolo[i];
        for (int i = 0; i < sz(hihi); i++) res[i + n] += hihi[i];
        for (int i = 0; i < sz(lohi); i++) res[i + n / 2] += lohi[i];
    }
    return res;
}
vl mul_poly(vi& a, vi& b) {
    int s = 1;
    while (s < max(sz(a), sz(b))) s *= 2;
    a.resize(s), b.resize(s); 
    return karatsuba(a, b);
}

void solve() {
	int N, M, L;
	cin >> N >> M >> L;
	vi h(N), w(M);
	for (auto &e : h) cin >> e;
	for (auto &e : w) cin >> e;
    vi hh(L);
    for (int i = 0; i < N; i++) {
        hh[1LL * i * M % L] += h[i];
    }
    dbg(hh);
    vl res = mul_poly(hh, w);
    dbg(res);
    vl ans(L);
    for (int i = 0; i < sz(res); i++) {
        ans[i % L] += res[i];
    }
    for (int i = 0; i < L; i++) cout << ans[i] << '\n';
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
