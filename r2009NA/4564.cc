//*****************************************************************************
// CPSC 3200          Professor: Howard Cheng
//                    Teaching Assistant: Darcy Best
// Written By: Camara Lerner
// Problem number: 
// Description: 
//*****************************************************************************
#include <iostream>
#include <string>
#include <map>
#include <utility>
using namespace std;

int table[151][151];
string a;

// x and y are solvable puzzles and A is a capital letter
bool solvable(const int &start, const int &len) {
   if(table[start][len] >= 0) {
      return (bool)table[start][len];
   }
   if(len == 0) {
      return true;
   } else if(len == 1) {
      return false;
   } else if(len == 2) {
      return a[start] == a[start + 1];
   } else if(len == 3) {
      return (a[start] == a[start + 1]) && (a[start] == a[start + 2]);
   }
   if(a[start] == a[start + len - 1]) {
      // AxAyA
      int next = a.find(a[start], start + 1);
      while(next < start + len - 1) {
	 if(solvable(start + 1, next - start - 1)) {
	    if(solvable(next + 1, start + len - next - 2)) {
	       return (bool)(table[start][len] =
			     true);
	    }
	 }
	 next = a.find(a[start], next + 1);
      }
      // AxA
      if(solvable(start + 1, len - 2)) {
	 return (bool)(table[start][len] =
		       true);
      }
   }

   // loop through this another way
   for(int i = 1; i < len; ++i) {
      if(solvable(start, i)) {
	 if(solvable(start + i, len - i)) {
	    return (bool)(table[start][len] =
			  true);
	 }
      }
   }
   return (bool)(table[start][len] = false);
}

int main() {

   while(cin >> a) {
      for(int i = 0; i < 151; ++i) {
	 for(int j = 0; j < 151; ++j) {
	    table[i][j] = -1;
	 }
      }
      if(solvable(0, a.length())) {
	 cout << "solvable" << endl;
      } else {
	 cout << "unsolvable" << endl;
      }
      a.clear();
   }
   return 0;
}
