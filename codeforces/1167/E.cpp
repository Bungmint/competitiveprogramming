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
        for (auto &ch : s) write_char(ch);
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

constexpr int M = 1e6 + 10;
int a[M], pr[M], su[M];
vi ind[M];
bool l_good[M], r_good[M];

void solve() {
	init();
	int n, x;
	read_int(n, x);
	int pref = -1, suf = n;
	for (int i = 0; i < n; i++) {
		read_int(a[i]);
		ind[a[i]].pb(i);
	}
	l_good[0] = 1;
	pr[0] = -1;
	r_good[x + 1] = 1;
	su[x + 1] = n;
	for (int i = 1; i <= x; i++) {
		if (sz(ind[i]) && pref > ind[i].front()) {
			break;
		}
		l_good[i] = 1;
		if (sz(ind[i])) pref = ind[i].back();
		pr[i] = pref;
	}
	for (int i = x; i >= 1; i--) {
		if (sz(ind[i]) && suf < ind[i].back()) {
			break;
		}
		r_good[i] = 1;
		if (sz(ind[i])) suf = ind[i].front();
		su[i] = suf;
		dbg(suf);
	}
	ll ans{};
	int r = 2;
	for (int l = 0; l <= x - 1; l++) {
		if (!l_good[l]) break;
		while (r <= x + 1 && (l + 2 > r || !r_good[r] || su[r] <= pr[l])) {
			r++;
		}
		dbg(r, x-r+2);
		ans += x - r + 2;
	}
	write_int(ans, '\n');
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
