//*****************************************************************************
// CPSC 3200          Professor: Howard Cheng
//                    Teaching Assistant: Darcy Best
// Written By: Camara Lerner
// Problem number: 5733 - Iterated Difference
// Description: I did Brute force
//*****************************************************************************
#include <iostream>
#include <cstdlib>
using namespace std;

int main() {

   int first[20];
   int next[20];
   int n;
   int cases = 1;
   while(cin >> n && n != 0) {
      int iterations = 0;
      for(int i = 0; i < n; ++i) {
	 cin >> first[i];
      }
      bool happy;
      for(int i = 0; i < 1000; ++i) {
	 int match = first[0];
	 happy = true;
	 for(int j = 1; j < n; ++j) {
	    happy = happy && (first[j] == match);
	 }
	 if(happy) {
	    break;
	 }
	 iterations++;
	 
	 for(int j = 0; j < n; ++j) {
	    next[j] = abs(first[j] - first[(j+1) % n]);
	 }
	 
	 for(int j = 0; j < n; ++j) {
	    first[j] = next[j];
	 }
      }
      cout << "Case " << cases++ << ": " ;
      if(happy) {
	 cout << iterations << " iterations" << endl;
      } else {
	 cout << "not attained" << endl;
      }
   }
   return 0;
}
