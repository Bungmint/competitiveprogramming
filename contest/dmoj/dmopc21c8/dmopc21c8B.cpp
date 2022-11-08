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
template <int MOD, int RT>
struct mint
{
	static const int mod = MOD;
	static constexpr mint rt() { return RT; } // primitive root for FFT
	int v;
	explicit operator int() const { return v; } // explicit -> don't silently convert to int
	mint() { v = 0; }
	mint(ll _v)
	{
		v = int((-MOD < _v && _v < MOD) ? _v : _v % MOD);
		if (v < 0)
			v += MOD;
	}
	bool operator==(const mint &o) const
	{
		return v == o.v;
	}
	friend bool operator!=(const mint &a, const mint &b)
	{
		return !(a == b);
	}
	friend bool operator<(const mint &a, const mint &b)
	{
		return a.v < b.v;
	}
	friend istream &operator>>(istream &is, const mint &o)
	{
		ll v;
		is >> v;
		o = mint(v);
		return is;
	}
	friend ostream &operator<<(ostream &os, const mint &o)
	{
		os << o.v;
		return os;
	}

	mint &operator+=(const mint &m)
	{
		if ((v += m.v) >= MOD)
			v -= MOD;
		return *this;
	}
	mint &operator-=(const mint &m)
	{
		if ((v -= m.v) < 0)
			v += MOD;
		return *this;
	}
	mint &operator*=(const mint &m)
	{
		v = int((ll)v * m.v % MOD);
		return *this;
	}
	mint &operator/=(const mint &m) { return (*this) *= inv(m); }
	friend mint pow(mint a, ll p)
	{
		mint ans = 1;
		assert(p >= 0);
		for (; p; p /= 2, a *= a)
			if (p & 1)
				ans *= a;
		return ans;
	}
	friend mint inv(const mint &a)
	{
		assert(a.v != 0);
		return pow(a, MOD - 2);
	}

	mint operator-() const { return mint(-v); }
	mint &operator++() { return *this += 1; }
	mint &operator--() { return *this -= 1; }
	friend mint operator+(mint a, const mint &b) { return a += b; }
	friend mint operator-(mint a, const mint &b) { return a -= b; }
	friend mint operator*(mint a, const mint &b) { return a *= b; }
	friend mint operator/(mint a, const mint &b) { return a /= b; }
};

using Mint = mint<MOD, 5>; // 5 is primitive root for both common mods

const int N = 1e6 + 10;
int a[2][N];

void solve()
{
	int n, m;
	cin >> n >> m;
	F0R(i, 2)
	F0R(j, n)
		cin >> a[i][j];
	auto helper = [&](int x) -> Mint
	{
		if (x <= m + 1)
			return Mint(x - 1);
		else
			return Mint(2 * m + 1 - x);
	};
	auto calc = [&](int st) -> Mint
	{
		Mint res = 1;
		int empty = 0;
		int full = 0;
		int mi = INF, mx = 0;
		for (int j = st; j < n; j += 2)
		{
			int x = a[0][j], y = a[1][j];
			if (x && y)
			{
				if (full == 0)
					full = x + y;
				else if (full != x + y)
					return Mint(0);
			}
			else if (!x && !y)
			{
				empty++;
			}
			else
			{
				if (y)
					swap(x, y);
				ckmin(mi, x), ckmax(mx, x);
			}
		}
		if (full)
		{
			res *= pow(helper(full), empty);
			if (mi != INF)
			{
				if (full > mi + m || full <= mx)
					return Mint(0);
			}
		}
		else
		{
			res = 0;
			FOR(i, 2, 2 * m + 1)
			{
				if (mi != INF)
				{
					if (i > mi + m || i <= mx)
						continue;
				}
				res += pow(helper(i), empty);
			}
		}
		return res;
	};
	Mint ans = calc(0) * calc(1);

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