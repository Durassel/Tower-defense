    /* ---------------------------------------------------------------------------------- */
    /* ----------------------------------- PATHFINDING ---------------------------------- */
    /* ---------------------------------------------------------------------------------- */

    int test(cell board[LIGNES][COLONNES], int x, int y);
    int cost(cell board[LIGNES][COLONNES], coordinates Exit, int nbPoints, int *listeX, int *listeY);
    void road(cell board[LIGNES][COLONNES], coordinates Exit, coordinates Enter);
    int pathfinding(cell board[LIGNES][COLONNES], coordinates Exit, coordinates Enter);
