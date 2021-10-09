
#pragma once
#include<iostream>
#include<vector>
#include<string>

/*  棋盘类 */
class ChessBoard{
private:
    int size;                                   // 棋盘大小
    std::vector<std::vector<int> > data;        // 棋盘数据
    std::vector<std::vector<bool> > isfull;     // 是否已经有棋子占据
    struct Cursor{                              // 用一个结构体存储光标位置X，Y
        int X;
        int Y;
    };
    Cursor cursor;                                              // 光标
public:
    ChessBoard(int s);                                          // 构造尺寸s的棋盘
    int getSize(){return size;}                                 // 获取棋盘尺寸
    int getCursorX(){return cursor.X;}                          // 获取光标的X信息
    int getCursorY(){return cursor.Y;}                          // 获取光标的Y信息
    bool getState();                                            // 获取光标位置处的棋子信息
    std::vector<std::vector<int> > getData(){return data;}      // 获取整个棋盘的信息
    void setCursor();                                           // 移动光标
    void setData(int i);                                        // 落子
    void setState(bool b);                                      // 设置棋盘信息
    void BoardPrint();                                          // 打印棋盘
    friend bool isNum(std::string str, ChessBoard cb);          // 检测输入的坐标是否对于棋盘合法
};

class Player;                   // 声明Player，Judge类中需要用

/* 裁判类 */
class Judge{
    bool GameOver;              // 控制游戏是否结束
public:
    Judge():GameOver(false){}       // 构造函数
    int initBoardSize();            // 棋盘大小
    void readRules();               // 宣读游戏规则
    void whoseTurn(Player p);       // 宣布回合切换
    void p1Win(ChessBoard cb);      // p1胜利
    void p2Win(ChessBoard cb);      // p2胜利
    bool getResult(){return GameOver;}  // 获取游戏信息
};

/* 棋手类 */
class Player{
private:
    int whichOne;                               // 1代表p1，2代表p2
public:
    Player(int i=1):whichOne(i){}               // 构造函数
    int getWhichOne(){return whichOne;}         // 获取棋手信息
    void chessMoves(ChessBoard& cb, Judge j);   // 落子
};
