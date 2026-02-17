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

ll dfs1(ll node, ll par, vector<vector<ll>> &adj, vector<ll> &dp){
    if(node != 0 && adj[node].size() == 1){
        // leaf found
        dp[node] = 0;
        return 0;
    }

    for(auto it : adj[node]){
        if(it == par) continue;
        ll res = dfs1(it, node, adj, dp); 
    }

    ll cnt = 0;
    for(auto it : adj[node]){
        if(it == par) continue;
        cnt++;
        cnt = cnt % mod7;
        cnt += dp[it];
        cnt = cnt % mod7;
    }

    return dp[node] = cnt % mod7;
}

void dfs2(ll node, ll par, vector<vector<ll>> &adj, vector<ll> &dp, vector<ll> &res){
    if(node != 1){
        // debug(node);
        ll up = res[par];
        // debug(up);
        ll ans = ((up + (2*dp[node]) % mod7) % mod7 + 1) % mod7;
        res[node] = ans;
    }

    for(auto &child : adj[node]){
        if(child == par) continue;
        dfs2(child, node, adj, dp, res);
    }
}

void solve() { 
    // (n + 1) vertices -> [0, 1, 2 ----> n] rooted at 0
    // 0 is the parent of 1 and all other have 2 children -> n is odd makes sense !!
    // leaf -> go to parent
    // nothing written -> write L nd go to left child
    // if L -> overwrites and go to right child
    // if R -> erase it and move to parent

    // hint of tree re routing !!
    // dp[u] : total number of edges in the subtree of node u
    ll n; cin >> n;
    vector<vector<ll>> adj(n + 1);
    adj[0].push_back(1);
    adj[1].push_back(0);
    for(ll i = 1; i <= n; i++){
        // for node (i - 1)
        ll l, r; cin >> l >> r;
        if(l == 0 && r == 0) continue;

        adj[i].push_back(l);
        adj[l].push_back(i);

        adj[i].push_back(r);
        adj[r].push_back(i);
    }

    vector<ll> dp(n + 1, 0);
    ll totEdges = dfs1(0, -1, adj, dp);
    // debug(totEdges);
    // print(dp);
    vector<ll> res(n + 1, 0);
    res[1] = 2*n - 1;

    dfs2(1, 0, adj, dp, res);
    // print(res);
    for(ll i = 1; i <= n; i++) cout << res[i] << " ";
    cout << endl;
}

int main() {
    fast_io
    #ifndef ONLINE_JUDGE
        freopen("Error.txt", "w", stderr);
    #endif
    ll t = 1;
    cin >> t;
    while (t--) solve();
    return 0;
}