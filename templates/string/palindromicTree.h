/**
 * Description: Trie-like structure storing distinct palindromes. Also called eertree
    * Edge from u to v with character c: S_v = "c" + S_u + "c"
    * Suffix links: Links to the longest nontrivial palindromic suffix
    * Root 1 = Length -1, Root 2 = Length 0
    * Unlike a trie, the number of nodes (distinct palindromes) is bounded to O(|S|)
    * For rollback, use an additional array of "smart suffix link" 
        * Which points to the maximum suffix palindrome with t preceding the palindrome
 * Source: http://adilet.org/blog/palindromic-tree/ 
 * Verification:
 * Time complexity: O(|S|) (Amortized, trying to rollback naively would result in TL)
 * Memory complexity: O(\sigma |S|) but can be reduced by not storing all edges
    * Check adamant's comment - https://codeforces.com/blog/entry/13959?#comment-313090
 */

struct Node {
    int to[26];
    int len;
    int link;
};

const int MAXN = 1e5;
Node tree[MAXN];
string s;
int num, last_suf; 

bool add_char(int pos) {
    int c = s[pos] - 'a';
    int cur = last_suf, cur_len = 0;
    while (1) {
        cur_len = tree[cur].len;
        if (pos-1-cur_len >= 0 && s[pos-1-cur_len] == s[pos]) {
            break;
        }
        cur = tree[cur].link;
    }
    if (tree[cur].to[c]) {
        last_suf = tree[cur].to[c];
        return false;
    }
    num++;
    tree[cur].to[c] = num;
    tree[num].len = 2 + tree[cur].len;
    last_suf = num;
    if (tree[num].len == 1) {
        tree[num].link = 2;
        return true;
    }
    while (1) {
        cur = tree[cur].link;
        cur_len = tree[cur].len;
        if (pos-1-cur_len >= 0 && s[pos-1-cur_len] == s[pos]) {
            tree[num].link = tree[cur].to[c];
            return true;
        }
    }
}
void init_tree() {
    tree[1].len = -1; tree[2].len = 0;
    tree[1].link = tree[2].link = 1;
    num = last_suf = 2;
}