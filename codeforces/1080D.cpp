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


// 1 <= ai <= 1000 -> not used yet !!
// f(x) = sum(ai * (i - x)) for all i
// f(1) : (2 - 1)a2 + (3 - 1)a3 + (4 - 1)a4 + (5 - 1)a5 ----> (n - 1 - 1)an-1 + (n - 1)an
//      : a2 + 2a3 + 3a4 + 4a5 + -----> (n - 2)an-1 + (n - 1)an
// f(2) : (1 - 2)a1 + (3 - 2)a3 + (4 - 2)a4 + (5 - 2)a5 ----> (n - 1 - 2)an-1 + (n - 2)an
//      : a1 + a3 + 2a4 + 3a5 + 4a6 + -------> (n - 1 - 2)an-1 + (n - 2)an
// f(1) : 0a1 + 1a2 + 2a3 + 3a4 + 4a5 = x1
// f(2) : 1a1 + 0a2 + 1a3 + 2a4 + 3a5 = x2
// f(3) : 2a1 + 1a2 + 0a3 + 1a4 + 2a5 = x3
// f(4) : 3a1 + 2a2 + 1a3 + 0a4 + 1a5 = x4
// f(5) : 4a1 + 3a2 + 2a3 + 1a4 + 0a5 = x5

// (x1 + x5) = (n - 1)*(a1 + a2 + a3 + a4 + a5)
// (x2 + x4) = (n - 2)*(a1 + a2 + a3 + a4 + a5)

// f(2) - f(1) - (a1 + a2 + a3 + a4 + a5) : 0 - 2a2 - 2a3 - 2a4 - 2a5
// f(3) - f(2) - (a1 + a2 + a3 + a4 + a5) : 0 + 0 - 2a3 - 2a4 - 2a5 
// f(4) - f(3) - (a1 + a2 + a3 + a4 + a5) : 0 + 0 + 0 - 2a4 - 2a5
// f(5) - f(4) - (a1 + a2 + a3 + a4 + a5) : 0 + 0 + 0 + 0 - 2a5
void solve() { 
    ll n; cin >> n;
    vector<ll> v(n + 1);
    for(ll i = 1; i <= n; i++) cin >> v[i];

    ll sum = (v[1] + v[n])/(n - 1);
    vector<ll> a;
    for(ll i = 2; i <= n; i++){
        ll val = v[i] - v[i - 1] - sum;
        a.push_back(val);
    }
    // print(a);
    ll an = (-1 * a.back())/2LL;
    // debug(an);
    vector<ll> res;
    res.push_back(an);
    for(ll i = a.size() - 2; i >= 0; i--){
        ll ai = (a[i + 1] - a[i])/2LL;
        res.push_back(ai);
    }
    res.push_back((a[0] + 2*sum)/2LL);
    reverse(all(res));
    for(auto it : res) cout << it << " ";
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