// Problem: 1896. War Games 2.1
// Contest: Timus
// URL: https://acm.timus.ru/problem.aspx?space=1&num=1896
// Memory Limit: 6 MB
// Time Limit: 500 ms
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

// Uses zero index for the input
template<typename T>
struct BIT{
	int N, lg;
	vector<T> bit;
	BIT(int n){bit.resize(n+1);N = n;lg=log2(N)+1;}
	void upd(int i, T v){ 
		for (;i<=N;i+=i&-i) bit[i]+=v;	
	}
	T query(int i){
		T res = 0;
		for (;i>0;i-=i&-i) res+=bit[i];
		return res;
	}
	int lower_bound(T v){
		T sum = 0, id = 0;
		R0F(i, lg){
			if (id+(1<<i)<=N&&sum+bit[id+(1<<i)]<v){
				sum += bit[id+(1<<i)];
				id += (1<<i);
			}
		}
		return id+1;
	}
};



void solve()
{
	int n, k;
	cin >> n >> k;
	BIT<int> bit(n);
	FOR(i, 1, n+1) bit.upd(i, 1);
	int last = k, ans = 0;
	ans = abs(last-1);
	bit.upd(last, -1);
	FOR(i, 2, n+1){
		int x = bit.query(last);
		int y = bit.query(n);
		int nxt, k2 = k;
		if (y<k) {k2%=y;if(k2==0) k2+=y;}
		if (y-x>=k2){
			nxt = bit.lb(x+k2);
		}else{
			nxt = bit.lb(k2-y+x);
		}
		last = nxt;
		ans ^=abs(i-nxt);
		bit.upd(nxt, -1);
	}
	
	cout << ans<<endl;
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