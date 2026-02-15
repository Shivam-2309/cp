#include<bits/stdc++.h>
using namespace std;
#define ll long long

// { -1, 1 } -> { 2 }
// { 0, 2} -> { 6, 9 }
bool check(vector<ll> &b, ll l, ll r){
    ll idx = lower_bound(b.begin(), b.end(), l) - b.begin();
    // cout << "l " << l << endl;
    // cout << "r " << r << endl;
    // cout << "idx " << idx << endl;
    if(idx == b.size()){
        return false;
    }
    if(r >= b[idx]) return true;
    return false;
}

int main(){
    ll t; cin >> t;
    while(t--){
        // so after i seconds i want to know how many robots are alive
        // logically -> logN mn find krna or something like that
        // 1 <= a.length() <= 2e5
        // 1 <= b.length() <= 2e5
        // 1 <= k <= 2e5
        // hr ek robot ke liye agr mn find krlu ki when would it die ? 
        // i think yeh ho skta h ? 
        // kyuki kisi bhi time ke baad it would be range of length <= 2e5 which if includes the spile it will die
        // and also afyter every other time ever after.
        // get that time
        // let say ki vo time aagya !!
        // ab ?
        // ab bs sort krke dekhlo ki ki jaise agr 5 to saare jo >= 5 h vo bch jaege and yes bingo hojaega question

        // question -> kisi bhi x time pr mera robot mara ya nhi yeh kaise find kru ? 
        // BS -> Goto approach -> but how ?
        // agr mn meri string se precompute krlu range ko kyuki vo hmesha bdhegi hi right
        // to bs check krna hoga ki iss range mn koi h ya nhi aur hojaega

        ll n, m, k; cin >> n >> m >> k;
        vector<ll> a(n);
        vector<ll> b(m);
        for(ll i = 0; i < n; i++) cin >> a[i];
        for(ll i = 0; i < m; i++) cin >> b[i];
        sort(b.begin(), b.end());
        string s; cin >> s;
        // cout << "B is : ";
        // for(auto it : b) cout << it << " ";
        // cout << endl;

        vector<pair<ll, ll>> time(k + 1, {0, 0});
        ll l = 0;
        ll lmx = l, rmx = l;
        for(ll i = 0; i < s.length(); i++){
            // after (i + 1)th second
            if(s[i] == 'L') l--;
            if(s[i] == 'R') l++;

            lmx = min(lmx, l);
            rmx = max(rmx, l);
            time[i] = {lmx, rmx};

            // cout << i << "th second ke baad : " << lmx << " " << rmx << endl;
        }

        vector<ll> t(n, -1);
        for(ll i = 0; i < n; i++){
            // kahan h ? 
            ll point = a[i];
            // kb mrega ?
            ll lo = 0;
            ll hi = k - 1;
            ll ans = -1;

            while(lo <= hi){
                ll mid = (lo + hi)/2LL;
                // itnse seconds baad kya mara ?
                pair<ll, ll> range = time[mid];
                ll lefty = point - abs(range.first);
                ll righty = point + range.second;

                // cout << "lefty : " << lefty << endl;
                // cout << "righty : " << righty << endl;
                // cout << "mid : " << mid << endl;

                // kya b mn left se lekr right tk mn koi nuumber h ?
                if(check(b, lefty, righty)){
                    ans = mid;
                    hi = mid - 1;
                }
                else{
                    lo = mid + 1;
                }
            }
            // cout << i << "th robot kb mrega: " << ans << endl; 
            if(ans == -1) t[i] = 1e18;
            else t[i] = ans + 1;
        }
        vector<ll> ans(k + 1, 0);

        for(ll i = 0; i < t.size(); i++){
            if(t[i] != 1e18){
                if(t[i] <= k) ans[t[i]]--;
            }
        }
        // cout << "ANS: ";
        // for(auto it : ans) cout << it << " ";
        // cout << endl;
        ll curr = n;
        for(ll i = 1; i <= k; i++){
            curr += ans[i];
            cout << curr << " ";
        }cout << endl;
    }

    return 0;
}