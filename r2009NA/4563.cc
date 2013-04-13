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
#include <cstdio>
using namespace std;

/****
     a should only be everything after the x
****/
bool hexNum(const string &a, string::size_type &index) {
   //cout << a << endl;
   string::size_type j = 0;
   for(string::size_type i = 0; i < a.size(); ++i) {
      if(   (a[i] >= '0' && a[i] <= '9')
	 || (a[i] >= 'a' && a[i] <= 'f')
	 || (a[i] >= 'A' && a[i] <= 'F')) {
	 ++j;
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

// holds the info after the < and > symbols
bool handleand(const string &a, string::size_type &index) {
   if(a.empty()) return false;
   //cout << a << endl;
   if(a.substr(0, 2) == "lt" || a.substr() == "gt") {
      index += 2;
      return true;
   } else if(a.substr(0,3) == "amp") {
      index += 3;
      return true;
   } else if(a[0] == 'x') {
      ++index;//eat the x
      if(a.size() <= 1) return false;
      return hexNum(a.substr(1, a.size() - 1), index);//start past the x
   } else {
      return false;
   }
}

bool validTag(const string &a) {
   for(string::size_type i = 0; i < a.size(); ++i) {
      if(!islower(a[i]) && !isdigit(a[i])) return false;
   }
   return true;
}

// a holds the info between the < and > symbols
bool handlelt(const string &a, stack<string> &context) {
   if(a.empty()) return false;
   cout << a << endl;
   if(a[0] == '/') {
      if(context.empty()) return false;
      if(a.substr(1, a.size() - 1) == context.top()) {
	 context.pop();
	 return true;
      } else {
	 return false;
      }
   } else if(a[a.size() - 1] == '/') {
      return validTag(a.substr(0, a.size() - 1));
   } else {
      if(validTag(a)) {
	 context.push(a);
	 return true;
      } else {
	 return false;
      }
   }
   
}

int main() {
   stack<string> context;
   string line;
   bool valid = true;
   while(getline(cin, line) && cin.good()) {
      for(string::size_type i = 0; i < line.size(); ) {
	 if(line[i] == '&') {
	    valid = handleand(line.substr(i + 1, line.size() - i - 1), i);
	 } else if(line[i] == '<') {
	    string::size_type index = line.find('>', i);
	    if(index == line.size()) valid = false;
	    else {
	       valid = handlelt(line.substr(i + 1, index - 1 - i),
				context);
	       i = index + 1;
	    }
	 } else if(line[i] == '>') {
	    valid = false;
	 } else {
	    valid = (line[i] >= 32) && (line[i] <= 127);
	    ++i;
	 }
	 if(!valid) {
	    break;
	 }
      }
      if(valid) {
	 if(context.empty()) {
	    cout << "valid" << endl;
	 } else {
	    cout << "invalid" << endl;
	 }
      } else {
	 cout << "invalid" << endl;
      }
	 
   }
   
   return 0;
}
