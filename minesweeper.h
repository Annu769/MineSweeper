//*************** MINESWEEPER GAME IN C++ *****************

#include <bits/stdc++.h>
#define MINE 'M'
#define UNOPENED_TILE '-'
#define BLANK_SPACE ' '
using namespace std;

class MineSweeper
{
private:
  int boardSize = 0;
  char board[100] [100];
  char displayBoard[100][100];
  int mines = 1;
  int tileOpenenCounter = 0;
  bool isGameOver = false;

public:
  void PlaceMines(int _rowInput, int _colInput)
{
  vector<pair<int, int>>mineLocations;
  for(int i = 0 ; i < boardSize; i++)
    {
      for(int j = 0; j < boardSize; j++)
        {
          mineLocations.push_back(make_pair(i,j));
        }
    }
  random_shuffle(mineLocations.begin(), mineLocations.end());
  for(int i = 0 ; i < mines; i++)
    {
      board[mineLocations[i].first][mineLocations[i].second] = MINE;
    }
    if(board[_rowInput][_colInput] == MINE)
    {
      board[_rowInput][_colInput] = '-';
    }
}
bool isInside(int _row, int _col, int _size)
{
  if(0 <= _row and _row <= _size && 0 <= _col && _col <= _size)
    {
    return true;
    }
  return false;
}
 int  calculateMines(int _row, int _col, int _size)
{
  int count = 0;
  int nextRow = 0;
  int nextCol = 0;
  for(int i = -1; i <= 1; i++)
    {
      for(int j = -1; j <= 1 ; j++)
        {
          nextRow = i + _row;
          nextCol = j + _col;
          if(isInside(nextRow, nextCol, _size) && board[nextRow][nextCol] == MINE)
          {
            count++;
          }
        }
    }
  return count;
}
void createBoard(int _difficulty, int rowInput, int colInput)
{
  boardSize = _difficulty + 7;
  mines = _difficulty  + 10;
  //mines = 4
  for(int i = 0; i < boardSize; i++)
    {
      for(int j = 0; j < boardSize; j++)
        {
          board[i][j] = UNOPENED_TILE;
          displayBoard[i][j] = UNOPENED_TILE;
          
        }
    }
  PlaceMines(rowInput, colInput);
  for(int i =0; i < boardSize; i++)
    {
      for(int j = 0; j < boardSize; j++)
        {
          if(board[i][j] != MINE)
          {
            board[i][j] = calculateMines(i, j, boardSize) + '0';
          }
        }
    }
}
void printCheatBoard()
{
  for(int i = 0 ; i < boardSize; i++)
    {
      cout<<i +1 << " ";
      if(i +1 < 10)
      {
        cout<<" ";
      }
      for(int j = 0; j < boardSize; j++)
        {
          cout<<"["<< board[i][j] <<"]";
        }
      cout<<endl;
    }
}
void printBoard()
{
  cout<<"   ";
  for(int i =0 ; i < boardSize; i++)
    {
      cout<<"  "<< i +1 <<" ";
      if(i+1 <10)
      {
        cout<<" ";
      }
    }
  cout<<endl;
  for(int i = 0; i < boardSize; i++)
    {
      cout<< i + 1 << " ";
      if(i +1 < 10)
      {
        cout<< " ";
      }
      for(int j = 0; j <boardSize; j++)
        {
          cout<<"[ "<< displayBoard[i][j] << " ]";
        }
      cout<<endl;
    }
}
bool checkwin()
{
  int maxMoves = (boardSize * boardSize) - mines;
  if((tileOpenenCounter == maxMoves))
  {
    cout<<"\n\n GAME WON!!!!!!\n\n";
    return true;
  }
  return false;
}
void blankSpaceTriggred(int _row, int _col)
{
  if(displayBoard[_row][_col] == UNOPENED_TILE)
  {
    int nextRow = 0;
    int nextCol = 0;

    if(board[_row][_col] == '0')
    {
      tileOpenenCounter++;
      displayBoard[_row][_col] = BLANK_SPACE;
      for(int i = -1; i <= 1; i++)
        {
          for(int j =-1; j<= 1; j++)
            {
              nextRow = i + _row;
              nextCol = j +_col;
              if(isInside(nextRow, nextCol, boardSize))
              {
                blankSpaceTriggred(nextRow, nextCol);
              }
            }
        }
    }
    else{
      displayBoard[_row][_col] = board[_row][_col];
      tileOpenenCounter++;
    }
  }
}
void userInputAction(int _row, int _col)
{
  if(displayBoard[_row][_col] == UNOPENED_TILE)
  {
    if(board[_row][_col] == '0')
    {
      blankSpaceTriggred(_row, _col);
    }
    else if(board[_row] [_col] == MINE)
    {
      cout<< "\n\n Oops, Stepped on a Mine.\n GAME OVER......"<<endl;
      isGameOver = true;
      return;
    }
    else
    {
      tileOpenenCounter++;
      displayBoard[_row][_col] = board[_row][_col];
    }
  }
  else{
    cout<<"Wrong Input, please re - enter. \n\n";
  }
}
void play(int input)
{
  int rowInput;
  int colInput;
  bool isBoardCreated = false;
  bool isPlayerWin = false;
  while(!isGameOver && !isPlayerWin)
    {
      cout<<"Enter Row number ";
      cin>>rowInput;
      cout<<"Enter Col Number ";
      cin>>colInput;
      if(!isBoardCreated)
      {
        createBoard(input, rowInput -1, colInput -1);
        cout<<"\n\n";
        isBoardCreated = true;
      }
      userInputAction(rowInput -1, colInput -1);
      printBoard();
      isPlayerWin = checkwin();
    }
}
};
