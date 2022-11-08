// Problem: Range Queries and Copies
// Contest: CSES - CSES Problem Set
// URL: https://cses.fi/problemset/task/1737
// Memory Limit: 512 MB
// Time Limit: 1000 ms
// 
// Powered by CP Editor (https://cpeditor.org)

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

// USACO Guide coming in clutch again
template<typename T, int MAXN>
struct PersistentSegTree{
	struct Node {
		T val, sum;
		Node *l, *r;
	
		Node(ll x) : val(x), sum(x), l(nullptr), r(nullptr) {}
		Node(Node *ll, Node *rr) : val(0), l(ll), r(rr) {sum = ll->sum+rr->sum;}
	};
	
	T n, a[MAXN]; // The initial array and its size
	Node* roots[MAXN]; // The persistent array's roots
	
	Node* build(int l, int r) {
		if (r-l == 1) return new Node(a[l]);
		int mid = (l + r) / 2;
		return new Node(build(l, mid), build(mid, r));
	}
	
	Node* update(Node* node, T val, int pos, int l, int r) {
		dbg(l,r);
		if (r-l == 1) return new Node(val);
		int mid = (l + r) / 2;
		if (pos >= mid)return new Node(node->l, update(node->r, val, pos, mid, r));
		else return new Node(update(node->l, val, pos, l, mid), node->r);
	}
	
	T query(Node* node,int lx, int rx, int l, int r) {
		if (r<=lx||rx<=l) return 0LL;
		if (lx<=l&&r<=rx) return node->sum;
		int mid = (l + r) / 2;
		return query(node->r, lx, rx, mid, r) + query(node->l, lx,rx, l, mid);
	}
	
	T query(int l, int r, int time) {
		return query(roots[time], l, r, 0, n);
	}
	
	void update_item(int index, T value, int prev_time, int curr_time) {
		// Updates the array item at a given index and time
		dbg(value);
		roots[curr_time] = update(roots[prev_time], value, index, 0, n);
		dbg(roots[prev_time]->sum);
		dbg(roots[curr_time]->sum);
	}
	
	PersistentSegTree(int nn, T* init) {
		// Initializes the persistent array, given an input array
		n = nn;
		for (int i = 0; i < n; i++)
			a[i] = init[i];
		roots[0] = build(0, n);
	}
};

const int MX = 2e5+1;
ll a[MX];
int saved[MX], cur = 1;
int ptr = 1;

void solve()
{
	int n, q;
	cin >> n>> q;
	F0R(i, n) cin >> a[i];
	PersistentSegTree<ll,MX> pst(n, a);
	F0R(i, q){
		int tt, k, id, b;
		cin >> tt >>k;
		k--;
		if (tt==1){
			cin >> id >> b;
			id--;
			pst.update_item(id, b, saved[k], cur);
			saved[k] = cur++;
		}else if (tt==2){
			cin >> id >> b;
			id--;
			cout << pst.query(id, b, saved[k])<<"\n";
		}else{
			saved[ptr++] = saved[k];
			dbg(saved[ptr-1]);
		}
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