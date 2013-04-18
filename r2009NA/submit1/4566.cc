//*****************************************************************************
// CPSC 3200          Professor: Howard Cheng
//                    Teaching Assistant: Darcy Best
// Written By: Camara Lerner
// Problem number: 4566 - Resistors
// Description: Read in the equation into a stack and evaluate the equation
// according to the rules
//*****************************************************************************

#include <string>
#include <iostream>
#include <cassert>
#include <vector>
#include <stack>
#include <cstdlib>
#include <sstream>
using namespace std;

long long gcd(long long a, long long b)
{
  long long r;

  /* unnecessary if a, b >= 0 */
  if (a < 0) {
    a = -a;
  }
  if (b < 0) {
    b = -b;
  }

  while (b) {
    r = a % b;
    a = b;
    b = r;
  }
  assert(a >= 0);
  return a;
}

long long lcd(long long a, long long b) {
   return a * b / gcd(a,b);
}

class Rational {
public:
   friend Rational sumOR(vector<Rational> & a);
   friend Rational sumAND(vector<Rational> & a);
   Rational() {}
   Rational(const string &a);
   Rational(const long long& a, const long long& b) : top(a), bot(b) {}
   string str() const;
private:
   Rational& reciprical();
   Rational& add(const Rational& a); 
   // hold the numerator and denominator
   long long top, bot;
};

Rational::Rational(const string &a) {
   string::size_type mid = a.find('/');
   top = atoi(a.substr(0,mid).c_str());
   bot = atoi(a.substr(mid + 1, a.size() - mid - 1).c_str());
}

Rational sumOR(vector<Rational> & a) {
   if(a.size() <= 0) {
      return Rational(0, 0);
   }
   a[0].reciprical();
   for(vector<Rational>::size_type i = 1; i < a.size(); ++i) {
      a[i].reciprical();
      a[0].add(a[i]);
   }
   a[0].reciprical();
   return a[0]; 
}

Rational sumAND(vector<Rational> & a) {
   for(vector<Rational>::size_type i = 1; i < a.size(); ++i) {
      a[0].add(a[i]);
   }
   return a[0];
}

Rational& Rational::reciprical() {
   long long temp = top;
   top = bot;
   bot = temp;
   return *this;
}

Rational& Rational::add(const Rational& a) {
   // does factor adding
   long long den = lcd(bot, a.bot);
   top = a.top*den/a.bot + top*den/bot;
   bot = den;
   // reduces the fraction
   long long fac = gcd(top, bot);
   top /= fac;
   bot /= fac;
   
   return *this;
}

string Rational::str() const {
   ostringstream oss;
   oss << top << '/' << bot;
   return oss.str();
}

void handleStack(stack<string> & equation) {
   // evaluate everthing on the stack that closes that bracket
   // and push it back onto the stack
   vector<Rational> mine;
   string operation;
   Rational answer;
   if(!equation.empty()) {
      while(equation.top() != "(") {
	 if(!equation.empty()) {
	    if(equation.top() == "&" || equation.top() == "|") {
	       operation = equation.top();
	    } else {
	       // add the rational to the vector
	       mine.push_back(Rational(equation.top()));
	    }
	    equation.pop();
	 }
      }
      equation.pop();
   }
   // figure out result
   if(operation == "&") {
      answer = sumAND(mine);
   } else if(operation == "|") {
      answer = sumOR(mine);
   } 
   // push the result onto the equation(stack)
   equation.push(answer.str());
}

int main() {
   string line;
   while(getline(cin, line)) {
      stack< string > equation;
      if(line[0] != '(') {
	 cout << line << endl;
      } else {
	 Rational answer;
	 for(string::size_type i = 0; i < line.size(); ) {
	    if(line[i] == ' ') {
	       ++i;
	    } else if(line[i] == ')') {
	       handleStack(equation);	       
	       ++i;
	    } else if((line[i] == '(') ||
		      (line[i] == '|') ||
		      (line[i] == '&')) {
	       // push onto the stack
	       equation.push(string(1,line[i]));
	       ++i;
	    } else {
	       int j = i;
	       // this is a rational
	       while((line[i] != ' ') && (line[i] != ')') &&
		     (i < line.size())) {
		  ++i;
	       }
	       equation.push(line.substr(j, i - j));
	    }
	 }
	 // output the answer
	 if(!equation.empty()) {
	    cout << equation.top() << endl;
	 }
      }
   }
   return 0;
   
}
