#include "board.h"
#include <iostream>

using namespace std;


int main(){
cout<<"hei"<<endl;

Board board;
board.print();
// for(int i = 1; i < 10; i++){
//   board.setValue(i, i, i);
// }
board.fill();

board.print();

}
