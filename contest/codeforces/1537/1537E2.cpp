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
const int P1 = 1e9+7, P2 = 1e9 + 9;
const int B = 37;
const int N = 1e6+1;
ll inv[N], pw[N], hsh[N], backhsh[N], backpw[N], backinv[N];

ll mpow(ll a, ll b,ll m){
	ll res = 1LL;
	while(b){
		if (b&1) res = (res*a)%m;
		b/=2;
		a = (a*a)%m;
	}
	return res;
}

void prec(){
	inv[0] = 1;
	inv[1] = mpow(B, MOD-2, MOD);
	backinv[0] = 1;
	backinv[1] = mpow(B, P2-2, P2);
	pw[0] = 1, pw[1] = B;
	backpw[0] = 1, backpw[1] = B;
	for (int i=2;i<N;i++){
		pw[i] = (pw[i-1]*B)%MOD;
		backpw[i] = (backpw[i-1]*B)%P2;
	}
	for (int i=2;i<N;i++){
		inv[i] = (inv[i-1]*inv[1]) %MOD;
		backinv[i] = (backinv[i-1]*backinv[1])%P2;
	}
}

void solve()
{
	prec();
	int n, k;
	cin >> n >> k;
	string s;
	cin >> s;
	s += s;
	for (int i=0;i<2*n;i++){
		hsh[i] = (i? hsh[i-1]+(s[i]-'a'+1)*pw[i]:s[i]-'a'+1);
		hsh[i]%=MOD;
		backhsh[i] = (i? backhsh[i-1]+(s[i]-'a'+1)*backpw[i]:s[i]-'a'+1);
		backhsh[i]%=P2;
	}
	
	
	int ans = 1;
	for (int i=1;i<n;i++){
		int l = i, r = 2*i-1, dif = -1;
		while(l<=r){
			int m = l + (r-l)/2;
			ll hashed = (hsh[m]-hsh[i-1]+MOD)*inv[i]%MOD;
			ll backhashed = (backhsh[m]-backhsh[i-1]+P2)*backinv[i]%P2;
			if (hashed!=hsh[m-i]||backhashed!=backhsh[m-i]){
				dif = m;
				r = m-1;
			}else l = m+1;
		}
		if (dif==-1){
			ans++;
			continue;
		}
		dbg(s[dif], s[dif-i],dif, i);
		if (s[dif]>s[dif-i]){
			break;
		}else{
			ans++;	
		}
	}
	for (int i=0;i<k;i++){
		cout << s[i%ans];
	}
	cout << "\n";
}

int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0), cout.tie(0);
    int testcase=1;
    //cin >> testcase;
    while (testcase--)
    {
        solve();
    }
}