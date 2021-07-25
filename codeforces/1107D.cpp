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

mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());

const int INF = 1e9;
const ll LINF = 1e18;
const int MOD = 1e9 + 7; //998244353;
bool grid[5200][5200];
int n;

bool check(int val){
	if (n%val!=0) return 0;
	int k = n/val;
	for (int r = 0;r<k;r++) for (int c = 0;c<k;c++){
		bool cur = grid[r*val][c*val];
		for (int i=0;i<val;++i){
			for (int j=0;j<val;++j){
				if (cur!=grid[r*val+i][c*val+j]){
					return 0;
				}
			}
		}
	}
	return 1;
}

void solve()
{
	cin >> n;
	for (int i=0;i<n;++i){
		string s;
		cin >> s;
		for (int j=0;j<n/4;++j){
			int x = s[j];
			if (s[j]>='0'&&s[j]<='9'){
				x-='0';
			}else{
				x-='A' - 10;
			}
			for (int k=3;k>=0;--k){
				if ((1<<k)&x){
					grid[i][4*j+3-k] = 1;

				}else grid[i][4*j+3-k] = 0;
			}
		}
	}
	
	vi works, nope;
	works.pb(1);
	for (int i=2;i<=n;++i){
		bool ok = 1;
		for (int x:works){
			if (i%x!=0){
				ok = 0;
			}
		}
		for (int x:nope){
			if (i%x==0) ok = 0;
		}
		if (!ok) continue;
		if (check(i)){
			works.pb(i);
		}else nope.pb(i);
	}
	cout << works.back()<<"\n";
}

int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0), cout.tie(0);
    solve();
}