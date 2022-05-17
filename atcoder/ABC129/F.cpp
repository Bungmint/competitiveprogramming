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

class Range {
	struct Iter
	{
		int iter;
		constexpr Iter(int it) noexcept : iter(it) {}
		constexpr void operator++() noexcept { iter++; }
		constexpr bool operator!=(const Iter &other) const noexcept { return iter != other.iter; }
		constexpr int operator*() const noexcept { return iter; }
	};
	const Iter first, last;

public:
	explicit constexpr Range(const int f, const int l) noexcept : first(f), last(max(f, l)) {}
	constexpr Iter begin() const noexcept { return first; }
	constexpr Iter end() const noexcept { return last; }
};

constexpr Range rep(const int l, const int r) noexcept { return Range(l, r); }
constexpr Range rep(const int n) noexcept { return Range(0, n); }

class ReversedRange {
    struct Iter {
        int itr;
        constexpr Iter(const int pos) noexcept : itr(pos) {}
        constexpr void operator++() noexcept { --itr; }
        constexpr bool operator!=(const Iter& other) const noexcept { return itr != other.itr; }
        constexpr int operator*() const noexcept { return itr; }
    };
    const Iter first, last;
 
  public:
    explicit constexpr ReversedRange(const int f, const int l) noexcept
        : first(l - 1), last(min(f, l) - 1) {}
    constexpr Iter begin() const noexcept { return first; }
    constexpr Iter end() const noexcept { return last; }
};
 
constexpr ReversedRange per(const int l, const int r) noexcept { return ReversedRange(l, r); }
constexpr ReversedRange per(const int n) noexcept { return ReversedRange(0, n); }

/**
 * Description: Basic functions for the builtin int128
 * Source: https://codeforces.com/blog/entry/75044
 * Verification: https://atcoder.jp/contests/abc129/tasks/abc129_f (Can be solved without 128bit integers)
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

i128 A, B, L, mod;

i128 normalize(i128 a) {
	a %= mod;
	if (a < 0) a += mod;
	return a;
}
i128 add(i128 a, i128 b) {
	a += b;
	if (a >= mod) a -= mod;
	return a;
}
i128 sub(i128 a, i128 b) {
	a -= b;
	if (a < 0) a += mod;
	return a;
}
i128 mul(i128 a, i128 b) {
	return i128(1) * a * b % mod;
}
i128 binPow(i128 a, i128 b) {
	i128 r = 1;
	while (b > 0) {
		if (b & 1) {
			r = mul(r, a);
		}
		a = mul(a, a);
		b >>= 1LL;
	}
	return r;
}

vector<i128> power(38);
void precalc() {
	power[0] = 1;
	for (int i: rep(1, 38)) {
		power[i] = power[i - 1] * 10;
	}
}
i128 getLen(i128 x) {
	return (ub(all(power), x) - power.begin());
}
i128 sum10(int d, i128 K) {
	if (K == 1) {
		return 1;
	}
	i128 m = K / 2;
	i128 ret{}, z = sum10(d, m);
	ret = mul(z, add(binPow(power[d], m), 1));
	if (K & 1) ret = add(ret, binPow(power[d], K - 1));
	return ret;
}
i128 divConquer(i128 st, int d, i128 len) {
	if (len == 1) {
		return normalize(st);
	}
	i128 m = len / 2;
	i128 ret = {}, z = divConquer(st, d, m);
	i128 sum = sum10(d, m);
	i128 pp = binPow(power[d], m);
	ret = mul(z, add(pp, 1));
	ret = add(ret, mul(sum, normalize(B * m)));
	if (len & 1) {
		ret = mul(ret, power[d]);
		ret = add(ret, normalize(st + B * (len - 1)));
	}
	return ret;
}

void solve()
{
	cin >> L >> A >> B >> mod;
	i128 last = L;
	i128 ans = 0;
	i128 len = 0;
	for (int d : per(1, 37)) {
		i128 l = 0, r = last - 1, ret = -1;
		while (l <= r) {
			i128 m = (l + r) / 2;
			i128 x = A + B * m;
			i128 y = getLen(x);
			if (y == d) {
				ret = m;
				r = m - 1;
			}else{
				l = m + 1;
			}
		}
		if (ret == -1) continue;
		ans = add(ans, mul(divConquer(A + B * ret, d,  last - ret), binPow(10, len)));
		len += (last - ret) * d;
		last = ret;
	}
	cout << ans << '\n';
}

int main()
{
	cin.tie(0)->sync_with_stdio(0);
	cin.exceptions(cin.failbit);
	precalc();
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
