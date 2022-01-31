// Problem: C2. Skyscrapers (hard version)
// Contest: Codeforces - Codeforces Round #622 (Div. 2)
// URL: https://codeforces.com/problemset/problem/1313/C2
// Memory Limit: 512 MB
// Time Limit: 3000 ms
// 
// Powered by CP Editor (https://cpeditor.org)

//Copyright © 2021 Youngmin Park. All rights reserved.
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

#define all(v) (v).begin(), (v).end()
#define ar array
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

struct chash
{
    static uint64_t splitmix64(uint64_t x)
    {
        x += 0x9e3779b97f4a7c15;
        x = (x ^ (x >> 30)) * 0xbf58476d1ce4e5b9;
        x = (x ^ (x >> 27)) * 0x94d049bb133111eb;
        return x ^ (x >> 31);
    }

    size_t operator()(uint64_t x) const
    {
        static const uint64_t FIXED_RANDOM = chrono::steady_clock::now().time_since_epoch().count();
        return splitmix64(x + FIXED_RANDOM);
    }
    size_t operator()(pair<uint64_t,uint64_t> x) const {
		static const uint64_t FIXED_RANDOM = chrono::steady_clock::now().time_since_epoch().count();
		return splitmix64(x.first + FIXED_RANDOM)^(splitmix64(x.second + FIXED_RANDOM) >> 1);
	}
};

void setIO(string s)
{
    freopen((s + ".in").c_str(), "r", stdin);
    freopen((s + ".out").c_str(), "w", stdout);
}

void solve()
{
	int n;
	cin >> n;
	vl a(n), L(n), R(n), dpL(n), dpR(n);
	stack<int> st;
	F0R(i, n) cin >> a[i];
	ll sum = 0, id = 0;
	F0R(i, n){
		while(!st.empty()&&a[st.top()]>=a[i]){
			st.pop();
		}
		L[i] = (st.empty()? -1: st.top());
		st.push(i);
		dpL[i] = a[i]*(i-L[i]);
		if (L[i]>=0) dpL[i] += dpL[L[i]];
	}
	while(sz(st)) st.pop();
	R0F(i, n){
		while(!st.empty()&&a[st.top()]>=a[i]){
			st.pop();
		}
		R[i] = (st.empty()? n: st.top());
		st.push(i);
		dpR[i] = a[i]*(R[i]-i);
		if (R[i]<n) dpR[i] += dpR[R[i]];
	}
	F0R(i, n){
		ll val = dpL[i]+dpR[i]-a[i];
		if (ckmax(sum, val)) id = i;
	}
	dbg(dpL, dpR);
	dbg(id);
	vl ans;
	ll cur = a[id];
	R0F(i, id){
		ckmin(cur, a[i]);
		ans.pb(cur);
	}
	reverse(all(ans));
	cur = a[id];
	FOR(i, id, n){
		ckmin(cur, a[i]);
		ans.pb(cur);
	}
	for (auto x:ans)cout << x << " ";
	cout << "\n";
	
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