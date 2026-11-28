class Solution {
public:
    int maximumSaleItems(vector<vector<int>>& items, int budget) {
        int n = items.size();
        int maxFactor =0;
        int minPrice = INT_MAX;

        vector<int> freq(n + 1, 0);

        for(auto it : items) {
            int factor = it[0];
            int price = it[1];

            freq[factor]++;
            maxFactor = max(maxFactor, factor);
            minPrice = min(minPrice, price);
        }

        vector<int> cnt(maxFactor + 1, 0);

        for(int f = 1; f <= maxFactor; f++) {
            if(freq[f] == 0) continue;

            cnt[f] = freq[f];

            for(int j = 2 * f; j <= maxFactor; j += f) {
                cnt[f] += freq[j];
            }
        }

        vector<pair<int, long long>> offers;

        for(auto it : items) {
            int factor = it[0];
            int price = it[1];
            long long gain = cnt[factor] - 1;

            if(gain > 0 && price <= 2LL * minPrice) {
                offers.push_back({price, gain});
            }
        }

        sort(offers.begin(), offers.end());

        long long ans = 0;
        long long remaining = budget;

        for(auto [price, gain] : offers) {
            if(remaining < price) break;

            long long take = min(gain, remaining / price);

            ans += 2 * take;
            remaining -= take * price;
        }

        ans += remaining / minPrice;

        return (int)ans;
    }
};