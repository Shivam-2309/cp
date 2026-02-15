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

void solve() { 
    ll n; cin >> n;
    vector<ll> a(n + 1), b(n + 1);
    for(ll i = 1; i <= n; i++){
        cin >> a[i];
        cin >> b[i];
    }

    // dp[i][0] : min cost to make the first i elements of the vector good with the ith element not changed
    // dp[i][1] : min cost to make the first i elements of the vector good with the ith element increase once
    // dp[i][2] : min cost to make the first i elements of the vector good with the ith element increased twice
    // ans -> min({dp[n][0], dp[n][1], dp[n][2]}) -> GOOD

    // dp[i][0] -> dp[i - 1][0] (if possible) dp[i - 1][1] (if possible) dp[i - 1][2] if possible
    vector<vector<ll>> dp(n + 1, vector<ll> (3, -1));
    dp[1][0] = 0;
    dp[1][1] = b[1];
    dp[1][2] = 2 * b[1];

    for(ll i = 2; i <= n; i++){
        dp[i][0] = 1e18;
        if(a[i - 1] != a[i]) dp[i][0] = min(dp[i][0], dp[i - 1][0]);
        if(a[i - 1] + 1 != a[i]) dp[i][0] = min(dp[i][0], dp[i - 1][1]);
        if(a[i - 1] + 2 != a[i]) dp[i][0] = min(dp[i][0], dp[i - 1][2]);

        dp[i][1] = 1e18;
        if(a[i - 1] != a[i] + 1) dp[i][1] = min(dp[i][1], dp[i - 1][0] + b[i]);
        if(a[i - 1] + 1 != a[i] + 1) dp[i][1] = min(dp[i][1], dp[i - 1][1] + b[i]);
        if(a[i - 1] + 2 != a[i] + 1) dp[i][1] = min(dp[i][1], dp[i - 1][2] + b[i]);

        dp[i][2] = 1e18;
        if(a[i - 1] != a[i] + 2) dp[i][2] = min(dp[i][2], dp[i - 1][0] + 2*b[i]);
        if(a[i - 1] + 1 != a[i] + 2) dp[i][2] = min(dp[i][2], dp[i - 1][1] + 2*b[i]);
        if(a[i - 1] + 2 != a[i] + 2) dp[i][2] = min(dp[i][2], dp[i - 1][2] + 2*b[i]);
        // debug(i);
        // debug(dp[i][0]);
        // debug(dp[i][1]);
        // debug(dp[i][2]);
    }

    cout << min({dp[n][0], dp[n][1], dp[n][2]}) << endl;
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
