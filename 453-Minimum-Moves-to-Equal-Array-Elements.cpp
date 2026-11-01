class Solution {
public:
    int minMoves(vector<int>& nums) {

        int n = nums.size();
        long long mini = *min_element(nums.begin(), nums.end());

        long long sum = accumulate(nums.begin(), nums.end(), 0LL);

        return sum - mini*n;
    }
};
        // return minimum number of moves required to make array equal
        // in one move , you can increament n-1 elements of the arr by 1;