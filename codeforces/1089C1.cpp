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
ll gcd(ll a, ll b){
    if(b == 0) return a;
    return gcd(b, a % b);
}
ll __lcm(ll a, ll b) {
    return (a / gcd(a, b)) * b;
}

void solve() {
    ll n;
    cin >> n;

    vector<ll> a(n);
    vector<ll> b(n);
    for(ll &x : a) cin >> x;
    for(ll &x : b) cin >> x;

    ll cnt = 0;

    if(n == 1){
        cout << 0 << endl;
        return;
    }

    if(gcd(a[0], a[1]) < a[0]) cnt++;

    for(ll i = 1; i < n - 1; i++){
        ll A = gcd(a[i], a[i - 1]);
        ll B = gcd(a[i], a[i + 1]);
        if(__lcm(A, B) < a[i]) cnt++;
    }

    if(gcd(a[n - 1], a[n - 2]) < a[n - 1]) cnt++;

    cout << cnt << endl;
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
