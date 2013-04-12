//*****************************************************************************
// CPSC 3200          Professor: Howard Cheng
//                    Teaching Assistant: Darcy Best
// Written By: Camara Lerner
// Problem number: 
// Description: 
//*****************************************************************************
#include <iostream>
#include <iomanip>
#include <cmath>
#include <cstdlib>
using namespace std;

double Dist_sqr( const double first[2], const double second[2]) {
   double x = (second[0] - first[0]);
   double y = (second[1] - first[1]);
   return x*x + y*y;
}

double Area_sqr( const double door[2], const double first[2],
		 const double second[2]) {
   
   double a = Dist_sqr(door, first);
   double b = Dist_sqr(first, second);
   double c = Dist_sqr(second, door);
  
/*
  if(abs(second[1] - 2.5) < 0.0001) {
  cout << "door: " << door[0] << " " << door[1] << endl;
  cout << "first: " << first[0] << " " << first[1] << endl;
  cout << "second: " << second[0] << " " << second[1] << endl;
  cout << "a, b, c: " << a << " " << b << " " << c << endl;
  }
*/
   
   return (2.0*a*b - a*a + 2.0*a*c - c*c + 2.0*b*c - b*b) / 16.0;
}

int main() {

   int width, height, door;
   int workers;
   double coord[105][2];
   double answer[100][2];
   while(cin >> width >> height >> door >> workers && (width != 0 || height != 0
	    || door != 0 || workers != 0)) {
      double eqArea_sqr = width * height / (double) workers;
      eqArea_sqr *= eqArea_sqr;
      cout << eqArea_sqr << endl;
      
      coord[0][0] = door;
      coord[0][1] = 0;

      coord[1][0] = width;
      coord[1][1] = 0;
      
      int index = 2;
      int answerIndex = 0;
      
      // trying all possible  coordinate positions
      for(int i = 1; i <= 1000 * height; ++i) {
	 coord[index][0] = width;
	 coord[index][1] = (double)i / 1000.0;
	 if(abs(Area_sqr(coord[0], coord[index - 1], coord[index]) - eqArea_sqr)
	    < 0.0005) {
	    answer[answerIndex][0] = coord[index][0];
	    answer[answerIndex++][1] = coord[index++][1];
	 }
      }
      // set special case for inbetween
      // check if there is extra area inbetween the corner and the last point
      coord[index][0] = width;
      coord[index++][1] = height;
      double extraArea = Area_sqr(coord[0], coord[index - 2], coord[index - 1]);
      cout << extraArea << endl;
      
      for(int i = 1000 * width - 1; i >= 0; --i) {
	 coord[index][0] = (double)i / 1000.0;
	 coord[index][1] = height;
	 if(abs(coord[index][0] - 2.5) < 0.0001) {
	    double temp[2] = {3.0, 5.0};
	    cout << Area_sqr(coord[0], temp, coord[index]) << endl;

	 }
	 
	 if(abs(Area_sqr(coord[0], coord[index - 1], coord[index]) -
	     eqArea_sqr + extraArea) < 0.0005) {
	    	    extraArea = 0;
	    answer[answerIndex][0] = coord[index][0];
	    answer[answerIndex++][1] = coord[index++][1];
	 }
      }
      // set special case for inbetween
      coord[index][0] = 0;
      coord[index++][1] = height;
      extraArea += Area_sqr(coord[0], coord[index - 2], coord[index - 1]);
      cout << extraArea << endl;
      
      for(int i = height * 1000; i >= 0 ; --i) {
	 coord[index][0] = 0;
	 coord[index][1] = (double)i / 1000.0;
	 if(abs(Area_sqr(coord[0], coord[index - 1], coord[index]) -
		eqArea_sqr + extraArea)  < 0.0005) {
	    extraArea = 0;
	    answer[answerIndex][0] = coord[index][0];
	    answer[answerIndex++][1] = coord[index++][1];
	 }
      }
      cout << fixed << setprecision(3);
      for(int i = 0; i < answerIndex; ++i) {
	 if(i != 0) {
	    cout << " ";
	 }
	 cout << answer[i][0] << " " << answer[i][1];
      }
      cout << endl;
   }
   return 0;
}
