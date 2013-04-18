//*****************************************************************************
// CPSC 3200          Professor: Howard Cheng
//                    Teaching Assistant: Darcy Best
// Written By: Camara Lerner
// Problem number: 5739 - User Names
// Description: Use a set to store all the user names used before
//*****************************************************************************
#include <iostream>
#include <set>
#include <sstream>
#include <string>
#include <cctype>
#include <cstdlib>
using namespace std;

string itoa(const int& a) {
   ostringstream oss;
   oss << a;
   return oss.str();
}

void addto9(string& username, const int & num, const int& maxlen) {
   string number = itoa(num);
   if((int)username.length() == maxlen) {
      username[username.length() - 1] = number[0];
   } else {
      // cases for when the number is attached to the end and I am trying to
      // replace it
      if(isdigit(username[username.length() -1])) {
	 username[username.length() - 1] = number[0];
      } else {	 
	 username.push_back(number[0]);
      }
   }
}

void addto99(string& username, const int& num, const int& maxlen) {
   string number = itoa(num);
   if((int)username.length() == maxlen) {
      username[username.length() - 2] = number[0];
      username[username.length() - 1] = number[1];
   } else {
      // cases for when the number is attached to the end and I am trying to
      // replace it
      if(isdigit(username[username.length() - 1])
	 && isdigit(username[username.length() - 2])) {
	 username[username.length() - 2] = number[0];
	 username[username.length() - 1] = number[1];
      } else if(!isdigit(username[username.length() - 2])) {
	 username[username.length() - 1] = number[0];
	 username.push_back(number[1]);
      } else {
	 username += number;
      }
   }
}

void firstAndLast(const string &line, string& first, string& last) {
   istringstream iss(line);
   iss >> first;
   string tmp;
   while(iss >> tmp) {
      last = tmp;
   }
}

string userName(const string &first, const string& last, const int &maxlen) {
   string ans;
   for(string::size_type i = 0; i < first.length(); ++i) {
      if(isalpha(first[i])) {
	 ans.push_back(tolower(first[i]));
	 break;
      }
   }
   for(string::size_type i = 0; i < last.length(); ++i) {
      if(isalpha(last[i]) && (int)ans.length() < maxlen) {
	 ans.push_back(tolower(last[i]));
      }
   }
   return ans;
}

int main() {
   int cases = 1;
   int n, maxlen;
   while(cin >> n >> maxlen && (n != 0 || maxlen != 0)) {
      cout << "Case " << cases++ << endl;
      set<string> names;
      string blankline;
      getline(cin, blankline);
      for(int i = 0; i < n; ++i) {
	 string line;
	 getline(cin, line);
	 string first, last;
	 firstAndLast(line, first, last);
	 string username = userName(first, last, maxlen);
	 // see if the username is in the names
	 set<string>::iterator it = names.find(username);
	 if(it != names.end()) {
	    // then do the 1 to 9 rule
	    for(int i = 1;it != names.end() && i <= 9; ++i) {
	       addto9(username, i, maxlen);
	       it = names.find(username);
	    }
	    // check if username is in names
	    it = names.find(username);
	    if(it != names.end()) {
	       // then do the 10 to 99 rule
	       for(int i = 10; it != names.end() && i <= 99; ++i) {
		  addto99(username, i, maxlen);
		  it = names.find(username);
	       }
	    }
	 }
	 names.insert(username);
	 cout << username << endl;
	 // output the username
      }
   }
   return 0;
}
