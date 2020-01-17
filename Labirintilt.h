#ifndef LABIRINTILT_H
#define LABIRINTILT_H

#include <stdlib.h>

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
        printf("stage: %d   ", i);
        describe_traffic(game.traffics[i]);
        printf("\n\n");
    }
}

void move_scenario(Game * game, int speed_min) 
{
    int i;
    Space * space;
    Traffic traffic;
    for (i = 0; i < STAGES / 2; i ++) {
        if (game->traffics[i].speed < speed_min) {
            continue;
        }
        traffic = game->traffics[i];
        for (space = traffic.first_space; space; space = space->next) {
        	space->x_start++;
        	space->x_final++;
            if (space->x_start > 120) {
                int pos = rand() % (120 / game->traffics[i].num_spaces);
                game->traffics[i].spaces[j].x_final = -1 * pos;
                game->traffics[i].spaces[j].x_start =  -1 * (pos +15);
            }
        }
    }
    speed_min = (speed_min++) % 5;
}

int colision(Game game) {
    int stage = game.player.y / 10 -1;
    Traffic traffic = game.traffics[stage/2];
    Space space;
    int i;
    
    for (i = 0; i < traffic.num_spaces; i++) {
        space = traffic.spaces[i];
        if ((game.player.x >space.x_start) && (game.player.x + 5 < space.x_final)) {
            return 0;
        }
    }
    return 1;
}

int survive(Game * game) {
    return die(&game->player);
}

#endif /* LABIRINTILT_H */
