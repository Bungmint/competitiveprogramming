// Problem: F. Let's Play the Hat?
// Contest: Codeforces - Codeforces Round #762 (Div. 3)
// URL: https://codeforces.com/contest/1619/problem/F
// Memory Limit: 256 MB
// Time Limit: 2000 ms
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

void solve()
{
	int n, m, k;
	cin >> n >> m >> k;
	if (n % m == 0) {
		int x = n / m;
		REP(k) {
			FOR(i, 0, m) {
				cout << x << " ";
				F0R(j, x) {
					cout << i * x + j + 1 << " ";
				}
				cout << "\n";
			}
		}
		cout << "\n";
		return;
	}
	int r = n % m, x = n / m;
	int cnt = (1LL * r * (x + 1) * k) / n;
	int rem = (1LL * r * (x + 1) * k) % n;
	set<pii> st;
	F0R(i, k) st.insert({r * (x + 1), i});
	vector<vi> ans(k);
	F0R(i, n) {
		vpi todo;
		if (rem) {
			REP(cnt + 1) {
				auto [z, t] = *--st.end();
				st.erase(--st.end());
				todo.pb({z, t});
			}
			rem--;
		}else{
			REP(cnt) {
				auto [z, t] = *--st.end();
				st.erase(--st.end());
				todo.pb({z, t});
			}
		}
		for (auto &[z, t] : todo) {
			if (z - 1 > 0) st.insert({z - 1, t});
			ans[t].pb(i);
		}
	}
	F0R(i, k) {
		vi cool(n);
		vi lo, hi;
		for (auto &e : ans[i]) {
			cool[e] = 1;
		}
		F0R(j, n) {
			if (cool[j]) hi.pb(j);
			else lo.pb(j);
		}
		F0R(j, m - r) {
			cout << x;
			FOR(id, j * (x), (j + 1) * (x)) {
				cout << " " << lo[id] + 1;
			}
			cout << "\n";
		}
		F0R(j, r) {
			cout << x + 1;
			FOR(id, j * (x + 1), (j + 1) * (x + 1)) {
				cout << " " << hi[id] + 1;
			}
			cout << "\n";
		}
	}
	cout << "\n";
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