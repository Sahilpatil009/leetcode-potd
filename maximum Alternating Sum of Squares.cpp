// 3727. Maximum Alternating Sum of Squares

#include<bits/stdc++.h>
using namespace std;

class Solution {
public:
    long long maxAlternatingSum(vector<int>& nums) {
        long long ans=0;
        vector<long long> sq;

        for(int num : nums) {
            sq.push_back(1LL*num*num);
        }

        sort(sq.begin(), sq.end());
        int n = sq.size();

        for(int i=0;i<n/2; i++) {
            ans += sq[n-1-i]-sq[i];
        }

        if(n%2 == 1) {
            ans += sq[n/2];
        }

        return ans;
    }
};