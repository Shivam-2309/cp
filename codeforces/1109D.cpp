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
vector<ll> a;
vector<ll> b;
vector<vector<ll>> dp;
ll f(ll idx, ll flipped){
    if(idx == 0){
        ll v1 = (flipped ? -a[idx] : a[idx]);
        if(b[idx]){
            ll p1 = -v1;
            ll p2 = v1;

            return max(p1, p2);
        }else{
            ll p2 = v1;
            return p2;
        }
    }

    if(dp[idx][flipped] != -1) return dp[idx][flipped];

    ll v1 = (flipped ? -a[idx] : a[idx]);
    if(b[idx]){
        ll p1 = -v1 + f(idx - 1, flipped ? 0 : 1);
        ll p2 = v1 + f(idx - 1, flipped);

        return dp[idx][flipped] = max(p1, p2);
    }

    ll p2 = v1 + f(idx - 1, flipped);
    return dp[idx][flipped] = p2;
}

void solve() {  
    ll n, m; cin >> n >> m;
    a.clear();
    b.clear();
    dp.clear();
    a.resize(n);
    b.resize(n, 0);
    dp.resize(n + 1, vector<ll> (2, -1));
    for(ll i = 0; i < n; i++) cin >> a[i];
    for(ll i = 0; i < m; i++){
        ll idx; cin >> idx;
        b[idx - 1] = 1;
    }
    // print(a);
    // print(b);
    ll ans = f(n - 1, 0);
    if(b.back() == n - 1) ans = max(ans, f(n - 1, 1));
    cout << ans << endl;
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
