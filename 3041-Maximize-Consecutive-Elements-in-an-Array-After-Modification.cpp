class Solution {
public:
    int maxSelectedElements(vector<int>& nums) {
        int n = nums.size();

        sort(nums.begin(), nums.end());

        int maxi = *max_element(nums.begin(), nums.end());

        vector<int> dp(maxi+2, 0);

        int ans = 0;

        for(int num: nums) {
            int prev = dp[num];
            // 1
            dp[num] = max(dp[num], dp[num-1]+1);
            // 2
            dp[num+1] = max(dp[num+1], prev+1);

            ans = max({ans, dp[num], dp[num+1]});
        }     

        return ans;
    }
};