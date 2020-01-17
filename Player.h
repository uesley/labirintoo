#ifndef PLAYER_H
#define PLAYER_H

#define PLAYER_STEP 5

typedef struct {
    int x; // posição horizontal do jogador
    int y; // posição vertical do jogador
    int lives; // quantidade de vidas restantes
} Player;


typedef int (*FunctionMove) (Player * player);

// Inicia 
void new_Player(Player *);

// Coloca as coordenadas iniciais do jogador
int reset_position_player(Player *);

// Diminui a quantidade de vidas e retorna a quantidade restante
int die(Player * player);

void new_Player(Player * player)
{
    player->lives = 3;
    reset_position_player(player);
}

int reset_position_player(Player * player)
{
    player->x = 60;
    player->y = 0;
}

int die(Player * player)
{
    reset_position_player(player);
    return --player->lives;
}



int move_player_up(Player * player) {
	if (player->y > 35) {
		return 0;
	}
    player->y = player->y + PLAYER_STEP;
}

int move_player_down(Player * player) {
	if (player->y <= 0) {
		return 0;
	}
    player->y = player->y - PLAYER_STEP;
}

int move_player_left(Player * player) {
	if (player->x <= 0) {
		return 0;
	}
    player->x = player->x - PLAYER_STEP;
}

int move_player_right(Player * player) {
	if (player->x >= 115) {
		return 0;
	}
    player->x = player->x + PLAYER_STEP;
}

void move_player(int key, Player * player) {
    FunctionMove function_move[4] = {
        move_player_left,
        move_player_up,
        move_player_right,
        move_player_down
    };

    (*(function_move[key]))(player);
}

void describe_player(Player player)
{
    printf("---PLAYER----\nlives: %d\nx: %d\ny: %d\n\n", player.lives, player.x, player.y);
}

#endif /* PLAYER_H */
