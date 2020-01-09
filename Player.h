#ifndef PLAYER_H
#define PLAYER_H

typedef struct {
    int x; // posição horizontal do jogador
    int y; // posição vertical do jogador
    int lives; // quantidade de vidas restantes
} Player;


// Inicia 
void new_Player(Player *);

// Coloca as coordenadas iniciais do jogador
int reset_position_player(Player *);

// Diminui a quantidade de vidas e retorna a quantidade restante
int die(Player * player);

// Controla as coordenadas do jogador ao se mover
int move_player(Player * player, int step_up, int step_down, int step_right, int step_left);




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
    player->lives --;
    return player->lives;
}

int move_player(Player * player, int step_up, int step_down, int step_right, int step_left)
{
    player->y += step_up - step_down;
    player->x += step_right - step_left; 
}

void describe_player(Player player)
{
    printf("---PLAYER----\nlives: %d\nx: %d\ny: %d\n\n", player.lives, player.x, player.y);
}

#endif /* PLAYER_H */