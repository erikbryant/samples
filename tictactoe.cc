//
// Copyright Erik Bryant (erikbryantology@gmail.com)
// GPLv2 http://www.gnu.org/licenses/gpl-2.0.html
//

#include <iostream>

using std::ostream;
using std::cout;
using std::endl;

class TicTacToe
{
public:
  enum CELLS { BLANK, X, O };

  TicTacToe()
  {
    startNewGame();
  }
  void startNewGame( void );
  bool hasWon( CELLS player );
  bool move( CELLS player, unsigned int row, unsigned int col );
  friend ostream &operator<<( ostream &os, const TicTacToe &t );

private:
  CELLS board[3][3];
};

//
// WARNING: This is called from the ctor.
// Don't do anything ctor-unsafe.
//
void TicTacToe::startNewGame( void )
{
  unsigned int row = 0;
  unsigned int col = 0;

  for ( row = 0; row <= 2; row++ )
    {
      for ( col = 0; col <= 2; col++ )
        {
          board[row][col] = BLANK;
        }
    }
}

bool TicTacToe::hasWon( CELLS player )
{
  unsigned int row = 0;
  unsigned int col = 0;

  // Check rows
  for ( row = 0; row <= 2; row++ )
    {
      if ( board[row][0] == player &&
           board[row][1] == player &&
           board[row][2] == player )
        {
          return true;
        }
    }

  // Check columns
  for ( col = 0; col <= 2; col++ )
    {
      if ( board[0][col] == player &&
           board[1][col] == player &&
           board[2][col] == player )
        {
          return true;
        }
    }

  // Check down-and-right diagonal
  if ( board[0][0] == player &&
       board[1][1] == player &&
       board[2][2] == player )
    {
      return true;
    }

  // Check up-and-right diagonal
  if ( board[2][0] == player &&
       board[1][1] == player &&
       board[0][2] == player )
    {
      return true;
    }

  return false;
}

bool TicTacToe::move( CELLS player, unsigned int row, unsigned int col )
{
  if ( player != BLANK && row <= 2 && col <= 2 )
    {
      if ( board[row][col] == BLANK )
        {
          board[row][col] = player;
          return true;
        }
    }

  return false;
}

ostream &operator<<( ostream &os, const TicTacToe &t )
{
  unsigned int row = 0;
  unsigned int col = 0;

  for ( row = 0; row <= 2; row++ )
    {
      for ( col = 0; col <= 2; col++ )
        {
          if ( t.board[row][col] == TicTacToe::BLANK )
            {
              os << "-";
            }
          else if ( t.board[row][col] == TicTacToe::X )
            {
              os << "X";
            }
          else if ( t.board[row][col] == TicTacToe::O )
            {
              os << "O";
            }
          else
            {
              os << "#";
            }
        }
      os << endl;
    }

  return os;
}

int main( int argc, char *argv[] )
{
  TicTacToe t;

  cout << t << endl;
  t.move( TicTacToe::X, 0, 0 );
  cout << t << endl;
  if ( t.hasWon( TicTacToe::X ) )
    {
      cout << "Congratulations! X has won the game." << endl;
      return 0;
    }

  t.move( TicTacToe::X, 1, 1 );
  cout << t << endl;
  if ( t.hasWon( TicTacToe::X ) )
    {
      cout << "Congratulations! X has won the game." << endl;
      return 0;
    }

  t.move( TicTacToe::X, 2, 2 );
  cout << t << endl;
  if ( t.hasWon( TicTacToe::X ) )
    {
      cout << "Congratulations! X has won the game." << endl;
      return 0;
    }

  return 0;
}
