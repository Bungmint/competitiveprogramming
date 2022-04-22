// Problem: G. Xor Plains
// Contest: Codeforces - Infoleague Winter 2021 Training Round
// URL: https://codeforces.com/gym/103449/problem/G
// Memory Limit: 64 MB
// Time Limit: 500 ms
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
	int n;
	cin >> n;
	int z = n % 4;
	if (z == 3) {
		FOR(i, 1, n + 1) {
			cout << i << ' ';
		}
	}else if (z == 0) {
		int mask = n - 1;
		int hi = 31 - __builtin_clz(mask);
		FOR(i, 1, n - 1) {
			cout << i << ' ';
		}
		cout << (1 << (hi + 1)) << ' ';
		cout << (mask ^ (1 << (hi + 1))) << ' ';
	}else if (z == 2) {
		int mask = n - 2;
		int hi = 31 - __builtin_clz(mask);
		FOR(i, 1, n - 1) {
			cout << i << ' ';
		}
		cout << (1 << (hi + 1)) << ' ';
		cout << (mask ^ (1 << (hi + 1))) << ' ';
	}else {
		int mask = n - 2;
		int hi = 31 - __builtin_clz(mask);
		int a, b, c;
		ar<int, 2> mi{INF, INF};
		F0R(i, 20) {
			if ((1 << i) & mask) continue;
			int ins = i;
			F0R(j, 2) {
				if (mi[j] > ins) swap(ins, mi[j]);
			}
		}
		dbg(hi, mi);
		if (hi < mi[0]) {
			a = 1 << mi[0];
			b = 1 << mi[1];
			c = a ^ b ^ mask;
		}else if (hi < mi[1]) {
			a = mask ^ (1 << mi[0]);
			F0R(i, mi[0]) a ^= (1 << i);
			b = 1 << mi[1];
			c = a ^ b ^ mask;
		}else {
			a = mask ^ (1 << mi[0]);
			F0R(i, mi[0]) a ^= (1 << i);
			b = mask ^ (1 << mi[1]);
			F0R(i, mi[1]) if (b & (1 << i)) b ^= (1 << i);
			c = mask ^ a ^ b;
		}
		FOR(i, 1, n - 2) {
			cout << i << ' ';
		}
		cout << a << ' ' << b << ' ' << c;
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