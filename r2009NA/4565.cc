//*****************************************************************************
// CPSC 3200          Professor: Howard Cheng
//                    Teaching Assistant: Darcy Best
// Written By: Camara Lerner
// Problem number: 4564 - Balance
// Description: 
//*****************************************************************************

#include <iostream>
using namespace std;

int main() {

   // after a term deduct a fixed administrative cost, and a fee percentage of
   // the amount of at the beginning of the term. Also add the return
   // percentage (+ or -) (if below zero at any time leave it at zero)

   // rebalancing occurs every NREBALANCE terms, to redistribute money
   // according to the original ratios. Note that if all instruments drop
   // to zero, they will all remain closed for the remaining terms.

   // report the ending value in each instrument(b/f rebalancing)
   // (do not round intermediate values)

   // numInstrument is at most 10
   // numTerm is at most 20
   int numInstrument, numTerm, rebalance;
   double info[3][10];
   // 0 = fixed_fee, 1 = percentage_fee, 2 = principal_start
   double returns[10][20];
   while(cin >> numInstrument >> numTerm >> numBalance) {

      for(int i = 0; i < 3; ++i) {
	 for(int j = 0; j < numInstrument; ++j) {
	    cin >> info[i][j]; // read in Fees and principal start
	 }
      }

      for(int i = 0; i < numTerm; ++i) {
	 for(int j = 0; j < numInstrument; ++j) {
	    cin >> returns[i][j]; // return # i for ninstrument j
	 }
      }

      // calculate the term price principal_end
      // have to loop through the terms and calculate principal
      for() {
         // have to loop throught the instruments to calculate the returns
            // taking off the adminstration fee and the percentage off and
	    // then add the return
            // check that you are above zero, and you are stay there
         // have your return
	 // check for the rebalance and do if needed
      }
      
   }
   
   return 0;
}
