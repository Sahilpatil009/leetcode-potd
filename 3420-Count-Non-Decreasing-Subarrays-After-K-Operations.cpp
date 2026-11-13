
class Solution {
public:
    long long countNonDecreasingSubarrays(vector<int>& nums, int k) {
        int n = nums.size();

        deque<pair<int, int>> dq;

        long long operations = 0;
        long long ans = 0;

        int j = n - 1;

        for(int i = n-1; i>=0; i--) {
            int cnt = 1;

            while(!dq.empty() && dq.back().first < nums[i]) {
                auto [val, count] = dq.back();
                dq.pop_back();

                operations += 1LL * (nums[i] - val) * count;
                cnt += count;
            }

            dq.push_back({nums[i], cnt});

            while(operations > k) {
                operations -= dq.front().first - nums[j];

                if(dq.front().second > 1) {
                    dq.front().second--;
                }else {
                    dq.pop_front();
                }

                j--;
            }

            ans += j-i+1;
        }

        return ans;
    }
};
