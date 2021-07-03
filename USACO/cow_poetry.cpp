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
#define PB push_back
#define sz(x) (int)(x).size()

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
int dp[5000], final[5001], n, m, k;
int pw[5001][5001], sum[5001], s[5000], rhyme[5000];

ll mpow(ll a, ll b){
	ll r = 1;
	while(b){
		if (b&1) r = (r*a)%MOD;
		b/=2;
		a = (a*a)%MOD;
	}
	return r;
}

void setIO(string s) { // the argument is the filename without the extension
	freopen((s+".in").c_str(),"r",stdin);
	freopen((s+".out").c_str(),"w",stdout);
}

void solve()
{
	cin >> n >> m >> k;
	dp[0] = 1;
	map<char,int> m1;
	for (int i=0;i<n;i++){
		cin >> s[i] >> rhyme[i];
	}
	for (int i=0;i<m;i++){
		char c;
		cin >> c;
		m1[c]++;
	}
	for (int i=1;i<k;i++){
		for (int j=0;j<n;j++){
			if (i-s[j]>=0) dp[i] = (dp[i]+dp[i-s[j]])%MOD;
		}
	}
	for (int i=0;i<n;++i){
		final[rhyme[i]] = (final[rhyme[i]]+dp[k-s[i]])%MOD;
	}
	for (int i=1;i<=5000;i++){
		for (int j=1;j<=5000;j++){
			if (j==1) pw[i][j] = final[i];
			else pw[i][j] = (ll)pw[i][j-1]*(ll)final[i]%MOD;
			sum[j] = (sum[j]+pw[i][j])%MOD;
		}
	}
	ll ans = 1LL;
	for (auto x:m1){
		if (x.second>5000){
			ll val = 0LL;
			for (int i=1;i<=n;i++){
				val += mpow(final[i], x.second);
				val%=MOD;
			}
			ans = (ans*val)%MOD;
		}else ans = (ans*(ll)sum[x.second])%MOD;
	}
	cout << ans << "\n";
}

int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0), cout.tie(0);
    setIO("poetry");
    solve();
}