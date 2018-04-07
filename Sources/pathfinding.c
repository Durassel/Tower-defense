#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <SDL.h>

#include "../Sources/defines.c"

#include "../Headers/structure.h"
#include "../Headers/pathfinding.h"

/* ---------------------------------------------------------------------------------- */
/* ----------------------------------- PATHFINDING ---------------------------------- */
/* ---------------- Chemin le plus court entre l'entrée et la sortie ---------------- */
/* ---------------------------------------------------------------------------------- */

// Test
int test(cell board[LIGNES][COLONNES], int x, int y)
{
    if(board[y][x].type == 0) // Case vide => possibilité de la remplir
        return 1;
    return 0;
}

// Calcul du coût de chaque case
int cost(cell board[LIGNES][COLONNES], coordinates Exit, int nbPoints, int *listeX, int *listeY)
{
    int i = 0;
    int nouveauNbPoints = 0;
    int *nouvelleListeX = NULL;
    int *nouvelleListeY = NULL;
    int impossible = 0;

    // OPTIMISATION : vérifier si les libérations sont correctes

    nouvelleListeX = (int *)malloc(sizeof(int) * 4);
    nouvelleListeY = (int *)malloc(sizeof(int) * 4);

    // On regarde les voisins de chaque point de la liste
    for(i=0;i<nbPoints;i++)
    {
        nouvelleListeX = (int *)realloc(nouvelleListeX, sizeof(int) * 4 *(i+1));
        nouvelleListeY = (int *)realloc(nouvelleListeY, sizeof(int) * 4 *(i+1));

        // A gauche
        if((listeX[i] > 0) && (test(board, listeX[i]-1, listeY[i]) == 1))
        {
            nouvelleListeX[nouveauNbPoints] = listeX[i]-1;
            nouvelleListeY[nouveauNbPoints] = listeY[i];
            board[nouvelleListeY[nouveauNbPoints]][nouvelleListeX[nouveauNbPoints]].type = board[listeY[i]][listeX[i]].type + 1;
            nouveauNbPoints++;
        }
        else
            impossible++;
        // A droite
        if((listeX[i] < COLONNES-1) && (test(board, listeX[i]+1, listeY[i]) == 1))
        {
            nouvelleListeX[nouveauNbPoints] = listeX[i]+1;
            nouvelleListeY[nouveauNbPoints] = listeY[i];
            board[nouvelleListeY[nouveauNbPoints]][nouvelleListeX[nouveauNbPoints]].type = board[listeY[i]][listeX[i]].type + 1;
            nouveauNbPoints++;
        }
        else
            impossible++;
        // En bas
        if((listeY[i] < LIGNES-1) && (test(board, listeX[i], listeY[i]+1) == 1))
        {
            nouvelleListeX[nouveauNbPoints] = listeX[i];
            nouvelleListeY[nouveauNbPoints] = listeY[i]+1;
            board[nouvelleListeY[nouveauNbPoints]][nouvelleListeX[nouveauNbPoints]].type = board[listeY[i]][listeX[i]].type + 1;
            nouveauNbPoints++;
        }
        else
            impossible++;
        // En haut
        if((listeY[i] > 0) && (test(board, listeX[i], listeY[i]-1) == 1))
        {
            nouvelleListeX[nouveauNbPoints] = listeX[i];
            nouvelleListeY[nouveauNbPoints] = listeY[i]-1;
            board[nouvelleListeY[nouveauNbPoints]][nouvelleListeX[nouveauNbPoints]].type = board[listeY[i]][listeX[i]].type + 1;
            nouveauNbPoints++;
        }
        else
            impossible++;
    }

    // Libération de mémoire
    free(listeX);
    free(listeY);

    // Si chaque point n'a plus de voisin disponible (=0), le chemin n'est pas réalisable
    if(impossible == (nbPoints * 4))
        return 0;

    if(board[Exit.y][Exit.x].type != 0) // Si on est arrivé à la fin, la valeur de la case a changé
        return 1;
    else
        return cost(board, Exit, nouveauNbPoints, nouvelleListeX, nouvelleListeY); // Fonction récursive (appel avec la nouvelle liste de points)
}

// Création du chemin
void road(cell board[LIGNES][COLONNES], coordinates Exit, coordinates Enter)
{
    int x = 0;
    int y = 0;
    int tab[4][2];
    int min = 0, max = 0;
    int i = 0;

    x = Exit.x; y = Exit.y;

    // Tant que l'on est pas arrivé au début
    while(x != Enter.x || y != Enter.y)
    {
        // Initialisation
        for(i=0;i<4;i++)
        {
            tab[i][0] = 0;
            tab[i][1] = 0;
        }

        // 1 = gauche / 2 = droite / 3 = haut / 4 = bas
        // Gauche
        if(x > 0 && board[y][x-1].type > 0)
            tab[0][0] = board[y][x-1].type;
        // Droite
        if(x < COLONNES-1 && board[y][x+1].type > 0)
            tab[1][0] = board[y][x+1].type;
        // Haut
        if(y > 0 && board[y-1][x].type > 0)
            tab[2][0] = board[y-1][x].type;
        // Bas
        if(y < LIGNES-1 && board[y+1][x].type > 0)
            tab[3][0] = board[y+1][x].type;

        // Maximum
        max = 0;
        for(i=0;i<4;i++)
        {
            if(tab[i][0] > max)
                max = tab[i][0];
        }

        // Minimum
        min = max;
        for(i=0;i<4;i++)
        {
            if(tab[i][0] < min && tab[i][0] > 0)
                min = tab[i][0];
        }

        // On parcours tab et on s'arrête dès qu'on trouve le premier min
        for(i=0;i<4;i++)
        {
            if(tab[i][0] == min)
            {
                tab[i][1] = 1;
                i = 4;
            }
        }

        board[y][x].type = -2;

        if(tab[0][1] == 1)
            x = x-1;
        if(tab[1][1] == 1)
            x = x+1;
        if(tab[2][1] == 1)
            y = y-1;
        if(tab[3][1] == 1)
            y = y+1;
    }
}

// pathfinding
int pathfinding(cell board[LIGNES][COLONNES], coordinates Exit, coordinates Enter)
{
    int *listeX = NULL;
    int *listeY = NULL;

    listeX = (int *)malloc(sizeof(int)); // X
    listeY = (int *)malloc(sizeof(int)); // Y

    listeX[0] = Enter.x;
    listeY[0] = Enter.y;

    // 0 = erreur / 1 = bon
    return cost(board, Exit, 1, listeX, listeY);
}
