//Copyright © 2022 Youngmin Park. All rights reserved.
#pragma GCC optimize("O3")
#pragma GCC target("avx2")
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
const int MOD = 1e9 + 7; //998244353;
const ld PI = acos((ld)-1.0);
const int dx[4] = {1, 0, -1, 0}, dy[4] = {0, 1, 0, -1};
mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());
template <typename T>
using pqg = priority_queue<T, vector<T>, greater<T>>;
template <typename T>
inline bool ckmin(T &a, const T &b) { return b < a ? a = b, 1 : 0; }
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
    cerr << endl;
}
template <typename Head, typename... Tail>
void dbg_out(Head H, Tail... T)
{
    cerr << ' ' << H;
    dbg_out(T...);
}
#ifdef LOCAL
#define dbg(...) cerr << "(" << #__VA_ARGS__ << "):", dbg_out(__VA_ARGS__)
#else
#define dbg(...) 42
#endif

inline namespace RecursiveLambda{
	template <typename Fun>
	struct y_combinator_result{
		Fun fun_;
		template <typename T> 
		explicit y_combinator_result(T &&fun): fun_(forward<T>(fun)){}
		template <typename...Args>
		decltype(auto) operator()(Args &&...args){
			return fun_(ref(*this), forward<Args>(args)...);
		}
	};
	template <typename Fun>
	decltype(auto) y_combinator(Fun &&fun){
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

bool vis[800][800];

void solve()
{
	int n, S;
	cin >> n >> S;
	vector<string> grid(n);
	for (auto &s : grid) cin >> s;
	pii st, en{};
	vector<vi> distHive(n, vi(n, INF));
	queue<pii> bee;
	F0R(i, n) F0R(j, n) {
		if (grid[i][j] == 'M') {
			st = {i, j};
		}
		if (grid[i][j] == 'H') {
			distHive[i][j] = 0;
			bee.push({i, j});
		}
		if (grid[i][j] == 'D') {
			en = {i, j};
		}
	}
	while (sz(bee)) {
		auto [r, c] = bee.front();
		bee.pop();
		F0R(i, 4) {
			int nr = r + dx[i], nc = c + dy[i];
			if (nr < 0 || nc < 0 || nr >= n || nc >= n) continue;
			if (grid[nr][nc] == 'T' || grid[nr][nc] == 'D') continue;
			if (ckmin(distHive[nr][nc], distHive[r][c] + 1)) {
				bee.push({nr, nc});
			}
		}
	}
	int l = 0, r = distHive[st.fi][st.se] - 1, ans = -1;
	while (l <= r) {
		int mid = (l + r) / 2;
		int tt = mid;
		queue<pair<int, pii>> q, nxt;
		memset(vis, 0, sizeof(bool) * 800 * 800);
		q.push({0, st});
		vis[st.fi][st.se] = 1;
		while (sz(q)) {
			while (sz(q)) {
				auto [x, y] = q.front().se;
				auto d = q.front().fi;
				q.pop();
				if (d == S) {
					if (distHive[x][y] > tt + 1) nxt.push({0, {x, y}});
					continue;
				}
				F0R(i, 4) {
					int nx = x + dx[i], ny = y + dy[i];
					if (nx < 0 || ny < 0 || nx >= n || ny >= n) continue;
					if (grid[nx][ny] == 'T') continue;
					if (distHive[nx][ny] <= tt) continue;
					if (!vis[nx][ny]) {
						vis[nx][ny] = 1;
						q.push({d + 1, {nx, ny}});
					}
				}
			}
			while (sz(nxt)) q.push({0, nxt.front().se}), nxt.pop();
			tt++;
		}
		if (vis[en.fi][en.se]) ans = mid, l = mid + 1;
		else r = mid - 1;
	}
	cout << ans;
}

int main()
{
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);
    int testcase=1;
    // cin >> testcase;
    while (testcase--)
    {
        solve();
    }
}