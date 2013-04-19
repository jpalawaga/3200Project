//*****************************************************************************
// CPSC 3200          Professor: Howard Cheng
//                    Teaching Assistant: Darcy Best
// Written By: Camara Lerner
// Problem number: 4564 - Clickomania
// Description: I use the rules they give us and I store the results of already
// computed strings in an array
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
      return true; // (bool)(table[start][len] = 1);
   } else if(len == 1) {
      return false; //(bool)(table[start][len] = 0);
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
   for(int i = 1; i < len - 1; ++i) {
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
      for(int i = 0; i < 151; ++i) {
	 table[i][0] = true;
	 table[i][1] = false;
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
