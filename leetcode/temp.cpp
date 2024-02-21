#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    int getMaxLen(vector<int>& nums) {
        int n = nums.size();
        vector<vector<int>>dp(n + 2, vector<int>(2, 0));
        if(nums[0] == 0){
            
        }
        else if(nums[0] > 0)
        {
            dp[0][1] = 1;
        }
        else
        {
            dp[0][0] = 1;
        }

        int ans = 0;
        for(int i = 1; i < n; i++){
            if(nums[i] == 0){
                ans = max(ans, (dp[i-1][1]));
            }
            else if(nums[i] > 0){
                dp[i][1] = max(dp[i][1], dp[i - 1][1] + 1);
                dp[i][0] = max(dp[i][0], dp[i - 1][0]);
            }
            else
            {
                dp[i][1] = max(dp[i][1], dp[i - 1][0] + 1);
                dp[i][0] = max(dp[i][0], dp[i - 1][1] + 1);
            }
            ans = max(ans, dp[i][1]);
        }
        for(int i = 0; i < n; i++){
            for(int j = 0; j < 2; j++){
                cout<<dp[i][j]<<" ";
            }
            cout<<endl;
        }
        cout<<ans<<endl;
        return ans;
    }
};

int main()
{
    Solution s;
    vector<int>v = {0,1,-2,-3,-4};
    s.getMaxLen(v);
}