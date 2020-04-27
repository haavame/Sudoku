#ifndef BOARD_H
#define BOARD_H

#include <set>

class Board{
private:
  int height, width;
  int blockHeight, blockWidth;
  int maxval;
  int **board;


public:
  int getHeight(){return height;};
  int getWidth(){return width;};

  void getRow(int posy, std::set<int>& row);
  void getCol(int posx, std::set<int>& col);
  void getBlock(int posy, int posx, std::set<int>& block);

  void check(int posx, int posy);

  bool setValue(int posy, int posx, int val);
  void fill();
  void print();
  void clear();

  bool checkIfPossible(int posy, int posx, int num);
  bool recSolve(int posy, int posx);
  bool solve();

  Board();
  Board(int h, int w);
  Board(const Board &oldBoard);
  ~Board();
};

struct unsolved{
  int y;
  int x;
  std::set<int> possible;
};


void setPrint(std::set<int> myset);




#endif
