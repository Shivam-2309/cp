// Author : Shivam Kapoor
#include <bits/stdc++.h>
using namespace std;
 
typedef long long ll;
typedef vector<ll> vll;
 
const ll mod7 = 1e9 + 7, mod9 = 998244353, INF = 1e18;
#define fast_io ios::sync_with_stdio(0); cin.tie(0); cout.tie(0);
#define all(v) (v).begin(), (v).end()
 
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
 
bool check(ll x, ll y, ll n){
    return (x >= 0 && x < n && y >= 0 && y < n);
}
 
void solve() { 
    ll n; cin >> n;
    vector<string> v(n);
    for(ll i = 0; i < n; i++) cin >> v[i];
 
    vector<vector<pair<ll, ll>>> par(n, vector<pair<ll, ll>> (n, {-1, -1}));
    vector<vector<ll>> vis(n, vector<ll> (n, 0));
    queue<pair<char, pair<ll, ll>>> q;
    q.push({v[0][0], {0, 0}});
 
    while(!q.empty()){
        ll cursz = q.size();
        vector<pair<char, pair<ll, ll>>> a;
        for(ll i = 0; i < cursz; i++){
            char ch = q.front().first;
            ll nx = q.front().second.first;
            ll ny = q.front().second.second;
 
            q.pop();
 
            ll nx1 = nx + 1, ny1 = ny;
            ll nx2 = nx, ny2 = ny + 1;
 
            if(check(nx1, ny1, n) && !vis[nx1][ny1]){
                vis[nx1][ny1] = 1;
                par[nx1][ny1] = {nx, ny};
                a.push_back({v[nx1][ny1], {nx1, ny1}});
            }
            if(check(nx2, ny2, n) && !vis[nx2][ny2]){
                vis[nx2][ny2] = 1;
                par[nx2][ny2] = {nx, ny};
                a.push_back({v[nx2][ny2], {nx2, ny2}});
            }
        }
 
        deque<pair<char, pair<ll, ll>>> dq;
        // debug(a.size());
        for(ll i = 0; i < a.size(); i++){
            while(!dq.empty() && dq.front().first > a[i].first) dq.pop_front();
            if(dq.empty() || dq.back().first == a[i].first) dq.push_back(a[i]);
        }
        // debug(dq.size());
        // for(auto it : dq){
        //     cout << it.first << " " << it.second.first << " " << it.second.second << endl;
        // }
        for(auto it : dq) q.push(it);
    }
 
    // for(ll i = 0; i < n; i++){
    //     for(ll j = 0; j < n; j++){
    //         cout << "parent of: { " << i << ", " << j << " } is : " << par[i][j].first << " " << par[i][j].second << endl; 
    //     }
    // }
 
    string ans = "";
    // ans.push_back(v[n - 1][n - 1]);
    pair<ll, ll> curr = { n-1, n-1 };
    while(curr.first != -1 && curr.second != -1){
        ans.push_back(v[curr.first][curr.second]);
        curr = par[curr.first][curr.second];
    }
    reverse(all(ans));
    // print(ans);
    cout << ans << endl;
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