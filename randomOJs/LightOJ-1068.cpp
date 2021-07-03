#pragma GCC optimize("O3")
#pragma GCC target("sse4")
#include <bits/stdc++.h>
using namespace std;

using ll = long long;

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
vector<int> num;
int dp[10][82][2][82],a,b,k; //First dim: Last dig

int po(ll a, ll b){
	int res = 1LL;
	while(b){
		if (b%2) res*=a;
		a*=a;
		b/=2;
	}
	return res;
}

int dping(int pos, int remainder, int mask, int sum){
	if (pos == sz(num)){
		if (remainder==0&&sum%k==0) return 1;
		return 0;
	}
	if (dp[pos][remainder][mask][sum] !=-1) return dp[pos][remainder][mask][sum];
	int DMT;
	if (mask) DMT = 9;
	else DMT = num[pos];
	int res = 0;
	for (int i=0;i<=DMT;i++){
		int newmask = mask;
		
		int newremain = (remainder + i*po(10, sz(num)-pos-1))%k;
		int newsum = sum + i;
		if (mask==0&&i<DMT) newmask = 1;
		res+=dping(pos+1, newremain, newmask,newsum);
	}
	return dp[pos][remainder][mask][sum] = res;
}

void solve(int t)
{
	cin >> a >> b >> k;
	if (k>=83) {cout <<"Case "<< t << ": "<< 0 << "\n";return;}
	memset(dp, -1, sizeof(dp));
	num.clear();
	int res1, res2;
	a--;
	while(a>0){
		num.PB(a%10);
		a/=10;
	}
	reverse(all(num));
	res1 = dping(0,0,0,0);
	num.clear();
	while(b>0){
		num.PB(b%10);
		b/=10;
	}
	memset(dp, -1, sizeof(dp));
	reverse(all(num));
	res2 = dping(0,0,0,0);
	cout << "Case " << t << ": "<< res2-res1 << "\n";
}

int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0), cout.tie(0);
    int t;
    cin >> t;
    for (int i=1;i<=t;++i)
    {
        solve(i);
    }
}