// Problem: D. Rectangles
// Contest: Codeforces - 2016 ACM Amman Collegiate Programming Contest
// URL: https://codeforces.com/gym/101102/problem/D
// Memory Limit: 256 MB
// Time Limit: 5000 ms
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

#define int long long

ll calc(ll n) {
	return n * (n - 1) / 2;
}

void solve()
{
	int r, c;
	cin >> r >> c;
	vpi a(c);
	vi L(c), R(c), pref(c);
	ll ans = 0;
	F0R(i, r) {
		pref[0] = 0;
		F0R(j, c) {
			int x;
			cin >> x;
			if (a[j].fi != x) a[j] = {x, 1};
			else a[j].se++;
			if (j) pref[j] = pref[j - 1];
			pref[j] += a[j].se;
		}	
		stack<int> st;
		map<pii, vi> mp;
		F0R(j, c) {
			while (sz(st) && a[st.top()].fi == a[j].fi && a[st.top()].se >= a[j].se) st.pop();
			L[j] = (sz(st) ? st.top() : -1);
			st.push(j);
		}
		while (sz(st)) st.pop();
		R0F(j, c) {
			while (sz(st) && a[st.top()].fi == a[j].fi && a[st.top()].se >= a[j].se) st.pop();
			R[j] = (sz(st) ? st.top() : c);
			st.push(j);
		}
		F0R(j, c) {
			mp[make_pair(L[j] + 1, R[j] - 1)].pb(j);
		}
		for (auto &[p, v] : mp) {
			auto [l, r] = p;
			auto h = a[v.front()].se;
			int totW = r - l + 1;
			ans += calc(totW + 1) * h;
			F0R(k, sz(v)) {
				if (k == 0) {
					int lll = l, rrr = v[k] - 1;
					if (lll <= rrr) {
						int w = rrr - lll + 1;
						ans -= calc(w + 1) * h;
					}
				}else{
					int lll = v[k - 1] + 1, rrr = v[k] - 1;
					if (lll <= rrr) {
						int w = rrr - lll + 1;
						ans -= calc(w + 1) * h;
					}
				}
			}
			int lll = v[sz(v) - 1] + 1, rrr = r;
			if (lll <= rrr) {
				int w = rrr - lll + 1;
				ans -= calc(w + 1) * h;
			}
		}
		dbg(ans);
	}
	cout << ans << "\n";
}

int32_t main()
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