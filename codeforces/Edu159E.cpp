// Author : Shivam Kapoor
#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef vector<ll> vll;
typedef pair<ll, ll> pll;

const ll mod7 = 1e9 + 7, mod9 = 998244353, INF = 1e18;
#define fast_io ios::sync_with_stdio(0); cin.tie(0); cout.tie(0);
#define all(v) (v).begin(), (v).end()
#define rall(v) (v).rbegin(), (v).rend()
#define sz(v) ((ll)(v).size())
#define rep(i, a, b) for (ll i = (a); i < (b); ++i)
#define rrep(i, a, b) for (ll i = (b)-1; i >= (a); --i)

#ifndef ONLINE_JUDGE
    #define debug(x) cout << "DEBUG: " << #x << " = " << (x) << endl;
    #define print(v) do { \
        cout << "vect--" << #v << " = [ "; \
        for (auto it = v.begin(); it != v.end(); ++it) cout << *it << " "; \
        cout << "]\n"; \
    } while(0)
    #define print2d(v) do { \
        cout << "Matrix:\n"; \
        for (auto it = v.begin(); it != v.end(); ++it) { \
            for (auto jt = it->begin(); jt != it->end(); ++jt) cout << *jt << " "; \
            cout << "\n"; \
        } \
    } while(0)
    #define printmap(m) do { \
        cout << "Map:\n"; \
        for (auto it = m.begin(); it != m.end(); ++it) { \
            cout << it->first << " -> " << it->second << "\n"; \
        } \
    } while(0)
    #define printpp(v) do { \
        cout << "[ "; \
        for (auto it = v.begin(); it != v.end(); ++it) cout << "(" << it->first << ", " << it->second << ") "; \
        cout << "]\n"; \
    } while(0)
#else
    #define debug(x)
    #define print(v)
    #define print2d(v)
    #define printmap(m)
    #define printpp(v)
#endif

ll modAdd(ll a, ll b, ll m = mod7) { return (a + b) % m; }
ll modSub(ll a, ll b, ll m = mod7) { return (a - b + m) % m; }
ll modMul(ll a, ll b, ll m = mod7) { return (a * b) % m; }
ll modExp(ll base, ll exp, ll m = mod7) { 
    ll res = 1; 
    while (exp) { 
        if (exp % 2) res = modMul(res, base, m); 
        base = modMul(base, base, m); 
        exp /= 2; 
    } 
    return res; 
}
ll modInv(ll a, ll m = mod7) { return modExp(a, m - 2, m); }

/* Define a struct for
each node in the trie */
struct Node {
    /* Array to store
    links to child nodes */
    Node* links[26];
    /* Counter for number of
    words that end at this node */
    int cntEndWith = 0;
    /* Counter for number of words
    that have this node as a prefix */
    int cntPrefix = 0;

    /* Function to check if the
    node contains a specific key */
    bool containsKey(char ch) {
        /* Check if the link corresponding
        to the character exists */
        return (links[ch - 'a'] != NULL);
    }

    /* Function to get the child
    node corresponding to a key */
    Node* get(char ch) {
        /* Return the link
        corresponding to the character */
        return links[ch - 'a'];
    }

    /* Function to insert a child
    node with a specific key */
    void put(char ch, Node* node) {
        /* Set the link corresponding to
        the character to the provided node */
        links[ch - 'a'] = node;
    }

    /* Function to increment the
    count of words that end at this node */
    void increaseEnd() {
        /* Increment the counter */
        cntEndWith++;
    }

    /* Function to increment the count of
    words that have this node as a prefix */
    void increasePrefix() {
        /* Increment the counter */
        cntPrefix++;
    }

    /* Function to decrement the count
    of words that end at this node */
    void deleteEnd() {
        /* Decrement the counter */
        cntEndWith--;
    }

    /* Function to decrement the count of
    words that have this node as a prefix */
    void reducePrefix() {
        /* Decrement the counter */
        cntPrefix--;
    }
};

class Trie {
private:
    Node* root;

public:
    Trie() {
        root = new Node();
    }
    void insert(string word) {
        Node* node = root;
        for (int i = 0; i < word.size(); i++) {
            if (!node->containsKey(word[i])) {
                node->put(word[i], new Node());
            }
            node = node->get(word[i]);
            node->increasePrefix();
        }
        node->increaseEnd();
    }

    int countWordsStartingWith(string word) {
        Node* node = root;
        for (int i = 0; i < word.size(); i++) {
            if (node->containsKey(word[i])) {
                node = node->get(word[i]);
            } else {
                return 0;
            }
        }
        return node->cntPrefix;
    }

    int check(string word, ll n) {
        ll add = 0;
        ll done = 0;
        print(word);
        Node* node = root;
        ll currlen = word.length();
        for (int i = 0; i < word.size(); i++) {
            if (node -> containsKey(word[i])) {
                node = node -> get(word[i]);
                ll left = (n - node->cntPrefix);
                ll newdo = left - done;
                debug(newdo);
                add += ((2 * currlen) * newdo);
                done = left;

                currlen--;
            } else {
                ll left = n;
                ll newdo = left - done;
                add += ((2 * currlen) * newdo);
                break;
            }
        }
        return add;
    }
};

void solve() { 
    ll n; cin >> n;
    vector<string> v(n);
    for(ll i = 0; i < n; i++){
        string s; cin >> s;
        v[i] = s;
    }

    // ab sbko daaldo meri trie mn
    Trie t;
    for(ll i = 0; i < n; i++){
        string s1 = v[i];
        reverse(s1.begin(), s1.end());
        t.insert(s1);
    }

    ll ans = 0;
    for(ll i = 0; i < n; i++){
        string s = v[i];
        ll y = (t.check(s, n));
        debug(y);
        ans += y;
    }
    cout << ans << endl;
}

int main() {
    fast_io
    #ifndef ONLINE_JUDGE
        freopen("Error.txt", "w", stderr);
    #endif
    ll t = 1;
    // cin >> t;
    while (t--) solve();
    return 0;
}
