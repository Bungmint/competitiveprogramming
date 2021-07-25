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
int leftover[1<<20], covered[1<<20], a[20], b[20], n, m;

void solve()
{
	cin >> n >> m;
	for (int i=0;i<n;++i) cin >> a[i];
	for (int i=0;i<m;++i) cin >> b[i];
	memset(leftover, -1, sizeof(leftover)); memset(covered, -1, sizeof(covered));
	leftover[0] = covered[0] = 0;
	for (int mask = 0;mask<(1<<m);++mask){
		for (int last=0;last<m;++last){
			if (((1<<last)&mask)==0) continue;
			int prev = mask&~(1<<last);
			if (covered[prev]==-1) continue;
			int amt = leftover[prev] + b[last];
			int cur = a[covered[prev]];
			if (amt<cur){
				covered[mask] = covered[prev];
				leftover[mask] = amt;
			}else if (amt==cur){
				covered[mask] = covered[prev]+1;
				leftover[mask] = 0;
			}
		}
		if (covered[mask]==n){
			cout << "YES"<<endl;
			return;
		}
	}
	cout << "NO"<<endl;
}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    // setIO("bank");
    int testcase=1;
    // cin >> testcase;
    while (testcase--)
    {
        solve();
    }
}