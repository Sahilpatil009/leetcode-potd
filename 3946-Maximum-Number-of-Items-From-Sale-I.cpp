class Solution {
public:
    int maximumSaleItems(vector<vector<int>>& items, int budget) {
        int n = items.size();
        vector<int> freecopies(n, 0);

        for(int i=0; i<n; i++) {
            for(int j=0; j<n; j++) {
                if(i != j && items[j][0] % items[i][0] == 0) {
                    freecopies[i]++;
                }
            }
        }

        int NEG = -1e9;
        vector<int> dp(budget+1, NEG);
        dp[0]=0;

        for(int i=0; i<n; i++) {
            int price = items[i][1];
            int bonus = freecopies[i];

            vector<int> active(budget+1, NEG);
            for(int b=price; b<=budget; b++) {
                if(dp[b-price] != NEG) {
                    active[b] = dp[b-price]+1+bonus;
                }
            }

            for(int b=price; b<=budget; b++) {
                if(active[b-price] != NEG) {
                    active[b] = max(active[b], active[b-price] +1);
                }
            }
            for(int b=0; b<=budget; b++) {
                dp[b] = max(dp[b], active[b]);
            }
        }

        return *max_element(dp.begin(), dp.end());

    }
};