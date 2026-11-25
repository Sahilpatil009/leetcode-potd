class Solution {
public:
    int smallestUniqueSubarray(vector<int>& nums) {
        int n = nums.size();

        // Step 1: Construct suffix array
        vector<int> sa(n), rank(n), nextRank(n);

        iota(sa.begin(), sa.end(), 0);

        // Initially sort suffixes by their first element
        sort(sa.begin(), sa.end(), [&](int a, int b) {
            return nums[a] < nums[b];
        });

        // Assign initial ranks
        rank[sa[0]] = 0;

        for (int i = 1; i < n; i++) {
            rank[sa[i]] = rank[sa[i - 1]] +
                          (nums[sa[i]] != nums[sa[i - 1]]);
        }

        // Doubling technique to construct suffix array
        for (int k = 1; k < n; k *= 2) {

            sort(sa.begin(), sa.end(), [&](int a, int b) {
                if (rank[a] != rank[b]) {
                    return rank[a] < rank[b];
                }

                int ra = (a + k < n) ? rank[a + k] : -1;
                int rb = (b + k < n) ? rank[b + k] : -1;

                return ra < rb;
            });

            nextRank[sa[0]] = 0;

            for (int i = 1; i < n; i++) {
                int a = sa[i - 1];
                int b = sa[i];

                int a1 = rank[a];
                int b1 = rank[b];

                int a2 = (a + k < n) ? rank[a + k] : -1;
                int b2 = (b + k < n) ? rank[b + k] : -1;

                nextRank[b] = nextRank[a] +
                              (a1 != b1 || a2 != b2);
            }

            rank.swap(nextRank);

            if (rank[sa[n - 1]] == n - 1) {
                break;
            }
        }

        // Step 2: Calculate inverse suffix array
        vector<int> pos(n);

        for (int i = 0; i < n; i++) {
            pos[sa[i]] = i;
        }

        // Step 3: Construct LCP array using Kasai's algorithm
        // lcp[i] = LCP of sa[i] and sa[i - 1]

        vector<int> lcp(n, 0);

        int h = 0;

        for (int i = 0; i < n; i++) {
            int p = pos[i];

            if (p == 0) {
                h = 0;
                continue;
            }

            int j = sa[p - 1];

            while (i + h < n && j + h < n &&
                   nums[i + h] == nums[j + h]) {
                h++;
            }

            lcp[p] = h;

            if (h > 0) {
                h--;
            }
        }

        // Step 4: Find the minimum unique subarray length

        int ans = n;

        for (int p = 0; p < n; p++) {
            int start = sa[p];

            int left = lcp[p];

            int right = (p + 1 < n) ? lcp[p + 1] : 0;

            int maxLCP = max(left, right);

            int candidate = maxLCP + 1;

            if (candidate <= n - start) {
                ans = min(ans, candidate);
            }
        }

        return ans;
    }
};