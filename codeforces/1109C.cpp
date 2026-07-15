// Author : Shivam Kapoor
#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef vector<ll> vll;
typedef pair<ll, ll> pll;

const ll mod7 = 1e9 + 7, mod9 = 998244353, INF = 1e18;
#define fast_io ios::sync_with_stdio(0); cin.tie(0); cout.tie(0);
#define all(v) (v).begin(), (v).end()
#define sz(v) ((ll)(v).size())
#define rep(i, a, b) for (ll i = (a); i < (b); ++i)

#ifndef ONLINE_JUDGE
    #define debug(x) cout << "DEBUG: " << #x << " = " << (x) << endl;
    #define print(v) do { \
        cout << "vect--" << #v << " = [ "; \
        for (auto it = v.begin(); it != v.end(); ++it) cout << *it << " "; \
        cout << "]\n"; \
    } while(0)
#else
    #define debug(x)
    #define print(v)
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

/*
    Simplify The Problem
*/

/*
    Simple Observations
*/

/*
    Algorithm
*/

class DisjointSetUnion {
public:
    vector<int> parent, sz;

    DisjointSetUnion(int n) {
        parent.resize(n);
        sz.assign(n, 1);

        for (int i = 0; i < n; i++)
            parent[i] = i;
    }

    int findPar(int node) {
        if (parent[node] == node)
            return node;

        return parent[node] = findPar(parent[node]); 
    }

    void uni(int u, int v) {
        u = findPar(u);
        v = findPar(v);

        if (u == v)
            return;

        // Union by Size
        if (sz[u] < sz[v])
            swap(u, v);

        parent[v] = u;
        sz[u] += sz[v];
    }
};

void solve() { 
    ll n, x, y; cin >> n >> x >> y;
    vector<ll> v(n);
    for(ll i = 0; i < n; i++) cin >> v[i];
    for(ll i = 0; i < n; i++) v[i]--;

    DisjointSetUnion ds(n);

    map<ll, set<ll>> mp1, mp2;
    for(ll i = 0; i + x < n; i++){
        ds.uni(i, i + x);
    }
    for(ll i = 0; i + y < n; i++){
        ds.uni(i, i + y);
    }

    for(ll i = 0; i < n; i++){
        ll par = ds.findPar(i);
        mp1[par].insert(i);
    }
    for(auto it : mp1){
        ll par = it.first;
        for(auto i : it.second){
            mp2[par].insert(v[i]);
        }
    }

    if(mp1 == mp2){
        cout << "YES" << endl;
    }
    else{
        cout << "NO" << endl;
    }
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
