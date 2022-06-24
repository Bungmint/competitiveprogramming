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

/* 
	Binary jumping FTW
*/

constexpr int N = 3e5, K = 17;
ll jmp[K][N][2][2]; // i, j, k, l: going from k to l
ar<pii, 2> doors[N];
int n;

inline int dist(pii a, pii b) {
	return abs(a.fi - b.fi) + abs(a.se - b.se);
}
void init() {
	for (int i : rep(K)) {
		for (int j : rep(N)) {
			for (int k : rep(2)) {
				for (int l : rep(2)) jmp[i][j][k][l] = LINF;
			}
		}
	}
	for (int i : rep(K)) {
		if (i == 0) {
			for (int x : rep(n - 2)) {
				for (int j : rep(2)) {
					for (int k : rep(2)) {
						pii cur = doors[x][j];
						if (j) cur.se++;
						else cur.fi++;
						ckmin(jmp[0][x][j][k], 1LL + dist(cur, doors[x + 1][k]));
					}	
				}
				for (int j : rep(2)) {
					for (int k : rep(2)) {
						ckmin(jmp[0][x][j][k], jmp[0][x][j ^ 1][k] + dist(doors[x][j], doors[x][j ^ 1]));
						// dbg(x, j, k, jmp[0][x][j][k]);
					}	
				}
			}
		}else{
			for (int x : rep(n - 1 - (1 << i))) {
				for (int j : rep(2)) {
					for (int k : rep(2)) {
						for (int m : rep(2)) {
							ckmin(jmp[i][x][j][k], jmp[i - 1][x][j][m] + jmp[i - 1][x + (1 << (i - 1))][m][k]);
							ckmin(jmp[i][x][j][k], jmp[i - 1][x][j][m] + jmp[i - 1][x + (1 << (i - 1))][m ^ 1][k] + dist(doors[x + (1 << (i - 1))][m], doors[x + (1 << (i - 1))][m ^ 1]));
						}
					}	
				}
			}
		}
	}
}

ar<ar<ll, 2>, 2> calc(int L, int R) {
	ar<ar<ll, 2>, 2> res{};
	for (int i : rep(2)) {
		res[i][i] = 0;
		res[i][i ^ 1] = dist(doors[L][i], doors[L][i ^ 1]);
	}
	// dbg(res);
	int d = R - L - 1;
	for (int i : per(K)) {
		if (d >> i & 1) {
			ar<ar<ll, 2>, 2> nxt{};
			for (int j : rep(2)) {
				nxt[j][0] = nxt[j][1] = LINF;
				for (int m : rep(2)) {
					for (int k : rep(2)) {
						ckmin(nxt[j][k], res[j][m] + jmp[i][L][m][k]);
						ckmin(nxt[j][k], res[j][m] + jmp[i][L][m ^ 1][k] + dist(doors[L][m ^ 1], doors[L][m]));
						// dbg(j, m, k, nxt[j][k], res[j][m], jmp[i][L][m][k]);
					}
				}
			}
			// dbg(nxt);
			swap(nxt, res);
			L += (1 << i);
		}
	}
	return res;
} 

#define mp make_pair

void solve()
{
	cin >> n;
	for (int i : rep(n - 1)) {
		for (int j : rep(2)) {
			cin >> doors[i][j].fi >> doors[i][j].se;
			doors[i][j].fi--, doors[i][j].se--;
		}
	}
	init();
	int q;
	cin >> q;
	for (int i : rep(q)) {
		int x1, y1, x2, y2;
		cin >> x1 >> y1 >> x2 >> y2;
		x1--, y1--, x2--, y2--;
		int I = max(x1, y1), J = max(x2, y2);
		if (I == J) {
			cout << dist(mp(x1, y1), mp(x2, y2)) << '\n';
			continue;
		}
		if (I > J) {
			swap(x1, x2), swap(y1, y2), swap(I, J);
		}
		ar<ll, 2> z{};
		for (int j : rep(2)) {
			z[j] = dist(mp(x1, y1), doors[I][j]);
		}
		auto res = calc(I, J);

		ll ans = LINF;
		for (int j : rep(2)) {
			for (int k : rep(2)) {
				ll cur = z[j] + res[j][k];
				pii t = doors[J - 1][k];
				if (k) t.se++;
				else t.fi++;
				cur += 1 + dist(mp(x2, y2), t);
				ckmin(ans, cur);
			}
		}
		cout << ans << '\n';

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
