// Problem: D. Unshuffling a Deck
// Contest: Codeforces - Codeforces Global Round 11
// URL: https://codeforces.com/contest/1427/problem/D
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
	int n;
	cin >> n;
	vi a(n);
	for (int i=0;i<n;++i) cin >> a[i],a[i]--;
	vector<bool> isConnected(n-1, false);
	for (int i=0;i<n-1;++i) if (a[i]==a[i+1]-1) isConnected[a[i]] = true;
	vector<vi> ans;
	while(true){
		bool ok = 1;
		for (int i=0;i<n-1;++i){
			ok &= isConnected[i];
		}
		if (ok) break;
		vi pos(n), b;
		for (int i=0;i<n;++i){
			pos[a[i]] = i;
		}
		int x=-1;
		for (int i=0;i<n-1;++i){
			if (!isConnected[i]&&pos[i]>pos[i+1]){
				x = i;
			}
		}
		assert(x!=-1);
		int flen = 1;
		while(pos[x+1]+flen<pos[x]&&a[pos[x+1]+flen]==x+1+flen){
			flen++;
		}
		if(pos[x+1]==0&&pos[x]==n-1){
			ans.pb({2, flen, n-flen});
			for (int i=flen;i<n;++i) b.pb(a[i]);
			for (int i=0;i<flen;++i) b.pb(a[i]);
		}else if (pos[x+1]==0){
			ans.pb({3, flen, pos[x]-flen+1, n-pos[x]-1});
			for (int i=pos[x]+1;i<n;++i) b.pb(a[i]);
			for (int i=flen;i<pos[x]+1;++i) b.pb(a[i]);
			for (int i=0;i<flen;++i) b.pb(a[i]);
		}else if (pos[x] == n-1){
			ans.pb({3, pos[x+1], flen, n-pos[x+1]-flen});
			for (int i=pos[x+1]+flen;i<n;++i) b.pb(a[i]);
			for (int i=pos[x+1];i<flen+pos[x+1];++i) b.pb(a[i]);
			for (int i=0;i<pos[x+1];++i) b.pb(a[i]);
		}else{
			ans.pb({4, pos[x+1], flen, pos[x]-flen-pos[x+1]+1, n-pos[x]-1});
			for (int i=pos[x]+1;i<n;++i) b.pb(a[i]);
			for (int i=pos[x+1]+flen;i<pos[x]+1;++i) b.pb(a[i]);
			for (int i=pos[x+1];i<pos[x+1]+flen;++i) b.pb(a[i]);
			for (int i=0;i<pos[x+1];++i) b.pb(a[i]);
		}
		
		
		a = b;
		for (int i=0;i<n-1;++i){
			if (a[i+1]==a[i]+1) isConnected[a[i]] = 1;
		}
	}
	cout << sz(ans)<<"\n";
	for (auto x:ans) {
		for (auto y:x) cout << y << " ";
		cout << "\n";
	}
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