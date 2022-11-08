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
const int MOD = 1e9 + 7; // 998244353;
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
	cerr << "\033[0m" << endl;
}
template <typename Head, typename... Tail>
void dbg_out(Head H, Tail... T)
{
	cerr << ' ' << H;
	dbg_out(T...);
}
#ifdef LOCAL
#define dbg(...) cerr << "\033[1;35m(" << #__VA_ARGS__ << "):\033[33m", dbg_out(__VA_ARGS__)
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

void setIO(string s) // USACO
{
#ifndef LOCAL
	freopen((s + ".in").c_str(), "r", stdin);
	freopen((s + ".out").c_str(), "w", stdout);
#endif
}

/**
 * Description: Performs range prefix sum queries and point updates. lower_bound returns the first prefix sum >= v
 * Source: Own
 * Verification: http://www.usaco.org/index.php?page=viewproblem2&cpid=693
 * Time Complexity: O(log n) for query and update
 * 1-indexing
 */
template <typename T>
struct BIT
{
	int N;
	vector<T> bit;
	BIT(int n)
	{
		bit.resize(n + 1);
		N = n;
	}
	void upd(int id, T v)
	{
		for (; id <= N; id += id & -id)
			bit[id] += v;
	}
	T query(int id)
	{
		T res = 0;
		for (; id > 0; id -= id & -id)
			res += bit[id];
		return res;
	}
	T range_query(int l, int r)
	{
		return query(r) - query(l - 1);
	}
	T lower_bound(T v)
	{
		int id = 0;
		T sum = 0;
		int lg = 31 - __builtin_clz(N);
		for (int j = lg; ~j; j--)
		{
			if (id + (1 << j) <= N && sum + bit[id + (1 << j)] < v)
			{
				id += (1 << j);
				sum += bit[id];
			}
		}
		return id + 1;
	}
};

const int N = 1e6 + 10;
ll a[N];

void precalc()
{
	a[0] = a[1] = a[2] = 0;
	FOR(i, 3, N)
	{
		ll z = (i - 1) / 2LL;
		a[i] = a[i - 1];
		if (i & 1)
			a[i] += z * z;
		else
			a[i] += z * (z + 1);
	}
}

void solve()
{
	int n;
	ll k;
	cin >> n >> k;
	auto helper = [&](int x) -> ll
	{
		return a[x];
	};
	if (helper(n) < k)
	{
		cout << -1 << '\n';
		return;
	}
	BIT<int> bit(n);
	FOR(i, 1, 1 + n)
	bit.upd(i, 1);
	vi ans(n);
	FOR(i, 1, n + 1)
	{
		ll lef = n + 1 - i;
		ll l = 0, r = (lef - 1) / 2, ret = -1;
		ll v = helper(lef - 1);
		while (l <= r)
		{
			ll mid = (l + r) >> 1;
			ll z = mid * (lef - 1 - mid) + v;
			if (i == 62)
				dbg(z, k);
			if (z >= k)
				ret = mid, r = mid - 1;
			else
				l = mid + 1;
		}
		dbg(i);
		assert(ret != -1);
		k -= ret * (lef - 1 - ret);
		int z = bit.lower_bound(ret + 1);
		bit.upd(z, -1);
		z--;
		dbg(z, k, ret, v);
		ans[z] = i;
	}
	for (auto &e : ans)
		cout << e << ' ';
	cout << '\n';
}

int main()
{
	cin.tie(0)->sync_with_stdio(0);
	cin.exceptions(cin.failbit);
	int testcase = 1;
	// cin >> testcase;
	precalc();
	while (testcase--)
	{
		solve();
	}
#ifdef LOCAL
	cerr << "Time elapsed: " << 1.0 * (double)clock() / CLOCKS_PER_SEC << " s.\n";
#endif
}