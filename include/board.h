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

  void check();
  bool setValue(int posy, int posx, int val);
  void fill();
  void print();
  void clear();
  bool solve();


  Board();
  Board(int, int);
  Board(const Board &oldBoard);
  ~Board();
};

struct unsolved{
  int y;
  int x;
  std::set<int> possible;
};







#endif
