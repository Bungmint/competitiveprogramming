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

mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());

const int INF = 1e9;
const ll LINF = 1e18;
const int MOD = 1e9 + 7; //998244353
ll dp[1<<20];
ll h[20], w[20], s[20];

void setIO(string s) { // the argument is the filename without the extension
	freopen((s+".in").c_str(),"r",stdin);
	freopen((s+".out").c_str(),"w",stdout);
}

void solve()
{
	int n, H;
	cin >> n>>H;
	memset(dp, -1, sizeof(dp));
	for (int i=0;i<n;++i){
		cin >> h[i]>>w[i] >> s[i];
	}
	for (int i=0;i<n;++i){
		dp[(1<<i)] = s[i];
	}
	dp[0] = 0;
	ll ans = -1;
	for (int mask=1;mask<(1<<n);mask++){
		for (int j=0;j<n;++j){
			if (mask&(1<<j)){
				if (dp[mask^(1<<j)]==-1) continue;
				ll st = min(dp[mask^(1<<j)]-w[j], s[j]);
				if (st<0) continue;
				dp[mask] = max(dp[mask], st);
			}
		}
	}
	for (int mask = 1;mask<(1<<n);mask++){
		if (dp[mask]>0){
			ll height = 0;
			for (int j=0;j<n;++j){
				if ((1<<j)&mask) height += h[j];
			}
			if (height>=H) ans = max(ans, dp[mask]);
		}
	}
	if (ans==-1){
		cout << "Mark is too tall"<<"\n";
	}else cout << ans << "\n";
}

int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0), cout.tie(0);
    setIO("guard");
    solve();
}