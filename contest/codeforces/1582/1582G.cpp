// Problem: G. Kuzya and Homework
// Contest: Codeforces - Codeforces Round #750 (Div. 2)
// URL: https://codeforces.com/contest/1582/problem/G
// Memory Limit: 512 MB
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

const int N = 1e6; // Only advised to use it under 1e7 (More Memory)
int lp[N + 1];
vector<int> pr;
vpi st[N + 1];
int nxt[N];
void linsieve()
{
    for (int i = 2; i <= N; i++)
    {
        if (lp[i] == 0)
        {
            lp[i] = i;
            pr.push_back(i);
        }
        for (int j = 0; j < (int)pr.size() && pr[j] <= lp[i] && i * pr[j] <= N; ++j)
        {
            lp[i * pr[j]] = pr[j];
        }
    }
}



void solve()
{
	int n;
	cin >> n;
	vi a(n), L(n), R(n);
	string s;
	for (auto &e : a) cin >> e;
	cin >> s;
	int last = -1;
	F0R(i, n) {
		int x = a[i];
		nxt[i] = i;
		while (x > 1) {
			int cnt = 0, p = lp[x];
			while (x % p == 0) x /= p, cnt++;
			if (s[i] == '*') {
				nxt[i] = i;
				st[p].push_back({cnt, i});
			}else{
				cnt = -cnt;
				while (cnt < 0 && sz(st[p])) {
					auto [y, id] = st[p].back();
					st[p].pop_back();
					ckmin(nxt[i], id);
					int z = min(y, -cnt);
					cnt += z;
					y -= z;
					if (y) st[p].push_back({y, id});
				}
				if (cnt < 0) {
					nxt[i] = -1;
					last = i;
				}
				if (nxt[i] < last) {
					nxt[i] = -1;
					last = i;
				}
			}
		}
		dbg(nxt[i]);
	}
	stack<int> stL, stR;
	F0R(i, n) {
		while (sz(stL) && nxt[stL.top()] > nxt[i]) stL.pop();
		if (sz(stL)) L[i] = stL.top();
		else L[i] = -1;
		stL.push(i);
	}
	R0F(i, n) {
		while (sz(stR) && nxt[stR.top()] >= nxt[i]) stR.pop();
		if (sz(stR)) R[i] = stR.top();
		else R[i] = n;
		stR.push(i);
	}
	ll ans{};
	F0R(i, n) {
		int l = L[i] + 1;
		if (nxt[i] < l) continue;
		int r = R[i] - 1;
		ans += 1LL * (nxt[i] - l + 1) * (r - i + 1);
		dbg(ans);
	}
	cout << ans << '\n';
}

int main()
{
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);
    int testcase=1;
    linsieve();
    // cin >> testcase;
    while (testcase--)
    {
        solve();
    }
}