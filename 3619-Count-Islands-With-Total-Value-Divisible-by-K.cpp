class Solution {
public:
    vector<int> dr = {-1, 0, 1, 0};
    vector<int> dc = {0, 1, 0, -1};

    int countIslands(vector<vector<int>>& grid, int k) {
        int m = grid.size();
        int n = grid[0].size();

        vector<vector<int>> vis(m, vector<int>(n,0));
        queue<pair<int, int>> q;

        int cnt=0;

        for(int i=0; i<m; i++) {
            for(int j=0; j<n; j++) {
                if(grid[i][j] > 0 && !vis[i][j]) {
                    long long sum = 0;
                    
                    vis[i][j]=1;
                    q.push({i, j});
                    sum += grid[i][j];

                    while(!q.empty()) {
                        auto [r, c] = q.front();
                        q.pop();

                        for(int k=0; k<4; k++) {
                            int nr = r + dr[k];
                            int nc = c + dc[k];

                            if(nr>=0 && nc >=0 && nr<m && nc<n && grid[nr][nc] > 0 && !vis[nr][nc]) {
                                vis[nr][nc]=1;
                                q.push({nr, nc});
                                sum += grid[nr][nc];
                            }
                        }
                    }

                    if(sum%k == 0) {
                        cnt++;
                    }
                }
            }
        }

        return cnt;
    }
};