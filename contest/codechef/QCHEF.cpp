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
const int N = 1<<20;
int a[N], res=0, previous=0;
int mi[N], mx[N];
int leftmost[N], n, m, k;
vector<pair<int,pi>> mem;



void addleft(int idx){
	mem.pb({0, {a[idx], mi[a[idx]]}});
	mem.pb({1, {a[idx], mx[a[idx]]}});
	mi[a[idx]] = idx;
	if (mx[a[idx]]<0) mx[a[idx]] = idx;
	res = max(res, mx[a[idx]]-mi[a[idx]]);
}     

void addright(int idx){
	mx[a[idx]] = idx;
	if (mi[a[idx]]>n) mi[a[idx]] = idx;
	res = max(res, mx[a[idx]]-mi[a[idx]]);
}

void snapshot(){
	previous = res;
}

void rollback(){
	while(mem.size()){
		pair<int,pi> p = mem.back();
		if (p.fi==0){
			mi[p.se.fi] = p.se.se;
		}else{
			mx[p.se.fi] = p.se.se;
		}
		mem.pop_back();
	}
	res = previous;
}

void init(){
	for (int i=1;i<=m;++i) mi[i] = INF, mx[i] = -INF;
 	res = 0;
}

const int block=320; //Dont forget to set

struct Query {
    int l, r, idx;
	inline pair<int, int> toPair() const {
		return make_pair(l / block, r);
	}
};
inline bool operator<(const Query &a, const Query &b) {
	return a.toPair() < b.toPair();
}

using vq = vector<Query>;


vi mo(vq queries) {
   	vi answers(queries.size());
    sort(queries.begin(), queries.end());
    /*
    	Light Queries
    */
    for (Query q: queries){
    	if (q.r-q.l+1<=block){
    		int ans = 0;
    		for (int j=q.l;j<=q.r;++j){
    			leftmost[a[j]] = INF;
    		}
    		for (int j=q.l;j<=q.r;++j){
    			ans = max(ans, j-leftmost[a[j]]);
    			if(leftmost[a[j]]>=n) leftmost[a[j]] = j;
    		}
    		answers[q.idx] = ans;
    	}
    }
    /*
    	Heavy Queries
    */
    int l, r;
    int last_bucket = -1;
    for (Query q : queries) {
        if (q.r-q.l+1<=block) continue;
        int bucket = q.l/block;
        if (bucket!=last_bucket){
        	init();
        	l = (bucket+1)*block;
        	if (l>=n) l = n;
        	r = q.r;
        	for (int j=l;j<=r;++j){
        		addright(j);
        		dbg(q.l, q.r, l, r,j);
        	}
        }
        last_bucket = bucket;
        while(r<q.r){
        	addright(++r);
        }
        snapshot();
        for (int j=l-1;j>=q.l;--j){
        	addleft(j);
        }
        answers[q.idx] = res;
        rollback();
    }
    return answers;
}

void solve()
{
	cin >> n >> m>>k;
	for (int i=0;i<n;++i) cin >> a[i];
	vq q(k);
	for (int i=0;i<k;++i){
		int l,r;
		cin >> l >> r;
		l--;r--;
		q[i] = {l,r,i};
	}
	vi ans = mo(q);
	for (int x:ans) cout << x <<"\n";
}

int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0), cout.tie(0);
    solve();
}