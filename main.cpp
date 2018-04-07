#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <SDL.h>

#include "Sources/defines.c"
#include "Sources/functions.c"
#include "Sources/pathfinding.c"

#include "Headers/structure.h"
#include "Headers/functions.h"

int main(int argc, char *argv[])
{
    // Ecriture en console
    freopen("CON", "w", stdout);
    freopen("CON", "r", stdin);
    freopen("CON", "w", stderr);

    // Déclaration de variables
    int choixMenu = 0; // Choix du menu
    int level = 0; // Level de la partie
    int iMouseX = 0; // Coordonnées x de la souris
    int iMouseY = 0; // Coordonnées y de la souris

    // SDL
    int continuer = 1; // Variable de boucle SDL
    SDL_Event event; // Evénement
    SDL_Rect pos_curs; // Coordonnées du curseur

    if(SDL_Init(SDL_INIT_VIDEO) == -1) // Démarrage de la SDL. Si erreur :
    {
        printf("Erreur d'initialisation de la SDL.\n"); // Écriture de l'erreur
        exit(EXIT_FAILURE); // On quitte le programme
    }

    SDL_Surface *screen = SDL_SetVideoMode(1200, 900, 32, SDL_HWSURFACE|SDL_FULLSCREEN|SDL_DOUBLEBUF);
    if(screen == NULL)
    {
        printf("Impossible de charger le mode video.\n");
        exit(EXIT_FAILURE);
    }
    SDL_WM_SetCaption("Tower Defense", NULL); // Title

    while(1)
    {
        // Initialisation de variable
        choixMenu = 0;
        level = 0;
        iMouseX = 0;
        iMouseY = 0;
        continuer = 1;
        pos_curs.x = 0;
        pos_curs.y = 0;

        /* ---------------------------------------------------------------------------------- */
        /* --------------------------------- MENU PRINCIPAL --------------------------------- */
        /* ----------------------------- CHARGEMENT DES IMAGES ------------------------------ */
        /* ---------------------------------------------------------------------------------- */

        // Chargement des images
        SDL_Surface* Loading = SDL_LoadBMP("Pictures/Loading screen.bmp");
        if (!Loading)
        {
            printf("Impossibilite de charger l'image: Loading screen\n");
            return 1;
        }
        SDL_BlitSurface(Loading, 0, screen, 0);
        SDL_Flip(screen);
        SDL_Surface* Loading1 = SDL_LoadBMP("Pictures/Loading screen 1.bmp");
        if (!Loading1)
        {
            printf("Impossibilite de charger l'image: Loading screen 1\n");
            return 1;
        }
        SDL_Surface* Loading2 = SDL_LoadBMP("Pictures/Loading screen 2.bmp");
        if (!Loading2)
        {
            printf("Impossibilite de charger l'image: Loading screen 2\n");
            return 1;
        }
        SDL_BlitSurface(Loading1, 0, screen,0);
        SDL_Flip(screen);
        SDL_Surface* Loading3 = SDL_LoadBMP("Pictures/Loading screen 3.bmp");
        if (!Loading3)
        {
            printf("Impossibilite de charger l'image: Loading screen 3\n");
            return 1;
        }
        SDL_Surface* Loading4 = SDL_LoadBMP("Pictures/Loading screen 4.bmp");
        if (!Loading4)
        {
            printf("Impossibilite de charger l'image: Loading screen 4\n");
            return 1;
        }
        SDL_BlitSurface(Loading2, 0, screen,0);
        SDL_Flip(screen);
        SDL_Surface* Curseur = SDL_LoadBMP("Pictures/Curseur.bmp");
        if (!Curseur)
        {
            printf("Impossibilite de charger l'image: Curseur\n");
            return 1;
        }
        SDL_SetColorKey(Curseur, SDL_SRCCOLORKEY, SDL_MapRGB(Curseur->format, 255, 255, 255));
        SDL_Surface* Menu = SDL_LoadBMP("Pictures/Menu 1.bmp");
        if (!Menu)
        {
            printf("Impossibilite de charger l'image: Menu 1\n");
            return 1;
        }
        SDL_BlitSurface(Loading3, 0, screen,0);
        SDL_Flip(screen);
        SDL_Surface* Menubtt1 = SDL_LoadBMP("Pictures/Menu 1-1.bmp");
        if (!Menubtt1)
        {
            printf("Impossibilite de charger l'image: Menu 1-1\n");
            return 1;
        }
        SDL_Surface* Menubtt2 = SDL_LoadBMP("Pictures/Menu 1-2.bmp");
        if (!Menubtt2)
        {
            printf("Impossibilite de charger l'image: Menu 1-2\n");
            return 1;
        }
        SDL_BlitSurface(Loading4, 0, screen,0);
        SDL_Flip(screen);
        SDL_Surface* Menubtt3 = SDL_LoadBMP("Pictures/Menu 1-3.bmp");
        if (!Menubtt3)
        {
            printf("Impossibilite de charger l'image: Menu 1-3\n");
            return 1;
        }
        SDL_Surface* Menubtt4 = SDL_LoadBMP("Pictures/Menu 1-4.bmp");
        if (!Menubtt3)
        {
            printf("Impossibilite de charger l'image: Menu 1-4\n");
            return 1;
        }

        // Menu principal
        while(continuer == 1)
        {
            while(SDL_PollEvent(&event))
            {
                switch(event.type)
                {
                    case SDL_MOUSEMOTION :
                    {
                        iMouseX = event.motion.x;
                        iMouseY = event.motion.y;
                        pos_curs.x = iMouseX;
                        pos_curs.y = iMouseY;
                        break;
                    }
                    case SDL_QUIT:
                        return 0;
                    case SDL_MOUSEBUTTONUP: //relachement du clic de la souris
                    {
                        if(event.button.button==SDL_BUTTON_LEFT)  //si clic gauche
                        {
                            if(iMouseX > 270 && iMouseX<945 && iMouseY>203 && iMouseY<346)
                            {
                                choixMenu = 1; // Nouvelle partie
                                continuer = 0;
                            }
                            if(iMouseX>270 && iMouseX<945 && iMouseY>378 && iMouseY<520)
                            {
                                choixMenu = 2; // Chargement d'une partie
                                continuer = 0;
                            }
                            if(iMouseX>270 && iMouseX<945 && iMouseY>552 && iMouseY<691)
                            {
                                choixMenu = 3; // Edition d'une map
                                continuer = 0;
                            }
                            if(iMouseX>270 && iMouseX<945 && iMouseY>723 && iMouseY<865)
                                return 0; // Quitter
                        }
                        break;
                    }
                } // Fin du switch des événements
            } // Fin while PollEvent
            SDL_FillRect(screen, 0, SDL_MapRGB(screen->format, 0, 0, 0));
            SDL_BlitSurface(Curseur, 0, screen, &pos_curs);

            if(iMouseX>270 && iMouseX<945 && iMouseY>203 && iMouseY<346)
                SDL_BlitSurface(Menubtt1, 0, screen, 0);
            else if(iMouseX>270 && iMouseX<945 && iMouseY>378 && iMouseY<520)
                SDL_BlitSurface(Menubtt2, 0, screen, 0);
            else if(iMouseX>270 && iMouseX<945 && iMouseY>552 && iMouseY<691)
                SDL_BlitSurface(Menubtt3, 0, screen, 0);
            else if(iMouseX>270 && iMouseX<945 && iMouseY>723 && iMouseY<865)
                SDL_BlitSurface(Menubtt4, 0, screen, 0);
            else
                SDL_BlitSurface(Menu, 0, screen, 0);

            SDL_BlitSurface(Curseur, 0, screen, &pos_curs);
            SDL_Flip(screen);
        }
        // Libération de mémoire
        SDL_FreeSurface(Menu);
        SDL_FreeSurface(Menubtt1);
        SDL_FreeSurface(Menubtt2);
        SDL_FreeSurface(Menubtt3);
        SDL_FreeSurface(Menubtt4);

        /* ---------------------------------------------------------------------------------- */
        /* -------------------------------- MENU SECONDAIRE --------------------------------- */
        /* ----------------------------- CHARGEMENT DES IMAGES ------------------------------ */
        /* ---------------------------------------------------------------------------------- */

        // Chargement des images
        continuer = 1;
        SDL_BlitSurface(Loading, 0, screen,0);
        SDL_Flip(screen);
        SDL_Surface* Choixlvl = SDL_LoadBMP("Pictures/choixlvl.bmp");
        if (!Choixlvl)
        {
            printf("Impossibilite de charger l'image: choixlvl\n");
            return 1;
        }
        SDL_BlitSurface(Loading1, 0, screen,0);
        SDL_Flip(screen);
        SDL_Surface* Choixlvl1 = SDL_LoadBMP("Pictures/choixlvl1.bmp");
        if (!Choixlvl1)
        {
            printf("Impossibilite de charger l'image: choixlvl1\n");
            return 1;
        }
        SDL_BlitSurface(Loading2, 0, screen,0);
        SDL_Flip(screen);
        SDL_Surface* Choixlvl2 = SDL_LoadBMP("Pictures/choixlvl2.bmp");
        if (!Choixlvl2)
        {
            printf("Impossibilite de charger l'image: choixlvl2\n");
            return 1;
        }
        SDL_BlitSurface(Loading3, 0, screen,0);
        SDL_Flip(screen);
        SDL_Surface* Choixlvl3 = SDL_LoadBMP("Pictures/choixlvl3.bmp");
        if (!Choixlvl3)
        {
            printf("Impossibilite de charger l'image: choixlvl3\n");
            return 1;
        }
        SDL_BlitSurface(Loading4, 0, screen,0);
        SDL_Flip(screen);
        SDL_Surface* Choixlvl4 = SDL_LoadBMP("Pictures/choixlvl4.bmp");
        if (!Choixlvl4)
        {
            printf("Impossibilite de charger l'image: choixlvl4\n");
            return 1;
        }

        // Menu secondaire
        if(choixMenu == 1) // Game
        {
            while(continuer == 1)
            {
                while(SDL_PollEvent(&event))
                {
                    switch(event.type)
                    {
                        case SDL_QUIT:
                            return 0;
                        case SDL_MOUSEMOTION :
                        {
                            iMouseX=event.motion.x;
                            iMouseY=event.motion.y;
                            pos_curs.x=iMouseX;
                            pos_curs.y=iMouseY;
                            SDL_BlitSurface(Curseur, 0, screen, &pos_curs);
                            SDL_Flip(screen);
                            break;
                        }
                        case SDL_MOUSEBUTTONUP: //relachement du clic de la souris
                        {
                            if(event.button.button==SDL_BUTTON_LEFT)  //si clic gauche
                            {
                                if(iMouseX>132 && iMouseX<430 && iMouseY>195 && iMouseY<492)
                                {
                                    level = 1;
                                    continuer = 0;
                                }
                                if(iMouseX>770 && iMouseX<1068 && iMouseY>195 && iMouseY<492)
                                {
                                    level = 2;
                                    continuer = 0;
                                }
                                if(iMouseX>132 && iMouseX<430 && iMouseY>450 && iMouseY<750)
                                {
                                    level = 3;
                                    continuer = 0;
                                }
                                if(iMouseX>770 && iMouseX<1068 && iMouseY>450 && iMouseY<750)
                                {
                                    level = 4;
                                    continuer = 0;
                                }
                            }
                            break;
                        }
                    } // Fin du switch des événements
                } // Fin while PollEvent
                SDL_FillRect(screen, 0, SDL_MapRGB(screen->format, 0, 0, 0));
                SDL_BlitSurface(Choixlvl, 0, screen, 0);

                if (iMouseX>132 && iMouseX<430 && iMouseY>195 && iMouseY<492)
                    SDL_BlitSurface(Choixlvl1, 0, screen, 0);
                else if(iMouseX>770 && iMouseX<1068 && iMouseY>195 && iMouseY<492)
                    SDL_BlitSurface(Choixlvl2, 0, screen, 0);
                else if(iMouseX>132 && iMouseX<430 && iMouseY>450 && iMouseY<750)
                    SDL_BlitSurface(Choixlvl3, 0, screen, 0);
                else if(iMouseX>770 && iMouseX<1068 && iMouseY>450 && iMouseY<750)
                    SDL_BlitSurface(Choixlvl4, 0, screen, 0);
                else
                    SDL_BlitSurface(Choixlvl, 0, screen, 0);
            }
            SDL_FreeSurface(Choixlvl);
            SDL_FreeSurface(Choixlvl1);
            SDL_FreeSurface(Choixlvl2);
            SDL_FreeSurface(Choixlvl3);
            SDL_FreeSurface(Choixlvl4);
            game(level, screen);
        }
        else if(choixMenu == 2) // Loader
        {
            level = 0;
            game(level, screen);
        }
        else if(choixMenu == 3) // Editor
            game(5, screen);
        else if(choixMenu == 4) // Quitter
            return 0;

        SDL_FreeSurface(Loading);
        SDL_FreeSurface(Loading1);
        SDL_FreeSurface(Loading2);
        SDL_FreeSurface(Loading3);
        SDL_FreeSurface(Loading4);
        SDL_FreeSurface(Choixlvl);
        SDL_FreeSurface(Choixlvl1);
        SDL_FreeSurface(Choixlvl2);
        SDL_FreeSurface(Choixlvl3);
        SDL_FreeSurface(Choixlvl4);
    }

    SDL_Quit(); // On quitte la SDL

    return 0;
}
