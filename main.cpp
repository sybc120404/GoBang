#include"classes.h"

using std::cin;
using std::cout;
using std::endl;

int main(){
    Judge j;
    j.readRules();
    ChessBoard cb(j.initBoardSize());
    cb.BoardPrint();
    Player p1(1), p2(2);
    while(!j.getResult()){
        p1.chessMoves(cb,j);
        j.p1Win(cb);
        if(j.getResult()){
            break;
        }
        p2.chessMoves(cb,j);
        j.p2Win(cb);
    }
    return 0;
}