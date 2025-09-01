#include <algorithm>
#include <vector>

class Solution {
public:
    bool canJump(std::vector<int>& nums) {
        int max;
        for (int i; i < nums.size(); i++) {
            if (i > max) {
                return false;
            }

            max = std::max(max, i + nums[i]);
        }

        return true;
    }
};
