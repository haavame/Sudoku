#include "board.h"
#include <iostream>

using namespace std;

int main(){
  int height, width;
  cout<<"Hello"<<endl;
  cout << "Please enter sudoku block size, on the form:"<<endl;
  cout << "block-height    block-width"<< endl;
  cin >> height >> width;

  Board board(height, width);
  board.fill();

  board.print();

  bool solved = board.solve();
  if(solved){
    cout << "Sudoku Solved"<< endl;
  }else{
    cout << "Failed to solve sudoku"<< endl;
  }

  board.print();
}
