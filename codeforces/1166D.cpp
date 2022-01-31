// Problem: D. Cute Sequences
// Contest: Codeforces - Codeforces Round #561 (Div. 2)
// URL: https://codeforces.com/contest/1166/problem/D
// Memory Limit: 256 MB
// Time Limit: 1000 ms
// 
// Powered by CP Editor (https://cpeditor.org)

#pragma GCC optimize("O3")
#pragma GCC target("sse4")
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
#define dbg(...)
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

const ld EPS = 1e-9;
bool hi(ld a, ld b){return a-b>EPS;}

void solve()
{
	ll a, b, m;
	cin >> a >> b >> m;
	if (a==b){
		cout << 1 << " ";
		cout << a << "\n";
		return;
	}
	FOR(i, 2, 51){
		ll L = a+1, R = a+m;
		ll shift = b>>(i-2LL);
		if (L<=shift){
			vl r(i+1, 1), ans(i+1), pref(i+1);
			if (shift==R&&b==(R<<(i-2))){
				dbg();
				ans[1] = a, pref[1] = a;
				FOR(j, 2,i+1) ans[j] = pref[j-1]+m, pref[j]=pref[j-1]+ans[j];
				cout << i << " ";
				FOR(j, 1, i+1) cout << ans[j]<<" ";
				cout << "\n";
				return;
			}else if (shift<R){
				dbg();
				ll dif = b - ((L)<<(i-2));
				FOR(j, 1, i){
					if (j==i-1){
						ll mi = min(m-1, dif);
						r[j] += mi;
						dif -= mi;
						continue;
					}
					ll mi = min(m-1, (dif>>(i-j-2)));
					r[j] += mi;
					dif -= mi*(1LL<<(i-j-2));
				}
				ans[1] = a, pref[1] = a;
				FOR(j, 2,i+1) ans[j] = pref[j-1]+r[j-1], pref[j]=pref[j-1]+ans[j];
				cout << i << " ";
				FOR(j, 1, i+1) cout << ans[j]<<" ";
				cout << "\n";
				return;
			}
		}
	}
	cout << -1 << "\n";
}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int testcase;
    cin >> testcase;
    while (testcase--)
    {
        solve();
    }
}