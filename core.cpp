//All code is released to the public domain under the terms of [http://unlicense.org]

#include <string.h>
#include <stdio.h>
#include <stdlib.h>
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
    //northwest
    if((y < 6) && (x > 1) && (board[x-1][y+1] == -color)) {
        for(int i=0; (x-i-2 >= 0) && (y+i+2 < 8); i++) {
            if(!board[x-i-2][y+i+2]) {
                break;
            } else if(board[x-i-2][y+i+2] == color) {
                directions.push_back(std::make_pair<int, int>(7, (x-i-2)*8+(y+i+2)));
                break;
            }
        }
    }
    return directions;
}

//returns all moves for a players on the current board. Each pair has a coordinate in the form
//x*8+y, and a vector of pairs, each pair contains a direction and an endpoint in the form x*8+y
std::vector< std::pair<int, std::vector< std::pair<int, int> > > > get_moves(int board[][8], int color) {
    std::vector< std::pair<int, std::vector< std::pair<int, int> > > > moves;
    for(int i=0; i < 8; i++) {
        for(int j=0; j < 8; j++) {
            moves.push_back(std::make_pair<int, std::vector< std::pair<int, int> > >(i*8+j, get_directions(board, i, j, color)));
            if(!moves.back().second.size()) {
                moves.pop_back();
            }
        }
    }
    return moves;
}

//makes a move and flips the appropriate pieces
void make_move(int board[][8], int x, int y, int color, std::vector< std::pair<int, int> > directions) {
    for(auto it=directions.begin(); it != directions.end(); it++) {
        int i = x;
        int j = y;
        while((i != ((*it).second/8)) || (j != ((*it).second&7))) {
            board[i][j] = color;
            if(i < ((*it).second/8)) {
                i++;
            } else if((i > (*it).second/8)) {
                i--;
            }
            if(j < ((*it).second&7)) {
                j++;
            } else if(j > ((*it).second&7)) {
                j--;
            }
        }
    }
}

//undoes a move (needs directions data so it can unflip stuff)
void undo_move(int board[][8], int x, int y, int color, std::vector< std::pair<int, int> > directions) {
    for(auto it=directions.begin(); it != directions.end(); it++) {
        int i = x;
        int j = y;
        while((i != ((*it).second/8)) || (j != ((*it).second&7))) {
            board[i][j] = -color;
            if(i < ((*it).second/8)) {
                i++;
            } else if((i > (*it).second/8)) {
                i--;
            }
            if(j < ((*it).second&7)) {
                j++;
            } else if(j > ((*it).second&7)) {
                j--;
            }
        }
        board[i][j] = color;
    }
    board[x][y] = 0;
}

void print(int board[][8]) {
    for(int i=7; i >= 0; i--) {
        printf("%d ", i);
        for(int j=0; j < 8; j++) {
            if(!board[j][i]) {
                printf("-");
            } else if(board[j][i] == 1) {
                printf("O");
            } else {
                printf("X");
            }
        }
        printf("\n");
    }
    printf("  ");
    for(int i=0; i < 8; i++) {
        printf("%d", i);
    }
    printf("\n\n");
}

int score(int board[][8], int color) {
    int sum = 0;
    for(int i=0; i < 8; i++) {
        for(int j=0; j < 8; j++) {
            sum += board[i][j];
        }
    }
    return sum * color;
}

//Largely the same pseudocode from the negamax wikipedia article, but adapted for the rules of othello
int negamax_aux(int board[][8], int color, int depth, int alpha, int beta) {
    if(depth == 0) {
        return score(board, color);
    }
    std::vector< std::pair<int, std::vector< std::pair<int, int> > > > moves = get_moves(board, color);
    if(moves.size() == 0) {
        if(get_moves(board, -color).size() == 0) {
            return score(board, color);
        }
        int val = -negamax_aux(board, -color, depth-1, -beta, -alpha);
        if(val >= beta) {
            return val;
        }
        if(val > alpha) {
            alpha = val;
        }
    } else {
        for(auto it=moves.begin(); it != moves.end(); it++) {
            make_move(board, (*it).first/8, (*it).first&7, color, (*it).second);
            int val = -negamax_aux(board, -color, depth-1, -beta, -alpha);
            undo_move(board, (*it).first/8, (*it).first&7, color, (*it).second);
            if(val >= beta) {
                return val;
            }
            if(val > alpha) {
                alpha = val;
            }
        }
    }
    return alpha;
}

//parent function to negamax_aux, this function actually maintains the current best move
int negamax(int board[][8], int color, int depth) {
    int alpha = -65;
    int beta = 65;
    std::vector< std::pair<int, std::vector< std::pair<int, int> > > > moves = get_moves(board, color);
    int move = moves[0].first;
    for(auto it=moves.begin(); it != moves.end(); it++) {
        make_move(board, (*it).first/8, (*it).first&7, color, (*it).second);
        int val = -negamax_aux(board, -color, depth-1, -beta, -alpha);
        undo_move(board, (*it).first/8, (*it).first&7, color, (*it).second);
        if(val >= beta) {
            return (*it).first;
        }
        if(val > alpha) {
            alpha = val;
            move = (*it).first;
        }
    }
    return move;
}

//run with ./reversi [int] where int is the number of ply the AI searches deep. Default is 3 ply.
int main(int argc, char **argv) {
    int depth = 3;
    if(argc > 1) {
        depth = atol(argv[1]);
    }
    depth *= 2;

    int board[8][8];
    memset(board, 0, sizeof(board));
    board[3][3] = board[4][4] = -1;
    board[3][4] = board[4][3] = 1;
    int turn = -1;
    while(true) {
        print(board);
        std::vector< std::pair<int, std::vector< std::pair<int, int> > > > moves= get_moves(board, turn);
        printf("available moves: ");
        for(auto it=moves.begin(); it != moves.end(); it++) {
            printf("(%d, %d)  ", (*it).first/8, (*it).first%8);
        }
        printf("\n");
        if(moves.size() == 0) {
            turn = -turn;
            moves = get_moves(board, turn);
            if(moves.size() == 0) {
                printf("final score: %d\n", score(board, -1));
                return 0;
            }
        } else {
            int x, y;
            if(turn == -1) {
                scanf("%d %d", &x, &y);
                for(auto it=moves.begin(); it != moves.end(); it++) {
                    if(x*8+y == ((*it).first)) {
                        printf("chose: %d %d\n", x, y);
                        make_move(board, x, y, turn, (*it).second);
                        turn = -turn;
                        break;
                    }
                }
            } else {
                x = negamax(board, turn, depth);
                for(auto it=moves.begin(); it != moves.end(); it++) {
                    if(x == ((*it).first)) {
                        printf("chose: %d %d\n", x/8, x%8);
                        make_move(board, x/8, x%8, turn, (*it).second);
                        turn = -turn;
                        break;
                    }
                }
            }
        }
    }
    return 0;
}

//Music while coding:
//Willow Beats - (All of their music)
//https://soundcloud.com/willowbeats
//
//Peter Kusiv - Someone Told Me
//https://soundcloud.com/peer-kusiv/peer-kusiv-someone-told-me
