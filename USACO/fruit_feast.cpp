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
const int N = 5e6+2;
bitset<N> dp1, dp2;

void setIO(string s) { // the argument is the filename without the extension
	freopen((s+".in").c_str(),"r",stdin);
	freopen((s+".out").c_str(),"w",stdout);
}

void solve()
{
	int t, a, b;
	cin >> t >> a >> b;
	dp1[0] = 1, dp2[0] = 1;
	for (int i=1;i<=t;i++){
		if (i>=a&&dp1[i-a]) dp1[i] = 1;
		if (i>=b&&dp1[i-b]) dp1[i] = 1; 
		if (dp1[i]) dbg(i);
		if (dp1[i])dp2[i/2] = dp1[i];
		if (dp1[i]) dbg(dp2[i/2], i/2);
	}
	dbg(dp2[16425]);
	for (int i=1;i<=t;i++){
		
		if (i>=a&&dp2[i-a]) dp2[i] = 1;
		if (i>=b&&dp2[i-b]) dp2[i] = 1; 
	}
	int ans = 0;
	for (int i=t;i>=0;i--){
		if(dp1[i]||dp2[i]){
			cout << i << "\n";
			return;
		}
	}
}

int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0), cout.tie(0);
    setIO("feast");
    solve();
}