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
const ld eps = 1e-9;
ld dp[15][1<<15], x[15], y[15], t[15];
int n;

ld sq(ld x){return x*x;}
ld dist(int i, int j){return sqrt(sq(x[i]-x[j])+sq(y[i]-y[j]));}
ld dist(int i){return sqrt(sq(x[i])+sq(y[i]));}
bool great(ld x, ld y){
	return (x-y>0&&x-y>eps);
}

void solve()
{
	cin >> n;
	for (int i=0;i<n;++i) cin >> x[i] >> y[i]>>t[i];
	ld mul;
	cin >> mul;
	dbg(mul);
	ld l = 0, r = 1e9;
	while(r-l>eps){
		for (int i=0;i<n;++i) for (int j=0;j<(1<<n);++j)dp[i][j] = LINF;
		ld m = l + (r-l)/2;
		vector<ld> mult(n+1, m);
		for (int j=0;j<n;++j){
			mult[j+1] = mult[j]*mul;
			if (great(t[j], dist(j)/m))dp[j][(1<<j)] = dist(j)/m;
		}
		for (int mask = 1;mask<(1<<n);++mask){
			int one = __builtin_popcount(mask);
			for (int last = 0;last<n;++last){
				if (((1<<last)&mask)==0) continue;
				if (great(dp[last][mask], t[last])) continue;
				for (int nxt=0;nxt<n;++nxt){
					if ((1<<nxt)&mask) continue;
					ld time = dist(last, nxt)/mult[one];
					if (great(t[nxt], dp[last][mask]+time)&&great(dp[nxt][mask|(1<<nxt)], dp[last][mask]+time)){
						dp[nxt][mask|(1<<nxt)] = dp[last][mask]+time;
					}
					
				}
			}
		}
		bool ok = 0;
		for (int i=0;i<n;++i) ok|=great(LINF,dp[i][(1<<n)-1]);
		if (ok) r = m;
		else l = m;
	}
	cout << setprecision(20)<<l << endl;
}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int testcase=1;
    // cin >> testcase;
    while (testcase--)
    {
        solve();
    }
}