#ifndef LABIRINTILT_H
#define LABIRINTILT_H

#include "Player.h"
#include "Scenario.h"

#define STAGES 9

typedef struct {
    int level;
    Player player;
    Traffic traffics[4];
} Game;

void new_Game(Game * game)
{
    game->level = 1;
    new_Player(&(game->player));
    int i;
    
    for (i = 0; i < STAGES / 2; i ++) {
        new_Traffic(&(game->traffics[i]));    
    }
}

void describe_scenario(Game game)
{
    int i;
    for (i = 3; i >=0; i--) {
        describe_traffic(game.traffics[i]);
        printf("\n\n");
    }
}


int colision(Player player, int stage);


#endif /* LABIRINTILT_H */

