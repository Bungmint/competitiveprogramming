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
int val[801][801], check[801][801], pref[801][801];


void solve()
{
	int n, k;
	
	int l = 1e9, r = 0, ans;
	cin >> n>>k;
	for (int i=0;i<n;i++)
		for (int j=0;j<n;j++){
			cin >> val[i][j];
			l = min(val[i][j], l);
			r = max(val[i][j], r);
		}
	
	ans = r;
	while(l<=r){
		int m = l + (r-l)/2;
		dbg(l,r,m);
		bool ok = false;
		for (int i=0;i<n;i++)
			for (int j=0;j<n;j++)
				check[i][j] = (val[i][j]<=m?1:-1);
		for (int i=0;i<n;i++){
			for (int j=0;j<n;j++){
				if (i==0&&j==0) pref[i][j] = check[i][j];
				else if (i==0) pref[i][j] = pref[i][j-1] + check[i][j];
				else if (j==0) pref[i][j] = pref[i-1][j] + check[i][j];
				else pref[i][j] = pref[i][j-1]+ pref[i-1][j] - pref[i-1][j-1] + check[i][j];
			}
		}
		
		for (int i=0;i<n-k+1;i++){
			for (int j=0;j<n-k+1;j++){
				if (i==0&&j==0){
					if (pref[i+k-1][j+k-1]>=0) ok =true;
				}else if (i==0){
					if (pref[i+k-1][j+k-1]-pref[i+k-1][j-1]>=0) ok =true;
				}else if (j==0){
					if (pref[i+k-1][j+k-1]-pref[i-1][j+k-1]>=0) ok = true;
				}else{
					if(pref[i+k-1][j+k-1]-pref[i-1][j+k-1]-pref[i+k-1][j-1]+pref[i-1][j-1]>=0) ok =true;
				}
				if (ok) break;
			}
			if (ok)break;
		}
		if (ok){
			r =m-1;
			ans = m;
		}else l = m+1;
	}
	cout << ans << "\n";
}

int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0), cout.tie(0);
    solve();
}