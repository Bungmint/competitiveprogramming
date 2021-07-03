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
const int S = 1e4, Nsqrt = 2e4;
bool is_pr[Nsqrt+1], block[S], cnt = 0;
vector<int> pr;

int calc(int n){
	int res = 0;
	for (int k=0;k*S<=n;k++){
		memset(block, true,sizeof(block));
		int st = k*S;
		for (int p:pr){
			int id = (st+p-1)/p;
			int j = max(id, p)*p -st;
			for (;j<S;j+=p) block[j] = 0;
		}
		if (k==0) block[0] = block[1] = 0;
		for (int i=0;i<S&&st+i<=n;i++)
			if (block[i]&&((st+i)%4==1||(st+i)==2)) res++;
	}
	return res;
}

void solve()
{
	int l, r;
	cin >> l >> r;
	memset(is_pr, true, sizeof(is_pr));
	is_pr[0] = is_pr[1] = false;
	for (int i=2;i<=Nsqrt;i++)
		if (is_pr[i]){
			pr.PB(i);
			for (int j=i*i;j<=Nsqrt;j+=i) is_pr[j] =false;
		}
	cout << calc(r) - calc(l-1)<<"\n";
}

int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0), cout.tie(0);
    solve();
}