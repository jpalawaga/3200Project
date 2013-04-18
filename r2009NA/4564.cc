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
      //cout << a.substr(start, len) << endl;
      //cout << "finished with " << (a[start] == a[start + 1]) << endl;
      return a[start] == a[start + 1];
   } else if(len == 3) {
      //cout << a.substr(start, len) << endl;
      //cout << "finished with "
      //<< (a[start] == a[start + 1] && a[start + 1] == a[start + 2])
      //<< endl;
      return (a[start] == a[start + 1]) && (a[start] == a[start + 2]);
   }
   if(a[start] == a[start + len - 1]) {
      // AxAyA
      int next = a.find(a[start], start + 1);
      while(next < start + len - 1) {
	 //cout << a.substr(start, len) << endl;
	 //cout << a.substr(start + 1, next - start - 1) << " "
	 //    << a.substr(next + 1, len - next - 2) << endl;
	 // cout << "AxAyA" << endl;
	 if(solvable(start + 1, next - start - 1)) {
	    if(solvable(next + 1, start + len - next - 2)) {

	       //    cout << "finish with true" << endl;
	       return (bool)(table[start][len] =
			     true);
	    }
	 }
	 next = a.find(a[start], next + 1);
	 //cout << "next: " <<  next << endl;
      }
      // AxA
      //cout << "AxA" << endl;
      if(solvable(start + 1, len - 2)) {
	 //cout << a.substr(start, len) << endl;
	 //cout << "finish with true" << endl;
	 return (bool)(table[start][len] =
		       true);
      }
   }

   // loop through this another way
   for(int i = 1; i < len; ++i) {
      // cout << "xy" << endl;
      if(solvable(start, i)) {
	 if(solvable(start + i, len - i)) {
	    //cout << a.substr(start, len) << endl;
	    //cout << "finish with true" << endl;
	    return (bool)(table[start][len] =
			  true);
	 }
      }
   }
   //cout << a.substr(start, len) << endl;
   //cout << "finish with false" << endl;
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
	 //cout << endl;
	 cout << "solvable" << endl;
	 //cout << endl;
      } else {
	 //cout << endl;
	 cout << "unsolvable" << endl;
	 //cout << endl;
      }
      a.clear();
   }
   return 0;
}
