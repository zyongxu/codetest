#include <iostream>
#include <vector>

using namespace std;

int maxProfit(vector<int> &prices) {
  vector<int> firstdeal;
  firstdeal.push_back(0);
  int len = prices.size();
  if (len<2)
    return 0;
  int tempmin=prices[0];
  int tempmax=prices[len-1];
  int maxp = 0;
  
  for (int i=1; i<len; i++) {
    if (prices[i] - tempmin > firstdeal[i-1]) {
      firstdeal.push_back(prices[i]-tempmin);
      maxp = prices[i]-tempmin;
    } else
      firstdeal.push_back(firstdeal[i-1]);
        
    if (prices[i]<tempmin)
      tempmin = prices[i];
  }
  
  for (int i=len-2; i>=1; i--) {
    if(firstdeal[i-1] + tempmax - prices[i] > maxp)
      maxp = firstdeal[i-1]+tempmax-prices[i];
    if (prices[i] > tempmax)
      tempmax = prices[i];
  }
  return maxp;
}    

int main () {
  vector<int> test;
  test.push_back(1);
  test.push_back(2);
  test.push_back(4);

  cout << maxProfit(test);
  return 0;
}
