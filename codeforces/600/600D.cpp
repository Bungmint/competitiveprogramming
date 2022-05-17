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

struct Circle{
	ll x, y, r;
};

istream& operator>>(istream& is, Circle& c){
	is >> c.x>>c.y>>c.r;
	return is;
}
ostream& operator<<(ostream& os, Circle& c){
	os << c.x <<" "<< c.y << " "<< c.r;
	return os;
}

inline ll sq(ll x){
	return x*x;
}

ll dist(Circle& c1, Circle& c2){
	return (c1.x-c2.x)*(c1.x-c2.x) + (c1.y-c2.y)*(c1.y-c2.y);
}

bool intersect(Circle& c1, Circle& c2){
	return (dist(c1,c2)<(c1.r+c2.r)*(c1.r+c2.r)) ;
}

bool contains(Circle c1, Circle c2){
	if (c1.r>c2.r) swap(c1, c2);
	return (dist(c1,c2)<=sq(c1.r-c2.r));
}


ld tri(ld a,ld b, ld c){
	ld s = (a+b+c)/(ld)2;
	return sqrt(s*(s-a)*(s-b)*(s-c));
}

void solve()
{
	Circle c1, c2;
	cin >> c1 >> c2;
	cout << setprecision(20);
	if (!intersect(c1,c2)){
		cout << 0 << "\n";
		return;
	}
	if (contains(c1,c2)){
		cout << acos(-1)*(ld)sq(min(c1.r,c2.r))<<"\n";
		return;
	}
	dbg(c1,c2);
	ll dsq = dist(c1,c2);
	ld d = sqrtl(dsq);
	ld t1 = acos((ld)(sq(c1.r)+dsq-sq(c2.r))/(ld)(2*c1.r*d));
	ld t2 = acos((ld)(sq(c2.r)+dsq-sq(c1.r))/(ld)(2*c2.r*d));
	ld sec1 = (ld)sq(c1.r)*t1- (ld)sq(c1.r)*sin(t1)*cos(t1);
	ld sec2 = (ld)sq(c2.r)*t2-(ld)sq(c2.r)*sin(t2)*cos(t2);
	cout << sec1+sec2 << "\n";
}

int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0), cout.tie(0);
    solve();
}