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
int a[300000], spar[300000][20], n, cnt[1000001];

void solve()
{
	cin >> n;
	for (int i=0;i<n;++i) cin >> a[i], spar[i][0] = a[i];
	for (int j=1;j<20;++j){
		for (int i=0;i+(1<<j)<=n;++i) spar[i][j] = gcd(spar[i][j-1], spar[i+(1<<(j-1))][j-1]);
	}
	int l = 1, r = n, val=-1;
	vi ans;
	while(l<=r){
		int m = l + (r-l)/2;
		int lg = log2(m);
		vi cur;
		memset(cnt, 0, sizeof(cnt));
		for (int i=0;i<m;++i){
			cnt[a[i]]++;
			dbg(a[i]);
		}
		int x = gcd(spar[0][lg], spar[m-1-(1<<lg)+1][lg]);
		if (cnt[x]) cur.pb(0);
		for (int i=m;i<n;++i){
			cnt[a[i]]++;
			cnt[a[i-m]]--;
			x = gcd(spar[i-m+1][lg], spar[i-(1<<lg)+1][lg]);
			dbg(i,m,x);
			if (cnt[x]) cur.pb(i-m+1);
		}
		
		
		if (sz(cur)){
			ans = cur;
			l = m+1;
			val = m-1;
		}else r = m-1;
		
	}
	cout << sz(ans) << " "<< val << endl;
	for (int x:ans) cout << x+1 << " ";
	cout << endl;
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