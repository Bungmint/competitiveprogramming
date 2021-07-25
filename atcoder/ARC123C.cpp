// Problem: C - 1, 2, 3 - Decomposition
// Contest: AtCoder - AtCoder Regular Contest 123
// URL: https://atcoder.jp/contests/arc123/tasks/arc123_c
// Memory Limit: 1024 MB
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
int f[20][12][5];
ll n;
vi num;

ll bin_pow(ll a, ll b){
	if (b==0) return 1;
	if (b==1) return a;
	ll m = bin_pow(a, b/2);
	return ((b&1)? m*m*a:m*m);
}

int dp(int pos, int choice, int up){
	int &res = f[pos][choice][up];
	if (res!=-1) return res;
	if (pos==sz(num)) return up==0;
	int cur = num[pos];
	res = 0;
	dbg(pos, cur, up, choice);
	for (int i=choice;i<=choice*3;++i){
		if ((i+up)%10==cur){
			for (int j=0;j<=choice;++j){
				res |= !!(dp(pos+1, j, (i+up)/10));
			}
		}
	}
	return res;
}

void solve()
{
	ll n1;
	cin >> n;
	n1 = n;
	num.clear();
	while(n1){num.pb(n1%10);n1/=10;}
	dbg(num);
	memset(f, -1, sizeof(f));
	for (int i=1;i<=10;++i){
		if (dp(0, i, 0)){
			cout << i << "\n";
			return;
		}
	}
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