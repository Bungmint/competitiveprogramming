#pragma GCC optimize("O3")
#pragma GCC target("sse4")
#include <bits/stdc++.h>
using namespace std;

using ll = long long;
using vi = vector<int>;
using pii = pair<int, int>;
using vpi = vector<pii>;
using pll = pair<ll, ll>;
using vl = vector<ll>;
using vpl = vector<pll>;
using ld = long double;

#define all(v) (v).begin(), (v).end()
#define ar array
#define pb push_back
#define sz(x) (int)(x).size()
#define fi first
#define se second
#define lb lower_bound
#define ub upper_bound
#define FOR(i, a, b) for (int i = (a); i < (b); ++i)
#define F0R(i, a) FOR(i, 0, a)
#define ROF(i, a, b) for (int i = (b)-1; i >= (a); --i)
#define R0F(i, a) ROF(i, 0, a)
#define REP(a) F0R(_, a)

const int INF = 1e9;
const ll LINF = 1e18;
const int MOD = 1e9 + 7; //998244353;
const ld PI = acos((ld)-1.0);
const int dx[4] = {1, 0, -1, 0}, dy[4] = {0, 1, 0, -1};
mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());
template <typename T>
using pqg = priority_queue<T, vector<T>, greater<T>>;
template <typename T>
bool ckmin(T &a, const T &b) { return b < a ? a = b, 1 : 0; }
template <typename T>
bool ckmax(T &a, const T &b) { return b > a ? a = b, 1 : 0; }

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

struct chash
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
    size_t operator()(pair<uint64_t,uint64_t> x) const {
		static const uint64_t FIXED_RANDOM = chrono::steady_clock::now().time_since_epoch().count();
		return splitmix64(x.first + FIXED_RANDOM)^(splitmix64(x.second + FIXED_RANDOM) >> 1);
	}
};

void setIO(string s)
{
    freopen((s + ".in").c_str(), "r", stdin);
    freopen((s + ".out").c_str(), "w", stdout);
}

const int MX = 5e7+1;
int mu[MX], d[MX], pp[MX], pr[MX];
int cnt;
ll sumMu[MX], sumD[MX];
unordered_map<ll,ll> mpMu, mpD;
bool isComp[MX];


void linsieve(int n){
	mu[1] = d[1] = 1;
	FOR(i, 2, n+1){
		if (!isComp[i]){
			mu[i] = -1;
			d[i] = 2;
			pp[i] = 1;
			pr[cnt++] = i;
		}
		for (int j=0;j<cnt&&pr[j]*i<=n;++j){
			int v = i*pr[j];
			pp[v] = 1;
			isComp[v] = 1;
			if (i%pr[j]==0){
				mu[v] = 0;
				pp[v] += pp[i];
				d[v] = d[i]/pp[v] * (pp[v]+1);
				break;
			}else mu[v] = - mu[i], d[v] = 2*d[i];
		}
	}
	FOR(i, 1, n+1) sumMu[i] = sumMu[i-1] + mu[i]*mu[i], sumD[i]=sumD[i-1]+d[i];
}
inline ll calcMu(ll x){
	if (x<=MX-1) return sumMu[x];
	if (mpMu.count(x)) return mpMu[x];
	ll res = 0;
	for (ll i=1;i*i<=x;++i){
		res += (ll)mu[i]*(x/(i*i));
	}
	return mpMu[x] = res;
}
inline ll calcD(ll x){
	if (x<=MX-1) return sumD[x];
	if (mpD.count(x)) return mpD[x];
	ll sum = 0;
	for (ll i = 1LL, la;i<=x;i = la+1LL){
		la = x/(x/i);
		sum += (la-i+1)*(x/i);
	}
	return mpD[x] = sum;
}

inline ll calc(ll x){
	ll sum = 0;
	for (ll i = 1LL, la;i<=x;i = la+1LL){
		la = x/(x/i);
		sum += (calcMu(la)-calcMu(i-1))*calcD(x/i);
	}
	return sum;
}

void solve()
{
	ll n;
	cin >> n;
	cout << calc(n)<<"\n";	
}

int main()
{
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);
    mpMu.reserve(1024), mpMu.max_load_factor(0.25);
    mpD.reserve(1024), mpD.max_load_factor(0.25);
    int testcase=1;
    cin >> testcase;
    if (testcase>800) linsieve(10000);
	else linsieve(MX-1);
    while (testcase--)
    {
        solve();
    }
}