#include "board.h"
#include <iostream>
#include <algorithm>
#include <cmath>
#include <cctype>
#include <vector>
#include <set>

Board::Board(){
  height = 9;
  width = 9;

  blockHeight = 3;
  blockWidth = 3;

  maxval = std::max(height, width);

  board = new int*[height];
  for(int i = 0; i < height; i++){
    board[i] = new int[width];
  }
}

Board::Board(int h, int w){
  blockHeight = h;
  blockWidth = w;

  height = blockHeight*blockWidth;
  width = blockHeight*blockWidth;

  maxval = std::max(height, width);

  board = new int*[height];
  for(int i = 0; i < height; i++){
    board[i] = new int[width];
  }
}

Board::Board(const Board &oldBoard){
  this->height = oldBoard.height;
  this->width = oldBoard.width;

  this->blockHeight = oldBoard.blockHeight;
  this->blockWidth = oldBoard.blockWidth;

  this->maxval = oldBoard.maxval;

  this->board = new int*[this->height];
  for(int i = 0; i < this->height; i++){
    this->board[i] = new int[this->width];
  }

  for(int i = 0; i < this->height; i++){
    for(int j = 0; j < this->width; j++){
      this->board[i][j] = oldBoard.board[i][i];
    }
  }
}

Board::~Board(){
    for(int i = 0; i < height; i++){
    delete[] board[i];
  }
  delete[] board;
}

bool Board::setValue(int posy, int posx, int val){
  if(posy < 0 || posy >= height) return false;
  if(posx < 0 || posx >= width) return false;
  if(val < 1 || val > maxval) return false;

  board[posy][posx] = val;
  return true;

}

void Board::check(int posy, int posx){
  std::set<int> test;
  getCol(posx, test);
  std::cout << "Column set "<<posx<<":"<<std::endl;
  setPrint(test);
  test.clear();
  getRow(posy, test);
  std::cout << "Row set "<<posy<<":"<<std::endl;
  setPrint(test);
  test.clear();
  getBlock(posy, posx, test);
  std::cout << "Block set ("<<posy<<","<<posx<<"):"<<std::endl;
  setPrint(test);
  test.clear();
  getRow(posy, test);
  getCol(posx, test);
  getBlock(posy, posx, test);
  std::cout << "combined set for ("<<posy<<","<<posx<<"):"<<std::endl;
  setPrint(test);
}

void Board::print(){
  for(int i = 0; i < width; i++){
    if(i%blockHeight == 0){
      for(int k = 0; k < 2*width+blockWidth+1; k++){
        std::cout << "-";
      }
      std::cout << std::endl;
    }
    for(int j = 0; j < height; j++){
      if(j%blockWidth == 0){
        std::cout << "|";
      }
      std::cout << board[i][j] << " ";
    }
    std::cout << "|" << std::endl;
  }
  for(int k = 0; k < 2*width+blockWidth+1; k++){
    std::cout << "-";
  }
  std::cout << std::endl;
}

void Board::fill(){
  char cont = 'Y';
  int row, col, val;

  // int newboard[9][9] = {{0, 0, 0, 0, 0, 3,  0, 2, 8}, {0, 2, 4, 8, 7, 1, 3, 0, 9}, {0, 8, 0, 5, 6, 0, 4, 1, 0}, {9, 0, 0, 1, 3, 0, 2, 0, 4}, {0, 0, 0, 0, 0, 0, 0, 0, 5}, {0, 0, 0, 0, 9, 4, 0, 3, 0}, {8, 0, 3, 4, 0, 0, 0, 7, 2}, {7, 1, 2, 0, 8, 0, 0, 0, 0}, {0, 4, 0, 0, 1, 7, 0, 9, 3}};
  // for(int i = 0; i < height; ++i){
  //   for(int j = 0; j < width; ++j){
  //     board[i][j] = newboard[i][j];
  //   }
  // }

  while(true){
    row = 0;
    col = 0;
    val = 0;

    std::cout << "Please enter number and position on format" << std::endl;
    std::cout << "row(1-"<<height<<") column(1-"<<width<<") number(1-"<<maxval<<")"<< std::endl;
    std::cout << "when done set either value 0"<< std::endl;
    std::cin >> row >> col >> val;
    if(!setValue(row-1, col-1, val)){
      return;
    }
  }
}

void Board::clear(){
  for(int i = 0; i < height; i++){
    for(int j = 0; j < width; j++){
      board[i][j] = 0;
    }
  }
}

bool Board::solve(){
/*
  std::vector<unsolved> allUnsolved;


  for(int i = 0; i < height; i++){
    for(int j = 0; j < width; j++){
      if(board[i][j] == 0){
        std::set<int> newset;
        unsolved newunsolved = {
          i,
          j,
          newset,
        };
        allUnsolved.push_back(newunsolved);
      }
    }
  }

  int donecount = 0;
  bool done;
  std::set<int> used;
  while(!allUnsolved.empty()){
    // std::vector<unsolved>::iterator it = allUnsolved.begin();
    // while(it != allUnsolved.end())
    for(std::vector<unsolved>::iterator it = allUnsolved.begin(); it != allUnsolved.end(); ++it){
      // std::cout << "solving pos ("<<it->y<<","<<it->x<<")"<<std::endl;
      // check(it->y, it->x);
      done = false;
      used.clear();
      getCol(it->x, used);
      getRow(it->y, used);
      getBlock(it->y, it->x, used);

      // std::cout << "used set: "<<std::endl;
      // setPrint(used);

      for(int i = 1; i <= maxval; ++i){
        if(used.find(i) == used.end()){
          it->possible.insert(i);
        }
      }
      // std::cout<<"possible numbers: ";
      // setPrint(it->possible);

      unsigned int size = it->possible.size();

      if(size == 0){
        std::cout << "Error, no possible numbers in position ("<<it->y<<","<<it->x<<")!"<<std::endl;
        return false;
      }else if(size == 1){
        done = true;
        std::set<int>::iterator iter = it->possible.begin();
        board[it->y][it->x] = *iter;
        allUnsolved.erase(it);
        print();
      }else{
        // ++it;
      }

    }
    // if(!done){
    //   ++donecount;
    // }else{
    //   donecount = 0;
    // }
    // if(allUnsolved.empty()){
    //   return true;
    // }else{
    //   return false;
    // }
  }
  // for(std::vector<unsolved>::iterator it = allUnsolved.begin(); it != allUnsolved.end(); ++it){
  //   // std::pair <std::set<int>::iterator, bool> dontcare;
  // }

*/
return recSolve(0, 0);

}

bool Board::recSolve(int posy, int posx){
  if(posx >= width){
    posy++;
    posx = 0;
    if(posy >= height){
      return true;
    }
  }

  if (board[posy][posx] != 0){
    return recSolve(posy, posx+1);
  }

  int i = 1;


  while(i <= maxval){
    if(checkIfPossible(posy, posx, i)){
      setValue(posy, posx, i);
      if(recSolve(posy, posx+1)){
        return true;
      }
    }
    ++i;
  }
  board[posy][posx] = 0;
  return false;
}

bool Board::checkIfPossible(int posy, int posx, int num){
  std::set<int> pos;
  getCol(posx, pos),
  getRow(posy, pos);
  getBlock(posy, posx, pos);

  if (pos.find(num) == pos.end()){
    return true;
  }
  return false;
}

void Board::getCol(int posx, std::set<int>& col){
  for(int i = 0; i < height; i++){
    if(board[i][posx] != 0){
      col.insert(board[i][posx]);
    }
  }
}

void Board::getRow(int posy, std::set<int>& row){
  for(int i = 0; i < width; i++){
    if(board[posy][i] != 0){
      row.insert(board[posy][i]);
    }
  }
}

void Board::getBlock(int posy, int posx, std::set<int>& block){

  int startx = posx - posx%blockWidth;
  int starty = posy - posy%blockHeight;

  for(int i = starty; i < starty+blockHeight; ++i){
    for(int j = startx; j < startx+blockWidth; ++j){
      if(board[i][j] != 0){
        block.insert(board[i][j]);
      }
    }
  }
}

void setPrint(std::set<int> myset){
  for(std::set<int>::iterator it = myset.begin(); it != myset.end(); ++it){
    std::cout<<*it<<" ";
  }
  std::cout<<std::endl;
}
