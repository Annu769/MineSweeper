#include "minesweeper.h"

int main()
{
  srand(time(0));
  MineSweeper ms;
  int input;
  cout<<"1. Noob \n2. Pro\n3. Ultra Pro\nChoose your  difficulty: ";
  do{
    cin>>input;
    if(input >3 || input < 0)
    {
      cout<<"\nWrong input, plaese choose between 1 - 3.\n";
    }
  }while(input >3 || input < 0);
  ms.play(input);
}