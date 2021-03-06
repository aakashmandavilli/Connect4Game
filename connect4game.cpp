#include <cmath>
using namespace std;
#include "connect4game.cpp"

namespace AI {
class Connect4Game {
    public:
        int player1Win=0;
        int Player2Win=0;
        /**
        * Constructor creates a board game, which is a n x m grid
        * starting with empty values
        */
        Connect4Game ();

        /**
        * Returns count of adjacent reds
        */
        int getConnectedReds ();

        /**
        * Returns count of adjacent reds
        */
        int getConnectedBlacks ();

        /**
        * checks if board at (row,col) has any pieces that match
        * supplied playerType parameter
        * Input: playerType, row, and col
        * playerType must = 1 for red, or = -1 for black
        * Returns: True if there is any match, else false
        **/
        bool hasSurroundingPieces(int, int, int);

        /**
        * Returns count of all reds and black in board
        */
        int getTotalPieces ();

        /**
        * Mutator function that drops a piece onto the board of a specified column
        * piece: 1 = red, -1 = black
        * col: column in which to drop the piece
        * Invariant: must be a valid piece and column
        */
        int dropPiece (int, int);

        /**
        * Mutator function that removes top piece from column
        * Input: int column
        * Post condition: piece from column is removed
        */
        void removeTopPiece (int);

		/**
		* Drop a player piece in random column
		* Input: integer where 1 = red player, -1 = black player
		* Pre: board must have a slot for player's piece to occupy
		* Post condition: another player piece is added on board
		*/
        void makeRandomMove (int);

        /**
       * Increment depth of board.
       * Postcondition: current_depth is incremented by 1.
       */
       void setDepthPlayed(int);

       /**
       * Get current depth of board. This number is used to
       * decide if  game state has been played to a far enough depth
       * E.g. if we've played enough turns
       * Return: current number of turns played
       */
       int getDepthPlayed();

       /**
       * Return vector of integers columns of which a piece may be dropped
       * in current game state.
       */
       vector<int> getOpenColumns();

       /**
      * Return the value at given row and col
      * Red = 1, black = -1
      */
      int getSlotValue(int /*row*/, int /*col*/);

       /**
       * Checks if connect 4 by any piece.
       * Return true if there is winning player
       */
       bool checkWin(Connect4Game /*unused*/);

		/**
		* clear board of all pieces
		*/
      void clearBoard();

      /**
      * printboard
      */
      void printBoard ();

      /**
      * Mutator function to set board member variable
      * Input: int array representing new board
      * PostCondtion: this member's board is changed to match the input array
      */
      void setBoard(int[6][7]);

      /**
      * Function to check if column is valid for drop piece
      * Input: game state, col
      * Output: returns true if column is open
      */
      bool checkValidMove(Connect4Game,int /*column*/);

      /**
      * Scorees board
      * Input: game state, row, col
      * Output: returns weighted scoring on grid
      */
      int getScore(Connect4Game &,int , int);

      /**
 		* Evaluation A function for present state of board. Unused.
 		*/
 		int evalA(Connect4Game,int);

 		/**
 		* Evaluation B (Eval 2) function for present state of board
      * used by Alphabeta search
      * Input: playerType (1 = red, -1 = black), col is column to evaluate
      * Output: Returns a scoring based on connectedness and column weight
      * Returns highest score if there is a connect 4
 		*/
 		int evalBAlphaBeta(int /*playerType*/, int /*col*/);

      /**
 		* Evaluation B (Eval 2) function for present state of board used by minmaxab.
      * Input: game state to evaluate, player piece to play
      * Output: Returns a scoring based on centrally weighted grid
 		*/
 		int evalBMinmax(Connect4Game /*board*/,int /* piece*/);
        int eval2MinMax(Connect4Game,int);
 		/**
 		* Evaluation C (eval 1) function for present state of board
      * using minimasab search
      * Input: game state to evaluate, player piece to play
      * Output: Returns a scoring based on centrally weighted grid
 		*/
 		int evalCMinmax(Connect4Game,int);

      /**
  		* Evaluation C (eval 1) function for present state of board
       * using alphabeta search
       * Input: playerType (1 = red, -1 = black), col is column to evaluate
       * Output: Returns a scoring based on connectedness and column weight
       * Returns highest score if there is a connect 4
 	 	*/
 		int evalCAlphaBeta(int,int);

        int curCol;
	//private:
        const static int ROWS = 6;
        const static int COLS = 7;
        vector<vector<int>> board;
        int current_depth; // used to count current depth of board state


};
namespace AI {

/**
* Constructor creates a board game, which is a n x m grid
* starting with empty values
*/
Connect4Game() {
   // initialize any necessary members
   vector<vector<int>> bd(this->ROWS, vector<int>(this->COLS, 0));
   this->board = bd;
   this->current_depth = 0;
}

/**
* Returns count of adjacent reds
*/
int getConnectedReds() {
   int count = 0;
   for (int r = 0; r < board.size (); r++) {
      for (int c = 0; c < board[0].size (); c++){
         //hardcoded red = 1
         if (board.at(r).at(c) == 1 && hasSurroundingPieces(1,r,c)){
             count += 1;
         }
      }
   }
   return count;
}

/**
* Returns count of adjacent blacks
*/
int getConnectedBlacks() {
   int count = 0;
   for (int r = 0; r < board.size (); r++) {
         for (int c = 0; c < board[0].size (); c++){
             //hardcoded black = -1
             if (board.at(r).at(c) == -1 && hasSurroundingPieces(-1,r,c)){
                 count += 1;
 	        }
         }
     }
   return count;
}

/**
* Returns true if adjacent to any red
*/
bool hasSurroundingPieces(int playerType, int row, int col){
    //Check straight up down
    if(col >=0 && col < this->COLS) {
      if(row >= 0 && row < this->ROWS - 1) {
          //check row above
          if (board.at(row+1).at(col) == playerType) {
              return true;
          }
      }

      if(row > 0 && row < this->ROWS) {
          //check row below
          if (board.at(row-1).at(col) == playerType) {
              return true;
          }
      }
    }

    //Check straight left right
    if (row >= 0 && row < this->ROWS){
        if(col >= 0 && col < this->COLS - 1) {
          //check col to right
          if (board.at(row).at(col+1) == playerType) {
              return true;
          }
        }

        if(col > 0 && col < this->COLS) {
          //check col to left
          if (board.at(row).at(col-1) == playerType) {
              return true;
          }
        }
    }

    //Check diagonal upper & lower right
    if(col >=0 && col < this->COLS-1) {
      if(row >= 0 && row < this->ROWS - 1) {
          //check upper right
          if (board.at(row+1).at(col+1) == playerType) {
              return true;
          }
      }

      if(row > 0 && row < this->ROWS) {
          //check lower right
          if (board.at(row-1).at(col+1) == playerType) {
              return true;
          }
      }
    }


    //Check diagonal upper and lower left
    if(col >0 && col < this->COLS) {
      if(row >= 0 && row < this->ROWS - 1) {
          //check upper right
          if (board.at(row+1).at(col-1) == playerType) {
              return true;
          }
      }

      if(row > 0 && row < this->ROWS) {
          //check lower right
          if (board.at(row-1).at(col-1) == playerType) {
              return true;
          }
      }
    }
  return false;
}

/**
* Returns count of all reds and black in board
*/
int getTotalPieces()
{
    int count = 0;
    for (int r = 0; r > board.size (); r++) {
        for (int c = 0; c < board[0].size (); c++){
            if (board.at (r).at (c) != 0) {
              count += 1;
            }
        }
    }
  return count;
}

/**
* Mutator function that drops a piece onto the board of a specified column
*/
int dropPiece (int piece, int col)
{
    int row = 0;
    if ((piece == -1 || piece == 1) && col >= 0 && col < this->COLS) {
        // 1) find lowest empty slot in the column
        while (row < this->ROWS && board.at(row).at(col) != 0) {
            row += 1;
        }

        // 2) insert piece into slot if it's empty
        if (row < this->ROWS && board.at(row).at(col) == 0) {
            board.at(row).at(col) = piece;
        }
    }
}

void removeTopPiece(int col) {

    int row = 0;
    if (col >= 0 && col < this->COLS) {
        // 1) find lowest empty slot in the column
        while (row < this->ROWS && board.at(row).at(col) != 0) {
            row += 1;
        }
        // 2) empty the slot
        row -= 1;
        if (row >= 0 && row < this->ROWS && board.at(row).at(col) != 0) {
            board.at(row).at(col) = 0;
        }
    }
}


/**
* Drop a player piece in random column
*/
void makeRandomMove(int player)
{
    if (player == 1 || player == -1) {
        int col = rand()% this->COLS;
       this->dropPiece(player, col);
    }

}

/**
* Increment depth of board.
*/

void setDepthPlayed(int new_depth) {
   this->current_depth = new_depth;
}

/**
* Get current depth of board. This number is used to
* decide if game state has been played to a far enough depth
*/
int getDepthPlayed() {
   return this->current_depth;
}


/**
* Get all open columns by checking if at topmost row
* is empty
*/
vector<int> getOpenColumns(){
   vector<int> playableCols;
   int row = this->ROWS-1; //topmost row
   for (int col = 0; col < this->COLS; col++) {
      if (board.at(row).at(col) == 0) {
         playableCols.push_back(col);
      }
   }
   return playableCols;
}

/**
* Return the value at given row and col
*/
int getSlotValue(int row, int col) {
   return this->board.at(row).at(col);
}

void setBoard(int a[6][7])
{
   int i,j,val;
   for(i=0;i<6;i++)
   for(j=0;j<7;j++)
   {
       val=a[i][j];
       board.at(i).at(j)=val;
   }
}

bool checkWin(Connect4Game board)
{
    int WIN=4;
    bool win;
  {
  for (int c = 0; c < 7; c++)
  for (int r = 0; r < 6; r++)
  if (getSlotValue(r,c) == 1)
  {
    // Check row
    int count = 0;
    for (int d = 0; d < WIN; d++)
       if ((r+d < ROWS) &&
          (getSlotValue(r+d,c) == 1)) count++;
    if (count == WIN)
    {
        player1Win=1;
        return true;

    }
    // Check column
    player1Win=0;
    count = 0;
    for (int d = 0; d < WIN; d++)
       if ((c+d < COLS) &&
          (getSlotValue(r,c+d) == 1)) count++;
    if (count == WIN)
    {
        player1Win=1;
        return true;
    }


    // Check first diagonal
    count = 0;
    player1Win=0;
    for (int d = 0; d < WIN; d++)
       if ((r+d < ROWS) && (c+d < COLS) &&
          (getSlotValue(r+d,c+d) == 1)) count++;
    if (count == WIN)
    {
        player1Win=1;
        return true;
    }

    // Check second diagonal
    count = 0;
    player1Win=0;
    for (int d = 0; d < WIN; d++)
       if ((r-d >= 0) && (c+d < COLS) &&
          (getSlotValue(r-d,c+d) == 1)) count++;
    if (count == WIN)
    {
        player1Win=1;
        return true;
    }
   }
   }
   {
   for (int c = 0; c < 7; c++)
   for (int r = 0; r < 6; r++)
   if (getSlotValue(r,c) == -1)
   {
    // Check row
    int count = 0;
    for (int d = 0; d < WIN; d++)
       if ((r+d < ROWS) &&
          (getSlotValue(r+d,c) == -1)) count++;
    if (count == WIN)
    {
        Player2Win=1;
        return true;
    }
    // Check column
    count = 0;
    for (int d = 0; d < WIN; d++)
       if ((c+d < COLS) &&
          (getSlotValue(r,c+d) == -1)) count++;
    if (count == WIN)
    {
        Player2Win=1;
        return true;
    }

    // Check first diagonal
    count = 0;
    for (int d = 0; d < WIN; d++)
       if ((r+d < ROWS) && (c+d < COLS) &&
          (getSlotValue(r+d,c+d) == -1)) count++;
    if (count == WIN)
    {
        Player2Win=1;
        return true;
    }
    // Check second diagonal
    count = 0;
    for (int d = 0; d < WIN; d++)
       if ((r-d >= 0) && (c+d < COLS) &&
          (getSlotValue(r-d,c+d) == -1)) count++;
   if (count == WIN)
   {
       Player2Win=1;
       return true;
   }

   }
   }
   return false;
}

bool checkValidMove(Connect4Game board,int column)
{
    int i,count2=0;
      if(column<0 || column>6)
          return false;

      for(i=0;i<6;i++)
      {
          if(getSlotValue(i,column)==1 || getSlotValue(i,column)==-1)
              count2++;
      }
      if(count2==6)
        return false;
      else
        return true;
}

/**
* Clear pieces from board
*/
void clearBoard()
{
    vector<vector<int>> bd(this->ROWS, vector<int>(this->COLS, 0));
    this->board = bd;
    this->current_depth = 0;
}

/**
* Prints board game
*/
void printBoard ()
{
    cout << "r\\c ";
    for (int c = 0; c < board[0].size (); c++) {
        cout << c << "  ";
    }

    cout << endl;
    for (int r = board.size () - 1; r >= 0; r--) {
        cout << r << "   ";

        for (int c = 0; c < board[0].size (); c++) {
            switch (board.at(r).at(c))
              {
              case -1:
        	cout << "B  ";
        	break;
              case 0:
        	cout << "_  ";
        	break;
              case 1:
        	cout << "R  ";
        	break;
              default:
        	break;
          }
    }
    cout << '\n';
  }
}

/**
* Evaluation A function for present state of board
*/
int evalA(Connect4Game board,int peice)
{
   int value=0;
       int evaluationTable[6][7] = {{3, 4, 5, 7, 5, 4, 3},
                                 {4, 6, 8, 10,8, 6, 4},
                                 {5, 8, 11,13,11,8, 5},
                                 {5, 8, 11,13,11,8, 5},
                                 {4, 6, 8, 10,8, 6, 4},
                                 {3, 4, 5, 7, 5, 4, 3}};

        int utility = 0;
        int sum = 0;
        for (int i = 0; i < 6; i++)
            for (int j = 0; j <7; j++)
                if (board.getSlotValue(i,j) == 1)
                    sum += evaluationTable[i][j];
                else if (board.getSlotValue(i,j) == -1)
                    sum -= evaluationTable[i][j];
    value=utility+sum;
    return value;
}

/**
* Evaluation B function for present state of board
* Returns 'goodness' of playing a column
*/
int evalBAlphaBeta(int playerType, int col) {
    //playerType = 1;

    //test if connect4
    this->dropPiece(playerType,col);
    if(this->checkWin(*this)){
        if(player1Win==1)
        return 1000; //highest weight
        else return -1000;
    }
    //return 0;
    this->removeTopPiece(col);

   //column 3 is the best col to start with
   int middleCol = (this->COLS - 1) / 2;

   //get first nonempty row at column
   int row = 0;
   while (row < this->ROWS && this->board.at(row).at(col) != 0) {
      row++;
   }
   //check if inserting piece at row will make a connection
    // score 1 for any surrounding pieces
   int surroundingPieces = 0;

   // below
   if (row > 0) {
     if(this->getSlotValue(row-1,col) == playerType) {
        surroundingPieces++;
     }
   }

    // upper right
    if((row < this->ROWS - 1) && (col < this->COLS - 1)) {
        if(this->getSlotValue(row+1,col+1) == playerType){
            surroundingPieces++;
        }
    }

    // upper left
    if((row < this->ROWS - 1) && (col > 0)) {
        if(this->getSlotValue(row+1,col-1) == playerType){
            surroundingPieces++;
        }
    }

    // right
    if((row < this->ROWS) && (col < this->COLS - 1)) {
        if(this->getSlotValue(row,col+1) == playerType){
            surroundingPieces++;
        }
    }

    // left
    if((row < this->ROWS) && (col > 0)) {
        if(this->getSlotValue(row,col-1) == playerType){
            surroundingPieces++;
        }
    }

    // lower right
    if((row > 0) && (col < this->COLS - 1)) {
        if(this->getSlotValue(row-1,col+1) == playerType){
            surroundingPieces++;
        }
    }

    // lower left
    if((row > 0) && (col > 0)) {
        if(this->getSlotValue(row-1,col-1) == playerType){
            surroundingPieces++;
        }
    }

   // add utility of intermediate values
   int util =  (middleCol - abs(middleCol - col))*3 + surroundingPieces;

   return util;
}

int  getScore(Connect4Game &board,int row, int col)
{
    int score = 0,ROWS=6,COLS=7;
    bool unblocked = true;
    int count1 = 0;
    //int r, c;
    if (row < ROWS-3)
    {
    //check up
    unblocked = true;
    count1 = 0;
        for (int r=row; r<row+4; r++)
        {
            if (board.getSlotValue(r,col) == -1)
            {
            unblocked = false;
            }
            if (board.getSlotValue(r,col) == 1)
            {
            count1 ++;
            }
        }
        if (unblocked == true)
        {
            score = score + (count1*count1*count1*count1);
        }

        if (col < COLS-3)
            {
            //check up and to the right
            unblocked = true;
            count1 = 0;
            for (int r=row, c=col; r<row+4; r++, c++)
            {
                if (board.getSlotValue(r,c) == -1)
                {
                unblocked = false;
                }
                if (board.getSlotValue(r,c) == 1)
                {
                count1 ++;
                }
            }
                if (unblocked == true)
                {
                score = score + (count1*count1*count1*count1);
                }
            }
    }

    if (col < COLS-3)
    {
        //check right
        unblocked = true;
        count1 = 0;
        for (int c=col; c<col+4; c++)
        {
            if (board.getSlotValue(row,c) == -1)
            {
                unblocked = false;
            }
            if (board.getSlotValue(row,c) == 1)
            {
                count1 ++;
            }
        }
        if (unblocked == true)
        {
            score = score + (count1*count1*count1*count1);
        }

        if (row > 2)
        {
        //check down and to the right
        unblocked = true;
        count1 = 0;
        for (int r=row, c=col; c<col+4; r--, c++)
        {
            if (board.getSlotValue(r,c) == -1)
            {
                unblocked = false;
            }
            if (board.getSlotValue(r,c) == 1)
            {
                count1 ++;
            }
        }
        if (unblocked == true)
        {
            score = score + (count1*count1*count1*count1);
        }
        }
    }
 return score;
 }


int evalCMinmax(Connect4Game board,int peice)
{
        int score = 0;
        if(this->checkWin(*this)){
        return 1000; //highest weight
        }
        for (int r= 0; r < 6; r++)
            {
                if (r <= 6-4)
                {
                    for (int c = 0; c < 7; c++)
                    {
                        score += getScore(board,r,c);
                    }
                }
                else
                {
                    for (int c = 0; c <= 7-4; c++)
                    {
                        score += getScore(board,r,c);
                    }
                }
            }

 return score;

}
int eval2MinMax(Connect4Game board,int piece)
{


}
int evalCAlphaBeta(int playerType, int col)
{
    Connect4Game tempBoard;
    tempBoard.board=this->board;
    tempBoard.dropPiece(playerType,col);
    if(this->checkWin(*this)){
        return 1000; //highest weight
        }
            int score = 0;
        for (int r= 0; r < 6; r++)
            {
                if (r <= 6-4)
                {
                    for (int c = 0; c < 7; c++)
                    {
                        score += getScore(tempBoard,r,c);
                    }
                }
                else
                {
                    for (int c = 0; c <= 7-4; c++)
                    {
                        score += getScore(tempBoard,r,c);
                    }
                }
            }

 return score;
}

int evalBMinmax(Connect4Game board,int peice)
{
    int ROWS=6;
    int COLS=7;
    int playerType=peice;

    if(checkWin(board)==true)
    {
        if(player1Win==1)
        return 1000;
        else return -1000;
    }
        //return 0;
      //column 3 is the best col to start with
   int middleCol = (COLS - 1) / 2;

   //get first nonempty row at column
   int row = 0;
   int col=board.curCol;
   while (row < ROWS && board.getSlotValue(row,col) != 0) {

      row++;
   }

   //check if inserting piece at row will make a connection
    // score 1 for any surrounding pieces
   int surroundingPieces = 0;
    // upper right
    if(row < ROWS - 1 && col < COLS - 1) {
        if(board.getSlotValue(row+1,col+1) == playerType){
            surroundingPieces++;
        }
    }
    // upper left
    if(row < ROWS - 1 && col > 0) {
        if(board.getSlotValue(row+1,col-1) == playerType){
            surroundingPieces++;
        }
    }
    // right
    if(row < ROWS && col < COLS - 1) {
        if(board.getSlotValue(row,col+1) == playerType){
            surroundingPieces++;
        }
    }
    // left
    if(row < ROWS && col > 0) {
        if(board.getSlotValue(row,col-1) == playerType){
            surroundingPieces++;
        }
    }
    // lower right
    if(row > 0 && col < COLS - 1) {
        if(board.getSlotValue(row-1,col+1) == playerType){
            surroundingPieces++;
        }
    }
    // lower left
    if(row > 0 && col > 0) {
        if(board.getSlotValue(row-1,col-1) == playerType){
            surroundingPieces++;
        }
    }
   // add utility of intermediate values
   int util =  (middleCol - abs(middleCol - col))*3 + surroundingPieces;//doubt
   return util;

}


}// end namespace AI
