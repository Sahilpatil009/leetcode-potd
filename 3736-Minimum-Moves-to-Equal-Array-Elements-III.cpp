class Solution {
public:
    int minMoves(vector<int>& nums) {
        int cnt =0;
        int maxNum = INT_MIN;

        for(int i=0; i<nums.size(); i++) {
            maxNum = max(maxNum, nums[i]);    
        }

        for(int i=0; i<nums.size(); i++) {
            cnt += (maxNum - nums[i]);
        }

        return cnt;
    }
};