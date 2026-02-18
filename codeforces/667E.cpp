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

class SegmentTree {
    int n;
    vector<ll> tree;

public:
    SegmentTree(const vector<ll>& data) {
        n = data.size();
        tree.resize(4 * n);
        build(data, 1, 0, n - 1);
    }

    void build(const vector<ll>& data, int node, int start, int end) {
        if (start == end) {
            tree[node] = data[start];
            return;
        }
        int mid = (start + end) / 2;
        build(data, 2 * node, start, mid);
        build(data, 2 * node + 1, mid + 1, end);
        tree[node] = max(tree[2 * node], tree[2 * node + 1]);
    }

    ll query(int node, int start, int end, int l, int r) {
        if (r < start || end < l) return 0;
        if (l <= start && end <= r) return tree[node];
        int mid = (start + end) / 2;
        return max(query(2 * node, start, mid, l, r),
                   query(2 * node + 1, mid + 1, end, l, r));
    }

    ll query(int l, int r) {
        if (l > r) return 0;
        return query(1, 0, n - 1, l, r);
    }
};

void solve() { 
    ll n, k; cin >> n >> k;
    vector<ll> x(n), y(n);
    for(ll i = 0; i < n; i++) cin >> x[i];
    for(ll i = 0; i < n; i++) cin >> y[i];

    // claim 1 -> platform must touch an x-coordinate for sure
    // claim 2 -> best answer can only be generated if -> 
    //          1) both the platforms are connected edge to edge
    //          2) both are connected separately
    sort(x.begin(), x.end());

    // case 1 handled
    ll ans = 1;
    for(ll i = 0; i < n; i++){
        ll curr = x[i];
        // isse equal ya bde aur x + k <= kitne h ?
        ll idx = upper_bound(x.begin(), x.end(), curr + 2*k) - x.begin();
        idx--;
        ll kitne = (idx - i + 1);
        ans = max(ans, kitne);
    }
    // case 2 handled
    vector<ll> dp(n, 1);
    for(ll i = 0; i < n; i++){
        ll curr = x[i];
        // isse equal ya bde aur x + k <= kitne h ?
        ll idx = upper_bound(x.begin(), x.end(), curr + k) - x.begin();
        idx--;
        ll kitne = (idx - i + 1);
        dp[i] = kitne;
    }

    SegmentTree seg(dp);
    for(ll i = 0; i < n; i++){
        ll curr = x[i];
        // isse equal ya bde aur x + k <= kitne h ?
        ll idx = upper_bound(x.begin(), x.end(), curr + k) - x.begin();
        // id out of bound then return 0;
        ll mx = seg.query(idx, n - 1);
        ans = max(ans, dp[i] + mx);
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