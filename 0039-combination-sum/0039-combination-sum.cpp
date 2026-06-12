class Solution {
public:
    vector<vector<int>> combinationSum(vector<int>& candidates, int target) {
        vector<vector<int>> ans;
        helper(candidates, {},0, target, ans);
        return ans;
    }
    void helper(vector<int>& cand, vector<int> curr, int i, int target,
                vector<vector<int>>& ans) {
        if (i == cand.size()) {
            if (target == 0) {
                ans.push_back(curr);
            }
                return;
        }
        if (cand[i] <= target) {
            curr.push_back(cand[i]);
            helper(cand, curr, i, target - cand[i], ans);
            curr.pop_back();
        }

        helper(cand, curr, i + 1, target, ans);
    }
};