
class Solution {
public:
    int maxLength(vector<int>& nums) {
        int n = nums.size();
        int ans = 2; // Any subarray of length 2 is valid.

        for (int i = 0; i < n; i++) {
            long long prod = nums[i];
            long long g = nums[i];
            long long l = nums[i];

            for (int j = i + 1; j < n; j++) {
                long long x = nums[j];

                // Update product, GCD and LCM
                prod *= x;
                g = gcd(g, x);
                l = l / gcd(l, x) * x;

                // Check product equivalence
                if (prod == g * l) {
                    ans = max(ans, j - i + 1);
                } 
                else {
                    // It cannot become valid again
                    break;
                }
            }
        }

        return ans;
    }
};
