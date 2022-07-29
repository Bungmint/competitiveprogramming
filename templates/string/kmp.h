/**
 * Description: Knuth-Morris-Pratt Algorithm
 * Source: Academic paper
 * Verification: CSES 1753 - https://cses.fi/problemset/task/1753
 * Time complexity - O(n), n = length of the string
 */

vi kmp(const string& s) {
    int n = sz(s);
    vi pi(n);
    for (int i = 1, j = 0; i < n; i++) {
        while (j && s[i] != s[j]) {
            j = pi[j - 1];
        }
        if (s[i] == s[j]) j++;
        pi[i] = j;
    }
    return pi;
}