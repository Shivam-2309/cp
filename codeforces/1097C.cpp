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

bool ok(ll open, ll closed, ll n){
    return open >= closed;
}

void solve() { 
    ll n; cin >> n;
    string s1, s2; cin >> s1 >> s2;
    map<string, ll> mp;
    ll x1 = 0, x2 = 0;
    for(ll i = 0; i < n; i++){
        if(s1[i] == '(') x1++;
        else x2++;

        if(s2[i] == '(') x1++;
        else x2++;
    }
    if(n%2!=0 && x1!=x2){
        cout << "NO" << endl;
        return;
    }

    ll o1 = 0, c1 = 0;
    ll o2 = 0, c2 = 0;

    for(ll i = 0; i < n; i++){
    if(s1[i] == s2[i]) {
        if(s1[i] == '(') { o1++; o2++; }
            else { c1++; c2++; }
        } 
        else {            
            ll bal1 = o1 - c1;
            ll bal2 = o2 - c2;

            if(bal1 <= bal2) {
                o1++; 
                c2++;
            } else {
                o2++;
                c1++;
            }
        }

        if(!ok(o1, c1, n) || !ok(o2, c2, n)) {
            cout << "NO" << endl;
            return;
        }
    }

    // debug(o1);
    // debug(c1);
    // debug(o2);
    // debug(c2);

    if(o1 == c1 && o2 == c2){
        cout << "YES" << endl;
        return;
    }

    cout << "NO" << endl;
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
