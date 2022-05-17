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
using BigInt = __int128_t;

__int128_t read()
{
    __int128_t x = 0, f = 1;
    char ch = getchar();
    while (ch < '0' || ch > '9')
    {
        if (ch == '-')
            f = -1;
        ch = getchar();
    }
    while (ch >= '0' && ch <= '9')
    {
        x = x * 10 + ch - '0';
        ch = getchar();
    }
    return x * f;
}
void print(__int128_t x)
{
    if (x < 0)
    {
        putchar('-');
        x = -x;
    }
    if (x > 9)
        print(x / 10);
    putchar(x % 10 + '0');
}
bool cmp(__int128_t x, __int128_t y) { return x > y; }

ostream& operator<< (ostream& os, BigInt x){
	if (x<0){
		os << "-";
		x = -x;
	}
	if (x==0){
		os << 0;
		return os;
	}
	string res = "";
	while(x){
		res += (x%10) + '0';
		x/=10;
	}
	reverse(all(res));
	os << res;
	return os;
}

BigInt GCD(BigInt a, BigInt b){
	return (b==0? a:GCD(b, a%b));
}

BigInt gcd(BigInt a, BigInt b, BigInt& x, BigInt& y) {
    if (b == 0) {
        x = 1;
        y = 0;
        return a;
    }
    BigInt x1, y1;
    BigInt d = gcd(b, a % b, x1, y1);
    x = y1;
    y = x1 - y1 * (a / b);
    return d;
}

void solve()
{
	ll n, p, w,d;
	cin >> n >> p >> w>>d;
	if (p%GCD(w,d)!=0){
		cout << -1 << "\n";
		return;
	}
	BigInt x, y, tmp;
	BigInt g = gcd(w,d, x, y);
	x *= p/g;
	y *= p/g;
	BigInt lo, hi;
	w /= g;
	d /=g;
	if (y>0){
		hi = y/w;
	}else{
		hi = (y-w+1)/w;
	}
	tmp = -x;
	if (tmp>0){
		lo = (tmp+d-1)/d;
	}else{
		lo = (tmp-d+1)/d;
	}
	//cout << lo << " "<< hi << "\n";
	if (lo>hi){
		cout << -1 << "\n";
		return;
	}

	BigInt a = x + hi*d, b = y-hi*w;
	BigInt c = n-a-b;
	if (c<0||a<0||b<0){
		cout << -1 << "\n";
		return;
	}
	
	cout << a << " "<< b << " "<<c <<"\n";
}

int main()
{
	ios_base::sync_with_stdio(0);
	cin.tie(0), cout.tie(0);
    solve();
}