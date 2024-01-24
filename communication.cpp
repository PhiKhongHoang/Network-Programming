#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>
#include <assert.h>

#include "communication.hpp"

char path[100];

void printBoard(int board[8][8])
{
    int line, column;
    for (line = 0; line < 8; line++)
    {
        for (column = 0; column < 8; column++)
        {
            switch (board[line][column])
            {
            case 1:
                strcpy(path, "image/quancocopy/KnightW.png");
                break;
            case 2:
                strcpy(path, "image/quancocopy/RookW.png");
                break;
            case 3:
                strcpy(path, "image/quancocopy/BishopW.png");
                break;
            case 4:
                strcpy(path, "image/quancocopy/QueenW.png");
                break;
            case 5:
                strcpy(path, "image/quancocopy/KingW.png");
                break;
            case 6:
                strcpy(path, "image/quancocopy/PawnW.png");
                break;

            case 7:
                strcpy(path, "image/quancocopy/KnightB.png");
                break;
            case 8:
                strcpy(path, "image/quancocopy/RookB.png");
                break;
            case 9:
                strcpy(path, "image/quancocopy/BishopB.png");
                break;
            case 10:
                strcpy(path, "image/quancocopy/KingB.png");
                break;
            case 11:
                strcpy(path, "image/quancocopy/QueenB.png");
                break;
            case 12:
                strcpy(path, "image/quancocopy/PawnB.png");
                break;

            case 13:
                strcpy(path, "image/nentrangfake.png");
                break;

            // set tat ca thanh nen mau do
            case -1:
                strcpy(path, "image/nuocdi.png");
                break; // HORSE_G1
            case -2:
                strcpy(path, "image/nuocdi.png");
                break; // TOWER_G1
            case -3:
                strcpy(path, "image/nuocdi.png");
                break; // BISPE_G1
            case -4:
                strcpy(path, "image/nuocdi.png");
                break; // QUEEN_G1
            case -5:
                strcpy(path, "image/nuocdi.png");
                break; // KING_G1
            case -6:
                strcpy(path, "image/nuocdi.png");
                break; // PEON_G1

            case -7:
                strcpy(path, "image/nuocdi.png");
                break; // HORSE_G2
            case -8:
                strcpy(path, "image/nuocdi.png");
                break; // TOWER_G2
            case -9:
                strcpy(path, "image/nuocdi.png");
                break; // BISPE_G2
            case -10:
                strcpy(path, "image/nuocdi.png");
                break; // QUEEN_G2
            case -11:
                strcpy(path, "image/nuocdi.png");
                break; // KING_G2
            case -12:
                strcpy(path, "image/quancocopy/PawnBan.png");
                break; // PEON_G2
            case -13:
                strcpy(path, "image/nuocdi.png");
                break;
            }
            ImageInfo quanco;
            if(strcmp(path, "image/nuocdi.png") == 0){
                loadMedia(&quanco, path, column * 55 + 36, line * 55 + 36);
                SDL_BlitSurface(quanco.surface, NULL, gScreenSurface, &quanco.position);
            }
            else if(strcmp(path, "image/quancocopy/PawnBan.png") == 0){
                loadMedia(&quanco, path, 45 + column * 52, 45+ line * 55);
                SDL_BlitSurface(quanco.surface, NULL, gScreenSurface, &quanco.position);
            }
            else 
            {
                loadMedia(&quanco, path, 38 + column * 52, line * 55);
                SDL_BlitSurface(quanco.surface, NULL, gScreenSurface, &quanco.position);
            }
            closeImage(&quanco);
        }
    }
}

char **strSplit(char *a_str, const char a_delim)
{
    char **result = 0;
    if (a_str != NULL)
    {
        size_t count = 0;
        char *tmp = a_str;
        char *last_comma = 0;
        char delim[2];
        delim[0] = a_delim;
        delim[1] = 0;

        // Count how many elements will be extracted
        while (*tmp)
        {
            if (a_delim == *tmp)
            {
                count++;
                last_comma = tmp;
            }
            tmp++;
        }
        count += last_comma < (a_str + strlen(a_str) - 1); // Add space for trailing token
        count++;                                           // Add space for terminating null string so caller knows where the list of strcpy(path,  ed strings ends
        // result = malloc(sizeof(char *) * count);
        char **result = new char *[count];

        if (result)
        {
            size_t idx = 0;
            char *token = strtok(a_str, delim);

            while (token)
            {
                assert(idx < count);
                *(result + idx++) = strdup(token);
                token = strtok(0, delim);
            }
            assert(idx == count - 1);
            *(result + idx) = 0;
        }
    }
    return result;
}

void printGamer1()
{
    printf("-------------------------------");
    printf("           GAMER 1 WIN         ");
    printf("-------------------------------\n");
}

void printGamer2()
{
    printf("-------------------------------");
    printf("          GAMER 2 WIN          ");
    printf("-------------------------------\n");
}
