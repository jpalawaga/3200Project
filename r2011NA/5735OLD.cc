//*****************************************************************************
// CPSC 3200          Professor: Howard Cheng
//                    Teaching Assistant: Darcy Best
// Written By: Camara Lerner
// Problem number: 
// Description: 
//*****************************************************************************
#include <iostream>
#include <map>
#include <vector>
#include <algorithm>
using namespace std;

int main() {
   int n, cases = 1;
   multimap<int, int>::size_type k1, k2;
   while(cin >> n >> k1 >> k2 && !((n == 0) && (k1 == 0) && (k1 == 0))) {
      multimap<int, int> low;
      multimap<int, int, greater<int> > high;
      for(int i = 0; i < n; ++i) {
	 int next;
	 cin >> next;
	 // cout << next << " " << i << endl;
	 low.insert(make_pair(next, i + 1));
	 high.insert(make_pair(next, i + 1));
	 if(high.size() > k2) {
	    high.erase(--high.end());
	 }
	 if(low.size() > k1) {
	    low.erase(--low.end());
	 }
      }

      cout << "Case " << cases++ << endl;
      int low_ans[101];
      int i = 0;
      vector<int> out;
      for(multimap<int, int>::iterator it = low.begin(), it2 = it;
	  it != low.end(); it = it2)
      {
	 int q = 0;
	 for(; it2->first == it->first && it2 !=
		low.end(); ++it2) {
	    low_ans[q++] = it2->second;
	    i++;
	 }
	 sort(low_ans, low_ans + q);
	 for(int w = 0; w < q; w++) {
	    out.push_back(low_ans[w]);
	 }
      }
      
      for(int i = 0; i < out.size(); ++i) {
	 if(i != 0) {
	    cout << " ";
	 }
	 cout << out[i];
      }
      cout << endl;
      int high_ans[101];
      i = 0;
      vector<int> out2;
      for(multimap<int, int, greater<int> >::iterator it = high.begin(),
	     it2 = it;
	  it != high.end(); it = it2) {
	 int q = 0;
	 for( ; it2->first == it->first && it2 != high.end(); ++it2) {
	    high_ans[q++] = it2->second;
	    i++;
	 }
	 sort(high_ans, high_ans + q);
	 for(int w = 0; w < q; w++) {
	    out2.push_back(high_ans[w]);
	 }
	 
      }
      for(int i = 0; i < out2.size(); ++i) {
	 if(i != 0) {
	    cout << " ";
	 }
	 cout << out2[i];
      }
      cout << endl;
      
   }

   
   return 0;
}
