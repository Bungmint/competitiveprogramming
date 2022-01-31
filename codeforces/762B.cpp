// Problem: B. USB vs. PS/2
// Contest: Codeforces - Educational Codeforces Round 17
// URL: https://codeforces.com/contest/762/problem/B
// Memory Limit: 256 MB
// Time Limit: 2000 ms
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
	vi v(3);
	F0R(i, 3)cin >> v[i];
	int m;
	cin >> m;
	vector<multiset<int>> st(2);
	REP(m){
		int c;
		string s;
		cin>> c>>s;
		if (s[0]=='U'){
			st[0].insert(c);
		}else{
			st[1].insert(c);
		}
	}
	ll cost = 0;
	int ans = min(v[0], sz(st[0]))+min(v[1], sz(st[1]))+min(v[2], max(0, sz(st[0])-v[0])+max(0, sz(st[1])-v[1]));
	bool ok = 1;
	dbg(st, v);
	while(ok){
		ok = 0;
		int val = 2*INF;
		int prod = 0, comp = 0;
		F0R(i, 2){
			if (sz(st[i])){
				if (v[i]){
					dbg(i);
					if (ckmin(val, *st[i].begin())) comp = prod = i;
				}else if (v[2]){
					if (ckmin(val, *st[i].begin())) comp = 2, prod = i;
				}
			}
		}
		ok |= (val<2*INF);
		if (val<2*INF){
			cost += *st[prod].begin();
			st[prod].erase(st[prod].begin());
			v[comp]--;
		}
	}
	cout << ans << " "<< cost << "\n";
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