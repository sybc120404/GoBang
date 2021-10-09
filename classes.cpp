#include"classes.h"

/* 棋盘 */

// 构造函数
ChessBoard::ChessBoard(int s):size(s){
    // 初始化光标位置，暂时不出现在棋盘中
    cursor.X=-2;
    cursor.Y=-2;
    // 初始化棋盘 均为0 表示最初全部为空格
    for(int i=0;i<size;i++){
        std::vector<int> temp;
        std::vector<bool> tempp;
        for(int j=0;j<size;j++){
            temp.push_back(0);
            tempp.push_back(false);
        }
        data.push_back(temp);
        isfull.push_back(tempp);
    }
}

// 打印棋盘
void ChessBoard::BoardPrint(){
    system("clear");                    // 清屏 Win、Dos将clear改为cls
    std::cout<<"    ";
    for(int i=0;i<size;i++){
        if(i<9){
            std::cout<<" "<<i+1<<" ";
        }else{
            std::cout<<i+1<<" ";
        }
    }
    std::cout<<" Y";
    std::cout<<std::endl;
    for(int i=0;i<size;i++){
        if(i<9){
            std::cout<<" "<<i+1<<"  ";
        }else{
            std::cout<<" "<<i+1<<" ";
        }
        for(int j=0;j<size;j++){
            if(data[i][j]==0){          // 空白
                std::cout<<" · ";
            }else if(data[i][j]==1){    // 黑子
                std::cout<<" ● ";
            }else if(data[i][j]==2){    // 白子
                std::cout<<" ○ ";
            }else if(data[i][j]==3){    // 光标
                std::cout<<" + ";
            }
        }
        std::cout<<std::endl;
    }
    std::cout<<" X "<<std::endl;
    // 光标位置
    std::cout<<"Cursor now: ("<<getCursorX()+1<<", "<<getCursorY()+1<<")"<<std::endl;
    // 是否有落子
    if(getCursorX()>=0 && getCursorY()>=0 && getState()){
        std::cout<<"State: Already chesses moved."<<std::endl;
    }else{
        std::cout<<"State: Still blank."<<std::endl;
    }
}

// 将输入的string类型数字转换为int
int str2int(std::string s){
    int len=s.size();
    int ans=0;
    for(int i=0;i<len;i++){
        ans=ans*10+s[i]-'0';
    }
    return ans;
}

bool isNum(std::string str, ChessBoard cb){    // 判断字符串是否合法数字（棋盘）
    for(auto s: str){
        if(isalpha(s)){     // 字符串包含字母，直接false
            return false;   
        }
    }
    int n=str2int(str);
    if(n<1||n>cb.size){     // 字符串代表数字越界，直接false
        return false;
    }
    return true;
}

void ChessBoard::setCursor(){   // 光标移动
    // 输入x y，检查
    std::string x,y;
    std::cout<<"Enter X: ";
    std::cin>>x;
    while(!isNum(x,*this)){
        std::cout<<"Invalid. Enter again! ";
        std::cin>>x;
    }
    std::cout<<"Enter Y: ";
    std::cin>>y;
    while(!isNum(y,*this)){
        std::cout<<"Invalid. Enter again! ";
        std::cin>>y;
    }
    int n=str2int(x);
    int m=str2int(y);
    cursor.X=n-1;
    cursor.Y=m-1;
    if(!getState()){            // 空白，则显示光标
        setData(3);
    }
}

void ChessBoard::setData(int i){
    data[getCursorX()][getCursorY()]=i;
}

bool ChessBoard::getState(){
    return isfull[getCursorX()][getCursorY()];
}

void ChessBoard::setState(bool b){
    isfull[getCursorX()][getCursorY()]=b;
}

/* 棋手 */

void Player::chessMoves(ChessBoard& cb, Judge j){
    bool done=false;    // 表征是否落子完毕的变量
    while(!done){
    j.whoseTurn(*this); // 裁判宣读到谁的回合
    cb.setCursor();     // 输入光标坐标数据
    cb.BoardPrint();
        if(!cb.getState()){  // 空白时才能够落子
            std::cout<<"Are you sure? [y/n]";   // 是否确定落子？
            char yesOrNot;
            std::cin>>yesOrNot;
            while(yesOrNot!='y'&&yesOrNot!='n'){
                std::cout<<"Enter y or n! Enter again! ";
                std::cin>>yesOrNot;
            }
            if(yesOrNot=='y'){
                cb.setData(whichOne);
                cb.setState(true);
                cb.BoardPrint();
                done=true;
            }else if(yesOrNot=='n'){
                cb.setData(0);
            }
        }else{              // 光标处已经有棋子
            std::cout<<"Already chess moves!"<<std::endl;
        }
    }
}

/* 裁判类方法 */

void Judge::whoseTurn(Player p){
    int who=p.getWhichOne();
    if(who==1){
        std::cout<<"P1's turn."<<std::endl;
    }else if(who==2){
        std::cout<<"P2's turn"<<std::endl;
    }
}

void Judge::readRules(){
    using std::cout;
    using std::cin;
    using std::endl;

    bool done=false;
    while(!done){
start:        
        cout<<"Welcome to my GoBang\n";
        cout<<"Here I will introduce the rules to you.\n";
        cout<<"1. Currently, only two players are supported.\n";
        cout<<"2. P1 first, then P2, then p1 ...\n";
        cout<<"3. Horizontal, vertical, diagonal direction with five pieces connected to win.\n";
        cout<<"\nUnderStand? [y/n]";
        std::string understand;
        cin>>understand;
        while(understand!="y"&&understand!="n"){
            std::cout<<"Enter y or n! ";
            std::cin>>understand;
        }
        if(understand=="y"){
            done=true;
        }else{              // 看不懂，再读一遍
            std::cout<<"Well. I'll repeat again.\n\n";
            goto start;
        }
        system("clear");
    }
}

int Judge::initBoardSize(){ // 设置棋盘大小 国际标准 15*15
    int size=15;
    return size;
}

void Judge::p1Win(ChessBoard cb){
    int n=cb.getSize(), m=n;
    std::vector<std::vector<int> > cbb=cb.getData();
    for(int i=0;i<=n-5;i++){
        for(int j=0;j<=m-2;j++){
            if(cbb[i][j]!=1){    // 当前位置非白子，继续搜索
                continue;
            }else if(cbb[i][j]==1){  // 当前位置为白子，开始搜索
                if((j+4<m&&cbb[i][j+1]==1&&cbb[i][j+2]==1&&cbb[i][j+3]==1&&cbb[i][j+4]==1) ||   // 右边
                    (i+4<n&&cbb[i+1][j]==1&&cbb[i+2][j]==1&&cbb[i+3][j]==1&&cbb[i+4][j]==1) ||  // 下边
                    (i-4>=0&&j+4<m&&cbb[i-1][j+1]==1&&cbb[i-2][j+2]==1&&cbb[i-3][j+3]==1&&cbb[i-4][j+4]==1) ||  // 斜右上方
                    (i+4<n&&j+4<m&&cbb[i+1][j+1]==1&&cbb[i+2][j+2]==1&&cbb[i+3][j+3]==1&&cbb[i+4][j+4]==1)){    // 斜右下方
                    GameOver=true;
                    std::cout<<"P1 Win!"<<std::endl;
                    return;
                }
            }
        }
    }
}

void Judge::p2Win(ChessBoard cb){
    int n=cb.getSize(), m=n;
    std::vector<std::vector<int> > cbb=cb.getData();
    for(int i=0;i<=n-5;i++){
        for(int j=0;j<=m-2;j++){
            if(cbb[i][j]!=2){    // 当前位置非白子，继续搜索
                continue;
            }else if(cbb[i][j]==2){  // 当前位置为白子，开始搜索
                if((j+4<m&&cbb[i][j+1]==2&&cbb[i][j+2]==2&&cbb[i][j+3]==2&&cbb[i][j+4]==2) ||   // 右边
                    (i+4<n&&cbb[i+1][j]==2&&cbb[i+2][j]==2&&cbb[i+3][j]==2&&cbb[i+4][j]==2) ||  // 下边
                    (i-4>=0&&j+4<m&&cbb[i-1][j+1]==2&&cbb[i-2][j+2]==2&&cbb[i-3][j+3]==2&&cbb[i-4][j+4]==2) ||  // 斜右上方
                    (i+4<n&&j+4<m&&cbb[i+1][j+1]==2&&cbb[i+2][j+2]==2&&cbb[i+3][j+3]==2&&cbb[i+4][j+4]==2)){    // 斜右下方
                    GameOver=true;
                    std::cout<<"P2 Win!"<<std::endl;
                    return;
                }
            }
        }
    }
}