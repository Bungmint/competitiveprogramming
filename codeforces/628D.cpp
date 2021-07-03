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
string a, b;
ll cache[2000][2000][2][2];
int m,d,leng, dig1[2000], dig2[2000],pows[2000];

void precalc(){
	for (int i=0;i<2000;i++){
		if (i==0) pows[i] = 1;
		else pows[i] = (pows[i-1]*10)%m;
	}
}

ll mpow(ll a, ll b, ll mod){
	ll res = 1LL;
	while(b){
		if (b&1) res = (res*a)%mod;
		a = (a*a)%mod;
		b/=2;
	}
	return res;
}

ll dp(int pos, ll rem, bool f1, bool f2){
	if (pos==leng){
		if (rem==0){
			 return 1;
		}
		return 0;
	}
	if (cache[pos][rem][f1][f2]!=-1) return cache[pos][rem][f1][f2];
	int LLT = (f1? 0: dig1[pos]),LGT = (f2? 9: dig2[pos]);
	ll res = 0LL;
	dbg(LLT,LGT);
	for (ll i=LLT;i<=LGT;++i){
		if (pos%2==0){
			if (i==d) continue;
			ll newrem = (rem+i*pows[leng-1-pos])%m;
			res = (res+dp(pos+1, newrem, f1||(i>LLT), f2||(i<LGT)))%MOD;
		}else{
			if (i!=d) continue;
			ll newrem = (rem+i*pows[leng-1-pos])%m;
			res = (res+dp(pos+1, newrem, f1||(i>LLT), f2||(i<LGT)))%MOD;
		}
	}
	return cache[pos][rem][f1][f2] = res;
}


void solve()
{
	cin >> m >> d;
	precalc();
	cin >> a >> b;
	leng = (int)a.length();
	memset(cache,-1,sizeof(cache));
	for (int i=0;i<leng;++i)
		dig1[i] = a[i]-'0', dig2[i] = b[i]-'0';
	cout << dp(0,0,0,0)<<"\n";
}

int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0), cout.tie(0);
    solve();
}