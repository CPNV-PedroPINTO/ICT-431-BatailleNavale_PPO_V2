/**
 * \author Pedro Pinto
 * \date 06.03.2020
 * \version 1.0
 * \description Jeu de la bataille Navale en c++
 * ********************************************
 */

#include <stdio.h>
#include <windows.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

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


            printf("Vos bateaux sont prets faite feu ! ! ! \ndonnez-moi vos coordonnees : ");
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
                            }
                        }
                    }
                }
            }
        }
    }
}


int main() {
    int choix;
    char pseudo[100];
    int valid;
    printf("  ____        _        _ _ _        _   _                  _       \n"
           " |  _ \\      | |      (_) | |      | \\ | |                | |      \n"
           " | |_) | __ _| |_ __ _ _| | | ___  |  \\| | __ ___   ____ _| | ___  \n"
           " |  _ < / _` | __/ _` | | | |/ _ \\ | . ` |/ _` \\ \\ / / _` | |/ _ \\ \n"
           " | |_) | (_| | || (_| | | | |  __/ | |\\  | (_| |\\ V / (_| | |  __/ \n"
           " |____/ \\__,_|\\__\\__,_|_|_|_|\\___| |_| \\_|\\__,_| \\_/ \\__,_|_|\\___| \n"
           " -------------------------------------------------------------------                                                ");
    printf("\n\nBienvenu dans le jeu de la bataille navale");
    printf("\ncommencez apr entrer votre pseudo : ");
    scanf("%s", pseudo);
    printf("\nBonjour %s Maintenant tu dois choisir l'une des options du menu\n\n");
    printf("  __  __ ______ _   _ _    _ \n"
           " |  \\/  |  ____| \\ | | |  | |\n"
           " | \\  / | |__  |  \\| | |  | |\n"
           " | |\\/| |  __| | . ` | |  | |\n"
           " | |  | | |____| |\\  | |__| |\n"
           " |_|  |_|______|_| \\_|\\____/\n -------------------------");

    do {
        printf("\n1 : Jouer\n2 : Regles\n3 : Scores\n9 : Quitter");
        fflush(stdin);
        scanf("%d",&choix);
        switch (choix) {
            valid = 0;
            case 1:
                play();
                break;
            case 2:
                printf("\nRegle de la Bataille navale\n"
                       "On vous proposera une grille de jeu numerotee de 1 a 10 horizontalement et\nde A a J verticalement avec les bateaux suivants deja places.\n"
                       "1 croiseur (4 cases)\n"
                       "1 contre-torpilleur (3 cases)\n"
                       "1 torpilleur (2 cases)\n"
                       "1 porte-avions (5 cases)\n");
                printf("Vous devez a present tirer sur la grille adverse et tenter de toucher les bateaux");
                printf("Le premier joueur a eliminer tout les bateaux adverses gagne le combat");
                printf("Voici une video explicative : https://www.youtube.com/watch?v=klO6vPWPkzE\n");
                printf("Tous a vos postes de COMBAT!!\n\n");
                break;
            case 3:
                printf("\nComming soon\n");
                break;
            case 9:
                printf("\nFin du programe\n");
                break;
            default:
                printf("\nValeur invalide ! ! !\n");
                valid = 1;
                break;
        }
    } while (valid == 1);

    system("Pause");
    return main();
}
