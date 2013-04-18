//*****************************************************************************
// CPSC 3200          Professor: Howard Cheng
//                    Teaching Assistant: Darcy Best
// Written By: Camara Lerner
// Problem number: 5737 - Pills
// Description: store a string where w represents a whole pill and h represents
// a half pill and they are stored so that the whole pills are stored at the
// front and the half pills are stored at the end
//*****************************************************************************
#include <iostream>
using namespace std;

long long ans[31][31];

long long navigate(int whole, int half) {

   if(ans[whole][half] != 0) {
      return ans[whole][half];
   }
   if(whole == 0) {
      return 1;
   }
   
   if(half == 0) {
      return ans[whole][half] = navigate(whole - 1, 1);
   } else {
      return ans[whole][half] = navigate(whole - 1, half + 1)
	 + navigate(whole, half - 1);
   }
  
}

int main() {

   
   int n;
   while(cin >> n && n != 0) {
      cout << navigate(n, 0) << endl;
   }
   
   return 0;
}
