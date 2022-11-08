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

// From the USACO tutorial lol
struct DSU {
	vector<int> e;
	vi L, R, ty, len;
	DSU(int N) { 
		e = vector<int>(N, -1); 
		L.resize(N), R.resize(N);
		ty.assign(N, -1);
		iota(all(L), 0), iota(all(R), 0);
		len.assign(N, 1);
	}

	// get representive component (uses path compression)
	// To use rollback, disable path compression
	int get(int x) { return e[x] < 0 ? x : e[x] = get(e[x]); }
	
	bool same_set(int a, int b) { return get(a) == get(b); }
	
	int size(int x) { return -e[get(x)]; }
	
	bool unite(int x, int y, int fl) {  // union by size
		x = get(x), y = get(y);
		if (x == y) return ty[x] == fl;
		if (e[x] > e[y]) swap(x, y);
		e[x] += e[y]; e[y] = x;
		if (ty[x] == (fl ^ 1) || ty[y] == (fl ^ 1)) return false;
		L[x] = min(L[x], L[y]), R[x] = max(R[x], R[y]);
		len[x] += len[y];
		ty[x] = fl;
		return true;
	}
};

void solve()
{
	int n, m;
	cin >> n >> m;
	DSU dsu(n - 1);
	auto setType = [&](int u, int fl) -> bool {
		u = dsu.get(u);
		if (dsu.ty[u] == (fl ^ 1)) return false;
		dsu.ty[u] = fl;
		return true;
	};
	for (int i : rep(m)) {
		int t, l, r;
		cin >> t >> l >> r;
		l--, r--; t--;
		int R = dsu.R[dsu.get(l)];
		if (!setType(l, t)) {
			cout << -1 << '\n';
			return;
		}
		while (R < r - 1) {
			bool fl = dsu.unite(l, R + 1, t);
			if (!fl) {
				cout << "-1" << '\n';
				return;
			}
			R = dsu.R[dsu.get(l)];
		}
	}
	vi ans(n);
	
	for (int i : rep(n - 1)) {
		i = dsu.get(i);
		if (dsu.ty[i] != -1) {
			int L = dsu.L[i], R = dsu.R[i];
			int lef = (L ? dsu.get(L - 1) : -1), rig = (R + 1 < n - 1 ? dsu.get(R + 1) : -1);
			// int leflef = (L > 1 ? dsu.get(L - 2) : -1), rigrig = (R + 2 < n - 1 ? dsu.get(R + 2) : -1);
			if (L && dsu.ty[lef] == dsu.ty[i]) {
				dsu.unite(i, L - 1, dsu.ty[i]);
			}
			if (R + 1 < n - 1 && dsu.ty[rig] == dsu.ty[i]) {
				dsu.unite(i, R + 1, dsu.ty[i]);
			}
		}
	}
	for (int i : rep(n - 1)) {
		i = dsu.get(i);
		if (dsu.ty[i] != -1) {
			int L = dsu.L[i], R = dsu.R[i];
			int lef = (L ? dsu.get(L - 1) : -1), rig = (R + 1 < n - 1 ? dsu.get(R + 1) : -1);
			int leflef = (L > 1 ? dsu.get(L - 2) : -1), rigrig = (R + 2 < n - 1 ? dsu.get(R + 2) : -1);
			if (L > 1 && lef != leflef && dsu.ty[leflef] != dsu.ty[i] && dsu.ty[lef] == -1) {
				if (dsu.len[leflef] <= dsu.len[i]) dsu.unite(leflef, lef, dsu.ty[leflef]);
				else dsu.unite(lef, i, dsu.ty[i]);
			}
		}
	}
	for (int i : rep(n - 1)) {
		i = dsu.get(i);
		if (dsu.ty[i] != -1) {
			int L = dsu.L[i], R = dsu.R[i];
			int rig = (R + 1 < n - 1 ? dsu.get(R + 1) : -1);
			int rigrig = (R + 2 < n - 1 ? dsu.get(R + 2) : -1);
			if (R + 2 < n - 1 && rig != rigrig && dsu.ty[rigrig] != dsu.ty[i] && dsu.ty[rig] == -1) {
				if (dsu.len[rigrig] >= dsu.len[i]) dsu.unite(i, rig, dsu.ty[i]);
				else dsu.unite(rigrig, rig, dsu.ty[rigrig]);
			}
			
		}
	}
	// ans[0] = n;
	// for (int i : rep(n - 1)) {
	// 	int h = dsu.get(i);
	// 	if (dsu.ty[h] == -1) ans[i + 1] = ans[i] + 1;
	// 	else if (dsu.ty[h] == 1) ans[i + 1] = ans[i] - 1;
	// 	else ans[i + 1] = ans[i] + 1;
	// }
	vi isSet;
	for (int i : rep(n - 1)) {
		if (dsu.get(i) == i && dsu.ty[i] != -1) {
			isSet.pb(i);
		}
	}
	for (int i : rep(sz(isSet))) {
		int head = isSet[i];
		int L = dsu.L[head], R = dsu.R[head];
		int t = dsu.ty[head];
		int len = R - L + 2;
		if (i == 0) {
			if (t == 0) {
				ans[L] = 1;
				for (int j : per(L)) {
					ans[j] = (ans[j + 1] == 1 ? 2 : 1);
				}
			}else{
				ans[L] = len;
				for (int j : per(L)) {
					ans[j] = ((L - j) & 1 ? 1 : 2);
				}
			}
		}
		
		if (!ans[L]) {
			if (t == 0) ans[L] = 1;
			else ans[L] = len;
		}else{
			// if (t == 0) {
			// 	assert(ans[L] == 1);
			// }else{
			// 	assert(ans[L] >= len);
			// }
		}
		for (int j : rep(L + 1, R + 2)) {
			ans[j] = ans[j - 1] + (t ? -1 : 1);
		}
		if (i + 1 < sz(isSet)) {
			int nxt = isSet[i + 1];
			int nL = dsu.L[nxt], nR = dsu.R[nxt];
			int nt = dsu.ty[nxt];
			int nlen = nR - nL + 2;
			if (nL == R + 1) {
				if (nt == 1) {
					ckmax(ans[nL], nR - nL + 2);
				}else{
					ans[nL] = 1;
				}
			}else{
				int k = nL - R - 2;
				{
					for (int j : rep(R + 2, nL)) {
						ans[j] = (ans[j - 1] == n + 1 ? n + 2 : n + 1);
						// ans[j] = ((j - R - 2 + k + nt) & 1 ? 2 : 1);
						// if (j == R + 2 && ans[R + 2] == ans[R + 1]) {
						// 	ans[R + 2] = 3;
						// }
					}
				}
			}
		}else{
			for (int j : rep(R + 2, n)) {
				if (ans[j - 1] == 1) ans[j] = 2;
				else ans[j] = 1;
			}
		}
	}
	for (int i : rep(n - 1)) {
		if (ans[i] == ans[i + 1]) {
			assert(false);
		}
	}
	for (int i : rep(n)) cout << ans[i] << " \n"[i == n - 1];
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
