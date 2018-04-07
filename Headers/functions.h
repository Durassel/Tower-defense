/* ---------------------------------------------------------------------------------- */
/* ----------------------------------- PROTOTYPES ----------------------------------- */
/* ---------------------------------------------------------------------------------- */

    /* ---------------------------------------------------------------------------------- */
    /* -------------------------------------- SDL --------------------------------------- */
    /* ---------------------------------------------------------------------------------- */

    int pause_clic(void);
    void refreshBoard(cell board[LIGNES][COLONNES], coordinates entryPoint, int iMouseX, int iMouseY, int *life, int *gold, int *wave, SDL_Surface* screen, SDL_Surface* Terre, int *choix_tour, int *descript, int *tour, int *selection, int *ameliorer, int *detruire, SDL_Surface* Porte_arche, SDL_Surface* Porte_mortier, SDL_Surface* Porte_tde, SDL_Surface* Chemin_Vertical, SDL_Surface* Chemin_Horizontal, SDL_Surface* Chemin_Bas_droite, SDL_Surface* Chemin_Bas_gauche, SDL_Surface* Chemin_Haut_droite, SDL_Surface* Chemin_Haut_gauche, SDL_Surface* ATH, SDL_Surface* ATH_Tour1, SDL_Surface* ATH_Tour2, SDL_Surface* ATH_Tour3, SDL_Surface* Tour1, SDL_Surface* Tour12, SDL_Surface* Tour13, SDL_Surface* Tour2, SDL_Surface* Tour22, SDL_Surface* Tour23, SDL_Surface* Tour3, SDL_Surface* Tour32, SDL_Surface* Tour33, SDL_Surface* Tour_transp1, SDL_Surface* Tour_transp2, SDL_Surface* Tour_transp3, SDL_Surface* Description_Tour11, SDL_Surface* Description_Tour12, SDL_Surface* Description_Tour13, SDL_Surface* Description_Tour21, SDL_Surface* Description_Tour22, SDL_Surface* Description_Tour23, SDL_Surface* Description_Tour31, SDL_Surface* Description_Tour32, SDL_Surface* Description_Tour33, SDL_Surface* Coeur_Plein, SDL_Surface* Coeur_Demi, SDL_Surface* Coeur_Vide, SDL_Surface* Argent, SDL_Surface* Tir, SDL_Surface* Tir2, SDL_Surface* Tir3, SDL_Surface* Ennemi, SDL_Surface* Ameliorer, SDL_Surface* Detruire, SDL_Surface* Chiffre0, SDL_Surface* Chiffre1, SDL_Surface* Chiffre2, SDL_Surface* Chiffre3, SDL_Surface* Chiffre4, SDL_Surface* Chiffre5, SDL_Surface* Chiffre6, SDL_Surface* Chiffre7, SDL_Surface* Chiffre8, SDL_Surface* Chiffre9, SDL_Surface* Vague);

    /* ---------------------------------------------------------------------------------- */
    /* ------------------------------ FONCTIONS PRINCIPALES ----------------------------- */
    /* ---------------------------------------------------------------------------------- */

    void game(int level, SDL_Surface* screen);
    void editor(cell board[LIGNES][COLONNES], coordinates *entryPoint, coordinates *exitPoint, SDL_Surface *screen, SDL_Surface *Terre, int *level);
    void loader(cell board[LIGNES][COLONNES], int *level, int *life, int *gold, coordinates *entryPoint, coordinates *exitPoint, int *wave);
    void save(cell board[LIGNES][COLONNES], int level, int life, int gold, coordinates entryPoint, coordinates exitPoint, int wave);

    /* ---------------------------------------------------------------------------------- */
    /* -------------------------------------- BOARD ------------------------------------- */
    /* ---------------------------------------------------------------------------------- */

    void initBoard(cell board[LIGNES][COLONNES], int level, coordinates *entryPoint, coordinates *exitPoint);
    void link(cell board[LIGNES][COLONNES], coordinates entryPoint);
    void setBlock(cell board[LIGNES][COLONNES], int level);
    void clearBoard(cell board[LIGNES][COLONNES], int numberReplacement, int replacedBy);

    /* ---------------------------------------------------------------------------------- */
    /* ------------------------------------- DEFENSE ------------------------------------ */
    /* ---------------------------------------------------------------------------------- */

    void initDefense(cell board[LIGNES][COLONNES], int x, int y, int type);
    int distanceEnemy(cell board[LIGNES][COLONNES], coordinates entryPoint, int x, int y);
    int arrondi(float nombre);
    coordinates lastCell(cell board[LIGNES][COLONNES], int x, int y, coordinates entryPoint);
    void detectEnemy(cell board[LIGNES][COLONNES], coordinates entryPoint, int x, int y, int *nbEnemyMain, clock_t t5, clock_t t8, int *gold);

    /* ---------------------------------------------------------------------------------- */
    /* ------------------------------------- ENNEMIS ------------------------------------ */
    /* ---------------------------------------------------------------------------------- */

    void waitTime(float temps);
    void moveEnemy(cell board[LIGNES][COLONNES], coordinates entryPoint);
    void coordinatesEnemy(cell board[LIGNES][COLONNES], coordinates entryPoint, coordinates exitPoint, int *nbEnemy, int *life);

    /* ---------------------------------------------------------------------------------- */
    /* ------------------------------------- LEVEL -------------------------------------- */
    /* ---------------------------------------------------------------------------------- */

    void initLevel(int level, int *nbWave, int *nbEnemyPerWave, float *creationTimeEnemy, float *positionTimeEnemy);
