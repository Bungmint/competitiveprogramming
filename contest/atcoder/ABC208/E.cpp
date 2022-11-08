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
ll f[20][2][2][2][54][37][20][20];
ll pow2[54], pow3[37], pow5[20], pow7[20], n, k;
vi num;

void precalc(ll x){
	pow2[0] = pow3[0] = pow5[0] = pow7[0] = 1;
	for (int i=1;i<54;++i) pow2[i] = pow2[i-1] * 2;
	for (int i=1;i<37;++i) pow3[i] = pow3[i-1] * 3;
	for (int i=1;i<20;++i) pow5[i] = pow5[i-1] * 5;
	for (int i=1;i<20;++i) pow7[i] = pow7[i-1] * 7;
}

ll dp(int pos,bool mask,bool real, bool zero, int a, int b, int c, int d){
	if (pos==sz(num)){
		if (!real) return 0;
		if (zero) return 1;
		if (a*log10(2)+b*log10(3)+c*log10(5)+d*log10(7)>log10(k)) return 0;
		if (pow2[a]*pow3[b]*pow5[c]*pow7[d]<=k) return 1;
		
		return 0;
	}
	if(f[pos][mask][real][zero][a][b][c][d]!=-1) return f[pos][mask][real][zero][a][b][c][d];
	int DMT = (mask? 9: num[pos]);
	ll val = 0;
	for (int i=0;i<=DMT;++i){
		if (zero){
			val += dp(pos+1, mask||i<DMT, real, zero, 0,0,0,0);
		}else{
			if(i==0&&real){
				val += dp(pos+1, mask||i<DMT, real, 1, 0,0,0,0);
			}else if (i==0){
				val += dp(pos+1, mask||i<DMT, real, zero, 0,0,0,0);
			}else{
				int fact2 = 0, fact3 = 0, fact5 = 0, fact7 = 0;
				int j = i;
				while(j%2==0){
					j/=2;
					fact2++;
				}
				while(j%3==0){
					j/=3;
					fact3++;
				}
				while(j%5==0){
					j/=5;
					fact5++;
				}
				while(j%7==0){
					j/=7;
					fact7++;
				}
				
				val += dp(pos+1, mask||i<DMT, real||i, zero, a+fact2, b+fact3, c+fact5, d+ fact7);
			
			}
		}
	}
	return f[pos][mask][real][zero][a][b][c][d] = val;
}

void solve()
{
	cin >> n >> k;
	while(n){
		num.pb(n%10);
		n/=10;
	}
	reverse(all(num));
	memset(f, -1, sizeof(f));
	precalc(k);
	cout << dp(0,0,0,0,0,0,0,0)<<"\n";
	
}

int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0), cout.tie(0);
    solve();
}