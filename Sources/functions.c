#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <SDL.h>

#include "../Sources/defines.c"

#include "../Headers/structure.h"
#include "../Headers/functions.h"
#include "../Headers/pathfinding.h"

/* ---------------------------------------------------------------------------------- */
/* -------------------------------------- SDL --------------------------------------- */
/* ---------------------------------------------------------------------------------- */

    /* ------------------------------------ Pause ----------------------------------- */
    int pause_clic(void)
    {
        int continuer = 0;
        while(continuer == 0)
        {
            SDL_Event event;
            while(SDL_WaitEvent(&event))
            {
                switch(event.type)
                {
                    case SDL_MOUSEBUTTONUP:
                    {
                        if (event.button.button == SDL_BUTTON_LEFT)
                        {
                            continuer = 1;
                            return 0;
                        }
                        break;
                    }
                }
            }
        }
        return 0;
    }

    void refreshBoard(cell board[LIGNES][COLONNES], coordinates entryPoint, int iMouseX, int iMouseY, int *life, int *gold, int *wave, SDL_Surface* screen, SDL_Surface* Terre, int *choix_tour, int *descript, int *tour, int *selection, int *ameliorer, int *detruire, SDL_Surface* Porte_arche, SDL_Surface* Porte_mortier, SDL_Surface* Porte_tde, SDL_Surface* Chemin_Vertical, SDL_Surface* Chemin_Horizontal, SDL_Surface* Chemin_Bas_droite, SDL_Surface* Chemin_Bas_gauche, SDL_Surface* Chemin_Haut_droite, SDL_Surface* Chemin_Haut_gauche, SDL_Surface* ATH, SDL_Surface* ATH_Tour1, SDL_Surface* ATH_Tour2, SDL_Surface* ATH_Tour3, SDL_Surface* Tour1, SDL_Surface* Tour12, SDL_Surface* Tour13, SDL_Surface* Tour2, SDL_Surface* Tour22, SDL_Surface* Tour23, SDL_Surface* Tour3, SDL_Surface* Tour32, SDL_Surface* Tour33, SDL_Surface* Tour_transp1, SDL_Surface* Tour_transp2, SDL_Surface* Tour_transp3, SDL_Surface* Description_Tour11, SDL_Surface* Description_Tour12, SDL_Surface* Description_Tour13, SDL_Surface* Description_Tour21, SDL_Surface* Description_Tour22, SDL_Surface* Description_Tour23, SDL_Surface* Description_Tour31, SDL_Surface* Description_Tour32, SDL_Surface* Description_Tour33, SDL_Surface* Coeur_Plein, SDL_Surface* Coeur_Demi, SDL_Surface* Coeur_Vide, SDL_Surface* Argent, SDL_Surface* Tir, SDL_Surface* Tir2, SDL_Surface* Tir3, SDL_Surface* Ennemi, SDL_Surface* Ameliorer, SDL_Surface* Detruire, SDL_Surface* Chiffre0, SDL_Surface* Chiffre1, SDL_Surface* Chiffre2, SDL_Surface* Chiffre3, SDL_Surface* Chiffre4, SDL_Surface* Chiffre5, SDL_Surface* Chiffre6, SDL_Surface* Chiffre7, SDL_Surface* Chiffre8, SDL_Surface* Chiffre9, SDL_Surface* Vague)
    {
        SDL_Rect buildmap;
        SDL_Rect pos_curs;
        int i = 0, j = 0;
        int continuer = 0;
        int x = 0, y = 0;
        coordinates *tab = NULL;
        int cpt = 0;
        int chiffre[4] = {0, 0, 0, 0};
        int tmp = 0;

        buildmap.x = 0;
        buildmap.y = 0;
        // Refresh de la terre
        for(i=0;i<LIGNES;i++)
        {
            for(j=0;j<COLONNES;j++)
            {
                if(board[i][j].type == 0 || board[i][j].type == 2)
                {
                    SDL_BlitSurface(Terre, 0, screen, &buildmap);
                }

                buildmap.x = buildmap.x + TAILLE_CASE;
            }
            buildmap.x = 0;
            buildmap.y = buildmap.y + TAILLE_CASE;
        }

        // On sauvegarde dans un tableau les coordonnées des ennemis
        for(i=0;i<LIGNES;i++)
        {
            for(j=0;j<COLONNES;j++)
            {
                if(board[i][j].type == 3)
                {
                    if(tab == NULL)
                    {
                        tab = (coordinates *)malloc(sizeof(coordinates));
                        tab[0].x = j;
                        tab[0].y = i;
                        cpt++;
                    }
                    else
                    {
                        cpt++;
                        tab = (coordinates *)realloc(tab, cpt * sizeof(coordinates)); // Realloc
                        tab[cpt-1].x = j;
                        tab[cpt-1].y = i;
                    }
                }
            }
        }

        // Refresh du chemin
        i = entryPoint.y;
        j = entryPoint.x;
        while(continuer == 0)
        {
            buildmap.x = j * TAILLE_CASE;
            buildmap.y = i * TAILLE_CASE;
            if(i < LIGNES-1 && (board[i+1][j].type == 1 || board[i+1][j].type == 3))//1 case en bas
            {
                if((board[i][j+1].type == 5 || board[i][j+1].type == 3) && j < COLONNES-1)//1 case a droite
                    SDL_BlitSurface(Chemin_Haut_droite, 0, screen, &buildmap);
                else if((board[i-1][j].type == 5 || board[i-1][j].type == 3) && i > 0)//1 case en haut
                    SDL_BlitSurface(Chemin_Vertical, 0, screen, &buildmap);
                else if((board[i][j-1].type == 5 || board[i][j-1].type == 3) && j > 0)//1case a gauche
                    SDL_BlitSurface(Chemin_Haut_gauche, 0, screen, &buildmap);
                else if(i == 0)
                {
                    SDL_BlitSurface(Chemin_Vertical, 0, screen, &buildmap);
                    board[i][j].type = 5;
                }
                else if(j == 0)
                {
                    SDL_BlitSurface(Chemin_Haut_gauche, 0, screen, &buildmap);
                    board[i][j].type = 5;
                }
                else if(j == COLONNES-1)
                {
                    SDL_BlitSurface(Chemin_Haut_droite, 0, screen, &buildmap);
                    board[i][j].type = 5;
                }
                i++;
            }
            else if((board[i][j+1].type == 1 || board[i][j+1].type == 3) && j < COLONNES-1)//1 case a droite
            {
                if((board[i+1][j].type == 5 || board[i+1][j].type == 3) && i < LIGNES-1)//1 case en bas
                    SDL_BlitSurface(Chemin_Haut_droite, 0, screen, &buildmap);
                else if((board[i-1][j].type == 5 || board[i-1][j].type == 3) && i > 0)//1 case en haut
                    SDL_BlitSurface(Chemin_Bas_droite, 0, screen, &buildmap);
                else if((board[i][j-1].type == 5 || board[i][j-1].type == 3) && j > 0)//1case a gauche
                    SDL_BlitSurface(Chemin_Horizontal, 0, screen, &buildmap);
                else if(i == 0)
                {
                    SDL_BlitSurface(Chemin_Bas_droite, 0, screen, &buildmap);
                    board[i][j].type = 5;
                }
                else if(i == LIGNES-1)
                {
                    SDL_BlitSurface(Chemin_Haut_droite, 0, screen, &buildmap);
                    board[i][j].type = 5;
                }
                else if(j == 0)
                {
                    SDL_BlitSurface(Chemin_Horizontal, 0, screen, &buildmap);
                    board[i][j].type = 5;
                }
                j++;
            }
            else if((board[i-1][j].type == 1 || board[i-1][j].type == 3) && i > 0)//1 case en haut
            {
                if((board[i+1][j].type == 5 || board[i+1][j].type == 3) && i < LIGNES-1)//1 case en bas
                    SDL_BlitSurface(Chemin_Vertical, 0, screen, &buildmap);
                else if((board[i][j+1].type == 5 || board[i][j+1].type == 3) && j < COLONNES-1)//1 case a droite
                    SDL_BlitSurface(Chemin_Bas_droite, 0, screen, &buildmap);
                else if((board[i][j-1].type == 5 || board[i][j-1].type == 3) && j > 0)//1case a gauche
                    SDL_BlitSurface(Chemin_Bas_gauche, 0, screen, &buildmap);
                else if(i == LIGNES-1)
                {
                    SDL_BlitSurface(Chemin_Vertical, 0, screen, &buildmap);
                    board[i][j].type = 5;
                }
                else if(j == 0)
                {
                    SDL_BlitSurface(Chemin_Bas_gauche, 0, screen, &buildmap);
                    board[i][j].type = 5;
                }
                else if(j == COLONNES-1)
                {
                    SDL_BlitSurface(Chemin_Bas_droite, 0, screen, &buildmap);
                    board[i][j].type = 5;
                }
                i--;
            }
            else if((board[i][j-1].type == 1 || board[i][j-1].type == 3) && j > 0)//1case a gauche
            {
                if((board[i+1][j].type == 5 || board[i+1][j].type == 3) && i < LIGNES-1)//1 case en bas
                    SDL_BlitSurface(Chemin_Haut_gauche, 0, screen, &buildmap);
                else if((board[i][j+1].type == 5 || board[i][j+1].type == 3) && j < COLONNES-1)//1 case a droite
                    SDL_BlitSurface(Chemin_Horizontal, 0, screen, &buildmap);
                else if((board[i-1][j].type == 5 || board[i-1][j].type == 3) && i > 0)//1 case en haut
                    SDL_BlitSurface(Chemin_Bas_gauche, 0, screen, &buildmap);
                else if(i == 0)
                {
                    SDL_BlitSurface(Chemin_Bas_gauche, 0, screen, &buildmap);
                    board[i][j].type = 5;
                }
                else if(i == LIGNES-1)
                {
                    SDL_BlitSurface(Chemin_Haut_gauche, 0, screen, &buildmap);
                    board[i][j].type = 5;
                }
                else if(j == COLONNES-1)
                {
                    SDL_BlitSurface(Chemin_Horizontal, 0, screen, &buildmap);
                    board[i][j].type = 5;
                }
                j--;
            }
            else //DERNIERE CASE DU CHEMIN
            {
                if(i == 0)
                {
                    if((board[i+1][j].type == 5 || board[i+1][j].type == 3) && i < LIGNES-1)//1 case en bas
                        SDL_BlitSurface(Chemin_Vertical, 0, screen, &buildmap);
                    else if((board[i][j+1].type == 5 || board[i][j+1].type == 3) && j < COLONNES-1)//1 case a droite
                        SDL_BlitSurface(Chemin_Bas_droite, 0, screen, &buildmap);
                    else if((board[i][j-1].type == 5 || board[i][j-1].type == 3) && j > 0)//1case a gauche
                        SDL_BlitSurface(Chemin_Bas_gauche, 0, screen, &buildmap);
                }
                else if(i == LIGNES-1)
                {
                    if((board[i][j+1].type == 4 || board[i][j+1].type == 3) && j < COLONNES-1)//1 case a droite
                        SDL_BlitSurface(Chemin_Haut_droite, 0, screen, &buildmap);
                    else if((board[i-1][j].type == 5 || board[i-1][j].type == 3) && i > 0)//1 case en haut
                        SDL_BlitSurface(Chemin_Vertical, 0, screen, &buildmap);
                    else if((board[i][j-1].type == 5 || board[i][j-1].type == 3) && j > 0)//1case a gauche
                        SDL_BlitSurface(Chemin_Haut_gauche, 0, screen, &buildmap);
                }
                else if(j == 0)
                {
                    if((board[i+1][j].type == 5 || board[i+1][j].type == 3) && i < LIGNES-1)//1 case en bas
                        SDL_BlitSurface(Chemin_Haut_gauche, 0, screen, &buildmap);
                    else if((board[i][j+1].type == 5 || board[i][j+1].type == 3) && j < COLONNES-1)//1 case a droite
                        SDL_BlitSurface(Chemin_Horizontal, 0, screen, &buildmap);
                    else if((board[i-1][j].type == 5 || board[i-1][j].type == 3) && i > 0)//1 case en haut
                        SDL_BlitSurface(Chemin_Bas_gauche, 0, screen, &buildmap);
                }
                else if(j == COLONNES-1)
                {
                    if((board[i+1][j].type == 5 || board[i+1][j].type == 3) && i < LIGNES-1)//1 case en bas
                        SDL_BlitSurface(Chemin_Haut_droite, 0, screen, &buildmap);
                    else if ((board[i-1][j].type == 5 || board[i-1][j].type == 3) && i > 0)//1 case en haut
                        SDL_BlitSurface(Chemin_Bas_droite, 0, screen, &buildmap);
                    else if ((board[i][j-1].type == 5 || board[i][j-1].type == 3) && j > 0)//1case a gauche
                        SDL_BlitSurface(Chemin_Horizontal, 0, screen, &buildmap);
                }
                continuer = 1;
            }
            board[i][j].type = 5; // Efface les ennemis présents sur le chemin
        }
        clearBoard(board, 5, 1);

        // Une fois le chemin tracé, on peut les replacer
        for(i=0;i<cpt;i++)
        {
            board[tab[i].y][tab[i].x].type = 3;
        }

        // Refresh ennemi
        buildmap.x = 0;
        buildmap.y = 0;
        for(i=0;i<LIGNES;i++)
        {
            for(j=0;j<COLONNES;j++)
            {
                if(board[i][j].type == 3)
                {
                    buildmap.x = j * TAILLE_CASE;
                    buildmap.y = i * TAILLE_CASE;

                    buildmap.x = buildmap.x + ((enemy *)board[i][j].actor)->relativePosition.x - 30;
                    buildmap.y = buildmap.y + ((enemy *)board[i][j].actor)->relativePosition.y - 30;

                    SDL_BlitSurface(Ennemi, 0, screen, &buildmap);
                    buildmap.x = 0;
                    buildmap.y = 0;
                }
            }
        }

        // Refresh des projectiles
        buildmap.x = 0;
        buildmap.y = 0;
        for(i=0;i<LIGNES;i++)
        {
            for(j=0;j<COLONNES;j++)
            {
                if(board[i][j].type == 2) // On regarde si la case a été réservé pour regarder dedans (sinon erreur)
                {
                    buildmap.x = (j * TAILLE_CASE) + ((defense *)board[i][j].actor)->shot.x;
                    buildmap.y = (i * TAILLE_CASE) + ((defense *)board[i][j].actor)->shot.y;

                    if(((defense *)board[i][j].actor)->type == 11 || ((defense *)board[i][j].actor)->type == 12 || ((defense *)board[i][j].actor)->type == 13)
                        SDL_BlitSurface(Tir, 0, screen, &buildmap);
                    else if(((defense *)board[i][j].actor)->type == 21 || ((defense *)board[i][j].actor)->type == 22 || ((defense *)board[i][j].actor)->type == 23)
                        SDL_BlitSurface(Tir2, 0, screen, &buildmap);
                    else if(((defense *)board[i][j].actor)->type == 31 || ((defense *)board[i][j].actor)->type == 32 || ((defense *)board[i][j].actor)->type == 33)
                        SDL_BlitSurface(Tir3, 0, screen, &buildmap);

                    buildmap.x = 0;
                    buildmap.y = 0;
                }
            }
        }

        // Refresh des défenses
        buildmap.x = 0;
        buildmap.y = 0;
        for(i=0;i<LIGNES;i++)
        {
            for(j=0;j<COLONNES;j++)
            {
                if(board[i][j].type == 2) // On regarde si la case a été réservé pour regarder dedans (sinon erreur)
                {
                    buildmap.x = j * TAILLE_CASE;
                    buildmap.y = i * TAILLE_CASE;

                    if(((defense *)board[i][j].actor)->type == 11)
                        SDL_BlitSurface(Tour1, 0, screen, &buildmap);
                    else if(((defense *)board[i][j].actor)->type == 12)
                        SDL_BlitSurface(Tour12, 0, screen, &buildmap);
                    else if(((defense *)board[i][j].actor)->type == 13)
                        SDL_BlitSurface(Tour13, 0, screen, &buildmap);
                    else if(((defense *)board[i][j].actor)->type == 21)
                        SDL_BlitSurface(Tour2, 0, screen, &buildmap);
                    else if(((defense *)board[i][j].actor)->type == 22)
                        SDL_BlitSurface(Tour22, 0, screen, &buildmap);
                    else if(((defense *)board[i][j].actor)->type == 23)
                        SDL_BlitSurface(Tour23, 0, screen, &buildmap);
                    else if(((defense *)board[i][j].actor)->type == 31)
                        SDL_BlitSurface(Tour3, 0, screen, &buildmap);
                    else if(((defense *)board[i][j].actor)->type == 32)
                        SDL_BlitSurface(Tour32, 0, screen, &buildmap);
                    else if(((defense *)board[i][j].actor)->type == 33)
                        SDL_BlitSurface(Tour33, 0, screen, &buildmap);

                    buildmap.x = 0;
                    buildmap.y = 0;
                }
            }
        }

        // Refresh ATH
        buildmap.x = 900;
        buildmap.y = 0;
        SDL_BlitSurface(ATH, 0, screen, &buildmap);
        if(*choix_tour == 1)
        {
            buildmap.x = 907;
            buildmap.y = 292;
            pos_curs.x=iMouseX-TAILLE_CASE/2;
            pos_curs.y=iMouseY-TAILLE_CASE/2;
            SDL_BlitSurface(ATH_Tour1,0,screen,&buildmap);
            buildmap.x=907;
            buildmap.y=387;
            SDL_BlitSurface(Description_Tour11,0,screen,&buildmap);
            if(*gold >= 100)
                SDL_BlitSurface(Tour_transp1,0,screen,&pos_curs);
        }
        else if(*choix_tour == 2)
        {
            buildmap.x = 1004;
            buildmap.y = 292;
            pos_curs.x=iMouseX-TAILLE_CASE/2;
            pos_curs.y=iMouseY-TAILLE_CASE/2;
            SDL_BlitSurface(ATH_Tour2,0,screen,&buildmap);
            buildmap.x=907;
            buildmap.y=387;
            SDL_BlitSurface(Description_Tour21,0,screen,&buildmap);
            if(*gold >= 150)
                SDL_BlitSurface(Tour_transp2,0,screen,&pos_curs);
        }
        else if(*choix_tour == 3)
        {
            buildmap.x = 1100;
            buildmap.y = 292;
            pos_curs.x=iMouseX-TAILLE_CASE/2;
            pos_curs.y=iMouseY-TAILLE_CASE/2;
            SDL_BlitSurface(ATH_Tour3,0,screen,&buildmap);
            buildmap.x=907;
            buildmap.y=387;
            SDL_BlitSurface(Description_Tour31,0,screen,&buildmap);
            if(*gold >= 200)
                SDL_BlitSurface(Tour_transp3,0,screen,&pos_curs);
        }

        // VAGUE
        buildmap.x = 940;
        buildmap.y = 35;
        SDL_BlitSurface(Vague, 0, screen, &buildmap);
        tmp = *wave;
        cpt = 0;
        do
        {
            tmp /= 10;
            cpt++;
        } while(tmp > 0);
        tmp = *wave;
        for(i=cpt;i>0;i--)
        {
            chiffre[cpt-i] = tmp / (pow(10, i-1));
            tmp -= chiffre[cpt-i] * (pow(10, i-1));
        }
        // Affichage des chiffres
        buildmap.x = 1000;
        buildmap.y = 38;
        for(i=0;i<cpt;i++)
        {
            if(chiffre[i] == 0)
                SDL_BlitSurface(Chiffre0, 0, screen, &buildmap);
            else if(chiffre[i] == 1)
                SDL_BlitSurface(Chiffre1, 0, screen, &buildmap);
            else if(chiffre[i] == 2)
                SDL_BlitSurface(Chiffre2, 0, screen, &buildmap);
            else if(chiffre[i] == 3)
                SDL_BlitSurface(Chiffre3, 0, screen, &buildmap);
            else if(chiffre[i] == 4)
                SDL_BlitSurface(Chiffre4, 0, screen, &buildmap);
            else if(chiffre[i] == 5)
                SDL_BlitSurface(Chiffre5, 0, screen, &buildmap);
            else if(chiffre[i] == 6)
                SDL_BlitSurface(Chiffre6, 0, screen, &buildmap);
            else if(chiffre[i] == 7)
                SDL_BlitSurface(Chiffre7, 0, screen, &buildmap);
            else if(chiffre[i] == 8)
                SDL_BlitSurface(Chiffre8, 0, screen, &buildmap);
            else if(chiffre[i] == 9)
                SDL_BlitSurface(Chiffre9, 0, screen, &buildmap);
            buildmap.x += 25;
        }
        cpt = 0;

        // ARGENT (pareil que la vague)
        buildmap.x = 950;
        buildmap.y = 128;
        SDL_BlitSurface(Argent, 0, screen, &buildmap);
        // Séparation des chiffres de gold
        tmp = *gold;
        cpt = 0;
        do
        {
            tmp /= 10;
            cpt++;
        } while(tmp > 0);
        tmp = *gold;
        for(i=cpt;i>0;i--)
        {
            chiffre[cpt-i] = tmp / (pow(10, i-1));
            tmp -= chiffre[cpt-i] * (pow(10, i-1));
        }
        // Affichage des chiffres
        buildmap.x = 1000;
        buildmap.y = 133;
        for(i=0;i<cpt;i++)
        {
            if(chiffre[i] == 0)
                SDL_BlitSurface(Chiffre0, 0, screen, &buildmap);
            else if(chiffre[i] == 1)
                SDL_BlitSurface(Chiffre1, 0, screen, &buildmap);
            else if(chiffre[i] == 2)
                SDL_BlitSurface(Chiffre2, 0, screen, &buildmap);
            else if(chiffre[i] == 3)
                SDL_BlitSurface(Chiffre3, 0, screen, &buildmap);
            else if(chiffre[i] == 4)
                SDL_BlitSurface(Chiffre4, 0, screen, &buildmap);
            else if(chiffre[i] == 5)
                SDL_BlitSurface(Chiffre5, 0, screen, &buildmap);
            else if(chiffre[i] == 6)
                SDL_BlitSurface(Chiffre6, 0, screen, &buildmap);
            else if(chiffre[i] == 7)
                SDL_BlitSurface(Chiffre7, 0, screen, &buildmap);
            else if(chiffre[i] == 8)
                SDL_BlitSurface(Chiffre8, 0, screen, &buildmap);
            else if(chiffre[i] == 9)
                SDL_BlitSurface(Chiffre9, 0, screen, &buildmap);
            buildmap.x += 25;
        }
        cpt = 0;

        // Refresh Vie
        buildmap.x = 955;
        buildmap.y = 230;
        if((*life%2) == 0) // Chiffre pair
        {
            // Plein
            for(i=0;i<(*life/2);i++)
            {
                SDL_BlitSurface(Coeur_Plein, 0, screen, &buildmap);
                buildmap.x = buildmap.x + 40;
            }
            // Vide
            for(i=(*life/2);i<5;i++)
            {
                SDL_BlitSurface(Coeur_Vide, 0, screen, &buildmap);
                buildmap.x = buildmap.x + 40;
            }
        }
        else // Chiffre impair
        {
            // Plein
            for(i=0;i<(*life/2);i++)
            {
                SDL_BlitSurface(Coeur_Plein, 0, screen, &buildmap);
                buildmap.x = buildmap.x + 40;
            }
            // Demi
            for(i=0;i<(*life%2);i++)
            {
                SDL_BlitSurface(Coeur_Demi, 0, screen, &buildmap);
                buildmap.x = buildmap.x + 40;
            }
            // Vide
            for(i=(*life/2)+(*life%2);i<5;i++)
            {
                SDL_BlitSurface(Coeur_Vide, 0, screen, &buildmap);
                buildmap.x = buildmap.x + 40;
            }
        }

        // Transcription des coordonnées en pixels en coordonnées du tableau
        for(i=0;i<LIGNES;i++)
        {
            if(iMouseX > i*TAILLE_CASE && iMouseX < (i+1)*TAILLE_CASE && iMouseX < 900)
                x = i;
            if(iMouseY > i*TAILLE_CASE && iMouseY < (i+1)*TAILLE_CASE)
                y = i;
        }

        // Création d'une défense
        if(*tour == 1)
        {
            if(board[y][x].type == 0)
            {
                if(*choix_tour == 1 && *gold >= 100)
                {
                    initDefense(board, x, y, *choix_tour);
                    if(board[y][x].type == 2)
                        *gold = *gold - ((defense *)board[y][x].actor)->price;
                }
                else if(*choix_tour == 2 && *gold >= 150)
                {
                    initDefense(board, x, y, *choix_tour);
                    if(board[y][x].type == 2)
                        *gold = *gold - ((defense *)board[y][x].actor)->price;
                }
                else if(*choix_tour == 3 && *gold >= 200)
                {
                    initDefense(board, x, y, *choix_tour);
                    if(board[y][x].type == 2)
                        *gold = *gold - ((defense *)board[y][x].actor)->price;
                }
            }
            *tour = 0;
            *choix_tour = 0;
        }

        // Affichage de la portée d'une tour
        if(*choix_tour == 0 && board[y][x].type == 2)
        {
            if(((defense *)board[y][x].actor)->type == 11 || ((defense *)board[y][x].actor)->type == 12 || ((defense *)board[y][x].actor)->type == 13)
            {
                buildmap.x = (x * TAILLE_CASE) - 60;
                buildmap.y = (y * TAILLE_CASE) - 60;
                SDL_BlitSurface(Porte_arche, 0, screen, &buildmap);
            }
            else if(((defense *)board[y][x].actor)->type == 21 || ((defense *)board[y][x].actor)->type == 22 || ((defense *)board[y][x].actor)->type == 23)
            {
                buildmap.x = (x * TAILLE_CASE) - 120;
                buildmap.y = (y * TAILLE_CASE) - 120;
                SDL_BlitSurface(Porte_mortier, 0, screen, &buildmap);
            }
            if(((defense *)board[y][x].actor)->type == 31 || ((defense *)board[y][x].actor)->type == 32 || ((defense *)board[y][x].actor)->type == 33)
            {
                buildmap.x = (x * TAILLE_CASE) - 240;
                buildmap.y = (y * TAILLE_CASE) - 240;
                SDL_BlitSurface(Porte_tde, 0, screen, &buildmap);
            }
        }

        // Affichage des caractéristiques des défenses
        if(*selection == 1 && *choix_tour == 0 && *ameliorer == 0 && *detruire == 0) // Le joueur a cliqué sur le plateau
        {
            if(board[y][x].type == 2) // On vérifie qu'il a cliqué sur une défense
            {
                if(((defense *)board[y][x].actor)->type == 11)
                {
                    *descript = 11;
                    *selection = 0;
                }
                else if(((defense *)board[y][x].actor)->type == 12)
                {
                    *descript = 12;
                    *selection = 0;
                }
                else if(((defense *)board[y][x].actor)->type == 13)
                {
                    *descript = 13;
                    *selection = 0;
                }
                else if(((defense *)board[y][x].actor)->type == 21)
                {
                    *descript = 21;
                    *selection = 0;
                }
                else if(((defense *)board[y][x].actor)->type == 22)
                {
                    *descript = 22;
                    *selection = 0;
                }
                else if(((defense *)board[y][x].actor)->type == 23)
                {
                    *descript = 23;
                    *selection = 0;
                }
                else if(((defense *)board[y][x].actor)->type == 31)
                {
                    *descript = 31;
                    *selection = 0;
                }
                else if(((defense *)board[y][x].actor)->type == 32)
                {
                    *descript = 32;
                    *selection = 0;
                }
                else if(((defense *)board[y][x].actor)->type == 33)
                {
                    *descript = 33;
                    *selection = 0;
                }
            }
            else
            {
                *descript = 0;
                *selection = 0;
            }
        }

        buildmap.x = 907;
        buildmap.y = 387;
        if(*choix_tour == 0)
        {
            if(*descript == 11 || *descript == 12 || *descript == 21 || *descript == 22 || *descript == 31 || *descript == 32)
            {
                if(*descript == 11)
                {
                    SDL_BlitSurface(Description_Tour11, 0, screen, &buildmap);
                }
                else if(*descript == 12)
                {
                    SDL_BlitSurface(Description_Tour12, 0, screen, &buildmap);
                }
                else if(*descript == 21)
                {
                    SDL_BlitSurface(Description_Tour21, 0, screen, &buildmap);
                }
                else if(*descript == 22)
                {
                    SDL_BlitSurface(Description_Tour22, 0, screen, &buildmap);
                }
                else if(*descript == 31)
                {
                    SDL_BlitSurface(Description_Tour31, 0, screen, &buildmap);
                }
                else if(*descript == 32)
                {
                    SDL_BlitSurface(Description_Tour32, 0, screen, &buildmap);
                }
                buildmap.x = 907;
                buildmap.y = 750;
                SDL_BlitSurface(Ameliorer, 0, screen, &buildmap);
                buildmap.x = 1052;
                buildmap.y = 750;
                SDL_BlitSurface(Detruire, 0, screen, &buildmap);
            }
            else if(*descript == 13 || *descript == 23 || *descript == 33)
            {
                if(*descript == 13)
                {
                    SDL_BlitSurface(Description_Tour13, 0, screen, &buildmap);
                }
                else if(*descript == 23)
                {
                    SDL_BlitSurface(Description_Tour23, 0, screen, &buildmap);
                }
                else if(*descript == 33)
                {
                    SDL_BlitSurface(Description_Tour33, 0, screen, &buildmap);
                }
                buildmap.x = 1052;
                buildmap.y = 750;
                SDL_BlitSurface(Detruire, 0, screen, &buildmap);
            }
        }
        else
            *descript = 0;

        // Amélioration d'une défense
        if(*ameliorer == 1 && *selection == 1)
        {
            if(board[y][x].type == 2)
            {
                // Il faut avoir assez d'argent
                if(((defense *)board[y][x].actor)->type != 13 && ((defense *)board[y][x].actor)->type != 23 && ((defense *)board[y][x].actor)->type != 33 && *gold >= ((defense *)board[y][x].actor)->price - 50)
                {
                    ((defense *)board[y][x].actor)->type += 1;
                    *gold = *gold - (((defense *)board[y][x].actor)->price - 50);
                }
            }
            *ameliorer = 0;
            *selection = 0;
            *descript = 0;
        }

        // Destruction d'une défense
        if(*detruire == 1 && *selection == 1 && board[y][x].type == 2)
        {
            *gold = *gold + ((((defense *)board[y][x].actor)->price * 50)/100); // On gagne 50% du prix à la destruction
            board[y][x].type = 0;
            free(board[y][x].actor);
            *detruire = 0;
            *selection = 0;
            *descript = 0;
        }

        for(i=0;i<cpt;i++)
            free(&tab[i]);
        free(tab);

        // Rafraichissement de la map
        SDL_Flip(screen);
    }

/* ---------------------------------------------------------------------------------- */
/* ----------------------------- FONCTIONS PRINCIPALES ------------------------------ */
/* ---------------------------------------------------------------------------------- */

    /* ------------------------------ Lancer une partie ----------------------------- */
    void game(int level, SDL_Surface* screen)
    {
        // BOARD
        cell board[LIGNES][COLONNES]; // Plateau de jeu
        coordinates entryPoint; // Point d'entré du chemin
        coordinates exitPoint; // Point de sortie du shemin
        int i = 0, k = 0, l = 0; // Compteurs

        // PLAYER
        int life = 0; // nombre de vies du joueur
        int result = 0; // Résultat de la partie (victoire ou défaite)
        int gold = 160; // Au début, le joueur ne peut poser qu'une tour de sorciers
        int wait = 0;

        // ENEMY
        clock_t t1, t2, t3, t4, t6, t7; // Temps permettant de créer et de déplacer des ennemis
        int nbEnemy = 0; // Nombre d'ennemis sur la plateau
        int nbWave = 0; // Nombre de vagues d'ennemis
        int wave = 1; // Numéro de la vague
        int nbEnemyPerWave = 0; // Nombre d'ennemis par vague (augmente)
        int nbEnemyPerWaveInitial = 0; // Nombre d'ennemis initial par vague
        int nbEnemyCreated = 0; // Nombre d'ennemis créés durant la vague
        float creationTimeEnemy = 0.0; // Ennemi créé toutes les x secondes
        float positionTimeEnemy = 0.0; // Ennemis déplacés toutes les x secondes
        float differenceTime = 0.0; // Temps écoulé entre 2 moments

        // DEFENSE
        clock_t t5, t8;

        // SDL
        SDL_Event event; // Evénement
        SDL_Rect buildmap;
        int iMouseX = 0;
        int iMouseY = 0;
        int pause = 0;
        int tour = 0;
        int selection = 0;
        int choix_tour = 0;
        int descript = 0;
        int ameliorer = 0;
        int detruire = 0;
        coordinates lastClic = {0, 0};

        /* ---------------------------------------------------------------------------------- */
        /* ----------------------------- CHARGEMENT DES IMAGES ------------------------------ */
        /* ---------------------------------------------------------------------------------- */

        SDL_Surface* Loading = SDL_LoadBMP("Pictures/Loading screen.bmp");
        if (!Loading)
        {
            printf("Impossibilite de charger l'image: Loading\n");
            exit(EXIT_FAILURE);
        }
        SDL_BlitSurface(Loading, 0, screen,0);
        SDL_Flip(screen);
        SDL_Surface* Terre= SDL_LoadBMP("Pictures/Terre.bmp");
        if (!Terre)
        {
            printf("Impossibilite de charger l'image: Terre\n");
            exit(EXIT_FAILURE);
        }
        SDL_Surface* ATH_Pause= SDL_LoadBMP("Pictures/ATH_Pause.bmp");
        if (!ATH_Pause)
        {
            printf("Impossibilite de charger l'image: ATH_Pause\n");
            exit(EXIT_FAILURE);
        }
        SDL_Surface* ATH_Pause_Sep= SDL_LoadBMP("Pictures/ATH_Pause_Sep.bmp");
        if (!ATH_Pause_Sep)
        {
            printf("Impossibilite de charger l'image: ATH_Pause_Sep\n");
            exit(EXIT_FAILURE);
        }
        SDL_Surface* ATH_Pause_Continue= SDL_LoadBMP("Pictures/ATH_Pause_Continue.bmp");
        if (!ATH_Pause_Continue)
        {
            printf("Impossibilite de charger l'image: ATH_Pause_Continu\n");
            exit(EXIT_FAILURE);
        }
        SDL_Surface* ATH_Pause_Save= SDL_LoadBMP("Pictures/ATH_Pause_Save.bmp");
        if (!ATH_Pause_Save)
        {
            printf("Impossibilite de charger l'image: ATH_Pause_Save\n");
            exit(EXIT_FAILURE);
        }
        SDL_Surface* ATH_Pause_Quit= SDL_LoadBMP("Pictures/ATH_Pause_Quit.bmp");
        if (!ATH_Pause_Quit)
        {
            printf("Impossibilite de charger l'image: ATH_Pause_Quit\n");
            exit(EXIT_FAILURE);
        }
        SDL_Surface* Porte_arche = SDL_LoadBMP("Pictures/Porte_arche.bmp");
        if(!Porte_arche)
        {
            printf("Impossibilite de charger l'image: Porte_arche\n");
            exit(EXIT_FAILURE);
        }
        SDL_SetColorKey(Porte_arche, SDL_SRCCOLORKEY, SDL_MapRGB(Porte_arche->format, 255, 255, 255));
        SDL_SetAlpha(Porte_arche, SDL_SRCALPHA, 50);
        SDL_Surface* Porte_mortier = SDL_LoadBMP("Pictures/Porte_mortier.bmp");
        if(!Porte_mortier)
        {
            printf("Impossibilite de charger l'image: Porte_mortier\n");
            exit(EXIT_FAILURE);
        }
        SDL_SetColorKey(Porte_mortier, SDL_SRCCOLORKEY, SDL_MapRGB(Porte_mortier->format, 255, 255, 255));
        SDL_SetAlpha(Porte_mortier, SDL_SRCALPHA, 50);
        SDL_Surface* Porte_tde = SDL_LoadBMP("Pictures/Porte_tde.bmp");
        if(!Porte_tde)
        {
            printf("Impossibilite de charger l'image: Porte_tde\n");
            exit(EXIT_FAILURE);
        }
        SDL_SetColorKey(Porte_tde, SDL_SRCCOLORKEY, SDL_MapRGB(Porte_tde->format, 255, 255, 255));
        SDL_SetAlpha(Porte_tde, SDL_SRCALPHA, 50);
        SDL_Surface* Chemin_Vertical= SDL_LoadBMP("Pictures/Chemin_Vertical.bmp");
        if (!Chemin_Vertical)
        {
            printf("Impossibilite de charger l'image: Chemin_Vertical\n");
            exit(EXIT_FAILURE);
        }
        SDL_Surface* Chemin_Horizontal= SDL_LoadBMP("Pictures/Chemin_Horizontal.bmp");
        if (!Chemin_Horizontal)
        {
            printf("Impossibilite de charger l'image: Chemin_Horizontal\n");
            exit(EXIT_FAILURE);
        }
        SDL_Surface* Chemin_Bas_droite= SDL_LoadBMP("Pictures/Chemin_Bas_droite.bmp");
        if (!Chemin_Bas_droite)
        {
            printf("Impossibilite de charger l'image: Chemin_Bas_droite\n");
            exit(EXIT_FAILURE);
        }
        SDL_Surface* Chemin_Bas_gauche= SDL_LoadBMP("Pictures/Chemin_Bas_gauche.bmp");
        if (!Chemin_Bas_gauche)
        {
            printf("Impossibilite de charger l'image: Chemin_Bas_gauche\n");
            exit(EXIT_FAILURE);
        }
        SDL_Surface* Chemin_Haut_droite= SDL_LoadBMP("Pictures/Chemin_Haut_droite.bmp");
        if (!Chemin_Haut_droite)
        {
            printf("Impossibilite de charger l'image: Chemin_Haut_droite\n");
            exit(EXIT_FAILURE);
        }
        SDL_Surface* Chemin_Haut_gauche= SDL_LoadBMP("Pictures/Chemin_Haut_gauche.bmp");
        if (!Chemin_Haut_gauche)
        {
            printf("Impossibilite de charger l'image: Chemin_Haut_gauche\n");
            exit(EXIT_FAILURE);
        }
        SDL_Surface* ATH= SDL_LoadBMP("Pictures/ATH.bmp");
        if (!ATH)
        {
            printf("Impossibilite de charger l'image: ATH\n");
            exit(EXIT_FAILURE);
        }
        SDL_Surface* ATH_Tour1 = SDL_LoadBMP("Pictures/ATH-Tour-1.bmp");
        if (!ATH_Tour1)
        {
            printf("Impossibilite de charger l'image: ATH-Tour-1\n");
            exit(EXIT_FAILURE);
        }
        SDL_Surface* ATH_Tour2 = SDL_LoadBMP("Pictures/ATH-Tour-2.bmp");
        if (!ATH_Tour2)
        {
            printf("Impossibilite de charger l'image: ATH-Tour-2\n");
            exit(EXIT_FAILURE);
        }
        SDL_Surface* ATH_Tour3 = SDL_LoadBMP("Pictures/ATH-Tour-3.bmp");
        if (!ATH_Tour3)
        {
            printf("Impossibilite de charger l'image: ATH-Tour-3\n");
            exit(EXIT_FAILURE);
        }
        SDL_Surface* Tour1 = SDL_LoadBMP("Pictures/Tour11.bmp");
        if (!Tour1)
        {
            printf("Impossibilite de charger l'image: Tour11.\n");
            exit(EXIT_FAILURE);
        }
        SDL_SetColorKey(Tour1, SDL_SRCCOLORKEY, SDL_MapRGB(Tour1->format, 255, 255, 255));
        SDL_Surface* Tour12 = SDL_LoadBMP("Pictures/Tour12.bmp");
        if (!Tour12)
        {
            printf("Impossibilite de charger l'image: Tour12.\n");
            exit(EXIT_FAILURE);
        }
        SDL_SetColorKey(Tour12, SDL_SRCCOLORKEY, SDL_MapRGB(Tour12->format, 255, 255, 255));
        SDL_Surface* Tour13 = SDL_LoadBMP("Pictures/Tour13.bmp");
        if (!Tour13)
        {
            printf("Impossibilite de charger l'image: Tour13.\n");
            exit(EXIT_FAILURE);
        }
        SDL_SetColorKey(Tour13, SDL_SRCCOLORKEY, SDL_MapRGB(Tour13->format, 255, 255, 255));
        SDL_Surface* Tour2 = SDL_LoadBMP("Pictures/Tour21.bmp");
        if (!Tour2)
        {
            printf("Impossibilite de charger l'image: Tour2\n");
            exit(EXIT_FAILURE);
        }
        SDL_SetColorKey(Tour2, SDL_SRCCOLORKEY, SDL_MapRGB(Tour2->format, 255, 255, 255));
        SDL_Surface* Tour22 = SDL_LoadBMP("Pictures/Tour22.bmp");
        if (!Tour22)
        {
            printf("Impossibilite de charger l'image: Tour22.\n");
            exit(EXIT_FAILURE);
        }
        SDL_SetColorKey(Tour22, SDL_SRCCOLORKEY, SDL_MapRGB(Tour22->format, 255, 255, 255));
        SDL_Surface* Tour23 = SDL_LoadBMP("Pictures/Tour23.bmp");
        if (!Tour23)
        {
            printf("Impossibilite de charger l'image: Tour23.\n");
            exit(EXIT_FAILURE);
        }
        SDL_SetColorKey(Tour23, SDL_SRCCOLORKEY, SDL_MapRGB(Tour23->format, 255, 255, 255));
        SDL_Surface* Tour3 = SDL_LoadBMP("Pictures/Tour31.bmp");
        if (!Tour3)
        {
            printf("Impossibilite de charger l'image: Tour3\n");
            exit(EXIT_FAILURE);
        }
        SDL_SetColorKey(Tour3, SDL_SRCCOLORKEY, SDL_MapRGB(Tour3->format, 255, 255, 255));
        SDL_Surface* Tour32 = SDL_LoadBMP("Pictures/Tour32.bmp");
        if (!Tour32)
        {
            printf("Impossibilite de charger l'image: Tour32.\n");
            exit(EXIT_FAILURE);
        }
        SDL_SetColorKey(Tour32, SDL_SRCCOLORKEY, SDL_MapRGB(Tour32->format, 255, 255, 255));
        SDL_Surface* Tour33 = SDL_LoadBMP("Pictures/Tour33.bmp");
        if (!Tour33)
        {
            printf("Impossibilite de charger l'image: Tour33.\n");
            exit(EXIT_FAILURE);
        }
        SDL_SetColorKey(Tour33, SDL_SRCCOLORKEY, SDL_MapRGB(Tour33->format, 255, 255, 255));
        SDL_Surface* Tour_transp1 = SDL_LoadBMP("Pictures/Tour_Transp1.bmp");
        if (!Tour_transp1)
        {
            printf("Impossibilite de charger l'image: Tour_Transp1\n");
            exit(EXIT_FAILURE);
        }
        SDL_SetColorKey(Tour_transp1, SDL_SRCCOLORKEY, SDL_MapRGB(Tour_transp1->format, 255, 255, 255));
        SDL_SetAlpha(Tour_transp1, SDL_SRCALPHA, 200);
        SDL_Surface* Tour_transp2 = SDL_LoadBMP("Pictures/Tour_Transp2.bmp");
        if (!Tour_transp2)
        {
            printf("Impossibilite de charger l'image: Tour_Transp2\n");
            exit(EXIT_FAILURE);
        }
        SDL_SetColorKey(Tour_transp2, SDL_SRCCOLORKEY, SDL_MapRGB(Tour_transp2->format, 255, 255, 255));
        SDL_SetAlpha(Tour_transp2, SDL_SRCALPHA, 200);
        SDL_Surface* Tour_transp3 = SDL_LoadBMP("Pictures/Tour_Transp3.bmp");
        if (!Tour_transp3)
        {
            printf("Impossibilite de charger l'image: Tour_Transp3\n");
            exit(EXIT_FAILURE);
        }
        SDL_SetColorKey(Tour_transp3, SDL_SRCCOLORKEY, SDL_MapRGB(Tour_transp3->format, 255, 255, 255));
        SDL_SetAlpha(Tour_transp3, SDL_SRCALPHA, 200);
        SDL_Surface* Description_Tour11 = SDL_LoadBMP("Pictures/description_tour_11.bmp");
        if (!Description_Tour11)
        {
            printf("Impossibilite de charger l'image: Description_Tour11\n");
            exit(EXIT_FAILURE);
        }
        SDL_Surface* Description_Tour12 = SDL_LoadBMP("Pictures/description_tour_12.bmp");
        if (!Description_Tour12)
        {
            printf("Impossibilite de charger l'image: Description_Tour12\n");
            exit(EXIT_FAILURE);
        }
        SDL_Surface* Description_Tour13 = SDL_LoadBMP("Pictures/description_tour_13.bmp");
        if (!Description_Tour13)
        {
            printf("Impossibilite de charger l'image: Description_Tour13\n");
            exit(EXIT_FAILURE);
        }
        SDL_Surface* Description_Tour21 = SDL_LoadBMP("Pictures/description_tour_21.bmp");
        if (!Description_Tour21)
        {
            printf("Impossibilite de charger l'image: description_tour21\n");
            exit(EXIT_FAILURE);
        }
        SDL_Surface* Description_Tour22 = SDL_LoadBMP("Pictures/description_tour_22.bmp");
        if (!Description_Tour22)
        {
            printf("Impossibilite de charger l'image: description_tour22\n");
            exit(EXIT_FAILURE);
        }
        SDL_Surface* Description_Tour23 = SDL_LoadBMP("Pictures/description_tour_23.bmp");
        if (!Description_Tour23)
        {
            printf("Impossibilite de charger l'image: description_tour23\n");
            exit(EXIT_FAILURE);
        }
        SDL_Surface* Description_Tour31 = SDL_LoadBMP("Pictures/description_tour_31.bmp");
        if (!Description_Tour31)
        {
            printf("Impossibilite de charger l'image: description_tour31\n");
            exit(EXIT_FAILURE);
        }
        SDL_Surface* Description_Tour32 = SDL_LoadBMP("Pictures/description_tour_32.bmp");
        if (!Description_Tour32)
        {
            printf("Impossibilite de charger l'image: description_tour32\n");
            exit(EXIT_FAILURE);
        }
        SDL_Surface* Description_Tour33 = SDL_LoadBMP("Pictures/description_tour_33.bmp");
        if (!Description_Tour33)
        {
            printf("Impossibilite de charger l'image: description_tour33\n");
            exit(EXIT_FAILURE);
        }
        SDL_Surface* Coeur_Plein = SDL_LoadBMP("Pictures/Coeur_Plein.bmp");
        if (!Coeur_Plein)
        {
            printf("Impossibilite de charger l'image: Coeur_Plein\n");
            exit(EXIT_FAILURE);
        }
        SDL_SetColorKey(Coeur_Plein, SDL_SRCCOLORKEY, SDL_MapRGB(Coeur_Plein->format, 255, 255, 255));
        SDL_Surface* Coeur_Demi = SDL_LoadBMP("Pictures/Coeur_Demi.bmp");
        if (!Coeur_Demi)
        {
            printf("Impossibilite de charger l'image: Coeur_Demi\n");
            exit(EXIT_FAILURE);
        }
        SDL_SetColorKey(Coeur_Demi, SDL_SRCCOLORKEY, SDL_MapRGB(Coeur_Demi->format, 255, 255, 255));
        SDL_Surface* Coeur_Vide = SDL_LoadBMP("Pictures/Coeur_Vide.bmp");
        if (!Coeur_Vide)
        {
            printf("Impossibilite de charger l'image: Coeur_Vide\n");
            exit(EXIT_FAILURE);
        }
        SDL_SetColorKey(Coeur_Vide, SDL_SRCCOLORKEY, SDL_MapRGB(Coeur_Vide->format, 255, 255, 255));
        SDL_Surface* Argent = SDL_LoadBMP("Pictures/Argent.bmp");
        if (!Argent)
        {
            printf("Impossibilite de charger l'image: Argent\n");
            exit(EXIT_FAILURE);
        }
        SDL_SetColorKey(Argent, SDL_SRCCOLORKEY, SDL_MapRGB(Argent->format, 255, 255, 255));
        SDL_Surface* Tir = SDL_LoadBMP("Pictures/tir1.bmp");
        if (!Tir)
        {
            printf("Impossibilite de charger l'image: Tir\n");
            exit(EXIT_FAILURE);
        }
        SDL_SetColorKey(Tir, SDL_SRCCOLORKEY, SDL_MapRGB(Tir->format, 255, 255, 255));
        SDL_Surface* Tir2 = SDL_LoadBMP("Pictures/tir2.bmp");
        if (!Tir2)
        {
            printf("Impossibilite de charger l'image: Tir2\n");
            exit(EXIT_FAILURE);
        }
        SDL_SetColorKey(Tir2, SDL_SRCCOLORKEY, SDL_MapRGB(Tir2->format, 255, 255, 255));
        SDL_Surface* Tir3 = SDL_LoadBMP("Pictures/tir3.bmp");
        if (!Tir3)
        {
            printf("Impossibilite de charger l'image: Tir3\n");
            exit(EXIT_FAILURE);
        }
        SDL_SetColorKey(Tir3, SDL_SRCCOLORKEY, SDL_MapRGB(Tir3->format, 255, 255, 255));
        SDL_Surface* Ameliorer = SDL_LoadBMP("Pictures/Btt_up.bmp");
        if (!Ameliorer)
        {
            printf("Impossibilite de charger l'image: Btt_up\n");
            exit(EXIT_FAILURE);
        }
        SDL_Surface* Detruire = SDL_LoadBMP("Pictures/Btt_supp.bmp");
        if (!Detruire)
        {
            printf("Impossibilite de charger l'image: Btt_supp\n");
            exit(EXIT_FAILURE);
        }
        SDL_Surface* Chiffre0 = SDL_LoadBMP("Pictures/0.bmp");
        if (!Chiffre0)
        {
            printf("Impossibilite de charger l'image: 0\n");
            exit(EXIT_FAILURE);
        }
        SDL_SetColorKey(Chiffre0, SDL_SRCCOLORKEY, SDL_MapRGB(Chiffre0->format, 255, 255, 255));
        SDL_Surface* Chiffre1 = SDL_LoadBMP("Pictures/1.bmp");
        if (!Chiffre1)
        {
            printf("Impossibilite de charger l'image: 1\n");
            exit(EXIT_FAILURE);
        }
        SDL_SetColorKey(Chiffre1, SDL_SRCCOLORKEY, SDL_MapRGB(Chiffre1->format, 255, 255, 255));
        SDL_Surface* Chiffre2 = SDL_LoadBMP("Pictures/2.bmp");
        if (!Chiffre2)
        {
            printf("Impossibilite de charger l'image: 2\n");
            exit(EXIT_FAILURE);
        }
        SDL_SetColorKey(Chiffre2, SDL_SRCCOLORKEY, SDL_MapRGB(Chiffre2->format, 255, 255, 255));
        SDL_Surface* Chiffre3 = SDL_LoadBMP("Pictures/3.bmp");
        if (!Chiffre3)
        {
            printf("Impossibilite de charger l'image: 3\n");
            exit(EXIT_FAILURE);
        }
        SDL_SetColorKey(Chiffre3, SDL_SRCCOLORKEY, SDL_MapRGB(Chiffre3->format, 255, 255, 255));
        SDL_Surface* Chiffre4 = SDL_LoadBMP("Pictures/4.bmp");
        if (!Chiffre4)
        {
            printf("Impossibilite de charger l'image: 4\n");
            exit(EXIT_FAILURE);
        }
        SDL_SetColorKey(Chiffre4, SDL_SRCCOLORKEY, SDL_MapRGB(Chiffre4->format, 255, 255, 255));
        SDL_Surface* Chiffre5 = SDL_LoadBMP("Pictures/5.bmp");
        if (!Chiffre5)
        {
            printf("Impossibilite de charger l'image: 5\n");
            exit(EXIT_FAILURE);
        }
        SDL_SetColorKey(Chiffre5, SDL_SRCCOLORKEY, SDL_MapRGB(Chiffre5->format, 255, 255, 255));
        SDL_Surface* Chiffre6 = SDL_LoadBMP("Pictures/6.bmp");
        if (!Chiffre6)
        {
            printf("Impossibilite de charger l'image: 6\n");
            exit(EXIT_FAILURE);
        }
        SDL_SetColorKey(Chiffre6, SDL_SRCCOLORKEY, SDL_MapRGB(Chiffre6->format, 255, 255, 255));
        SDL_Surface* Chiffre7 = SDL_LoadBMP("Pictures/7.bmp");
        if (!Chiffre7)
        {
            printf("Impossibilite de charger l'image: 7\n");
            exit(EXIT_FAILURE);
        }
        SDL_SetColorKey(Chiffre7, SDL_SRCCOLORKEY, SDL_MapRGB(Chiffre7->format, 255, 255, 255));
        SDL_Surface* Chiffre8 = SDL_LoadBMP("Pictures/8.bmp");
        if (!Chiffre8)
        {
            printf("Impossibilite de charger l'image: 8\n");
            exit(EXIT_FAILURE);
        }
        SDL_SetColorKey(Chiffre8, SDL_SRCCOLORKEY, SDL_MapRGB(Chiffre8->format, 255, 255, 255));
        SDL_Surface* Chiffre9 = SDL_LoadBMP("Pictures/9.bmp");
        if (!Chiffre9)
        {
            printf("Impossibilite de charger l'image: 9\n");
            exit(EXIT_FAILURE);
        }
        SDL_SetColorKey(Chiffre9, SDL_SRCCOLORKEY, SDL_MapRGB(Chiffre9->format, 255, 255, 255));
        SDL_Surface* Vague = SDL_LoadBMP("Pictures/vague.bmp");
        if (!Vague)
        {
            printf("Impossibilite de charger l'image: vague\n");
            exit(EXIT_FAILURE);
        }
        SDL_SetColorKey(Vague, SDL_SRCCOLORKEY, SDL_MapRGB(Vague->format, 255, 255, 255));
        SDL_Surface* Ennemi = SDL_LoadBMP("Pictures/Ennemi-1-1.bmp");
        if (!Ennemi)
        {
            printf("Impossibilite de charger l'image: Ennemi\n");
            exit(EXIT_FAILURE);
        }
        SDL_SetColorKey(Ennemi, SDL_SRCCOLORKEY, SDL_MapRGB(Ennemi->format, 255, 255, 255));
        SDL_Surface* Victoire = SDL_LoadBMP("Pictures/victoire.bmp");
        if (!Victoire)
        {
            printf("Impossibilite de charger l'image: Victoire\n");
            exit(EXIT_FAILURE);
        }
        SDL_SetColorKey(Victoire, SDL_SRCCOLORKEY, SDL_MapRGB(Victoire->format, 255, 255, 255));
        SDL_Surface* Defaite = SDL_LoadBMP("Pictures/defaite.bmp");
        if (!Defaite)
        {
            printf("Impossibilite de charger l'image: Defaite\n");
            exit(EXIT_FAILURE);
        }
        SDL_SetColorKey(Defaite, SDL_SRCCOLORKEY, SDL_MapRGB(Defaite->format, 255, 255, 255));

        // Chargement d'une partie
        if(level == 0)
            loader(board, &level, &life, &gold, &entryPoint, &exitPoint, &wave);
        // Edition d'une carte
        else if(level == 5)
        {
            editor(board, &entryPoint, &exitPoint, screen, Terre, &level);
            wave = 1;
            life = 10;
        }
        // Partie normale
        else
        {
            initBoard(board, level, &entryPoint, &exitPoint); // Initialisation du board
            wave = 1;
            life = 10; // Changer selon les levels ?
        }

        // Caractéristiques des niveaux
        initLevel(level, &nbWave, &nbEnemyPerWave, &creationTimeEnemy, &positionTimeEnemy);
        nbEnemyPerWaveInitial = nbEnemyPerWave;

        // Début de la partie
        while(nbWave > 0)
        {
            // Début du chrono
            t1 = clock(); // Création des ennemis
            t6 = clock(); // Déplacement pixel par pixel

            // Initialisation
            nbEnemy = 1; // Pour rentrer la 1ère fois dans la boucle
            i = 0;
            nbEnemyCreated = 0;
            nbEnemyPerWave = nbEnemyPerWaveInitial * wave; // Augmentation du nombre d'ennemis selon la vague (Ex : 5 * 3 = 15 ennemis)
            creationTimeEnemy = creationTimeEnemy - (wave - 1) * 0.05; // Accélération de la création d'ennemis
            positionTimeEnemy = positionTimeEnemy - (wave - 1) * 0.025; // Accélération du déplacement des ennemis

            while(nbEnemyCreated < nbEnemyPerWave || nbEnemy > 0) // 1: créer au moins x ennemis / 2: attendre que les ennemis soient morts/arrivés à la fin
            {
                t4 = clock();
                // Sélection d'une tour
                while(SDL_PollEvent(&event))
                {
                    switch(event.type)
                    {
                        case SDL_MOUSEMOTION :
                        {
                            iMouseX = event.motion.x;
                            iMouseY = event.motion.y;
                            break;
                        }
                        case SDL_QUIT:
                            exit(EXIT_FAILURE);
                        case SDL_MOUSEBUTTONUP: //relachement du clic de la souris
                        {
                            if(event.button.button == SDL_BUTTON_LEFT)  //si clic gauche
                            {
                                if(iMouseX>907 && iMouseX<1193 && iMouseY>831 && iMouseY<895)
                                    pause = 1;
                                if(iMouseY>292 && iMouseY<383 && iMouseX>907 && iMouseX<1000)
                                    choix_tour = 1;
                                else if(iMouseY>292 && iMouseY<383 && iMouseX>1004 && iMouseX<1096)
                                    choix_tour = 2;
                                else if(iMouseY>292 && iMouseY<383 && iMouseX>1100 && iMouseX<1193)
                                    choix_tour = 3;
                                else if(iMouseX > 907 && iMouseX < 1047 && iMouseY > 750 && iMouseY < 830)
                                {
                                    ameliorer = 1;
                                    choix_tour = 0;
                                    iMouseX = lastClic.x;
                                    iMouseY = lastClic.y;
                                }
                                else if(iMouseX > 1052 && iMouseX < 1193 && iMouseY > 750 && iMouseY < 830)
                                {
                                    detruire = 1;
                                    choix_tour = 0;
                                    iMouseX = lastClic.x;
                                    iMouseY = lastClic.y;
                                }
                                else if(iMouseX > 900)
                                    choix_tour = 0;

                                if(iMouseX<900)// Coté PLATEAU
                                {
                                    if(choix_tour != 0)
                                    {
                                        tour = 1;
                                        selection = 0;
                                    }
                                    else if(choix_tour == 0)
                                    {
                                        selection = 1;
                                        lastClic.x = iMouseX;
                                        lastClic.y = iMouseY;
                                    }
                                }
                            }
                        }
                    }
                }

                // Menu pause
                while(pause == 1)
                {
                    while(SDL_PollEvent(&event))
                    {
                        switch (event.type)
                        {
                            case SDL_MOUSEMOTION :
                            {
                                iMouseX=event.motion.x;
                                iMouseY=event.motion.y;
                                break;
                            }
                            case SDL_MOUSEBUTTONUP:
                            {
                                if(event.button.button == SDL_BUTTON_LEFT)
                                {
                                    if(iMouseX>907 && iMouseX<1193 && iMouseY>135 && iMouseY<190)
                                        pause = 0;
                                    else if(iMouseX>907 && iMouseX<1193 && iMouseY>247 && iMouseY<302)
                                    {
                                        save(board, level, life, gold, entryPoint, exitPoint, wave);
                                        pause = 0;
                                    }
                                    else if(iMouseX>907 && iMouseX<1193 && iMouseY>354 && iMouseY<409)
                                        exit(EXIT_FAILURE);
                                }
                                break;
                            }
                        }
                    }

                    buildmap.x = 900;
                    buildmap.y = 0;
                    if(iMouseX>907 && iMouseX<1193 && iMouseY>135 && iMouseY<190)
                        SDL_BlitSurface(ATH_Pause_Continue, 0, screen, &buildmap);
                    else if(iMouseX>907 && iMouseX<1193 && iMouseY>247 && iMouseY<302)
                        SDL_BlitSurface(ATH_Pause_Save, 0, screen, &buildmap);
                    else if(iMouseX>907 && iMouseX<1193 && iMouseY>354 && iMouseY<409)
                        SDL_BlitSurface(ATH_Pause_Quit, 0, screen, &buildmap);
                    else
                        SDL_BlitSurface(ATH_Pause,0,screen,&buildmap);

                    buildmap.x = 899;
                    SDL_BlitSurface(ATH_Pause_Sep,0,screen,&buildmap);
                    SDL_Flip(screen);
                }
                SDL_FillRect(screen, 0, SDL_MapRGB(screen->format, 0, 0, 0));

                // Refresh map
                refreshBoard(board, entryPoint, iMouseX, iMouseY, &life, &gold, &wave, screen, Terre, &choix_tour, &descript, &tour, &selection, &ameliorer, &detruire, Porte_arche, Porte_mortier, Porte_tde, Chemin_Vertical, Chemin_Horizontal, Chemin_Bas_droite, Chemin_Bas_gauche, Chemin_Haut_droite, Chemin_Haut_gauche, ATH, ATH_Tour1, ATH_Tour2, ATH_Tour3, Tour1, Tour12, Tour13, Tour2, Tour22, Tour23, Tour3, Tour32, Tour33, Tour_transp1, Tour_transp2, Tour_transp3, Description_Tour11, Description_Tour12, Description_Tour13, Description_Tour21, Description_Tour22, Description_Tour23, Description_Tour31, Description_Tour32, Description_Tour33, Coeur_Plein, Coeur_Demi, Coeur_Vide, Argent, Tir, Tir2, Tir3, Ennemi, Ameliorer, Detruire, Chiffre0, Chiffre1, Chiffre2, Chiffre3, Chiffre4, Chiffre5, Chiffre6, Chiffre7, Chiffre8, Chiffre9, Vague);

                // Attente de 10 sec avant la nouvelle vague
                if(wait == 0)
                {
                    // Pour rentrer dans la boucle la première fois
                    if(i == 0)
                        nbEnemy = 0;

                    t3 = clock();
                    t5 = clock();
                    t7 = clock();
                    t8 = clock();

                    differenceTime =(((float)t3 - (float)t1) / 1000000.0F ) * 1000; // Temps en millisecondes
                    // Création des ennemis
                    if(differenceTime >= creationTimeEnemy && nbEnemyCreated < nbEnemyPerWave && board[entryPoint.y][entryPoint.x].type == 1) // 0.5 secondes de plus de base, pour éviter qu'un ennemi passe sur l'autre lors de virages
                    {
                        t1 = t3;
                        board[entryPoint.y][entryPoint.x].type = 3;
                        board[entryPoint.y][entryPoint.x].actor = malloc(sizeof(enemy));
                        ((enemy *)board[entryPoint.y][entryPoint.x].actor)->health = 100 + ((wave - 1) * 40); // La vie des ennemis augmentent à chaque vague
                        ((enemy *)board[entryPoint.y][entryPoint.x].actor)->relativePosition.x = 30;
                        ((enemy *)board[entryPoint.y][entryPoint.x].actor)->relativePosition.y = 30;
                        ((enemy *)board[entryPoint.y][entryPoint.x].actor)->timeBeforeTurn = 0.0;
                        nbEnemy++;
                        nbEnemyCreated++;
                    }

                    // Déplacer les ennemis pixel par pixel
                    differenceTime =(((float)t7 - (float)t6) / 1000000.0F ) * 1000; // Temps en millisecondes
                    if(differenceTime >= (positionTimeEnemy/TAILLE_CASE))
                    {
                        coordinatesEnemy(board, entryPoint, exitPoint, &nbEnemy, &life);
                        t6 = t7;
                    }

                    // Tirs de défenses
                    for(k=0;k<LIGNES;k++)
                    {
                        for(l=0;l<COLONNES;l++)
                        {
                            if(board[k][l].type == 2)
                            {
                                detectEnemy(board, entryPoint, l, k, &nbEnemy, t5, t8, &gold);
                            }
                        }
                    }

                    // Après avoir déplacer les ennemis, on regarde si la vie du joueur est > 0
                    if(life > 0) // Si oui, on continue la partie
                    {
                        // Repérer quand tous les ennemis sont morts ou sont arrivés à la fin
                        if(nbEnemy == 0 && nbEnemyCreated == 0)
                        {
                            nbEnemy = 1;
                            i = 0;
                        }
                        else
                            i++;
                    }
                    else
                    {
                        nbEnemy = 0;
                        nbWave = 0;
                        result = 1;
                        nbEnemyCreated = nbEnemyPerWave;
                    }
                }
                differenceTime = (((float)t4 - (float)t2) / 1000000.0F ) * 1000; // Temps en millisecondes
                if(differenceTime >= 10) // Attendre 10 secondes avant de passer à la vague suivante
                    wait = 0;
            }
            if(result != 1) // Si la partie continue, on change de vague
            {
                wave++;
                nbWave--;
                wait = 1;
                t2 = clock();
            }
        }

        // Affichage du résultat
        if(result == 1)
        {
            // Défaite
            buildmap.x = 0;
            buildmap.y = 0;
            SDL_BlitSurface(Defaite, 0, screen, &buildmap);
        }
        else
        {
            // Victoire
            buildmap.x = 0;
            buildmap.y = 0;
            SDL_BlitSurface(Victoire, 0, screen, &buildmap);
        }
        SDL_Flip(screen);
        pause_clic();

        // Libération
        SDL_FreeSurface(Loading);
        SDL_FreeSurface(Terre);
        SDL_FreeSurface(ATH_Pause);
        SDL_FreeSurface(ATH_Pause_Sep);
        SDL_FreeSurface(ATH_Pause_Continue);
        SDL_FreeSurface(ATH_Pause_Save);
        SDL_FreeSurface(ATH_Pause_Quit);
        SDL_FreeSurface(Porte_arche);
        SDL_FreeSurface(Chemin_Vertical);
        SDL_FreeSurface(Chemin_Horizontal);
        SDL_FreeSurface(Chemin_Bas_droite);
        SDL_FreeSurface(Chemin_Bas_gauche);
        SDL_FreeSurface(Chemin_Haut_droite);
        SDL_FreeSurface(Chemin_Haut_gauche);
        SDL_FreeSurface(ATH);
        SDL_FreeSurface(ATH_Tour1);
        SDL_FreeSurface(ATH_Tour2);
        SDL_FreeSurface(ATH_Tour3);
        SDL_FreeSurface(Tour1);
        SDL_FreeSurface(Tour2);
        SDL_FreeSurface(Tour3);
        SDL_FreeSurface(Tour_transp1);
        SDL_FreeSurface(Tour_transp2);
        SDL_FreeSurface(Tour_transp3);
        SDL_FreeSurface(Description_Tour11);
        SDL_FreeSurface(Ennemi);
        SDL_FreeSurface(Coeur_Plein);
        SDL_FreeSurface(Coeur_Demi);
        SDL_FreeSurface(Coeur_Vide);
        SDL_FreeSurface(Argent);
        SDL_FreeSurface(Tir);
        SDL_FreeSurface(Tir2);
        SDL_FreeSurface(Tir3);
        SDL_FreeSurface(Victoire);
        SDL_FreeSurface(Defaite);
    }

    /* --------------------- Mode édition (création d'un niveau) -------------------- */
    void editor(cell board[LIGNES][COLONNES], coordinates *entryPoint, coordinates *exitPoint, SDL_Surface *screen, SDL_Surface *Terre, int *level)
    {
        // DEMANDER AU JOUEUR LE NIVEAU DE LA PARTIE ?
        int i = 0, j = 0;
        int voisin = 0;
        int continuer = 0;
        int chemin = 0;
        int iMouseX = 0, iMouseY = 0;
        int x = 0, y = 0;
        int error = 0;
        SDL_Event event;
        SDL_Rect buildmap;
        srand(time(NULL));
        int ath = 0;

        SDL_Surface* Chemin_pot = SDL_LoadBMP("Pictures/Chemin_pot.bmp");
        if(!Chemin_pot)
        {
            printf("Impossibilite de charger l'image: Chemin_pot.\n");
            exit(EXIT_FAILURE);
        }
        SDL_Surface* ATH_editeur = SDL_LoadBMP("Pictures/ATH_editeur.bmp");
        if(!ATH_editeur)
        {
            printf("Impossibilite de charger l'image: ATH_editeur.\n");
            exit(EXIT_FAILURE);
        }
        SDL_Surface* ATH_editeur_difficile = SDL_LoadBMP("Pictures/ATH_editeur_difficile.bmp");
        if(!ATH_editeur_difficile)
        {
            printf("Impossibilite de charger l'image: ATH_editeur_difficile.\n");
            exit(EXIT_FAILURE);
        }
        SDL_Surface* ATH_editeur_extreme = SDL_LoadBMP("Pictures/ATH_editeur_extreme.bmp");
        if(!ATH_editeur_extreme)
        {
            printf("Impossibilite de charger l'image: ATH_editeur_extreme.\n");
            exit(EXIT_FAILURE);
        }
        SDL_Surface* ATH_editeur_facile = SDL_LoadBMP("Pictures/ATH_editeur_facile.bmp");
        if(!ATH_editeur_facile)
        {
            printf("Impossibilite de charger l'image: ATH_editeur_facile.\n");
            exit(EXIT_FAILURE);
        }
        SDL_Surface* ATH_editeur_moyen = SDL_LoadBMP("Pictures/ATH_editeur_moyen.bmp");
        if(!ATH_editeur_moyen)
        {
            printf("Impossibilite de charger l'image: ATH_editeur_moyen.\n");
            exit(EXIT_FAILURE);
        }
        SDL_Surface* ATH_Pause_Sep = SDL_LoadBMP("Pictures/ATH_Pause_sep.bmp");
        if(!ATH_Pause_Sep)
        {
            printf("Impossibilite de charger l'image: ATH_Pause_Sep.\n");
            exit(EXIT_FAILURE);
        }

        // Initialisation de toutes les cases à 0
        for(i=0;i<LIGNES;i++)
        {
            for(j=0;j<COLONNES;j++)
            {
                board[i][j].type = 0;
                board[i][j].actor = NULL;
                board[i][j].next = NULL;
            }
        }

        // Détermination du point d'entrée
        entryPoint->x = rand() % (COLONNES/5);
        if(entryPoint->x > 0)
        {
            // On choisit soit la première soit la dernière ligne
            entryPoint->y = rand() % 2;
            if(entryPoint->y == 1)
                entryPoint->y = LIGNES-1;
        }
        else // X = 0
        {
            entryPoint->y = rand() % 2;
            if(entryPoint->y == 1) // Coin en haut à gauche
                entryPoint->y = rand() % (LIGNES/5); // De 0 à 5
            else // Coin en bas à gauche
                entryPoint->y = (rand() % (LIGNES/5)) + (LIGNES - (LIGNES/5));
        }

        do
        {
            clearBoard(board, -1, 0); // Nettoie les résidus
            board[entryPoint->y][entryPoint->x].type = 1;
            continuer = 0;
            while(continuer == 0)
            {
                while(SDL_PollEvent(&event))
                {
                    switch(event.type)
                    {
                        case SDL_MOUSEMOTION :
                        {
                            iMouseX = event.motion.x;
                            iMouseY = event.motion.y;
                            break;
                        }
                        case SDL_MOUSEBUTTONUP:
                        {
                            if(event.button.button==SDL_BUTTON_LEFT)
                            {
                                if(iMouseX < 900)
                                    chemin = 1;
                                if(iMouseX > 907 && iMouseX < 1193 && iMouseY > 135 && iMouseY < 190)
                                    *level = 1;
                                else if(iMouseX > 907 && iMouseX < 1193 && iMouseY > 247 && iMouseY < 302)
                                    *level = 2;
                                else if(iMouseX > 907 && iMouseX < 1193 && iMouseY > 354 && iMouseY < 409)
                                    *level = 3;
                                else if(iMouseX > 907 && iMouseX < 1193 && iMouseY > 459 && iMouseY < 519)
                                    *level = 4;
                                else if(iMouseX > 907 && iMouseX < 1193 && iMouseY > 826 && iMouseY < 886 && *level > 0 && *level < 5)
                                    continuer = 1;
                            }
                            break;
                        }
                    }
                }

                // Nettoyage
                SDL_FillRect(screen, 0, SDL_MapRGB(screen->format, 0, 0, 0));

                // Ecrire
                if(chemin == 1)
                {
                    for(i=0;i<LIGNES;i++)
                    {
                        if(iMouseX>i*60 && iMouseX<(i+1)*60 && iMouseX<900)
                            x = i;
                        if(iMouseY>i*60 && iMouseY<(i+1)*60)
                            y = i;
                    }

                    // Différents cas impossibles
                    if(y > 0 && x > 0 && board[y-1][x].type == 1 && board[y-1][x-1].type == 1 && board[y][x-1].type == 1)
                        chemin = 0;
                    else if(y < LIGNES-1 && x > 0 && board[y+1][x].type == 1 && board[y+1][x-1].type == 1 && board[y][x-1].type == 1)
                        chemin = 0;
                    else if(y < LIGNES-1 && x < COLONNES-1 && board[y+1][x].type == 1 && board[y+1][x+1].type == 1 && board[y][x+1].type == 1)
                        chemin = 0;
                    else if(y > 0 && x < COLONNES-1 && board[y-1][x+1].type == 1 && board[y-1][x].type == 1 && board[y][x+1].type == 1)
                        chemin = 0;
                    else if(y > 0 && x < COLONNES-1 && x > 0 && board[y-1][x-1].type == 1 && board[y-1][x].type == 1 && board[y-1][x+1].type == 1)
                        chemin = 0;
                    else if(y > 0 && x > 0 && y < LIGNES-1 && board[y-1][x-1].type == 1 && board[y][x-1].type == 1 && board[y+1][x-1].type == 1)
                        chemin = 0;
                    else if(y > 0 && x < COLONNES-1 && y < LIGNES-1 && board[y-1][x+1].type == 1 && board[y+1][x+1].type == 1 && board[y][x+1].type == 1)
                        chemin = 0;
                    else if(x > 0 && y < LIGNES-1 && x < COLONNES-1 && board[y+1][x-1].type == 1 && board[y+1][x].type == 1 && board[y+1][x+1].type == 1)
                        chemin = 0;
                    else if(y > 1 && x > 0 && board[y-2][x].type == 1 && board[y-1][x].type == 1 && board[y-1][x-1].type == 1)
                        chemin = 0;
                    else if(y > 1 && x < COLONNES-1 && board[y-2][x].type == 1 && board[y-1][x].type == 1 && board[y-1][x+1].type == 1)
                        chemin = 0;
                    else if(x < COLONNES-2 && y > 0 && board[y][x+2].type == 1 && board[y][x+1].type == 1 && board[y-1][x+1].type == 1)
                        chemin = 0;
                    else if(x < COLONNES-2 && y < LIGNES-1 && board[y][x+2].type == 1 && board[y][x+1].type == 1 && board[y+1][x+1].type == 1)
                        chemin = 0;
                    else if(y < LIGNES-2 && x < COLONNES-1 && board[y+2][x].type == 1 && board[y+1][x].type == 1 && board[y+1][x+1].type == 1)
                        chemin = 0;
                    else if(y < LIGNES-2 && x > 0 && board[y+2][x].type == 1 && board[y+1][x].type == 1 && board[y+1][x-1].type == 1)
                        chemin = 0;
                    else if(x > 1 && y < LIGNES-1 && board[y][x-2].type == 1 && board[y][x-1].type == 1 && board[y+1][x-1].type == 1)
                        chemin = 0;
                    else if(x > 1 && y > 0 && board[y][x-2].type == 1 && board[y][x-1].type == 1 && board[y-1][x-1].type == 1)
                        chemin = 0;
                    else if(y > 0 && x > 0 && x < COLONNES-1 && board[y-1][x].type == 1 && board[y][x-1].type == 1 && board[y][x+1].type == 1)
                        chemin = 0;
                    else if(y > 0 && y < LIGNES-1 && x < COLONNES-1 && board[y-1][x].type == 1 && board[y+1][x].type == 1 && board[y][x+1].type == 1)
                        chemin = 0;
                    else if(y > 0 && y < LIGNES-1 && x > 0 && board[y-1][x].type == 1 && board[y+1][x].type == 1 && board[y][x-1].type == 1)
                        chemin = 0;
                    else if(y < LIGNES-1 && x > 0 && x < COLONNES-1 && board[y+1][x].type == 1 && board[y][x-1].type == 1 && board[y][x+1].type == 1)
                        chemin = 0;


                    if(board[y][x].type == 0 && chemin == 1)
                    {
                        board[y][x].type = 1;
                        voisin = 0;
                        if(y > 0 && board[entryPoint->y-1][entryPoint->x].type == 1)
                           voisin++;
                        if(y < LIGNES-1 && board[entryPoint->y+1][entryPoint->x].type == 1)
                           voisin++;
                        if(x > 0 && board[entryPoint->y][entryPoint->x-1].type == 1)
                           voisin++;
                        if(x < COLONNES-1 && board[entryPoint->y][entryPoint->x+1].type == 1)
                           voisin++;

                        if(voisin > 1)
                            board[y][x].type = 0;
                    }
                    else if(board[y][x].type == 1 && (x != entryPoint->x || y != entryPoint->y))
                        board[y][x].type = 0;
                    chemin = 0;
                }

                //REFRESH TERRE
                buildmap.x = 0;
                buildmap.y = 0;
                for(i=0;i<LIGNES;i++)
                {
                    for(j=0;j<COLONNES;j++)
                    {
                        if(board[i][j].type == 0)
                            SDL_BlitSurface(Terre, 0, screen, &buildmap);

                        buildmap.x = buildmap.x + TAILLE_CASE;
                    }
                    buildmap.x = 0;
                    buildmap.y = buildmap.y + TAILLE_CASE;
                }

                //REFRESH CHEMIN
                buildmap.x = 0;
                buildmap.y = 0;
                for(i=0;i<LIGNES;i++)
                {
                    for(j=0;j<COLONNES;j++)
                    {
                        if(board[i][j].type == 1)
                            SDL_BlitSurface(Chemin_pot, 0, screen, &buildmap);

                        buildmap.x = buildmap.x + TAILLE_CASE;
                    }
                    buildmap.x = 0;
                    buildmap.y = buildmap.y + TAILLE_CASE;
                }

                // REFRESH ATH
                buildmap.x = 900;
                buildmap.y = 0;
                SDL_BlitSurface(ATH_editeur, 0, screen, &buildmap);

                buildmap.x = 900;
                buildmap.y = 0;

                if((iMouseX > 907 && iMouseX < 1193 && iMouseY > 135 && iMouseY < 190) || *level == 1)
                    SDL_BlitSurface(ATH_editeur_facile, 0, screen, &buildmap);
                else if((iMouseX > 907 && iMouseX < 1193 && iMouseY > 247 && iMouseY < 302) || *level == 2)
                    SDL_BlitSurface(ATH_editeur_moyen, 0, screen, &buildmap);
                else if((iMouseX > 907 && iMouseX < 1193 && iMouseY > 354 && iMouseY < 409) || *level == 3)
                    SDL_BlitSurface(ATH_editeur_difficile, 0, screen, &buildmap);
                else if((iMouseX > 907 && iMouseX < 1193 && iMouseY > 459 && iMouseY < 519) || *level == 4)
                    SDL_BlitSurface(ATH_editeur_extreme, 0, screen, &buildmap);

                buildmap.x = 899;
                buildmap.y = 0;
                SDL_BlitSurface(ATH_Pause_Sep, 0, screen, &buildmap);
                SDL_Flip(screen);
            }

            // Trouver le point de sortie
            // On part du point d'entrée: une fois que l'on ne trouve plus de 1, on est sur le point de sortie
            continuer = 0;
            x = entryPoint->x;
            y = entryPoint->y;
            while(continuer == 0)
            {
                board[y][x].type = 5;
                if(y > 0 && board[y-1][x].type == 1)
                    y = y - 1;
                else if(y < LIGNES-1 && board[y+1][x].type == 1)
                    y = y + 1;
                else if(x > 0 && board[y][x-1].type == 1)
                    x = x - 1;
                else if(x < COLONNES-1 && board[y][x+1].type == 1)
                    x = x + 1;
                else
                    continuer = 1;
            }
            clearBoard(board, 1, 0); // Nettoie les résidus
            clearBoard(board, 5, 1); // Remet le chemin à 1
            exitPoint->x = x;
            exitPoint->y = y;

            // Vérifier que la sortie appartienne à un bord
            if(exitPoint->x == 0 || exitPoint->x == COLONNES-1 || exitPoint->y == 0 || exitPoint->y == LIGNES-1)
                error = 1;
            else
                error = 0;

            // Vérifier que le chemin est faisable (remplir le vide par des obstacles)
            clearBoard(board, 0, -1); // Nettoie les résidus

            // Si la sortie est bonne, on regarde que le chemin soit faisable
            if(error == 1)
            {
                clearBoard(board, 1, 0); // Nettoie les résidus
                error = pathfinding(board, *exitPoint, *entryPoint); // Remplissage du plateau avec les coûts de chaque case
            }
        } while(error == 0);
        road(board, *exitPoint, *entryPoint); // A partir du coût de chaque case, on trouve un chemin

        // Nettoyage du plateau
        for(i=0;i<LIGNES;i++)
        {
            for(j=0;j<COLONNES;j++)
            {
                if(board[i][j].type != -2 && board[i][j].type != 1) // On ne garde que le chemin
                    board[i][j].type = 0;
            }
        }

        // On remplace les -2 par 1
        clearBoard(board, -2, 1);
        board[entryPoint->y][entryPoint->x].type = 1;

        // Chaînage du chemin
        link(board, *entryPoint);
    }

    /* ----------------- Chargement d'un niveau à partir d'un fichier --------------- */
    void loader(cell board[LIGNES][COLONNES], int *level, int *life, int *gold, coordinates *entryPoint, coordinates *exitPoint, int *wave)
    {

        int nbDefense = 0;
        int i = 0, j = 0;
        int x = 0, y = 0;
        int tmp = 0;
        float tmpFloat = 0.0;
        FILE* fichier = NULL;

        fichier = fopen("sauvegarde.txt", "r+");
        // Chargement des données du fichier
        if(fichier != NULL)
        {
            // Level de la partie
            fscanf(fichier, "%d", level);
            fseek(fichier, +1, SEEK_CUR);

            // Initialisation des pointeurs à NULL
            for(i=0;i<LIGNES;i++)
            {
                for(j=0;j<COLONNES;j++)
                {
                    board[i][j].actor = NULL;
                    board[i][j].next = NULL;
                }
            }

            // Board
            for(i=0;i<LIGNES;i++)
            {
                for(j=0;j<COLONNES;j++)
                {
                    fscanf(fichier, "%d", &board[i][j].type);
                    fseek(fichier, +1, SEEK_CUR);
                }
                fseek(fichier, +1, SEEK_CUR);
            }

            // Point d'entrée
            fscanf(fichier, "%d", &entryPoint->x);
            fseek(fichier, +1, SEEK_CUR);
            fscanf(fichier, "%d", &entryPoint->y);
            fseek(fichier, +1, SEEK_CUR);

            // Point de sortie
            fscanf(fichier, "%d", &exitPoint->x);
            fseek(fichier, +1, SEEK_CUR);
            fscanf(fichier, "%d", &exitPoint->y);
            fseek(fichier, +1, SEEK_CUR);

            // Chaînage
            link(board, *entryPoint);

            // Vie
            fseek(fichier, +1, SEEK_CUR);
            fscanf(fichier, "%d", life);
            fseek(fichier, +1, SEEK_CUR);

            // Gold
            fseek(fichier, +1, SEEK_CUR);
            fscanf(fichier, "%d", gold);
            fseek(fichier, +1, SEEK_CUR);

            // Vague
            fseek(fichier, +1, SEEK_CUR);
            fscanf(fichier, "%d", wave);
            fseek(fichier, +1, SEEK_CUR);

            // Nombre de défenses
            for(i=0;i<LIGNES;i++)
            {
                for(j=0;j<COLONNES;j++)
                {
                    if(board[i][j].type == 2)
                        nbDefense++;
                }
            }

            // Défenses
            for(i=0;i<nbDefense;i++)
            {
                // X et Y
                fseek(fichier, +1, SEEK_CUR);
                fscanf(fichier, "%d ", &x);
                fscanf(fichier, "%d", &y);
                fseek(fichier, +1, SEEK_CUR);

                // Réservation de la défense
                board[y][x].actor = malloc(sizeof(defense));
                // Caractéristiques
                    // Type de défense
                    fscanf(fichier, "%d", &tmp);
                    ((defense *)board[y][x].actor)->type = tmp;
                    fseek(fichier, +1, SEEK_CUR);
                    // Dommages
                    fscanf(fichier, "%d", &tmp);
                    ((defense *)board[y][x].actor)->damage = tmp;
                    fseek(fichier, +1, SEEK_CUR);
                    // Portée
                    fscanf(fichier, "%d", &tmp);
                    ((defense *)board[y][x].actor)->range = tmp;
                    fseek(fichier, +1, SEEK_CUR);
                    // Vitesse d'attaque
                    fscanf(fichier, "%f", &tmpFloat);
                    ((defense *)board[y][x].actor)->rate = tmpFloat;
                    fseek(fichier, +1, SEEK_CUR);
                    // Prix
                    fscanf(fichier, "%d", &tmp);
                    ((defense *)board[y][x].actor)->price = tmp;
                    fseek(fichier, +1, SEEK_CUR);

                    // Autres
                    ((defense *)board[y][x].actor)->lastAttack = clock();
                    ((defense *)board[y][x].actor)->shot.x = 30;
                    ((defense *)board[y][x].actor)->shot.y = 30;
                    ((defense *)board[y][x].actor)->shotTime = clock();
                    ((defense *)board[y][x].actor)->attack = 0;
            }

            fclose(fichier);
        }
        else
            printf("Erreur : le fichier \"sauvegarde.txt\" n'est pas present.\n");
    }

    /* --------------------------- Sauvegarde d'une partie -------------------------- */
    void save(cell board[LIGNES][COLONNES], int level, int life, int gold, coordinates entryPoint, coordinates exitPoint, int wave)
    {
        int i = 0, j = 0;
        FILE* fichier = NULL;

        fichier = fopen("sauvegarde.txt", "r+");
        // Sauvegarde des données dans le fichier
        if(fichier != NULL)
        {
            // Level de la partie
            fprintf(fichier, "%d\n", level);

            // Sauvegarde du plateau
            for(i=0;i<LIGNES;i++)
            {
                for(j=0;j<COLONNES;j++)
                {
                    if(board[i][j].type == 3)
                        fprintf(fichier, "1 ");
                    else
                        fprintf(fichier, "%d ", board[i][j].type);
                }
                fprintf(fichier, "\n");
            }

            // Points d'entrée et de sortie
            fprintf(fichier, "%d ", entryPoint.x);
            fprintf(fichier, "%d\n", entryPoint.y);
            fprintf(fichier, "%d ", exitPoint.x);
            fprintf(fichier, "%d\n\n", exitPoint.y);

            // Vie
            fprintf(fichier, "%d\n\n", life);

            // Gold (Argent)
            fprintf(fichier, "%d\n\n", gold);

            // Vague
            fprintf(fichier, "%d\n\n", wave);

            // Sauvegarde des défenses
            for(i=0;i<LIGNES;i++)
            {
                for(j=0;j<COLONNES;j++)
                {
                    if(board[i][j].type == 2)
                    {
                        // X et Y
                        fprintf(fichier, "%d ", j); // X
                        fprintf(fichier, "%d\n", i); // Y
                        fprintf(fichier, "%d\n", ((defense *)board[i][j].actor)->type); // Type
                        fprintf(fichier, "%d\n", ((defense *)board[i][j].actor)->damage); // Dommages
                        fprintf(fichier, "%d\n", ((defense *)board[i][j].actor)->range); // Portée
                        fprintf(fichier, "%f\n", ((defense *)board[i][j].actor)->rate); // Vitesse d'attaque
                        fprintf(fichier, "%d\n\n", ((defense *)board[i][j].actor)->price); // Prix
                    }
                }
            }
            fclose(fichier);
        }
        else
            printf("Erreur : le fichier \"sauvegarde.txt\" n'est pas present.\n");
    }

/* ---------------------------------------------------------------------------------- */
/* ------------------------------------- BOARD -------------------------------------- */
/* ---------------------------------------------------------------------------------- */

    /* ---------------------- Génération aléatoire d'un chemin ---------------------- */
    void initBoard(cell board[LIGNES][COLONNES], int level, coordinates *entryPoint, coordinates *exitPoint)
    {
        int i = 0, j = 0;
        int result = 0;

        // Initialisation de toutes les cases à 0
        for(i=0;i<LIGNES;i++)
        {
            for(j=0;j<COLONNES;j++)
            {
                board[i][j].type = 0;
                board[i][j].actor = NULL;
                board[i][j].next = NULL;
            }
        }

        if(level == 1)
        {
            board[0][3].type = 1;
            board[1][3].type = 1;
            for(i=3;i<=13;i++)
                board[1][i].type = 1;
            for(i=2;i<=5;i++)
                board[i][13].type = 1;
            for(i=0;i<=12;i++)
                board[5][i].type = 1;
            for(i=6;i<=13;i++)
                board[i][0].type = 1;
            for(i=1;i<=4;i++)
                board[13][i].type = 1;
            for(i=7;i<=12;i++)
                board[i][4].type = 1;
            for(i=5;i<=13;i++)
                board[7][i].type = 1;
            for(i=8;i<=11;i++)
                board[i][13].type = 1;
            for(i=7;i<=12;i++)
                board[11][i].type = 1;
            for(i=12;i<=13;i++)
                board[i][7].type = 1;
            for(i=8;i<=13;i++)
                board[13][i].type = 1;
            board[14][13].type = 1;

            entryPoint->x = 3;
            entryPoint->y = 0;
            exitPoint->x = 13;
            exitPoint->y = 14;
        }
        else if(level == 2)
        {
            for(i=0;i<=13;i++)
                board[i][1].type = 1;
            for(i=1;i<=13;i++)
                board[13][i].type = 1;
            for(i=1;i<=13;i++)
                board[i][13].type = 1;
            for(i=0;i<=13;i++)
                board[i][1].type = 1;
            for(i=5;i<=12;i++)
                board[1][i].type = 1;
            for(i=2;i<=9;i++)
                board[i][5].type = 1;
            for(i=6;i<=9;i++)
                board[9][i].type = 1;
            for(i=6;i<=9;i++)
                board[9][i].type = 1;
            board[8][9].type = 1;
            for(i=7;i<=9;i++)
                board[7][i].type = 1;
            for(i=3;i<=6;i++)
                board[i][7].type = 1;
            for(i=8;i<=11;i++)
                board[3][i].type = 1;
            for(i=4;i<=11;i++)
                board[i][11].type = 1;
            for(i=3;i<=10;i++)
                board[11][i].type = 1;
            for(i=0;i<=10;i++)
                board[i][3].type = 1;

            entryPoint->x = 1;
            entryPoint->y = 0;
            exitPoint->x = 3;
            exitPoint->y = 0;
        }
        else if(level == 3)
        {
            board[14][1].type = 1;
            board[13][1].type = 1;
            board[12][1].type = 1;
            board[11][1].type = 1;
            board[11][2].type = 1;
            board[11][3].type = 1;
            board[12][3].type = 1;
            board[13][3].type = 1;
            board[13][4].type = 1;
            board[13][5].type = 1;
            board[13][6].type = 1;
            board[13][7].type = 1;
            board[13][8].type = 1;
            board[13][9].type = 1;
            board[12][9].type = 1;
            board[11][9].type = 1;
            board[10][9].type = 1;
            board[9][9].type = 1;
            board[8][9].type = 1;
            board[7][9].type = 1;
            board[6][9].type = 1;
            board[6][8].type = 1;
            board[6][7].type = 1;
            board[6][6].type = 1;
            board[6][5].type = 1;
            board[6][4].type = 1;
            board[7][4].type = 1;
            board[8][4].type = 1;
            board[8][3].type = 1;
            board[8][2].type = 1;
            board[8][1].type = 1;
            board[7][1].type = 1;
            board[6][1].type = 1;
            board[5][1].type = 1;
            board[4][1].type = 1;
            board[3][1].type = 1;
            board[2][1].type = 1;
            board[1][1].type = 1;
            board[1][2].type = 1;
            board[1][3].type = 1;
            board[1][4].type = 1;
            board[2][4].type = 1;
            board[3][4].type = 1;
            board[3][5].type = 1;
            board[3][6].type = 1;
            board[3][7].type = 1;
            board[2][7].type = 1;
            board[1][7].type = 1;
            board[1][8].type = 1;
            board[1][9].type = 1;
            board[2][9].type = 1;
            board[3][9].type = 1;
            board[4][9].type = 1;
            board[4][10].type = 1;
            board[4][11].type = 1;
            board[3][11].type = 1;
            board[2][11].type = 1;
            board[1][11].type = 1;
            board[1][12].type = 1;
            board[1][13].type = 1;
            board[2][13].type = 1;
            board[3][13].type = 1;
            board[4][13].type = 1;
            board[5][13].type = 1;
            board[6][13].type = 1;
            board[6][12].type = 1;
            board[6][11].type = 1;
            board[7][11].type = 1;
            board[8][11].type = 1;
            board[9][11].type = 1;
            board[10][11].type = 1;
            board[11][11].type = 1;
            board[12][11].type = 1;
            board[13][11].type = 1;
            board[13][12].type = 1;
            board[13][13].type = 1;
            board[12][13].type = 1;
            board[11][13].type = 1;
            board[11][14].type = 1;

            entryPoint->x = 1;
            entryPoint->y = 14;
            exitPoint->x = 14;
            exitPoint->y = 11;
        }
        else if(level == 4) // Aléatoire
        {
            // Génération d'un chemin faisable
            while(result == 0) // result = 0, chemin impossible (on remet tout à 0, on trouve de nouvelles coordonnées d'entrée et de sortie, on repositionne des obstacles)
            {
                // Initialisation de toutes les cases à 0
                for(i=0;i<LIGNES;i++)
                {
                    for(j=0;j<COLONNES;j++)
                    {
                        board[i][j].type = 0;
                        board[i][j].actor = NULL;
                        board[i][j].next = NULL;
                    }
                }

                // Point d'entrée (partie gauche du plateau)
                entryPoint->x = rand() % (COLONNES/5); // On trouve un x parmis les 8 (40/5) premières cases
                if(entryPoint->x > 0) // Cases 1 à 7
                {
                    // On choisit soit la première soit la dernière ligne
                    entryPoint->y = rand() % 2;
                    if(entryPoint->y == 1)
                        entryPoint->y = LIGNES-1;
                }
                else // Case 0
                {
                    entryPoint->y = rand() % 2;
                    if(entryPoint->y == 1) // Coin en haut à gauche
                        entryPoint->y = rand() % (LIGNES/5); // De 0 à 5
                    else // Coin en bas à gauche
                        entryPoint->y = (rand() % (LIGNES/5)) + (LIGNES - (LIGNES/5));
                }
                board[entryPoint->y][entryPoint->x].type = 1;

                // Point de sortie
                // Si le point d'entrée est en haut à gauche, le point de sortie est en bas à droite
                if(entryPoint->y < (LIGNES/2))
                {
                    exitPoint->x = (rand() % (COLONNES/5)) + (COLONNES - (COLONNES/5));
                    if(exitPoint->x == COLONNES-1) // Case 39
                        exitPoint->y = (rand() % (LIGNES/5)) + (LIGNES - (LIGNES/5));
                    else
                        exitPoint->y = LIGNES-1;
                }
                // Sinon si le point d'entrée est en bas à gauche, le point de sortie est en haut à droite
                else
                {
                    exitPoint->x = (rand() % (COLONNES/5)) + (COLONNES - (COLONNES/5)); // [0;8] + 32 = [32;40]
                    if(exitPoint->x == COLONNES-1) // Case 39
                        exitPoint->y = rand() % (LIGNES/5);
                    else
                        exitPoint->y = 0;
                }
                board[exitPoint->y][exitPoint->x].type = 1;

                setBlock(board, 1); // Level = introduction de + ou - d'obstacles sur la plateau
                board[exitPoint->y][exitPoint->x].type = 0; // Recherche du chemin le + court nécessite un 0

                result = pathfinding(board, *exitPoint, *entryPoint); // Remplissage du plateau avec les coûts de chaque case
            }
            road(board, *exitPoint, *entryPoint); // A partir du coût de chaque case, on trouve un chemin

            // Nettoyage du plateau
            for(i=0;i<LIGNES;i++)
            {
                for(j=0;j<COLONNES;j++)
                {
                    if(board[i][j].type != -2 && board[i][j].type != 1) // On ne garde que le chemin
                        board[i][j].type = 0;
                }
            }

            // On remplace les -2 par 1
            clearBoard(board, -2, 1);
        }

        // Chaînage du chemin
        link(board, *entryPoint);
    }

    /* ------------------------ Chainage des cases du chemin ------------------------ */
    void link(cell board[LIGNES][COLONNES], coordinates entryPoint)
    {
        int i = 0, j = 0;
        int end = 0;

        i = entryPoint.y;
        j = entryPoint.x;
        while(end == 0)
        {
            board[i][j].type = -1; // Ne pas revenir en arrière
            // Tests sur les côtés de la case
            if(i > 0 && board[i-1][j].type == 1) // En haut
            {
                board[i][j].next = &board[i-1][j];
                i = i-1;
            }
            else if(i < LIGNES-1 && board[i+1][j].type == 1) // En bas
            {
                board[i][j].next = &board[i+1][j];
                i = i+1;
            }
            else if(j < COLONNES-1 && board[i][j+1].type == 1) // A droite
            {
                board[i][j].next = &board[i][j+1];
                j = j+1;
            }
            else if(j > 0 && board[i][j-1].type == 1) // A gauche
            {
                board[i][j].next = &board[i][j-1];
                j = j-1;
            }
            else
            {
                board[i][j].next = NULL;
                end = 1;
            }
        }
        clearBoard(board, -1, 1);
    }

    /* ---------------- Génération aléatoire d'obstacles sur la carte --------------- */
    void setBlock(cell board[LIGNES][COLONNES], int level)
    {
        int i = 0;
        int blocks = 0; // Nombre de blocks placés au hasard sur le plateau
        int x = 0, y = 0;
        srand(time(NULL));

        // Difficulté des niveaux
        // Logique : plus on ajoute d'obstacles, plus il y aura de tournants, plus les défenses pourront attaquer
        // Idée : créer des séparations verticales pour augmenter/réduire les variations du chemin
        // 20 blocks par ligne
        if(level == 1) // Facile
        {
            blocks = 50;
            // 3 lignes verticales
            for(i=0;i<(LIGNES-(LIGNES/3));i++) // 1ère
            {
                board[i][COLONNES/4].type = -1;
                blocks--;
            }
            for(i=LIGNES-1;i>(LIGNES/3)-1;i--) // 2ème
            {
                board[i][(COLONNES/4)*2].type = -1;
                blocks--;
            }
            for(i=0;i<(LIGNES-(LIGNES/3));i++) // 3ème
            {
                board[i][(COLONNES/4)*3].type = -1;
                blocks--;
            }
            // 240 blocks restants
        }
        else if(level == 2) // Moyen
        {
            blocks = 40;
            // 2 lignes verticales
            for(i=0;i<(LIGNES-(LIGNES/3));i++) // 1ère
            {
                board[i][COLONNES/3].type = -1;
                blocks--;
            }
            for(i=LIGNES-1;i>(LIGNES/3)-1;i--) // 2ème
            {
                board[i][(COLONNES/3)*2].type = -1;
                blocks--;
            }
            // 160 blocks restants
        }
        else if(level == 3) // Difficile
        {
            blocks = 30;
            // 1 ligne verticale
            for(i=0;i<(LIGNES-(LIGNES/3));i++) // 1ère
            {
                board[i][COLONNES/2].type = -1;
                blocks--;
            }
            // 80 blocks restants
        }
        else if(level == 4) // Extrême
        {
            blocks = 20;
        }

        // Placement aléatoire du reste des blocks
        // Plus de variations dans le chemin : A eviter
        for(i=0;i<blocks;i++)
        {
            x = rand() % COLONNES;
            y = rand() % LIGNES;

            if(board[y][x].type == -1 || board[y][x].type == 1) // Si déjà obstacle ou point d'entrée/sortie => pas de nouvel obstacle
                i--;
            else
                board[y][x].type = -1;
        }
    }

    /* ---------------------------- Nettoyage du plateau ---------------------------- */
    void clearBoard(cell board[LIGNES][COLONNES], int numberReplacement, int replacedBy)
    {
        int i = 0, j = 0;

        for(i=0;i<LIGNES;i++)
        {
            for(j=0;j<COLONNES;j++)
            {
                if(board[i][j].type == numberReplacement)
                    board[i][j].type = replacedBy;
            }
        }
    }

/* ---------------------------------------------------------------------------------- */
/* ------------------------------------ DEFENSES ------------------------------------ */
/* ---------------------------------------------------------------------------------- */

    /* ------------------------ Initialisation d'une défense ------------------------ */
    void initDefense(cell board[LIGNES][COLONNES], int x, int y, int type)
    {
        // Initialisation d'une défense
        if(type == 1 || type == 2 || type == 3) // Défense de niveau 1 => allouer de la mémoire
        {
            board[y][x].type = 2; // 0 = vide / 1 = chemin / 2 = defense / 3 = ennemi
            board[y][x].actor = malloc(sizeof(defense));
            ((defense *)board[y][x].actor)->lastAttack = clock(); // Dernière attaque de la défense (initialisation à l'heure actuelle)
            ((defense *)board[y][x].actor)->shot.x = 30;
            ((defense *)board[y][x].actor)->shot.y = 30;
            ((defense *)board[y][x].actor)->shotTime = clock();
            ((defense *)board[y][x].actor)->attack = 0;
        }

        // Test au cas où
        if(board[y][x].type == 2)
        {
            // Définition des caractéristiques des défenses
            if(type == 1) // Tour d'archers lvl 1
            {
                ((defense *)board[y][x].actor)->type = 11;
                ((defense *)board[y][x].actor)->damage = 35;
                ((defense *)board[y][x].actor)->range = 1; // Portée : 1 case
                ((defense *)board[y][x].actor)->rate = 1.5; // Ratio : 1 tir chaque x secondes
                ((defense *)board[y][x].actor)->price = 100;
            }
            else if(type == 12) // Tour d'archers lvl 2
            {
                ((defense *)board[y][x].actor)->damage = 70;
                ((defense *)board[y][x].actor)->range = 1; // Portée : 1 case
                ((defense *)board[y][x].actor)->rate = 1.5; // Ratio : 1 tir chaque x secondes
                ((defense *)board[y][x].actor)->price = 150; // Total payé pour avoir une tour lvl 2
            }
            else if(type == 13) // Tour d'archers lvl 3
            {
                ((defense *)board[y][x].actor)->damage = 140;
                ((defense *)board[y][x].actor)->range = 1; // Portée : 1 case
                ((defense *)board[y][x].actor)->rate = 1.5; // Ratio : 1 tir chaque x secondes
                ((defense *)board[y][x].actor)->price = 200; // Total payé pour avoir une tour lvl 3
            }
            else if(type == 2) // Mortier lvl 1
            {
                ((defense *)board[y][x].actor)->type = 21;
                ((defense *)board[y][x].actor)->damage = 50;
                ((defense *)board[y][x].actor)->range = 2; // Portée : 1 case
                ((defense *)board[y][x].actor)->rate = 2.0; // Ratio : 1 tir chaque x secondes
                ((defense *)board[y][x].actor)->price = 150;
            }
            else if(type == 22) // Mortier lvl 2
            {
                ((defense *)board[y][x].actor)->damage = 100;
                ((defense *)board[y][x].actor)->range = 2; // Portée : 1 case
                ((defense *)board[y][x].actor)->rate = 2.0; // Ratio : 1 tir chaque x secondes
                ((defense *)board[y][x].actor)->price = 200;
            }
            else if(type == 23) // Mortier lvl 1
            {
                ((defense *)board[y][x].actor)->damage = 150;
                ((defense *)board[y][x].actor)->range = 2; // Portée : 1 case
                ((defense *)board[y][x].actor)->rate = 2.0; // Ratio : 1 tir chaque x secondes
                ((defense *)board[y][x].actor)->price = 250;
            }
            else if(type == 3) // Tour de l'enfer lvl 1
            {
                ((defense *)board[y][x].actor)->type = 31;
                ((defense *)board[y][x].actor)->damage = 75;
                ((defense *)board[y][x].actor)->range = 4; // Portée : 1 case
                ((defense *)board[y][x].actor)->rate = 2.5; // Ratio : 1 tir chaque x secondes
                ((defense *)board[y][x].actor)->price = 200;
            }
            else if(type == 32) // Tour de l'enfer lvl 2
            {
                ((defense *)board[y][x].actor)->damage = 150;
                ((defense *)board[y][x].actor)->range = 4; // Portée : 1 case
                ((defense *)board[y][x].actor)->rate = 2.5; // Ratio : 1 tir chaque x secondes
                ((defense *)board[y][x].actor)->price = 350;
            }
            else if(type == 33) // Tour de l'enfer lvl 3
            {
                ((defense *)board[y][x].actor)->damage = 300;
                ((defense *)board[y][x].actor)->range = 4; // Portée : 1 case
                ((defense *)board[y][x].actor)->rate = 2.5; // Ratio : 1 tir chaque x secondes
                ((defense *)board[y][x].actor)->price = 500;
            }
        }

    }

    /* -------------- Distance parcourue par un ennemi depuis le départ ------------- */
    int distanceEnemy(cell board[LIGNES][COLONNES], coordinates entryPoint, int x, int y)
    {
        cell *l = NULL;
        int cpt = 0;

        l = &board[entryPoint.y][entryPoint.x];
        // Utilisation de la liste chainée
        while(l != &board[y][x])
        {
            cpt++;
            l = l->next;
        }
        return cpt+1;
    }

    /* ------------------------ Arrondi supérieur d'une valeur ---------------------- */
    int arrondi(float nombre)
    {
        return nombre + 0.5;
    }

    /* --------------- Détermine la dernière case visée par une défense ------------- */
    coordinates lastCell(cell board[LIGNES][COLONNES], int x, int y, coordinates entryPoint)
    {
        detection *tab = NULL;
        int i = 0, j = 0, m = 0;
        int range = 0;
        int cpt = 0;
        int insertion = 0;
        coordinates lastCellRange;
        int max = 0;

        lastCellRange.x = 0;
        lastCellRange.y = 0;
        if(board[y][x].type == 2)
        {
            range = ((defense *)board[y][x].actor)->range;

            for(i=y-range;i<=y+range;i++)
            {
                for(j=x-range;j<=x+range;j++)
                {
                    if(board[i][j].type == 1 || board[i][j].type == 3)
                    {
                        if(cpt == 0)
                        {
                            cpt++;
                            tab = (detection *)malloc(cpt * sizeof(detection));
                            tab[cpt-1].x = j;
                            tab[cpt-1].y = i;
                            tab[cpt-1].nbCells = distanceEnemy(board, entryPoint, j, i);
                        }
                        else
                        {
                            // Regarder si la case n'est pas déjà présente dans le tableau
                            for(m=0;m<cpt;m++)
                            {
                                if(tab[m].x == j && tab[m].y == i)
                                    insertion = 1;
                            }
                            // Si la case n'est pas dans le tableau, on l'ajoute
                            if(insertion == 0)
                            {
                                cpt++;
                                tab = (detection *)realloc(tab, cpt * sizeof(detection)); // Realloc
                                tab[cpt-1].x = j;
                                tab[cpt-1].y = i;
                                tab[cpt-1].nbCells = distanceEnemy(board, entryPoint, j, i);
                            }
                        }
                    }
                }
            }

            // Trouver la case la plus loin (maximum)
            if(cpt > 0)
            {
                // Comparaison des ennemis => sélection de l'ennemi le plus loin sur le chemin
                max = tab[0].nbCells;
                for(i=0;i<cpt;i++)
                {
                    if(max < tab[i].nbCells)
                        max = tab[i].nbCells;
                }
            }

            for(i=0;i<cpt;i++)
            {
                if(max == tab[i].nbCells)
                {
                    lastCellRange.x = tab[i].x;
                    lastCellRange.y = tab[i].y;
                }
            }

            for(i=0;i<cpt;i++)
                free(&tab[i]);
            free(tab);
        }

        return lastCellRange;
    }

    /* ---------------------------- Détection des ennemis --------------------------- */
    void detectEnemy(cell board[LIGNES][COLONNES], coordinates entryPoint, int x, int y, int *nbEnemyMain, clock_t t5, clock_t t8, int *gold)
    {
        // Trouver l'ennemi le plus loin sur le chemin dans le champ de portée de la tour
        int k = 0, l = 0;
        int m = 0, i = 0;
        int range = 0; // Portée
        detection *tab = NULL; // Structure X / Y / nbCells (Nb Cases Parcourues)
        int nbEnemy = 0;
        int insertion = 0;
        int max = 0;
        float differenceTime = 0.0;
        int xEnemy = 0, yEnemy = 0;
        int pixelXEnemy = 0, pixelYEnemy = 0;
        int pixelXProjectile= 0, pixelYProjectile = 0;
        float coefficientDirecteur = 0.0;
        coordinates endOfRange;
        float distance = 0.0, time = 0.0;
        int pixelXLastCell = 0, pixelYLastCell = 0;
        int pixelXDefense = 0, pixelYDefense = 0;

        endOfRange.x = 0;
        endOfRange.y = 0;

        if(board[y][x].type == 2)
        {
            range = ((defense *)board[y][x].actor)->range;

            // Détection des cases à la bonne portée
            // On parcourt le carré contenu dans la portée
            for(k=y-range;k<=y+range;k++)
            {
                for(l=x-range;l<=x+range;l++)
                {
                    // Si la case est dans le tableau, on peut check
                    if(k >= 0 && k < LIGNES-1 && l >= 0 && l > 0 && l < COLONNES-1 && board[k][l].type == 3 && (l != entryPoint.x || k != entryPoint.y)) // On ne tire pas sur un ennemi qui vient d'être créé
                    {
                        // On retient dans un tableau les coordonnées et le nombre de cases déjà parcourues
                        // Il faut maintenant trouver l'ennemi le plus loin sur le chemin
                        // => compter le nombre de cases chemins avant => comparaison
                        if(nbEnemy == 0)
                        {
                            nbEnemy++;
                            tab = (detection *)malloc(nbEnemy * sizeof(detection));
                            tab[nbEnemy-1].x = l;
                            tab[nbEnemy-1].y = k;
                            tab[nbEnemy-1].nbCells = distanceEnemy(board, entryPoint, l, k);
                        }
                        else
                        {
                            // Regarder si l'ennemi n'est pas déjà présent dans le tableau
                            for(m=0;m<nbEnemy;m++)
                            {
                                if(tab[m].x == l && tab[m].y == k)
                                    insertion = 1;
                            }

                            // Si l'ennemi n'est pas dans le tableau
                            if(insertion == 0)
                            {
                                nbEnemy++;
                                tab = (detection *)realloc(tab, nbEnemy * sizeof(detection)); // Realloc
                                tab[nbEnemy-1].x = l;
                                tab[nbEnemy-1].y = k;
                                tab[nbEnemy-1].nbCells = distanceEnemy(board, entryPoint, l, k);
                            }
                        }
                    }
                }
            }

            if(nbEnemy > 0)
            {
                // Comparaison des ennemis => sélection de l'ennemi le plus loin sur le chemin
                max = tab[0].nbCells;
                for(m=0;m<nbEnemy;m++)
                {
                    if(max < tab[m].nbCells)
                        max = tab[m].nbCells;
                }

                for(m=0;m<nbEnemy;m++)
                {
                    if(max == tab[m].nbCells)
                    {
                        endOfRange = lastCell(board, x, y, entryPoint);
                        // Calculer la distance entre la défense et la dernière case possiblement touchable
                        // Coordonnées en pixel de la dernière case
                        pixelXLastCell = (endOfRange.x * TAILLE_CASE) + 30;
                        pixelYLastCell = (endOfRange.y * TAILLE_CASE) + 30;
                        // Coordonnées en pixel de la défense
                        pixelXDefense = (x * TAILLE_CASE) + 30;
                        pixelYDefense = (y * TAILLE_CASE) + 30;

                        distance = sqrt(pow(pixelXLastCell-pixelXDefense, 2) + pow(pixelYLastCell-pixelYDefense, 2)); // Formule de maths
                        time = distance / (1/0.005); // T = d/v

                        if(((tab[m].x == endOfRange.x && tab[m].y == endOfRange.y && ((enemy *)board[tab[m].y][tab[m].x].actor)->timeBeforeTurn > time && board[tab[m].y][tab[m].x].type == 3) || (tab[m].x != endOfRange.x || tab[m].y != endOfRange.y)) && board[y][x].type == 2)
                        {
                            differenceTime = ((float)t5) - ((float)((defense *)board[y][x].actor)->lastAttack);
                            differenceTime =(differenceTime / 1000000.0F ) * 1000; // Pour chaque tour, regarder son temps de tir ...
                            if(differenceTime >= ((defense *)board[y][x].actor)->rate) // Création d'un tir
                            {
                                ((defense *)board[y][x].actor)->shot.x = 30;
                                ((defense *)board[y][x].actor)->shot.y = 30;
                                ((defense *)board[y][x].actor)->lastAttack = t5;
                                ((defense *)board[y][x].actor)->attack = 1;
                            }

                            // Déplacement du projectile
                            differenceTime = ((float)t8) - ((float)((defense *)board[y][x].actor)->shotTime);
                            differenceTime = (differenceTime / 1000000.0F ) * 1000;
                            if(differenceTime >= 0.005 && ((defense *)board[y][x].actor)->attack == 1) // vitesse de déplacement du projectile
                            {
                                // Coordonnées en pixel du projectile
                                pixelXProjectile = (x * TAILLE_CASE) + ((defense *)board[y][x].actor)->shot.x;
                                pixelYProjectile = (y * TAILLE_CASE) + ((defense *)board[y][x].actor)->shot.y;

                                // Coordonnées en pixel de l'ennemi
                                pixelXEnemy = (tab[m].x * TAILLE_CASE) + ((enemy *)board[tab[m].y][tab[m].x].actor)->relativePosition.x;
                                pixelYEnemy = (tab[m].y * TAILLE_CASE) + ((enemy *)board[tab[m].y][tab[m].x].actor)->relativePosition.y;

                                // Calcul des coordonnées en pixel de l'ennemi par rapport au projectile
                                xEnemy = pixelXEnemy - pixelXProjectile;
                                yEnemy = pixelYProjectile - pixelYEnemy;

                                // Calcul du coefficient directeur
                                if(xEnemy != 0)
                                    coefficientDirecteur = (float)yEnemy / (float)xEnemy;
                                // Si xEnemy = 0, le coefficient directeur est infini

                                // Calcul du x projectile
                                if(xEnemy > 0)
                                    pixelXProjectile = 1;
                                else if(xEnemy < 0)
                                    pixelXProjectile = -1;

                                // Calcul du y projectile
                                if(xEnemy != 0)
                                    pixelYProjectile = arrondi(coefficientDirecteur * pixelXProjectile);
                                else if(yEnemy > 0)
                                    pixelYProjectile -= 1;
                                else if(yEnemy < 0)
                                    pixelYProjectile += 1;

                                ((defense *)board[y][x].actor)->shot.x = ((defense *)board[y][x].actor)->shot.x + pixelXProjectile;
                                ((defense *)board[y][x].actor)->shot.y = ((defense *)board[y][x].actor)->shot.y - pixelYProjectile;
                                ((defense *)board[y][x].actor)->shotTime = t8;
                            }

                            // Coordonnées en pixel du projectile
                            pixelXProjectile = (x * TAILLE_CASE) + ((defense *)board[y][x].actor)->shot.x;
                            pixelYProjectile = (y * TAILLE_CASE) + ((defense *)board[y][x].actor)->shot.y;

                            // Coordonnées en pixel de l'ennemi
                            pixelXEnemy = (tab[m].x * TAILLE_CASE) + ((enemy *)board[tab[m].y][tab[m].x].actor)->relativePosition.x;
                            pixelYEnemy = (tab[m].y * TAILLE_CASE) + ((enemy *)board[tab[m].y][tab[m].x].actor)->relativePosition.y;

                            // Si on touche l'ennemi, on enlève de la vie
                            if(((pixelXProjectile >= (pixelXEnemy - 10)) && (pixelXProjectile <= (pixelXEnemy + 10))) && ((pixelYProjectile >= (pixelYEnemy - 15)) && (pixelYProjectile <= (pixelYEnemy + 15))))
                            {
                                ((enemy *)board[tab[m].y][tab[m].x].actor)->health -= ((defense *)board[y][x].actor)->damage; // L'ennemi perd de la vie
                                ((defense *)board[y][x].actor)->lastAttack = t5;
                                ((defense *)board[y][x].actor)->shot.x = 30;
                                ((defense *)board[y][x].actor)->shot.y = 30;
                                ((defense *)board[y][x].actor)->attack = 0;

                                if(((enemy *)board[tab[m].y][tab[m].x].actor)->health <= 0) // Ennemi tué
                                {
                                    *nbEnemyMain = *nbEnemyMain - 1; // Augmentation du nombre de morts
                                    *gold = *gold + 40;// Augmentation de l'argent (gold)
                                    board[tab[m].y][tab[m].x].type = 1;
                                    free(board[tab[m].y][tab[m].x].actor);
                                    board[tab[m].y][tab[m].x].actor = NULL;
                                }
                            }
                        }
                        else if(tab[m].x == endOfRange.x && tab[m].y == endOfRange.y && ((enemy *)board[tab[m].y][tab[m].x].actor)->timeBeforeTurn < 0.33333333 && board[y][x].type == 2)
                        {
                            ((defense *)board[y][x].actor)->shot.x = 30;
                            ((defense *)board[y][x].actor)->shot.y = 30;
                        }
                    }
                }
            }

            for(i=0;i<nbEnemy;i++)
                free(&tab[i]);
            free(tab);
        }
    }

/* ---------------------------------------------------------------------------------- */
/* ------------------------------------ ENNEMIS ------------------------------------- */
/* ---------------------------------------------------------------------------------- */

    /* ----------------------------- Attendre x secondes ---------------------------- */
    void waitTime(float temps)
    {
        clock_t arrivee = clock()+(temps*CLOCKS_PER_SEC); // On calcule le moment où l'attente devra s'arrêter

        while(clock()<arrivee);
    }

    /* --------------------------- Déplacement d'un ennemi -------------------------- */
    void moveEnemy(cell board[LIGNES][COLONNES], coordinates pointEnemy)
    {
        cell *curr = NULL;

        curr = &board[pointEnemy.y][pointEnemy.x];
        curr->next = board[pointEnemy.y][pointEnemy.x].next;

        (curr->next)->actor = curr->actor;
        curr->actor = NULL;

        (curr->next)->type = curr->type;
        curr->type = 1;
    }

    /* ----------------------- Déplacement de tous les ennemis ---------------------- */
    void coordinatesEnemy(cell board[LIGNES][COLONNES], coordinates entryPoint, coordinates exitPoint, int *nbEnemy, int *life)
    {
        coordinates pointEnemy;
        coordinates lastPoint;
        int i = 0;
        int x = 0;
        int y = 0;
        int cpt = 0;

        for(i=(*nbEnemy);i>0;i--)
        {
            cpt = 0;
            x = entryPoint.x;
            y = entryPoint.y;

            lastPoint.x = -1;
            lastPoint.y = -1;

            // Parcourir le chemin jusqu'à trouver le i-ème ennemi
            while(cpt != i)
            {
                // Si on trouve un 3, on le comptabilise
                if(board[y][x].type == 3)
                    cpt++;

                if(cpt != i)
                {
                    // On  déplace ensuite x/y
                    if(y > 0 && lastPoint.y != y-1 && (board[y-1][x].type == 1 || board[y-1][x].type == 3)) // Haut
                    {
                        lastPoint.x = x;
                        lastPoint.y = y;
                        y = y-1;
                    }
                    else if(y < LIGNES-1 && lastPoint.y != y+1 && (board[y+1][x].type == 1 || board[y+1][x].type == 3)) // Bas
                    {
                        lastPoint.x = x;
                        lastPoint.y = y;
                        y = y+1;
                    }
                    else if(x > 0 && lastPoint.x != x-1 && (board[y][x-1].type == 1 || board[y][x-1].type == 3)) // Gauche
                    {
                        lastPoint.x = x;
                        lastPoint.y = y;
                        x = x-1;
                    }
                    else if(x < COLONNES-1 && lastPoint.x != x+1 && (board[y][x+1].type == 1 || board[y][x+1].type == 3)) // Droite
                    {
                        lastPoint.x = x;
                        lastPoint.y = y;
                        x = x+1;
                    }
                    else
                    {
                        // Pas d'ennemi à déplacer
                        cpt = i;
                    }
                }
            }
            pointEnemy.x = x;
            pointEnemy.y = y;

            if(board[y][x].type == 3)
            {
                if(x == entryPoint.x && y == entryPoint.y)
                {
                    if(y > 0 && (board[y-1][x].type == 1 || board[y-1][x].type == 3))
                    {
                        if(((enemy *)board[y][x].actor)->relativePosition.y == 0)
                        {
                            if(y > 0 && board[y-1][x].type == 1)
                            {
                                ((enemy *)board[y][x].actor)->relativePosition.y = 60;
                                ((enemy *)board[y][x].actor)->timeBeforeTurn = (float)((enemy *)board[y][x].actor)->relativePosition.y / 60.0;
                                moveEnemy(board, pointEnemy);
                            }
                        }
                        else
                        {
                            ((enemy *)board[y][x].actor)->relativePosition.y = ((enemy *)board[y][x].actor)->relativePosition.y - 1;
                            ((enemy *)board[y][x].actor)->timeBeforeTurn = (float)((enemy *)board[y][x].actor)->relativePosition.y / 60.0;
                        }
                    }
                    else if(y < LIGNES-1 && (board[y+1][x].type == 1 || board[y+1][x].type == 3))
                    {
                        if(((enemy *)board[y][x].actor)->relativePosition.y == 60)
                        {
                            if(y < LIGNES-1 && board[y+1][x].type == 1)
                            {
                                ((enemy *)board[y][x].actor)->relativePosition.y = 0;
                                ((enemy *)board[y][x].actor)->timeBeforeTurn = (60 - (float)((enemy *)board[y][x].actor)->relativePosition.y) / 60.0;
                                moveEnemy(board, pointEnemy);
                            }
                        }
                        else
                        {
                            ((enemy *)board[y][x].actor)->relativePosition.y = ((enemy *)board[y][x].actor)->relativePosition.y + 1;
                            ((enemy *)board[y][x].actor)->timeBeforeTurn = (60 - (float)((enemy *)board[y][x].actor)->relativePosition.y) / 60.0;
                        }
                    }
                    else if(x > 0 && (board[y][x-1].type == 1 || board[y][x-1].type == 3))
                    {
                        if(((enemy *)board[y][x].actor)->relativePosition.x == 0)
                        {
                            if(x > 0 && board[y][x-1].type == 1)
                            {
                                ((enemy *)board[y][x].actor)->relativePosition.x = 60;
                                ((enemy *)board[y][x].actor)->timeBeforeTurn = (float)((enemy *)board[y][x].actor)->relativePosition.x / 60.0;
                                moveEnemy(board, pointEnemy);
                            }
                        }
                        else
                        {
                            ((enemy *)board[y][x].actor)->relativePosition.x = ((enemy *)board[y][x].actor)->relativePosition.x - 1;
                            ((enemy *)board[y][x].actor)->timeBeforeTurn = (float)((enemy *)board[y][x].actor)->relativePosition.x / 60.0;
                        }
                    }
                    else if(x < COLONNES-1 && (board[y][x+1].type == 1 || board[y][x+1].type == 3))
                    {
                        if(((enemy *)board[y][x].actor)->relativePosition.x == 60)
                        {
                            if(x < COLONNES-1 && board[y][x+1].type == 1)
                            {
                                ((enemy *)board[y][x].actor)->relativePosition.x = 0;
                                ((enemy *)board[y][x].actor)->timeBeforeTurn = (60 - (float)((enemy *)board[y][x].actor)->relativePosition.x) / 60.0;
                                moveEnemy(board, pointEnemy);
                            }
                        }
                        else
                        {
                            ((enemy *)board[y][x].actor)->relativePosition.x = ((enemy *)board[y][x].actor)->relativePosition.x + 1;
                            ((enemy *)board[y][x].actor)->timeBeforeTurn = (60 - (float)((enemy *)board[y][x].actor)->relativePosition.x) / 60.0;
                        }
                    }
                }
                else if(x == exitPoint.x && y == exitPoint.y)
                {
                    if(lastPoint.x == x-1)
                    {
                        if(((enemy *)board[y][x].actor)->relativePosition.x == 60)
                        {
                            *nbEnemy = *nbEnemy - 1;
                            board[exitPoint.y][exitPoint.x].type = 1;
                            free(board[exitPoint.y][exitPoint.x].actor);
                            board[exitPoint.y][exitPoint.x].actor = NULL;
                            *life = *life - 1;
                        }
                        else
                        {
                            ((enemy *)board[y][x].actor)->relativePosition.x = ((enemy *)board[y][x].actor)->relativePosition.x + 1;
                            ((enemy *)board[y][x].actor)->timeBeforeTurn = (60 - (float)((enemy *)board[y][x].actor)->relativePosition.x) / 60.0;
                        }
                    }
                    else if(lastPoint.x == x+1)
                    {
                        if(((enemy *)board[y][x].actor)->relativePosition.x == 0)
                        {
                            *nbEnemy = *nbEnemy - 1;
                            board[exitPoint.y][exitPoint.x].type = 1;
                            free(board[exitPoint.y][exitPoint.x].actor);
                            board[exitPoint.y][exitPoint.x].actor = NULL;
                            *life = *life - 1;
                        }
                        else
                        {
                            ((enemy *)board[y][x].actor)->relativePosition.x = ((enemy *)board[y][x].actor)->relativePosition.x - 1;
                            ((enemy *)board[y][x].actor)->timeBeforeTurn = (float)((enemy *)board[y][x].actor)->relativePosition.x / 60.0;
                        }
                    }
                    else if(lastPoint.y == y-1)
                    {
                        if(((enemy *)board[y][x].actor)->relativePosition.y == 60)
                        {
                            *nbEnemy = *nbEnemy - 1;
                            board[exitPoint.y][exitPoint.x].type = 1;
                            free(board[exitPoint.y][exitPoint.x].actor);
                            board[exitPoint.y][exitPoint.x].actor = NULL;
                            *life = *life - 1;
                        }
                        else
                        {
                            ((enemy *)board[y][x].actor)->relativePosition.y = ((enemy *)board[y][x].actor)->relativePosition.y + 1;
                            ((enemy *)board[y][x].actor)->timeBeforeTurn = (60 - (float)((enemy *)board[y][x].actor)->relativePosition.y) / 60.0;
                        }
                    }
                    else if(lastPoint.y == y+1)
                    {
                        if(((enemy *)board[y][x].actor)->relativePosition.y == 0)
                        {
                            *nbEnemy = *nbEnemy - 1;
                            board[exitPoint.y][exitPoint.x].type = 1;
                            free(board[exitPoint.y][exitPoint.x].actor);
                            board[exitPoint.y][exitPoint.x].actor = NULL;
                            *life = *life - 1;
                        }
                        else
                        {
                            ((enemy *)board[y][x].actor)->relativePosition.y = ((enemy *)board[y][x].actor)->relativePosition.y - 1;
                            ((enemy *)board[y][x].actor)->timeBeforeTurn = (float)((enemy *)board[y][x].actor)->relativePosition.y / 60.0;
                        }
                    }
                }
                else if(y > 0 && lastPoint.y != y-1 && (board[y-1][x].type == 1 || board[y-1][x].type == 3)) // Haut
                {
                    // 3 cas
                    if(lastPoint.x == x+1)
                    {
                        if(((enemy *)board[y][x].actor)->relativePosition.x > 30)
                        {
                            ((enemy *)board[y][x].actor)->relativePosition.x = ((enemy *)board[y][x].actor)->relativePosition.x - 1;
                            ((enemy *)board[y][x].actor)->timeBeforeTurn = 1.0;
                        }
                        else if(((enemy *)board[y][x].actor)->relativePosition.x == 30 && ((enemy *)board[y][x].actor)->relativePosition.y > 0)
                        {
                            ((enemy *)board[y][x].actor)->relativePosition.y = ((enemy *)board[y][x].actor)->relativePosition.y - 1;
                            ((enemy *)board[y][x].actor)->timeBeforeTurn = (float)((enemy *)board[y][x].actor)->relativePosition.y / 60.0;
                        }
                        else if(((enemy *)board[y][x].actor)->relativePosition.y == 0)
                        {
                            if(y > 0 && board[y-1][x].type == 1)
                            {
                                ((enemy *)board[y][x].actor)->relativePosition.y = 60;
                                ((enemy *)board[y][x].actor)->timeBeforeTurn = (float)((enemy *)board[y][x].actor)->relativePosition.y / 60.0;
                                moveEnemy(board, pointEnemy);
                            }
                        }
                    }
                    else if(lastPoint.y == y+1)
                    {
                        if(((enemy *)board[y][x].actor)->relativePosition.y > 0)
                        {
                            ((enemy *)board[y][x].actor)->relativePosition.y = ((enemy *)board[y][x].actor)->relativePosition.y - 1;
                            ((enemy *)board[y][x].actor)->timeBeforeTurn = (float)((enemy *)board[y][x].actor)->relativePosition.y / 60.0;
                        }
                        else if(((enemy *)board[y][x].actor)->relativePosition.y == 0)
                        {
                            if(y > 0 && board[y-1][x].type == 1)
                            {
                                ((enemy *)board[y][x].actor)->relativePosition.y = 60;
                                ((enemy *)board[y][x].actor)->timeBeforeTurn = (float)((enemy *)board[y][x].actor)->relativePosition.y / 60.0;
                                moveEnemy(board, pointEnemy);
                            }
                        }
                    }
                    else if(lastPoint.x == x-1)
                    {
                        if(((enemy *)board[y][x].actor)->relativePosition.x < 30)
                        {
                            ((enemy *)board[y][x].actor)->relativePosition.x = ((enemy *)board[y][x].actor)->relativePosition.x + 1;
                            ((enemy *)board[y][x].actor)->timeBeforeTurn = 1.0;
                        }
                        else if(((enemy *)board[y][x].actor)->relativePosition.x == 30 && ((enemy *)board[y][x].actor)->relativePosition.y > 0)
                        {
                            ((enemy *)board[y][x].actor)->relativePosition.y = ((enemy *)board[y][x].actor)->relativePosition.y - 1;
                            ((enemy *)board[y][x].actor)->timeBeforeTurn = (float)((enemy *)board[y][x].actor)->relativePosition.y / 60.0;
                        }
                        else if(((enemy *)board[y][x].actor)->relativePosition.y == 0)
                        {
                            if(y > 0 && board[y-1][x].type == 1)
                            {
                                ((enemy *)board[y][x].actor)->relativePosition.y = 60;
                                ((enemy *)board[y][x].actor)->timeBeforeTurn = (float)((enemy *)board[y][x].actor)->relativePosition.y / 60.0;
                                moveEnemy(board, pointEnemy);
                            }
                        }
                    }
                }
                else if(y < LIGNES-1 && lastPoint.y != y+1 && (board[y+1][x].type == 1 || board[y+1][x].type == 3)) // Bas
                {
                    // 3 cas
                    if(lastPoint.x == x+1)
                    {
                        if(((enemy *)board[y][x].actor)->relativePosition.x > 30)
                        {
                            ((enemy *)board[y][x].actor)->relativePosition.x = ((enemy *)board[y][x].actor)->relativePosition.x - 1;
                            ((enemy *)board[y][x].actor)->timeBeforeTurn = 1.0;
                        }
                        else if(((enemy *)board[y][x].actor)->relativePosition.x == 30 && ((enemy *)board[y][x].actor)->relativePosition.y < 60)
                        {
                            ((enemy *)board[y][x].actor)->relativePosition.y = ((enemy *)board[y][x].actor)->relativePosition.y + 1;
                            ((enemy *)board[y][x].actor)->timeBeforeTurn = (60 - (float)((enemy *)board[y][x].actor)->relativePosition.y) / 60.0;
                        }
                        else if(((enemy *)board[y][x].actor)->relativePosition.y == 60)
                        {
                            if(y < LIGNES-1 && board[y+1][x].type == 1)
                            {
                                ((enemy *)board[y][x].actor)->relativePosition.y = 0;
                                ((enemy *)board[y][x].actor)->timeBeforeTurn = (60 - (float)((enemy *)board[y][x].actor)->relativePosition.y) / 60.0;
                                moveEnemy(board, pointEnemy);
                            }
                        }
                    }
                    else if(lastPoint.y == y-1)
                    {
                        if(((enemy *)board[y][x].actor)->relativePosition.y < 60)
                        {
                            ((enemy *)board[y][x].actor)->relativePosition.y = ((enemy *)board[y][x].actor)->relativePosition.y + 1;
                            ((enemy *)board[y][x].actor)->timeBeforeTurn = (60 - (float)((enemy *)board[y][x].actor)->relativePosition.y) / 60.0;
                        }
                        else if(((enemy *)board[y][x].actor)->relativePosition.y == 60)
                        {
                            if(y < LIGNES-1 && board[y+1][x].type == 1)
                            {
                                ((enemy *)board[y][x].actor)->relativePosition.y = 0;
                                ((enemy *)board[y][x].actor)->timeBeforeTurn = (60 - (float)((enemy *)board[y][x].actor)->relativePosition.y) / 60.0;
                                moveEnemy(board, pointEnemy);
                            }
                        }
                    }
                    else if(lastPoint.x == x-1)
                    {
                        if(((enemy *)board[y][x].actor)->relativePosition.x < 30)
                        {
                            ((enemy *)board[y][x].actor)->relativePosition.x = ((enemy *)board[y][x].actor)->relativePosition.x + 1;
                            ((enemy *)board[y][x].actor)->timeBeforeTurn = 1;
                        }
                        else if(((enemy *)board[y][x].actor)->relativePosition.x == 30 && ((enemy *)board[y][x].actor)->relativePosition.y < 60)
                        {
                            ((enemy *)board[y][x].actor)->relativePosition.y = ((enemy *)board[y][x].actor)->relativePosition.y + 1;
                            ((enemy *)board[y][x].actor)->timeBeforeTurn = (60 - (float)((enemy *)board[y][x].actor)->relativePosition.y) / 60.0;
                        }
                        else if(((enemy *)board[y][x].actor)->relativePosition.y == 60)
                        {
                            if(y < LIGNES-1 && board[y+1][x].type == 1)
                            {
                                ((enemy *)board[y][x].actor)->relativePosition.y = 0;
                                ((enemy *)board[y][x].actor)->timeBeforeTurn = (60 - (float)((enemy *)board[y][x].actor)->relativePosition.y) / 60.0;
                                moveEnemy(board, pointEnemy);
                            }
                        }
                    }
                }
                else if(x > 0 && lastPoint.x != x-1 && (board[y][x-1].type == 1 || board[y][x-1].type == 3)) // Gauche
                {
                    // 3 cas
                    if(lastPoint.y == y-1)
                    {
                        if(((enemy *)board[y][x].actor)->relativePosition.y < 30)
                        {
                            ((enemy *)board[y][x].actor)->relativePosition.y = ((enemy *)board[y][x].actor)->relativePosition.y + 1;
                            ((enemy *)board[y][x].actor)->timeBeforeTurn = 1.0;
                        }
                        else if(((enemy *)board[y][x].actor)->relativePosition.y == 30 && ((enemy *)board[y][x].actor)->relativePosition.x > 0)
                        {
                            ((enemy *)board[y][x].actor)->relativePosition.x = ((enemy *)board[y][x].actor)->relativePosition.x - 1;
                            ((enemy *)board[y][x].actor)->timeBeforeTurn = (float)((enemy *)board[y][x].actor)->relativePosition.x / 60.0;
                        }
                        else if(((enemy *)board[y][x].actor)->relativePosition.x == 0)
                        {
                            if(x > 0 && board[y][x-1].type == 1)
                            {
                                ((enemy *)board[y][x].actor)->relativePosition.x = 60;
                                ((enemy *)board[y][x].actor)->timeBeforeTurn = (float)((enemy *)board[y][x].actor)->relativePosition.x / 60.0;
                                moveEnemy(board, pointEnemy);
                            }
                        }
                    }
                    else if(lastPoint.y == y+1)
                    {
                        if(((enemy *)board[y][x].actor)->relativePosition.y > 30)
                        {
                            ((enemy *)board[y][x].actor)->relativePosition.y = ((enemy *)board[y][x].actor)->relativePosition.y - 1;
                            ((enemy *)board[y][x].actor)->timeBeforeTurn = 1.0;
                        }
                        else if(((enemy *)board[y][x].actor)->relativePosition.y == 30 && ((enemy *)board[y][x].actor)->relativePosition.x > 0)
                        {
                            ((enemy *)board[y][x].actor)->relativePosition.x = ((enemy *)board[y][x].actor)->relativePosition.x - 1;
                            ((enemy *)board[y][x].actor)->timeBeforeTurn = (float)((enemy *)board[y][x].actor)->relativePosition.x / 60.0;
                        }
                        else if(((enemy *)board[y][x].actor)->relativePosition.x == 0)
                        {
                            if(x > 0 && board[y][x-1].type == 1)
                            {
                                ((enemy *)board[y][x].actor)->relativePosition.x = 60;
                                ((enemy *)board[y][x].actor)->timeBeforeTurn = (float)((enemy *)board[y][x].actor)->relativePosition.x / 60.0;
                                moveEnemy(board, pointEnemy);
                            }
                        }
                    }
                    else if(lastPoint.x == x+1)
                    {
                        if(((enemy *)board[y][x].actor)->relativePosition.x > 0)
                        {
                            ((enemy *)board[y][x].actor)->relativePosition.x = ((enemy *)board[y][x].actor)->relativePosition.x - 1;
                            ((enemy *)board[y][x].actor)->timeBeforeTurn = (float)((enemy *)board[y][x].actor)->relativePosition.x / 60.0;
                        }
                        else if(((enemy *)board[y][x].actor)->relativePosition.x == 0)
                        {
                            if(x > 0 && board[y][x-1].type == 1)
                            {
                                ((enemy *)board[y][x].actor)->relativePosition.x = 60;
                                ((enemy *)board[y][x].actor)->timeBeforeTurn = (float)((enemy *)board[y][x].actor)->relativePosition.x / 60.0;
                                moveEnemy(board, pointEnemy);
                            }
                        }
                    }
                }
                else if(x < COLONNES-1 && lastPoint.x != x+1 && (board[y][x+1].type == 1 || board[y][x+1].type == 3)) // Droite
                {
                    // 3 cas
                    if(lastPoint.y == y-1)
                    {
                        if(((enemy *)board[y][x].actor)->relativePosition.y < 30)
                        {
                            ((enemy *)board[y][x].actor)->relativePosition.y = ((enemy *)board[y][x].actor)->relativePosition.y + 1;
                            ((enemy *)board[y][x].actor)->timeBeforeTurn = 1.0;
                        }
                        else if(((enemy *)board[y][x].actor)->relativePosition.y == 30 && ((enemy *)board[y][x].actor)->relativePosition.x < 60)
                        {
                            ((enemy *)board[y][x].actor)->relativePosition.x = ((enemy *)board[y][x].actor)->relativePosition.x + 1;
                            ((enemy *)board[y][x].actor)->timeBeforeTurn = (60 - (float)((enemy *)board[y][x].actor)->relativePosition.x) / 60.0;
                        }
                        else if(((enemy *)board[y][x].actor)->relativePosition.x == 60)
                        {
                            if(x < COLONNES-1 && board[y][x+1].type == 1)
                            {
                                ((enemy *)board[y][x].actor)->relativePosition.x = 0;
                                ((enemy *)board[y][x].actor)->timeBeforeTurn = (60 - (float)((enemy *)board[y][x].actor)->relativePosition.x) / 60.0;
                                moveEnemy(board, pointEnemy);
                            }
                        }
                    }
                    else if(lastPoint.y == y+1)
                    {
                        if(((enemy *)board[y][x].actor)->relativePosition.y > 30)
                        {
                            ((enemy *)board[y][x].actor)->relativePosition.y = ((enemy *)board[y][x].actor)->relativePosition.y - 1;
                            ((enemy *)board[y][x].actor)->timeBeforeTurn = 1.0;
                        }
                        else if(((enemy *)board[y][x].actor)->relativePosition.y == 30 && ((enemy *)board[y][x].actor)->relativePosition.x < 60)
                        {
                            ((enemy *)board[y][x].actor)->relativePosition.x = ((enemy *)board[y][x].actor)->relativePosition.x + 1;
                            ((enemy *)board[y][x].actor)->timeBeforeTurn = (60 - (float)((enemy *)board[y][x].actor)->relativePosition.x) / 60.0;
                        }
                        else if(((enemy *)board[y][x].actor)->relativePosition.x == 60)
                        {
                            if(x < COLONNES-1 && board[y][x+1].type == 1)
                            {
                                ((enemy *)board[y][x].actor)->relativePosition.x = 0;
                                ((enemy *)board[y][x].actor)->timeBeforeTurn = (60 - (float)((enemy *)board[y][x].actor)->relativePosition.x) / 60.0;
                                moveEnemy(board, pointEnemy);
                            }
                        }
                    }
                    else if(lastPoint.x == x-1)
                    {
                        if(((enemy *)board[y][x].actor)->relativePosition.x < 60)
                        {
                            ((enemy *)board[y][x].actor)->relativePosition.x = ((enemy *)board[y][x].actor)->relativePosition.x + 1;
                            ((enemy *)board[y][x].actor)->timeBeforeTurn = (60 - (float)((enemy *)board[y][x].actor)->relativePosition.x) / 60.0;
                        }
                        else if(((enemy *)board[y][x].actor)->relativePosition.x == 60)
                        {
                            if(x < COLONNES-1 && board[y][x+1].type == 1)
                            {
                                ((enemy *)board[y][x].actor)->relativePosition.x = 0;
                                ((enemy *)board[y][x].actor)->timeBeforeTurn = (60 - (float)((enemy *)board[y][x].actor)->relativePosition.x) / 60.0;
                                moveEnemy(board, pointEnemy);
                            }
                        }
                    }
                }
            }
        }
    }

    /* ---------------------------------------------------------------------------------- */
    /* ------------------------------------- LEVEL -------------------------------------- */
    /* ---------------------------------------------------------------------------------- */

    /* ---------------- Initialisation des caractéristiques de la partie ---------------- */
    void initLevel(int level, int *nbWave, int *nbEnemyPerWave, float *creationTimeEnemy, float *positionTimeEnemy)
    {
        if(level == 1)
        {
            *nbWave = 15;
            *nbEnemyPerWave = 3;
            *creationTimeEnemy = 3.5;
            *positionTimeEnemy = 1.5;
        }
        else if(level == 2)
        {
            *nbWave = 15;
            *nbEnemyPerWave = 3;
            *creationTimeEnemy = 3.25;
            *positionTimeEnemy = 1.375;
        }
        else if(level == 3)
        {
            *nbWave = 15;
            *nbEnemyPerWave = 3;
            *creationTimeEnemy = 3.0;
            *positionTimeEnemy = 1.25;
        }
        else if(level == 4)
        {
            *nbWave = 15;
            *nbEnemyPerWave = 3;
            *creationTimeEnemy = 2.75;
            *positionTimeEnemy = 1.125;
        }
    }

