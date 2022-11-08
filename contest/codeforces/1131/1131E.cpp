// Problem: E. String Multiplication
// Contest: Codeforces - Codeforces Round #541 (Div. 2)
// URL: https://codeforces.com/problemset/problem/1131/E
// Memory Limit: 256 MB
// Time Limit: 2000 ms
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

void solve()
{
	int n, k;
	cin>>n;
	vl dp(26);
	string s;
	cin >> s;
	k = sz(s);
	for (int i=0;i<k;++i){
		ll cnt =1;
		while(i+1<k&&s[i+1]==s[i]){
			i++;
			cnt++;
		}
		dp[s[i]-'a'] = max(dp[s[i]-'a'], cnt);
	}
	
	for (int i=1;i<n;++i){
		vl nxt(26);
		cin >> s;
		k = sz(s);
		vector<pl> v;
		for (int j=0;j<26;++j) nxt[j] = max((ll)(dp[j]>0), nxt[j]);
		for (int j=0;j<k;++j){
			ll cnt =1;
			while(j+1<k&&s[j+1]==s[j]){
				j++;
				cnt++;
			}
			nxt[s[j]-'a'] = max(nxt[s[j]-'a'], cnt);
			v.pb({s[j]-'a', cnt});
		}
		if (sz(v)==1){
			pl p = v.front();
			dbg(p);
			dbg(dp[p.fi], nxt[p.fi], p.se*dp[p.fi]+p.se+dp[p.fi]);
			nxt[p.fi] = max(nxt[p.fi], p.se*dp[p.fi]+p.se+dp[p.fi]);
		}else{
			pl p = v.front(), q = v.back();
			if (p.fi!=q.fi){
				nxt[p.fi] = max(p.se+ (!!dp[p.fi]) , nxt[p.fi]);
				nxt[q.fi] = max(q.se + (!!dp[q.fi]), nxt[q.fi]);
 			}else if (dp[p.fi]){
 				nxt[p.fi] = max(p.se+q.se+1, nxt[p.fi]);
 			}
		}	
		for (int j=0;j<26;++j) dp[j] = nxt[j];
		dbg(dp);
	}
	dbg(dp);
	ll res = 0;
	for (int i=0;i<26;++i){
		res = max(res, dp[i]);
	}
	cout << res << endl;
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