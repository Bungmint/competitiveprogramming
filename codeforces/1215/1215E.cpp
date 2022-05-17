// Problem: E. Marbles
// Contest: Codeforces - Codeforces Round #585 (Div. 2)
// URL: https://codeforces.com/contest/1215/problem/E
// Memory Limit: 256 MB
// Time Limit: 4000 ms
// 
// Powered by CP Editor (https://cpeditor.org)

#pragma GCC optimize("O3")
#pragma GCC target("sse4")
#include <bits/stdc++.h>
using namespace std;

using ll = long long;
using vi = vector<int>;
using pi = pair<int, int>;
using vpi = vector<pair<int, int>>;
using pl = pair<ll, ll>;
using vl = vector<ll>;
using vpl = vector<pl>;
using ld = long double;

#define all(v) (v).begin(), (v).end()
#define ar array
#define pb push_back
#define sz(x) (int)(x).size()
#define fi first
#define se second
#define lb lower_bound

template <typename T>
using pqg = priority_queue<T, vector<T>, greater<T>>;
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

struct custom_hash
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
};

void setIO(string s)
{
    freopen((s + ".in").c_str(), "r", stdin);
    freopen((s + ".out").c_str(), "w", stdout);
}

mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());

const int INF = 1e9;
const ll LINF = 1e18;
const int MOD = 1e9 + 7; //998244353;
const int N = 4e5+10;
ll dp[1<<20], a[N], pref[N][20], lastInd[20];
ll extraMoves[20][20], cnt[20];
int n;

void solve()
{
	cin >> n;
	for (int i=1;i<=n;++i) cin >> a[i], a[i]--;
	for (int i=1;i<=n;++i){
		for (int j=0;j<20;++j) pref[i][j] = pref[i-1][j];
		pref[i][a[i]]++;
		cnt[a[i]]++;
	}
	for (int i=1;i<=n;++i){
		for (int j=0;j<20;++j){
			if (a[i]==j) continue;
			extraMoves[a[i]][j] += (ll)cnt[a[i]]* ((ll)pref[i-1][j]-(ll)pref[lastInd[a[i]]][j]);
		}
		cnt[a[i]]--;
		lastInd[a[i]] = i;
	}
	fill(dp, dp+(1<<20), LINF);
	dp[0] = 0;
	for (int mask=1;mask<(1<<20);++mask){
		for (int last = 0; last<20;++last){
			if (!(mask&(1<<last))) continue;
			int prevMask = mask - (1<<last);
			if (dp[prevMask]==INF) continue;
			if (!lastInd[last]) dp[mask]=min(dp[mask],dp[prevMask]);
			else{
				ll res = 0;
				for (int j=0;j<20;++j){
					if ((1<<j)&mask) continue;
					res += extraMoves[last][j];
				}
				dp[mask] = min(dp[mask], dp[prevMask]+res);
			}
		}
	}
	cout << dp[(1<<20)-1]<<endl;
}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int testcase=1;
    // cin >> testcase;
    while (testcase--)
    {
        solve();
    }
}