// Problem: Sliding Cost
// Contest: CSES - CSES Problem Set
// URL: https://cses.fi/problemset/task/1077
// Memory Limit: 512 MB
// Time Limit: 1000 ms
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
	int n, k;
	cin >> n >> k;
	vi a(n);
	multiset<int> small, large;
	ll smallS{}, largeS{};
	for (auto &e : a) cin >> e;
	auto add = [&](int u) {
		if (sz(small) == 0) {
			small.insert(u);
			smallS += u;
			return;
		}
		if (*small.rbegin() <= u) {
			large.insert(u);
			largeS += u;
			if (sz(large) > sz(small)) {
				smallS += *large.begin();
				largeS -= *large.begin();
				small.insert(*large.begin()), large.erase(large.begin());
			}
		}else{
			small.insert(u);
			smallS += u;
			if (sz(small) > sz(large) + 1) {
				smallS -= *small.rbegin();
				largeS += *small.rbegin();
				large.insert(*small.rbegin()), small.erase(--small.end());
			}
		}
	};
	auto remove = [&](int u) {
		if (*small.rbegin() < u) {
			large.erase(large.find(u));
			largeS -= u;
			if (sz(large) + 1 < sz(small)) {
				smallS -= *small.rbegin();
				largeS += *small.rbegin();
				large.insert(*small.rbegin()), small.erase(--small.end());
			}
		}else{
			small.erase(small.find(u));
			smallS -= u;
			if (sz(small) < sz(large)) {
				smallS += *large.begin();
				largeS -= *large.begin();
				small.insert(*large.begin()), large.erase(large.begin());
			}
		}
	};
	auto calc = [&]() -> ll {
		ll median = *small.rbegin();
		return largeS - median * sz(large) + median * sz(small) - smallS;
	};
	F0R(i, k) add(a[i]);
	cout << calc() << " ";
	FOR(i, k, n) {
		add(a[i]);
		remove(a[i - k]);
		dbg(small, large, largeS, smallS);
		cout << calc() << " ";
	}
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