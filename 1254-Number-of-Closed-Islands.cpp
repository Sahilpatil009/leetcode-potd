class Solution {
public:
    vector<int> dr = {-1, 0, 1, 0};
    vector<int> dc = {0, 1, 0, -1};

    int closedIsland(vector<vector<int>>& grid) {
        // 2d grid with 0s and 1s
        // 4 directions allowed
        // connected group of 0s island
        // 1 water
        // return number of closed islands

        int m = grid.size();
        int n = grid[0].size();

        vector<vector<int>> vis(m, vector<int>(n,0));

        queue<pair<int, int>> q;
        int cnt=0;

        for(int i=0; i<m; i++) {
            for(int j=0; j<n; j++) {
                if(grid[i][j]==0 && !vis[i][j]) {
                    bool isClosed=true;

                    vis[i][j]=1;
                    q.push({i, j});

                    while(!q.empty()) {
                        auto [r, c] = q.front();
                        q.pop();

                        if(r==0 | c== 0 || r==m-1 || c==n-1) {
                            isClosed = false;
                        }

                        for(int k=0; k<4; k++) {
                            int nr = r+dr[k];
                            int nc = c+dc[k];

                            if(nr>=0 && nc>=0 && nr<m && nc<n && grid[nr][nc]==0 && !vis[nr][nc]) {
                                vis[nr][nc]=1;
                                q.push({nr, nc});
                            }
                        }
                    }

                    if(isClosed) {
                        cnt++;
                    }
                }
            }
        }

        return cnt;
    }
};