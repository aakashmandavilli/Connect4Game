/*
 * Author: SriAakash Mandavilli
 */


#include<bits/stdc++.h>
#include<vector>
#include <chrono>
#include "connect4game.cpp"

namespace AI {

class MiniMaxAB{
    public:
        Connect4Game board;
        vector<MiniMaxAB> child;
        vector<MiniMaxAB> bestPathMinmaxAB;
        int totalNodes=0,expandedNodes=0,col=0,value,dep;;
        MiniMaxAB();
         /** Function for Human vs Computer using MinmaxAB */
        void humanVsComputerMinimaxAB(int,int);

        /** Function for MinimaxAB algorithm*/
        MiniMaxAB miniMaxSearch(Connect4Game&,int,int,int,int,int=1);

        /**Check if max depth is reached*/
        bool deepEnough(int);

        /**Function which evaluates the board position and returns the number*/
        void Eval(MiniMaxAB &,int,int);

        /**Function which give score to the board based on the row and column number*/
        int getScore(MiniMaxAB &,int, int);

        /**Function which prints game board*/
        void printGameBoard();

        /**Function which clears the game board*/
        void clearGameBoard();

        /**Move generator Function*/
        void MoveGen(MiniMaxAB &,int);

        /**Function which returns the peice value at the specified board position*/
        int getSlotValueBoard(int,int);

        /**Function which sets the board position to new board position*/
        void setBoard1(int [6][7] );

        /**Function which checks if there are any connected four in the board*/
        bool checkWinBoard(Connect4Game);

        /**Function which checks if the move specified by the user is a valid move*/
        bool checkValidMoveBoard(Connect4Game,int );

};
using namespace std;
using namespace std::chrono;
static int t,e;
namespace AI {

static int gamePath=0;
static int executionTime=0;
MiniMaxAB() {
    //initialize any internal member variables
}
//vector<MiniMaxAB> bestPath;
bool checkWinBoard(Connect4Game board)
{
    bool a;
    a=this->board.checkWin(board);
    return a;
}

bool checkValidMoveBoard(Connect4Game board,int column)
{
    bool b;
    b=this->board.checkValidMove(board,column);
    return b;
}

void Eval(MiniMaxAB &session, int piece,int evalType)
{
    if(evalType==1)
    {
        session.value=this->board.evalBMinmax(session.board,piece);

    }
    else
        session.value=this->board.evalCMinmax(session.board,piece);
}

void MoveGen(MiniMaxAB &session,int piece)
{
    int i,j=0;
    MiniMaxAB session1;
    session1.board=session.board;
    if(j==0)
    {
        for(i=0;i<6;i++)
            {
                if(session1.board.getSlotValue(i,j)==0 && session1.board.getSlotValue(i,j)!=-1 && session1.board.getSlotValue(i,j)!=1)
                {
                    t++;
                    session1.board.dropPiece(piece,j);
                    session1.board.curCol=j;
                    child.push_back(session1);
                    break;
                }
            }
    }
    session1.board=session.board;
    j++;
    if(j==1)
    {
        for(i=0;i<6;i++)
            {
                if(session1.board.getSlotValue(i,j)==0 && session1.board.getSlotValue(i,j)!=-1 && session1.board.getSlotValue(i,j)!=1 && j==1)
                {
                    t++;
                    session1.board.dropPiece(piece,j);
                    session1.board.curCol=j;
                    child.push_back(session1);
                    break;
                }
            }

    }
    j++;
    session1.board=session.board;
    if(j==2)
    {
        for(i=0;i<6;i++)
            {
                if(session1.board.getSlotValue(i,j)==0 && session1.board.getSlotValue(i,j)!=-1 && session1.board.getSlotValue(i,j)!=1)
                {
                    t++;
                    session1.board.dropPiece(piece,j);
                    session1.board.curCol=j;
                    child.push_back(session1);
                    break;
                }
            }

    }
    j++;
    session1.board=session.board;
    if(j==3)
    {
      for(i=0;i<6;i++)
            {
                if(session1.board.getSlotValue(i,j)==0 && session1.board.getSlotValue(i,j)!=-1 && session1.board.getSlotValue(i,j)!=1)
                {
                    t++;
                    session1.board.dropPiece(piece,j);
                    session1.board.curCol=j;
                    child.push_back(session1);
                    break;
                }
            }
    }
    j++;
    session1.board=session.board;
    if(j==4)
    {
        for(i=0;i<6;i++)
            {
                if(session1.board.getSlotValue(i,j)==0 && session1.board.getSlotValue(i,j)!=-1 && session1.board.getSlotValue(i,j)!=1)
                {
                    t++;
                    session1.board.dropPiece(piece,j);
                    session1.board.curCol=j;
                    child.push_back(session1);
                    break;
                }
            }

    }
    j++;
    session1.board=session.board;
    if(j==5)
    {
        for(i=0;i<6;i++)
            {
                if(session1.board.getSlotValue(i,j)==0 && session1.board.getSlotValue(i,j)!=-1 && session1.board.getSlotValue(i,j)!=1)
                {
                    t++;
                    session1.board.dropPiece(piece,j);
                    session1.board.curCol=j;
                    child.push_back(session1);
                    break;
                }
            }

    }
    j++;

    session1.board=session.board;
    if(j==6)
    {
        for(i=0;i<6;i++)
            {
                if(session1.board.getSlotValue(i,j)==0 && session1.board.getSlotValue(i,j)!=-1 && session1.board.getSlotValue(i,j)!=1)
                {
                    t++;
                    session1.board.dropPiece(piece,j);
                    session1.board.curCol=j;
                    child.push_back(session1);
                    break;
                }
            }
    }
}


MiniMaxAB miniMaxSearch(Connect4Game& board,int depth, int piece,int UT,int PT,int evalType)
{
    unsigned int i;
    MiniMaxAB session;
    session.board=board;
    if(deepEnough(depth))
    {
        Eval(session,piece,evalType);
        if(piece==-1)
            session.value*=-1;
        session.totalNodes=t;
        return session;
    }

    session.MoveGen(session,piece);
    //cout<<"\nThe child size is:"<<session.child.size()<<endl;
    if(session.child.size()==0)
    {
        Eval(session,piece,evalType);
        if(piece==-1)
            session.value*=-1;
        session.totalNodes=t;
        return session;
    }
    for(i=0;i<session.child.size();i++)
    {
        MiniMaxAB Successor= miniMaxSearch(session.child[i].board,depth+1,(-1*piece),(-1*PT),(-1*UT),evalType);
        int newValue=-1*Successor.value;
        if(newValue > PT)
            {
                PT = newValue;
                if(depth == 0)
                bestPathMinmaxAB.push_back(session.child[i]);
                e++;
            }
        if(PT >= UT)
            {
                session.child[i].value=PT;
                e++;
                session.child[i].totalNodes=t;
                session.child[i].expandedNodes=e;
                return session.child[i];
            }
    }
    session.totalNodes=t;
    session.expandedNodes=e;
	session.value=PT;
	return session;
}

void humanVsComputerMinimaxAB(int depth,int peice)
{
    MiniMaxAB temp;
    int m;
    int columnNumber;
    bool win;
    int memorySize,nodeSize=43;
    for(m=0;m<22;m++)
    {
        int pass[6][7];
        peice=1;
        win=false;
        bestPathMinmaxAB.clear();
        auto start = high_resolution_clock::now();
        temp = miniMaxSearch(board,depth,peice,100,-120);
        auto stop = high_resolution_clock::now();
        auto duration = duration_cast<microseconds>(stop - start);
        executionTime+=duration.count();
//        cout<<"\ntemp.value"<<temp.value;
//        cout<<"\n\nAfter executing Minimax Search in humanVsComputer"<<endl;
//        cout<<"temp.col"<<temp.col<<endl;
//        this->board.dropPiece(peice,temp.col);
        for(int i=0;i<6;i++)
		{
			for(int j=0;j<7;j++)
			{
				//find child with move 0 and then store it into board
				pass[i][j] = bestPathMinmaxAB[bestPathMinmaxAB.size() -1].board.getSlotValue(i,j);
			}
		}
		setBoard1(pass);
        cout<<"\nThe board position after computer's turn is"<<endl;
        this->board.printBoard();
        gamePath++;
        win=checkWinBoard(board);
        if(win)
        {
            cout<<"\nAI(MinmaxAB) won the game!! Better luck next time"<<endl;
            cout<<"\nTotal length of the game: "<<gamePath;
            cout<<"\nTotal number of nodes generated are: "<<temp.totalNodes+1;
            cout<<"\nTotal number of nodes expanded are: "<<temp.expandedNodes+1;
            memorySize=(temp.expandedNodes+1)*nodeSize;
            cout<<"\nThe size of memory used by the program: "<<memorySize;
            cout <<"\nExecution time: "<< executionTime << endl;
            break;
        }
        peice=-1;
        win=false;
        cout<<"\nYour turn, Enter the column number you want to drop the coin:\n"<<endl;
        cin>>columnNumber;
        bool valid=checkValidMoveBoard(board,columnNumber);
        if(!valid)
        {
            cout<<"\nInvalid column number,Enter the valid column number again:\n";
            cin>>columnNumber;
        }
        this->board.dropPiece(peice,columnNumber);
         cout<<"\nThe board position after your(Human) turn is"<<endl;
        this->board.printBoard();
        gamePath++;
        win=checkWinBoard(board);
        if(win)
        {
            cout<<"\nCongratulations!!! You won the game"<<endl;
            cout<<"\nTotal length of the game: "<<gamePath<<endl;
           cout<<"Total number of nodes generated are: "<<temp.totalNodes+1;
            cout<<"\nTotal number of nodes expanded are: "<<temp.expandedNodes+1;
            memorySize=(temp.expandedNodes+1)*nodeSize;
            cout<<"\nThe size of memory used by the program: "<<memorySize;
            cout <<"\nExecution time: "<< executionTime << endl;
            break;
        }
    }
cout<<"\nThank You\n\n";
}

bool deepEnough(int d)
{
    return d >= 2;
}

void printGameBoard()
{
   this->board.printBoard();
}
void clearGameBoard()
{
    this->board.clearBoard();
}

int getSlotValueBoard(int x,int y)
{
    return this->board.getSlotValue(x,y);
}

void setBoard1(int a[6][7])
{
    this->board.setBoard(a);
}

} //end namespace AB
