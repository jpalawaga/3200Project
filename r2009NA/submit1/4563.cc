//*****************************************************************************
// CPSC 3200          Professor: Howard Cheng
//                    Teaching Assistant: Darcy Best
// Written By: Camara Lerner
// Problem number: 4563 XML
// Description: Doing very careful string parsing.
// I keep track of the start of the part of the string I am looking at and the
// length of the string that needs to be looked at
//*****************************************************************************

#include <iostream>
#include <iomanip>
#include <string>
#include <stack>
#include <cstdio>
using namespace std;


// a should only be everything after the x

bool hexNum(const string &a, const int &start,
	    const int &ln, string::size_type &index) {
   string::size_type j = 0;
   for(int i = start; i < start + ln; ++i) {
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
      if(start + ln == (int)a.size()) {
	 return true;
      } else {
	 return a[start + ln] == ';';
      }
   }
}

// holds the info after the & symbol
bool handleand(const string &a, const int &start,
	       const int &ln, string::size_type &index) {
   if(start >= start + ln) return false;
   if(a.substr(start, 3) == "lt;"
      || a.substr(start, 3) == "gt;") {
      index += 3;
      return true;
   } else if(a.substr(start, 4) == "amp;") {
      index += 4;
      return true;
   } else if(a[start] == 'x') {
      ++index;//eat the x
      if(ln <= 1) return false;
      return hexNum(a, start + 1, ln - 1, index);//start past the x
   } else {
      return false;
   }
}

// a holds the info between the < and > symbols
bool validTag(const string &a, const int &start,
	      const int &ln) {
   for(int i = start; i < start + ln; ++i) {
      if(!islower(a[i]) && !isdigit(a[i])) return false;
   }
   return true;
}

// a holds the info between the < and > symbols
bool handlelt(const string &a, const int &start,
	      const int &ln, stack<string> &context) {
   if(start >= start + ln) return false;
   if(a[start] == '/') {
      if(context.empty()) return false;
      if(a.substr(start + 1, ln - 1) == context.top()) {
	 context.pop();
	 return true;
      } else {
	 return false;
      }
   } else if(a[start + ln - 1] == '/') {
      return validTag(a, start, ln - 1);
   } else {
      if(validTag(a, start, ln)) {
	 context.push(a.substr(start, ln));
	 return true;
      } else {
	 return false;
      }
   }
   
}

int main() {
   string line;
   while(getline(cin, line) && cin.good()) {
      bool valid = true;
      stack<string> context;
      for(string::size_type i = 0; i < line.size(); ) {
	 if(line[i] == '&') {
	    valid = handleand(line, i + 1, line.size() - i - 1, i);
	 } else if(line[i] == '<') {
	    string::size_type index = line.find('>', i);
	    if(index == line.size()) {
	       valid = false;
	    } else {
	       valid = handlelt(line, i + 1, index - 1 - i,
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
