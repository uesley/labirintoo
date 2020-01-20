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
    int i,j;
    Space * space;
    Traffic traffic;
    for (i = 0; i < STAGES / 2; i ++) {
        if (game->traffics[i].speed < speed_min) {
            continue;
        }
        traffic = game->traffics[i];
        for (space = traffic.first_space, j =0; j < traffic.num_spaces; j ++ , space = space->next) {
        	space->x_start++;
        	space->x_final++;
            if (space->x_start > 120) {
            	srand(time(NULL));
                space->x_final = 0;
                space->x_start = -15;
                rotateTraffic(&(game->traffics[i]), space);
            }
        }
    }
    speed_min = (speed_min++) % 5;
}

int colision(Game game) {
    int stage = (game.player.y) / 5;	
//    printf("\nstage: %d\n",stage);
    if (stage % 2 == 0) {
    	return 0;
	}
    Traffic traffic = game.traffics[stage / 2];
    Space * space;
	int count;
    for (space = traffic.first_space, count = 0;count < traffic.num_spaces; count++, space = space->next) {
        if ((game.player.x >= space->x_start) && (game.player.x + 5 <= space->x_final)) {
            return 0;
        }
    }
    return 1;
}

int survive(Game * game) {
    return die(&game->player);
}

void next_level(Game * game) {
	game->level ++;
	game->player.lives ++;
	describe_player(game->player);
	reset_position_player(&game->player);
}

int win(Game game) {
	int stage = game.player.y / 5 + 1;
	return stage == STAGES;
}

#endif /* LABIRINTILT_H */
