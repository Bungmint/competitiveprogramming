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
 

void solve()
{
	int n, q;
	cin >> n >> q;
	string s;
	cin >> s;
	int timer{};
	vector<vi> tree(n + 1);
	vi par(n + 1), lef(n + 1, -1), rig(n + 1, -1), id(n + 1, -1), tin(n + 1), tout(n + 1);
	vi ch(n + 1), cnt(n + 1);
	vl sum(n + 1);
	vector<vl> prefSum(n + 1), prefCnt(n + 1);
	vector<bool> good(n + 1);
	vi todo;
	deque<int> sta;
	for (int i : rep(n)) {
		if (s[i] == '(') {
			sta.pb(i);
		}else{
			if (sz(sta)) {
				int le = sta.back();
				sta.pop_back();
				lef[i] = le;
				rig[le] = i;
				par[le] = (sz(sta) ? sta.back() : n);
				good[le] = 1;
				// id[le] = sz(tree[par[le]]);
				// tree[par[le]].pb(le);
				// ch[par[le]]++;
			}
		}
	}
	for (int i : rep(n)) {
		if (good[i]) {
			if (par[i] < n && good[par[i]] == 0) {
				par[i] = n;
			}
			id[i] = sz(tree[par[i]]);
			tree[par[i]].pb(i);
			ch[par[i]]++;
		}
	}
	auto dfsInit = y_combinator([&](auto self, int u) -> void {
		tin[u] = timer++;
		prefSum[u].resize(ch[u] + 1);
		prefCnt[u].resize(ch[u] + 1);
		for (int i : rep(ch[u])) {
			auto v = tree[u][i];
			prefSum[u][i + 1] = prefSum[u][i];
			prefCnt[u][i + 1] = prefCnt[u][i];
			if (!good[v]) continue;
			self(v);
			prefSum[u][i + 1] += sum[v];
			prefCnt[u][i + 1]++;
		}
		cnt[u] = prefCnt[u][ch[u]];
		sum[u] = prefSum[u][ch[u]] + (1LL * (cnt[u] + 1)) * (cnt[u]) / 2LL;
		tout[u] = timer - 1;
	});
	auto isAnc = [&](int L, int R, int v) -> bool {
		return tin[L] <= tin[v] && tout[v] <= tout[R];
	};
	auto recalc = y_combinator([&](auto self, int u) -> void {
		for (int i : rep(ch[u])) {
			auto v = tree[u][i];
			assert(i + 1 < sz(prefSum[u]));
			assert(v >= 0 && v <= n);
			prefSum[u][i + 1] = prefSum[u][i];
			prefCnt[u][i + 1] = prefCnt[u][i];
			if (!good[v]) continue;
			self(v);
			prefSum[u][i + 1] += sum[v];
			prefCnt[u][i + 1]++;
		}
		assert(sz(prefCnt[u]) > ch[u] && sz(prefSum[u]) > ch[u] && u >= 0 && u <= n);
		cnt[u] = prefCnt[u][ch[u]];
		sum[u] = prefSum[u][ch[u]] + (1LL * (cnt[u] + 1)) * (cnt[u]) / 2LL;
	});
	dfsInit(n);
	int LIM = sqrt(n) + 10;
	for (int i : rep(q)) {
		if (sz(todo) == LIM) {
			while (sz(todo)) {
				auto &v = todo.back();
				good[v] = 0;
				todo.pop_back();
			}
			recalc(n);
		}
		int t, l, r;
		cin >> t >> l >> r;
		l--, r--;
		if (t == 1) {
			todo.pb(l);
		}else{
			int p = par[l];
			int L = l, R = lef[r];
			assert(L >= 0 && R >= 0 && p >= 0 && id[L] < ch[p] && id[R] < ch[p]);
			ll ans = prefSum[p][id[R] + 1] - prefSum[p][id[L]];
			int cur = prefCnt[p][id[R] + 1] - prefCnt[p][id[L]];
			for (auto &v : todo) {
				if (isAnc(L, R, v)) {
					assert(par[v] >= 0 && par[v] <= n);
					if (par[v] == p) {
						cur--;
					}else{
						ans -= cnt[par[v]];
						cnt[par[v]]--;
					}
				}
			}
			ans += 1LL * (cur + 1LL) * (cur) / 2LL;
			cout << ans << '\n';
			for (auto &v : todo) {
				if (isAnc(L, R, v)) {
					if (par[v] == p) {
						cur++;
					}else{
						cnt[par[v]]++;
					}
				}
			}
		}
	}

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
