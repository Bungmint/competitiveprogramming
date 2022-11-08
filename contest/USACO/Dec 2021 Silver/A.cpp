// Problem: Problem 1. Closest Cow Wins
// Contest: USACO - USACO 2021 December Contest, Silver
// URL: http://www.usaco.org/index.php?page=viewproblem2&cpid=1158
// Memory Limit: 256 MB
// Time Limit: 4000 ms
// 
// Powered by CP Editor (https://cpeditor.org)

//Copyright © 2021 Youngmin Park. All rights reserved.
// #pragma GCC optimize("O3")
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
	int k, m, n; ll ans = 0;
	cin >> k>> m >> n;
	vl p(k), t(k), ind(k), cow(m), pref(k);
	F0R(i,k) cin >> p[i] >> t[i], p[i]*=2;
	for (auto&e:cow) cin>>e, e*=2;
	sort(all(cow)), iota(all(ind), 0), sort(all(ind), [&](ll i, ll j){
		return p[i]<p[j];
	});
	F0R(i, k) pref[i] = t[ind[i]] + (i?pref[i-1]:0);
	auto lower = [&](int x){
		if (p[ind[k-1]]<x) return k;
		int l = 0, r = k-1, ans = 0;
		while(l<=r){
			int mid = (l+r)/2;
			if (p[ind[mid]]>=x) ans = mid, r = mid - 1;
			else l = mid + 1;
		}
		return ans; 
	};
	auto upper = [&](int x){
		if (p[ind[k-1]]<=x) return k;
		int l = 0, r = k-1, ans = 0;
		while(l<=r){
			int mid = (l+r)/2;
			if (p[ind[mid]]>x) ans = mid, r = mid - 1;
			else l = mid + 1;
		}
		return ans; 
	};
	multiset<ll> st;
	FOR(i, 0, m){
		if (!i){
			int id = lower(cow[i]) - 1;
			if (id>=0) st.insert(pref[id]);
		}else{
			int idL = lower(cow[i-1]), idR = lower(cow[i]) - 1;
			if (idL>idR) continue;
			ll slide = 0, tot = pref[idR] - (idL? pref[idL-1]:0);
			FOR(j, idL, idR+1){
				ll x = 2*p[ind[j]]-cow[i-1] - 1;
				if (x>=cow[i]) break;
				ll RR = (x+cow[i])/2;
				int idrr = upper(RR) - 1;
				ll val = pref[idrr] - (j? pref[j-1]:0);
				ckmax(slide, val);
			}
			st.insert(slide);
			if (tot-slide) assert(tot-slide>0), st.insert(tot-slide);
		}
	}
	int id = lower(cow[m-1]);
	if (id<=k){
		ll val = pref[k-1];
		if (id) val -= pref[id-1];
		st.insert(val);
	}
	dbg(st);
	while(sz(st)&&n){
		ans += *st.rbegin();
		st.erase(--st.end());
		n--;
	}
	cout << ans;
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