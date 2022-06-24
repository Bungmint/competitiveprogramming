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



void solve()
{
	int n, p, q;
	cin >> n >> p >> q;
	int half = n / 2, nhalf = n - n / 2;
	vi a(n), b(n), c(n);
	for (int i = 0; i < n; i++) cin >> a[i] >> b[i] >> c[i];
	vi ind, mi;
	int ans = INF;
	for (int mask = 0; mask < (1 << half); mask++) {
		int cost = 0;
		int P = 0, Q = 0;
		for (int i = 0; i < half; i++) {
			if (mask >> i & 1) P += a[i], Q += b[i], cost += c[i];
		}
		if (P && Q && P * q - p * Q == 0) {
			ckmin(ans, cost);
		}else if (P * q - p * Q != 0) ind.pb(P * q - p * Q);
	}
	sort(all(ind)), ind.resize(unique(all(ind)) - ind.begin()), mi.assign(sz(ind), INF);
	for (int mask = 0; mask < (1 << half); mask++) {
		int cost = 0;
		int P = 0, Q = 0;
		for (int i = 0; i < half; i++) {
			if (mask >> i & 1) P += a[i], Q += b[i], cost += c[i];
		}
		if (P * q - p * Q == 0) continue;
		auto it = lb(all(ind), P * q - p * Q) - ind.begin();
		ckmin(mi[it], cost);
	}
	for (int mask = 1; mask < (1 << nhalf); mask++) {
		int cost = 0;
		int P = 0, Q = 0;
		for (int i = 0; i < nhalf; i++) {
			if (mask >> i & 1) P += a[i + half], Q += b[i + half], cost += c[i + half];
		}
		if (Q * p - P * q == 0) {
			ckmin(ans, cost);
		}else{
			auto it = lb(all(ind), Q * p - P * q) - ind.begin();
			if (it != sz(ind) && ind[it] == Q * p - P * q) {
				ckmin(ans, cost + mi[it]);
			}
		}
	}
	cout << (ans == INF ? -1 : ans) << '\n';
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
