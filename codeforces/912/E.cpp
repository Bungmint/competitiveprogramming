// Copyright © 2022 Youngmin Park. All rights reserved.
#pragma GCC optimize("O3")
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
template <typename T>
ostream &operator<<(ostream &os, const deque<T> &v) {
	os << vector<T>(all(v));
	return os;
}
template <typename T, typename S, typename C>
ostream &operator<<(ostream &os, priority_queue<T, S, C> pq) {
	vector<T> v;
	while (sz(pq)) {
		v.pb(pq.top());
		pq.pop();
	}
	os << v;
	return os;
}
void dbg_out()
{
	cerr << "\033[0m" << endl;
}
template <typename Head, typename... Tail>
void dbg_out(Head H, Tail... T)
{
	cerr << ' ' << H;
	dbg_out(T...);
}
#ifdef LOCAL
#define dbg(...) cerr << "\033[1;35m" << __func__ << ':' << __LINE__ << " (" << #__VA_ARGS__ << "):\033[33m", dbg_out(__VA_ARGS__)
#else
#define dbg(...) 42
#endif

inline namespace RecursiveLambda
{
	template <typename Fun>
	struct y_combinator_result
	{
		Fun fun_;
		template <typename T>
		explicit y_combinator_result(T &&fun) : fun_(forward<T>(fun)) {}
		template <typename... Args>
		decltype(auto) operator()(Args &&...args)
		{
			return fun_(ref(*this), forward<Args>(args)...);
		}
	};
	template <typename Fun>
	decltype(auto) y_combinator(Fun &&fun)
	{
		return y_combinator_result<decay_t<Fun>>(forward<Fun>(fun));
	}
};

inline namespace Range {
	class ForwardRange {
		int src, dst;

	  public:
	  	explicit constexpr ForwardRange(const int l, const int r) : src(l), dst(r) {}
		explicit constexpr ForwardRange(const int n) : src(0), dst(n) {}
		constexpr ForwardRange begin() const { return *this; }
		constexpr monostate end() const { return {}; }
		constexpr bool operator!=(monostate) const { return src < dst; }
		constexpr void operator++() const {}
		constexpr int operator*() { return src++; }
	};
	class BackwardRange {
		int src, dst;

	  public:
	  	explicit constexpr BackwardRange(const int l, const int r) : src(r), dst(l) {}
		explicit constexpr BackwardRange(const int n) : src(n), dst(0) {}
		constexpr BackwardRange begin() const { return *this; }
		constexpr monostate end() const { return {}; }
		constexpr bool operator!=(monostate) const { return src > dst; }
		constexpr void operator++() const {}
		constexpr int operator*() { return --src; }
	};
	using rep = ForwardRange;
	using per = BackwardRange;
};

// /**
//  * Description: Tests primality up to SZ
//  * Source: Benq
//  * Time complexity: O(SZ log log SZ) or O(SZ)
//  */
// template <int SZ>
// struct Sieve {
//     bitset<SZ> is_prime;
//     vi primes;
//     Sieve() {
//         is_prime.set();
//         is_prime[0] = is_prime[1] = 0;
//         for (int i = 4; i < SZ; i += 2) is_prime[i] = 0;
//         for (int i = 3; i * i < SZ; i += 2) {
//             if (is_prime[i]) {
//                 for (int j = i * i; j < SZ; j += 2 * i) {
//                     is_prime[j] = 0;
//                 }
//             }
//         }
//         for (int i : rep(SZ)) if (is_prime[i]) primes.pb(i);
//     }
//     // int lp[SZ];
//     // Sieve() {
//     //     for (int i : rep(2, SZ)) {
//     //         if (lp[i] == 0) lp[i] = i, primes.pb(i);
//     //         for (int p : primes) {
//     //             if (p > lp[i] || i * p >= SZ) break;
//     //             lp[i * p] = p;
//     //         }
//     //     }
//     // }
// };

// Sieve<100> sieve;

void generateAll(int id, ll prod, vl& ret, vi& pr) {
	// dbg(prod, id, sz(pr));
	if (sz(pr) == id) {
		ret.pb(prod);
		return;
	}
	ll pp = 1;
	ll p = pr[id];
	const ll LIM = LINF / prod;
	const ll befL = LIM / p;
	while (pp <= LIM) {
		generateAll(id + 1, prod * pp, ret, pr);
		if (pp <= befL) pp *= p;
		else break;
	}
}

void solve()
{
	// vi p, ret;
	// vi pp, rr;
	// for (int i : rep(6)) {
	// 	pp.pb(sieve.primes[i]);
	// }
	// for (int i : rep(6, 16)) p.pb(sieve.primes[i]);
	// generateAll(0, 1, ret, p);
	// generateAll(0, 1, rr, pp);
	// dbg(sz(ret), sz(rr));
	vi pr1, pr2;
	vl ret1, ret2;
	int n; ll k;
	cin >> n;
	vi p(n);
	for (auto &E : p) cin >> E;
	cin >> k;
	sort(all(p));
	int half = min(6, n / 2);
	for (int i : rep(half)) pr1.pb(p[i]);
	for (int i : rep(half, n)) pr2.pb(p[i]);
	generateAll(0, 1, ret1, pr1);
	generateAll(0, 1, ret2, pr2);
	sort(all(ret1)), sort(all(ret2));
	reverse(all(ret2));
	
	auto calc = [&](const ll t) -> int {
		int ptr = 0;
		ll ans = 0;
		bool acc{};
		for (ll x : ret1) {
			ll targ = t / x;
			while (ptr < sz(ret2) && ret2[ptr] > targ) {
				ptr++;
			}
			// if (t == 6)	dbg(ans, targ, x, t);
			if (sz(ret2) == ptr) break;
			ans += sz(ret2) - ptr;
			if (ptr < sz(ret2) && ret2[ptr] * x == t) acc = 1;
		}
		if (ans > k) return -1;
		if (ans < k) return 0;
		if (ans == k) {
			if (acc) return 1;
			else return 2;
		}
		assert(1);
		return 3;
	};
	ll L = 1, R = 1e18, ans = 1;
	while (L <= R) {
		ll M = (L + R) / 2;
		int x = calc(M);
		// dbg(M, x);
		if (x == 0) {
			L = M + 1;
		}else if (x == -1) {
			R = M - 1;
		}else if (x == 2) {
			R = M - 1;
		}else{
			ans = M;
			break;
		}
	}
	cout << ans << '\n';
	
}

int main()
{
	cin.tie(0)->sync_with_stdio(0);
	cin.exceptions(cin.failbit);
	int testcase = 1;
	// cin >> testcase;
	while (testcase--)
	{
		solve();
	}
#ifdef LOCAL
	cerr << "Time elapsed: " << 1.0 * (double)clock() / CLOCKS_PER_SEC << " s.\n";
#endif
}
