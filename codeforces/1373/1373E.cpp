// Problem: E. Sum of Digits
// Contest: Codeforces - Educational Codeforces Round 90 (Rated for Div. 2)
// URL: https://codeforces.com/contest/1373/problem/E
// Memory Limit: 512 MB
// Time Limit: 2000 ms
// 
// Powered by CP Editor (https://cpeditor.org)

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

void solve()
{
	int n, k;
	cin >>n >>k;
	string ans;
	F0R(i, 200) ans += "9";
	F0R(x, n+1){
		int sum = (k+1)*(2*x+k)/2LL;
		if (sum%9==n%9&&sum>=n){
			F0R(up, k+1){
				if (up==0){
					if (sum==n){
						string res = "";
						int xCopy = x;
						int MAX = 9-k;
						if (x>=MAX){
							dbg(x);
							res += '0'+MAX;
							x-= MAX;
							while(x>=9) res += '9', x-=9;
							if (x)res += '0'+x;
							reverse(all(res));
						}else{
							res += '0'+x;
						}
						x = xCopy;
						if (res.empty()) res+='0';
						if (sz(res)<sz(ans)) ans = res;
						else if (sz(res)==sz(ans)) ckmin(ans, res);
					}
				}else if ((sum-n)%(9*up)==0){
					int carry = (sum-n)/(9*up);
					int r = x+k-up;
					if (r>=9*carry){
						string res="";
						r-=9*carry;
						if (r%9==0&&r>0){
							res+='1';
							r-=1;
							while(r>=9) res+='9', r-=9;
							assert(r==8), res+='8';
						}else if (r>=9){
							res+=(char)('0'+(r%9)+1);
							r -= (r%9)+1;
							while(r>=9) res += '9', r-=9;
							assert(r==8), res += '8';
						}else if (r){
							res += '0'+r;
						}
						F0R(i, carry-1) res += '9';
						res += (char)('9'-k+up);
						if (sz(res)<sz(ans)) ans = res;
						else if (sz(res)==sz(ans)) ckmin(ans, res);
					}
				}
			}
		}
	}
	if (sz(ans)==200)cout << -1 << "\n";
	else cout << ans << "\n";
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