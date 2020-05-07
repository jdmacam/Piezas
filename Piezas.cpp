#include "Piezas.h"
#include <vector>
/** CLASS Piezas
 * Class for representing a Piezas vertical board, which is roughly based
 * on the game "Connect Four" where pieces are placed in a column and
 * fall to the bottom of the column, or on top of other pieces already in
 * that column. For an illustration of the board, see:
 *  https://en.wikipedia.org/wiki/Connect_Four
 *
 * Board coordinates [row,col] should match with:
 * [2,0][2,1][2,2][2,3]
 * [1,0][1,1][1,2][1,3]
 * [0,0][0,1][0,2][0,3]
 * So that a piece dropped in column 2 should take [0,2] and the next one
 * dropped in column 2 should take [1,2].
**/


/**
 * Constructor sets an empty board (default 3 rows, 4 columns) and
 * specifies it is X's turn first
**/
Piezas::Piezas()
{
  //set size of the board
  board.resize(BOARD_ROWS);
  for(int i = 0; i < BOARD_ROWS; i++){
    board[i].resize(BOARD_COLS);
  }

  //set all spaces to blank
  for(int i = 0; i < BOARD_ROWS; i++){
    for(int j = 0; j < BOARD_COLS; j++){
      board[i][j] = Blank;
    }
  }

  //set X as first turn
  turn = X;
}

/**
 * Resets each board location to the Blank Piece value, with a board of the
 * same size as previously specified
**/
void Piezas::reset()
{
  //set all spaces to blank
  for(int i = 0; i < BOARD_ROWS; i++){
    for(int j = 0; j < BOARD_COLS; j++){
      board[i][j] = Blank;
    }
  }
}

/**
 * Places a piece of the current turn on the board, returns what
 * piece is placed, and toggles which Piece's turn it is. dropPiece does
 * NOT allow to place a piece in a location where a column is full.
 * In that case, placePiece returns Piece Blank value
 * Out of bounds coordinates return the Piece Invalid value
 * Trying to drop a piece where it cannot be placed loses the player's turn
**/
Piece Piezas::dropPiece(int column)
{
    Piece dropped = turn;
    //check if valid column
    if(column >= BOARD_COLS || column < 0){
        if(turn == X){
            turn = O;
        }
        else{
            turn = X;
        }
        return Invalid;
    }

    //check if column is full
    if(pieceAt(2,column) != Blank){ //a piece is at top row
        if(turn == X){
            turn = O;
        }
        else{
            turn = X;
        }
        return Blank;
    }

    //find appropriate spot in column, place piece
    for(int i = 0; i < BOARD_ROWS; i++){
      if(pieceAt(i,column) == Blank){
        board[i][column] = turn;
        break;
      }
    }

    if(turn == X){
        turn = O;
    }
    else{
        turn = X;
    }
    return dropped;
}

/**
 * Returns what piece is at the provided coordinates, or Blank if there
 * are no pieces there, or Invalid if the coordinates are out of bounds
**/
Piece Piezas::pieceAt(int row, int column)
{
    return board[row][column];
}

/**
 * Returns which Piece has won, if there is a winner, Invalid if the game
 * is not over, or Blank if the board is filled and no one has won ("tie").
 * For a game to be over, all locations on the board must be filled with X's
 * and O's (i.e. no remaining Blank spaces). The winner is which player has
 * the most adjacent pieces in a single line. Lines can go either vertically
 * or horizontally. If both X's and O's have the same max number of pieces in a
 * line, it is a tie.
**/
Piece Piezas::gameState()
{
    //check if game is over (any empty spaces)
    for(int i = 0; i < BOARD_COLS; i++){
        if(pieceAt(2,i) == Blank){
            return Invalid;
        }
    }

    //largest scores for each coressponding piece and coressponding direction
    int x_vert = 0;
    int x_hori = 0;
    int o_vert = 0;
    int o_hori = 0;
    int cur;

    //vertical X tally
    cur = 0;
    for(int i = 0; i < BOARD_COLS; i++){
        for(int j = 0; j < BOARD_ROWS; j++){
            if(board[j][i] == X){
                cur++;
            }
            else{
                if(cur > x_vert){
                    x_vert = cur;
                }
                cur = 0;
            }
        }
    }

    //vertical O tally
    cur = 0;
    for(int i = 0; i < BOARD_COLS; i++){
        for(int j = 0; j < BOARD_ROWS; j++){
            if(board[j][i] == O){
                cur++;
            }
            else{
                if(cur > o_vert){
                    o_vert = cur;
                }
                cur = 0;
            }
        }
    }

    //horizontal X tally
    cur = 0;
    for(int i = 0; i < BOARD_ROWS; i++){
        cur = 0;
        for(int j = 0; j < BOARD_COLS; j++){
            if(board[i][j] == X){
                cur++;
            }
            else{
                if(cur > x_hori){
                    x_hori = cur;
                }
                cur = 0;
            }
        }
    }

    //horizontal O tally
    cur = 0;
    for(int i = 0; i < BOARD_ROWS; i++){
        cur = 0;
        for(int j = 0; j < BOARD_COLS; j++){
            if(board[i][j] == O){
                cur++;
            }
            else{
                if(cur > o_hori){
                    o_hori = cur;
                }
                cur = 0;
            }
        }
    }

    //determine final tally for X and O
    int x_final;
    int o_final;
    //X
    if(x_vert >= x_hori){
        x_final = x_vert;
    }
    else{
        x_final = x_hori;
    }
    //O
    if(o_vert >= o_hori){
        o_final = o_vert;
    }
    else{
        o_final = o_hori;
    }

    Piece winner;
    if(x_final > o_final){
        winner = X;
    }
    else if(o_final > x_final){
        winner = O;
    }
    else{ //tie
        winner = Blank;
    }
    return winner;
}
