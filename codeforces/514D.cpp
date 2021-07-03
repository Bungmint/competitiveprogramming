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
const int N = 1e5, LOG = 17;
int spar[5][N][LOG], n,m,k, res[5];

ll query(int l, int r){
	ll ans = 0LL;
	int lg = log2(r-l+1);
	for (int t=0;t<m;t++){
		ans += max(spar[t][l][lg], spar[t][r-(1<<lg)+1][lg]);
	}
	return ans;
}

int go(int L){
	int l = L, r = n-1, pos = -1, mid;
	while(l<=r){
		mid = l + (r-l)/2;
		if (query(L, mid)<=k){
			pos = mid;
			l = mid+1;
		}else r = mid-1;
	}
	return (pos==-1 ? 0: pos-L+1);
}

void solve()
{
	cin >> n>>m>>k;
	for (int i=0;i<n;i++) for (int j=0;j<m;j++)
			cin >> spar[j][i][0];
	for (int t=0;t<m;t++) for (int i=1;i<LOG;i++) for (int j=0;j+(1<<i)-1<n;j++)
			spar[t][j][i] = max(spar[t][j][i-1], spar[t][j+(1<<(i-1))][i-1]);
	int ans = 0LL;
	
	for (int i=0;i<n;i++){
		int len = go(i);
		dbg(len, i);
		if (len>ans){
			int lg = log2(len);
			ans = len;
			for (int t=0;t<m;t++)
				res[t] = max(spar[t][i][lg], spar[t][i+len-1-(1<<lg)+1][lg]);
		}
	}
	for (int i=0;i<m;i++) cout << res[i]<<" ";
	cout<< "\n";
}

int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0), cout.tie(0);
    solve();
}