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

constexpr int N = 5e4 + 10;
int ind[N];
ar<int, 2> a[N];
int dp[N];
int par[N];
int n;
int bit[N + 1];
int tmp[N];

int merge(int i, int j) {
	if (i == j) return i;
	if (i == -1) return j;
	if (j == -1) return i;
	if (dp[i] != dp[j]) return (dp[i] > dp[j] ? i : j);
	return (i < j ? i : j);
}
void upd(int i, int v) {
	for (i++; i <= n; i += i & -i) {
		bit[i] = merge(bit[i], v);
	}
}
int query(int i) {
	int ret = -1;
	for (i++; i; i -= i & -i) {
		ret = merge(bit[i], ret);
	}
	return ret;
}
void clear(int i) {
	for (i++; i <= n; i += i & -i) {
		bit[i] = -1;
	}
}


void cdq(int L, int R) {
	if (R - L == 1) return;
	int M = (L + R) / 2;
	cdq(L, M);
	for (int i = M; i < R; i++) tmp[i] = ind[i];
	sort(ind + L, ind + M, [&](int i, int j) {
		return a[i][0] < a[j][0];
	});
	sort(ind + M, ind + R, [&](int i, int j) {
		return a[i][0] < a[j][0];
	});
	for (int i = L, j = M; j < R; j++) {
		for (; i < M && a[ind[i]][0] <= a[ind[j]][0]; i++) {
			upd(a[ind[i]][1], ind[i]);
		}
		int z = query(a[ind[j]][1]);
		if (z != -1) {
			if (ckmax(dp[ind[j]], 1 + dp[z])) {
				par[ind[j]] = z;
			}else if (dp[ind[j]] == 1 + dp[z]) {
				ckmin(par[ind[j]], z);
			}
		}
	}
	for (int i = L; i < M; i++) clear(a[ind[i]][1]);
	for (int i = M; i < R; i++) ind[i] = tmp[i];
	cdq(M, R);
}


void solve()
{
	int x;
	while (cin >> x) {
		n = x;
		vector<vi> order(2);
		for (int j = 0; j < 2; j++) {
			for (int i = 0; i < n; i++) {
				cin >> a[i][j];
				if (j == 1) a[i][j] = -a[i][j];
				order[j].pb(a[i][j]);
			}
		}
		for (int i = 0; i < 2; i++) sort(all(order[i])), order[i].resize(unique(all(order[i])) - order[i].begin());
		for (int i = 0; i < n; i++) {
			for (int j = 0; j < 2; j++) {
				a[i][j] = lb(all(order[j]), a[i][j]) - order[j].begin();
			}
		}
		iota(ind, ind + n, 0);
		reverse(ind, ind + n);
		fill(dp, dp + n, 1);
		fill(par, par + n, -1);
		fill(bit, bit + n + 1, -1);
		cdq(0, n);
		int head = -1, ans = 0;
		for (int i = 0; i < n; i++) {
			if (ckmax(ans, dp[i])) head = i;
			else if (ans == dp[i] && i < head) head = i;
		}
		cout << ans << '\n';
		vi res;
		while (head != -1) {
			res.pb(head);
			head = par[head];
		}
		for (int i = 0; i < ans; i++) cout << res[i] + 1 << " \n"[i == ans - 1];
	}
}

int main()
{
	cin.tie(0)->sync_with_stdio(0);
	// cin.exceptions(cin.failbit);
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
