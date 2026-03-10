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

bool check(pair<ll, ll> &s, ll left, ll right){
    if((s.first <= left) && (left <= right) && (right <= s.second)) return true;
    return false;
}

void solve() { 
    ll n; cin >> n;
    vector<ll> p1(n + 1), p2(n + 1);
    for(ll i = 1; i <= n; i++) cin >> p1[i];
    for(ll i = 1; i <= n; i++) cin >> p2[i];

    map<ll, ll> mp1, mp2;
    for(ll i = 1; i <= n; i++){
        mp1[p1[i]] = i;
        mp2[p2[i]] = i;
    }

    ll ans = 0;
    ll curlo = mp1[1];
    ll curhi = mp2[1];
    ll mn = min(mp1[1], mp2[1]);
    ll mx = max(mp1[1], mp2[1]);

    ll len1 = (mn - 1);
    ll len2 = (mx - mn - 1);
    ll len3 = (n - mx);

    ans += ((len1) * (len1 + 1))/2LL;
    ans += ((len2) * (len2 + 1))/2LL;
    ans += ((len3) * (len3 + 1))/2LL;
    // debug(ans);
    curlo = mn;
    curhi = mx;

    for(ll i = 2; i <= n; i++){
        ll mex = i;
        // debug("NAYA");
        // debug(mex);

        ll pos1 = mp1[i];
        ll pos2 = mp2[i];
        ll left = min(pos1, pos2);
        ll right = max(pos1, pos2);

        pair<ll, ll> s1 = {1LL, left - 1};
        pair<ll, ll> s2 = {left + 1, right - 1};
        pair<ll, ll> s3 = {right + 1, n};

        // debug(curlo);
        // debug(curhi);

        // ab curlo se curhi tk to pkka lena hi lena h
        // check krna h ki kya curlo aur curhi kisi s1, s2, s3 ke andr pura ka pura aa rha h ya nhi
        if(check(s1, curlo, curhi)){
            // debug("IDHR1");
            ll l = s1.first;
            ll r = s1.second;

            ll l1 = (curlo - l + 1);
            ll l2 = (r - curhi + 1);

            ll val = l1 * l2;
            // debug(val);
            ans += (l1 * l2);
        }
        if(check(s2, curlo, curhi)){
            // debug("IDHR2");
            ll l = s2.first;
            ll r = s2.second;

            ll l1 = (curlo - l + 1);
            ll l2 = (r - curhi + 1);

            ll val = l1 * l2;
            // debug(val);
            ans += (l1 * l2);
        }
        if(check(s3, curlo, curhi)){
            // debug("IDHR3");
            ll l = s3.first;
            ll r = s3.second;
            // debug(l);
            // debug(r);

            ll l1 = (curlo - l + 1);
            ll l2 = (r - curhi + 1);

            ll val = l1 * l2;
            // debug(val);
            ans += (l1 * l2);
        }

        curlo = min(curlo, left);
        curhi = max(curhi, right);
    }

    cout << ans + 1 << endl;
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
