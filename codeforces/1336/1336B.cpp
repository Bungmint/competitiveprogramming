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

inline ll sum(ll a, ll b, ll c){
	return (a-b)*(a-b) + (b-c)*(b-c) + (c-a)*(c-a);
}

void solve()
{
	int nr, ng, nb;
	cin >> nr >> ng >> nb;
	vl R(nr), G(ng), B(nb);
	for (int i=0;i<nr;++i) cin >> R[i];
	for (int i=0;i<ng;++i) cin >> G[i];
	for (int i=0;i<nb;++i) cin >> B[i];
	sort(all(R));
	sort(all(G));
	sort(all(B));
	ll mi = LINF*9;
	for (int i=0;i<nr;++i){
		int g1 = lower_bound(all(G), R[i])-G.begin();
		int g2 = upper_bound(all(G), R[i])-G.begin()-1;
		int b1 = upper_bound(all(B), R[i])-B.begin()-1;
		int b2 = lower_bound(all(B), R[i])-B.begin();
		if (g1<ng&&b1>=0) mi = min(mi, sum(R[i], G[g1], B[b1]));
		if (g2>=0&&b2<nb) mi = min(mi, sum(R[i], G[g2], B[b2]));
	}
	for (int i=0;i<ng;++i){
		int r1 = lower_bound(all(R), G[i])-R.begin();
		int r2 = upper_bound(all(R), G[i])-R.begin()-1;
		int b1 = upper_bound(all(B), G[i])-B.begin()-1;
		int b2 = lower_bound(all(B), G[i])-B.begin();
		if (r1<nr&&b1>=0) mi = min(mi, sum(R[r1], G[i], B[b1]));
		if (r2>=0&&b2<nb) mi = min(mi, sum(R[r2], G[i], B[b2]));
	}
	for (int i=0;i<nb;++i){
		int r1 = lower_bound(all(R), B[i])-R.begin();
		int r2 = upper_bound(all(R), B[i])-R.begin()-1;
		int g1 = upper_bound(all(G), B[i])-G.begin()-1;
		int g2 = lower_bound(all(G), B[i])-G.begin();
		if (r1<nr&&g1>=0) mi = min(mi, sum(R[r1], G[g1], B[i]));
		if (r2>=0&&g2<ng) mi = min(mi, sum(R[r2], G[g2], B[i]));
	}
	cout << mi << "\n";
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