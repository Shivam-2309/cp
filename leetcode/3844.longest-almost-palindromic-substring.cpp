/*
 * @lc app=leetcode id=3844 lang=cpp
 *
 * [3844] Longest Almost-Palindromic Substring
 */
#include<bits/stdc++.h>
// @lc code=start
#define ll long long
class Solution {
public:
    int almostPalindromic(string s) {
        ll n = s.length();
        ll mx = 2;
        
        // odd case
        for(ll curr = 0; curr < n; curr++){
            // ith pr middle h
            ll i = curr;
            ll j = curr;
            bool f = true;
            while(i >= 0 && j < n){
                if(s[i] == s[j]){
                    i--;
                    j++;
                }
                else if(f){
                    f = !f;
                    i--;
                    j++;
                }
                else{
                    mx = max(mx, j - i + 1);
                    break;
                }
            }
            i++;
            j--;
            mx = max(mx, j - i + 1);
        }

        cout << mx << endl;

        // even case
        for(ll curr = 0; curr < n - 1; curr++){
            bool f = true;
            if(s[curr] != s[curr + 1]) f = false;

            ll i = curr - 1;
            ll j = curr + 2;

            while(i >= 0 && j < n){
                if(s[i] == s[j]){
                    i--;
                    j++;
                }
                else if(f){
                    i--;
                    j++;
                    f = false;
                }
                else{
                    mx = max(mx, j - i + 1);
                    break;
                }
            }
            i++;
            j--;
            mx = max(mx, j - i + 1);
        }
        return mx;
    }
};
// @lc code=end

