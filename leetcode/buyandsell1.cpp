/*
 * Say you have an array for which the ith element is 
 * the price of a given stock on day i.
 * 
 * If you were only permitted to complete at most one transaction (ie, buy one 
 * and sell one share of the stock), design an algorithm to find the maximum
 * profit.
 */

class Solution {
public:
  int maxProfit(vector<int> &prices) {
    int min_idx = 0;
    int maxp = 0;
    int len = prices.size();
    
    for (int i=1; i<len; i++) {
      if (prices[i]<prices[min_idx])
        min_idx = i;
      else {
        int prof = prices[i]-prices[min_idx];
        if (prof > maxp)
          maxp = prof;
      }
    }
    return maxp;
  }
};
