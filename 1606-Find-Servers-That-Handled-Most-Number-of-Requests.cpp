class Solution {
public:
    vector<int> busiestServers(int k, vector<int>& arrival, vector<int>& load) {
        set<int> availables;

        for(int i=0; i<k; i++) {
            availables.insert(i);
        }

        priority_queue<
        pair<int, int>,
        vector<pair<int, int>>,
        greater<pair<int, int>>
        > pq;

        vector<int> cnt(k, 0);

        for(int i=0; i<arrival.size(); i++) {
            while(!pq.empty() && pq.top().first <= arrival[i]) {
                availables.insert(pq.top().second);
                pq.pop();
            }

            if(availables.empty()) continue;

            int preferred = i%k;
            auto it = availables.lower_bound(preferred);

            if(it == availables.end()) it = availables.begin();

            int server = *it;

            availables.erase(it);

            cnt[server]++;

            pq.push({arrival[i]+load[i], server});
        }

        int maxi = *max_element(cnt.begin(), cnt.end());

        vector<int> ans;


        for(int i=0; i<k; i++){
            if(cnt[i]==maxi) {
                ans.push_back(i);
            }
        }

        return ans;
    }
};