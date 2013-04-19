//*****************************************************************************
// CPSC 3200          Professor: Howard Cheng
//                    Teaching Assistant: Darcy Best
// Written By: Camara Lerner
// Problem number: 5736 - Contour Tracing
// Description: 
//*****************************************************************************
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;
//                   W  NW   N  NE   E  SE   S  SW
const int dr[8] = {  0, -1, -1, -1,  0,  1,  1,  1};
const int dc[8] = { -1, -1,  0,  1,  1,  1,  0, -1};
char board[202][202];
bool contour[202][202]; // will hold all the pixels in all the contours
int rows, cols;

// holds the current row and column and a reference to the direction you just came from
void move(int &r, int &c, int &pr) {
   for(int i = 1; i <= 8; ++i) {
      if(board[r + dr[(pr + i) % 8]][c + dc[(pr + i) % 8]] == '1') {
	 r += dr[(pr + i) % 8];
	 c += dc[(pr + i) % 8];
	 pr = (pr + i + 4) % 8;
	 return;
      }
   }
   return;
}

int traceContour(const int &r, const int &c, int& moves) {
   int sr = r, sc = c, pr = 0;
   bool visited[202][202];
   moves = 1;

   //cout << "r: " << r << " c: " << c << endl;
   for(int i = 1; i <= rows; ++i) {
      for(int j = 1; j <= cols; ++j) {
	 visited[i][j] = false;
      }
   }
   contour[r][c] = visited[r][c] = true;

   //cout << "r: " << r << " c: " << c << " pr: " << pr << endl;
   move(sr,sc, pr);
   while(!(sr == r && sc == c)) {
      // cout << "sr: " << sr << " sc: " << sc << " pr: " << pr << endl;
      contour[sr][sc] = visited[sr][sc] = true;
      move(sr, sc, pr);
      ++moves;
   }
   // fill in the contour
   /*
     int pixels = 0;
   for(int i = 1; i <= rows; ++i) {
      for(int j = 1; j <= cols; ++j) {
	 if(visited[i][j]) {
	    ++pixels;
	    int w = j + 1;
	    for(; w <=cols; ++w) {
	       if(visited[i][w]) {
		  fill(visited[i] + j, visited[i] + w, true);
		  fill(contour[i] + j, contour[i] + w, true);
		  pixels += w - j;
		  //cout << "w - j: " << w - j << endl;
		  break;
	       }
	    }
	    j = w;
	 }
      }
      }
   */
/*   for(int i = 1; i <= rows; ++i) {
      for(int j = 1; j <= cols; ++j) {
	 cout << visited[i][j] << " ";
      }
      cout << endl;
   }
   cout << "pixels: " << pixels << endl;
*/ 
   return pixels;
}

int main() {
   int cases = 1;
   while(cin >> rows >> cols && rows != 0 && cols != 0) {
      for(int i = 0; i <= max(rows, cols) + 1; ++i) {
	 board[0][i] = board[i][0] = board[rows + 1][i]
	    = board[i][cols + 1] = '0';
	 contour[0][i] = contour[i][0] = contour[rows + 1][i]
	    = contour[i][cols + 1] = false;
      }
      for(int i = 1; i <= rows; ++i) {
	 for(int j = 1; j <= cols; ++j) {
	    cin >> board[i][j];
	    contour[i][j] = false;
	 }
      }
      vector<int> ans;
      int r = 2, c = 3, pr = 0;
      move(r, c, pr);
      for(int i = 1; i <= rows; ++i) {
	 for(int j = 1; j <=cols; ++j) {
	    if(board[i][j] == '1') {
	       if(!contour[i][j]) {
		  //cout << "i: " << i << " j: " << j << endl;
		  int trace;
		  if(traceContour(i, j, trace) >= 5) {
		     ans.push_back(trace);
		  }
		  for(int w = j + 1; w <= cols; ++w) {
		     if(board[i][j] == '0') {
			j = w - 1;
			break;
		     }
		  }
	       } else {
		  for(int w = j + 1; w <= cols; ++w) {
		     if(board[i][j] == '0') {
			j = w - 1;
			break;
		     }
		  }
	       }
	    }
	 }
      }

      cout << "Case " << cases++ << endl;
      sort(ans.begin(), ans.end());
      for(vector<int>::size_type i = 0; i < ans.size(); ++i) {
	 if(i != 0) {
	    cout << " ";
	 }
	 cout << ans[i];
      }
      if(ans.empty()) {
	 cout << "no objects found";
      }
      cout << endl;
	  
   }
   

   return 0;
}


