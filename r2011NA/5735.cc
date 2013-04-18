//*****************************************************************************
// CPSC 3200          Professor: Howard Cheng
//                    Teaching Assistant: Darcy Best
// Written By: Camara Lerner
// Problem number: 5735 - Stock Prices
// Description: I first store the stock prices in a vector of pairs, which hold
// the stock price and then the day. After that I sort the vector then find
// and sort the first k1 days in ascending order and find and sort the last k2
// days in descending order
//*****************************************************************************
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

bool myGreater(const pair<int, int>& a, const pair<int, int>& b) {
   return a.first > b.first;
}

int main() {

   int cases = 1;
   int n, k1, k2;
   while(cin >> n >> k1 >> k2 && !( n == 0 && k1 == 0 && k2 == 0)) {
      vector<pair<int, int> > numbers;
      numbers.resize(n);
      for(int i = 1 ; i <= n; ++i) {
	 int next;
	 cin >> next;
	 numbers[i-1] = make_pair(next, i);
      }
      sort(numbers.begin(), numbers.end());
      vector<pair<int,int> > low, high;
      low.resize(k1);
      high.resize(k2);
 
      cout << "Case " << cases++ << endl;
      for(int i = 0; i < k1; ++i) {
	 low[i] = make_pair(numbers[i].second, numbers[i].first);
      }
      sort(low.begin(), low.end());
      for(int i = 0; i < k1; ++i) {
	 if(i != 0)
	    cout << " ";
	 cout<< low[i].first;
      }
      cout << endl;
      int index = 0;
      for(int i = (int)numbers.size() - 1; i >= (int)numbers.size() - k2; --i) {
	 high[index++] = make_pair(numbers[i].second, numbers[i].first);
      }
      sort(high.begin(), high.end(), myGreater);
      //   cout << "size: " << high.size() << " == " << k2 << endl;
      for(int i = 0; i < k2; ++i) {
	 if(i != 0)
	    cout << " ";
	 cout << high[i].first;
      }
      cout << endl;
   }

   
}
