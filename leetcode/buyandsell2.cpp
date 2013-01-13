class Solution {
public:
  int maxProfit(vector<int> &prices) {
    int len = prices.size();
    if (len < 2)
      return 0;

    int maxp = 0;
    int curbuy = -1;
    for (int i=0; i<len-1; i++) {
      if (curbuy > -1) {
        // holding stock for sale
        if (prices[i] > prices[i+1]) {
          maxp += prices[i] - prices[curbuy];
          curbuy=-1;
        }
      } else {
        // looking for stock to buy
        if (prices[i] < prices[i+1]) 
          curbuy = i;
      }
    }
    
    if (curbuy > -1 && prices[len-1] > prices[curbuy])
      maxp += prices[len-1] - prices[curbuy];
    return maxp;
  }
};
