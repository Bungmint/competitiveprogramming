// Copyright © 2022 Youngmin Park. All rights reserved.
//#pragma GCC optimize("O3")
//#pragma GCC target("avx2")
#include <bits/stdc++.h>
using namespace std;

using ll = long long;
using vi = vector<int>;
using pii = pair<int, int>;
using vpi = vector<pii>;
using pll = pair<ll, ll>;
using vl = vector<ll>;
using vpl = vector<pll>;
using ld = long double;
template <typename T, size_t SZ>
using ar = array<T, SZ>;
template <typename T>
using pqg = priority_queue<T, vector<T>, greater<T>>;

#define all(v) (v).begin(), (v).end()
#define pb push_back
#define sz(x) (int)(x).size()
#define fi first
#define se second
#define lb lower_bound
#define ub upper_bound

constexpr int INF = 1e9;
constexpr ll LINF = 1e18;
const ld PI = acos((ld)-1.0);
constexpr int dx[4] = {1, 0, -1, 0}, dy[4] = {0, 1, 0, -1};
mt19937_64 rng(chrono::steady_clock::now().time_since_epoch().count());
template <typename T>
constexpr bool ckmin(T &a, const T &b) { return b < a ? a = b, 1 : 0; }
template <typename T>
constexpr bool ckmax(T &a, const T &b) { return b > a ? a = b, 1 : 0; }
ll cdiv(ll a, ll b) { return a / b + ((a ^ b) > 0 && a % b); } // divide a by b rounded up
ll fdiv(ll a, ll b) { return a / b - ((a ^ b) < 0 && a % b); } // divide a by b rounded down

#ifdef LOCAL
#include "miscellaneous/debug.h"
#else
#define dbg(...) 42
#endif

inline namespace RecursiveLambda {
	template <typename Fun>
	struct y_combinator_result {
		Fun fun_;
		template <typename T>
		explicit constexpr y_combinator_result(T &&fun) : fun_(forward<T>(fun)) {}
		template <typename... Args>
		constexpr decltype(auto) operator()(Args &&...args) const {
			return fun_(ref(*this), forward<Args>(args)...);
		}
	};
	template <typename Fun>
	decltype(auto) y_combinator(Fun &&fun) {
		return y_combinator_result<decay_t<Fun>>(forward<Fun>(fun));
	}
};

// TODO: Test implementation
/**
 * Description: Implementation of 2D points using std::pair
 * Source: Benq
 * Verification: Various
 */

// #include "../miscellaneous/template.h"

using T = ld; // Can be ll
constexpr T EPS = 1e-9;
using Point = pair<T, T>; 
using vP = vector<Point>;
using Line = pair<Point, Point>;
int sgn(T a) { return (a > EPS) - (a < -EPS); }
T sq(T a) { return a*a; }

bool close(const Point& a, const Point& b) {
    return sgn(a.fi-b.fi) == 0 && sgn(a.se-b.se) == 0;
}
T norm(const Point& a) { return sq(a.fi) + sq(a.se); }
T abs(const Point& a) { return sqrt(norm(a)); }
T arg(const Point& a) { return atan2(a.se, a.fi); }
Point conj(const Point& a) { return Point(a.fi, -a.se); }
Point perp(const Point& a) { return Point(-a.se, a.fi); }
Point dir(T ang) { return Point(cos(ang), sin(ang)); }

Point operator-(const Point& l) { return Point(-l.fi, -l.se); }
Point operator+(const Point& l, const Point& r) {
    return Point(l.fi+r.fi, l.se+r.se);
}
Point operator-(const Point& l, const Point& r) {
    return Point(l.fi-r.fi, l.se-r.se);
}
Point operator*(const Point& l, const T& r) {
    return Point(r*l.fi, r*l.se);
}
Point operator*(const T& l, const Point& r) {
    return r*l;
}
Point operator/(const Point& l, const T& r) {
    return Point(l.fi/r, l.se/r);
}
Point operator*(const Point& l, const Point& r) {
    return Point(l.fi*r.fi-l.se*r.se, l.fi*r.se+l.se*r.fi);
}
Point operator/(const Point& l, const Point& r) {
    return l*conj(r)/norm(r);
}
Point& operator+=(Point& l, const Point& r) { return l = l + r; }
Point& operator-=(Point& l, const Point& r) { return l = l - r; }
Point& operator*=(Point& l, const T& r)     { return l = l * r; }
Point& operator/=(Point& l, const T& r)     { return l = l / r; }
Point& operator*=(Point& l, const Point& r) { return l = l * r; }
Point& operator/=(Point& l, const Point& r) { return l = l / r; }

Point unit(const Point& p) { return p/abs(p); }
T dot(const Point& a, const Point& b) { return a.fi*b.fi + a.se*b.se; }
T dot(const Point& p, const Point& a, const Point& b) {
    return dot(a-p, b-p);
}
T cross(const Point& a, const Point& b) { return a.fi*b.se - a.se*b.fi; }
T cross(const Point& p, const Point& a, const Point& b) {
    return cross(a-p, b-p);
}
Point reflect(const Point& p, const Line& l) { // Check EGMO for the proof
    Point a = l.fi, b = l.se;
    Point d = b - a;
    return a + conj((p-a)/d)*d;
}
Point foot(const Point& p, const Line& l) {
    return (p+reflect(p, l))/T(2);
}
bool on_seg(const Point& p, const Line& l) {
    return sgn(cross(p, l.fi, l.se)) == 0 &&
           sgn(dot(p, l.fi, l.se)) <= 0;
}
istream& operator>>(istream& is, Point& a) {
    is >> a.fi >> a.se;
    return is;
}

/**
 * Description: Fast input and output.
 * Time: input is $\sim$300ms faster for $10^6$ long longs on CF
 * Source: 
 	* https://codeforces.com/contest/1254/submission/65420506 (neal)
 * Verification: https://codeforces.com/gym/102394/problem/G 
 */

namespace FastIO {
    constexpr int BUFFER_SIZE = 1 << 15;

    char input_buffer[BUFFER_SIZE];
    int input_pos = 0, input_len = 0;

    char output_buffer[BUFFER_SIZE];
    int output_pos = 0;

    char number_buffer[100];
    uint8_t lookup[100];
 
    void _update_input_buffer() {
        input_len = fread(input_buffer, sizeof(char), BUFFER_SIZE, stdin);
        input_pos = 0;
        if (input_len == 0) input_buffer[0] = EOF;
    }
    inline char next_char(bool advance = true) {
        if (input_pos >= input_len) _update_input_buffer();
        return input_buffer[advance ? input_pos++ : input_pos];
    }
    void read_string(string &s) {
        char ch; 
        while (isspace(ch = next_char()));
        do {
            s += ch;
        } while(!isspace(ch = next_char()) && ch != EOF);
    }
    template<typename T>
    inline void read_int(T &number) {
        bool negative = false;
        number = 0;
        while (!isdigit(next_char(false)))
            if (next_char() == '-') negative = true;
        do {
            number = 10 * number + (next_char() - '0');
        } while (isdigit(next_char(false)));
        if (negative) number = -number;
    }
    template<typename T, typename... Args>
    inline void read_int(T &number, Args &... args) {
        read_int(number);
        read_int(args...);
    }
    void _flush_output() {
        fwrite(output_buffer, sizeof(char), output_pos, stdout);
        output_pos = 0;
    }
    inline void write_char(char c) {
        if (output_pos == BUFFER_SIZE) _flush_output();
        output_buffer[output_pos++] = c;
    }
    void write_string(const string& s) {
		int cnt = 0;
		bool fl = 0;
        for (auto &ch : s) {
			if (cnt == 2) return;
			write_char(ch);
			if (ch == '.') fl = 1;
			else if (fl) cnt++;
		}
    }
    template<typename T>
    inline void write_int(T number, char after = '\0') {
        if (number < 0) {
            write_char('-');
            number = -number;
        }
        int length = 0;
        while (number >= 10) {
            uint8_t lookup_value = lookup[number % 100];
            number /= 100;
            number_buffer[length++] = (lookup_value & 15) + '0';
            number_buffer[length++] = (lookup_value >> 4) + '0';
        }
        if (number != 0 || length == 0) write_char(number + '0');
        for (int i = length - 1; i >= 0; i--) write_char(number_buffer[i]);
        if (after) write_char(after);
    }
    void init() {
        // Make sure _flush_output() is called at the end of the program.
        bool exit_success = atexit(_flush_output) == 0;
        assert(exit_success);
        for (int i = 0; i < 100; i++) lookup[i] = (i / 10 << 4) + i % 10;
    }
}
using namespace FastIO;

void solve() {
	init();
	while (1) {
		int n;
		read_int(n);
		dbg(n);
		if (n == 0) return;
		vP a(n);
		for (auto &e : a) {
			string s, t;
			read_string(s); read_string(t);
			e.fi = stod(s), e.se = stod(t);
		}
		dbg(a);
		ld d = LINF;
		Line min_dist{};
		sort(all(a));
		int ptr = 0;
		auto cmp = [&](const Point& x, const Point& y) {
			return x.se + EPS < y.se;
		};
		multiset<Point, decltype(cmp)> st(cmp);
		for (int i = 0; i < n; i++) {
			// if (i && a[i] == a[i - 1]) {
			// 	cout << a[i-1].fi << ' ' << a[i-1].se << ' ';
			// 	cout << a[i].fi << ' ' << a[i].se << '\n';
				
			// }
			for (; ptr < n && (a[i].fi-a[ptr].fi) > EPS + d; ptr++) {
				st.erase(st.find(a[ptr]));
			}
			for (auto it = st.lb({0.0, a[i].se-d}); it != st.end() && it->se + EPS < a[i].se+d; it++) {
				if (ckmin(d, abs(*it-a[i]))) {
					min_dist = {*it, a[i]};
				}
			}
			st.insert(a[i]);
		}
		auto [p, q] = min_dist;
		dbg(p, q);
		write_string(to_string(p.fi));
		write_char(' ');
		write_string(to_string(p.se));
		write_char(' ');
		write_string(to_string(q.fi));
		write_char(' ');
		write_string(to_string(q.se));
		write_char('\n');
		// printf("%.2Lf %.2Lf %.2Lf %.2Lf\n", p.fi, p.se, q.fi, q.se);
		// cout << min_dist.fi.fi << ' ' << min_dist.fi.se << ' ';
		// cout << min_dist.se.fi << ' ' << min_dist.se.se << '\n';
	}
}

int main() {
	// cin.tie(0)->sync_with_stdio(0);
	// cin.exceptions(cin.failbit);
	int testcase = 1;
	// cin >> testcase;
	while (testcase--) {
		solve();
	}
// #ifdef LOCAL
// 	cerr << "Time elapsed: " << 1.0 * (double)clock() / CLOCKS_PER_SEC << " s.\n";
// #endif
}
