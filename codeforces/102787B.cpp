#pragma GCC optimize("O3")
#pragma GCC target("sse4")
#include <bits/stdc++.h>
using namespace std;

using ll = long long;
using vi = vector<int>;
using vvi = vector<vector<int>>;
using pi = pair<int, int>;
using vpi = vector<pair<int, int>>;

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
const int N = 3e5+10;
ll p[N];

void pre(){
	for (int i=0;i<N;i++){
		p[i] = (i? p[i-1]*37%MOD:1);
	}
}

// THIS ISN'T ACTUALLY TESTED, USE WITH CAUTION
// It was written ported to C++ by SecondThread, a Java main,
// so some debugging might be necessary.
struct Treap {
	int data, priority;
	array<Treap*, 2> kids;
	int subtreeSize;
	ll lhash, rhash;
	Treap(int data);
};

int size(Treap *me) {
	return me == NULL ? 0 : me->subtreeSize;
}


void recalc(Treap *me) {
	if (me==NULL) return;
	me->subtreeSize = 1;
	me->lhash = me->data;
	me->rhash = me->data;
	for (Treap* t:me->kids) if (t != NULL) me->subtreeSize += t->subtreeSize;
	if (me->kids[0]!=NULL){
		me->lhash = (me->kids[0]->lhash + me->data*p[size(me->kids[0])])%MOD;
		me->rhash = (me->data + me->kids[0]->rhash*p[1])%MOD;
	}
	if (me->kids[1]!=NULL){
		me->lhash = (me->kids[1]->lhash*p[size(me)-size(me->kids[1])]+me->lhash)%MOD;
		me->rhash = (me->kids[1]->rhash + p[size(me->kids[1])]*me->rhash)%MOD;
	}
}


Treap* merge(Treap *l, Treap *r) {
	if (l==NULL) return r;
	if (r==NULL) return l;
	if (l->priority < r->priority) {
		l->kids[1]=merge(l->kids[1], r);
		recalc(l);
		return l;
	}
	else {
		r->kids[0]=merge(l, r->kids[0]);
		recalc(r);
		return r;
	}
}

array<Treap*, 2> split(Treap *me, int nInLeft) {
	if (me == NULL) return {NULL, NULL};
	if (size(me->kids[0])>=nInLeft) {
		array<Treap*, 2> leftRes=split(me->kids[0], nInLeft);
		me->kids[0]=leftRes[1];
		recalc(me);
		return {leftRes[0], me};
	}
	else {
		nInLeft = nInLeft - size(me->kids[0]) - 1;
		array<Treap*, 2> rightRes = split(me->kids[1], nInLeft);
		me->kids[1] = rightRes[0];
		recalc(me);
		return {me, rightRes[1]};
	}
	return {NULL, NULL};
}

Treap::Treap(int data) {
	kids={NULL, NULL};
	this->data = data;
	this->priority = rng();
	recalc(this);
}

void solve()
{
	Treap * t=nullptr;
	int n, q;
	cin >> n>>q;
	string s;
	cin>>s;
	for (int i=0;i<n;i++){
		Treap* t1 = new Treap(s[i]-'a'+1);
		t = merge(t,t1);
	}
	while(q--){
		int op;
		cin >> op;
		if (op==1){
			int l, r;
			cin >> l >> r;
			ar<Treap*, 2> a = split(t, l-1), b = split(a[1], r-l+1);
			t = merge(a[0], b[1]);
		}else if (op==2){
			char c;
			int p;
			cin >> c >> p;
			ar<Treap*, 2> a = split(t, p-1);
			Treap * tmp = new Treap(c-'a'+1);
			t = merge(a[0], merge(tmp, a[1]));
		}else{
			int l, r;
			cin >> l >> r;
			ar<Treap*,2> a= split(t, l-1), b= split(a[1], r-l+1);
			if (b[0]->lhash == b[0]->rhash){
				cout << "yes\n";
			}else cout << "no\n";
			
			t = merge(a[0], merge(b[0], b[1]));
		}
	}
}

int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0), cout.tie(0);
    pre();
    int testcase=1;
    //)cin >> testcase;
    while (testcase--)
    {
        solve();
    }
}