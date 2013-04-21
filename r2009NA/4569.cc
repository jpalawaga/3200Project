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

int width, height, doorwid;

void rightWall(const double first[2], const double &area, double answer[2]) {
   answer[0] = width;
   answer[1] = area * 2.0 / (width - doorwid) + first[1];
}

void leftWall(const double first[2], const double &area, double answer[2]) {
   answer[0] = 0;
   answer[1] = first[1] - area * 2.0 / doorwid;
}

void rightCeil(const double first[2], const double &area, double answer[2]) {
   answer[0] = area * 2.0 / height - first[0];
   answer[1] = first[1];
}

void leftCeil(const double first[2], const double &area, double answer[2]) {
   answer[0] = first[0] - area * 2.0 / height;
   answer[1] = first[1];
}

int main() {
   int workers;
   double answer[105][2];
   while(cin >> width >> height >> doorwid >> workers &&
	 (width != 0 || height != 0 || doorwid != 0 || workers != 0)) {
      double eqArea = width * height / (double) workers;
      double first[2];
      double area = eqArea - 0.0;
      int i = 0;
     
      first[1] = 0.0;
      first[0] = width;
      rightWall(first, area, answer[i]);
      while(answer[i][1] < height) {
	 rightWall(answer[i], area, answer[i + 1]); 
	 ++i;
      }

      area = area - (width - doorwid)*(answer[i - 1][1])/ 2.0;
      first[1] = height;
      first[0] = width;
      rightCeil(first, area, answer[i]);
      while(answer[i][0] > doorwid) {
	 area = eqArea;
	 rightCeil(answer[i], area, answer[i + 1]);
	 ++i;
      }

      area = area - (height) * (answer[i - 1][0] - doorwid) / 2.0;
      first[1] = height;
      first[0] = 0.0;
      leftCeil(first, area, answer[i]);
      while(answer[i][0] > 0) {
	 area = eqArea;
	 leftCeil(answer[i], area, answer[i + 1]);
	 ++i;
      }

      area = area - height* answer[i-1][0] / 2.0;
      first[0] = 0.0;
      first[1] = height;
      leftWall(answer[i], area, answer[i + 1]);
      while(answer[i][1] > 0) {
	 area = eqArea;
	 leftCeil(answer[i], area, answer[i + 1]);
	 ++i;
      }
      for(int w = 0; w <= i; ++w) {
	 if(w != 0) {
	    cout << " ";
	 }
	 cout << answer[w][0] << " " << answer[w][1];
      }
      cout << endl;
   }
   
   return 0;
}
