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

struct Line {
	ll m, b;
	ll operator()(ll x) { return m*x + b; }
	friend ll intersect(Line l, Line r) {
		return fdiv(r.b-l.b, l.m-r.m);
	};
	friend bool cross(Line ins, Line f, Line s) {
		return (ld)1.0*(s.b-ins.b)/(ins.m-s.m) + 1e-12 < (ld)1.0*(s.b-f.b)/(f.m-s.m);
	}
};

void solve() {
	int n; cin >> n;
	vl s(n + 1), t(n + 1);
	for (int i = 1; i <= n; i++) {
		ll x; cin >> x;
		s[i] = s[i - 1] + x;
		t[i] = t[i - 1] + i*x;
	}
	deque<Line> deq;
	deq.pb({0, 0});
	ll ans{};
	auto insert_line = [&](Line l) {
		while (sz(deq) >= 2 && !cross(l, deq[0], deq[1])) {
			deq.pop_front();
		}
		deq.push_front(l);
	};
	auto get_max = [&](ll x) -> ll {
		int lo = 0, hi = sz(deq) - 1, ret = 0;
		while (lo <= hi) {
			int mid = (lo + hi) / 2;
			if (mid == sz(deq) - 1) { ret = mid; break; }
			if (intersect(deq[mid], deq[mid + 1]) < x) {
				lo = mid + 1;
			}else{
				ret = mid;
				hi = mid - 1;
			}
		}
		return deq[ret](x);
	};
	for (int i = 1; i <= n; i++) {
		ckmax(ans, t[i] + get_max(s[i]));
		insert_line({-i, i*s[i] - t[i]});
	}
	cout << ans << '\n';
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
