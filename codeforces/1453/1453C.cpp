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

void solve()
{
	int n;
	cin >> n;
	vector<vi> grid(n, vi(n));
	vi cnt(10);
	for (int i=0;i<n;++i){
		string s;
		cin >> s;
		for (int j=0;j<n;++j){
			grid[i][j] = s[j]-'0';
			cnt[grid[i][j]]++;
		}
	}
	vi ans(10);
	for (int d=0;d<10;++d){
		int x = -1, y=-1;
		int mix = INF, miy = INF;
		if (cnt[d]<=1) continue;
		for (int j=0;j<n;++j){
			for (int k=0;k<n;++k){
				if (grid[j][k]==d) x = max(x,j), y = max(y, k), mix = min(mix, j), miy = min(miy,k);
			}
		}
		dbg(mix, miy);
		for (int i=0;i<=x;++i){
			int row = i;
			int rowl=n, rowr = -1;
			for (int j=0;j<n;++j){
				if (grid[i][j] == d) rowl = min(rowl, j), rowr = max(rowr, j);
			}
			if (rowl==n) continue;
			ans[d] = max((rowr-rowl)*(n-1-row), ans[d]);
			ans[d] = max((rowr-rowl)*(row), ans[d]);
			ans[d] = max(ans[d], max((rowr)*(x-row), (n-1-rowl)*(x-row)));
			ans[d] = max(ans[d], max((rowr)*(row-mix), (n-1-rowl)*(row-mix)));
		}
		for (int i=0;i<=y;++i){
			int row = i;
			int rowl=n, rowr = -1;
			for (int j=0;j<n;++j){
				if (grid[j][i] == d) rowl = min(rowl, j), rowr = max(rowr, j);
			}
			if (rowl==n) continue;
			dbg(row,rowl, rowr);
			ans[d] = max((rowr-rowl)*(n-1-row), ans[d]);
			ans[d] = max((rowr-rowl)*(row), ans[d]);
			ans[d] = max(ans[d], max((rowr)*(y-row), (n-1-rowl)*(y-row)));
			ans[d] = max(ans[d], max((rowr)*(row-miy), (n-1-rowl)*(row-miy)));
		}
		
	}
	for (int x:ans) cout << x << " ";
	cout << "\n";
}

int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0), cout.tie(0);
    int testcase;
    cin >> testcase;
    while (testcase--)
    {
        solve();
    }
}