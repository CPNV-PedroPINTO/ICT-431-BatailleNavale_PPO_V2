/**
 * \author Pedro Pinto
 * \date 06.03.2020
 * \version 1.0
 * \description Jeu de la bataille Navale en c++
 * ********************************************
 */

#include <stdio.h>
#include <stdio.h>
#include <windows.h>

#define SIZE 10
#define STLC 218 // ┌, Single Top Left Corner
#define STRC 191 // ┐, Single Top Right Corner
#define SBLC 192 // └, Single Bottom Left Corner
#define SBRC 217 // ┘, Single Bottom Right Corner
#define SVSB 179 // │, Single Vertical Simple Border
#define SVRB 180 // ┤, Single Vertical Right Border
#define SVLB 195 // ├, Single Vertical Left Border
#define SHSB 196 // ─, Single Horizontal Simple Border
#define SHBB 193 // ┴, Single Horizontal Bottom Border
#define SHTB 194 // ┬, Single Horizontal Top Border
#define SC   197 // ┼, Single Center
#define CUBE 219

int hit[5] = {0, 0, 0, 0, 0};
int grille[SIZE][SIZE] = {{3, 0, 0, 0, 0, 0, 0, 0, 0, 0},
                          {3, 0, 0, 0, 5, 5, 5, 5, 5, 0},
                          {3, 0, 0, 0, 0, 0, 0, 0, 0, 0},
                          {0, 2, 2, 0, 0, 0, 0, 0, 0, 0},
                          {0, 0, 0, 0, 0, 0, 4, 0, 0, 0},
                          {0, 0, 0, 0, 0, 0, 4, 0, 0, 0},
                          {0, 0, 0, 0, 0, 0, 4, 0, 0, 0},
                          {0, 0, 0, 0, 0, 0, 4, 0, 0, 0},
                          {0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
                          {0, 0, 0, 0, 0, 0, 0, 0, 0, 0}};


void topborder(int top) {
    printf("     A   B   C   D   E   F   G   H   I   J     \n");
    printf("   %c", STLC);             //┌
    for (int row = 0; row < top - 1; row++) {
        printf("%c%c%c%c", SHSB, SHSB, SHSB, SHTB);         //9x ─┬
    }
    printf("%c%c%c%c\n", SHSB, SHSB, SHSB, STRC);// ─┐
}

void horizontalborder(int horizon) {
    printf("   %c", SVLB);           //\n├
    for (int row = 0; row < horizon - 1; row++) {
        printf("%c%c%c%c", SHSB, SHSB, SHSB, SC);       //9x ─┼
    }
    printf("%c%c%c%c\n", SHSB, SHSB, SHSB, SVRB);     //─┤
}

void botborder(int bot) {
    printf("   %c", SBLC);                    //\n puis └
    for (int row = 0; row < bot - 1; row++) {
        printf("%c%c%c%c", SHSB, SHSB, SHSB, SHBB);         //─┴
    }
    printf("%c%c%c%c\n", SHSB, SHSB, SHSB, SBRC);              //─┘
}

void Verticalborder(int vertical, int num) {

    printf("%2d %c", num, SVSB);                    //\n puis └
    for (int row = 0; row < vertical; row++) {

        char carAFF = ' ';
        if (grille[num][row] > 10) {
            carAFF = 'X';
        }
        if (grille[num][row] > 20) {
            carAFF = CUBE;
        }
        if (grille[num][row] == -1) {
            carAFF = 'O';
        }
        printf(" %c %c", carAFF, SVSB);         //─┴
    }
    printf("\n");              //─┘
}

void play() {
    int bateaux_coules = 0;
    int test = 0;
    while (test != 1) {
        //Afficher la grille
        while (bateaux_coules != 4) {
    topborder(SIZE);
    for (int row = 0; row < SIZE; row++) {          //Grille
        if (row > 0)//first line
        {
            horizontalborder(SIZE);

        }
        Verticalborder(SIZE, row);

    }

    botborder(SIZE);
            char tir[5];


            printf("Vos bateaux sont prets faite feu ! ! ! \n donnez-moi vos coordonnees : ");
            scanf("%s", &tir);
            int col = tir[0] - 65;
            int row = tir[1] - 48;
            int valcase = grille[row][col];

            if (valcase == 0) {
                printf("\nA L'EAU\n");
                grille[row][col] = -1;
            }
            if (valcase >= 2) {
                printf("\nTOUCHE\n");
                hit[valcase]++;
                grille[row][col] += 10;
            }


            //Appliquer le tir sur le model
            int x = 0;
            int y = 0;
            int compteur = 0;
            for (int bateau = 1; bateau <= 5; bateau++) {
                for (x = 0; x < SIZE; x++) {
                    for (y = 0; y < SIZE; y++) {
                        if (grille[x][y] == bateau + 10) {
                            compteur++;
                        }
                    }
                }
                if (compteur == bateau) {                //le bateau est coulé
                    printf("COULE ! ! !\n");
                    for (x = 0; x < SIZE; x++) {
                        for (y = 0; y < SIZE; y++) {
                            if (grille[x][y] == bateau + 10) {
                                grille[x][y] = bateau + 20;

                                bateaux_coules++;
                                printf("\nBateaux coules : %d", bateaux_coules);

                            }
                        }
                    }
                }
            }
        }
    }
}




int main() {
    int grille;
    int vertical;
    int bot;
    int horizon;
    int top;

    play();
}

