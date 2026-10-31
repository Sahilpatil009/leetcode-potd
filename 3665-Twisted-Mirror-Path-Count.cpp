class Solution {
public:
    const int MOD = 1e9+7;
    int m , n;
    vector<vector<vector<int>>> dp;
    
    int solve(int i, int j, int dir, vector<vector<int>>& grid) {
        if(i>=m || j>=n) {
            return 0;
        }

        if(i==m-1 && j==n-1) {
            return 1;
        }

        int &ans = dp[i][j][dir];

        if(ans != -1) {
            return ans;
        }

        if(grid[i][j] == 1) {
            if(dir == 0) {
                return ans = solve(i+1, j, 1, grid);
            } else {
                return ans = solve(i, j+1, 0, grid);
            }
        }

        long long right = solve(i, j+1, 0, grid);
        long long down = solve(i+1, j, 1, grid);

        return ans = (right+down) % MOD;
    }
    int uniquePaths(vector<vector<int>>& grid) {
        m = grid.size();
        n = grid[0].size();

        dp.assign(m, vector<vector<int>>(n, vector<int>(2,-1)));

        long long right = solve(0, 1, 0, grid);
        long long down = solve(1, 0, 1, grid);

        return (right+down)%MOD;
        
    }
};
// directions right and down
// if right == 1 then down
// if down == 1 then right
// out of boundry doesnt exits
// return number of unique paths from 0, 0 to (m-1, n-1);