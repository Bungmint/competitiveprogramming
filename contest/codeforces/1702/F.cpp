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

void solve() {
	int n; cin >> n;
	vi a(n), b(n);
	map<int, int> freq, freq_b;
	for (auto &e : a) cin >> e;
	for (auto &e : b) cin >> e;
	for (int i = 0; i < n; i++) {
		int cnt = 1;
		while (i + 1 < n && a[i] == a[i + 1]) i++, cnt++;
		while (a[i] % 2 == 0) a[i] /= 2;
		freq[a[i]] += cnt;
	}
	for (int i = 0; i < n; i++) {
		int cnt = 1;
		while (i + 1 < n && b[i] == b[i + 1]) i++, cnt++;
		while (b[i] % 2 == 0) b[i] /= 2;
		freq_b[b[i]] += cnt;
	}
	auto it = --freq_b.end();
	auto t = --freq.end();
	while (1) {
		if (t->fi > it->fi) {
			cout << "NO\n";
			return;
		}else if (t->fi < it->fi) {
			freq_b[it->fi/2] += it->se;
			freq_b.erase(it);
			it = --freq_b.end();
		}else{
			dbg(freq, freq_b, t->se, it->se);
			int mi = min(t->se, it->se);
			if (mi == t->se) {
				freq.erase(t);
				if (sz(freq) == 0) break;
				t = --freq.end();
			}else{
				freq[t->fi] -= mi;
			}
			if (mi == it->se) {
				freq_b.erase(it);
				if (sz(freq_b) == 0) {
					if (sz(freq)) {
						cout << "NO\n";
						return;
					}else break;
				}
				it = --freq_b.end();
			}else{
				freq_b[it->fi] -= mi;
			}
			dbg(freq, freq_b);
		}
	}
	cout << "YES\n";
}

int main() {
	cin.tie(0)->sync_with_stdio(0);
	cin.exceptions(cin.failbit);
	int testcase = 1;
	cin >> testcase;
	while (testcase--) {
		solve();
	}
#ifdef LOCAL
	cerr << "Time elapsed: " << 1.0 * (double)clock() / CLOCKS_PER_SEC << " s.\n";
#endif
}
