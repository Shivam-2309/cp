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

void solve() { 
    ll n; cin >> n;
    vector<ll> v(n);
    for(ll i = 0; i < n; i++) cin >> v[i];
    vector<ll> p = v;
    for(ll i = 1; i < n; i++) p[i] += p[i - 1];
    vector<ll> a = v;
    sort(a.begin(), a.end());
    ll ans = 0;
    vector<ll> suff = v;
    for(ll i = n - 2; i >= 0; i--) suff[i] = min(suff[i], suff[i + 1]);
    // print(suff);
    for(ll h = 1; h <= a.back(); h++){
        // find first index from the back such that the value is strictly less than h
        ll lo = 0;
        ll hi = n - 1;
        ll idx = n;

        while(lo <= hi){
            ll mid = (lo + hi)/2LL;
            if(suff[mid] >= h){
                idx = mid;
                hi = mid - 1;
            }
            else{
                lo = mid + 1;
            }
        }
        // debug(idx);
        ll intact = (n - idx);
        // debug(intact);
        ll tot = n - (lower_bound(a.begin(), a.end(), h) - a.begin());
        ll hile = (tot - intact);
        ans += hile;
        // debug(hile);
    }   
    // debug(ans);
    ll res = ans;
    // uthane ka faeda sirf tbhi h jb usko htane ke baad kuch effect aaye.
    // iska mtlb hatao sirf tbhi agr vo ek suffix minimum ho.
    // print(suff);
    for(ll i = n - 1; i >= 0; i--){
        if(v[i] != suff[i]) continue;
        // mtlb htake kuch acha ho skta h !!
        // debug(i);
        ll lo = 0;
        ll hi = i;
        ll idx = i;
        while(lo <= hi){
            ll mid = (lo + hi)/2LL;
            if(suff[mid] >= v[i]){
                idx = mid;
                hi = mid - 1;
            }
            else{
                lo = mid + 1;
            }
        }
        // debug(idx);
        ll hile = (i - idx);
        ll better = res + hile;
        // debug(better);
        ans = max(ans, better);
    }
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
