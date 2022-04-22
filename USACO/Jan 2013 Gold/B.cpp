// Problem: Problem 2. Island Travels
// Contest: USACO - USACO 2013 January Contest, Gold
// URL: http://www.usaco.org/index.php?page=viewproblem2&cpid=230
// Memory Limit: 256 MB
// Time Limit: 4000 ms
// 
// Powered by CP Editor (https://cpeditor.org)

//Copyright © 2022 Youngmin Park. All rights reserved.
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
const int MOD = 1e9 + 7; //998244353;
const ld PI = acos((ld)-1.0);
const int dx[4] = {1, 0, -1, 0}, dy[4] = {0, 1, 0, -1};
mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());
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

int dist[15][50][50];
int cov[1 << 15][15];
bool vis[50][50];

void solve()
{
	int n, m;
	cin >> n >> m;
	vector<string> a(n);
	for (auto &e : a) cin >> e;

	vector<vpi> island;
	F0R(i, n) F0R(j, m) {
		if (a[i][j] == 'X' && !vis[i][j]) {
			vpi nxt;
			nxt.pb({i, j});
			vis[i][j] = 1;
			queue<pii> q;
			q.push({i, j});
			while (sz(q)) {
				auto [r, c] = q.front(); q.pop();
				F0R(k, 4) {
					int nr = dx[k] + r, nc = dy[k] + c;
					if (nr >= n || nc >= m || nr < 0 || nc < 0) continue;
					if (a[nr][nc] == 'X' && !vis[nr][nc]) {
						vis[nr][nc] = 1;
						q.push({nr, nc});
					}
				}
			}
			island.pb(nxt);
		}
	}
	memset(dist, 0x3f, sizeof(dist));
	int cnt = sz(island);
	F0R(i, sz(island)) {
		deque<pii> q;
		for (auto &[r, c] : island[i]) {
			q.pb({r, c});
			dist[i][r][c] = 0;
		}
		while (sz(q)) {
			auto [r, c] = q.front();
			q.pop_front();
			int d = dist[i][r][c];
			F0R(k, 4) {
				int nr = r + dx[k], nc = c + dy[k];
				if (nr >= n || nc >= m || nr < 0 || nc < 0) continue;
				if (a[nr][nc] == '.') continue;
				if (a[nr][nc] == 'X' && ckmin(dist[i][nr][nc], d)) {
					q.push_front({nr, nc});
				}else if (a[nr][nc] == 'S' && ckmin(dist[i][nr][nc], d + 1)) {
					q.pb({nr, nc});
				}
			}
		}
	}
	int ans = {2 * INF};
	memset(cov, 0x3f, sizeof(cov));
	F0R(i, cnt) cov[1 << i][i] = 0;
	F0R(mask, 1 << cnt) {
		F0R(last, cnt) {
			if (!((1 << last) & mask)) continue;
			int prevMask = mask ^ (1 << last);
			auto [r, c] = island[last].front();
			F0R(j, cnt) {
				if ((1 << j) & prevMask) {
					ckmin(cov[mask][last], cov[prevMask][j] + dist[j][r][c]);

				}
			}
			if (mask == (1 << cnt) - 1) {
				ckmin(ans, cov[mask][last]);
			}
		}
	}
	cout << ans << "\n";
	
	
}

int main()
{
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);
    int testcase=1;
    setIO("island");
    // cin >> testcase;
    while (testcase--)
    {
        solve();
    }
}