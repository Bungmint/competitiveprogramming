#pragma GCC optimize("O3")
#pragma GCC target("sse4")
#include <bits/stdc++.h>
using namespace std;

using ll = long long;

#define all(v) (v).begin(), (v).end()
#define ar array
#define PB push_back
#define sz(x) (int)(x).size()

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

const int INF = 1e9;
const ll LINF = 1e18;
const int MOD = 1e9 + 7; //998244353

void solve()
{
	int n;
	cin>>n;
	vector<int> p(n+1), ans;
	int cnt = 0;
	for (int i=1;i<=n;i++)cin>>p[i];
	int sorted = 0;
	for (int i=1;i<=n;i++){
		int id = -1;
		for (int j=1;j<=n;j++){
			if (p[j] == i){
				id = j;
				break;
			}
		}
		int j = id;
		if (j!=i){
			if (cnt%2==j%2){
				cnt += j-i;
				for (int k=j-1;k>=i;k--){ans.PB(k);swap(p[k+1],p[k]);}
			}else{
				if (j-i>=2){
					cnt += j-i+1;
					ans.PB(j-2);
					swap(p[j-2], p[j-1]);
					for (int k=j-1;k>=i;k--){ans.PB(k);swap(p[k+1],p[k]);}
				}else{
					cnt += 5;
					swap(p[i], p[j]);
					assert(i-1>=1);
					ans.PB(i-1);
					ans.PB(i);
					ans.PB(i-1);
					ans.PB(i);
					ans.PB(i-1);
				}
			}
		}
	}
	cout << sz(ans)<<"\n";
	for (int x:ans)cout << x << " ";
	cout << "\n";
}

int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0), cout.tie(0);
    int t;
    cin >> t;
    while (t--)
    {
        solve();
    }
}