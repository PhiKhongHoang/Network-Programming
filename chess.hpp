#ifndef XADREZ_H_INCLUDED
#define XADREZ_H_INCLUDED

int testPosition(int column, int line, int board[8][8], int gamer);
void testTower(int column_ori, int line_ori, int board[8][8], int gamer);
void testHorse(int column_ori, int line_ori, int board[8][8], int gamer);
void testBispe(int column_ori, int line_ori, int board[8][8], int gamer);
void testQueen(int column_ori, int line_ori, int board[8][8], int gamer);
void testKing(int column_ori, int line_ori, int board[8][8], int gamer);
int searchPieceDiagonalPeon(int column, int line, int board[8][8], int gamer);
void testPeon(int column_ori, int line_ori, int board[8][8], int gamer);
int testMovePiece(int column_ori, int line_ori, int valuePosition, int board[8][8], int gamer);

#endif // XADREZ_H_INCLUDED
