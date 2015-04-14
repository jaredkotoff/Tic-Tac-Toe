#include "board.h"
#include "player.h"
#include <iostream>
#include <string>
#include <stdlib.h>
#include <vector>
using namespace std;


void gameLoop(Board &current_game, Player &player1, Player &player2){
    int winner = 0;
    int move=-1;
    
    while(!current_game.win()){
        if(player1.piece == "X"){
            while(!current_game.validateMove(move)){
                current_game.print();
                current_game.printMoves();
                cout << endl << "Player 1: Select cell: ";
                cin >> move;
            }
            current_game.insertMove(player1.team, move);
            move = -1;
            if(current_game.win()){
                winner = 1;
                break;
            }
            if(player2.ishuman){
                while(!current_game.validateMove(move)){
                    current_game.print();
                    current_game.printMoves();
                    cout << endl << "Player 2: Select cell: ";
                    cin >> move;
                }
                current_game.insertMove(player2.team, move);
                move = -1;
            }else{
                //current_game.insertMove(player2.team, player2.getAIMove(current_game));
            }
            if(current_game.win()){
                winner = 2;
                break;
            }
        }else{
            if(player2.ishuman){
                while(!current_game.validateMove(move)){
                    current_game.print();
                    current_game.printMoves();
                    cout << endl << "Player 2: Select cell: ";
                    cin >> move;
                }
                current_game.insertMove(player2.team, move);
                move = -1;
            }else{
                //current_game.insertMove(player1.team, player1.getAIMove(current_game));
            }
            if(current_game.win()){
                winner = 2;
                break;
            }
            while(!current_game.validateMove(move)){
                current_game.print();
                current_game.printMoves();
                cout << endl << "Player 1: Select cell: ";
                cin >> move;
            }
            current_game.insertMove(player1.team, move);
            move = -1;
            if(current_game.win()){
                winner = 1;
                break;
            }
        }
    }
    current_game.print();
    if(player1.team == winner){
        cout << endl  << "Player 1 won.";
    }else{
        cout << endl << "Player 2 won.";
    }
}

string oppositePiece(string piece){
    if(piece == "X"){
        return "O";
    }
    return "X";
}

int main(){
  int board_size = 3;
  int humans = 1;
  string player = "X";
  cout << "Pick the size of the grid (default = 3): ";
  cin >> board_size;
  Board board(board_size); //initialize a new board
  board.print();
  cout << endl << "1 or 2 human players? ";
  cin >> humans;
  if(humans == 1){
      cout << endl << "X or O (X moves first): ";
      cin >> player;
      player = toupper(player[0]);
      Player human(player); //initializes human player to their piece
      cout << "You are " << human.convertToPiece();
      AI ai(oppositePiece(human.piece)); //initializes ai player to opposite piece
      cout << endl << "AI is " << ai.piece; 
      gameLoop(board, human, ai); //game logic within the game is done here
  }else if(humans == 2){
      cout << endl << "Player 1: X or O (X moves first): ";
      cin >> player;
      player = toupper(player[0]);
      Player human1(player); //initializes human player to their piece
      Player human2(oppositePiece(human1.piece)); //initializes player 2 to opposite piece
      cout << endl << "Player 1 is: " << human1.piece;
      cout << endl << "Player 2 is: " << human2.piece; 
      gameLoop(board, human1, human2); //game logic within the game is done here   
  }
  return 0;
}