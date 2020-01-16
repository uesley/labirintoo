#include <stdlib.h>
#include <stdio.h>
#include "Labirintilt.h"
#include "assertions.h"

void test_create_player();

void test_create_game();

void test_create_traffic();

void test_create_space();

void test_move_player();

void test_move_scenario();

void test_colision();

void test_survive();

void test_creation_new_spaces();

void test_passa_level();

int main ()
{
    test_colision();
    test_create_player();
    test_create_space();
    test_create_traffic();
    test_create_game();
    test_move_player();
    test_move_scenario();
    test_survive();
//    test_creation_new_spaces();
}

void test_create_player()
{
    Player player;
    new_Player(&player);
    
    assertEquals(60, player.x);
    assertEquals(0, player.y);
    assertEquals(3, player.lives);
    printf("Create Player OK\n");
}

void test_create_space()
{
    Space space;
    new_Space(&space, 20);

    assertEquals(20, space.x_start);
    assertEquals(20 + 15, space.x_final);
    printf("Create Space OK\n");
}

void test_create_traffic()
{
    Traffic traffic;
    new_Traffic(&traffic);
    
    assertGreaterThan(0, traffic.num_spaces);
    int i;
    for (i = 0; i < traffic.num_spaces; i++) {
        assertEquals(traffic.spaces[i].x_start + 15, traffic.spaces[i].x_final);
    }
    printf("Create Traffic OK\n");
}

void test_create_game()
{
    Game game;
    
    new_Game(&game);
    
    assertEquals(1, game.level);
    assertEquals(3, game.player.lives);
    assertGreaterThan(1, game.traffics[0].num_spaces);
    assertGreaterThan(1, game.traffics[1].num_spaces);
    assertGreaterThan(1, game.traffics[2].num_spaces);
    assertGreaterThan(1, game.traffics[3].num_spaces);
    
    printf("Create Game OK\n");
}

void test_move_player()
{
    #ifndef GLUT_KEY_LEFT
        #define GLUT_KEY_LEFT 0
        #define GLUT_KEY_UP 1
        #define GLUT_KEY_RIGHT 2
        #define GLUT_KEY_DOWN 3
    #endif
    
    Player player;
    new_Player(&player);
    player.x = 60;
    player.y = 20;
    
    move_player(GLUT_KEY_LEFT, &player);
    assertEquals(55, player.x);
    
    move_player(GLUT_KEY_UP, &player);
    assertEquals(25, player.y);
    
    move_player(GLUT_KEY_RIGHT, &player);
    assertEquals(60, player.x);
    
    move_player(GLUT_KEY_DOWN, &player);
    assertEquals(20, player.y);
    
    printf("move player OK\n");
}

void test_move_scenario()
{
    Game game;
    new_Game(&game);
    
    int i;
    
    for (i = 0; i < 4; i++) {
        game.traffics[i].speed = 1 + i;
        game.traffics[i].num_spaces = 1;
        game.traffics[i].spaces[0].x_start = 20;
        game.traffics[i].spaces[0].x_final = 30;
    }
    
    move_scenario(&game, 1);
    for (i = 0; i < 4; i ++) {
        assertEquals(21, game.traffics[i].spaces[0].x_start);
        assertEquals(31, game.traffics[i].spaces[0].x_final);
    }
    
    move_scenario(&game, 2);
    assertEquals(21, game.traffics[0].spaces[0].x_start);
    assertEquals(31, game.traffics[0].spaces[0].x_final);
    for (i = 1; i < 4; i ++) {
        assertEquals(22, game.traffics[i].spaces[0].x_start);
        assertEquals(32, game.traffics[i].spaces[0].x_final);
    }
    
    move_scenario(&game, 3);
    assertEquals(21, game.traffics[0].spaces[0].x_start);
    assertEquals(31, game.traffics[0].spaces[0].x_final);
    assertEquals(22, game.traffics[1].spaces[0].x_start);
    assertEquals(32, game.traffics[1].spaces[0].x_final);
    for (i = 2; i < 4; i ++) {
        assertEquals(23, game.traffics[i].spaces[0].x_start);
        assertEquals(33, game.traffics[i].spaces[0].x_final);
    }
    
    move_scenario(&game, 4);
    assertEquals(21, game.traffics[0].spaces[0].x_start);
    assertEquals(22, game.traffics[1].spaces[0].x_start);
    assertEquals(32, game.traffics[1].spaces[0].x_final);
    assertEquals(23, game.traffics[2].spaces[0].x_start);
    assertEquals(33, game.traffics[2].spaces[0].x_final);
    assertEquals(24, game.traffics[3].spaces[0].x_start);
    assertEquals(34, game.traffics[3].spaces[0].x_final);
    
    move_scenario(&game, 5);
    assertEquals(21, game.traffics[0].spaces[0].x_start);
    assertEquals(31, game.traffics[0].spaces[0].x_final);
    assertEquals(22, game.traffics[1].spaces[0].x_start);
    assertEquals(32, game.traffics[1].spaces[0].x_final);
    assertEquals(23, game.traffics[2].spaces[0].x_start);
    assertEquals(33, game.traffics[2].spaces[0].x_final);
    assertEquals(24, game.traffics[3].spaces[0].x_start);
    assertEquals(34, game.traffics[3].spaces[0].x_final);
    
    printf("move scenario OK\n");
}

void test_colision()
{
    Game game;
    new_Game(&game);
    new_Player(&game.player);
    
    game.traffics[0].num_spaces = 1;
    game.traffics[0].spaces[0].x_start = 50;
    game.traffics[0].spaces[0].x_final = 60;
    
    game.player.y = 10;
    game.player.x = 48;
    
    assertTrue(colision(game));
    
    game.player.x = 61;
   assertTrue(colision(game));
    
    game.player.x = 56;
    assertTrue(colision(game));
    
    printf("Colision OK\n");
}

void test_survive()
{
    Game game;
    new_Game(&game);
    
    
    game.player.x = 30;
    game.player.y = 30;
    survive(&game);
    
    assertEquals(2, game.player.lives);
    assertEquals(60, game.player.x);
    assertEquals(0, game.player.y);
    
    game.player.x = 30;
    game.player.y = 30;
    survive(&game);
    assertEquals(1, game.player.lives);
    assertEquals(60, game.player.x);
    assertEquals(0, game.player.y);
    
    game.player.x = 30;
    game.player.y = 30;
    survive(&game);
    assertEquals(0, game.player.lives);
    
    printf("Survive OK\n");
}