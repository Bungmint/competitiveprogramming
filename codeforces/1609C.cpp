// Problem: C. Complex Market Analysis
// Contest: Codeforces - Deltix Round, Autumn 2021 (open for everyone, rated, Div. 1 + Div. 2)
// URL: https://codeforces.com/contest/1609/problem/C
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

const int N = 1e6; // Only advised to use it under 1e7 (More Memory)
int lp[N + 1];
vector<int> pr;
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
	int n, e;
	cin >> n >> e;
	vi a(n+1);
	FOR(i,1, n+1) cin >> a[i];
	vi isPrime(n+1), nxtPrime(n+1, -1), nxtNO(n+1, -1);
	vector<bool> vis(n+1);
	ROF(i, 1, n+1){
		if (a[i]==1) isPrime[i] = 0;
		if (a[i]>1&&lp[a[i]]==a[i]) isPrime[i] = 1;
		else if (a[i]>1) isPrime[i] = -1;
	}
	ROF(i, 1, n+1){
		if (vis[i]) break;
		int id = -1;
		int j = i;
		while(j>0){
			vis[j] = 1;
			nxtPrime[j] = id;
			if (isPrime[j]==-1) id = -1;
			else if (isPrime[j]==1) id = j;
			j-=e;
		}
	}
	fill(all(vis), false);
	ROF(i, 1, n+1){
		if (vis[i]) break;
		int id = -1;
		int j = i;
		while(j>0){
			vis[j] = 1;
			nxtNO[j] = id;
			if (isPrime[j]) id = j;
			j-=e;
		}
	}
	ll ans = 0;
	FOR(i, 1, n+1){
		if (isPrime[i]==0){
			if (nxtPrime[i]==-1) continue;
			int cnt = 0;
			if (nxtNO[nxtPrime[i]]==-1) cnt += (n-nxtPrime[i])/e;
			else cnt += (nxtNO[nxtPrime[i]]-nxtPrime[i]-e)/e;
			ans += 1+cnt;
		}else if (isPrime[i] == 1){
			if (nxtNO[i]==-1){
				ans += (n-i)/e;
			}else{
				ans += (nxtNO[i]-i-e)/e;
			}
		}
	}
	cout << ans << "\n";
}

int main()
{
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);
    int testcase=1;
    linsieve();
    cin >> testcase;
    while (testcase--)
    {
        solve();
    }
}