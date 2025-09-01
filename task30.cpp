#include <vector>

class Solution {
public:
    int maxProfit(std::vector<int>& prices) {
        int money = 0;
        
        for (int i = 1; i < prices.size(); i++) {
            if (prices[i] > prices[i-1]) {
                money += prices[i] - prices[i-1];
            }
        }   

        return money;
    }
};
