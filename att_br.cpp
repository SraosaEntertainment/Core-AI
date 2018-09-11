#include <vector>
#include <utility>

//returns a pair <direction, coordinate> where direction is North, Northeast, etc (clockwise)
//and coordinate is in the form x*8 + y
std::vector< std::pair<int, int> > get_directions(int board[][8], int x, int y, int color) {
    std::vector< std::pair<int, int> > directions;
    if(board[x][y]) {
        return directions;
    }
    //north
    if((y < 6) && (board[x][y+1] == -color)) {
        for(int i=y+2; i < 8; i++) {
            if(!board[x][i]) {
                break;
            } else if(board[x][i] == color) {
                directions.push_back(std::make_pair<int, int>(0, x*8+i));
                break;
            }
        }
    }
    //northeast
    if((y < 6) && (x < 6) && (board[x+1][y+1] == -color)) {
        for(int i=0; (x+i+2 < 8) && (y+i+2 < 8); i++) {
            if(!board[x+i+2][y+i+2]) {
                break;
            } else if(board[x+i+2][y+i+2] == color) {
                directions.push_back(std::make_pair<int, int>(1, (x+i+2)*8+(y+i+2)));
                break;
            }
        }
    }
    //east
    if((x < 6) && (board[x+1][y] == -color)) {
        for(int i=x+2; i < 8; i++) {
            if(!board[i][y]) {
                break;
            } else if(board[i][y] == color) {
                directions.push_back(std::make_pair<int, int>(2, i*8+y));
                break;
            }
        }
    }
    //southeast
    if((y > 1) && (x < 6) && (board[x+1][y-1] == -color)) {
        for(int i=0; (x+i+2 < 8) && (y-i-2 >= 0); i++) {
            if(!board[x+i+2][y-i-2]) {
                break;
            } else if(board[x+i+2][y-i-2] == color) {
                directions.push_back(std::make_pair<int, int>(3, (x+i+2)*8+(y-i-2)));
                break;
            }
        }
    }
    //south
    if((y > 1) && (board[x][y-1] == -color)) {
        for(int i=y-2; i >= 0; i--) {
            if(!board[x][i]) {
                break;
            } else if(board[x][i] == color) {
                directions.push_back(std::make_pair<int, int>(4, x*8+i));
                break;
            }
        }
    }
    //southwest
    if((y > 1) && (x > 1) && (board[x-1][y-1] == -color)) {
        for(int i=0; (x-i-2 >= 0) && (y-i-2 >= 0); i++) {
            if(!board[x-i-2][y-i-2]) {
                break;
            } else if(board[x-i-2][y-i-2] == color) {
                directions.push_back(std::make_pair<int, int>(5, (x-i-2)*8+(y-i-2)));
                break;
            }
        }
    }

	int validp (int move) {
	  if ((move >= 11) && (move <= 88) && (move%10 >= 1) && (move%10 <= 8))
	     return 1;
	  else return 0;
	}


	/* findbracketingpiece is called from wouldflip (below).
	   findbracketingpiece starts from a *square* that is occupied
	   by a *player*'s opponent, moves in a direction, *dir*, past
	   all opponent pieces, until a square occupied by the *player*
	   is found. If a square occupied by *player* is not found before
	   hitting an EMPTY or OUTER square, then 0 is returned (i.e., no
	   bracketing piece found). For example, if the current board is

	         1 2 3 4 5 6 7 8
	     10  . . . . . . . .
	     20  . . . . . . . .
	     30  . . . . . . . .
	     40  . . b b b . . .
	     50  . . w w w b . .
	     60  . . . . . w . .
	     70  . . . . . . . .
	     80  . . . . . . . .

	   then findbracketingpiece(66, BLACK, board, -11) will return 44
	        findbracketingpiece(53, BLACK, board, 1) will return 56
	        findbracketingpiece(55, BLACK, board, -9) will return 0

	*/


	int findbracketingpiece(int square, int player, int * board, int dir) {
	  while (board[square] == opponent(player)) square = square + dir;
	  if (board[square] == player) return square;
	  else return 0;
	}

	/* wouldflip is called by legalmove (below). Give a *move* (square)
	   to which a player is considering moving, wouldflip returns
	   the square that brackets opponent pieces (along with the sqaure
	   under consideration, or 0 if no such bracketing square exists
	*/

	int wouldflip (int move, int player, int * board, int dir) {
	  int c;
	  c = move + dir;
	  if (board[c] == opponent(player))
	     return findbracketingpiece(c+dir, player, board, dir);
	  else return 0;
	}


	/* A "legal" move is a valid move, but it is also a move/location
	  that will bracket a sequence of the opposing player's pieces,
	  thus flipping at least one opponent piece. legalp considers a
	  move/square and seaches in all directions for at least one bracketing
	  square. The function returns 1 if at least one bracketing square
	  is found, and 0 otherwise.
	*/

	int legalp (int move, int player, int * board) {
	  int i;
	  if (!validp(move)) return 0;
	  if (board[move]==EMPTY) {
	    i=0;
	    while (i<=7 && !wouldflip(move, player, board, ALLDIRECTIONS[i])) i++;
	    if (i==8) return 0; else return 1;
	  }
	  else return 0;
	}
    //west
    if((x > 1) && (board[x-1][y] == -color)) {
        for(int i=x-2; i >= 0; i--) {
            if(!board[i][y]) {
                break;
            } else if(board[i][y] == color) {
                directions.push_back(std::make_pair<int, int>(6, i*8+y));
                break;
            }
        }
    }