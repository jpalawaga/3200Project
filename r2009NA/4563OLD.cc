//*****************************************************************************
// CPSC 3200          Professor: Howard Cheng
//                    Teaching Assistant: Darcy Best
// Written By: Camara Lerner
// Problem number: 
// Description: 
//*****************************************************************************

#include <iostream>
#include <sstream>
#include <iomanip>
#include <stack>
#include <string>
using namespace std;

bool handlelt(const string &a, stack<string> & context) {
   // cout << a << endl;
   if(a.empty()) {
      return false;
   }
   if(a[0] == '/') {
      if(context.empty()) return false;
      if(a.size() >= 2) {
//	 cout << a.substr(1, a.size() - 1) << endl;
	 if(a.substr(1, a.size() - 1) == context.top() ) {
	    context.pop();
	    return true;
	 } else {
	    return false;
	 }
      } else {
	 if("" == context.top()) {
	    context.pop();
	    return true;
	 } else {
	    return false;
	 }
      }
   } else if(a[a.size() - 1] == '/') {
      if(a.size() > 1) {
	 // cout << "a;iog" << endl;
	 //cout << a << endl;
	 for(string::size_type i = 0; i < a.size() - 1; ++i) {
	    // cout << !(islower(a[i]) || isdigit(a[i]));
	    if(!(islower(a[i]) || isdigit(a[i]))) return false;
	 }
	 return true;
      } else {
	 return false;
      }
   } else {
      if(a.size() > 0 ) {
	 // cout << "aoibg" << endl;
	 //cout << a << endl;
	 for(string::size_type i = 0; i < a.size(); ++i) {
	    // cout << !(islower(a[i]) || isdigit(a[i]));
	    if(!(islower(a[i]) || isdigit(a[i]))) return false;
	 }
	 context.push(a);
	 return true;
      } else {
	 return false;
      }
   }
   
}

int number(unsigned char a) {
   if( a >= '0' && a <= '9' ) {
      return a - '0';
   } else if( a >= 'A' && a <= 'F') {
      return a - 'A' + 10;
   } else if( a >= 'a' && a <= 'f') {
      return a - 'a' + 10;
   } else {
      return -1;
   }
}
/*
int hex(string a) {
   cout << "0x" << a << endl;
   int num = 0;
   for(string::size_type i = 0; i < a.size(); ++i) {
      if(number(a[i]) < 0) return -1;
      num = num * 16 + number(a[i]);
   }
   return num;
}
*/
string::size_type handleand(const string &a, bool &valid) {
   if(a.size() < 2) {
      valid = false;
      return a.size();
   }
   if(a.substr(0,2) == "lt" || a.substr(0,2) == "gt" ) {
      return 2; 
   } else if( a.substr(0,3) == "amp") {
      return 3;
   } else if(a[0] == 'x') {
      //   cout << a << endl;
      string::size_type i, j = 0;
      for(i = 1; i < a.size(); ) {
	 //cout << a[i] << " " << number(a[i]) << " " ;
	 if(number(a[i]) >= 0 && number(a[i]) <= 16) {
	    j = i;
	    ++i;
	 } else {
	    break;
	 }
      }
//      cout << j << endl;
      if( (j % 2) == 1 || j == 0) {
	 valid = false;
	 return a.size();
      } else {
	 return i;
      }
   } else {
      valid = false;
      return a.size();
   }
}

int main() {
   stack<string> context;
/*   cout << boolalpha;
   cout << handlelt("a",context) << endl;
   cout << handlelt("/a",context) << endl;
   cout << handlelt("a/", context) << endl;
   cout << !handlelt("/a",context) << endl;
   cout << handlelt("a",context) << endl;
   cout << handlelt("a/", context) << endl;
   cout << handlelt("abc",context) << endl;
   cout << handlelt("/abc",context) << endl;
   cout << handlelt("aoigh/", context) << endl;
   cout << !handlelt("/asiobvg",context) << endl;
   cout << handlelt("aso",context) << endl;
   cout << handlelt("aaiubgv/", context) << endl;
*/

   string line;
   while(getline(cin, line)) {
      stack<string> context;
      bool valid = true;
      for(string::size_type i = 0; i < line.size();) {
	 unsigned char c = line[i];
	 string::size_type index;
	 switch(line[i]) {
	    case '<':
	       index = line.find('>',i);
	       if(index < line.size()) {
		  valid = handlelt(line.substr(i + 1, index - i - 1), context);
		  i = index + 1;
		  //	  cout << i << endl;
	       } else {
		  valid = false;
	       }
	       break;
	    case '>':
	       valid = false;
	       break;
	    case '&':
	       i += handleand(line.substr(i + 1, line.size() - i - 1), valid);
	       break;
	    default:
	       if(c < 32 || c > 127) {
		  valid = false;
	       }
	       i++;
	 };
	 if(!valid) {
	    break;
	 }
      }
      if(context.empty()) {
	 if(valid) {
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
