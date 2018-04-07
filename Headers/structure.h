#ifndef INCLUDE
    #define INCLUDE

    #include "../Sources/defines.c"

/* ---------------------------------------------------------------------------------- */
/* ----------------------------------- STRUCTURES ----------------------------------- */
/* ---------------------------------------------------------------------------------- */

    typedef struct cell cell;
    struct cell
    {
        int type; // Type permet de savoir sur quoi pointe le pointeur (0 = null (vide), 1 = path, 2 = defense, 3 = enemy)
        void *actor; // Pointeur sur structure path/enemy/defense
        cell *next; // Pointeur sur la prochaine case du chemin
    };

    typedef struct coordinates coordinates;
    struct coordinates
    {
        int x;
        int y;
    };

    typedef struct defense defense;
    struct defense
    {
        int type; // Type de défense
        int price; // Prix de la construction
        int damage; // Dommages
        int range; // Portée
        float rate; // Vitesse d'attaque
        clock_t lastAttack; // Temps de la dernière attaque
        coordinates shot; // Coordonnées du projectile
        clock_t shotTime; // Dernier temps de déplacement du projectile
        int attack; // Permet de savoir si la tour est en train d'attaquer
    };

    typedef struct enemy enemy;
    struct enemy
    {
        int health; // Vie
        coordinates relativePosition; // Position relative (pixels)
        float timeBeforeTurn; // Temps restant avant de changer de case
        int direction;
    };

    typedef struct detection detection;
    struct detection
    {
        int x;
        int y;
        int nbCells; // Nombre de cases parcourues par l'ennemi
    };

#endif
