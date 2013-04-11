//*****************************************************************************
// CPSC 3200          Professor: Howard Cheng
//                    Teaching Assistant: Darcy Best
// Written By: Camara Lerner
// Problem number: 4564 - Balance
// Description: I follow the rules mentioned in the question very carefully
//*****************************************************************************

#include <iostream>
#include <iomanip>
using namespace std;

int main() {

   // numInstrument is at most 10
   // numTerm is at most 20
   int numInstrument, numTerm, rebalance;
   // 0 = fixed_fee, 1 = percentage_fee, 2 = principal_start
   double info[3][10];
   double ratios[10];
   double returns[20][10];
   while(cin >> numInstrument >> numTerm >> rebalance) {

      for(int i = 0; i < 3; ++i) {
	 for(int j = 0; j < numInstrument; ++j) {
	    cin >> info[i][j]; // read in Fees and principal start
	 }
      }
      {  // setting the ratios for each numInstrument
	 double total = 0.0;
	 for(int i = 0; i < numInstrument; ++i) {
	    if(info[2][i] > 0) {
	       total += info[2][i];
	    }
	 }
	 for(int i = 0; i < numInstrument; ++i) {
	    ratios[i] = info[2][i] / total;
	 }
      }

      for(int i = 0; i < numTerm; ++i) {
	 for(int j = 0; j < numInstrument; ++j) {
	    cin >> returns[i][j]; // return # i for ninstrument j
	 }
      }

      // calculate the term price principal_end
      // have to loop through the terms and calculate principal
      for(int i = 0; i < numTerm; ++i) {
         // have to loop throught the instruments to calculate the returns

         // check for the rebalance and do if needed
	 if((i % rebalance) == 0 && i != 0) {
	    double total = 0.0;
	    for(int i = 0; i < numInstrument; ++i) {
	       if(info[2][i] > 0) {
		     total += info[2][i];
	       }
	    }
	    for(int i = 0; i < numInstrument; ++i) {
	       info[2][i] = ratios[i] * total;
	       }
	 }
	 for(int j = 0; j < numInstrument; ++j) {
	    // adds the return and
	    // then takes off the adminstration fee and
	    // the percentage off
	    info[2][j] = (1.0 + returns[i][j]) * info[2][j]
	       - info[2][j] * info[1][j]
	       - info[0][j];
	    // check that you are above zero, and if not puts you there
	    if(info[2][j] < 0.0) {
	       info[2][j] = 0.0;
	    }
	 }
      }

      cout << fixed << setprecision(2);
      // output the returns
      for(int i = 0; i < numInstrument; ++i) {
	 if(i != 0 ) {
	    cout << " ";
	 }
	 cout << info[2][i];
      }
      cout << endl;
   }
   
   return 0;
}
