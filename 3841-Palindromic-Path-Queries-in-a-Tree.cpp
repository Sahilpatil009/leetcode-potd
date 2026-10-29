class Solution {
    int n;
    vector<int> tag;
    vector<vector<int>> up;
    vector<int> depth, start, size, letter;

    void update(int node, int lo, int hi, int l, int r, int delta) {
        if(r < lo || hi < l) return;

        if(l <= lo && hi <= r) {
            tag[node] ^= delta;
            return;
        }

        int mid = (lo + hi) / 2;
        update(2 * node, lo, mid, l, r, delta);
        update(2 * node + 1, mid + 1, hi, l, r, delta);
    }

    int pointValue(int node, int lo, int hi, int pos) {
        if(lo == hi) return tag[node];

        int mid = (lo + hi) / 2;

        if(pos <= mid)
            return tag[node] ^ pointValue(2 * node, lo, mid, pos);

        return tag[node] ^  pointValue(2 * node + 1, mid + 1, hi, pos);
    }

    void flipSubtree(int v, int delta) {
        update(1, 0, n - 1, start[v],
               start[v] + size[v] - 1, delta);
    }

    int rootMask(int v) {
        return pointValue(1, 0, n - 1, start[v]);
    }

    int lca(int u, int v) {
        if(depth[u] < depth[v]) swap(u, v);

        int diff = depth[u] - depth[v];

        for(int k = 16; k >= 0; k--) {
            if ((diff >> k) & 1) {
                u = up[k][u];
            }
        }

        if(u == v) return u;


        for(int k = 16; k >= 0; k--) {
            if(up[k][u] != up[k][v]) {
                u = up[k][u];
                v = up[k][v];
            }
        }

        return up[0][u];
    }

public:
    vector<bool> palindromePath(
        int n,
        vector<vector<int>>& edges,
        string s,
        vector<string>& queries
    ) {
        this->n = n;

        vector<vector<int>> adj(n);

        for(auto& e : edges) {
            int u = e[0], v = e[1];
            adj[u].push_back(v);
            adj[v].push_back(u);
        }

        vector<int> parent(n, 0), order;
        depth.assign(n, 0);

        vector<int> st = {0};

        while(!st.empty()) {
            int v = st.back();
            st.pop_back();
            order.push_back(v);

            for(int w : adj[v]) {
                if(w == parent[v]) continue;

                parent[w] = v;
                depth[w] = depth[v] + 1;
                st.push_back(w);
            }
        }

        start.assign(n, 0);
        size.assign(n, 1);

        for(int i = 0; i < n; i++) {
            start[order[i]] = i;
        }

        for(int i = n - 1; i > 0; i--) {
            size[parent[order[i]]] += size[order[i]];
        }

        up.assign(17, vector<int>(n, 0));

        for(int v = 1; v < n; v++) {
            up[0][v] = parent[v];
        }

        for(int k = 1; k < 17; k++) {
            for(int v = 0; v < n; v++) {
                up[k][v] = up[k - 1][up[k - 1][v]];
            }
        }

        tag.assign(4 * n, 0);
        letter.assign(n, 0);

        for(int v = 0; v < n; v++) {
            letter[v] = 1 << (s[v] - 'a');
            flipSubtree(v, letter[v]);
        }

        vector<bool> answer;

        for(string& q : queries) {
            stringstream in(q);
            string type;
            in >> type;

            if(type == "update") {
                int u;
                char c;
                in >> u >> c;

                int newLetter = 1 << (c - 'a');

                flipSubtree(u, letter[u] ^ newLetter);
                letter[u] = newLetter;
                continue;
            }

            int u, v;

            in >> u >> v;

            int ancestor = lca(u, v);

            int mask = rootMask(u) ^ rootMask(v) ^ letter[ancestor];

            int oddLetters = __builtin_popcount((unsigned int)mask);

            answer.push_back(oddLetters <= 1);
        }

        return answer;
    }
};