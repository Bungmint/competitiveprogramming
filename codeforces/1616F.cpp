// Problem: F. Tricolor Triangles
// Contest: Codeforces - Good Bye 2021: 2022 is NEAR
// URL: https://codeforces.com/problemset/problem/1616/F
// Memory Limit: 256 MB
// Time Limit: 1000 ms
// 
// Powered by CP Editor (https://cpeditor.org)

//Copyright © 2022 Youngmin Park. All rights reserved.
// #pragma GCC optimize("Ofast")
// #pragma GCC target("avx2")
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

const int mod = 3;

int solveLinear(vector<vi>& A, vi& b, vi& x) {
	int n = sz(A), m = sz(x), rank = 0, br, bc;
	if (n) assert(sz(A[0]) == m);
	vi col(m); iota(all(col), 0);
	FOR(i, 0, n) {
		dbg(A);
		int v, bv = 0;
		FOR(r, i, n) FOR(c, i, m)
			if (A[r][c] != 0) {
				br = r, bc = c, bv = A[r][c];
				break;
			}
		if (bv == 0) {
			FOR(j, i, n) if (b[j]) return -1;
			break;
		}
		swap(A[i], A[br]);
		swap(b[i], b[br]);
		swap(col[i], col[bc]);
		FOR(j, 0, n) swap(A[j][i], A[j][bc]);
		bv = A[i][i];
		FOR(j, i+1, n) {
			int fac = A[j][i] * bv % mod;
			b[j] -= fac * b[i];
			b[j] %= mod;
			if (fac)
			{
				FOR(k, i+1, m) {
					A[j][k] -= fac*A[i][k];
					A[j][k] %= mod;
				}
			}
		}
		rank++;
	}
	x.assign(m, 0);
	for (int i = rank; i--;) {
		b[i] *= A[i][i];
		b[i] %= mod;
		x[col[i]] = b[i];
		FOR(j, 0, i) {
			b[j] -= A[j][i] * b[i];
			b[j] %= mod;
		}
	}
	return rank; // (multiple solutions if rank < m)
}

vector<vi> t;
vi b, x;
int n, m;

void insert_eq(const vi& a) {
	b.pb(a.back());
	vi ret(m);
	F0R(i, sz(a) - 1) ret[a[i]] = 1;
	t.pb(ret);
}


void solve()
{
	cin >> n >> m;
	t.clear(), b.clear(), x.clear();
	x.resize(m);
	vector<vector<int>> adj(n, vi(n, -1));
	vi col(m);
	F0R(i, m) {
		int a, b, c;
		cin >> a >> b >> c;
		a--, b--;
		adj[a][b] = adj[b][a] = i;
		col[i] = c;
		if (~c) insert_eq({i, c});
	}
	F0R(i, n) FOR(j, i + 1, n) FOR(k, j + 1, n) {
		if (adj[i][j] != -1 && adj[j][k] != -1 && adj[k][i] != -1) {
			auto xx = adj[i][j];
			auto yy = adj[j][k];
			auto zz = adj[k][i];
			insert_eq({adj[i][j], adj[j][k], adj[k][i], 0});
		}
	}
	int z = solveLinear(t, b, x);
	if (z == -1) {
		cout << z << '\n';
		return;
	}
	F0R(i, m) {
		if (x[i] <= 0) x[i] += 3;
		cout << x[i] << ' ';
	}
	cout << '\n';
}

int main()
{
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);
    int testcase=1;
    cin >> testcase;
    while (testcase--)
    {
        solve();
    }
}