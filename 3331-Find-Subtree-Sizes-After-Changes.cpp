class Solution {
public:
    vector<vector<int>> adj, updated;
    vector<int> ans, last;
    
    void dfs1(int u, string &s, vector<int> &newParent) {
        int c = s[u]-'a';

        int prev = last[c];

        if(prev != -1) {
            newParent[u] = prev;
        }

        last[c] = u;

        for(int v: adj[u]) {
            dfs1(v, s, newParent);
        }

        last[c] = prev;
    }

    int dfs2(int u) {
        int size = 1;

        for(int v: updated[u]) {
            size += dfs2(v);
        }

        return ans[u] = size;
    }

    vector<int> findSubtreeSizes(vector<int>& parent, string s) {
        int n = parent.size();

        adj.resize(n);
        updated.resize(n);
        ans.resize(n);
        last.assign(26, -1);

        for(int i=1; i<n; i++) {
            adj[parent[i]].push_back(i); 
        }

        vector<int> newParent = parent;

        dfs1(0, s, newParent);

        for(int i=1; i<n; i++) {
            updated[newParent[i]].push_back(i);
        }

        dfs2(0);

        return ans;
    }
};