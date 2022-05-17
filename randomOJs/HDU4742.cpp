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

constexpr int mod = (1 << 30) - 1;
const int N = 1e5 + 10;
pii dp[N];
ar<int, 4> a[N], tmp[N];
pii tree[N];
int n;

pii merge(pii lhs, pii rhs) {
	if (lhs.fi != rhs.fi) return max(lhs, rhs);
	return {lhs.fi, (lhs.se + rhs.se) & mod};
}
void upd(int i, pii v) {
	for (i++; i <= n; i += i & -i) tree[i] = merge(tree[i], v);
}
void clear(int i) {
	for (i++; i <= n; i += i & -i) tree[i] = {0, 0};
}
pii query(int i) {
	pii ret{};
	for (i++; i; i -= i & -i) {
		ret = merge(ret, tree[i]);
	}
	return ret;
}


void cdq(int L, int R) {
	if (R - L == 1) return;
	int M = (L + R) >> 1;
	cdq(L, M);
	for (int i = M; i < R; i++) tmp[i] = a[i];
	sort(a + L, a + M, [&](ar<int, 4> p, ar<int, 4> q) {
		return p[1] < q[1];
	});
	sort(a + M, a + R, [&](ar<int, 4> p, ar<int, 4> q) {
		return p[1] < q[1];
	});
	for (int i = L, j = M; j < R; j++) {
		for (; i < M && a[j][1] >= a[i][1]; i++) {
			upd(a[i][2], dp[a[i][3]]);
		}
		pii p = query(a[j][2]);
		if (p.fi != 0) p.fi++, dp[a[j][3]] = merge(dp[a[j][3]], p);
	}
	for (int i = L; i < M; i++) clear(a[i][2]);
	for (int i = M; i < R; i++) a[i] = tmp[i];
	cdq(M, R);
}


void solve()
{
	cin >> n;
	fill(dp, dp + n, make_pair(1, 1));
	vector<vi> ind(3);
	for (int i = 0; i < n ; i++) {
		for (int j = 0; j < 3; j++) {
			cin >> a[i][j];
			ind[j].pb(a[i][j]);
		}
		a[i][3] = i;
		dbg(a[i]);
	}
	for (int i = 0; i < 3; i++) {
		sort(all(ind[i])), ind[i].resize(unique(all(ind[i])) - ind[i].begin());
		for (int j = 0; j < n; j++) {
			a[j][i] = lb(all(ind[i]), a[j][i]) - ind[i].begin();
		}
	}
	sort(a, a + n, [&](ar<int, 4> x, ar<int, 4> y) {
		return (x[0] == y[0] ? (x[1] == y[1] ? x[2] < y[2] : x[1] < y[1]) : x[0] < y[0]);
	});
	cdq(0, n);
	pii ret{};
	for (int i = 0; i < n; i++) {
		ret = merge(ret, dp[i]);
		dbg(dp[i]);
	}
	cout << ret.fi << ' ' << ret.se << '\n';
}

int main()
{
	cin.tie(0)->sync_with_stdio(0);
	cin.exceptions(cin.failbit);
	int testcase = 1;
	cin >> testcase;
	while (testcase--)
	{
		solve();
	}
#ifdef LOCAL
	cerr << "Time elapsed: " << 1.0 * (double)clock() / CLOCKS_PER_SEC << " s.\n";
#endif
}
