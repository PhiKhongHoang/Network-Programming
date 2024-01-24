#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>

int testPosition(int column, int line, int board[8][8], int gamer)
{
    if(column >= 0 && column < 8 && line >= 0 && line < 8)   // IF POSITION VALIDATES
    {
        if(gamer == 1)
        {
            if(board[line][column] >= 7 && board[line][column] <= 12) // PIECES GAMER 2
            {
                board[line][column] *= -1;
                return 1;
            }
            else if(board[line][column] == 13) // EMPTY
            {
                board[line][column] *= -1;
                return 0;
            }

        }
        else if(gamer == 2)
        {
            if(board[line][column] >= 1 && board[line][column] <= 6) // PIECES GAMER 1
            {
                board[line][column] *= -1;
                return 1;
            }
            else if(board[line][column] == 13)   // EMPTY
            {
                board[line][column] *= -1;
                return 0;
            }
        }
    }
    return 1;
}

void testTower(int column_ori, int line_ori, int board[8][8], int gamer)
{
    int line, column, test;
    // UP
    line = line_ori - 1;
    test = 0;
    while(line >= 0 && test == 0)
    {
        test = testPosition(column_ori, line, board, gamer);
        line--;
    }

    // DOWN
    line = line_ori + 1;
    test = 0;
    while(line < 8 && test == 0)
    {
        test = testPosition(column_ori, line, board, gamer);
        line++;
    }

    // LEFT
    column = column_ori - 1;
    test = 0;
    while(column >= 0 && test == 0)
    {
        test = testPosition(column, line_ori, board, gamer);
        column--;
    }

    // RIGHT
    column = column_ori + 1;
    test = 0;
    while(column < 8 && test == 0)
    {
        test = testPosition(column, line_ori, board, gamer);
        column++;
    }
}

void testHorse(int column_ori, int line_ori, int board[8][8], int gamer)
{
    testPosition(column_ori - 1, line_ori - 2, board, gamer); // UP LEFT
    testPosition(column_ori - 1, line_ori + 2, board, gamer); // DOWN LEFT
    testPosition(column_ori + 1, line_ori - 2, board, gamer); // UP RIGHT
    testPosition(column_ori + 1, line_ori + 2, board, gamer); // DOWN RIGHT
    testPosition(column_ori - 2, line_ori - 1, board, gamer); // LEFT UP
    testPosition(column_ori - 2, line_ori + 1, board, gamer); // LEFT DOWN
    testPosition(column_ori + 2, line_ori - 1, board, gamer); // RIGHT UP
    testPosition(column_ori + 2, line_ori + 1, board, gamer); // RIGHT DOWN
}

void testBispe(int column_ori, int line_ori, int board[8][8], int gamer)
{
    int line, column, test;
    // UP RIGHT
    line = line_ori - 1;
    column = column_ori + 1;
    test = 0;
    while(line >= 0 && column < 8 && test == 0)
    {
        test = testPosition(column, line, board, gamer);
        line--;
        column++;
    }

    // UP LEFT
    line = line_ori - 1;
    column = column_ori - 1;
    test = 0;
    while(line >= 0 && column >= 0 && test == 0)
    {
        test = testPosition(column, line, board, gamer);
        line--;
        column--;
    }

    // DOWN LEFT
    line = line_ori + 1;
    column = column_ori - 1;
    test = 0;
    while(line < 8 && column >= 0 && test == 0)
    {
        test = testPosition(column, line, board, gamer);
        line++;
        column--;
    }

    // DOWN RIGHT
    line = line_ori + 1;
    column = column_ori + 1;
    test = 0;
    while(line < 8 && column < 8 && test == 0)
    {
        test = testPosition(column, line, board, gamer);
        line++;
        column++;
    }
}

void testQueen(int column_ori, int line_ori, int board[8][8], int gamer)
{
    testTower(column_ori, line_ori, board, gamer);
    testBispe(column_ori, line_ori, board, gamer);
}

void testKing(int column_ori, int line_ori, int board[8][8], int gamer)
{
    testPosition(column_ori, line_ori - 1, board, gamer);     // UP
    testPosition(column_ori, line_ori + 1, board, gamer);     // DOWN
    testPosition(column_ori + 1, line_ori, board, gamer);     // RIGHT
    testPosition(column_ori - 1, line_ori, board, gamer);     // LEFT
    testPosition(column_ori + 1, line_ori - 1, board, gamer); // UP RIGHT
    testPosition(column_ori - 1, line_ori - 1, board, gamer); // UP LEFT
    testPosition(column_ori + 1, line_ori + 1, board, gamer); // DOWN RIGHT
    testPosition(column_ori - 1, line_ori + 1, board, gamer); // DOWN LEFT
}

int searchPieceDiagonalPeon(int column, int line, int board[8][8], int gamer)
{
    if(column >= 0 && column < 8 && line >= 0 && column < 8)
    {
        if(gamer == 1 && board[line][column] != 13 && board[line][column] >= 7 && board[line][column] <= 12)
            return 0;
        if(gamer == 2 && board[line][column] != 13 && board[line][column] >= 1 && board[line][column] <= 6)
            return 0;
    }
    return 1;
}

void testPeon(int column_ori, int line_ori, int board[8][8], int gamer)
{
    if(gamer == 1)
    {
        if(line_ori == 6 && column_ori >= 0 && column_ori <= 7 && (line_ori - 2) >= 0) // MOVE TWO HOUSES
        {
            if(board[line_ori - 2][column_ori] == 13) // MOVE FORWARD IF THERE IS NO PIECE
                testPosition(column_ori, line_ori - 2, board, gamer);
        }
        if((line_ori - 1) >= 0)
        {
            if(board[line_ori - 1][column_ori] == 13) // MOVE FORWARD IF THERE IS NO PIECE
                testPosition(column_ori, line_ori - 1, board, gamer);
        }
        // TEST IF THERE IS ANY OPPONENT OF PECA IN DIAGONAL
        if(searchPieceDiagonalPeon(column_ori + 1, line_ori - 1, board, gamer) == 0)
            testPosition(column_ori + 1, line_ori - 1, board, gamer);
        if(searchPieceDiagonalPeon(column_ori - 1, line_ori - 1, board, gamer) == 0)
            testPosition(column_ori - 1, line_ori - 1, board, gamer);
    }
    else if(gamer == 2)
    {
        if(line_ori == 1 && column_ori >= 0 && column_ori <= 7 && (line_ori + 2) <= 7)  // MOVE TWO HOUSES
        {
            if(board[line_ori + 2][column_ori] == 13) // MOVE FORWARD IF THERE IS NO PIECE
                testPosition(column_ori, line_ori + 2, board, gamer);
        }
        if((line_ori + 1) <= 7)
        {
            if(board[line_ori + 1][column_ori] == 13) // MOVE FORWARD IF THERE IS NO PIECE
                testPosition(column_ori, line_ori + 1, board, gamer);
        }
	// TEST IF THERE IS ANY OPPONENT OF PECA IN DIAGONAL
        if(searchPieceDiagonalPeon(column_ori + 1, line_ori + 1, board, gamer) == 0)
            testPosition(column_ori + 1, line_ori + 1, board, gamer);
        if(searchPieceDiagonalPeon(column_ori - 1, line_ori + 1, board, gamer) == 0)
            testPosition(column_ori - 1, line_ori + 1, board, gamer);
    }
}

int testMovePiece(int column_ori, int line_ori, int valuePosition, int board[8][8], int gamer)
{
    int c, l;
    // VERIFY BOARD
    for(l = 0; l < 8; l++)
    {
        for(c = 0; c < 8; c++)
        {
            if(board[l][c] < 0)
                board[l][c] = board[l][c] * -1;
        }
    }

    switch(valuePosition)
    {
    case 1: testHorse(column_ori, line_ori, board, gamer); break; 		// HORSE_G1
    case 2: testTower(column_ori, line_ori, board, gamer); break; 		// TOWER_G1
    case 3: testBispe(column_ori, line_ori, board, gamer); break;		// BISPE_G1
    case 4: testQueen(column_ori, line_ori, board, gamer); break;		// QUEEN_G1
    case 5: testKing(column_ori, line_ori, board, gamer); break;		// KING_G1
    case 6: testPeon(column_ori, line_ori, board, gamer); break;		// PEON_G1

    case 7: testHorse(column_ori, line_ori, board, gamer); break; 		// HORSE_G2
    case 8: testTower(column_ori, line_ori, board, gamer); break; 		// TOWER_G2
    case 9: testBispe(column_ori, line_ori, board, gamer); break;		// BISPE_G2
    case 10: testQueen(column_ori, line_ori, board, gamer); break;		// QUEEN_G2
    case 11: testKing(column_ori, line_ori, board, gamer); break;		// KING_G2
    case 12: testPeon(column_ori, line_ori, board, gamer); break;		// PEON_G2
    }
    
    // TEST IF THERE IS AT LEAST ONE VALID MOVE
    for(l = 0; l < 8; l++)
    {
        for(c = 0; c < 8; c++)
        {
            if(board[l][c] < 0)
                return 1;
        }
    }
    return 0;
}
