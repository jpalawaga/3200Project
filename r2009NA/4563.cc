//*****************************************************************************
// CPSC 3200          Professor: Howard Cheng
//                    Teaching Assistant: Darcy Best
// Written By: Camara Lerner
// Problem number: 
// Description: 
//*****************************************************************************

#include <iostream>
#include <iomanip>
#include <string>
#include <stack>
using namespace std;

bool hexNum(const string &a, int &index) {
   string::size_type j = 0;
   for(string::size_type i = 0; i < a.size(); ) {
      if((a[i] >= '0' && a[i] <= '9') || (a[i] >= 'a' && a[i] <= 'f')
	 || (a[i] >= 'A' && a[i] <= 'F')) {
	 j = i;
	 ++i;
      } else {
	 break;
      }
   }
   if((j % 2 == 1) || (j == 0)) {
      return false;
   } else {
      index += j + 1;
      return true;
   }
}

bool handleand(const string &a, int &index) {
   if(a.empty()) return false;
   if(a.substr(0, 2) == "lt" || a.substr() == "gt") {
      index += 2;
      return true;
   } else if(a.substr(0,3) == "amp") {
      index += 3;
      return true;
   } else if(a[0] == 'x') {
      if(a.size() <= 1) return false;
      return hexNum(a.substr(1, a.size() - 1), index);
   } else {
      return false;
   }
}

bool handlelt(const string &a, int &index) {
   if(a.empty()) return false;
   
}

int main() {

   string line;
   while(getline(cin, line)) {


   }
   
   return 0;
}
