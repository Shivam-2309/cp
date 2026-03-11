#include<bits/stdc++.h>
using namespace std;
#define ll long long
#define rev(v) reverse(v.begin(), v.end())
#define srt(v) sort(v.begin(), v.end())
#define endl '\n'
const ll mod7 = 1e9 + 7;
const ll mod9 = 998244353;
ll power(ll a, ll b)
{
    ll res = 1;
    while (b > 0)
    {
        if (b & 1)
            res = (res * a);
        a = (a * a);
        b >>= 1;
    }
    return res;
}
const int NUM = 2e5 + 7;
const ll INF = 1e18 + 5;
void sieveOfEratosthenes() {
    bool sieve[NUM];
    memset(sieve, true, sizeof(sieve));
    sieve[1] = false;
    sieve[0] = false; 
    for (ll p = 2; p * p <= NUM; p++) {
        if (sieve[p]) {
            for (ll i = p * p; i <= NUM; i += p)
                sieve[i] = false;
        }
    }
}
 
void solve(){
    int n, sum;
    cin >> n >> sum;
 
    vector<int> v(n);
    for(int i=0; i<n; i++) cin >> v[i];
 
    vector<int> dp(1000001, 1e9);
    dp[0] = 0;
    for(int i=1; i<=sum; i++){
        for(int j=0; j<n; j++){
            if(i - v[j] >= 0){
                dp[i] = min(dp[i], 1 + dp[i - v[j]]);
            }
        }
    }
 
    if(dp[sum] == 1e9){
        cout << -1 << endl;
    }
    else{
        cout << dp[sum] << endl;
    }
}
 
int main(){
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    // sieveOfEratosthenes()
    // memset(dp, -1, sizeof(dp));
    ll t = 1;
    // cin >> t;
    while (t--)
    {
        solve();
    }
    return 0;
}
