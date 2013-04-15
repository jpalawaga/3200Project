//*****************************************************************************
// CPSC 3200          Professor: Howard Cheng
//                    Teaching Assistant: Darcy Best
// Written By: Camara Lerner
// Problem number: 
// Description: 
//*****************************************************************************

// Determines the point(s) of intersection if a circle and a line
//
// Author: Darcy Best
// Date  : May 1, 2010
// Source: http://mathworld.wolfram.com/Circle-LineIntersection.html

#include <iostream>
#include <cmath>
#include <iomanip>
#include <algorithm>
using namespace std;

#define SQR(X) ((X) * (X))

// How close to call equal
const double EPS = 1e-7;

bool dEqual(double x,double y){
  return fabs(x-y) < EPS;
}

struct Point{
   double x,y;
};

struct Line{
  Point p1,p2;
};

struct Circle{
  Point centre;
  double radius;
};

// Input of:
//  - 2 distinct points on the line
//  - The centre of the circle
//  - The radius of the circle
// Output:
//  Number of points of intersection points
//  If 1 or 2, then ans1 and ans2 contain those points.
int intersect_iline_circle(Line l,Circle c,Point& ans1,Point& ans2){
  Point p1 = l.p1;
  Point p2 = l.p2;
	
  Point circCentre = c.centre;
  double rad = c.radius;
	
  p1.x -= circCentre.x;
  p2.x -= circCentre.x;
  p1.y -= circCentre.y;
  p2.y -= circCentre.y;
	
  double dx = p2.x - p1.x;
  double dy = p2.y - p1.y;
  double dr = SQR(dx) + SQR(dy);
  double D  = p1.x*p2.y - p2.x*p1.y;
	
  double desc = SQR(rad)*dr - SQR(D);
	
  if(dEqual(desc,0)){
    ans1.x = (D*dy) / dr;
    ans1.y = (-D*dx) / dr;
    return 1;
  } else if(desc < 0){
    return 0;
  }
	
  double sgn = (dy < -EPS ? -1 : 1);
	
  ans1.x = circCentre.x + (D*dy + sgn*dx*sqrt(desc)) / dr;
  ans1.y = circCentre.y + (-D*dx + abs(dy)*sqrt(desc)) / dr;
	
  ans2.x = circCentre.x + (D*dy - sgn*dx*sqrt(desc)) / dr;
  ans2.y = circCentre.y + (-D*dx - abs(dy)*sqrt(desc)) / dr;
	
  return 2;
}

bool within(const Point &a, const Line &path) {
   return (a.x >= path.p1.x) && (a.x <= path.p2.x) &&
      (a.y >= path.p1.y) && (a.y <= path.p2.y);
}

bool within(const pair<double, double> &a,
	    const pair<pair<double, double>, pair<double, double> > &path) {
   return (a.first >= path.first.first) && (a.first <= path.second.first) &&
      (a.second >= path.first.second) && (a.second <= path.second.second);
}

double dist(const Line &path) {
   double x = (path.p1.x - path.p2.x);
   double y = (path.p1.y - path.p2.y);
   return sqrt(x*x + y*y);
}

double dist(const pair<pair<double, double>, pair<double, double> > &path) {
   double x = (path.first.first - path.second.first);
   double y = (path.first.second - path.second.second);
   return sqrt(x*x + y*y);
}

int main(){
   Circle towers[100];
   int n;
   Line path;
   pair< pair<double, double>, pair<double, double> > coverage[100];
   while(cin >> n >> path.p1.x >> path.p1.y >> path.p2.x >> path.p2.y) {
      /* cout << "path: " << path.p1.x << " " << path.p1.y << " " << path.p2.x
	   << " " << path.p2.y << endl;
      */
      if(path.p1.x > path.p2.x) {
	 Point c;
	 c.x = path.p1.x;
	 c.y = path.p1.y;
	 path.p1.x = path.p2.x;
	 path.p1.y = path.p2.y;
	 path.p2.x = c.x;
	 path.p2.y = c.y;
      }
      int j = 0;
      Point a, b;
      // reads in the towers and determines where they cover the path
      for(int i = 0; i < n; ++i) {
	 cin >> towers[i].centre.x >> towers[i].centre.y >> towers[i].radius;
	 a.x = a.y = b.x = b.y = -200.0;
	 int num = intersect_iline_circle(path, towers[i], a, b);
	 //cout << "line intersect: " << a.x << " " << a.y << " " << b.x << " "
	 //<< b.y << endl;
	 

	 if(num == 1) {
	    if(within(b, path)) {
	       //   cout << "input: " << a.x << " " << a.y << endl;
	       coverage[j].first.first = coverage[j].second.first = a.x;
	       coverage[j].first.second = coverage[j].second.second = a.y;
	       j++;
	    }
	 } else if(num == 2) {
	    if(b.x < a.x) {
	       Point c;
	       c.x = b.x;
	       c.y = b.y;
	       b.x = a.x;
	       b.y = a.y;
	       a.x = c.x;
	       a.y = c.y;
	    }
	    if(within(a, path) || within(b, path)) {
	       // cout << "input: " << a.x << " " << a.y << endl;
	       if(within(a, path)) {
		  coverage[j].first.first = a.x;
		  coverage[j].first.second = a.y;
	       } else {
		  coverage[j].first.first = path.p1.x;
		  coverage[j].first.second = path.p1.y;
	       }
	       
	       if(within(b, path)) {
		  coverage[j].second.first = b.x;
		  coverage[j].second.second = b.y;
	       } else {
		  coverage[j].second.first = path.p2.x;
		  coverage[j].second.second = path.p2.y;
	       }
	       j++;
	    }
	 }
      }

      n = j;
      // sorting the list of lines
      sort(coverage, coverage + n);

      /*
      for(int i = 0; i < n; ++i) {
	 cout << coverage[i].first.first << " " << coverage[i].second.first
	      << endl;
	      }
      */

      // getting rid of the overlapping areas
      for(int i = 0; i < n; ++i) {
/*	 if(coverage[i].first.first - EPS < path.p1.x ||
	    coverage[i].second.first - EPS > path.p2.x ) {
	    cout << "i.p1.x: " << path.p1.x << " "
		 <<  coverage[i].first.first << endl;
	    cout << " i.p2.x: " << path.p2.x << " "
		 << coverage[i].second.first << endl;
	 }
*/
	 for(int j = i + 1; j < n; ++j) {
	    if(within(coverage[j].first, coverage[i])) {
	       if(coverage[i].second.first < coverage[j].second.first) {

		  coverage[i].second.first = coverage[j].second.first;
		  coverage[i].second.second = coverage[j].second.second;
	       }
	       coverage[j].first.first =
		  coverage[j].first.second =
		  coverage[j].second.first =
		  coverage[j].second.second = -200;
	       
	    }
	 }
      }

      cout << "next" << endl;
      for(int i = 0; i < n; ++i) {
	 cout << coverage[i].first.first << " " << coverage[i].second.first
	      << endl;
      }
    
      double distance = 0.0;
      for(int i = 0; i < n; ++i) {
	 distance += dist(coverage[i]);
      }
      cout << fixed << setprecision(2);
      cout << (distance / dist(path)) * 100.0 << endl;
      
   }
   
/*
  Line L;
  Circle C;
  Point a1,a2;
  
  cin >> L.p1.x >> L.p1.y >> L.p2.x >> L.p2.y;
  cin >> C.centre.x >> C.centre.y >> C.radius;
	
  int num = intersect_iline_circle(L,C,a1,a2);
  if(num == 0)
    cout << "NO INTERSECTION." << endl;
  else if(num == 1)
    cout << "ONE INTERSECTION:  (" << a1.x << "," << a1.y << ")" << endl;
  else if(num == 2)
    cout << "TWO INTERSECTIONS: (" << a1.x << "," << a1.y << ")" 
	 << "(" << a2.x << "," << a2.y << ")" << endl;
   */
  return 0;
}
