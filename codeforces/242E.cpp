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

using a20 = ar<int,20>;

const int MAXN = 1e5+1;
const ll seg_lazy_sentinel = 0;
// Change this accordingly to the q

ll sz, lazy[4*MAXN];

struct Node{
	a20 v;
	int k;
} t[4*MAXN];

const Node seg_initial = {{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0}, 0};
const Node NEUTRAL =  {{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0}, 0};

// Change the inline function accordingly to the q
inline Node merge(Node a, Node b){
	Node res;
	for (int i=0;i<20;++i){
		res.v[i] = a.v[i] + b.v[i];
	}
	res.k = a.k + b.k;
	return res;
}

inline int lazy_apply(ll lazy_val, ll new_val){
	return new_val^lazy_val;
}

inline Node lazy_func(Node cur_val, ll lazy_val, int l, int r){
	for (int i=0;i<20;++i){
		if ((1<<i)&lazy_val){
			cur_val.v[i] = cur_val.k-cur_val.v[i];
		}
	}
	return cur_val;
}
inline Node single(int x){
	Node res;
	for (int i=0;i<20;++i){
		res.v[i] = !!((x&(1<<i)));
	}
	res.k=1;
	return res;
}

void init(int n){
	sz = 1;
	while(sz<n) sz*=2;
	fill(t, t+4*MAXN, seg_initial);
	fill(lazy, lazy + 4*MAXN, seg_lazy_sentinel);
}

void seg_eval_lazy(int i, int l, int r)
{
    if (lazy[i] == seg_lazy_sentinel)
        return;

    t[i] = lazy_func(t[i], lazy[i], l, r);

    if (r-l>1)
    {
        lazy[i * 2 + 1] = lazy_apply(lazy[i * 2 + 1], lazy[i]);
       	lazy[i * 2 + 2] = lazy_apply(lazy[i * 2 + 2], lazy[i]);
    }

    lazy[i] = seg_lazy_sentinel;
}

void build(vector<int> &vec, int x, int l, int r)
{
    if (r - l == 1)
    {
        if (l < (int)vec.size())
            t[x] = single(vec[l]);
        return;
    }
    int mid = (l + r) / 2;
    build(vec, 2 * x + 1, l, mid);
    build(vec, 2 * x + 2, mid, r);
    t[x] = merge(t[2 * x + 1], t[2 * x + 2]);
}
void build(vector<int> &vec)
{
    build(vec, 0, 0, sz);
}
Node upd(int x, int l, int r, int lx, int rx, int v)
{
	seg_eval_lazy(x, lx, rx);
	if (lx>=r||rx<=l) return t[x];
	if (lx>=l&&rx<=r){
		lazy[x] = lazy_apply(lazy[x],v);
		seg_eval_lazy(x, lx ,rx);
		return t[x];
	}
	if (rx-lx==1) return t[x];
    
    int mid = (lx + rx) / 2;
    Node a = upd(2*x+1, l, r, lx, mid, v);
    Node b = upd(2*x+2, l, r, mid, rx, v);
   	return t[x] = merge(a, b);
}
void upd(int l, int r, int v)
{
    upd(0, l, r, 0, sz, v);
}
Node query(int l, int r, int x, int lx, int rx)
{
	seg_eval_lazy(x, lx, rx);
    if (lx >= r || rx <= l)
        return NEUTRAL;
    if (lx >= l && rx <= r)
        return t[x];
    int mid = (lx + rx) / 2;
    Node a = query(l, r, 2 * x + 1, lx, mid);
    Node b = query(l, r, 2 * x + 2, mid, rx);
    return merge(a, b);
}
Node query(int l, int r)
{
    return query(l, r, 0, 0, sz);
}

void solve()
{
	int n;
	cin >> n;
	vi a(n);
	for (int i=0;i<n;++i){
		cin >> a[i];
	}
	init(n);
	build(a);
	int m;
	cin >> m;
	while(m-->0){
		int op;
		cin >> op;
		if (op==1){
			int l, r;
			cin >> l >> r;
			l--;
			Node res = query(l, r);
			ll ans = 0;
			for (int i=0;i<20;++i){
				ans += (ll)res.v[i]*(ll)(1LL<<i);
			}
			cout << ans << "\n";
		}else{
			int l, r, x;
			cin >> l >> r >> x;
			l--;
			upd(l, r, x);
		}
	}
}

int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0), cout.tie(0);
    solve();
}