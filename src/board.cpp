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

  blockHeight = sqrt(height);
  blockWidth = sqrt(width);

  maxval = std::max(height, width);

  board = new int*[height];
  for(int i = 0; i < height; i++){
    board[i] = new int[width];
  }
}

Board::Board(int h, int w){
  height = h;
  width = w;

  blockHeight = sqrt(height);
  blockWidth = sqrt(width);

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
  if(posy < 1 || posy > height) return false;
  if(posx < 1 || posx > width) return false;
  if(val < 1 || val > maxval) return false;

  board[posy-1][posx-1] = val;
  return true;

}

void Board::check(){
  std::cout << "width = " << width << std::endl;
  std::cout << "height = " << height << std::endl;

  std::cout << "element (1,1) = " << board[0][0]<< std::endl;
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

  while(toupper(cont) == 'Y'){
    row = 0;
    col = 0;
    val = 0;

    std::cout << "Please enter number and position on format" << std::endl;
    std::cout << "row(1-"<<height<<") column(1-"<<width<<") number(1-"<<maxval<<")"<< std::endl;
    std::cin >> row >> col >> val;
    if(!setValue(row, col, val)){
      std::cout << "Error! Invalid input!"<< std::endl;
    }
    do{
      std::cout << "More inputs? (y, n)"<<std::endl;
      std::cin >> cont;
    }while(toupper(cont) != 'Y' && toupper(cont) != 'N');
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
  std::vector<unsolved> allUnsolved;


  for(int i = 0; i < height; i++){
    for(int j = 0; j < width; j++){
      if(board[i][j] == 0){
        unsolved newunsolved = {
          i,
          j,
          // std::set<int>,
        };
        allUnsolved.insert(allUnsolved.end(), 1, newunsolved);
      }
    }
  }
  

}
