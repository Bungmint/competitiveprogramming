#pragma GCC optimize("O3")
#pragma GCC target("sse4")
#include <bits/stdc++.h>
using namespace std;

using ll = long long;

#define all(v) (v).begin(), (v).end()
#define ar array
#define PB push_back

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
const int N = 1e8+1;
const int Nsqrt = 1e4+1;
const int S=10000;
vector<int> prim;
int pr[5761455], cnt = 0;
bool A[Nsqrt], B[S];
ll n,n1, ans=1;

ll pow(ll a, ll b){
	ll r = 1;
	while(b){
		if (b&1) r*=a;
		a *=a;
		b>>=1;
	}
	return r;
}

inline void sqsieve(){
	fill(A, A+Nsqrt, true);
	A[0] = A[1] = 0;
	for (int i=2;i<Nsqrt;i++)
		if (A[i]){
			prim.PB(i);
			for (int j=i*i;j<Nsqrt;j+=i)
				A[j] = 0;
		}
}

void segsieve(){
	for (int k=0;k*S<=N;k++){
		int st = k*S;
		fill(B, B+S, true);
		for (int p:prim){
			int id = (st+p-1)/p;
			int j = max(id, p)*p-st;
			for (;j<S;j+=p) B[j] = 0;
		}
		if (k==0) B[0]=B[1] = 0;
		for (int i=0;i<S&&st+i<=N;i++)
			if (B[i]){
				if (cnt>=50847540)dbg(i+st, cnt);
				pr[cnt] = i+st;
				cnt++;
			}
				
	}
}

void solve()
{
	cin >> n;
	n1 = n;
	ans = 1;
	for (int i=0;i<5761455;i++){
		ll p = pr[i];
		int nsq = sqrt(n);
		if (p>nsq&&p<n) break;
		if (n%p) continue;
		cnt = 0;
		while(n%p==0){
			cnt++;
			n/=p;
		}
		ans *= (pow((ll)p, cnt+1)-1)/((ll)p-1);
	}
	if (n>1) ans *= (n+1);
	cout << ans-n1 << "\n";
}

int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0), cout.tie(0);
    sqsieve();
    segsieve();
    int t;
    cin >> t;
    while (t--)
    {
        solve();
    }
}