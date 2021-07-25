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
const int N = 1e5+1;
vi G[N];
int c[N], st[N], en[N], a[N], freq[N], n,m, timer = 0;
int bit[2*N];

void upd(int i,int v){
	for (++i;i<=200001;i+=i&-i) bit[i] += v;
}
int query(int i){
	int res =0 ;
	for (++i;i>0;i-=i&-i) res += bit[i];
	return res;
}

void remove(int idx){
	upd(freq[a[idx]], -1);
	freq[a[idx]]--;
	upd(freq[a[idx]], 1);
}
void add(int idx){
	upd(freq[a[idx]], -1);
	freq[a[idx]]++;
	upd(freq[a[idx]], 1);
}     
int get_answer(int c){
	dbg(c);
	dbg(query(2*n-1), query(c-1));
	return query(2*n-1)-query(c-1);
}
const int block=320; //Dont forget to set

struct Query {
    int l, r, idx, k;
	inline pair<int, int> toPair() const {
		return make_pair(l / block, ((l / block) & 1) ? -r : +r);
	}
};
inline bool operator<(const Query &a, const Query &b) {
	return a.toPair() < b.toPair();
}

using vq = vector<Query>;


vi mo(vq queries) {
   	vi answers(queries.size());
    sort(queries.begin(), queries.end());
	upd(0, n);
    int cur_l = 0;
    int cur_r = -1;
    for (Query q : queries) {
        while (cur_l > q.l) {
            cur_l--;
            add(cur_l);
        }
        while (cur_r < q.r) {
            cur_r++;
            add(cur_r);
        }
        while (cur_l < q.l) {
            remove(cur_l);
            cur_l++;
        }
        while (cur_r > q.r) {
            remove(cur_r);
            cur_r--;
        }

        answers[q.idx] = get_answer(q.k);
    }
    return answers;
}

void dfs(int V, int pV){
	st[V] = timer++;
	a[st[V]] = c[V];
	dbg(c[V], st[V],V);
	for (int e:G[V]){
		if (e!=pV) dfs(e,V);
	}
	en[V] = timer-1;
}

void solve()
{
	cin >> n >> m;	
	for (int i=1;i<=n;++i) cin >> c[i];
	for (int i=1;i<=n-1;++i){int u,v;cin >> u >> v;G[u].pb(v);G[v].pb(u);}
	vq Q(m);
	dfs(1,0);
	for (int i=0;i<m;++i){
		int v, k;
		cin >> v>>k;
		Q[i] = {st[v], en[v], i, k};
	}
	vi ans =mo(Q);
	for (int x:ans) cout << x << "\n";
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