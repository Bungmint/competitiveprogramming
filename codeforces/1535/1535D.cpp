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
const int LOG = 19;
int k, q, st[1<<LOG], n;
string s;

void build(){
	for (int i=n;i<2*n;i++) st[i] = 1;
	for (int i=n-1;i>=1;i--){
		if (s[i-1]=='?') st[i] = st[2*i] +st[2*i+1];
		else if (s[i-1]=='0') st[i] = st[2*i+1];
		else st[i] = st[2*i];
	}
}

void set1(int pos, char c){
	char c1 = s[pos-1];
	if (c1==c) return;
	if (c1 =='0'){
		if (c=='1') st[pos] = st[2*pos];
		else st[pos] = st[2*pos] +st[2*pos+1];
	}else if (c1=='1'){
		if (c=='0') st[pos] = st[2*pos+1];
		else st[pos] = st[2*pos] +st[2*pos+1];
	}else{
		if (c=='0') st[pos] = st[2*pos+1];
		else st[pos] = st[2*pos];
	}
	dbg(pos, st[pos]);
	for (int x = pos>>1;x>=1;x>>=1){
		dbg(x);
		if (s[x-1]=='?') st[x] = st[2*x] +st[2*x+1];
		else if (s[x-1]=='0') st[x] = st[2*x+1];
		else st[x] = st[2*x];
	}
	s[pos-1] = c;
	//for (int i=1;i<=15;i++) dbg(st[i]);
}


void solve()
{
	cin >> k >> s>>q;
	n = 1<<k;
	reverse(all(s));
	build();
	while(q--){
		int p;
		char c;
		cin >> p >> c;
		dbg(p, c, (1<<k)-p);
		set1((1<<k)- p, c);
		cout << st[1]<<"\n";
	}
}

int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0), cout.tie(0);
    solve();
}