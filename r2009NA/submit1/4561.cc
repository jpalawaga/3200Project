//*****************************************************************************
// CPSC 3200          Professor: Howard Cheng
//                    Teaching Assistant: Darcy Best
// Written By: Camara Lerner
// Problem : 4561 - Range
// Description: Uses the rules given and calculates the distance that can be
// reached
//*****************************************************************************

#include <iostream>
using namespace std;

int main() {

   double odo, wei;
   while(cin >> odo >> wei && !(odo == -1.0 && wei == -1.0)) {
      double distance = 0, fuel = 0;
      double nexo, nwei;
      while(cin >> nexo >> nwei && !(nexo == 0.0 && nwei == 0.0)) {
	 if(wei > nwei) {
	    distance += nexo - odo;
	    fuel += wei - nwei;
	 }
	 wei = nwei;
	 odo = nexo;
      }
      cout << (int)(wei * distance / fuel + 0.5) << endl;
   }
   
   return 0;
}
