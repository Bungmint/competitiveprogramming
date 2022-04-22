// Problem: P5 - Scratch Cat and Desktop Backgrounds
// Contest: DMOJ - MALD Contest 1
// URL: https://dmoj.ca/problem/mald1p5
// Memory Limit: 512 MB
// Time Limit: 1000 ms
// 
// Powered by CP Editor (https://cpeditor.org)

//Copyright © 2022 Youngmin Park. All rights reserved.
#pragma GCC optimize("Ofast")
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



const int N = 1e6;
int tree[N + 10];
int a[N];
int co{};
int LIM;
ll ans = 0;

void upd(int i, int v) {
	for (i++; i <= LIM; i += i & -i) {
		tree[i] += v;
	}
}
int q(int r) {
	int res{};
	for (r++; r; r -= r & -r) res += tree[r];
	return res;
}
int qq(int l, int r) {
	return q(r) - q(l - 1);
}


void solve()
{
	int bl, br;
	cin >> bl >> br;
	string s;
	cin >> s;
	int n = sz(s), sm{};
	vi tmp;
	tmp.pb(sm), a[co++] = sm;
	F0R(i, n) {
		int fl = (s[i] == '1' ? 1 : -1);
		sm += 100 * fl - br;
		tmp.pb(sm);
		a[co++] = sm;
	}
	sort(all(tmp)), tmp.resize(unique(all(tmp)) - tmp.begin());
	LIM = sz(tmp);
	F0R(i, co) {
		a[i] = lb(all(tmp), a[i]) - tmp.begin();
		ans += qq(a[i], LIM - 1);
		upd(a[i], 1);
	}
	memset(tree, 0, sizeof(int) * (LIM + 1));
	tmp.clear();
	sm = 0, co = 0;
	a[co++] = sm;
	tmp.pb(sm);
	F0R(i, n) {
		int fl = (s[i] == '1' ? 1 : -1);
		sm += 100 * fl - bl;
		tmp.pb(sm);
		a[co++] = sm;
	}
	sort(all(tmp)), tmp.resize(unique(all(tmp)) - tmp.begin());
	LIM = sz(tmp);
	F0R(i, co) {
		a[i] = lb(all(tmp), a[i]) - tmp.begin();
		ans -= qq(a[i] + 1, LIM - 1);
		upd(a[i], 1);
	}
	dbg(ans);
	
	
	// Negatives
	memset(tree, 0, sizeof(int) * (LIM + 1));
	tmp.clear();
	sm = 0, co = 0;
	a[co++] = sm;
	tmp.pb(sm);
	F0R(i, n) {
		int fl = (s[i] == '1' ? 1 : -1);
		sm += 100 * fl + br;
		tmp.pb(sm);
		a[co++] = sm;
	}
	sort(all(tmp)), tmp.resize(unique(all(tmp)) - tmp.begin());
	// dbg(tmp);
	LIM = sz(tmp);
	F0R(i, co) {
		a[i] = lb(all(tmp), a[i]) - tmp.begin();
		ans += qq(0, a[i]);
		// dbg(a[i]);
		upd(a[i], 1);
	}
	// dbg(ans);
	memset(tree, 0, sizeof(int) * (LIM + 1));
	tmp.clear();
	sm = 0, co = 0;
	a[co++] = sm;
	tmp.pb(sm);
	F0R(i, n) {
		int fl = (s[i] == '1' ? 1 : -1);
		sm += 100 * fl + bl;
		tmp.pb(sm);
		a[co++] = sm;
	}
	sort(all(tmp)), tmp.resize(unique(all(tmp)) - tmp.begin());
	LIM = sz(tmp);
	F0R(i, co) {
		a[i] = lb(all(tmp), a[i]) - tmp.begin();
		ans -= qq(0, a[i] - 1);
		upd(a[i], 1);
	}
	// dbg(ans);
	// Zero
	if (bl == 0) {
		tmp.clear();
		sm = 0, co = 0;
		a[co++] = sm;
		F0R(i, n) {
			int fl = (s[i] == '1' ? 1 : -1);
			sm += fl;
			tmp.pb(sm);
			a[co++] = sm;
		}
		sort(a, a + co);
		F0R(i, co) {
			int cnt = 1;
			while (i + 1 < co && a[i] == a[i + 1]) cnt++, i++;
			ans -= 1LL * cnt * (cnt - 1LL) / 2LL;
		}
	}
	cout << ans << '\n';
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