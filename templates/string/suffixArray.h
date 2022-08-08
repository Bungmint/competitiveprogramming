/**
 * Description: Sort suffixes. The first element of SA is sz(S),
    * isa is the inverse of sa, and lcp stores
    * the longest common prefix of two consecutive elements of sa
 * Source: Benq
 * Verification:
 * Time complexity: O(nlogn)
 */

#include "data-structures/sparseTable.h"

struct SuffixArray {
    string s; 
    int n;
    vi sa, isa, lcp;
    SparseTable<int> rmq;
    SuffixArray(const string &_s) : s(_s) {
        s += (char)(0);
        n = sz(s);
        generate_sa();
        generate_lcp();
    }
    void count_sort_zero() {
        vi cnt(128), pos(128);
        for (int i = 0; i < n; i++) cnt[s[i]]++;
        for (int i = 1; i < 128; i++) pos[i] = pos[i - 1] + cnt[i - 1];
        for (int i = 0; i < n; i++) {
            sa[pos[s[i]]++] = i;
        }
        isa[sa[0]] = 0;
        for (int i = 1; i < n; i++) {
            isa[sa[i]] = isa[sa[i - 1]];
            if (s[sa[i]] != s[sa[i - 1]]) isa[sa[i]]++;
        }
    }
    void count_sort(int k) {
        vi cnt(n), pos(n), new_sa(n), new_isa(n);
        for (int i = 0; i < n; i++) cnt[isa[i]]++;
        for (int i = 1; i < n; i++) pos[i] = pos[i - 1] + cnt[i - 1];
        for (int i = 0; i < n; i++) {
            new_sa[pos[isa[sa[i]]]++] = sa[i];
        }
        swap(sa, new_sa);
        for (int i = 1; i < n; i++) {
            new_isa[sa[i]] = new_isa[sa[i - 1]];
            if (isa[sa[i]] != isa[sa[i - 1]] || 
            isa[(sa[i] + (1 << k)) % n] != isa[(sa[i - 1] + (1 << k)) % n]) {
                new_isa[sa[i]]++;
            }
        }
        swap(isa, new_isa);
    }
    void generate_sa() {
        int k = 0;
        sa.resize(n); isa.resize(n);
        count_sort_zero();
        while ((1 << k) < n) {
            for (auto &x : sa) {
                x -= (1 << k);
                if (x < 0) x += n;
            }
            count_sort(k++);
        }
    }
    void generate_lcp() {
        lcp.resize(n - 1);
        int k = 0;
        for (int i = 0; i < n - 1; i++) {
            int pi = isa[i];
            int j = sa[pi - 1];
            while (s[i + k] == s[j + k]) k++;
            lcp[pi - 1] = k;
            if (k) k--;
        }
        rmq = SparseTable<int>(lcp);
    }
    int get_lcp(int a, int b) {
        if (a == b) return sz(s) - a;
        int l = isa[a], r = isa[b];
        if (l > r) swap(l, r);
        return rmq.query(l, r - 1);
    }
};
