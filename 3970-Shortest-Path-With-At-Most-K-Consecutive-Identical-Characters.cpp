class Solution {
public:
    int shortestPath(int n, vector<vector<int>>& edges, string labels, int k) {
        vector<vector<pair<int, int>>> adj(n);

        for(auto it : edges) {
            int u = it[0];
            int v = it[1];
            int w = it[2];

            adj[u].push_back({v, w});
        }
        vector<vector<int>> res(n, vector<int>(k+1, INT_MAX));
        priority_queue<
        tuple<int, int, int>,
        vector<tuple<int, int, int>>,
        greater<tuple<int, int, int>>>pq;

        pq.push({0, 0, 1});

        while(!pq.empty()) {
            auto [d, node, cnt] = pq.top();
            pq.pop();

            if(res[node][cnt] <d) {
                continue;
            }

            if(node==n-1) {
                return d;
            }

            for(auto &vec: adj[node]) {
                int adjNode = vec.first;
                int wt = vec.second;

                int newCnt = (labels[adjNode] == labels[node]) ? cnt+1: 1;

                if(newCnt>k) {
                    continue;
                }

                int newDist = d+wt;

                if(newDist < res[adjNode][newCnt]) {
                    res[adjNode][newCnt] = newDist;
                    pq.push({newDist, adjNode, newCnt});
                }
            }
        }

        return -1;
    }
};