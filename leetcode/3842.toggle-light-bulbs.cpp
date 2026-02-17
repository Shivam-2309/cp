/*
 * @lc app=leetcode id=3842 lang=cpp
 *
 * [3842] Toggle Light Bulbs
 */
#include<bits/stdc++.h>
#define ll long long
// @lc code=start
class Solution {
public:
    vector<int> toggleLightBulbs(vector<int>& bulbs) {
        set<int> st;
        for(int i = 1; i <= 100; i++) st.insert(i);

        for(auto it : bulbs){
            if(st.find(it) != st.end()) st.erase(it);
            else st.insert(it);
        }
        vector<int> res;
        for(int i = 1; i <= 100; i++){
            if(st.find(i) != st.end()) continue;
            res.push_back(i);
        }
        return res;
    }
};
// @lc code=end

