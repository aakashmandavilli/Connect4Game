/*
 * Author: SriAakash Mandavilli
 */


#include <iostream>
#include "minimaxalphabeta.h"
#include "MinimaxAB.h"
#include "connect4game.h"
#include "AIgame.h"

using namespace std;
using namespace AI;
int main()
{

    int choice;
    cout<<"\nCONNECT FOUR GAME"<<endl;
    cout<<"\nEnter the mode from the following:\n1.Human vs Computer(MinimaxAB)\n2.Human vs Computer(AlphaBeta)\n3. Computer(MinmaxAB) vs Computer(Alphabeta)\n4. Computer(MinmaxAB) vs Computer(MinmaxAB)\n5. Computer(Alphabeta) Vs Computer(Alphabeta)\n6. Computer(MinMaxAB) Vs Computer(Alphabeta) with evaluation 2\n";
    cin>>choice;
    //individual evaluation for minmaxAB
    /*if(choice==1)
    {
        MiniMaxAB minimaxab_session;
        minimaxab_session.clearGameBoard();
        cout<<"\nComputer's turn..."<<endl;
        minimaxab_session.humanVsComputerMinimaxAB(0,1);
    }
    else if(choice==2)
    {
   //alpha beta
      AlphaBeta alphabeta_session;
      alphabeta_session.humanVsComputerAlphaBeta(0,1);
    }
    else if(choice==3)
    {
        AIgame aiGame_session;
        aiGame_session.MinmaxVsAlphabeta(0,1,1);
   }
    else if(choice==4)
    {
        AIgame aiGame_session;
        aiGame_session.MinmaxVsMinmax(0,1);
    }
    else if(choice==5)
    {
      AIgame aiGame_session;
      aiGame_session.AlphaBetaVsAlphaBeta(0,1);
      //be sure to set evalType in alphabeta module
    }
    else if(choice==6)
    {
        AIgame aiGame_session;
        aiGame_session.MinmaxVsAlphabeta(0,1,2);
    }
    else
    {
        cout<<"Invalid choice";
        exit(0);
    }*/

    switch(choice){

case 1:
    {
        MiniMaxAB minimaxab_session;
        minimaxab_session.clearGameBoard();
        cout<<"\nComputer's turn..."<<endl;
        minimaxab_session.humanVsComputerMinimaxAB(0,1);
        break;
    }

case 2:
    {
        AlphaBeta alphabeta_session;
        alphabeta_session.humanVsComputerAlphaBeta(0,1);
        break;
    }
case 3:
    {
        AIgame aiGame_session;
        aiGame_session.MinmaxVsAlphabeta(0,1,1);
    break;
    }

case 4:
    {
        AIgame aiGame_session;
    aiGame_session.MinmaxVsMinmax(0,1);
    break;
    }

case 5:
    {
        AIgame aiGame_session;
    aiGame_session.AlphaBetaVsAlphaBeta(0,1);
    break;
    }

case 6:
    {
        AIgame aiGame_session;
    aiGame_session.MinmaxVsAlphabeta(0,1,2);
    break;
    }

default:
    cout<<"Invalid choice";
    break;





    }












    return 0;
}
