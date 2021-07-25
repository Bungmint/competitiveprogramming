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
map<ar<ll,3>, ld> dp[20];
const ld N = 1e5;

ld dping(int len, ll c, ll m, ll p, ll v){
	if (c==0&&m==0){
		return len+1;
	}
	ar<ll,3> a = {c,m,p};
	if (dp[len].count(a)) return dp[len][a];
	
	ld val = 0;
	ld chosec = (ld)c/(ld)(c+m+p), chosem = (ld)m/(ld)(c+m+p), chosep = (ld)p/(ld)(c+m+p);
	if (c&&m){
		ld res;
		if (c>v){
			res = dping(len+1, c-v, m+v/2, p+v/2, v);
		}else{
			res = dping(len+1, 0,m+c/2, p+c/2, v);
		}
		val += res*chosec;
		if (m>v){
			res = dping(len+1, c+v/2,m-v, p+v/2, v);
		}else{
			res = dping(len+1, c+m/2, 0, p+m/2, v);
		}
		val += res*chosem;
	}else if (c){
		ld res;
		if (c>v){
			res = dping(len+1, c-v, 0, p+v, v);
		}else{
			res = dping(len+1, 0,0, p+c, v);
		}
		val += res*chosec;
	}else{
		ld res;
		if (m>v){
			res = dping(len+1, 0,m-v, p+v, v);
		}else{
			res = dping(len+1, 0, 0, p+m, v);
		}
		val += res*chosem;
	}
	

	
	val += (ld)(len+1)*chosep;
	return dp[len][a] = val;
}


ll read(){
	string s;
	cin >> s;
	while(sz(s)<6){
		s+='0';
	}
	int res = 0;
	for (int i=2;i<sz(s);++i){
		res *= 10;
		res += s[i]-'0';
	}
	return res*10000;
}

void solve()
{
	ll c, m, p, v;
	for (int i=0;i<20;++i) dp[i].clear();
	c = read(), m= read(), p= read(), v= read();
	cout << setprecision(20)<<dping(0, c,m,p,v)<<"\n";
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