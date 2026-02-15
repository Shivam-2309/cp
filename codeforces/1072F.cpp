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

// in my rooted tree i need to shake at any point and all the descendents of the tree would fall -> subtree would be cleared
// ever leaf must be touched once 
// number of vertices to shake is a multiple of 3 -> important !!
// if leaves % 3 == 0 -> YES
// at any vertice how many leaves are under it -> dp[u]
// now agr i have total leaves as 7 and one node has 2 leaves under it the yes it can be possbile

// dp[node][k] : is it possible to shake the subtree of node u abiding all the conditions such that the number of shakes
//               congruent to (k % 3)
void dfs(ll node, ll par, vector<vector<ll>> &adj, vector<vector<bool>> &dp, vector<ll> &subtree){
    if(node != 0 && adj[node].size() == 1) {
        dp[node][0] = false;
        dp[node][1] = true;
        dp[node][2] = false;
        return;
    }

    ll totLeaves = subtree[node] % 3;
    dp[node][totLeaves] = true;
    dp[node][1] = true;

    for(auto child : adj[node]){
        if(child == par) continue;
        dfs(child, node, adj, dp, subtree);
    }
    ll num_child = adj[node].size() - (par == -1 ? 0 : 1);

    vector<bool> dp1(3, false);
    dp1[0] = true;
    for(auto child : adj[node]){
        if(child == par) continue;
        vector<bool> dp2(3, false);
        if(dp[child][0]){
            // acha to zero add ho skta h
            if(dp1[0]) dp2[(0 + 0) % 3] = true;
            if(dp1[1]) dp2[(1 + 0) % 3] = true;
            if(dp1[2]) dp2[(2 + 0) % 3] = true;
        }
        if(dp[child][1]){
            // acha to one add ho skta h 
            if(dp1[0]) dp2[(0 + 1) % 3] = true;
            if(dp1[1]) dp2[(1 + 1) % 3] = true;
            if(dp1[2]) dp2[(2 + 1) % 3] = true;
        }
        if(dp[child][2]){
            // acha to two add ho skta h
            if(dp1[0]) dp2[(0 + 2) % 3] = true;
            if(dp1[1]) dp2[(1 + 2) % 3] = true;
            if(dp1[2]) dp2[(2 + 2) % 3] = true;
        }
        dp1 = dp2;
    }

    if(dp1[0]) dp[node][0] = true;
    if(dp1[2]) dp[node][2] = true;

    dp[node][totLeaves] = true;
    dp[node][1] = true;
}


ll dfs1(ll node, ll par, vector<vector<ll>> &adj, vector<ll> &subtree){
    if(node != 0 && adj[node].size() == 1){
        subtree[node] = 1;
        return 1;
    }
    ll cnt = 0;
    for(auto it : adj[node]){
        if(it == par) continue;
        cnt += dfs1(it, node, adj, subtree);
    }
    return subtree[node] = cnt;
}

void solve() { 
    ll n; cin >> n;
    vector<vector<ll>> adj(n);
    for(ll i = 1; i <= n - 1; i++){
        ll u, v; cin >> u >> v;
        u--; v--;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    vector<ll> subtree(n, 0);
    ll totLeaves = dfs1(0, -1, adj, subtree);
    // print(subtree);

    vector<vector<bool>> dp(n, vector<bool> (3, false));
    dfs(0, -1, adj, dp, subtree);

    if(dp[0][0]) cout << "YES" << endl;
    else cout << "NO" << endl;
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

// is it possible to find the sum of s sequence by selecting one from every row such that the sum is congruent to k
// dp1[n - 1][k] is true ???
 