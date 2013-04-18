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
using namespace std;

// x and y are solvable puzzles and A is a capital letter
bool solvable(const string &a, const int &start, const int &len,
	      map<string, bool> &table) {
   map<string, bool>::iterator it = table.find(a);
   if(it != table.end()) {
      return it->second;
   }
   if(len == 0) {
      return true;
   } else if(len == 1) {
      return false;
   }

   bool cases = false;
   // AxA
   if(a[start] == a[start + len]) {
      string::size_type next = a.find(a[start], start);
      // AxAyA
      if(next < start + len) {
	 cases |= solvable(a, start + 1, next - start - 2, table)
	    && solvable(a, next + 1, len - next - 2, table);
	 if(cases) {
	    return table[a] = true;
	 }
      }
      // AxA
      else {
	 cases |= solvable(a, start + 1, len - 2, table);
      }
      if(cases) {
	 return table[a] = true;
      }
   }
   
   for(int i = 1; i < len; ++i) {
      cout << a.substr(start, i) << " " << a.substr(start + i, len - i) << endl;
      cases |= (solvable(a, start, i, table)
		&& solvable(a, start + i, len - i, table));
      cout << boolalpha << cases << endl;
      if(cases) {
	 break;
      }
   }
   return table[a] = cases;
}

int main() {

   string str;
   while(cin >> str) {
      map<string, bool> table;
      if(solvable(str, 0, str.length(), table)) {
	 cout << "solvable" << endl;
      } else {
	 cout << "unsolvable" << endl;
      }
   }
   return 0;
}
