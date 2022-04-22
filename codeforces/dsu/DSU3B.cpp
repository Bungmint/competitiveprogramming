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
pi Edge[50011];
int p[50011], SZ[50011], previous,ans[50000];
int l[50000], r[50000];
vpi bucket[50000];
stack<pair<pi,pi>> mem;
int n, m;
int cnt, prevcnt;


int get(int x){return (x==p[x]? x:get(p[x]));}

void unite(int x, int y){
	dbg(x,y);
	x = get(x), y = get(y);
	if (x==y)return;
	mem.push({{x, SZ[x]}, {y,SZ[y]}});
	if (SZ[x]>SZ[y]) swap(x,y);
	SZ[y]+=SZ[x];
	p[x] = y;
	cnt--;
}

void add(int i){
	unite(Edge[i].fi, Edge[i].se);
}     


const int block=250; //Dont forget to set

void solve()
{
	cin>> n >> m;
	cnt = n;
	for (int i=1;i<=n;++i){
		p[i] = i;
		SZ[i] = 1;
	}
	for (int i=0;i<m;++i){
		cin >> Edge[i].fi >> Edge[i].se;
	}
	int k;
	cin >> k;
	for (int i=0;i<k;++i){
		cin >> l[i] >> r[i];
		l[i]--;r[i]--;
		if (r[i]-l[i]>=block){
			bucket[l[i]/block].pb({r[i], i});
			dbg(i);
		}
	}
	int ql,qr;
	for (int i=0;i<=m/block;++i){
		if (!sz(bucket[i])) continue;
		for (int j=1;j<=n;++j){
			p[j] = j;
			SZ[j] = 1;
		}
		sort(all(bucket[i]));
		dbg(bucket[i]);
		ql = (i+1)*block;
		qr = bucket[i][0].fi;
		cnt = n;
		for (int j=ql;j<=qr;++j) add(j);
		dbg(cnt);
		if (ql>=m) ql = m;
		dbg(i, ql, qr);
		for (int j=0;j<bucket[i].size();++j){
			int id = bucket[i][j].se;
			dbg(id);
			while(qr<r[id]){
				dbg(qr);
				add(++qr);

			}
			previous = sz(mem);
			prevcnt = cnt;
			for (int x=ql-1;x>=l[id];--x) add(x);
			ans[id] = cnt;
			cnt = prevcnt;
			while(previous!=sz(mem)){
				pair<pi,pi> x = mem.top();
				p[x.fi.fi] = x.fi.fi;
				SZ[x.fi.fi] = x.fi.se;
				p[x.se.fi] = x.se.fi;
				SZ[x.se.fi] = x.se.se;
				mem.pop();
			}
		}
	}
	for (int j=1;j<=n;++j){
		p[j] = j;
		SZ[j] = 1;
	}
	cnt = n;
	previous = sz(mem);
	prevcnt = cnt;
	for (int i=0;i<k;++i){
		if (r[i]-l[i]<block){
			dbg(i);
			for (int j=l[i];j<=r[i];++j){
				add(j);
			}
			ans[i] = cnt;
			cnt = prevcnt;
			while(previous!=sz(mem)){
				pair<pi,pi> x = mem.top();
				p[x.fi.fi] = x.fi.fi;
				SZ[x.fi.fi] = x.fi.se;
				p[x.se.fi] = x.se.fi;
				SZ[x.se.fi] = x.se.se;
				mem.pop();
			}
		}
	}
	
	
	
	
	for (int i=0;i<k;++i)cout << ans[i] << "\n";
}

int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0), cout.tie(0);
    int testcase=1;
    // cin >> testcase;
    while (testcase--)
    {
        solve();
    }
}