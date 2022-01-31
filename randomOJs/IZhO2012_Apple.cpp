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
};

void setIO(string s)
{
    freopen((s + ".in").c_str(), "r", stdin);
    freopen((s + ".out").c_str(), "w", stdout);
}

struct Node{
	int sum, lazy, tl, tr, l, r;
	Node():sum(0), lazy(0), l(-1),r(-1){}
};

const int MAXN = 123456;
Node segtree[MAXN*64];
int cnt = 1;

void push_lazy(int node){
	if (segtree[node].lazy){
		segtree[node].sum = segtree[node].tr-segtree[node].tl;
		int mid = (segtree[node].tr+segtree[node].tl)>>1;
		if (segtree[node].l==-1){
			segtree[node].l = cnt++;
			segtree[segtree[node].l].tl = segtree[node].tl;
			segtree[segtree[node].l].tr = mid;
		}
		if (segtree[node].r==-1){
			segtree[node].r = cnt++;
			segtree[segtree[node].r].tl = mid;
			segtree[segtree[node].r].tr = segtree[node].tr;
		}
		segtree[segtree[node].l].lazy = segtree[segtree[node].r].lazy = 1;
		segtree[node].lazy = 0;
	}
}

void upd(int node, int l, int r){
	push_lazy(node);
	if (segtree[node].tl==l&&segtree[node].tr==r){
		segtree[node].lazy = 1;
		push_lazy(node);
		return;
	}
	int mid = (segtree[node].tr+segtree[node].tl)>>1;
	if (segtree[node].l==-1){
		segtree[node].l = cnt++;
		segtree[segtree[node].l].tl = segtree[node].tl;
		segtree[segtree[node].l].tr = mid;
	}
	if (segtree[node].r==-1){
		segtree[node].r = cnt++;
		segtree[segtree[node].r].tl = mid;
		segtree[segtree[node].r].tr = segtree[node].tr;
	}
	if (l>=mid) upd(segtree[node].r, l, r);
	else if (r<=mid) upd(segtree[node].l, l, r);
	else{
		upd(segtree[node].l, l, mid);
		upd(segtree[node].r, mid, r);
	}
	push_lazy(segtree[node].l), push_lazy(segtree[node].r);
	segtree[node].sum = segtree[segtree[node].l].sum+segtree[segtree[node].r].sum;
}

int query(int node, int l, int r){
	push_lazy(node);
	if (segtree[node].tl==l&&segtree[node].tr==r){
		return segtree[node].sum;
	}
	int mid = (segtree[node].tr+segtree[node].tl)>>1;
	if (segtree[node].l==-1){
		segtree[node].l = cnt++;
		segtree[segtree[node].l].tl = segtree[node].tl;
		segtree[segtree[node].l].tr = mid;
	}
	if (segtree[node].r==-1){
		segtree[node].r = cnt++;
		segtree[segtree[node].r].tl = mid;
		segtree[segtree[node].r].tr = segtree[node].tr;
	}
	if (l>=mid) return query(segtree[node].r, l, r);
	else if (r<=mid) return query(segtree[node].l, l, r);
	else return query(segtree[node].l, l, mid)+ query(segtree[node].r, mid, r);
}


void solve()
{
	int c = 0;
	int q;
	cin >> q;
	segtree[0].tl = 1, segtree[0].tr = 1e9+1;
	segtree[0].sum=segtree[0].lazy = 0;
	
	while(q--){
		int d, l, r;
		cin >> d >> l >> r;
		if (d==1){
			c = query(0, l+c, r+c+1);
			cout << c << "\n";
		}else upd(0, l+c, r+c+1);
	}
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